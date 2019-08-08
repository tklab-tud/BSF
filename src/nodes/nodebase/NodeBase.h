#ifndef __BOSS_BASENODE_H_
#define __BOSS_BASENODE_H_

#include "../../messagehandlers/basichandler/BasicMessageHandler.h"
#include <omnetpp.h>
#include <memory>

#include "../../botnetIds/basicid/BasicID.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"
#include "../../membershipmanagers/mmbase/MMBase.h"
#include "../../defenses/defensebase/DefenseBase.h"
#include "../../messages/basicmessages/BasicNetworkMsg_m.h"
#include "../../neighborlists/simplenl/SimpleNL.h"
#include "../../selfmessagehandlers/basicselfmsghandler/BasicSelfMsgHandler.h"

class ChurnBase;

using namespace omnetpp;

class NodeBase: public cSimpleModule {
protected:
//    std::shared_ptr<DefenseBase> defenses[];
    std::vector<BasicMessageHandler*> MH;
    std::vector<BasicSelfMsgHandler*> SMH;

    ChurnBase* CG;

    bool isInitialized = 0;

    bool active;
    BasicSelfMsg* init_timer;
    BasicSelfMsg* offline_timer_msg;
    BasicSelfMsg* come_alive_msg;
    int timeToInitialize;

    simtime_t initializedAt;

    void handleMessage(cMessage *msg);

    virtual void signalChange(bool leaving) = 0;

public:
    std::shared_ptr<BasicID> ID;
    virtual int numInitStages() const = 0;
    virtual void bootstrap() = 0;
    virtual void initialize(int stage) = 0;
    virtual ~NodeBase() = 0;
    virtual void setBasicID(int id);
    virtual std::shared_ptr<BasicID> getBasicID();
    virtual int getIntID();
    virtual bool handleSelfMessage(BasicSelfMsg *msg);
    virtual void setActive();
    virtual void sendOffline();
    void setCG(ChurnBase* cg);
    void connectToUnderlay();
    void simpleSend(BasicNetworkMsg* msg, std::shared_ptr<BasicID> dst);
    void simpleSend(BasicNetworkMsg* msg, int dst);
    bool isActive();
    void setTimeToInitialize(double time);
    virtual void sendTimeoutMsg(int dst, BasicNetworkMsg* toMsg,
            int timeouttype);
    double getOnlineTime();
    double getOfflineTime();
};

#endif
