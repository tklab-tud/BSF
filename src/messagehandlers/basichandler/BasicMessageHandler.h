/*
 * BasicMessageHandler.h
 *
 *  Created on: Mar 13, 2017
 *      Author: xtikka
 */

#ifndef MESSAGEHANDLERS_BASICHANDLER_BASICMESSAGEHANDLER_H_
#define MESSAGEHANDLERS_BASICHANDLER_BASICMESSAGEHANDLER_H_

#include "../../messages/basicmessages/BasicNetworkMsg_m.h"

class NodeBase;

class BasicMessageHandler {
public:
    BasicMessageHandler();
    virtual ~BasicMessageHandler();
    virtual void handleMessage(BasicNetworkMsg *msg) = 0;
    BasicMessageHandler(NodeBase* owner);
    NodeBase* node;

};

#endif /* MESSAGEHANDLERS_BASICHANDLER_BASICMESSAGEHANDLER_H_ */
