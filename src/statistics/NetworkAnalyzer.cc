#include "NetworkAnalyzer.h"

#include <omnetpp.h>
#include <fstream>
#include <strings.h>

#include "GraphDumper.h"

using namespace omnetpp;

Define_Module(NetworkAnalyzer);

void NetworkAnalyzer::initialize() {
    getSimulation()->getSystemModule()->subscribe("Neighbor", this);
    snapshotTimer = new cMessage("SnapshotTimer");
    snapshotInterval = par("snapshotInterval");
    scheduleAt(simTime() + snapshotInterval, snapshotTimer);

    remove_offline = par("remove_offline");
}

NetworkAnalyzer::~NetworkAnalyzer() {
    //initialize all nodes + write neighbors for this dump
    dumpGraph();
    cancelAndDelete(snapshotTimer);
    unsubscribe("neighbor", this); //unregister when finished
}

void NetworkAnalyzer::handleMessage(cMessage *msg) {
    if (msg == snapshotTimer) {
        //reschedule timer
        scheduleAt(simTime() + snapshotInterval, snapshotTimer);

        //DumpSnapshot
        dumpGraph();

        return;
    }

    delete msg;
}

void NetworkAnalyzer::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject* details) {
    NeighborGD *update = static_cast<NeighborGD *>(obj);
    if (update) {
        /* Dumping graph in Graphviz format */

        //get string representation
        std::string neighbors = "";
        if (!update->neighborsIP->empty() && !update->leaving) //not empty and not leaving
                {
//            for (unsigned int i = 0; i < update->neighborsIP.size()-1; i++) //size-1 to avoid trailing space
//                neighbors += "\""+update->neighborsIP[i].str()+"\" ";
//            neighbors += "\""+update->neighborsIP[update->neighborsIP.size()-1].str()+"\""; //add final entry

            for (unsigned int i = 0; i < update->neighborsIP->size() - 1; i++) //size-1 to avoid trailing space
                neighbors += "\""
                        + std::to_string(
                                update->neighborsIP->at(i)->getBasicID())
                        + "\" ";
            neighbors +=
                    "\""
                            + std::to_string(
                                    update->neighborsIP->at(
                                            update->neighborsIP->size() - 1)->getBasicID())
                            + "\""; //add final entry
        }
        nlLength[update->nodeId->getBasicID()] = update->neighborsIP->size();
        updateNeighbors(update->nodeId.get(), neighbors, update->leaving); //update our map

        /* End of graphiz format dumping*/
    }
}

void NetworkAnalyzer::dumpGraph() {
    //std::string currentRun = "testrun";//par("runid");//ev.getConfigEx()->getVariable(CFGVAR_REPETITION);
    std::string configname = par("configname"); //par("runnumber");//ev.getConfigEx()->getActiveConfigName();

    int runNumber = par("run_number"); //EV.getConfigEx()->getActiveRunNumber();//par("runid");
    int num_nodes = par("total_nodes");

    std::ofstream dumpFile;
    std::stringstream ss;
    ss << "../simulations/dumps/";
    ss << configname;
    ss << "-Run";
    ss << runNumber;
    ss << "Time";
    ss << SIMTIME_DBL(simTime()) / 100;
    ss << "00";
    ss << "Nodes";
    ss << num_nodes;
    ss << ".gv";

    opp_string file = ss.str().c_str();
    dumpFile.open(file.buffer(), std::fstream::out); //will be located in folder 'simulations/dumps/' of OverSim

    dumpFile << "digraph dumpedGraph {\n";
    dumpFile << "\t\tnode[color=Red,fontname=Courier]\n"; //all node's style
    dumpFile << "\t\tedge[color=Blue,style=dashed]\n"; //all edge's style
    dumpFile << "\t\trankdir=LR; //Rank Direction Left to Right\n";
    dumpFile << "\t\t/*Total Nodes : " << globalKnowledge.size() << " */\n";

    //initialize all nodes + write neighbors for this dump
    const_iter = globalKnowledge.begin(); //initialize
    while (const_iter != globalKnowledge.end()) //while not the end of map iteration
    {
        formatEntries(const_iter->first, const_iter->second, dumpFile); //id,neighbors
        const_iter++;
    }

    dumpFile << "}";
    dumpFile.close();
    //std::cout<<"DUMPING! @ "<<file<<endl;
}

void NetworkAnalyzer::updateNeighbors(BasicID* id, std::string neighbors,
        bool leaving) {
    iter = globalKnowledge.find(id->getBasicID());

    if (leaving && iter != globalKnowledge.end() && remove_offline) //entry exist
        globalKnowledge.erase(iter); //delete information of a leaving node
    else if (!leaving)
        globalKnowledge[id->getBasicID()] = neighbors; //update the change information
}

void NetworkAnalyzer::formatEntries(int id, std::string neighbors,
        std::ofstream& dumpFile) {
    dumpFile << "\"" << id << "\"->{" << neighbors << "}\n";
}

