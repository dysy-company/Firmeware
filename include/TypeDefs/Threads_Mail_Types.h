
/*
    This file content Threads Mail definitions
*/


#ifndef Threads_Mail_Types_h
#define Threads_Mail_Types_h

#include <mbed.h>
#include "..//Enums//Commands.h"
#include "..//Tasks.h"

/* DAC Mail */
typedef struct {
  uint8_t state;
  double frequency;
  double voltage;
  uint32_t counter;
  //experimental fields
  double eTimeLength;
  double eTimeDelay;
  bool frequencySign;
  bool voltageSign;
  bool eTimeLengthSign;
  bool eTimeDelaySign;
} DACMail_t;

/* Direction DO Mail */
typedef struct {
  long direction;
  uint32_t counter;
} DirectionDOMail_t;

/* Ethernet CMD Mail */
typedef struct {
  COMMAND command;
  uint32_t dataLength;
  char data[1024];
} EthernetMail_t;

/* Ethernet answer Mail */
typedef struct {
  COMMAND command;
  uint32_t dataLength;
  char data[1024];
} EthernetAnswerMail_t;

/* Task Manager Mail */
typedef struct {
  Task task;
  char data[1024];
  uint32_t dataLength;
} TaskManagerMail_t;

typedef struct : public EthernetMail_t {
  // COMMAND command;
  // char data[1024];
  // unsigned int dataLength;
} UARTMail_t;

#endif