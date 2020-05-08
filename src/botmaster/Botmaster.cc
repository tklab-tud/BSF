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

#include "Botmaster.h"
#include "../globalnodelist/GlobalNodeList.h"
#include "../nodes/nodebase/NodeBase.h"
#include "../nodes/simplebot/SimpleBot.h"

#include "omnetpp.h"


using namespace omnetpp;
Define_Module(Botmaster);

void Botmaster::initialize() {
    bool use_botmaster = par("use_botmaster");
    if(use_botmaster){
        version = 0;
        version_update = new BasicSelfMsg("Triggering Spawn");
        scheduleAt(simTime()+7200, version_update);
    }
}

void Botmaster::handleMessage(cMessage *msg)  {
    if (msg->isSelfMessage()) {
        if (msg == version_update) {
            injectUpdate();
            scheduleAt(simTime()+7200, version_update);
        }
    }
}

void Botmaster::injectUpdate(){
    version+=1;
//    std::cout << "Botmaster updated its version at " << simTime() << " to version " << version << std::endl;

    GlobalNodeList* gnl = static_cast<GlobalNodeList*>(getModuleByPath("BasicNetwork.GlobalNodeList"));

    NodeBase* bot = gnl->getRandomActiveNode();
    SimpleBot* s_bot = static_cast<SimpleBot*>(bot);
    s_bot->inject_botmaster_msg(version);

}

Botmaster::~Botmaster() {
    cancelAndDelete(version_update);
}

