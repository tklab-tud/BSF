#include "SimpleEntry.h"
#include "omnetpp.h"

#include <memory>
#include "../../botnetIds/basicid/BasicID.h"

using namespace omnetpp;

SimpleEntry::SimpleEntry() {
    // TODO Auto-generated constructor stub

}

SimpleEntry::SimpleEntry(std::shared_ptr<BasicID> id) {
    missed_replies = 0;
    this->id = id;
    last_seen = 0;
}

SimpleEntry::~SimpleEntry() {
    // TODO Auto-generated destructor stub
}

void SimpleEntry::reset_missed_replies() {
    missed_replies = 0;
}

std::shared_ptr<BasicID> SimpleEntry::getId() {
    return id;
}

void SimpleEntry::increase_missed_replies() {
    missed_replies++;
}

int SimpleEntry::get_missed_replies() {
    return missed_replies;
}

void SimpleEntry::update_last_seen(SimTime t) {
    last_seen = t;
}
