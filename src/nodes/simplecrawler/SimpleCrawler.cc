#include "SimpleCrawler.h"
#include "../../selfmessagehandlers/crawlerselfmsgehandler/CrawlerSelfMsgHandler.h"
#include "../../messagehandlers/simplecrawlerhandler/SimpleCrawlerMsgHandler.h"
#include "../../globalnodelist/GlobalNodeList.h"
Define_Module(SimpleCrawler);

void SimpleCrawler::crawl() {
    int node = getNext();
    int count = 0;
    while(node != -1){
        count++;
        for(int i = 0; i < request_per_crawl; i++){
            if(node != this->getBasicID()->getBasicID())
                sendNLReq(node);
        }
        node = getNext();
    }
    std::cout << "Just crawled: " << count << " nodes at " << simTime() << endl;

    stopCrawl();
}

void SimpleCrawler::initialize(int stage) {
    if (stage == 0) {
        maxNLSize = par("max_nl_size");
        NLMinThreshold = par("nl_min_threshold");
        bootstrapNodes = par("bootstrap_nodes");
        mmInterval = par("mmInterval");
        NL_return_size = par("nl_return_size");
        crawler_start_time = par("crawler_start_time");

        offline_timer_msg = new BasicSelfMsg("offline_timer");

        ID = std::make_shared<BasicID>();

        MH.push_back(new SimpleCrawlerMsgHandler(this, this));
//        MH.push_back(new SimpleMsgHandler(this));
//        MH.push_back(new SimpleTimeoutHandler(this)); //TODO check if this works properly
        CrawlerSelfMsgHandler* csmh = new CrawlerSelfMsgHandler(this, this, crawler_start_time);
        SMH.push_back(csmh);
        active = false;

        request_per_crawl = par("request_per_crawl");

        crawl_dump_timeout = par("snapshotInterval");
        crawl_timeout = par("crawl_timeout");

        NL = std::make_shared<SimpleNL>(maxNLSize, NLMinThreshold);
        SimpleNeighbor = registerSignal("Neighbor");

        int total_nodes = par("total_nodes");
        crawler_data = new CrawlerData(this, total_nodes);
    }

    if (stage == 1) {
        connectToUnderlay();
    }

    if (stage == 2) {
        isInitialized = false;
    }
}

void SimpleCrawler::bootstrap() {
    GlobalNodeList* gnl = static_cast<GlobalNodeList*>(getModuleByPath(
            "BasicNetwork.GlobalNodeList"));

    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> b_nodes =
            gnl->getBootstrapNodes(bootstrapNodes);

    for (unsigned int i = 0; i < b_nodes->size(); i++) {
        if (b_nodes->at(i) != getBasicID()) {
            startNodes.insert(b_nodes->at(i)->getBasicID());
        }
    }
    initializedAt = simTime();
    isInitialized = true;
    setActive();
    std::cout << "Crawler initialized" << endl;
}
