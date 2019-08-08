/*
 * SensorNLEntry.h
 *
 *  Created on: Sep 5, 2017
 *      Author: xtikka
 */

#ifndef MONITORINGDATA_SENSORNLENTRY_H_
#define MONITORINGDATA_SENSORNLENTRY_H_

#include "omnetpp.h"

using namespace omnetpp;

class SensorNLEntry {
protected:
    simtime_t lastSeen;

public:
    SensorNLEntry();
    SensorNLEntry(simtime_t time);
    virtual ~SensorNLEntry();
    void updateLastSeen(simtime_t time);
    simtime_t getTimeLastSeen();
};

#endif /* MONITORINGDATA_SENSORNLENTRY_H_ */
