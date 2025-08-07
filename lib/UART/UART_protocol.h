/*
	UART_protocol.h - Library for getting Commands and Data through UART with package support (including CRC8).
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#ifndef UART_protocol_h
#define UART_protocol_h

#include <mbed.h>
//#include <BufferedSerial.h>
#define UART_PACKAGE_TIMEOUT 500 //ms  
class UART_protocol {
public:
	UART_protocol(BufferedSerial &serial, long baudrate);
	void exit(BufferedSerial &serial);
	void resetPacketState(bool &packetReady);
	void read_UART(BufferedSerial &serial, unsigned char *packet, bool &packetReady, char &packetLength, uint16_t &packetCommand, char *packetData);
	unsigned char getDataLength(unsigned char &_packetLength);
	void answer_UART(BufferedSerial &serial, uint16_t &command, char *answerData, char &answerLength);
	
private:
	BufferedSerial *serial;
	unsigned char Crc8(unsigned char *pcBlock, unsigned char len);
	Timer timeoutTimer;
	char packetCRC8;
	char packetPointer = 0;
	bool stateFirst = true;
	char command[2];
	char data[10];
	char buf[1];
	char packetState = 0;
	//0   - initial state/ wait start packet/ packed parsed
	//8   - wait length byte, start byte received
	//16  - wait command 2 bytes/ length byte received
	//32  - wait data bytes/ command bytes received
	//64  - wait CRC8 byte
	//128 - CRC8 received 

	unsigned long currentTimer = 0;
	unsigned long startTimer = 0;
};
#endif
