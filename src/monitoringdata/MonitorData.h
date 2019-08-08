/*
 * SensorLogic.h
 *
 *  Created on: Sep 5, 2017
 *      Author: xtikka
 */

#ifndef SENSORLOGIC_MONITORINGSTORAGE_
#define SENSORLOGIC_MONITORINGSTORAGE_

#include "SensorNLEntry.h"
#include "../botnetIds/basicid/BasicID.h"
#include <map>
#include "../nodes/sensorbase/SensorBase.h"
#include "../nodes/nodebase/NodeBase.h"

#include "omnetpp.h"

using namespace omnetpp;

class MonitorData {
private:
    std::map<int, SensorNLEntry*>* sensorNL;
    NodeBase* node;
    std::string type;
//    double boost_timeout;

public:
    MonitorData(NodeBase* node, std::string type);
    virtual ~MonitorData();
    void updateEntry(BasicID* node, simtime_t time);
    void updateEntry(int nodeID, simtime_t time);
    void dumpSensorData();
    void startBoosting();
    void stopBoosting();
    std::vector<int>* getBoostTargets();
};

#endif /* SENSORLOGIC_MONITORINGSTORAGE_ */
