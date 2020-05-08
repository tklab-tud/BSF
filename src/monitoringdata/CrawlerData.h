#ifndef MONITORINGDATA_CRAWLERDATA_H_
#define MONITORINGDATA_CRAWLERDATA_H_

#include "../nodes/nodebase/NodeBase.h"
#include <fstream>

class CrawlerData {
private:
    double **adjacency;
    int* versions;
    std::ofstream versionDumps;
    int num_nodes;

public:
    NodeBase* node;

    CrawlerData(NodeBase* node, int num_nodes);
    virtual ~CrawlerData();
    void updateEntry(int src, int dst, double time);
    void updateVersion(int node, int version, simtime_t time);
    std::vector<int>* getStartNodes();
    void dumpEntries();
    void initVersionDump();
};

#endif /* MONITORINGDATA_CRAWLERDATA_H_ */
