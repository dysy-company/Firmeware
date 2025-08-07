/*
    This file content Ethernet settings
*/
#include <mbed.h>
#ifndef Ethernet_Config_h
#define Ethernet_Config_h
        
    #define ETHERNET_BOARD_STATUS_SIZE                                          16
    #define ETHERNET_DEFAULT_TIMEOUT                                            5000
    #define ETHERNET_DEFAULT_SEND_TIMEOUT                                       500
    #define ETHERNET_DEFAULT_RECV_TIMEOUT                                       0
    #define ETHERNET_DEFAULT_PORT                                               8082
    #define ETHERNET_DEFAULT_MAX_CLIENTS                                        1
    #define ETHERNET_DEFAULT_SEND_FREQUENCY                                     1ms
    #define ETHERNET_DEFAULT_WAIT_CONNECTION                                    100ms
    #define ETHERNET_DEFAULT_TIME_BETWEEN_CMDS                                  10000 //us

    #define ETHERNET_DEFAULT_BOARD_IP_ADDRESS                                   "192.168.100.100"
    #define ETHERNET_DEFAULT_NET_MASK                                           "255.255.255.0"
    #define ETHERNET_DEFAULT_GATEWAY                                            "192.168.100.1"

//error codes
    #define ETHERNET_NO_ERROR                                                   0x0
    
    #define ETHERNET_DENIED_MODE_WHILE_SETTING_SAMPLE                           0xFFFF1000

#endif
