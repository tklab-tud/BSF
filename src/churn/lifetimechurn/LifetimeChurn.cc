#include <memory>
#include <omnetpp.h>

#include "LifetimeChurn.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"
#include "../../nodes/nodebase/NodeBase.h"
#include "../../globalnodelist/GlobalNodeList.h"

#include <math.h>

using namespace omnetpp;

Define_Module(LifetimeChurn);

LifetimeChurn::~LifetimeChurn() {
    cancelAndDelete(respawn_msg);
    delete inactiveNodes;
}

void LifetimeChurn::initialize() {
    inactiveNodes = new std::vector<NodeBase*>();

    start_spawning = par("start_spawning");
    target_node_count = par("target_node_count");

    setupParams();

    trigger_spawn = new BasicSelfMsg("Triggering Spawn");
    respawn_msg = new BasicSelfMsg("Respawning node");
    scheduleAt(start_spawning, trigger_spawn);

    meanSpawnDelay = par("mean_spawn_delay");

    num_nodes = par("num_nodes");
}

void LifetimeChurn::setupParams() {
    shape_arrival = par("shape_arrival");
    shape_lifetime = par("shape_lifetime");
    scale_lifetime = par("scale_lifetime");

    double life_time_mean = scale_lifetime * tgamma(1 + 1 / shape_lifetime);
    double mean = life_time_mean / target_node_count;
    arrival_stretch = mean / tgamma(1 + 1 / shape_arrival);
}

void LifetimeChurn::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg == trigger_spawn) {
            spawn();
            delete trigger_spawn;
        } else if (msg == respawn_msg) {
            arrivalLoop();
            scheduleAt(simTime() + respawnTime(), respawn_msg);
        }
    }
}

void LifetimeChurn::spawn() {
    int offset = 0;
    for (int i = 0; i < getIndex(); i++) {
        int x =
                static_cast<ChurnBase*>(getModuleByPath(
                        ("BasicNetwork.ChurnGenerator[" + std::to_string(i)
                                + "]").c_str()))->num_nodes;
        offset += x;
    }

    GlobalNodeList* gnl = static_cast<GlobalNodeList*>(getModuleByPath(
            "BasicNetwork.GlobalNodeList"));

    int num_init_stages = par("num_init_stages");
    double init_time = start_spawning;

    for (int i = offset; i < num_nodes + offset; i++) {
        //std::string nodeType = par("node_type");
        cModuleType *moduleType = cModuleType::get(nodeType.c_str());
        std::string name = "Bot" + std::to_string(i);
        cModule *module = moduleType->create(name.c_str(), getParentModule());
        module->finalizeParameters();
        module->buildInside();

        NodeBase *node = static_cast<NodeBase*>(module);
        node->callInitialize(0);

        node->setBasicID(i);

        node->setCG(this);

        //        while(init_time < (start_spawning*1.0)){
        //            init_time = truncnormal(meanSpawnDelay,meanSpawnDelay);

        init_time = init_time + respawnTime();

        //        }

        node->setTimeToInitialize(init_time);

        for (int j = 1; j < num_init_stages; j++) {
            node->callInitialize(j);
        }

        inactiveNodes->push_back(node);
        gnl->registerNode(node->getBasicID());
    }
    scheduleAt(simTime() + respawnTime(), respawn_msg);
}

void LifetimeChurn::arrivalLoop() {
    if (!inactiveNodes->empty()) {
        int node_pos = uniform(0, inactiveNodes->size() - 1);
        //        std::cout << "Node pos: " << node_pos << endl;
        inactiveNodes->at(node_pos)->setActive();

        joinVec.record(inactiveNodes->at(node_pos)->getBasicID()->getBasicID());

        inactiveNodes->erase(inactiveNodes->begin() + node_pos);
    }
}

double LifetimeChurn::getActiveTime() {
    double jointSessionTime = weibull(scale_lifetime, shape_lifetime);
    if ((jointSessionTime + SIMTIME_DBL(simTime()) + 10000.0)
            > SIMTIME_DBL(SIMTIME_MAX-1)) {
        return SIMTIME_DBL(SIMTIME_MAX-1) - SIMTIME_DBL((simTime() + 10000.0));
    } else {
        return jointSessionTime;
    }
}

double LifetimeChurn::respawnTime() {
    double arrivalTime = weibull(arrival_stretch, shape_arrival);
//    double arrivalTime = weibull(5.814,0.66);
    if (arrivalTime + SIMTIME_DBL(simTime())
            + 10000.0> SIMTIME_DBL(SIMTIME_MAX-1)) {
        return SIMTIME_DBL(SIMTIME_MAX-1) - SIMTIME_DBL((simTime() + 10000.0));
    } else {
        return arrivalTime;
    }
}

void LifetimeChurn::registerInactive(NodeBase* node) {
    leaveVec.record(node->getBasicID()->getBasicID());
    inactiveNodes->push_back(node);
}

