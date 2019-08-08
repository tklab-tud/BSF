#ifndef NEIGHBORLISTS_SIMPLEENTRY_SIMPLEENTRY_H_
#define NEIGHBORLISTS_SIMPLEENTRY_SIMPLEENTRY_H_

#include "omnetpp.h"
#include "../../botnetIds/basicid/BasicID.h"

#include <memory>

using namespace omnetpp;

class SimpleEntry {
private:
    int missed_replies;
    SimTime last_seen;
    std::shared_ptr<BasicID> id;

public:
    SimpleEntry();
    SimpleEntry(std::shared_ptr<BasicID> id);
    virtual ~SimpleEntry();
    void reset_missed_replies();
    void increase_missed_replies();
    int get_missed_replies();
    std::shared_ptr<BasicID> getId();
    void update_last_seen(SimTime t);
};

#endif /* NEIGHBORLISTS_SIMPLEENTRY_SIMPLEENTRY_H_ */
