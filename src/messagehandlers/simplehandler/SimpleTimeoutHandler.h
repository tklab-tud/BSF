/*
 * SimpleTimeoutHandler.h
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#ifndef MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTHANDLER_H_
#define MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTHANDLER_H_

#include "../basichandler/BasicMessageHandler.h"
#include "../../messages/basicmessages/NetworkTimeoutMsg_m.h"
#include "../../nodes/simplebot/SimpleBot.h"

class SimpleTimeoutHandler: public BasicMessageHandler {
public:
    SimpleTimeoutHandler(NodeBase* owner);
    virtual ~SimpleTimeoutHandler();
    void handleMessage(BasicNetworkMsg* msg);
    void handlePingTimeout(NetworkTimeoutMsg* timeout);
    SimpleBot* node;
};

#endif /* MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTHANDLER_H_ */
