#include "DataExchangeProtocol.h"

DataExchangeProtocol::DataExchangeProtocol(
    std::list<AnyDataChannel*>  *channelBuffers,
    uint16_t version
){
    //check version
    switch (version)
    {
    case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
      this->version               = version;
      break;
    default:
      this->version               = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO;
      break;
    }
}

void DataExchangeProtocol::setProtocolVersion(uint16_t version){
  this->version = version;
}

uint16_t DataExchangeProtocol::getProtocolVersion(){
  return this->version;
}

uint32_t DataExchangeProtocol::getCommandSize(){
  return sizeof(COMMAND);
}

uint32_t DataExchangeProtocol::getDataLengthSize(){
  return sizeof(uint16_t);
}



uint32_t DataExchangeProtocol::buildPacket(char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize){
  switch (this->version)
  {
  case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:
    return this->buildPacketV0(sendBuffer, cmd, dataToSend, dataSize);
    break;
  case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
    return this->buildPacketV1(sendBuffer, cmd, dataToSend, dataSize);
    break;
  default:
    return this->buildPacketV0(sendBuffer, cmd, dataToSend, dataSize);
    break;
  }
}

uint32_t DataExchangeProtocol::buildPacketV0(char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize){
  std::copy(dataToSend, dataToSend + dataSize, sendBuffer + this->buildPacketHeadV0(sendBuffer, cmd, dataSize));
  dataSize += DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_ZERO;
  return dataSize;
}

uint32_t DataExchangeProtocol::buildPacketHeadV0(char *sendBuffer, COMMAND cmd, uint32_t dataSize){
  basic.writeValueToBytesBuffer<uint32_t>(sendBuffer, dataSize);
  basic.writeValueToBytesBuffer(sendBuffer + sizeof (dataSize), cmd);
  return sizeof (dataSize) + sizeof (cmd);
}

uint32_t DataExchangeProtocol::buildPacketV1(char *sendBuffer, COMMAND cmd, char *dataToSend, uint32_t dataSize){
  std::copy(dataToSend, dataToSend + dataSize, sendBuffer + this->buildPacketHeadV1(sendBuffer, cmd, dataSize));
  dataSize += DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST;
  basic.writeValueToBytesBuffer<uint32_t>(sendBuffer, (uint32_t)basic.Crc32((unsigned char*)sendBuffer, dataSize), dataSize);
  dataSize += sizeof(uint32_t);
  return dataSize;
}

uint32_t DataExchangeProtocol::buildPacketHeadV1(char *sendBuffer, COMMAND cmd, uint32_t dataSize){
  basic.writeValueToBytesBuffer<uint16_t>(sendBuffer, this->startWord);
  basic.writeValueToBytesBuffer<uint16_t>(sendBuffer, this->version, sizeof(this->startWord));
  //write command
  basic.writeValueToBytesBuffer(sendBuffer, cmd, sizeof(this->startWord) + sizeof(this->version));
  basic.writeValueToBytesBuffer<uint16_t>(sendBuffer, (uint16_t)dataSize, sizeof(this->startWord) + sizeof(this->version) + sizeof(cmd));
  return sizeof(this->startWord) + sizeof(this->version) + sizeof(cmd) + sizeof ((uint16_t)dataSize);
}



uint16_t DataExchangeProtocol::parseHeader(char *startOfMessage, uint32_t *dataSize){
  uint32_t header = 0xFFFFFFFF;
  uint16_t startHalfWord = 0;
  uint16_t version = 0;
  *dataSize = 0xFFFFFFFF;
  //read startHalfWord (in versions 1 or higher) or datalength (in version 0)
  basic.writeBytesBufferToValue(startOfMessage, &header);
  startHalfWord = (header >> 16) & 0xFFFF;
  if(startHalfWord == this->startWord){
    //version 1 or higher
    //read version except version 0
    version = header & 0xFFFF;
    //basic.writeBytesBufferToValue<uint16_t>(recvBuffer + sizeof(startHalfWord), &version);
  }else{
    if(header <= DATA_EXCHANGE_PROTOCOL_VERSION_ZERO_MAX_DATA_LENGTH){
      //version 0
      version = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO; 
      *dataSize = header;
    }else{
      version = DATA_EXCHANGE_PROTOCOL_VERSION_UNDEFINED;
    }
  }
  return version;
}

COMMAND DataExchangeProtocol::parseCommand(char *cmdPoint){
  COMMAND command = COMMAND::UNDEFINED;
  //read command
  basic.writeBytesBufferToValue(cmdPoint, &command);
  return command;
}

uint16_t DataExchangeProtocol::parseDataLength(char *dataLengthPoint, uint16_t version){
  uint16_t dataSize = 0;
  switch (version)
  {
  case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
     basic.writeBytesBufferToValue(dataLengthPoint, &dataSize);
    break;
  
  default:
    break;
  }
  return dataSize;
}

void DataExchangeProtocol::parseData(char *startOfMessage, char **data, uint32_t dataSize, uint16_t version, COMMAND cmd){
  switch (version){
    case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:{
      uint32_t crc32 = 0;
      //read crc32
      basic.writeBytesBufferToValue<uint32_t>(startOfMessage 
                                            + sizeof(this->startWord) 
                                            + sizeof(version) 
                                            + sizeof(cmd)
                                            + sizeof(uint16_t) //dataSize field
                                            + dataSize, &crc32);
      //check CRC32
      if(basic.Crc32((unsigned char *)startOfMessage, 
            sizeof(this->startWord) 
          + sizeof(version) 
          + sizeof(cmd) 
          + sizeof(uint16_t) //dataSize field
          + dataSize) == crc32)
      {
        //automatic switch to current version of protocol
        //this->version = version;
        *data = startOfMessage + sizeof(this->startWord) + sizeof(version) + sizeof(cmd) + sizeof(uint16_t);
      }
      break;
    }
    case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:{
      //version 0
      //this->version = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO; 
      *data = startOfMessage + sizeof(uint32_t) + sizeof(cmd);
      break;
    }
    default:
      //this->version = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO;
      break;
  }
}

uint32_t DataExchangeProtocol::getHeadSize(uint16_t version){
  uint32_t dataSize = 0;
  switch (version)
  {
    case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:
      dataSize = 4;
      break;
    case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:
      dataSize = 4;
      break;
    default:
      dataSize = 8;
      break;
  }
  return dataSize;
}
