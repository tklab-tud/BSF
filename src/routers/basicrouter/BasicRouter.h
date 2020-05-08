#ifndef __BOSS_BASICROUTER_H_
#define __BOSS_BASICROUTER_H_

#include <omnetpp.h>
#include <fstream>

using namespace omnetpp;

class BasicRouter: public cSimpleModule {
protected:
    std::ofstream dumpFile;
    std::ofstream cmdDumpFile;

    bool record_trace;
    double start_recording_trace;
    bool record_commands;


    virtual void initialize();
    virtual ~BasicRouter();
    virtual void handleMessage(cMessage *msg);
};

#endif
