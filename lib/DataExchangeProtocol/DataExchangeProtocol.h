#ifndef DATA_EXCHANGE_PROTOCOL_H
#define DATA_EXCHANGE_PROTOCOL_H

#include <mbed.h>
#include <list>
#include "..//BasicElements/BasicElements.h"
#include "..//DataChannel/DataChannel.h"

#define DATA_EXCHANGE_PROTOCOL_VERSION_LAST                  DATA_EXCHANGE_PROTOCOL_VERSION_1_2

#define DATA_EXCHANGE_PROTOCOL_VERSION_ZERO                  0x0000
#define DATA_EXCHANGE_PROTOCOL_VERSION_FIRST                 0x0001
#define DATA_EXCHANGE_PROTOCOL_VERSION_1_1                   0x0002
#define DATA_EXCHANGE_PROTOCOL_VERSION_1_2                   0x0003

#define DATA_EXCHANGE_PROTOCOL_VERSION_UNDEFINED             0xFFFF

#define DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_ZERO          8
#define DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST         10  

#define DATA_EXCHANGE_PROTOCOL_VERSION_ZERO_MAX_DATA_LENGTH  0xA559FFFF

#define DATA_EXCHANGE_PROTOCOL_ERROR_NO_ERROR                0x0

typedef uint32_t dataExchangeProtocolError_t;

class DataExchangeProtocol{

    public:
        DataExchangeProtocol(
            std::list<AnyDataChannel*>  *channelBuffers,
            uint16_t version
        );
        ~DataExchangeProtocol();

        uint32_t buildPacket         (char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize);
        template <uint32_t BufferSize>
        uint32_t buildSyncTMPacket   (char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command);
        template <uint32_t BufferSize>
        uint32_t buildSyncTMPacket   (char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command, uint16_t size);
        uint32_t buildPacketV0       (char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize);
        uint32_t buildPacketV1       (char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize);
        uint32_t buildPacketHeadV0   (char *sendBuffer, COMMAND cmd, uint32_t dataSize);
        uint32_t buildPacketHeadV1   (char *sendBuffer, COMMAND cmd, uint32_t dataSize);
        
        template <uint32_t BufferSize>
        uint32_t buildSyncTMPacketV0 (char *sendBuffer, AnyDataChannel *channel);
        
        template <uint32_t BufferSize>
        uint32_t buildSyncTMPacketV1 (char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command);
        template <uint32_t BufferSize>
        uint32_t buildSyncTMPacketV1 (char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command, uint16_t size);
        /**
         * @brief Parse header bytes
         * 
         * @param recvBuffer 
         * @return uint16_t Protocol Version of receive message
         */
         uint16_t parseHeader         (char *recvBuffer, uint32_t *dataSize);
        /**
         * @brief Parse Command of receive message
         * 
         * @param recvBuffer 
         * @return COMMAND result of parcing
         */
        COMMAND  parseCommand        (char *recvBuffer);
        /**
         * @brief Parse Data from receive message
         * 
         * @param recvBuffer 
         * @param data result after parsing
         * @param dataSize size of result
         */
        void     parseData           (char *startOfMessage, char **data, uint32_t dataSize, uint16_t version, COMMAND cmd);
        /**
         * @brief Parse DataLength from receive message
         * 
         * @param recvBuffer 
         * @param version 
         * @return uint16_t parsed datasize
         */
         uint16_t parseDataLength     (char *dataLengthPoint, uint16_t version);
        template <  typename serialNumberType, 
                    typename idType, 
                    typename modeType, 
                    typename testStatusType,
                    typename workModeType> 
         void     buildStatusData     (char* statusData, 
                                                serialNumberType serialnumber,
                                                idType id,
                                                modeType mode,
                                                testStatusType testStatus,
                                                workModeType workMode);
        
        template <  typename serialNumberType, 
                    typename idType, 
                    typename modeType, 
                    typename testStatusType,
                    typename workModeType> 
         uint32_t getStatusDataSize   ();

         uint32_t getHeadSize(uint16_t version);
         uint32_t getCommandSize();
         uint32_t getDataLengthSize();

        void setProtocolVersion(uint16_t version);
        uint16_t getProtocolVersion();

        
    private:
        BasicElements basic;
        /**
         * @brief Current version of protocol implementation
         * 
         */
        uint16_t version = 0;
        
        
        //start word should be same for all versions of protocols to save compability
        const uint16_t startWord = 0xA55A;

        
        

};
#include "DataExchangeProtocol.t.hpp"
#endif