#include "StaticNoChurn.h"
#include "../../globalnodelist/GlobalNodeList.h"

Define_Module(StaticNoChurn);

double StaticNoChurn::spawnTime() {
    return start_up;
}

void StaticNoChurn::start_up_nodes() {
    GlobalNodeList* gnl = static_cast<GlobalNodeList*>(getModuleByPath(
            "BasicNetwork.GlobalNodeList"));
    if (!inactiveNodes->empty()) {

        gnl->registerNode(
                std::shared_ptr<BasicID>(inactiveNodes->back()->getBasicID()));

        inactiveNodes->back()->setActive();
        inactiveNodes->pop_back();
    }
    scheduleAt(simTime() + 1, spawn_msg);
}

void StaticNoChurn::spawn() {
    int offset = 0;
    for (int i = 0; i < getIndex(); i++) {
        int x =
                static_cast<ChurnBase*>(getModuleByPath(
                        ("ChurnGenerator[" + std::to_string(i) + "]").c_str()))->num_nodes;
        offset += x;
    }

    int num_init_stages = par("num_init_stages");
    start_up = par("no_churn_startup");

    double init_time = start_spawning;

    for (int i = offset; i < num_nodes + offset; i++) {
        cModuleType *moduleType = cModuleType::get(nodeType.c_str());
        std::string name = "Bot" + std::to_string(i);
        cModule *module = moduleType->create(name.c_str(), getParentModule());
        module->finalizeParameters();
        module->buildInside();

        NodeBase *node = static_cast<NodeBase*>(module);
        node->callInitialize(0);

        node->setBasicID(i);

        node->setCG(this);

        init_time = init_time + spawnTime();

        node->setTimeToInitialize(init_time);

        inactiveNodes->push_back(node);

        for (int j = 1; j < num_init_stages; j++) {
            node->callInitialize(j);
        }

    }
    scheduleAt(simTime() + spawnTime(), spawn_msg);
}
