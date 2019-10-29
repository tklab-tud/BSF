#include <memory>
#include <omnetpp.h>
#include <iostream>

#include "NodeBase.h"
#include "../../routers/basicrouter/BasicRouter.h"
#include "../../messages/basicmessages/NetworkTimeoutMsg_m.h"
#include "../../churn/lifetimechurn/LifetimeChurn.h"

NodeBase::~NodeBase() {
}

/**
 * Standard method to connect a node to the underlay network
 */
void NodeBase::connectToUnderlay() {
    BasicRouter *router = static_cast<BasicRouter*>(getModuleByPath(
            "BasicNetwork.BasicRouter"));
    cDelayChannel* channel = cDelayChannel::create("chan");
    latency_mean = par("latency_mean");
    latency_stddev = par("latency_stddev");
    if(latency_mean == 0.0){
        channel->setDelay(0.1);
        std::cout << "Warning! No latency stated. Using a default 100ms latency on the channel." << endl;
    }
    gate("net_out")->connectTo(router->gate("nodes_in", getIntID()), channel);
    router->gate("nodes_out", getIntID())->connectTo(gate("net_in"));
}

/**
 * get this nodes ID as an int
 */
int NodeBase::getIntID() {
    return ID.get()->getBasicID();
}

/**
 * Set this nodes Basic ID
 *
 * WARNING! only call this method if you know what you are doing
 */
void NodeBase::setBasicID(int id) {
    ID.get()->setBasicID(id);
}

/**
 * Get this nodes BasicID
 */
std::shared_ptr<BasicID> NodeBase::getBasicID() {
    return ID;
}

/**
 * Receives a network message and passes it through all registered message handlers
 * before deleting it
 */
void NodeBase::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        BasicSelfMsg *self_msg = static_cast<BasicSelfMsg*>(msg);
        handleSelfMessage(self_msg);
    } else {
        BasicNetworkMsg *nw_msg = static_cast<BasicNetworkMsg*>(msg);
        for (unsigned int i = 0; i < MH.size(); i++) {
            MH[i]->handleMessage(nw_msg);
        }
        delete nw_msg;
    }
}

/**
 * Passes self messages to all self message handlers
 *
 * Also handles standard churn self messages
 */
bool NodeBase::handleSelfMessage(BasicSelfMsg *msg) {
    bool handled = false;
    for (unsigned int i = 0; i < SMH.size(); i++) {
        handled = handled || SMH[i]->handleSelfMessage(msg);
    }
    if (!handled) {
        if (msg == init_timer) {
//            setActive();
            std::cout << "WARNING! init_time is still being used!!!" << endl;
//            return true;
        } else if (msg == offline_timer_msg) {
            sendOffline();
            return true;
        } else {
            std::cout << "WARNING! self message: " << msg << " was not handled!"
                    << endl;
        }
    }
    return handled;
}

/**
 * Sends a given msg to a given destination (BasicID) on the underlay network
 */
void NodeBase::simpleSend(BasicNetworkMsg* msg, std::shared_ptr<BasicID> dst) {
    msg->setDstNode(dst->getBasicID());
    sendDelayed(msg, getLatency(), gate("net_out"));
}

/**
 * Sends a given msg to a given destination (int) on the underlay network
 */
void NodeBase::simpleSend(BasicNetworkMsg* msg, int dst) {
    if (dst == this->getBasicID()->getBasicID()) {
        std::cout
                << "WARINING!: You are trying to send the following network message to yourself!: "
                << endl;
        std::cout << msg << endl;
        cancelAndDelete(msg);
    } else {
        msg->setDstNode(dst);
        sendDelayed(msg, getLatency(), gate("net_out"));
    }
}

/**
 * Method to calculate latency for sending messages
 */
simtime_t NodeBase::getLatency(){
    simtime_t latency = normal(latency_mean, latency_stddev);
    while(latency < 0.03 || latency > 10.0){                      // Empirical values taken from real world pcaps
        latency = normal(latency_mean, latency_stddev);
    }
    return latency;
}

/**
 * Getter
 */
bool NodeBase::isActive() {
    return active;
}

/**
 * Churn related method to send a node offline
 */
void NodeBase::sendOffline() {
    CG->registerInactive(this);
    active = false;
    //    signalChange(true);

    for (unsigned int i = 0; i < SMH.size(); i++) {
        SMH[i]->cancelEvents(); //    cancelEvent(mm_cycle_msg);
    }
}

/**
 * Churn related method to make a node come back to live
 */
void NodeBase::setActive() {
    Enter_Method_Silent();

    if(isInitialized) {
        active = true;
        for(unsigned int i = 0; i < SMH.size(); i++) {
            SMH[i]->rescheduleEvents();
            //    cancelEvent(mm_cycle_msg);
            //    scheduleAt(simTime()+mmInterval, mm_cycle_msg); //schedule next interval
        }
        scheduleAt(simTime()+getOnlineTime(), offline_timer_msg);
        signalChange(false);
    } else {
        bootstrap();
    }
}

/**
 * Setter for initialization timer
 */
void NodeBase::setTimeToInitialize(double time) {
    timeToInitialize = time;
}

/**
 * Method to send a timeout message if the node is currently offline
 *
 * This simulates the timeout of a TCP connection
 */
void NodeBase::sendTimeoutMsg(int dst, BasicNetworkMsg* toMsg,
        int timeouttype) {
    NetworkTimeoutMsg* msg = new NetworkTimeoutMsg();
    msg->setTimeouttype(timeouttype);
    msg->setToMsg(*toMsg);
    msg->setSrcNode(ID->getBasicID());
    simpleSend(msg, dst);
}

/**
 * Fetches the duration of time this node will stay online from it's churn generator
 */
double NodeBase::getOnlineTime() {
    return CG->getActiveTime();
}

/**
 * Deprecated
 */
double NodeBase::getOfflineTime() {
    //    ChurnBase* churn = static_cast<ChurnBase*>(getModuleByPath(CG.c_str()));
    //    return churn->getOfflineTime();
    return 0.0;
}

/**
 * Sets this nodes Churn Generator
 *
 * WARNING! only use this if you know what you are doing!
 */
void NodeBase::setCG(ChurnBase* cg) {
    CG = cg;
}
