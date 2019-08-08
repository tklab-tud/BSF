#ifndef NODES_CRAWLERBASE_CRAWLERBASE_H_
#define NODES_CRAWLERBASE_CRAWLERBASE_H_

#include "../../monitoringdata/CrawlerData.h"
#include "../../messages/basicmessages/BasicSelfMsg_m.h"
#include <queue>

class CrawlerBase {

public:

    bool isCrawling = false;
    std::set<int> visited;
    std::set<int> startNodes;

    int request_per_crawl;

    std::queue<int> Q;

    double crawl_timeout; // = 4*3600;
    double crawl_dump_timeout; // = 24*3600;

    BasicSelfMsg* crawl_msg = new BasicSelfMsg("Crawl Message");
    BasicSelfMsg* crawl_dump_msg = new BasicSelfMsg("Crawl dump message");

    CrawlerBase();
    virtual ~CrawlerBase();
    virtual void crawl() = 0;

    CrawlerData* crawler_data;

    virtual void updateEntry(int src, int dst, simtime_t time);
    virtual int getNext();
    virtual void add2Q(int node);
    virtual void startCrawl();
    virtual void stopCrawl();
};

#endif /* NODES_CRAWLERBASE_CRAWLERBASE_H_ */
