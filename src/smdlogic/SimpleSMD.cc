#include "SimpleSMD.h"
#include <map>
#include <omnetpp.h>

using namespace omnetpp;

SimpleSMD::SimpleSMD() {
//    enumerate = new std::map<BasicID*, int>();
}

SimpleSMD::~SimpleSMD() {
//    delete enumerate;
}

void SimpleSMD::insert(int id) {
    if (enumerate.find(id) != enumerate.end()) {
        enumerate[id] = enumerate[id] + 1;
    } else {
        enumerate[id] = 1;
    }
}

void SimpleSMD::report() {
    std::cout << "Enumerated: " << enumerate.size() << " nodes!" << endl;
}
