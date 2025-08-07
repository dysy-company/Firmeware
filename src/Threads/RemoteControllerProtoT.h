#ifndef REMOTECONTROLLERPROTOT_H
#define REMOTECONTROLLERPROTOT_H

#include <mbed.h>
#include "BasicElements.h"
#include "DataExchangeProtocol.h"
#include "Trigger.h"
#include "Global_Variables.h"
#include "Typedefs/Threads_Mail_Types.h"

#define RE_CO_VALUES_BUFFERS_SIZE 512

class RemoteControllerProtocolThread
{
public:
    RemoteControllerProtocolThread(PinName _rx,
                                   PinName _tx,
                                   int _baudRate,
                                   globalVariables_t *_GV,
                                   std::list<AnyDataChannel *> *_channelBuffers,
                                   Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *REMOTECONTROLLERMailBox,
                                   Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *REMOTECONTROLLERAnswerMailBox,
                                   Mail<TaskManagerMail_t, DEFAULT_MAIL_SIZE> *TASKManagerMailBox);
    ~RemoteControllerProtocolThread();

    void threadExecute();

private:
	int Read(unsigned int len);
	void getHandshake();

	int findStartWord();
    BasicElements basic;

    // recive data buffer
    char rbuffer[RE_CO_VALUES_BUFFERS_SIZE + DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST];
    short rDataLen = 0;

    // send data buffer
    char sbuffer[RE_CO_VALUES_BUFFERS_SIZE + DATA_EXCHANGE_PACKET_HEAD_SIZE_VERSION_FIRST];
    short sDataLen = 0;

    Trigger *offlineTrigger;
    Timer boardStatusTimer;
	Timer syncTMTimer;
    PinName rxPin;
    PinName txPin;
    int baudRate;

    DataExchangeProtocol *dataProtocol;

    BufferedSerial *UART;

    globalVariables_t *GV;

    std::list<AnyDataChannel *> *channelBuffers;
    Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *RemoteControllerMailBox;
    Mail<UARTMail_t, DEFAULT_MAIL_SIZE> *RemoteControllerAnswerMailBox;
    Mail<TaskManagerMail_t, DEFAULT_MAIL_SIZE> *TaskManagerMailBox;

    const std::chrono::milliseconds boardStatusTMPeriod = 200ms;

    template<uint32_t BufferSize>
    inline void     resetAllChannels    ();
};

#endif // REMOTECONTROLLERPROTOT_H