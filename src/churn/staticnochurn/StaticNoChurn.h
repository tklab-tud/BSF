#ifndef __BOSS_STATICNOCHURN_H_
#define __BOSS_STATICNOCHURN_H_

#include <omnetpp.h>
#include "../nochurn/NoChurn.h"
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class StaticNoChurn: public NoChurn {
protected:
    int start_up;
    double spawnTime();
    virtual void start_up_nodes();
    virtual void spawn();
};

#endif
