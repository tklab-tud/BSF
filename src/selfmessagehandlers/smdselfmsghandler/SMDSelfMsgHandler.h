#ifndef SELFMESSAGEHANDLERS_SMDSELFMSGHANDLER_SMDSELFMSGHANDLER_H_
#define SELFMESSAGEHANDLERS_SMDSELFMSGHANDLER_SMDSELFMSGHANDLER_H_

#include "../basicselfmsghandler/BasicSelfMsgHandler.h"
#include "../../nodes/smdbase/SMDBase.h"
#include "../../nodes/nodebase/NodeBase.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"

class SMDSelfMsgHandler: public BasicSelfMsgHandler {
public:
    SMDSelfMsgHandler(NodeBase* node, SMDBase* smd, double startTime);
    virtual ~SMDSelfMsgHandler();

    bool handleSelfMessage(BasicSelfMsg* msg);
    void cancelEvents();
    void rescheduleEvents();
    SMDBase* smd;
    double startTime;
};

#endif /* SELFMESSAGEHANDLERS_SMDSELFMSGHANDLER_SMDSELFMSGHANDLER_H_ */
