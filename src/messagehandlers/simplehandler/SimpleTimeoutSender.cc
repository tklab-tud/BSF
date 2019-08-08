/*
 * SimpleTimeoutHandler.cc
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#include "SimpleTimeoutSender.h"
#include "../../messages/basicmessages/NetworkTimeoutMsg_m.h"

SimpleTimeoutSender::SimpleTimeoutSender(NodeBase* owner) {
    node = static_cast<SimpleBot*>(owner);
}

SimpleTimeoutSender::~SimpleTimeoutSender() {

}

void SimpleTimeoutSender::handleMessage(BasicNetworkMsg* msg) {
    if (!node->isActive()) {
        NetworkTimeoutMsg* timeout = new NetworkTimeoutMsg();
        timeout->setTimeouttype(msg->getType());
        timeout->setSrcNode(node->getBasicID()->getBasicID());
        timeout->setDstNode(msg->getSrcNode());
        node->simpleSend(timeout, msg->getSrcNode());
    }
}
