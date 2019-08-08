#ifndef COMMON_IPADDRESS_H_
#define COMMON_IPADDRESS_H_

#include <memory>

class IPAddress {
private:
    unsigned int numeric_ip;
public:
    IPAddress();
    IPAddress(unsigned int ID);
    virtual ~IPAddress();

    bool equals(std::shared_ptr<IPAddress> ip);
    unsigned int getNumericIP();
};

#endif /* COMMON_IPADDRESS_H_ */
