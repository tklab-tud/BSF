#include "CrawlerSelfMsgHandler.h"

#include "omnetpp.h"

using namespace omnetpp;

CrawlerSelfMsgHandler::CrawlerSelfMsgHandler(NodeBase* node,
        CrawlerBase *crawler, double startTime) {
    this->node = node;
    this->crawler = crawler;
    this->startTime = startTime;
}

CrawlerSelfMsgHandler::~CrawlerSelfMsgHandler() {
    // TODO Auto-generated destructor stub
}

bool CrawlerSelfMsgHandler::handleSelfMessage(BasicSelfMsg* msg) {
    if (msg == crawler->crawl_msg) {
        if (node->isActive()) {
            if (simTime() > startTime) {
                if (!crawler->isCrawling) {
                    crawler->startCrawl();
                }
            }
            node->scheduleAt(simTime() + crawler->crawl_timeout,
                    crawler->crawl_msg);
        }
        return true;
    } else if (msg == crawler->crawl_dump_msg) {
        crawler->crawler_data->dumpEntries();
        double normalize = std::round(
                1 + SIMTIME_DBL(simTime() / crawler->crawl_dump_timeout));
        node->scheduleAt(0 + normalize * crawler->crawl_dump_timeout,
                crawler->crawl_dump_msg);
        return true;
    }
    return false;
}

void CrawlerSelfMsgHandler::cancelEvents() {
    node->cancelEvent(crawler->crawl_msg);

    node->cancelEvent(crawler->crawl_dump_msg);
}

void CrawlerSelfMsgHandler::rescheduleEvents() {
    node->cancelEvent(crawler->crawl_msg);
    node->scheduleAt(simTime() + crawler->crawl_timeout, crawler->crawl_msg);

    node->cancelEvent(crawler->crawl_dump_msg);
    double normalize = std::round(
            1 + SIMTIME_DBL(simTime() / crawler->crawl_dump_timeout));
    node->scheduleAt(0 + normalize * crawler->crawl_dump_timeout,
            crawler->crawl_dump_msg);
}
