#include "IPAddress.h"

#include <memory>

IPAddress::IPAddress(unsigned int ID) {
    numeric_ip = ID;
}

IPAddress::IPAddress() {
    numeric_ip = 0;
}

IPAddress::~IPAddress() {
}

bool IPAddress::equals(std::shared_ptr<IPAddress> ip) {
    return (ip->getNumericIP() == getNumericIP());
}

unsigned int IPAddress::getNumericIP() {
    return numeric_ip;
}
