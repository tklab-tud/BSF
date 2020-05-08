#ifndef __BOSS_GLOBALNODELIST_H_
#define __BOSS_GLOBALNODELIST_H_

#include <omnetpp.h>
#include <memory>

#include "../nodes/nodebase/NodeBase.h"
#include "../botnetIds/basicid/BasicID.h"

using namespace omnetpp;

class GlobalNodeList: public cSimpleModule {
protected:
    ~GlobalNodeList();
    void initialize();
    void handleMessage(cMessage *msg);

    int tn;
    int num_bootstrapped = 0;

    std::map<int, std::shared_ptr<BasicID>>* nodeMap; /**< Map variation*/
//    std::vector<peerEntry>* neighborListVector; /**< Vector variation*/

// Iterators
    typedef std::map<int, std::shared_ptr<BasicID>>::iterator NodeMapIter;
    typedef std::map<int, std::shared_ptr<BasicID>>::const_iterator NodeMapConstIter;

//    typedef std::vector<peerEntry>::iterator NeighborsVectorIterator;
//    typedef std::vector<peerEntry>::const_iterator NeighborsVectorConstIterator;

public:
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> getBootstrapNodes(
            int num_nodes = 1);
    std::shared_ptr<BasicID> getRandomNode();
    NodeBase* getRandomActiveNode();
    void registerNode(std::shared_ptr<BasicID> node);
};

#endif
