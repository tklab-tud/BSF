#ifndef SELFMESSAGEHANDLERS_SENSORSELFMSGHANDLER_SENSORSELFMSGHANDLER_H_
#define SELFMESSAGEHANDLERS_SENSORSELFMSGHANDLER_SENSORSELFMSGHANDLER_H_

#include "../basicselfmsghandler/BasicSelfMsgHandler.h"
#include "../../nodes/sensorbase/SensorBase.h"
#include "../../nodes/nodebase/NodeBase.h"

class SensorSelfMsgHandler: public BasicSelfMsgHandler {
public:
    SensorSelfMsgHandler(NodeBase* node, SensorBase* sensor, double startTime);
    virtual ~SensorSelfMsgHandler();
    bool handleSelfMessage(BasicSelfMsg* msg);
    void cancelEvents();
    void rescheduleEvents();
    SensorBase* sensor;
    double startTime;
};

#endif /* SELFMESSAGEHANDLERS_SENSORSELFMSGHANDLER_SENSORSELFMSGHANDLER_H_ */
