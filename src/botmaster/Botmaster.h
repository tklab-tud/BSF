//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SRC_BOTMASTER_BOTMASTER_H_
#define SRC_BOTMASTER_BOTMASTER_H_
#include "omnetpp.h"
#include "../messages/basicmessages/BasicSelfMsg_m.h"
#include "../nodes/nodebase/NodeBase.h"

using namespace omnetpp;

class Botmaster: public cSimpleModule {
public:
    void initialize();
    virtual ~Botmaster();
private:
    int version;
    BasicSelfMsg* version_update;

    void handleMessage(cMessage *msg);
    void injectUpdate();
};

#endif /* SRC_BOTMASTER_BOTMASTER_H_ */
