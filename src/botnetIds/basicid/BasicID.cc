#include "BasicID.h"

#include <iostream>

BasicID::BasicID() {
    basicID = -1;
}

BasicID::BasicID(BasicID* id) {
    basicID = id->basicID;
}

BasicID::BasicID(int id) {
    basicID = id;
}

BasicID::~BasicID() {
}

void BasicID::setBasicID(int id) {
    basicID = id;
}

int BasicID::getBasicID() const {
    return basicID;
}

bool BasicID::isSet() {
    if (basicID != -1) {
        return true;
    } else {
        return false;
    }
}
