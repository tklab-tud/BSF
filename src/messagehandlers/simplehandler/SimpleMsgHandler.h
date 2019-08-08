/*
 * SimpleMsgHandler.h
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#ifndef MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLEMSGHANDLER_H_
#define MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLEMSGHANDLER_H_

#include "../basichandler/BasicMessageHandler.h"
#include "../../nodes/simplebot/SimpleBot.h"
class SimpleBot;

class SimpleMsgHandler: public BasicMessageHandler {
public:
    SimpleMsgHandler(NodeBase* owner);
    virtual ~SimpleMsgHandler();
    void handleMessage(BasicNetworkMsg *msg);
    void handleNLReq(BasicNetworkMsg* msg);
    void handleNLResp(BasicNetworkMsg* msg);
    void handlePingMsg(BasicNetworkMsg* msg);
    void handlePongMsg(BasicNetworkMsg* msg);
    SimpleBot* node;
};

#endif /* MESSAGEHANDLERS_SIMPLEHANDLER_SIMPLEMSGHANDLER_H_ */
