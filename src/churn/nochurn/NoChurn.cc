#include "NoChurn.h"
#include "../../globalnodelist/GlobalNodeList.h"

Define_Module(NoChurn);

void NoChurn::initialize() {
    inactiveNodes = new std::vector<NodeBase*>();

    start_spawning = par("start_spawning");
    target_node_count = par("target_node_count");

    double life_time_mean = 1193.317 * tgamma(1 + 1 / 0.28);
    double shape = 0.66;
    double mean = life_time_mean / target_node_count;
    arrival_stretch = mean / tgamma(1 + 1 / shape);

//    arrival_stretch = par("arrival_stretch");

    spawn_msg = new BasicSelfMsg("spawn_msg");
    trigger_spawn = new BasicSelfMsg("Triggering Spawn");
    scheduleAt(start_spawning, trigger_spawn);

    meanSpawnDelay = par("mean_spawn_delay");

    num_nodes = par("num_nodes");
}

void NoChurn::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg == trigger_spawn) {
            spawn();
            delete trigger_spawn;
        } else if (msg == spawn_msg) {
            start_up_nodes();
        }
    }
}

void NoChurn::start_up_nodes() {
    if (!inactiveNodes->empty()) {
        int node_pos = uniform(0, inactiveNodes->size() - 1);
        inactiveNodes->at(node_pos)->setActive();
        inactiveNodes->erase(inactiveNodes->begin() + node_pos);
    }
    scheduleAt(simTime() + spawnTime(), spawn_msg);
}

void NoChurn::spawn() {
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

    for (int i = offset; i < num_nodes + offset; i++) {
//        std::string nodeType = par("node_type");
        cModuleType *moduleType = cModuleType::get(nodeType.c_str());
        std::string name = "Bot" + std::to_string(i);
        cModule *module = moduleType->create(name.c_str(), getParentModule());
        module->finalizeParameters();
        module->buildInside();

        NodeBase *node = static_cast<NodeBase*>(module);
        node->callInitialize(0);

        node->setBasicID(i);

        node->setCG(this);

//        init_time = init_time + spawnTime();
//
////        node->setTimeToInitialize(init_time); //DEBUG
//        node->setTimeToInitialize(start_spawning);

        inactiveNodes->push_back(node);

        for (int j = 1; j < num_init_stages; j++) {
            node->callInitialize(j);
        }

        gnl->registerNode(node->getBasicID());
    }
    scheduleAt(simTime() + spawnTime(), spawn_msg);
}

double NoChurn::spawnTime() {
    double arrivalTime = weibull(arrival_stretch, 0.66);
//    double arrivalTime = weibull(5.814,0.66);
    if (arrivalTime + SIMTIME_DBL(simTime())
            + 10000.0> SIMTIME_DBL(SIMTIME_MAX-1)) {
        return SIMTIME_DBL(SIMTIME_MAX-1) - SIMTIME_DBL((simTime() + 10000.0));
    } else {
        return arrivalTime;
    }
}

double NoChurn::getActiveTime() {
    return SIMTIME_DBL(SIMTIME_MAX-(simTime()+432000));
}

void NoChurn::registerInactive(NodeBase* node) {
    inactiveNodes->push_back(node);
}

