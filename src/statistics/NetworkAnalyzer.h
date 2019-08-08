#ifndef __BOSS_NETWORKANALYZER_H_
#define __BOSS_NETWORKANALYZER_H_

#include <omnetpp.h>

#include "../botnetIds/basicid/BasicID.h"

using namespace omnetpp;

class NetworkAnalyzer: public cSimpleModule, cIListener {
protected:
    bool remove_offline;

    void initialize();
    ~NetworkAnalyzer();
    void handleMessage(cMessage *msg);

    //Method to update neighborhood information
    void updateNeighbors(BasicID* id, std::string neighbors, bool leaving);
    //Output
    void dumpGraph(); //dump globalKnowledge in a graphviz format
    void formatEntries(int id, std::string neighbors, std::ofstream& dumpFile); //write neighbors of a node (id) in dot language

    //    int maxNodes;           //maximum number of nodes will be simulated (a.k.a. vertices)
    //    opp_string fileName;    //name of the output file
    //    int receivedLivenessSignals;

    std::map<int, std::string> globalKnowledge; //FUTURE implement BasicID as comparable!
    std::map<int, int> nlLength;       //FUTURE implement BasicID as comparable!
    std::map<int, std::string>::iterator iter; //FUTURE implement BasicID as comparable!
    std::map<int, std::string>::const_iterator const_iter; //FUTURE implement BasicID as comparable!
    cMessage* snapshotTimer;
    simtime_t snapshotInterval;

    //Signal virtual methods
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj,
            cObject *details);
    void receiveSignal(cComponent *src, simsignal_t id, long l,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, double d,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, simtime_t t,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, const char *,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, bool,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, unsigned long l,
            cObject *details) {
    }
    ;
    void receiveSignal(cComponent *src, simsignal_t id, const SimTime& t,
            cObject *details) {
    }
    ;
};

#endif
