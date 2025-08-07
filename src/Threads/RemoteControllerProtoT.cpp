#include "RemoteControllerProtoT.h"
#define SEND_TM_DELAY 300000
#define SEND_BOARD_STATUS_TM_DELAY 600000
#define PROTOCOL_VERSION 2

RemoteControllerProtocolThread::RemoteControllerProtocolThread(PinName _rx,
                                                               PinName _tx,
                                                               int _baudRate,
                                                               globalVariables_t *_GV,
                                                               std::list<AnyDataChannel *> *_channelBuffers,
                                                               Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *REMOTECONTROLLERMailBox,
                                                               Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *REMOTECONTROLLERAnswerMailBox,
                                                               Mail<TaskManagerMail_t, DEFAULT_MAIL_SIZE> *TASKManagerMailBox)
{
    rxPin = _rx;
    txPin = _tx;
    baudRate = _baudRate;
    GV = _GV;
    channelBuffers = _channelBuffers;
    RemoteControllerMailBox = REMOTECONTROLLERMailBox;
    RemoteControllerAnswerMailBox = REMOTECONTROLLERAnswerMailBox;
    TaskManagerMailBox = TASKManagerMailBox;
    dataProtocol = new DataExchangeProtocol(channelBuffers, PROTOCOL_VERSION);
    UART = new BufferedSerial(txPin, rxPin, baudRate);
}

RemoteControllerProtocolThread::~RemoteControllerProtocolThread()
{
    delete dataProtocol;
    delete UART;
}

template<uint32_t BufferSize>
inline void RemoteControllerProtocolThread::resetAllChannels(){
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

int RemoteControllerProtocolThread::findStartWord()
{
	int finded = 0, check = 0;
	while(!finded) {
		rDataLen = 0;
		check = UART->read(rbuffer, 1);
		if(check <= 0)
			return 0;
		if(rbuffer[0] == 0xA5) {
			check = UART->read(rbuffer + 1, 1);
			if(check <= 0)
				return 0;
			if(rbuffer[1] == 0x5A) {
				finded = 1;
			}
		}
	}
	rDataLen = 2;
	return rDataLen;
}

void RemoteControllerProtocolThread::getHandshake()
{
	while(1) {
		if(UART->readable()) {
			return;
		}
		ThisThread::sleep_for(1s);
	}
}

int RemoteControllerProtocolThread::Read(unsigned int len)
{
	int check = 0, cnt = 0;
	while(len) {
		check = UART->read(rbuffer + rDataLen, len);
		if(check > 0) {
			rDataLen += check;
			len -= check;
		} else {
			ThisThread::sleep_for(5ms);
		}
		if(cnt > 20) {
			return 0;
		}
		cnt++;
	}
	return rDataLen;
}

void RemoteControllerProtocolThread::threadExecute()
{
	unsigned long long check_timer = 0;
	char statusData[256];
    UART->set_blocking(0);
    short check_poll = 0;
    char *startPtr = rbuffer;
    int check = 0;
    boardStatusTimer.reset();
    boardStatusTimer.start();
	syncTMTimer.reset();
	syncTMTimer.start();
    char *offset;
    COMMAND cmd;
    unsigned short dataLength;
    rDataLen = 0;
	getHandshake();
    this->resetAllChannels<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>();
    while (1)
    {
        Watchdog::get_instance().kick();
        rDataLen = 0;
#if 0
		printf("[start loop sDataLen = %d]", sDataLen);
#endif
        // init send data
		if(!sDataLen) {
			check_timer = syncTMTimer.read_us();
			if ((check_timer >= SEND_TM_DELAY)) {      // Init TM packet
				sDataLen = this->dataProtocol->buildSyncTMPacket<(REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE)>(sbuffer, channelBuffers, COMMAND::TM_SYNC_CHANNELS, 1);
#if 0
				printf("[TM sDataLen = %d]", sDataLen);
#endif
				syncTMTimer.stop();
				syncTMTimer.reset();
				syncTMTimer.start();
			// init board status TM
			} else {
				check_timer = boardStatusTimer.read_us();
				if ((check_timer >= SEND_BOARD_STATUS_TM_DELAY)) {
					uint32_t BS_size = this->dataProtocol->getStatusDataSize<uint64_t, uint64_t, uint32_t, uint8_t, uint32_t>();
					if(BS_size > 256) {		// not happen
						continue;
					}
					this->dataProtocol->buildStatusData<uint64_t, uint64_t, uint32_t, uint8_t, uint32_t>(statusData,
																								GV->machineInfo.serialNumber,
																								GV->machineInfo.id,
																								GV->Mode,
																								GV->testStatus,
																								GV->WorkMode);
					sDataLen = this->dataProtocol->buildPacket(sbuffer, COMMAND::TM_BOARD_STATUS, statusData, BS_size);
#if 0
					printf("[BS sDataLen = %d]", sDataLen);
#endif
					boardStatusTimer.stop();
					boardStatusTimer.reset();
					boardStatusTimer.start();
				// init answer
				} else {
					UARTMail_t *ReCoAnswerMail = RemoteControllerAnswerMailBox->try_get_for(0ms);
					if(ReCoAnswerMail != nullptr) {
						sDataLen = dataProtocol->buildPacket(sbuffer, ReCoAnswerMail->command, ReCoAnswerMail->data, ReCoAnswerMail->dataLength);
#if 0
						printf("[cmd sDataLen = %d]", sDataLen);
#endif
						RemoteControllerAnswerMailBox->free(ReCoAnswerMail);
					}
				}
			}
		}

        check_poll = UART->poll(POLLIN | POLLOUT);
        // send UART sbuffer
        if ((check_poll & POLLOUT) == POLLOUT && sDataLen) {
			char dummy[2] = {0xff, 0xff};	// , 0xff, 0xff};
			UART->write(dummy, 2);
            int checkSendData = UART->write(sbuffer, sDataLen);
#if 0
			printf("[send %d]\n", checkSendData);
#endif
            if (checkSendData < 1)
                continue;
            else if (checkSendData == sDataLen) {
				sDataLen = 0;
            }
        }
        // read UART to rbuffer
        if ((check_poll & POLLIN) == POLLIN) {

			/* get start word to rbuffer*/
			rDataLen = findStartWord();
            if(rDataLen <= 0)
				continue;
			/* get version to rbuffer, next to startword*/
            check = Read(this->dataProtocol->getHeadSize(PROTOCOL_VERSION)-rDataLen);
            if(check <= 0)
				continue;
			// count rbuffer
#if 0
            for (unsigned short i = 0; i < rDataLen; i++) {
                startPtr = rbuffer + i;
                if((*(startPtr) == 0xA5 || *(startPtr + 1) == 0x5A) && *(startPtr + 2) == 0) {
                    break;
                }
                startPtr = nullptr;
            }
#endif
			startPtr = rbuffer;
            if(startPtr == nullptr)
                continue;

			static uint16_t vers = PROTOCOL_VERSION;
			basic.writeBytesBufferToValue(startPtr+2, &vers);
			if(vers != PROTOCOL_VERSION) {
				printf("reco protocol undef\n");
			}
            check = Read(this->dataProtocol->getCommandSize());
			if(check <= 0) {
				continue;
			}
            offset = startPtr + this->dataProtocol->getHeadSize(PROTOCOL_VERSION);
            cmd = this->dataProtocol->parseCommand(startPtr+sizeof(int));
            offset = offset + this->dataProtocol->getCommandSize();

            check = Read(this->dataProtocol->getDataLengthSize());
            if(check < 0) continue;
            dataLength = this->dataProtocol->parseDataLength(offset, PROTOCOL_VERSION);
            offset = offset + this->dataProtocol->getDataLengthSize();

            check = Read(dataLength + sizeof(uint32_t));
            if(check < 0) continue;

            char *dataPoint = nullptr;
            this->dataProtocol->parseData(startPtr, &dataPoint, dataLength, PROTOCOL_VERSION, cmd);
            if(dataPoint == nullptr)
                continue;
            // send data to parser
            UARTMail_t *ReCoMail = RemoteControllerMailBox->try_alloc_for(2ms);
            if(ReCoMail == nullptr)
                continue;
            ReCoMail->command = cmd;
            ReCoMail->dataLength = dataLength;
            std::copy(offset, offset + dataLength, ReCoMail->data);
            RemoteControllerMailBox->put(ReCoMail);
        }
		ThisThread::sleep_for(20ms);
    }
}