cplusplus {{
#include "../basicmessages/BasicNetworkMsg_m.h"
}}
packet BasicNetworkMsg;

//
// TODO generated message class
//
packet PongMsg extends BasicNetworkMsg {
    type = PONG;
    int version;
}
