#include "SMDSelfMsgHandler.h"
#include "../../nodes/smdbase/SMDBase.h"
#include "../../nodes/nodebase/NodeBase.h"

SMDSelfMsgHandler::SMDSelfMsgHandler(NodeBase* node, SMDBase* smd,
        double startTime) {
    this->node = node;
    this->smd = smd;
    this->startTime = startTime;
}

SMDSelfMsgHandler::~SMDSelfMsgHandler() {
    delete smd->start_up_msg;
}

bool SMDSelfMsgHandler::handleSelfMessage(BasicSelfMsg* msg) {
    if (msg == smd->start_up_msg) {
        smd->startUp();

        return true;
    } else if (msg == smd->smd_dump_msg) {
        smd->smdLogic->dumpSensorData();
        double normalize = std::round(
                1 + SIMTIME_DBL(simTime() / smd->smd_dump_timeout));
        node->scheduleAt(0 + normalize * smd->smd_dump_timeout,
                smd->smd_dump_msg);
        return true;
    }
    return false;
}

void SMDSelfMsgHandler::cancelEvents() {
//    node->cancelEvent(sensor->boost_msg);

    node->cancelEvent(smd->smd_dump_msg);
}

void SMDSelfMsgHandler::rescheduleEvents() {
//    node->cancelEvent(sensor->boost_msg);
//    node->scheduleAt(simTime()+sensor->boost_timeout, sensor->boost_msg);

    node->cancelEvent(smd->smd_dump_msg);
    double normalize = std::round(
            1 + SIMTIME_DBL(simTime() / smd->smd_dump_timeout));
    node->scheduleAt(0 + normalize * smd->smd_dump_timeout, smd->smd_dump_msg);
}
