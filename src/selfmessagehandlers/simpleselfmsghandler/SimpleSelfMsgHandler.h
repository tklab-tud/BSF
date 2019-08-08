/*
 * SimpleSelfMsgHandler.h
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#ifndef SELFMESSAGEHANDLERS_SIMPLESELFMSGHANDLER_SIMPLESELFMSGHANDLER_H_
#define SELFMESSAGEHANDLERS_SIMPLESELFMSGHANDLER_SIMPLESELFMSGHANDLER_H_

#include "../basicselfmsghandler/BasicSelfMsgHandler.h"
#include "../../nodes/simplebot/SimpleBot.h"
#include "../../nodes/nodebase/NodeBase.h"

class SimpleBot;

class SimpleSelfMsgHandler: public BasicSelfMsgHandler {
public:
    SimpleSelfMsgHandler(NodeBase* owner, int interval);
    virtual ~SimpleSelfMsgHandler();
    bool handleSelfMessage(BasicSelfMsg* msg);
    void cancelEvents();
    void rescheduleEvents();
    SimpleBot* node;
    BasicSelfMsg* mm_cycle_msg;
    int mm_interval;
};

#endif /* SELFMESSAGEHANDLERS_SIMPLESELFMSGHANDLER_SIMPLESELFMSGHANDLER_H_ */
