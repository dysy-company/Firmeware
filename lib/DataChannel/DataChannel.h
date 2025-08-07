#ifndef DATA_CHANNEL_H
#define DATA_CHANNEL_H

#include <mbed.h>
#include "..//..//include//Enums//Commands.h"
//#include "..//..//include//Ethernet/Ethernet_Config.h"

typedef enum channelType    :   uint8_t{
    CHANNEL_TYPE_UNDEFINED      =   0x00,
    CHANNEL_TYPE_POSITION       =   0x01,
    CHANNEL_TYPE_STRAIN         =   0x02,
    CHANNEL_TYPE_DEFORMATION    =   0x03,
    CHANNEL_TYPE_DEFORMATION_2  =   0x04,
    CHANNEL_TYPE_DEFORMATION_3  =   0x05,
    CHANNEL_TYPE_CURRENT_MODE   =   0x50,
    CHANNEL_TYPE_STEP_ID        =   0x51,
    CHANNEL_TYPE_TIME           =   0xF0,
    CHANNEL_TYPE_CYCLE          =   0xF1,
    CHANNEL_TYPE_DIAGNOSTICS    =   0xF2,
    CHANNEL_TYPE_VALVE          =   0xF3
}channelType_t;

typedef enum channelDataType : uint8_t{
    FLOAT                       = 0x00,
    DOUBLE                      = 0x01,
    UINT64                      = 0x02,
    UINT32                      = 0x03,
    UINT16                      = 0x04,
    UINT8                       = 0x05,
    INT64                       = 0x06,
    INT32                       = 0x07,
    INT16                       = 0x08,
    INT8                        = 0x09
}channelDataType_t;

class AnyDataChannel{
    public:
        virtual size_t getDataSize(){
            return this->dataSize;
        }
        virtual channelDataType_t getDataType(){
            return this->dataType;
        }
        virtual channelType_t getChannelType(){
            return this->channelType;
        }
        virtual COMMAND getChannelCommand(){
            return this->command;
        }
    private:

    protected:
        size_t dataSize = 0;
        channelType_t channelType = CHANNEL_TYPE_UNDEFINED;
        channelDataType_t dataType = FLOAT;
        COMMAND command;
};



template<typename T, uint32_t BufferSize> class DataChannel : public CircularBuffer<T, BufferSize>{
    public:
        DataChannel(channelType_t channelType){
            this->setChannelType(channelType);
        }
        DataChannel(channelType_t channelType, bool isEnabled){
            this->setChannelType(channelType);
            this->isEnabled = isEnabled;
        }
        channelType_t getChannelType(){
            return this->channelType;
        }
        void setChannelType(channelType_t channelType){
            this->channelType = channelType;
        }
        bool getChannelEnabled(){
            return this->isEnabled;
        }
        void setChannelEnabled(bool isEnabled){
            this->isEnabled = isEnabled;
        }
        uint32_t getBufferSize(){
            return this->bufferSize;
        }
    private:
        channelType_t channelType = CHANNEL_TYPE_UNDEFINED;
        bool isEnabled = true;
        uint32_t bufferSize = BufferSize;
};


template <uint32_t BufferSize> class DoubleDataChannel : public AnyDataChannel{
    public:
        DataChannel<double, BufferSize> *channel;
        DoubleDataChannel(DataChannel<double, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(double);
            this->dataType = DOUBLE;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class FloatDataChannel : public AnyDataChannel{
    public:
        DataChannel<float, BufferSize> *channel;
        FloatDataChannel(DataChannel<float, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(float);
            this->dataType = FLOAT;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Uint64DataChannel : public AnyDataChannel{
    public:
        DataChannel<uint64_t, BufferSize> *channel;
        Uint64DataChannel(DataChannel<uint64_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(uint64_t);
            this->dataType = UINT64;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Uint32DataChannel : public AnyDataChannel{
    public:
        DataChannel<uint32_t, BufferSize> *channel;
        Uint32DataChannel(DataChannel<uint32_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(uint32_t);
            this->dataType = UINT32;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Uint16DataChannel : public AnyDataChannel{
    public:
        DataChannel<uint16_t, BufferSize> *channel;
        Uint16DataChannel(DataChannel<uint16_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(uint16_t);
            this->dataType = UINT16;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Uint8DataChannel : public AnyDataChannel{
    public:
        DataChannel<uint8_t, BufferSize> *channel;
        Uint8DataChannel(DataChannel<uint8_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(uint8_t);
            this->dataType = UINT8;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Int64DataChannel : public AnyDataChannel{
    public:
        DataChannel<int64_t, BufferSize> *channel;
        Int64DataChannel(DataChannel<int64_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(int64_t);
            this->dataType = INT64;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Int32DataChannel : public AnyDataChannel{
    public:
        DataChannel<int32_t, BufferSize> *channel;
        Int32DataChannel(DataChannel<int32_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(int32_t);
            this->dataType = INT32;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Int16DataChannel : public AnyDataChannel{
    public:
        DataChannel<int16_t, BufferSize> *channel;
        Int16DataChannel(DataChannel<int16_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(int16_t);
            this->dataType = INT16;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

template <uint32_t BufferSize> class Int8DataChannel : public AnyDataChannel{
    public:
        DataChannel<int8_t, BufferSize> *channel;
        Int8DataChannel(DataChannel<int8_t, BufferSize> *channel, COMMAND TMCommand) : AnyDataChannel(){
            this->channel = channel;
            this->dataSize = sizeof(int8_t);
            this->dataType = INT8;
            this->channelType = channel->getChannelType();
            this->command = TMCommand;
        }
    private:
};

#endif 