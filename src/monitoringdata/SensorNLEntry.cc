/*
 * SensorNLEntry.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: xtikka
 */

#include "SensorNLEntry.h"

SensorNLEntry::SensorNLEntry() {
    lastSeen = 0;
}

SensorNLEntry::SensorNLEntry(simtime_t time) {
    lastSeen = time;
}

SensorNLEntry::~SensorNLEntry() {
    // TODO Auto-generated destructor stub
}

void SensorNLEntry::updateLastSeen(simtime_t time) {
    lastSeen = time;
}

simtime_t SensorNLEntry::getTimeLastSeen() {
    return lastSeen;
}
