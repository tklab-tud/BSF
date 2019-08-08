#ifndef NEIGHBORLISTS_SIMPLENL_SIMPLENL_H_
#define NEIGHBORLISTS_SIMPLENL_SIMPLENL_H_

#include <omnetpp.h>
#include <memory>

#include"../../neighborlists/simpleentry/SimpleEntry.h"

using namespace omnetpp;

class SimpleNL {

private:

protected:
    std::map<int, std::shared_ptr<SimpleEntry>>* neighborsMap; /**< Map variation*/
//    std::vector<std::shared_ptr<SimpleEntry>>* neighborsVector; /**< Vector variation*/

// Iterators
    typedef std::map<int, std::shared_ptr<SimpleEntry>>::iterator neighborMapIter;
    typedef std::map<int, std::shared_ptr<SimpleEntry>>::const_iterator neighborMapConstIter;

//    typedef std::vector<std::shared_ptr<SimpleEntry>>::iterator neighborVectorIter;
//    typedef std::vector<std::shared_ptr<SimpleEntry>>::const_iterator neighborVectorConstIter;

    cRNG* m_twist;
    unsigned int MAX_NL_SIZE;
    unsigned int MIN_NL_SIZE;

public:
    SimpleNL(unsigned int maxNLSize, unsigned int nl_min_thresh);
    SimpleNL();
    virtual ~SimpleNL();

    bool exists(std::shared_ptr<BasicID> peer);
    void addPeer(std::shared_ptr<BasicID> peer);
    void removePeer(int peer);
    std::shared_ptr<BasicID> getRandomPeer(int rand);
    std::shared_ptr<BasicID> getPeer(int entry_num);
    std::shared_ptr<SimpleEntry> getEntry(int entry_num);
    std::shared_ptr<std::vector<std::shared_ptr<BasicID>>> getAll();
    void resetNL();
    unsigned int getSize();
    bool isFull();
    unsigned int getMaxSize();
    void update(SimTime t, int node);
    void dumpNL();
};

#endif /* NEIGHBORLISTS_SIMPLENL_SIMPLENL_H_ */
