#include <omnetpp.h>
#include <iostream>
#include "../nodes/simplebot/SimpleBot.h"

#include "GlobalNodeList.h"

using namespace omnetpp;

Define_Module(GlobalNodeList);

void GlobalNodeList::initialize() {
    nodeMap = new std::map<int, std::shared_ptr<BasicID>>();
    tn = par("total_nodes");
    std::cout << "Global Node list path: " << getFullPath() << endl;
}

GlobalNodeList::~GlobalNodeList() {
    delete nodeMap;
}

void GlobalNodeList::handleMessage(cMessage *msg) {
}

std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> GlobalNodeList::getBootstrapNodes(
        int num_nodes) {
    num_bootstrapped++;
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> nodes =
            std::make_shared<std::vector<std::shared_ptr<BasicID>>>(
                    std::vector<std::shared_ptr<BasicID>>());

    if (num_bootstrapped < tn / 2) {
        for (int i = 0; i < num_nodes; i++) {
            nodes->push_back(getRandomNode());
        }
    } else {
        while (true) {
            std::shared_ptr<BasicID> node = getRandomNode();
            std::stringstream ss;
            ss << "BasicNetwork.Bot" << node->getBasicID();
            std::string s = ss.str();
            NodeBase* node_base = static_cast<NodeBase*>(getModuleByPath(
                    s.c_str()));
            SimpleBot* s_node = static_cast<SimpleBot*>(node_base);
            if (s_node->isActive()) {
                nodes = s_node->NL->getAll();
                break;
            }
        }
    }

    return nodes;
}

std::shared_ptr<BasicID> GlobalNodeList::getRandomNode() {
    return nodeMap->at(intrand(nodeMap->size(), 0));
}

NodeBase* GlobalNodeList::getRandomActiveNode(){
    while (true) {
        std::shared_ptr<BasicID> node = getRandomNode();
        std::stringstream ss;
        ss << "BasicNetwork.Bot" << node->getBasicID();
        std::string s = ss.str();
        NodeBase* node_base = static_cast<NodeBase*>(getModuleByPath(
                s.c_str()));
        if (node_base->isActive()) {
            return node_base;
        }
    }
}

void GlobalNodeList::registerNode(std::shared_ptr<BasicID> node) {
    nodeMap->insert(
            std::pair<int, std::shared_ptr<BasicID>>(node->getBasicID(), node));
}
