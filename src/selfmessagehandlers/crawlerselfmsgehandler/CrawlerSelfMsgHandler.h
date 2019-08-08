#ifndef SELFMESSAGEHANDLERS_CRAWLERSELFMSGEHANDLER_CRAWLERSELFMSGHANDLER_H_
#define SELFMESSAGEHANDLERS_CRAWLERSELFMSGEHANDLER_CRAWLERSELFMSGHANDLER_H_

#include "../basicselfmsghandler/BasicSelfMsgHandler.h"
#include "../../nodes/nodebase/NodeBase.h"
#include "../../nodes/crawlerbase/CrawlerBase.h"

class CrawlerSelfMsgHandler: public BasicSelfMsgHandler {
public:
    CrawlerBase* crawler;
    double startTime;
    CrawlerSelfMsgHandler(NodeBase* node, CrawlerBase* crawler,
            double startTime);
    virtual ~CrawlerSelfMsgHandler();

    virtual bool handleSelfMessage(BasicSelfMsg* msg);
    virtual void cancelEvents();
    virtual void rescheduleEvents();
};

#endif /* SELFMESSAGEHANDLERS_CRAWLERSELFMSGEHANDLER_CRAWLERSELFMSGHANDLER_H_ */
