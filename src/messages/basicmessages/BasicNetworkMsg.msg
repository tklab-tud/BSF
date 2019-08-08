//
// TODO generated message class
//
cplusplus {{
#include "../../botnetIds/basicid/BasicID.h"
}}

class noncobject BasicID;


enum NetworkMsgType
{
        BASIC_NMSG = 0;
        //PING_PONG = 1;
        TIMEOUT = 3;
        NL_REQ = 10;
        NL_RESP = 11;
        PING = 4;
        PONG = 5;
}

packet BasicNetworkMsg {
    int srcNode;
    int dstNode;
    int type = BASIC_NMSG;
}
