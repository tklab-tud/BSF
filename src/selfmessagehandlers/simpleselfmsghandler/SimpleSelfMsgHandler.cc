/*
 * SimpleSelfMsgHandler.cc
 *
 *  Created on: Mar 20, 2017
 *      Author: xtikka
 */

#include "SimpleSelfMsgHandler.h"

#include "../../nodes/simplebot/SimpleBot.h"

/**
 * Constructor for the standard self message handler of simple bot
 */
SimpleSelfMsgHandler::SimpleSelfMsgHandler(NodeBase* owner, int interval) {
    node = static_cast<SimpleBot*>(owner);
    mm_cycle_msg = new BasicSelfMsg("mm_cycle_msg");
    mm_interval = interval;
}

/**
 * Destructor
 */
SimpleSelfMsgHandler::~SimpleSelfMsgHandler() {
    node->cancelEvent(mm_cycle_msg);
    delete mm_cycle_msg;
}

/**
 * This message is called for every self message
 *
 * if the self message is handled by this class this method returns true,
 * otherwise it will return false and leave the handling of the self message to another module
 */
bool SimpleSelfMsgHandler::handleSelfMessage(BasicSelfMsg* msg) {
    if (msg == mm_cycle_msg) {
        if (node->isActive()) {
            node->mmCycle();
        }
        return true;
    }
    return false;
}

/**
 * Cancels all current self messages associated by this handler
 */
void SimpleSelfMsgHandler::cancelEvents() {
    node->cancelEvent(mm_cycle_msg);
}

/**
 * Reschedules all self messages associated with this handler
 */
void SimpleSelfMsgHandler::rescheduleEvents() {
    node->cancelEvent(mm_cycle_msg);
    node->scheduleAt(simTime() + mm_interval, mm_cycle_msg); //schedule next interval
}
