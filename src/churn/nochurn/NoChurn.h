#ifndef __BOSS_NOCHURN_H_
#define __BOSS_NOCHURN_H_

#include <omnetpp.h>

#include "../churnbase/ChurnBase.h"

using namespace omnetpp;

class NoChurn: public ChurnBase {
private:

//    std::vector<NodeBase*>* inactiveNodes; /**< Map variation*/
//    typedef std::vector<NodeBase*>::iterator inactiveNodeIterator;

protected:
    BasicSelfMsg* trigger_spawn;
    BasicSelfMsg* spawn_msg;
    double meanSpawnDelay;
    int start_spawning;
    double arrival_stretch;
    int target_node_count;
    void start_up_nodes();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void spawn();
public:
    virtual void registerInactive(NodeBase* node);
    virtual double getActiveTime();
    double spawnTime();
};

#endif
