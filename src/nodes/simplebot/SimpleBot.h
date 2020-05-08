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
    simtime_t delay;

    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> neighbors;
    int max_parallel_conns;
    int mm_index;
    int open_conns;
    int version;

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
    void sendPing(int dest, simtime_t delay = 0);
    void sendPong(BasicNetworkMsg* msg);
    void sendCmdReq(BasicNetworkMsg* msg);
    void sendCmdRep(BasicNetworkMsg* msg);
    void removeNeighbor(int peerID);
    void continueMM(int replyID = -1);
    void resetMM();
    void inject_botmaster_msg(int version);


    void sendOffline();

    int getVersion();
    void setVersion(int version);

    SimpleSelfMsgHandler* ssmh;
};

#endif
