#include <omnetpp.h>
#include <iostream>

#include "BasicRouter.h"
#include "../../messages/basicmessages/BasicNetworkMsg_m.h"
#include <fstream>

Define_Module(BasicRouter);

void BasicRouter::initialize() {
    record_trace = par("record_trace");
    start_recording_trace = par("start_recording_trace");
    int runNumber = par("run_number");

    if (record_trace) {
        std::stringstream ss;
        ss << "./traces/NetworkTrace" << runNumber << ".txt";
        opp_string file = ss.str().c_str();
        dumpFile.open(file.buffer(), std::fstream::out);
    }
}

BasicRouter::~BasicRouter() {
    if (record_trace) {
        dumpFile.close();
    }
}

void BasicRouter::handleMessage(cMessage *msg) {
    BasicNetworkMsg* n_msg = static_cast<BasicNetworkMsg*>(msg);

    if(record_trace && simTime() > start_recording_trace){
        dumpFile << "Src: " << n_msg->getSrcNode() << ", Dst: " << n_msg->getDstNode() << ", Type: " << n_msg->getType() << ", Time: " << simTime() << endl;
    }

    send(n_msg, gate("nodes_out", n_msg->getDstNode()));
}
