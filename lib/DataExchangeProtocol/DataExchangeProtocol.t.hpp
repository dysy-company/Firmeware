#ifndef DATA_EXCHANGE_PROTOCOL_T_HPP
#define DATA_EXCHANGE_PROTOCOL_T_HPP

#include "DataExchangeProtocol.h"

template <typename serialNumberType, 
          typename idType, 
          typename modeType, 
          typename testStatusType,
          typename workModeType> 
inline void DataExchangeProtocol::buildStatusData(char* statusData, 
                                                    serialNumberType serialNumber, 
                                                    idType id, 
                                                    modeType mode, 
                                                    testStatusType testStatus,
                                                    workModeType workMode){
  basic.writeValueToBytesBuffer(statusData, serialNumber);
  basic.writeValueToBytesBuffer(statusData, id, sizeof(serialNumber));
  basic.writeValueToBytesBuffer(statusData, mode, sizeof(serialNumber) + sizeof(id));
  basic.writeValueToBytesBuffer(statusData, testStatus, sizeof(mode) + sizeof(serialNumber) + sizeof(id));
  switch(this->version){
    case DATA_EXCHANGE_PROTOCOL_VERSION_1_1 ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
      basic.writeValueToBytesBuffer(statusData, workMode, sizeof(mode) + sizeof(serialNumber) + sizeof(id) + sizeof(testStatus));
      break;
    default:
      break;
  }
  
}

template <typename serialNumberType, 
          typename idType, 
          typename modeType, 
          typename testStatusType,
          typename workModeType> 
inline uint32_t DataExchangeProtocol::getStatusDataSize(){
  switch (this->version)
  {
  case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO ... DATA_EXCHANGE_PROTOCOL_VERSION_FIRST:
    return
    sizeof (serialNumberType) + 
    sizeof (idType) +
    sizeof (modeType) +
    sizeof (testStatusType);
    break;
  case DATA_EXCHANGE_PROTOCOL_VERSION_1_1 ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
    return
    sizeof (serialNumberType) + 
    sizeof (idType) +
    sizeof (modeType) +
    sizeof (testStatusType)+
    sizeof (workModeType);
    break;
  default:
    return
    sizeof (serialNumberType) + 
    sizeof (idType) +
    sizeof (modeType) +
    sizeof (testStatusType);
    break;
  }
  
}

template <uint32_t BufferSize> uint32_t DataExchangeProtocol::buildSyncTMPacket(char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command){
  switch (this->version)
  {
    case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:
      //return this->buildSyncTMPacketV0(sendBuffer);
      break;
    case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
      return this->buildSyncTMPacketV1<BufferSize>(sendBuffer, channelBuffers, command);
      break;
    default:
      return 0;
      break;
  }
  return 0;
}

template <uint32_t BufferSize> uint32_t DataExchangeProtocol::buildSyncTMPacket(char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command, uint16_t size){
  switch (this->version)
  {
    case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:
      //return this->buildSyncTMPacketV0(sendBuffer);
      break;
    case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
      return this->buildSyncTMPacketV1<BufferSize>(sendBuffer, channelBuffers, command, size);
      break;
    default:
      return 0;
      break;
  }
  return 0;
}

template <uint32_t BufferSize> uint32_t DataExchangeProtocol::buildSyncTMPacketV0 (char *sendBuffer, AnyDataChannel *channel){
    //COMMAND command= COMMAND::UNDEFINED;
    uint32_t floatNumbers = 0;
    uint32_t bytesNumbers = 0;
    uint32_t counter = 0;
    //channelType_t channelType = CHANNEL_TYPE_UNDEFINED;
    size_t channelSize = 0;
    size_t dataSize = 0;

    switch (channel->getDataType())
    {
      case FLOAT:{
        FloatDataChannel<BufferSize>* channelPointer = (FloatDataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case DOUBLE:{
        DoubleDataChannel<BufferSize>* channelPointer = (DoubleDataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case UINT64:{
        Uint64DataChannel<BufferSize>* channelPointer = (Uint64DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case UINT32:{
        Uint32DataChannel<BufferSize>* channelPointer = (Uint32DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case UINT16:{
        Uint16DataChannel<BufferSize>* channelPointer = (Uint16DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      default:{
        Uint8DataChannel<BufferSize>* channelPointer = (Uint8DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case INT64:{
        Int64DataChannel<BufferSize>* channelPointer = (Int64DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case INT32:{
        Int32DataChannel<BufferSize>* channelPointer = (Int32DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case INT16:{
        Int16DataChannel<BufferSize>* channelPointer = (Int16DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
      case INT8:{
        Int8DataChannel<BufferSize>* channelPointer = (Int8DataChannel<BufferSize>*)(channel);
        //channelType = channelPointer->channel->getChannelType();
        channelSize = channelPointer->channel->size();
        dataSize = channelPointer->getDataSize();
        break;
      }
    }

    // switch(channelType){
    //   case CHANNEL_TYPE_POSITION:{
    //     command = COMMAND::TM_DISPLACEMENT_VALUES;
    //     break;
    //   }
    //   case CHANNEL_TYPE_STRAIN:{
    //     command = COMMAND::TM_LOAD_VALUES;
    //     break;
    //   }
    //   case CHANNEL_TYPE_DEFORMATION:{
    //     command = COMMAND::TM_DEFORMATION_VALUES;
    //     break;
    //   }
    //   case CHANNEL_TYPE_TIME:{
    //     command = COMMAND::TM_TIME;
    //     break;
    //   }
    //   case CHANNEL_TYPE_CYCLE:{
    //     command = COMMAND::TM_CYCLE;
    //     break;
    //   }
    //   default:

    //     break;
    // }
    counter = DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_ZERO;
    floatNumbers = channelSize;
    bytesNumbers = floatNumbers * dataSize;
    for(int i = 0; i < (int)floatNumbers; i++){
      switch (channel->getDataType())
      {
        case FLOAT:{
          float value = NAN;
          FloatDataChannel<BufferSize>* channelPointer = (FloatDataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case DOUBLE:{
          double value = NAN;
          DoubleDataChannel<BufferSize>* channelPointer = (DoubleDataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case UINT64:{
          uint64_t value = 0;
          Uint64DataChannel<BufferSize>* channelPointer = (Uint64DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case UINT32:{
          uint32_t value = 0;
          Uint32DataChannel<BufferSize>* channelPointer = (Uint32DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case UINT16:{
          uint16_t value = 0;
          Uint16DataChannel<BufferSize>* channelPointer = (Uint16DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        default:{
          uint8_t value = 0;
          Uint8DataChannel<BufferSize>* channelPointer = (Uint8DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case INT64:{
          int64_t value = 0;
          Int64DataChannel<BufferSize>* channelPointer = (Int64DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case INT32:{
          int32_t value = 0;
          Int32DataChannel<BufferSize>* channelPointer = (Int32DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case INT16:{
          int16_t value = 0;
          Int16DataChannel<BufferSize>* channelPointer = (Int16DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
        case INT8:{
          int8_t value = 0;
          Int8DataChannel<BufferSize>* channelPointer = (Int8DataChannel<BufferSize>*)(channel);
          channelPointer->channel->pop(value);
          counter += basic.writeValueToBytesBuffer(sendBuffer, value, counter);   
          break;
        }
      }
      
    }
    this->buildPacketHeadV0(sendBuffer, channel->getChannelCommand(), bytesNumbers);
    return counter;
}

template <uint32_t BufferSize> uint32_t DataExchangeProtocol::buildSyncTMPacketV1(char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command, uint16_t size){
  uint8_t countOfChannels = 0;
  for (auto channel = channelBuffers->begin(); channel != channelBuffers->end(); channel++)
  {
    countOfChannels++;
  }
  //build number, length, interval, stroke
  uint32_t dataSize = basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, countOfChannels, DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST);
  dataSize += basic.writeValueToBytesBuffer<uint16_t>(sendBuffer, size, DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST + sizeof(countOfChannels));
  int offset = DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST + sizeof(countOfChannels) + sizeof(size);
  
  for (auto channel = channelBuffers->begin(); channel != channelBuffers->end(); channel++)
  {
    switch ((*channel)->getDataType()){
      case FLOAT:{
        FloatDataChannel<BufferSize>* channelPointer = (FloatDataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          float value = NAN;
          for (size_t i = 0; i < size; i++)
          {
            value = NAN;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (float);
          }
        }
        break;
      }
      case DOUBLE:{
        DoubleDataChannel<BufferSize>* channelPointer = (DoubleDataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          double value = NAN;
          for (size_t i = 0; i < size; i++)
          {
            value = NAN;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (double);
          }
        }
        break;
      }
      case UINT64:{
        Uint64DataChannel<BufferSize>* channelPointer = (Uint64DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          uint64_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (uint64_t);
          }
        }
        break;
      }
      case UINT32:{
        Uint32DataChannel<BufferSize>* channelPointer = (Uint32DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          uint32_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (uint32_t);
          }
        }
        break;
      }
      case UINT16:{
        Uint16DataChannel<BufferSize>* channelPointer = (Uint16DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          uint16_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (uint16_t);
          }
        }
        break;
      }
      default:{
        Uint8DataChannel<BufferSize>* channelPointer = (Uint8DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          uint8_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (uint8_t);
          }
        }
        break;
      }

      case INT64:{
        Int64DataChannel<BufferSize>* channelPointer = (Int64DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          int64_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (int64_t);
          }
        }
        break;
      }
      case INT32:{
        Int32DataChannel<BufferSize>* channelPointer = (Int32DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          int32_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (int32_t);
          }
        }
        break;
      }
      case INT16:{
        Int16DataChannel<BufferSize>* channelPointer = (Int16DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          int16_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (int16_t);
          }
        }
        break;
      }
      case INT8:{
        Int8DataChannel<BufferSize>* channelPointer = (Int8DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->channel->getChannelType(), offset);
          offset++;
          dataSize += basic.writeValueToBytesBuffer<uint8_t>(sendBuffer, channelPointer->getDataType(), offset);
          offset++;
          int8_t value = 0;
          for (size_t i = 0; i < size; i++)
          {
            value = 0;
            channelPointer->channel->pop(value);
            dataSize += basic.writeValueToBytesBuffer(sendBuffer, value, offset);
            offset += sizeof (int8_t);
          }
        }
        break;
      }
    
    }
  }
  dataSize += this->buildPacketHeadV1(sendBuffer, command, dataSize);
  dataSize += basic.writeValueToBytesBuffer<uint32_t>(sendBuffer, (uint32_t)basic.Crc32((unsigned char*)sendBuffer, dataSize), dataSize);
  return dataSize;
}

template <uint32_t BufferSize> uint32_t DataExchangeProtocol::buildSyncTMPacketV1(char *sendBuffer, std::list<AnyDataChannel*>  *channelBuffers, COMMAND command){
  uint16_t minChannelSize = UINT16_MAX;
  for (auto channel = channelBuffers->begin(); channel != channelBuffers->end(); channel++)
  {
    switch ((*channel)->getDataType())
    {
      case FLOAT:{
        FloatDataChannel<BufferSize>* channelPointer = (FloatDataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case DOUBLE:{
        DoubleDataChannel<BufferSize>* channelPointer = (DoubleDataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case UINT64:{
        Uint64DataChannel<BufferSize>* channelPointer = (Uint64DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case UINT32:{
        Uint32DataChannel<BufferSize>* channelPointer = (Uint32DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case UINT16:{
        Uint16DataChannel<BufferSize>* channelPointer = (Uint16DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      default:{
        Uint8DataChannel<BufferSize>* channelPointer = (Uint8DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case INT64:{
        Int64DataChannel<BufferSize>* channelPointer = (Int64DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case INT32:{
        Int32DataChannel<BufferSize>* channelPointer = (Int32DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case INT16:{
        Int16DataChannel<BufferSize>* channelPointer = (Int16DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }

      case INT8:{
        Int8DataChannel<BufferSize>* channelPointer = (Int8DataChannel<BufferSize>*)(*channel);
        if(channelPointer->channel->getChannelEnabled()){
          
          if(channelPointer->channel->size() < minChannelSize){
            minChannelSize = channelPointer->channel->size();
          }
        }
        break;
      }
    
    }
    
  } 
  return this->buildSyncTMPacketV1<BufferSize>(sendBuffer, channelBuffers, command, minChannelSize);
}

#endif