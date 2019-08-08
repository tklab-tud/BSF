/*
 * BasicSelfMsgHandler.h
 *
 *  Created on: Mar 14, 2017
 *      Author: xtikka
 */

#ifndef SELFMESSAGEHANDLERS_BASICSELFMSGHANDLER_H_
#define SELFMESSAGEHANDLERS_BASICSELFMSGHANDLER_H_

#include "../../messages/basicmessages/BasicSelfMsg_m.h"

class NodeBase;

class BasicSelfMsgHandler {
public:
    BasicSelfMsgHandler();
    BasicSelfMsgHandler(NodeBase* owner);
    virtual ~BasicSelfMsgHandler();
    virtual bool handleSelfMessage(BasicSelfMsg* msg) = 0;
    virtual void cancelEvents() = 0;
    virtual void rescheduleEvents() = 0;
    NodeBase* node;
};

#endif /* SELFMESSAGEHANDLERS_BASICSELFMSGHANDLER_H_ */
