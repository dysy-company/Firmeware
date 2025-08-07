#ifndef ONE_WIRE_THREAD_H
#define ONE_WIRE_THREAD_H
#include <mbed.h>
#include "..//..//include/Global_Variables.h"
#include "..//..//include/Typedefs/Threads_Mail_Types.h"
#include "..//..//lib/TEDs/TEDs.h"
#include "..//..//include/Boards/Board.h"
#include "..//..//lib/BasicElements/BasicElements.h"
#include "..//..//include/Shared_Params.h"

extern globalVariables_t GV;
//extern Mail<DirectionDOMail_t, 16> DirectionMailBox;
/* Ethernet answer Mail Box */
extern Mail<EthernetAnswerMail_t, 16> EthernetAnswerMailBox;
extern TEDs TEDsAcq;
extern BasicElements basic;
//void Reference_Voltage_Adjuster (float *setVoltage);

#endif