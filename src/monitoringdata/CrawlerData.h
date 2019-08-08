#ifndef MONITORINGDATA_CRAWLERDATA_H_
#define MONITORINGDATA_CRAWLERDATA_H_

#include "../nodes/nodebase/NodeBase.h"

class CrawlerData {
private:
    double **adjacency;

public:
    NodeBase* node;

    CrawlerData(NodeBase* node, int num_nodes);
    virtual ~CrawlerData();
    void updateEntry(int src, int dst, double time);
    std::vector<int>* getStartNodes();
    void dumpEntries();
};

#endif /* MONITORINGDATA_CRAWLERDATA_H_ */
