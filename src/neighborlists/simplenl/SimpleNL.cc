#include "../simplenl/SimpleNL.h"

#include <memory>
#include <omnetpp.h>

#include "../../botnetIds/basicid/BasicID.h"
#include"../../neighborlists/simpleentry/SimpleEntry.h"

using namespace omnetpp;

SimpleNL::SimpleNL(unsigned int maxNLSize, unsigned int nl_min_thresh) {
    neighborsMap = new std::map<int, std::shared_ptr<SimpleEntry>>();
    MAX_NL_SIZE = maxNLSize;
    MIN_NL_SIZE = nl_min_thresh;

}

SimpleNL::SimpleNL() {

}

SimpleNL::~SimpleNL() {
    delete neighborsMap;
}

bool SimpleNL::exists(std::shared_ptr<BasicID> peer) {
    if (neighborsMap->count(peer->getBasicID())) {
        return true;
    } else {
        return false;
    }
}

void SimpleNL::addPeer(std::shared_ptr<BasicID> peer) {
    if (!exists(peer) && !isFull()) {
        neighborsMap->insert(
                std::pair<int, std::shared_ptr<SimpleEntry>>(peer->getBasicID(),
                        std::make_shared<SimpleEntry>(peer)));
    }
}

void SimpleNL::removePeer(int peer) {
    if (neighborsMap->size() > MIN_NL_SIZE) {
        neighborsMap->erase(peer);
    }
}

std::shared_ptr<BasicID> SimpleNL::getRandomPeer(int rand) {
    return getAll().get()->at(rand);

}

std::shared_ptr<BasicID> SimpleNL::getPeer(int entry_num) {
    return neighborsMap->at(entry_num)->getId();
}

std::shared_ptr<SimpleEntry> SimpleNL::getEntry(int entry_num) {
    return neighborsMap->at(entry_num);
}

std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> SimpleNL::getAll() {
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> retVec =
            std::make_shared<std::vector<std::shared_ptr<BasicID>>>();

    for (neighborMapIter it = neighborsMap->begin(); it != neighborsMap->end();
            ++it) {
        retVec->push_back(it->second->getId());
    }

    return retVec;
}

void SimpleNL::resetNL() {
    delete neighborsMap;
    neighborsMap = new std::map<int, std::shared_ptr<SimpleEntry>>();
}

unsigned int SimpleNL::getSize() {
    return neighborsMap->size();
}

bool SimpleNL::isFull() {
    if (neighborsMap->size() == getMaxSize()) {
        return true;
    } else {
        return false;
    }
}

unsigned int SimpleNL::getMaxSize() {
    return MAX_NL_SIZE;
}

void SimpleNL::update(SimTime t, int node) {
    neighborsMap->at(node)->update_last_seen(t);
    neighborsMap->at(node)->reset_missed_replies();
}

void SimpleNL::dumpNL() {
    std::cout << "------------ Dumping NL ------------ " << getSize() << endl;
}
