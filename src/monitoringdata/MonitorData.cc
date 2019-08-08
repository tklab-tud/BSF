/*
 * SensorLogic.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: xtikka
 */

#include "MonitorData.h"
#include "omnetpp.h"
#include <fstream>

using namespace omnetpp;

MonitorData::MonitorData(NodeBase* node, std::string type) {
    sensorNL = new std::map<int, SensorNLEntry*>;
    this->node = node;
    this->type = type;
}

MonitorData::~MonitorData() {
    dumpSensorData();
    delete sensorNL;
}

void MonitorData::updateEntry(BasicID* node, simtime_t time) {
    if (sensorNL->count(node->getBasicID()) > 0) {
        sensorNL->at(node->getBasicID())->updateLastSeen(time);
    } else {
        sensorNL->emplace(node->getBasicID(), new SensorNLEntry(time));
    }
}

void MonitorData::updateEntry(int nodeID, simtime_t time) {
    if (sensorNL->count(nodeID) > 0) {
        sensorNL->at(nodeID)->updateLastSeen(time);
    } else {
        sensorNL->emplace(nodeID, new SensorNLEntry(time));
    }
}

void MonitorData::dumpSensorData() {
    std::cout << sensorNL->size() << endl;

    std::string configname = node->par("configname"); //par("runnumber");//ev.getConfigEx()->getActiveConfigName();

    int runNumber = node->par("run_number"); //EV.getConfigEx()->getActiveRunNumber();//par("runid");
    int num_nodes = node->par("total_nodes");

    std::ofstream dumpFile;
    std::stringstream ss;
    ss << "../simulations/dumps/monitor data/";
    ss << configname;
    ss << "-Run";
    ss << runNumber;
    ss << "Time";
    ss << SIMTIME_DBL(simTime()) / 100;
    ss << "00";
    ss << "Nodes";
    ss << num_nodes;
    ss << type;
    ss << node->getBasicID()->getBasicID();
    ss << ".txt";

    opp_string file = ss.str().c_str();
    dumpFile.open(file.buffer(), std::fstream::out); //will be located in folder 'simulations/dumps/' of OverSim
    //
    for (std::map<int, SensorNLEntry*>::iterator it = sensorNL->begin();
            it != sensorNL->end(); ++it) {
        dumpFile << it->first << ": " << it->second->getTimeLastSeen() << endl;
    }

    dumpFile.close();
}

std::vector<int>* MonitorData::getBoostTargets() {
    std::vector<int>* targets = new std::vector<int>();
    for (std::map<int, SensorNLEntry*>::iterator it = sensorNL->begin();
            it != sensorNL->end(); ++it) {
        targets->push_back(it->first);
    }
    return targets;
}
