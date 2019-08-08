#ifndef __BOSS_LIFETIMECHURN_H_
#define __BOSS_LIFETIMECHURN_H_

#include <omnetpp.h>

#include "../churnbase/ChurnBase.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"
#include "../../nodes/nodebase/NodeBase.h"

using namespace omnetpp;

class LifetimeChurn: public ChurnBase {
private:
    double shape_arrival;
//    double scale_arrival;
    double arrival_stretch;

    double shape_lifetime;
    double scale_lifetime;

    BasicSelfMsg* trigger_spawn;
    BasicSelfMsg* respawn_msg;
    double meanSpawnDelay;
    int start_spawning;
    int target_node_count;
    cOutVector joinVec;
    cOutVector leaveVec;
protected:
    ~LifetimeChurn();
    void initialize();
    void handleMessage(cMessage *msg);
    void spawn();
    void arrivalLoop();
    double respawnTime();
    void setupParams();
public:
    double getActiveTime();
    void registerInactive(NodeBase* node);

};

#endif
