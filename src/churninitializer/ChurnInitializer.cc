#include "ChurnInitializer.h"
#include "../churn/churnbase/ChurnBase.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

Define_Module(ChurnInitializer);

void ChurnInitializer::initialize() {
    createCGs();
}

void ChurnInitializer::handleMessage(cMessage *msg) {
}

void ChurnInitializer::createCGs() {
    std::vector<CGparams>* CGs = parseParams();

    for (unsigned int i = 0; i < CGs->size(); i++) {
        std::string nodeType = CGs->at(i).CGType;
        cModuleType *moduleType = cModuleType::get(nodeType.c_str());

        std::string name = nodeType;
        cModule *module = moduleType->create("ChurnGenerator",
                getParentModule(), i + 1, i);
        module->finalizeParameters();
        module->buildInside();
        static_cast<ChurnBase*>(module)->setNodeType(CGs->at(i).NodeType);
    }
    delete CGs;
}

std::vector<CGparams>* ChurnInitializer::parseParams() {
    std::vector<CGparams>* CGs = new std::vector<CGparams>();

    std::string CGtypes = par("churn_generators");
    std::string NodeTypes = par("node_types");

    std::istringstream iss(CGtypes);
    std::vector<std::string> CGtypevec { std::istream_iterator<std::string> {
            iss }, std::istream_iterator<std::string> { } };

    iss = std::istringstream(NodeTypes);
    std::vector<std::string> NodeTypeVec { std::istream_iterator<std::string> {
            iss }, std::istream_iterator<std::string> { } };

    ASSERT(CGtypevec.size() == NodeTypeVec.size());

    for (unsigned int i = 0; i < CGtypevec.size(); i++) {
        CGparams cgp = { };
        cgp.CGType = CGtypevec[i];
        cgp.NodeType = NodeTypeVec[i];
        CGs->push_back(cgp);
    }

    return CGs;
}
