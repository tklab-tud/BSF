#ifndef SMDLOGIC_SIMPLESMD_H_
#define SMDLOGIC_SIMPLESMD_H_

#include "../botnetIds/basicid/BasicID.h"
#include <map>

class SimpleSMD {
public:
    SimpleSMD();
    virtual ~SimpleSMD();
    std::map<int, int> enumerate;
    void insert(int id);
    void report();
};

#endif /* SMDLOGIC_SIMPLESMD_H_ */
