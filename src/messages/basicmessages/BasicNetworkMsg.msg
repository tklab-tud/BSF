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
        NL_REQ = 101;
        NL_RESP = 102;
        PING = 103;
        PONG = 104;
        CMD_REQ = 105;
        CMD_REP = 106;
}

packet BasicNetworkMsg {
    int srcNode;
    int dstNode;
    int type = BASIC_NMSG;
}
