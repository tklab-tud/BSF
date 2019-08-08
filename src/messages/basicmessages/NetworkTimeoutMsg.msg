cplusplus {{
#include "BasicNetworkMsg_m.h"
}}
packet BasicNetworkMsg;
//class noncobject BasicNetworkMsg;

//
// TODO generated message class
//
packet NetworkTimeoutMsg extends BasicNetworkMsg {
    type = TIMEOUT;
    BasicNetworkMsg toMsg;
    int timeouttype;
}
