/*
	UART_protocol.cpp - Library for getting Commands and Data through UART with package support (including CRC8).
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
 
 #include <UART_protocol.h>
 
 UART_protocol::UART_protocol(BufferedSerial &serial, long baudrate){
  serial.set_baud(9600);
  timeoutTimer.start();
}
 
/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт (127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/

const unsigned char Crc8Table[256] = {
    0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97,
    0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
    0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4,
    0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
    0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11,
    0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
    0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52,
    0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
    0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA,
    0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
    0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9,
    0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
    0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C,
    0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
    0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F,
    0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
    0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED,
    0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
    0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE,
    0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
    0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B,
    0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
    0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28,
    0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
    0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0,
    0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
    0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93,
    0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
    0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56,
    0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
    0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15,
    0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC
};

void UART_protocol::exit(BufferedSerial &serial){
}

unsigned char UART_protocol::Crc8(unsigned char *pcBlock, unsigned char len)
{
    unsigned char crc = 0xFF;

    while (len--)
        crc = Crc8Table[crc ^ *pcBlock++];

    return crc;
}

unsigned char UART_protocol::getDataLength(unsigned char &_packetLength){
	return _packetLength - 5;
}

void UART_protocol::resetPacketState(bool &packetReady){
 packetReady = false;
 packetState = 0;
 packetPointer = 0;
}

void UART_protocol::read_UART(BufferedSerial &serial, unsigned char *packet, bool &packetReady, char &packetLength, uint16_t &packetCommand, char *packetData){
    switch (packetState){
    //0   - initial state/ wait start packet/ packed parsed
    case 0:
      stateFirst = true;
      if (serial.readable()){
        serial.read(buf,1);
        char startByte = buf[0];
        if(startByte == 0xA5){
          //start byte received
          //WSerial.write(startByte);
          packet[0] = 0xA5;
          packetState = 8;
        }
      }
      else{
        //waiting start byte
        resetPacketState(packetReady);
      }
    break;
    //8   - wait length byte, start byte received
    case 8:
      if (serial.readable()){
        stateFirst = true;
        serial.read(buf,1);
        char pLength = buf[0];
        if (pLength >= 3){
          //length byte received
          packetLength = pLength;
          packet[1] = packetLength;
          packetPointer = 2;
          //BufferedSerial.write(packetLength);
          if (packetLength >= 5){
            packetState = 16;   
          }
          else{
            packetState = 64;
          }
        }
        else{
          //length byte is wrong, going to wait start byte
          resetPacketState(packetReady);
        }
      }
      else{
        //wait length byte
        if (stateFirst){
          startTimer = timeoutTimer.read_ms();
          packetState = 8;
          stateFirst = false;
        }
        else{
          if (timeoutTimer.read_ms() - startTimer < UART_PACKAGE_TIMEOUT){
            packetState = 8;
          }
          else{
            packetState = 0;
            resetPacketState(packetReady);
            stateFirst = true;
          }
        }   
      }
    break;
    //16  - wait command 2 bytes/ length byte received
    case 16:
      if (serial.readable()/* > 1 */){
        stateFirst = true;
        serial.read(buf,1);
        command[0] = buf[0];
        serial.read(buf,1);
        command[1] = buf[0];
        packet[packetPointer] = command[0];
        packetPointer++;
        packet[packetPointer] = command[1];
        packetPointer++;
        if (packetLength - 5 > 0){
          packetState = 32;
        }
        else{
          packetState = 64;
        }
      }
      else{
        //wait command
        if (stateFirst){
          startTimer = timeoutTimer.read_ms();
          packetState = 16;
          stateFirst = false;
        }
        else{
          if (timeoutTimer.read_ms() - startTimer < UART_PACKAGE_TIMEOUT){
            packetState = 16;
          }
          else{
            packetState = 0;
            resetPacketState(packetReady);
            stateFirst = true;
          }
        }
      }
    break;
    //32  - wait data bytes/ command bytes received
    case 32:
      if (serial.readable() /*>= packetLength - 5*/){
        stateFirst = true;
        for (char i = 0; i < packetLength - 5; i++){
          serial.read(buf,1);
          data[i] = buf[0];
          packet[packetPointer] = data[i];
          packetPointer++;
        }
        packetState = 64;
      }
      else{
        //wait data
        if (stateFirst){
          startTimer = timeoutTimer.read_ms();
          packetState = 32;
          stateFirst = false;
        }
        else{
          if (timeoutTimer.read_ms() - startTimer < UART_PACKAGE_TIMEOUT){
            packetState = 32;
          }
          else{
            packetState = 0;
            resetPacketState(packetReady);
            stateFirst = true;
          }
        }
      }
    break;
    //64  - wait CRC8 byte
    case 64:
      if (serial.readable()){
        stateFirst = true;
        serial.read(buf,1);
        int pCRC8 = buf[0];
        packet[packetPointer] = pCRC8;
        char calcCRC8 = Crc8(packet, packetLength - 1);
        //BufferedSerial.write(packet, packetLength);
        //BufferedSerial.write(calcCRC8);
        if (pCRC8 == calcCRC8){
          packetCRC8 = pCRC8;
          packetState = 128;
		  packetReady = true;
        }
        else{
          resetPacketState(packetReady);
        }
      }
      else{
        //wait CRC8
        if (stateFirst){
          startTimer = timeoutTimer.read_ms();
          packetState = 64;
          stateFirst = false;
        }
        else{
          if (timeoutTimer.read_ms() - startTimer < UART_PACKAGE_TIMEOUT){
            packetState = 64;
          }
          else{
            packetState = 0;
            resetPacketState(packetReady);
            stateFirst = true;
          }
        }
      }
    break;
    //128 - CRC8 received 
    case 128:
	  //packetState = 128;
    break;   
  }
  if (packetReady){
	packetCommand = command[0];
    packetCommand = packetCommand<<8;
    packetCommand |= command[1];
	for (int i = 0; i < 10; i++){
      packetData[i] = data[i];
    }
    //BufferedSerial.write(packet, packetLength);
    //resetPacketState(packetReady);
  }
}

void UART_protocol::answer_UART(BufferedSerial &serial, uint16_t &command, char *answerData, char &answerLength){
	unsigned char _packet[answerLength + 5];
	_packet[0] = 0xBD;
	_packet[1] = answerLength + 5;
	_packet[2] = command >> 8;
	_packet[3] = command;
	for (int i = 0; i < answerLength; i++){
		_packet[i+4] = answerData[i];
	}
	_packet[answerLength + 4] = Crc8(_packet, 4 + answerLength);
	//for (int i = 0; i < answerLength + 5; i++){
	//	serial.putc(_packet[i]);
	//}
  serial.write(_packet, answerLength + 5);
}
