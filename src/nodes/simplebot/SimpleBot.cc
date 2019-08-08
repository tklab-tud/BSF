#include "../../messagehandlers/simplehandler/SimpleTimeoutSender.h"
#include "SimpleBot.h"
#include "../../globalnodelist/GlobalNodeList.h"
#include "../../messages/simplemessages/PingMsg_m.h"
#include "../../messages/simplemessages/PongMsg_m.h"
#include "../../messages/simplemessages/SimpleNLReqMsg_m.h"
#include "../../messages/simplemessages/SimpleNLRespMsg_m.h"
#include "../../messagehandlers/simplehandler/SimpleMsgHandler.h"
#include "../../selfmessagehandlers/simpleselfmsghandler/SimpleSelfMsgHandler.h"
#include "../../messagehandlers/simplehandler/SimpleTimeoutHandler.h"

Define_Module(SimpleBot);

/**
 * Initialization of the module
 *
 * This method is called three times by a churn generator
 * stage 0 initializes all variables
 * stage 1 connects the module to the network
 * stage 2 schedules the initialization message of the module
 */
void SimpleBot::initialize(int stage) {
    if (stage == 0) {
        maxNLSize = par("max_nl_size");
        NLMinThreshold = par("nl_min_threshold");
        bootstrapNodes = par("bootstrap_nodes");
        mmInterval = par("mmInterval");
        NL_return_size = par("nl_return_size");

        offline_timer_msg = new BasicSelfMsg("offline_timer");

        ID = std::make_shared<BasicID>();

        MH.push_back(new SimpleTimeoutSender(this));
        MH.push_back(new SimpleMsgHandler(this));
        MH.push_back(new SimpleTimeoutHandler(this)); //TODO check if this works properly
        ssmh = new SimpleSelfMsgHandler(this, mmInterval);
        SMH.push_back(ssmh);
        active = false;

        NL = std::make_shared<SimpleNL>(maxNLSize, NLMinThreshold);
        SimpleNeighbor = registerSignal("Neighbor");
    }

    if (stage == 1) {
        connectToUnderlay();
    }

    if (stage == 2) {
//        scheduleAt(timeToInitialize, init_timer);
    }
}

/**
 * Destructor
 *
 * cleans up allocated memory at the end of a simulation
 */
SimpleBot::~SimpleBot() {
//    if(isActive()){
//            std::cout << "Initialized at: " << initializedAt << endl; // DEBUG
//            NL->dumpNL();
//    }
    cancelAndDelete(offline_timer_msg);
    for (unsigned int i = 0; i < SMH.size(); i++) {
        delete SMH.at(i);
    }
}

/**
 * Returns the amount of initialization stages
 */
int SimpleBot::numInitStages() const {
    return 3;
}

/**
 * Bootstrap the module to the overlay network
 */
void SimpleBot::bootstrap() {
    GlobalNodeList* gnl = static_cast<GlobalNodeList*>(getModuleByPath(
            "BasicNetwork.GlobalNodeList"));

    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> b_nodes =
            gnl->getBootstrapNodes(bootstrapNodes);

    for (unsigned int i = 0; i < b_nodes->size(); i++) {
        if (b_nodes->at(i) != getBasicID()) {
            addNeighbor(b_nodes->at(i));
        }
    }
    initializedAt = simTime();
    isInitialized = true;
    setActive();
}

/**
 * Update and replace entries within the neighborlist
 */
void SimpleBot::mmCycle() {
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> neighbors =
            NL->getAll();
    for (unsigned int i = 0; i < neighbors->size(); i++) {
        sendPing(neighbors.get()->at(i)->getBasicID());
    }
    if (NL->getSize() < NLMinThreshold) {
        requestNeighbors();
    }

    ssmh->rescheduleEvents();
}

/**
 * Sends out a NL request to all neighbors in a nodes neighborlist
 */
void SimpleBot::requestNeighbors() {
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> neighbors =
            NL->getAll();
    for (unsigned int i = 0; i < neighbors->size(); i++) {
        sendNLReq(neighbors.get()->at(i)->getBasicID());
    }
}

/**
 * Add a new node to the nodes neighborlist
 */
void SimpleBot::addNeighbor(std::shared_ptr<BasicID> peer) {
    if (peer->getBasicID() != getBasicID()->getBasicID()) {
        NL->addPeer(peer);
    }
}

/**
 * Removes the specified node from the neighborlist
 */
void SimpleBot::removeNeighbor(int peerID) {
    if (NL->getEntry(peerID)->get_missed_replies() > 5)
        NL->removePeer(peerID);
}

/**
 * Sends a neighborlist request to the specified destionation node
 */
void SimpleBot::sendNLReq(int dest) {
    SimpleNLReqMsg* req = new SimpleNLReqMsg();
    req->setSrcNode(getBasicID()->getBasicID());
    req->setDstNode(dest);
    simpleSend(req, dest);
}

/**
 * Sends a NL reply message to the requester.
 *
 * The amount of neighbors returned in a single request depends on the NL_return_size parameter
 */
void SimpleBot::sendNLResp(BasicNetworkMsg* msg) {
    SimpleNLRespMsg* resp = new SimpleNLRespMsg();
    std::vector<std::shared_ptr<BasicID>>* neighbors = new std::vector<
            std::shared_ptr<BasicID>>;
    for (int i = 0; i < NL_return_size; i++) {
        int random_peer = intrand(NL->getSize());
        if (random_peer != msg->getSrcNode() && NL->getSize() > 0) {
            neighbors->push_back(NL->getRandomPeer(random_peer));
        }

    }

    resp->setNeighbors(neighbors);
    resp->setSrcNode(getBasicID()->getBasicID());
    resp->setDstNode(msg->getSrcNode());
    simpleSend(resp, msg->getSrcNode());
}

/**
 * Sends a ping message to the specified destination node to check if it is still responsive
 */
void SimpleBot::sendPing(int dest) {
    PingMsg* ping = new PingMsg();
    ping->setSrcNode(getBasicID()->getBasicID());
    ping->setDstNode(dest);
    simpleSend(ping, dest);
}

/**
 * Sends a pong message in reply to a ping to signal this node is still active
 */
void SimpleBot::sendPong(BasicNetworkMsg* msg) {
    PongMsg* pong = new PongMsg();
    pong->setSrcNode(getBasicID()->getBasicID());
    pong->setDstNode(msg->getSrcNode());
    simpleSend(pong, msg->getSrcNode());
}

/**
 * Signal snapshot relevant changes of this node to the NetworkAnalyzer
 */
void SimpleBot::signalChange(bool leaving) {
    change.updateTime = simTime();
    change.nodeIP = getBasicID();
    change.leaving = leaving;
    change.nodeId = getBasicID();
    if (!leaving) {
        change.neighborsIP = NL->getAll(); //neighborList->getAllIPs();
    } else {
        change.neighborsIP = std::make_shared<
                std::vector<std::shared_ptr<BasicID>>>();

    }
    //    change.neighborsIP = std::make_shared<std::vector<IPAddress>>();

    emit(SimpleNeighbor, &change);
}

void SimpleBot::sendOffline() {
    NodeBase::sendOffline();
    signalChange(true);
}

