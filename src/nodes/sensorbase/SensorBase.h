#ifndef NODES_SENSORBASE_SENSORBASE_H_
#define NODES_SENSORBASE_SENSORBASE_H_

#include "omnetpp.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"
class MonitorData;

using namespace omnetpp;

class SensorBase {
public:
    BasicSelfMsg* boost_msg = new BasicSelfMsg("boost_msg");
    BasicSelfMsg* sensor_dump_msg = new BasicSelfMsg("sensor_dump_timer_msg");
    double boost_timeout = 1800;
    double sensor_dump_timeout;
    bool boosting = true;
    virtual void boost()=0;
    MonitorData* sensorLogic;
};

#endif /* NODES_SENSORBASE_SENSORBASE_H_ */
