#include "CrawlerBase.h"

CrawlerBase::CrawlerBase() {
    // FIXME Auto-generated constructor stub

}

CrawlerBase::~CrawlerBase() {
    std::cout << "Nodes Crawled: " << startNodes.size() << endl;
    crawler_data->dumpEntries();
}

void CrawlerBase::updateEntry(int src, int dst, simtime_t time) {
    crawler_data->updateEntry(src, dst, SIMTIME_DBL(time));
}

void CrawlerBase::add2Q(int node) {
    if (visited.count(node) == 0 && node != -1) {
        Q.push(node);
        startNodes.insert(node);
        visited.insert(node);
    }
}

int CrawlerBase::getNext() {
    if (!Q.empty()) {
        int ret = Q.front();
        Q.pop();
        return ret;
    } else {
        return -1;
    }
}

void CrawlerBase::startCrawl() {
    isCrawling = true;
    visited.clear();
    std::queue<int> empty;
    std::swap(Q, empty);
    for (std::set<int>::iterator it = startNodes.begin();
            it != startNodes.end(); ++it) {
        Q.push(*it);
        visited.insert(*it);
    }
    crawl();
}

void CrawlerBase::stopCrawl() {
    isCrawling = false;
    for (std::set<int>::iterator it = visited.begin(); it != visited.end();
            ++it) {
        startNodes.insert(*it);
    }
}

