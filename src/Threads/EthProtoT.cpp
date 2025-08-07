#include "EthProtoT.h"

EthernetProtocolThread::EthernetProtocolThread(
  EthernetInterface *net, 
  globalVariables_t *GV, 
  std::list<AnyDataChannel*>  *channelBuffers,
  Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE>                  *EthernetMailBox,
  Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE>                  *EthernetAnswerMailBox,
  Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>                  *TaskManagerMailBox,
  uint16_t version
){
  this->net = net;
  this->GV  = GV;
  this->channelBuffers        = channelBuffers;
  this->EthernetMailBox       = EthernetMailBox;
  this->EthernetAnswerMailBox = EthernetAnswerMailBox;
  this->TaskManagerMailBox    = TaskManagerMailBox;
  this->offlineTriger = new Trigger(TRIGGER_FALL_EDGE);
  this->dataProtocol = new DataExchangeProtocol(channelBuffers, version);
  this->nextVersion = version;
  this->connectionTimeout = new Timeout();
}

EthernetProtocolThread::~EthernetProtocolThread(){
  delete this->offlineTriger;
  delete this->connectionTimeout;
}

template<uint32_t BufferSize> inline void EthernetProtocolThread::resetAllChannels(){
  for (auto channel = channelBuffers->begin(); channel != channelBuffers->end(); channel++)
  {
    switch ((*channel)->getDataType())
    {
      case FLOAT:{
        FloatDataChannel<BufferSize>* channelPointer = (FloatDataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case DOUBLE:{
        DoubleDataChannel<BufferSize>* channelPointer = (DoubleDataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case UINT64:{
        Uint64DataChannel<BufferSize>* channelPointer = (Uint64DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case UINT32:{
        Uint32DataChannel<BufferSize>* channelPointer = (Uint32DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case UINT16:{
        Uint16DataChannel<BufferSize>* channelPointer = (Uint16DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      default:{
        Uint8DataChannel<BufferSize>* channelPointer = (Uint8DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case INT64:{
        Int64DataChannel<BufferSize>* channelPointer = (Int64DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case INT32:{
        Int32DataChannel<BufferSize>* channelPointer = (Int32DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case INT16:{
        Int16DataChannel<BufferSize>* channelPointer = (Int16DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
      case INT8:{
        Int8DataChannel<BufferSize>* channelPointer = (Int8DataChannel<BufferSize>*)(*channel);
        channelPointer->channel->reset();
        break;
      }
    }
  }
}

void EthernetProtocolThread::setProtocolVersion(uint16_t version){
  this->nextVersion = version;
}

uint16_t EthernetProtocolThread::getProtocolVersion(){
  return this->dataProtocol->getProtocolVersion();
}

void EthernetProtocolThread::threadExecute(){
  net->set_dhcp(0);
  net->set_network(GV->machineInfo.EthernetBoardIPAddress, 
                  GV->machineInfo.EthernetNetMask, 
                  GV->machineInfo.EthernetGateway); 
  net->connect();
  socketError = socket.open(net);
  socket.set_timeout(this->EthernetTimeout);
  socketError = socket.bind(GV->machineInfo.EthernetPort);
  socketError = socket.listen(this->EthernetMaxClients);
  
  boardStatusTimer.reset();
  boardStatusTimer.start();

  while (ethernetThreadState) {
        Watchdog::get_instance().kick();
        client = socket.accept(&socketError);
        if (socketError < 0) {
            continue;
        }
        else{
          this->connectionTimeout->detach();
          offlineTriger->push(true);
          this->resetAllChannels<VALUES_BUFFERS_SIZE>();
          while (1){
            Watchdog::get_instance().kick();
            if(this->nextVersion != this->dataProtocol->getProtocolVersion()){
              this->dataProtocol->setProtocolVersion(nextVersion);
            }
            //send answer for cmd
            if(connectionstate){
              connectionstate = false;
              EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox->try_alloc_for(100ms);
              if(EthernetAnswerMail != nullptr){
                EthernetAnswerMail->command = COMMAND::TM_ONCE_CONNECTED;
                EthernetAnswerMail->dataLength = 4;
                basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)0x0);
                EthernetAnswerMailBox->put(EthernetAnswerMail);
              }
            }
            EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox->try_get_for(0ms);
            if (EthernetAnswerMail != nullptr){
              
              uint32_t bytesToSend = dataProtocol->buildPacket(sbuffer, EthernetAnswerMail->command, EthernetAnswerMail->data, EthernetAnswerMail->dataLength);
              
              EthernetAnswerMailBox->free(EthernetAnswerMail);
              client->set_timeout(this->EthernetSendTimeout);
              socketError = client->send(sbuffer, bytesToSend);
              if (socketError < 0){
                socketError = client->close();
                break;
              }
            }

            //send periodical TM
            uint32_t bytesToSend = 0;
            if(this->dataProtocol->getProtocolVersion() == DATA_EXCHANGE_PROTOCOL_VERSION_ZERO){
              for (auto channel = channelBuffers->begin(); channel != channelBuffers->end(); channel++)
              {
                AnyDataChannel * ch = (*channel);
                bytesToSend = this->dataProtocol->buildSyncTMPacketV0<VALUES_BUFFERS_SIZE>(sbuffer, ch);
                if(bytesToSend != 0){
                  client->set_timeout(this->EthernetSendTimeout);
                  socketError = client->send(sbuffer, bytesToSend);
                  if (socketError < 0){
                    //socketError = client->close();
                    break;
                  }
                }
              }
              if (socketError < 0){
                socketError = client->close();
                break;
              }
            }else{
              if (this->dataProtocol->getProtocolVersion() >= DATA_EXCHANGE_PROTOCOL_VERSION_FIRST && this->dataProtocol->getProtocolVersion() < DATA_EXCHANGE_PROTOCOL_VERSION_UNDEFINED){
                bytesToSend = this->dataProtocol->buildSyncTMPacket<VALUES_BUFFERS_SIZE>(sbuffer, channelBuffers, COMMAND::TM_SYNC_CHANNELS);
                if(bytesToSend != 0){
                  client->set_timeout(this->EthernetSendTimeout);
                  socketError = client->send(sbuffer, bytesToSend);
                  if (socketError < 0){
                    socketError = client->close();
                    break;
                  }
                }
              }else{
                //version undefined
                this->nextVersion = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO;
              }
            }

            //send board status once in minimum 50 ms or more
            if (std::chrono::duration_cast<std::chrono::milliseconds>(boardStatusTimer.elapsed_time()) >= this->boardStatusTMPeriod){
              char statusData[this->dataProtocol->getStatusDataSize<uint64_t, uint64_t, uint32_t, uint8_t, uint8_t>()];
              this->dataProtocol->buildStatusData<uint64_t, uint64_t, uint32_t, uint8_t,uint8_t>(statusData, 
                                                                                          GV->machineInfo.serialNumber,
                                                                                          GV->machineInfo.id,
                                                                                          GV->Mode,
                                                                                          GV->testStatus,
                                                                                          (uint8_t)GV->WorkMode);
              uint32_t statusDataSize = this->dataProtocol->buildPacket(sbuffer, COMMAND::TM_BOARD_STATUS, statusData, this->dataProtocol->getStatusDataSize<uint64_t, uint64_t, uint32_t, uint8_t, uint8_t>());
              client->set_timeout(this->EthernetSendTimeout);
              socketError = client->send(sbuffer, statusDataSize);
              if (socketError < 0){
                socketError = client->close();
                break;
              }
              boardStatusTimer.reset();
            }

            //receive process
            client->set_timeout(this->EthernetRecvTimeout);
            //get first 8 bytes to save compability with old version of protocol
            //in old version first 8 bytes collect datalength and command
            socketError = client->recv(rbuffer, this->dataProtocol->getHeadSize(DATA_EXCHANGE_PROTOCOL_VERSION_UNDEFINED));
            uint32_t dataLength = 0;
            if (socketError >= 0){
              //read datalength if ver.0 
              uint16_t version = this->dataProtocol->parseHeader(rbuffer, &dataLength);
              char *offset = rbuffer + this->dataProtocol->getHeadSize(version);
              COMMAND cmd = this->dataProtocol->parseCommand(offset);
              offset = offset + this->dataProtocol->getCommandSize();
              switch(version)
              {
                case DATA_EXCHANGE_PROTOCOL_VERSION_FIRST ... DATA_EXCHANGE_PROTOCOL_VERSION_LAST:{
                  socketError = client->recv(offset, this->dataProtocol->getDataLengthSize());
                  if (socketError >= 0){
                    dataLength = this->dataProtocol->parseDataLength(offset, version);
                    offset = offset + this->dataProtocol->getDataLengthSize();
                    socketError = client->recv(offset, dataLength + sizeof(uint32_t));
                    if (socketError >= 0){
                      char *dataPoint = nullptr;
                      this->dataProtocol->parseData(rbuffer, &dataPoint, dataLength, version, cmd);
                      if(dataPoint != nullptr){
                        //send data to parser
                        EthernetMail_t *EthernetMail = EthernetMailBox->try_alloc_for(0ms);
                        if(EthernetMail != nullptr){
                          EthernetMail->command = cmd;
                          EthernetMail->dataLength = dataLength;
                          std::copy(offset, 
                                    offset + dataLength, EthernetMail->data);
                          EthernetMailBox->put(EthernetMail);
                        }else{
                          //alloc fail
                        }
                      }
                    }
                  }
                  break;
                }
                case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO:{
                  //  version 0
                  //this->nextVersion = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO; 
                  if (dataLength <= sizeof(((EthernetMail_t*)(0)))->data){
                    EthernetMail_t *EthernetMail = EthernetMailBox->try_alloc_for(0ms);
                    if(EthernetMail != nullptr){
                      EthernetMail->command = cmd;
                      EthernetMail->dataLength = dataLength;
                      client->set_timeout(this->EthernetRecvTimeout + 200);
                      socketError = client->recv(offset, dataLength);
                      if (socketError >= 0){
                        std::copy(offset, offset + dataLength, EthernetMail->data);
                      }
                      else{
                        //TODO: socket error
                      }
                    }
                    else{
                      //TODO: alloc fail
                    }
                    EthernetMailBox->put(EthernetMail);
                  }
                  break;
                }
              }
              
              
              
            }
            else{
              //TODO: socket error
            }
            client->set_timeout(this->EthernetSendTimeout);
            if(this->nextVersion != this->dataProtocol->getProtocolVersion()){
              this->dataProtocol->setProtocolVersion(this->nextVersion);
            }
            ThisThread::sleep_for(this->EthernetSendFrequency);
          }
          offlineTriger->push(false);
          connectionstate = true;
        }
        if (offlineTriger->getState()){
          this->connectionTimeout->attach(callback(this,&EthernetProtocolThread::connectionTimeoutAction), std::chrono::milliseconds(GV->machineInfo.ethernetConnectionTimeoutStopTest));
          // if (GV->controllerOnlineMode ){
          //   GV->ConstDisplacementModeParams.speedEnable = false;
          //   GV->ConstDisplacementModeParams.PositionToHold = GV->roCurrentAvPosition;
          //   GV->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          //   GV->Mode = DAC_STATE_DISP_CONST;
          //   GV->stopCurrentTestProcess = true;
          // }   
        }
        ThisThread::sleep_for(this->EthernetWaitConnection);                      
  } 
}

void EthernetProtocolThread::connectionTimeoutAction(){
  //DEPRECATED
  //if (GV->controllerOnlineMode ){
    GV->ConstDisplacementModeParams.speedEnable = false;
    GV->ConstDisplacementModeParams.PositionToHold = GV->roCurrentAvPosition;
    GV->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV->Mode = DAC_STATE_DISP_CONST;
    GV->stopCurrentTestProcess = true;
    //reset pause state
    GV->testProcessPause.resetState();
  //} 
}


