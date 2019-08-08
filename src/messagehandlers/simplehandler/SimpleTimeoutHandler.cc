/*
 * SimpleTimeoutHandler.cc
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#include "SimpleTimeoutHandler.h"
#include "../../messages/basicmessages/NetworkTimeoutMsg_m.h"

/**
 * Timeout message handler for simplebot
 */
SimpleTimeoutHandler::SimpleTimeoutHandler(NodeBase* owner) {
    node = static_cast<SimpleBot*>(owner);
}

/**
 * Destructor
 */
SimpleTimeoutHandler::~SimpleTimeoutHandler() {
}

/**
 * Handler for simplebot timeout messages
 */
void SimpleTimeoutHandler::handleMessage(BasicNetworkMsg* msg) {
    if (msg->getType() == TIMEOUT) {
        NetworkTimeoutMsg* timeout = static_cast<NetworkTimeoutMsg*>(msg);
        if (timeout->getTimeouttype() == PING) {
            handlePingTimeout(timeout);
        } else if (timeout->getTimeouttype() == PONG) {
            //DO nothing
        } else if (timeout->getTimeouttype() == NL_REQ) {
            //DO nothing
        } else if (timeout->getTimeouttype() == NL_RESP) {
            //DO nothing
        }
    }
}

/**
 * Removes the timed out node from the neighborlist and
 * queries for new neighbors if the NL size is below NLMinThreshold
 */
void SimpleTimeoutHandler::handlePingTimeout(NetworkTimeoutMsg* timeout) {
    node->removeNeighbor(timeout->getSrcNode());
//    if(node->NL->getSize() < node->NLMinThreshold){
//        node->requestNeighbors();
//    }
}
