#include <omnetpp.h>
#include <iostream>

#include "BasicRouter.h"
#include "../../messages/basicmessages/BasicNetworkMsg_m.h"
#include "../../messages/simplemessages/CmdRepMsg_m.h"

#include <fstream>

Define_Module(BasicRouter);

void BasicRouter::initialize() {
    record_trace = par("record_trace");
    start_recording_trace = par("start_recording_trace");
    record_commands = par("record_commands");
    int runNumber = par("run_number");
    std::string configname = par("configname"); //par("runnumber");//ev.getConfigEx()->getActiveConfigName();

    if (record_trace) {
        std::stringstream ss;
        ss << "./traces/"<< configname << runNumber << ".txt";
        opp_string file = ss.str().c_str();
        dumpFile.open(file.buffer(), std::fstream::out);
    }

    if (record_commands) {
        std::stringstream ss;
        ss << "./cmd_traces/"<< configname << runNumber << "_cmd-trace.txt";
        opp_string file = ss.str().c_str();
        cmdDumpFile.open(file.buffer(), std::fstream::out);
        cmdDumpFile <<  "Src , " <<  "Dst, " << "Timestamp, " << "Version" << endl;

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

    if(record_commands && (n_msg->getType()==CMD_REP)){
        CmdRepMsg* rep = static_cast<CmdRepMsg*>(n_msg);
        cmdDumpFile << n_msg->getSrcNode() << ", " <<  n_msg->getDstNode() << ", " << simTime()  << ", " << rep->getVersion() << endl;
    }

    send(n_msg, gate("nodes_out", n_msg->getDstNode()));
}
