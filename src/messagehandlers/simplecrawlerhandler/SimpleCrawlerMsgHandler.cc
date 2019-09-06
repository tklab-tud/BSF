#include "SimpleCrawlerMsgHandler.h"

#include "../../nodes/simplecrawler/SimpleCrawler.h"
#include "../../messages/simplemessages/SimpleNLRespMsg_m.h"
#include "../../nodes/nodebase/NodeBase.h"

SimpleCrawlerMsgHandler::SimpleCrawlerMsgHandler(NodeBase* owner, CrawlerBase* crawler) {
    node = static_cast<SimpleCrawler*>(owner);
    this->crawler = crawler;
}

SimpleCrawlerMsgHandler::~SimpleCrawlerMsgHandler() {
    // TODO Auto-generated destructor stub
}

void SimpleCrawlerMsgHandler::handleMessage(BasicNetworkMsg* msg) {
    //    if (msg->getType() == TIMEOUT) {
    //    // DO NOTHING
    //    }
    if (node->isActive()) {
        if (msg->getType() == NL_REQ) {
            //            handleNLReq(msg);
            // Ignore
        } else if (msg->getType() == NL_RESP) {
            handleNLResp(msg);
        } else if (msg->getType() == PING) {
            handlePingMsg(msg);
        } else if (msg->getType() == PONG) {
            //            handlePongMsg(msg);
            // Ignore
        }
    }
}

void SimpleCrawlerMsgHandler::handleNLResp(BasicNetworkMsg* msg) {
    SimpleNLRespMsg* nl_resp = static_cast<SimpleNLRespMsg*>(msg);
    for(auto it = nl_resp->getNeighbors()->begin(); it != nl_resp->getNeighbors()->end(); ++it) {
//        std::cout << "NL REP: " << it->get()->getBasicID() << endl;
        crawler->updateEntry(msg->getSrcNode(), it->get()->getBasicID(), simTime());
        crawler->add2Q(it->get()->getBasicID());
    }
//    for (unsigned int i = 0; i < nl_resp->getNeighbors()->size(); i++) {
//        //        node->addNeighbor(resp->getNeighbors()->at(i));
//        crawler->updateEntry(msg->getSrcNode(), nl_resp->getNeighbors()->at(i)->getBasicID(), simTime());
//        crawler->add2Q(nl_resp->getNeighbors()->at(i)->getBasicID());
//    }
}

void SimpleCrawlerMsgHandler::handlePingMsg(BasicNetworkMsg* msg) {
}
