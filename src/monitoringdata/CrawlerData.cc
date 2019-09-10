#include "CrawlerData.h"
#include <fstream>

CrawlerData::CrawlerData(NodeBase* node, int num_nodes) {
    adjacency = new double*[num_nodes];
    this->node = node;
    for (int i = 0; i < num_nodes; ++i) {
        adjacency[i] = new double[num_nodes] { 0.0 };
    }
//    std::cout << adjacency[1][1] << endl;
}

CrawlerData::~CrawlerData() {
    dumpEntries();
    delete adjacency;
}

void CrawlerData::dumpEntries() {
    std::string configname = node->par("configname"); //par("runnumber");//ev.getConfigEx()->getActiveConfigName();

    int runNumber = node->par("run_number"); //EV.getConfigEx()->getActiveRunNumber();//par("runid");
    int num_nodes = node->par("total_nodes");

    std::stringstream dir;
    dir << "mkdir -p ../simulations/dumps/";
    dir << configname;
    dir << "/crawlers/";
    const int dir_err = system(dir.str().c_str());
    if (-1 == dir_err){
        std::cout << "Error creating directory" << endl;
    }

    std::ofstream dumpFile;
    std::stringstream ss;
    ss << "../simulations/dumps/";
    ss << configname;
    ss << "/crawlers/";
    ss << configname;
    ss << "-Run";
    ss << runNumber;
    ss << "Time";
    ss << SIMTIME_DBL(simTime()) / 100;
    ss << "00";
    ss << "Nodes";
    ss << num_nodes;
    ss << "Crawler";
    ss << node->getBasicID()->getBasicID();
    ss << ".txt";

    opp_string file = ss.str().c_str();

    dumpFile.open(file.buffer(), std::fstream::out); //will be located in folder 'simulations/dumps/' of OverSim

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            dumpFile << adjacency[i][j] << " ";
        }
        dumpFile << endl;
    }

    dumpFile.close();
}

void CrawlerData::updateEntry(int src, int dst, double time) {
    adjacency[src][dst] = time;
}

