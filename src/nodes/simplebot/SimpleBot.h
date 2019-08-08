#ifndef __BOSS_SIMPLEBOT_H_
#define __BOSS_SIMPLEBOT_H_

#include <omnetpp.h>
#include "../nodebase/NodeBase.h"
#include "../../statistics/GraphDumper.h"
#include "../../selfmessagehandlers/simpleselfmsghandler/SimpleSelfMsgHandler.h"

using namespace omnetpp;

class SimpleSelfMsgHandler;

class SimpleBot: public NodeBase {
protected:
    virtual void initialize(int stage);
    ~SimpleBot();

    NeighborGD change;

    int maxNLSize;
    int bootstrapNodes;
    int NL_return_size;
    int mmInterval;
    int numInitStages() const;

    void bootstrap();

    void signalChange(bool leaving);
public:
    simsignal_t SimpleNeighbor;
    std::shared_ptr<SimpleNL> NL;
    unsigned int NLMinThreshold;

    void mmCycle();

    void addNeighbor(std::shared_ptr<BasicID> peer);
    void requestNeighbors();

    void sendNLReq(int dest);
    void sendNLResp(BasicNetworkMsg* msg);
    void sendPing(int dest);
    void sendPong(BasicNetworkMsg* msg);
    void removeNeighbor(int peerID);

    void sendOffline();

    SimpleSelfMsgHandler* ssmh;
};

#endif
