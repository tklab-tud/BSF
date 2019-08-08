#include "SensorSelfMsgHandler.h"
#include "../../monitoringdata/MonitorData.h"

SensorSelfMsgHandler::SensorSelfMsgHandler(NodeBase* node, SensorBase* sensor,
        double startTime) {
    this->node = node;
    this->sensor = sensor;
    this->startTime = startTime;
}

SensorSelfMsgHandler::~SensorSelfMsgHandler() {
    node->cancelAndDelete(sensor->boost_msg);
}

bool SensorSelfMsgHandler::handleSelfMessage(BasicSelfMsg* msg) {
    if (msg == sensor->boost_msg) {
        if (node->isActive()) {
            if (simTime() > startTime) {
                sensor->boost();
            }
            node->scheduleAt(simTime() + sensor->boost_timeout,
                    sensor->boost_msg);
        }
        return true;
    } else if (msg == sensor->sensor_dump_msg) {
        sensor->sensorLogic->dumpSensorData();
        double normalize = std::round(
                1 + SIMTIME_DBL(simTime() / sensor->sensor_dump_timeout));
        node->scheduleAt(0 + normalize * sensor->sensor_dump_timeout,
                sensor->sensor_dump_msg);
        return true;
    }
    return false;
}

void SensorSelfMsgHandler::cancelEvents() {
    node->cancelEvent(sensor->boost_msg);

    node->cancelEvent(sensor->sensor_dump_msg);
}

void SensorSelfMsgHandler::rescheduleEvents() {
    node->cancelEvent(sensor->boost_msg);
    node->scheduleAt(simTime() + sensor->boost_timeout, sensor->boost_msg);

    node->cancelEvent(sensor->sensor_dump_msg);
    double normalize = std::round(
            1 + SIMTIME_DBL(simTime() / sensor->sensor_dump_timeout));
    node->scheduleAt(0 + normalize * sensor->sensor_dump_timeout,
            sensor->sensor_dump_msg);

}
