#ifndef SRC_MESSAGEHANDLERS_SIMPLECRAWLERHANDLER_SIMPLECRAWLERMSGHANDLER_H_
#define SRC_MESSAGEHANDLERS_SIMPLECRAWLERHANDLER_SIMPLECRAWLERMSGHANDLER_H_

#include "../../nodes/nodebase/NodeBase.h"
#include "../../nodes/simplecrawler/SimpleCrawler.h"

class SimpleCrawlerMsgHandler : public BasicMessageHandler  {
public:
    SimpleCrawlerMsgHandler(NodeBase* owner, CrawlerBase* crawler);
    virtual ~SimpleCrawlerMsgHandler();
    CrawlerBase* crawler;
    void handleMessage(BasicNetworkMsg *msg);
    void handleNLResp(BasicNetworkMsg* msg);
    void handlePingMsg(BasicNetworkMsg* msg);
    void handlePongMsg(BasicNetworkMsg* msg);

};

#endif /* SRC_MESSAGEHANDLERS_SIMPLECRAWLERHANDLER_SIMPLECRAWLERMSGHANDLER_H_ */
