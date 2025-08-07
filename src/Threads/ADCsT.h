/*
    MCP3201 ADCs acquisition thread
    Created 22-09-2021. By Grigorii Bragin.
*/
#ifndef ADCS_THREAD_H
#define ADCS_THREAD_H

#include <mbed.h>
#include "Global_Variables.h"
#include "Typedefs/Threads_Mail_Types.h"
#include "BasicElements.h"
#include "Shared_Params.h"
//#include "MCP3201.h"

extern globalVariables_t GV;
//extern MCP3201 ADCMCP3201;
extern DigitalOut  SSICurrentCS;
extern DigitalOut  StrainSenseCurrentCS;
extern DigitalOut  CoilCurrentCS;
extern DigitalOut  StrainSenseVoltageCS;
/* Ethernet answer Mail Box */
extern Mail<EthernetAnswerMail_t, 16> EthernetAnswerMailBox;
extern BasicElements basic;
extern CircularBuffer<SensorTM_t, ADC_TM_BUFFERS_SIZE> ADCTMBuffer;

enum    CurrentADC{
    SSICurrent,
    StrainSenseCurrent,
    CoilCurrent,
    StrainSenseVoltage
};

#endif