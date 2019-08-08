cplusplus {{
#include "../basicmessages/BasicNetworkMsg_m.h"
#include "../../botnetIds/basicid/BasicID.h"
#include <memory>

typedef std::vector<std::shared_ptr<BasicID>>* BasicIDVec;
}}
packet BasicNetworkMsg;
class BasicIDVec extends void;
//
// TODO generated message class
//
packet SimpleNLRespMsg extends BasicNetworkMsg {
    type = NL_RESP;
    BasicIDVec neighbors;
}
