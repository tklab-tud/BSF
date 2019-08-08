#ifndef __BOSS_CHURNBASE_H_
#define __BOSS_CHURNBASE_H_

#include <omnetpp.h>
#include "../../nodes/nodebase/NodeBase.h"

using namespace omnetpp;

class ChurnBase: public cSimpleModule {
protected:
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
    virtual void spawn() = 0;

    std::vector<NodeBase*>* inactiveNodes; /**< Map variation*/
    typedef std::vector<NodeBase*>::iterator inactiveNodeIterator;
    std::string nodeType;

public:
    virtual void registerInactive(NodeBase* node) = 0;
    virtual double getActiveTime() = 0;

    void setNodeType(std::string name) {
        nodeType = name;
    }

    int num_nodes;
};

#endif
