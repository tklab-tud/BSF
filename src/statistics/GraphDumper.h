/**
 *  GraphDumper Object classes
 *  Used to carry information to pass to the graph dumper from the simulation
 *
 */

#ifndef NEIGHBORGD_H_
#define NEIGHBORGD_H_

#include <omnetpp.h>
#include "../botnetIds/basicid/BasicID.h"
#include "../common/IPAddress.h"
#include <memory.h>

class NeighborGD: public cObject, public noncopyable {
public:
    std::shared_ptr<BasicID> nodeId;
//    std::shared_ptr<IPAddress> nodeIP; DEBUG
    std::shared_ptr<BasicID> nodeIP;
    bool leaving;
    bool useKey;
    simtime_t updateTime;
    std::vector<BasicID> neighbors;
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> neighborsIP; // FUTURE change back to IP !
};

#endif /* NEIGHBORGD_H_ */
