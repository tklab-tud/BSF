/*
 * SimpleTimeoutHandler.h
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#ifndef MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTSENDER_H_
#define MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTSENDER_H_

#include "../../messagehandlers/basichandler/BasicMessageHandler.h"
#include "../../messages/basicmessages/BasicNetworkMsg_m.h"
#include "../../nodes/nodebase/NodeBase.h"
#include "../../nodes/simplebot/SimpleBot.h"

class SimpleTimeoutSender: public BasicMessageHandler {
public:
    SimpleTimeoutSender(NodeBase* owner);
    virtual ~SimpleTimeoutSender();
    void handleMessage(BasicNetworkMsg* msg);
    SimpleBot* node;
};

#endif /* MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLETIMEOUTSENDER_H_ */
