/*
 * SimpleMsgHandler.cc
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#include "SimpleMsgHandler.h"
#include "../../nodes/simplebot/SimpleBot.h"
#include "../../messages/simplemessages/SimpleNLRespMsg_m.h"
#include "../../messages/simplemessages/PongMsg_m.h"
#include "../../messages/simplemessages/CmdReqMsg_m.h"
#include "../../messages/simplemessages/CmdRepMsg_m.h"


/**
 * Message handler for standard messages used by simplebot
 */
SimpleMsgHandler::SimpleMsgHandler(NodeBase* owner) {
    node = static_cast<SimpleBot*>(owner);
}

/**
 * Destructor
 */
SimpleMsgHandler::~SimpleMsgHandler() {
}

/**
 * Handler method for standard messages used by simplebot
 */
void SimpleMsgHandler::handleMessage(BasicNetworkMsg *msg) {
    if (node->isActive()) {
        if (msg->getType() == NL_REQ) {
            handleNLReq(msg);
        } else if (msg->getType() == NL_RESP) {
            handleNLResp(msg);
        } else if (msg->getType() == PING) {
            handlePingMsg(msg);
        } else if (msg->getType() == PONG) {
            handlePongMsg(msg);
        } else if (msg->getType() == CMD_REQ) {
            handleCmdReq(msg);
        } else if (msg->getType() == CMD_REP) {
            handleCmdRep(msg);
        }
    }
}

/**
 * Handle a simplebot NL request
 */
void SimpleMsgHandler::handleNLReq(BasicNetworkMsg* msg) {
    node->sendNLResp(msg);
}

/**
 * Handle a simplebot NL response
 */
void SimpleMsgHandler::handleNLResp(BasicNetworkMsg* msg) {
    SimpleNLRespMsg* resp = static_cast<SimpleNLRespMsg*>(msg);
    for (unsigned int i = 0; i < resp->getNeighbors()->size(); i++) {
        node->addNeighbor(resp->getNeighbors()->at(i));
    }
    node->continueMM();
}

/**
 * Handle a simplebot Ping message
 */
void SimpleMsgHandler::handlePingMsg(BasicNetworkMsg* msg) {
    node->sendPong(msg);
}

/**
 * Handle a simplebot Pong message
 */
void SimpleMsgHandler::handlePongMsg(BasicNetworkMsg* msg) {
    node->NL->update(simTime(), msg->getSrcNode());
    PongMsg* pong = static_cast<PongMsg*>(msg);
    if(pong->getVersion() > node->getVersion()){
        node->sendCmdReq(msg);
    }
    node->continueMM(msg->getSrcNode());
}

void SimpleMsgHandler::handleCmdReq(BasicNetworkMsg* msg){
//    CmdReqMsg* req = static_cast<CmdReqMsg*>(msg);
    node->sendCmdRep(msg);
}

void SimpleMsgHandler::handleCmdRep(BasicNetworkMsg* msg){
    CmdRepMsg* rep = static_cast<CmdRepMsg*>(msg);
    if(rep->getVersion() > node->getVersion()){
        node->setVersion(rep->getVersion());
    }
}
