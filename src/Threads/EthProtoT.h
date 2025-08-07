/**
 * @file EthProtoT.h
 * @author Grigorii Bragin
 * @brief Class definition of ethernet protocol thread
 * @version 1.1
 * @date 2024-05-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef ETHERNET_PROTOCOL_THREAD_H
#define ETHERNET_PROTOCOL_THREAD_H
#include <mbed.h>
#include <EthernetInterface.h>
#include "..//..//include/TypeDefs/Threads_Mail_Types.h"
#include "..//..//include/Global_Variables.h"
#include "..//..//lib/BasicElements/BasicElements.h"
#include "..//..//lib/Trigger/Trigger.h"
#include <list>
#include "..//..//lib/DataChannel/DataChannel.h"
#include "..//..//lib/DataExchangeProtocol/DataExchangeProtocol.h"
#include "..//..//include/Shared_Params.h"


/**
 * @brief Implements connection, state, send and receive data of ethernet protocol
 * 
 */
class EthernetProtocolThread{
    public:
        EthernetProtocolThread(
            EthernetInterface *net, 
            globalVariables_t *GV, 
            std::list<AnyDataChannel*>  *channelBuffers,
            Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE>                  *EthernetMailBox,
            Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE>                  *EthernetAnswerMailBox,
            Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>                  *TaskManagerMailBox,
            uint16_t version
        );
        ~EthernetProtocolThread();
        
        /**
         * @brief Implementation
         * 
         */
        void threadExecute();
        void setProtocolVersion(uint16_t version);
        uint16_t getProtocolVersion();
        
    private:
        BasicElements basic;
        /**
         * @brief Receive data buffer
         * 
         */
        char rbuffer[VALUES_BUFFERS_SIZE * 4 + DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST];
        /**
         * @brief Send data buffer
         * 
         */
        char sbuffer[VALUES_BUFFERS_SIZE + DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST];
        Trigger *offlineTriger; 
        Timeout *connectionTimeout; 
        Timer boardStatusTimer;
        TCPSocket socket;
        TCPSocket *client;
        nsapi_error_t socketError;
        uint32_t ethernetThreadState = 1;
        
        DataExchangeProtocol *dataProtocol;
        uint16_t nextVersion = 0;

        bool connectionstate = true;

         //ETHERNET PARAMS:
        int EthernetTimeout =       ETHERNET_DEFAULT_TIMEOUT;           
        int EthernetSendTimeout =   ETHERNET_DEFAULT_SEND_TIMEOUT;
        int EthernetRecvTimeout =   ETHERNET_DEFAULT_RECV_TIMEOUT;   
        // uint16_t EthernetPort =     ETHERNET_DEFAULT_PORT;     
        int EthernetMaxClients =    ETHERNET_DEFAULT_MAX_CLIENTS;
        std::chrono::milliseconds EthernetSendFrequency =   ETHERNET_DEFAULT_SEND_FREQUENCY;
        std::chrono::milliseconds EthernetWaitConnection =  ETHERNET_DEFAULT_WAIT_CONNECTION;
        // SocketAddress EthernetBoardIPAddress =  ETHERNET_DEFAULT_BOARD_IP_ADDRESS;
        // SocketAddress EthernetNetMask =         ETHERNET_DEFAULT_NET_MASK;
        // SocketAddress EthernetGateway =         ETHERNET_DEFAULT_GATEWAY;

        EthernetInterface *net;
        globalVariables_t *GV;
        std::list<AnyDataChannel*>  *channelBuffers;
        Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE>                  *EthernetMailBox;
        Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE>                  *EthernetAnswerMailBox;
        Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>                  *TaskManagerMailBox;
        
        
        const std::chrono::milliseconds boardStatusTMPeriod = 50ms;

        template<uint32_t BufferSize>
        inline void     resetAllChannels    ();
        void connectionTimeoutAction();
};

#endif