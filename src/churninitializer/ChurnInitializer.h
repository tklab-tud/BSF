#ifndef __BOSS_CHURNINITIALIZER_H_
#define __BOSS_CHURNINITIALIZER_H_

#include <omnetpp.h>

using namespace omnetpp;

struct CGparams {
    CGparams() :
            CGType("none"), NodeType("none") {

    }
    std::string CGType;
    std::string NodeType;
};

class ChurnInitializer: public cSimpleModule {
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    std::vector<CGparams>* parseParams();
    void createCGs();
};

#endif
