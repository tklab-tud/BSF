#ifndef NODES_SMDBASE_SMDBASE_H_
#define NODES_SMDBASE_SMDBASE_H_

#include "../../messages/basicmessages/BasicSelfMsg_m.h"
#include "../../monitoringdata/MonitorData.h"

class SMDBase {
public:
    BasicSelfMsg* smd_dump_msg = new BasicSelfMsg("smd_dump_timer_msg");
    BasicSelfMsg* start_up_msg = new BasicSelfMsg("smd_start_up_message");

    double smd_dump_timeout;
    MonitorData* smdLogic;

    virtual void startUp() = 0;
};

#endif /* NODES_SMDBASE_SMDBASE_H_ */
