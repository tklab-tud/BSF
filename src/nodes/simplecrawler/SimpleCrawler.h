#ifndef SRC_NODES_SIMPLECRAWLER_SIMPLECRAWLER_H_
#define SRC_NODES_SIMPLECRAWLER_SIMPLECRAWLER_H_

#include "../simplebot/SimpleBot.h"
#include "../crawlerbase/CrawlerBase.h"
#include "../../selfmessagehandlers/crawlerselfmsgehandler/CrawlerSelfMsgHandler.h"

using namespace omnetpp;

class SimpleCrawler : public SimpleBot, public CrawlerBase {
public:
    CrawlerSelfMsgHandler* csmh;

    void crawl();

protected:
    double crawler_start_time;
    void initialize(int stage);
    virtual void bootstrap();

//    SimpleCrawler();
//    virtual ~SimpleCrawler();
};

#endif /* SRC_NODES_SIMPLECRAWLER_SIMPLECRAWLER_H_ */
