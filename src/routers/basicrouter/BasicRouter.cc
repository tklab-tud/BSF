#include <omnetpp.h>
#include <iostream>

#include "BasicRouter.h"
#include "../../messages/basicmessages/BasicNetworkMsg_m.h"
#include <fstream>

Define_Module(BasicRouter);

void BasicRouter::initialize() {
    record_trace = par("record_trace");
    start_recording_trace = par("start_recording_trace");
    int runNumber = par("run_number"); //EV.getConfigEx()->getActiveRunNumber();//par("runid");

    if (record_trace) {
        std::stringstream ss;
        ss << "./traces/NetworkTrace" << runNumber << ".txt";
        opp_string file = ss.str().c_str();
        dumpFile.open(file.buffer(), std::fstream::out); //will be located in folder 'results/NetworkTrace' of OverSim
    }
}

BasicRouter::~BasicRouter() {
    if (record_trace) {
        dumpFile.close();
    }
}

void BasicRouter::handleMessage(cMessage *msg) {
    BasicNetworkMsg* n_msg = static_cast<BasicNetworkMsg*>(msg);
    send(n_msg, gate("nodes_out", n_msg->getDstNode()));
}
