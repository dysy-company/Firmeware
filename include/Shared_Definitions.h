#ifndef SHARED_DEFINITIONS_H
#define SHARED_DEFINITIONS_H
/*
    This file content shared definitions
*/

/*  
    System definitions
*/

#include <mbed.h>
#include <EthernetInterface.h>
#include "Boards/BoardDefine.h"

#include "..//lib/CommandMap/CmdMap.h"
CommandMap cmdMap;

#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN
    #include "..//lib/CommandMap/Map_SM.h"
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED ||CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
    #include "Map_SH.h"
#endif
/*
    Shared params and definitions
*/
#include "..//lib/BasicElements/BasicElements.h"
#include "Shared_Params.h"
#include "Global_Variables.h"
#include "BackupVariables.h"

/*
    Internal Hardware definitions
*/
#include "..//lib/Direction/Direction.h"
#include "..//lib/InternalFlash/InternalFlash.h"
#include "..//lib/InternalFlashDMA/InternalFlashDMA.h"

/*
    External Hardware definitions
*/
#include "..//lib/MCP492x/MCP492x.h"
#include "..//lib/MCP492xPWR/MCP492xPWR.h"
#include "..//lib/AD56x1/AD56x1.h"
#include "..//lib/RSSI/RSSI.h"
#include "..//lib/TI ADS8320/ADS8320.h"
#include "..//lib/TI ADS8320 Extens/ADS8320Extens.h"
//#include "MCP3201.h"

#include "..//lib/TEDs/TEDs.h"
#include "..//lib/MotorDriver/MotorDriver.h"
#include "..//lib/Encoder/Encoder.h"
#include "..//lib/ADS869xExt/ADS869xExt.h"
#include "..//lib/Encoder extensia/Encoder_Extensia.h"
#include "..//lib/ADS869xStr/ADS869xStr.h"
#if (PROJECT_NAME == PROJECT_NAME_MPD)
#include "..//lib/Encoder extensia 2/Encoder_Extensia_2.h"
#endif

/*
    Typedefs
*/
#include "Typedefs/Threads_Mail_Types.h"

/*
    Abstract classes definitions
*/
#include "..//lib/PID/PID.h"
#include "..//lib/Trigger/Trigger.h"
#include "..//lib/MaxMinCalc/MaxMinCalc.h"
#include "..//lib/GlobalVariablesInterface/GlobalVariablesInterface.h"
#include "..//lib/Filter/Filter.h"
#include "..//lib/SpeedCalibration/SpeedCalibration.h"
#include "..//lib/FilteredDataSwitcher/FilteredDataSwitcher.h"
/*
    Threads definitions
*/
#include "Tasks.h"
#include "../src/Threads/ExecutionT.h"
#include "../src/Threads/EthProtoT.h"
#include "../src/Threads/EthParserT.h"
#include "../src/Threads/RefVoltT.h"
#include "../src/Threads/AmplTuneT.h"
#include "../src/Threads/OneWireT.h"
#include "../src/Threads/RemoteControllerProtoT.h"
#include "../src/Threads/ReCoParserT.h"

/*
    Modes definitions
*/
//#include "PulseMode.h"

/*
    Ethernet protocol and so on
*/
#include "Ethernet/Ethernet_Config.h"
#include "Enums/Commands.h"
//#include "EthrntProto.h"
#include "../lib/EthParser/EthParser.h"
#include "../lib/DataChannel/DataChannel.h"

#include <list>

backupVariables_t BV;

MotorDriver motorDriver(0);

InternalFlash internalFlash;

#if BOARD_INDEX == 2
DMA_HandleTypeDef SPI5_DMA_IRQ_HANDLER;
SPI_HandleTypeDef SPI5_IRQ_HANDLER;
#endif
#if BOARD_INDEX == 3
// DMA_HandleTypeDef SPI5_DMA_IRQ_HANDLER;
// SPI_HandleTypeDef SPI5_IRQ_HANDLER;
#endif
//Shared classes    
BasicElements basic;

//Ethernet classes
EthernetInterface net;
////char rbuffer[ETHERNET_VALUES_BUFFERS_SIZE*20 + 4*ETHERNET_PACKET_HEAD_SIZE_VERSION_FIRST];
////char sbuffer[ETHERNET_VALUES_BUFFERS_SIZE*20 + 4*ETHERNET_PACKET_HEAD_SIZE_VERSION_FIRST];

//std::list<DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE>> dataChannels;

// std::list<DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE>> ethFloatChannels;
// std::list<DataChannel<double, ETHERNET_VALUES_BUFFERS_SIZE>> ethDoubleChannels;
// std::list<DataChannel<uint64_t, ETHERNET_VALUES_BUFFERS_SIZE>> ethUint64Channels;
// std::list<DataChannel<uint32_t, ETHERNET_VALUES_BUFFERS_SIZE>> ethUint32Channels;

std::list<AnyDataChannel*> dataChannels;

DataChannel<uint64_t, VALUES_BUFFERS_SIZE> TimeBuffer(CHANNEL_TYPE_TIME);
DataChannel<float, VALUES_BUFFERS_SIZE> RSSIValuesBuffer(CHANNEL_TYPE_POSITION);
DataChannel<float, VALUES_BUFFERS_SIZE> StrainBuffer(CHANNEL_TYPE_STRAIN);
DataChannel<float, VALUES_BUFFERS_SIZE> ExtensBuffer1(CHANNEL_TYPE_DEFORMATION);
DataChannel<uint64_t, VALUES_BUFFERS_SIZE> CyclesBuffer(CHANNEL_TYPE_CYCLE);
DataChannel<float, DIAGNOSTICS_BUFFERS_SIZE> DiagnosticsBuffer(CHANNEL_TYPE_DIAGNOSTICS);
DataChannel<int32_t, VALVE_BUFFERS_SIZE> ValveBuffer(CHANNEL_TYPE_VALVE);

DataChannel<uint32_t, VALUES_BUFFERS_SIZE> StepIDBuffer(CHANNEL_TYPE_STEP_ID);
DataChannel<uint32_t, VALUES_BUFFERS_SIZE> ModeBuffer(CHANNEL_TYPE_CURRENT_MODE);

std::list<AnyDataChannel *> reCoDataChannels;

DataChannel<uint64_t, REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> reCoTimeBuffer(CHANNEL_TYPE_TIME);
DataChannel<float, REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> reCoRSSIValuesBuffer(CHANNEL_TYPE_POSITION);
DataChannel<float, REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> reCoStrainBuffer(CHANNEL_TYPE_STRAIN);
DataChannel<float, REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> reCoExtensBuffer(CHANNEL_TYPE_DEFORMATION);
DataChannel<uint64_t, REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> reCoCyclesBuffer(CHANNEL_TYPE_CYCLE);
DataChannel<float, 1> reCoDiagnosticsBuffer(CHANNEL_TYPE_DIAGNOSTICS);

// CircularBuffer<float, VALUES_BUFFERS_SIZE> ExtensBuffer2;
// CircularBuffer<float, VALUES_BUFFERS_SIZE> ExtensBuffer3;
//CircularBuffer<float, VALUES_BUFFERS_SIZE> TMPulsePID;
//CircularBuffer<float, VALUES_BUFFERS_SIZE> TMCOSPID;
//CircularBuffer<float, VALUES_BUFFERS_SIZE> TMZeroPID;
//CircularBuffer<SensorTM_t, ADC_TM_BUFFERS_SIZE> ADCTMBuffer;
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
CircularBuffer<bool, DEFAULT_ENCODER_BUFFER_SIZE> EncoderBuffer;
#endif
//movement emcoder
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
InterruptIn EncoderA(DI_FB_RC_0);
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
InterruptIn EncoderA(IP_MK6);
#endif
#endif
//movement buttons
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
DigitalIn moveEnable(IP_MK6, PullUp);
#endif
#if ((REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP))
    InterruptIn moveUp(IP_MK5, PullUp);
    InterruptIn moveDown(IP_MK7, PullUp);
#endif

#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)
InterruptIn moveUpFast(IP_MK8, PullUp);
#if (LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_5V || LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_UNDEFINED)
InterruptIn moveDownFast(IP_MK2, PullUp);
InterruptIn StartButton(IP_MK1, PullUp);
#else
InterruptIn moveDownFast(IP_MK10, PullUp);
InterruptIn StartButton(IP_MK9, PullUp);
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
InterruptIn StopButton(IP_MK6, PullUp);
#endif
EventFlags emergencyFlag;
EventFlags startTestProcessFlag;
#endif

//DigitalOut moveEnable(DO_RC_2);
#if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE)
    #if (LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_5V || LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_UNDEFINED)
    InterruptIn switch1(IP_MK9);
    #else
    InterruptIn switch1(IP_MK1);
    #endif
#endif
#if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO)
    #if (LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_5V || LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_UNDEFINED)
    InterruptIn switch1(IP_MK9);
    InterruptIn switch2(IP_MK10);
    #else
    InterruptIn switch1(IP_MK1);
    InterruptIn switch2(IP_MK2);
    #endif
#endif
#if (EMERGENCY_STOP_TYPE == EMERGENCY_STOP_TYPE_BUTTON)
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
    InterruptIn emergencyStopButton(DI_RC_5, PullUp);
    #endif
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    InterruptIn emergencyStopButton(IP_MK3, PullUp);
    #endif
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
    InterruptIn emergencyStopButton(IP_MK10, PullUp);
    #endif
#endif

#if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
InterruptIn leftDoorSwitch(IP_MK1);
InterruptIn rightDoorSwitch(IP_MK2);
#endif

#if (PROJECT_NAME == PROJECT_NAME_MPD)
DigitalOut alarmLight(COM5, 0);
#endif

DigitalOut led2(LED2, 0);
DigitalOut led3(LED3, 0);

// LEDs
DigitalOut greenLED(DO_LED_GREEN, 1);
DigitalOut yellowLED(DO_LED_YELLOW, 0);
DigitalOut redLED(DO_LED_RED, 0); 

//BufferedSerial pc(PD_1, PD_0, 9600);
BufferedSerial debug_pc(TARGET_TX_PIN, TARGET_RX_PIN, 9600);
//Mutex ADCMutex;

Timer SystemTimer;

//External hardware definitions
//create SPI class and set configuration inside constructor
//SPI spiDAC(
//    DO_DAC_MCP4921_SerValve_MOSI, 
//    NC, 
//    DO_DAC_MCP4921_SerValve_SCK, 
//    DO_DAC_MCP4921_SerValve_CS);
InternalFlashDMA internalFlashDMA;
#if BOARD_INDEX == 2
//create DAC class and set spi inside constructor
MCP492x DACext (GV.DACSpiMode, SERVO_DAC_BAUD_RATE_PRESCALER);
#if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
ADS8320 ADCext (STRAIN_SENSOR_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t)); //128 pairs of double
#else
ADS869xStr ADS869xStrain (EXTENS_SENSOR1_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
#endif

ADS8320_Extens ADCextExtens (EXTENS_SENSOR_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
ADS869xExt ADS869xExtens (EXTENS_SENSOR1_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
//ADS869xExt_LVDT ADS869xExt2 (EXTENS_SENSOR_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
TEDs TEDsAcq;
//create RSSI reader class and config it inside constructor
#if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)||(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN))
RSSI RSSIReader(
    RSSI_BAUD_RATE_PRESCALER, 
    RSSI_NUMBER_OF_BITS,
    FLASH_AREA_SIZE / sizeof(point_t),
    DO_RSSI_DisplSensor_SCK,
    DI_RSSI_DisplSensor_DATA);
#else
RSSI RSSIReader(
    RSSI_BAUD_RATE_PRESCALER, 
    RSSI_NUMBER_OF_BITS,
    FLASH_AREA_SIZE / sizeof(point_t),
    PF_7,
    PF_8);
#endif

//create Reference Voltage Adjuster
// AD56x1 DACAD5621 (
//     REFERENCE_VOLTAGE_ADJUSTER_BAUD_RATE_PRESCALER, 
//     REFERENCE_VOLTAGE_ADJUSTER_TYPE, 
//     REFERENCE_VOLTAGE_ADJUSTER_OPERATION_TYPE, 
//     REFERENCE_VOLTAGE_ADJUSTER_POWER_SUPPLY,
//     (bool)false,
//     &SPI5_DMA_IRQ_HANDLER,
//     &SPI5_IRQ_HANDLER 
// );
// MCP492x_PWR DACExtensPwr(REFERENCE_VOLTAGE_ADJUSTER_EXTENS_BAUD_RATE_PRESCALER,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_OUT_MODE,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_IN_BUF_CTRL,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_GAIN,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_OUT_PWR_DOWN_CTRL,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_POWER_SUPPLY,
//     &SPI5_DMA_IRQ_HANDLER,
//     &SPI5_IRQ_HANDLER    
// );
#endif
#if BOARD_INDEX == 3
//create DAC class and set spi inside constructor
MCP492x DACext (GV.DACSpiMode, SERVO_DAC_BAUD_RATE_PRESCALER);
ADS8320 ADCext (STRAIN_SENSOR_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t)); //128 pairs of double
ADS8320_Extens ADCextExtens (EXTENS_SENSOR_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
ADS869xExt ADS869xExtens (EXTENS_SENSOR1_BAUD_RATE_PRESACALER, FLASH_AREA_SIZE / sizeof(point_t));
// TEDs TEDsAcq;
//create RSSI reader class and config it inside constructor
RSSI RSSIReader(
    RSSI_BAUD_RATE_PRESCALER, 
    RSSI_NUMBER_OF_BITS,
    FLASH_AREA_SIZE / sizeof(point_t),
    PF_7,
    PF_8);
//create Reference Voltage Adjuster
// AD56x1 DACAD5621 (
//     REFERENCE_VOLTAGE_ADJUSTER_BAUD_RATE_PRESCALER, 
//     REFERENCE_VOLTAGE_ADJUSTER_TYPE, 
//     REFERENCE_VOLTAGE_ADJUSTER_OPERATION_TYPE, 
//     REFERENCE_VOLTAGE_ADJUSTER_POWER_SUPPLY,
//     (bool)false,
//     &SPI5_DMA_IRQ_HANDLER,
//     &SPI5_IRQ_HANDLER 
// );
// MCP492x_PWR DACExtensPwr(REFERENCE_VOLTAGE_ADJUSTER_EXTENS_BAUD_RATE_PRESCALER,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_OUT_MODE,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_IN_BUF_CTRL,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_GAIN,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_OUT_PWR_DOWN_CTRL,
//     REFERENCE_VOLTAGE_ADJUSTER_EXTENS_POWER_SUPPLY,
//     &SPI5_DMA_IRQ_HANDLER,
//     &SPI5_IRQ_HANDLER    
// );
#endif
//MCP3201 ADCMCP3201 (
//    MCP3201_BAUD_RATE_PRESCALER,
//    MCP3201_REF_VOLTAGE
//);

//initialize direction pins
DigitalOut directHigh (DO_Direct_H, 1);
DigitalOut reverseHigh (DO_Reverse_H, 0);
DigitalOut debugPin (DO_Debug, 0);
//Pulse displacement sensor
//DigitalOut  startPulseDispl(DO_StartPulse, 0);
//DigitalIn   stopPulseDispl(DI_StopPulse, PullUp);
//Hardware commads out
DigitalOut  HwCmd0(DO_RC_0, 0); //PU
DigitalOut  HwCmd1(DO_RC_1, 0); //DIR
DigitalOut  HwCmd2(DO_RC_2_MOTOR_STEP_CW, 0); //MF
DigitalOut  HwCmd3(DO_RC_3_MOTOR_DIR_CCW, 0);
DigitalOut  HwCmd4(DO_RC_4_WARNING_LIGHT, 0);
DigitalOut  HwCmd5(DO_RC_5_MOTOR_ENABLE, 0);
DigitalOut  HwCmd6(DO_RC_6_ALARM_LIGHT, 0);
//DigitalOut  HwCmd7Up(DO_RC_7, 0);
// DigitalOut  HwCmd7Down(DO_RC_8, 0);
#if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN))
DigitalOut  HwCmd8Up(DO_RC_9, 0);
DigitalOut  HwCmd8Down(DO_RC_10, 0);
#endif
#if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN ))
//Hardware commands feedback
DigitalIn   HwCmdFb0(DI_RC_9, OpenDrain);
#endif
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
//channel B
DigitalIn   HwCmdFb1(DI_FB_RC_1, OpenDrain);
//permission
DigitalIn   HwCmdFb2(DI_FB_RC_2, OpenDrain);
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
//channel B
DigitalIn   HwCmdFb1(IP_MK8, OpenDrain);
//permission
DigitalIn   HwCmdFb2(IP_MK9, OpenDrain);
#endif
#endif
#if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN ))
#if (!(REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER))
DigitalIn   HwCmdFb1(DI_RC_10, OpenDrain);
#endif
// DigitalIn   HwCmdFb2(DI_RC_2_UP_END_SWITCH, OpenDrain);
// DigitalIn   HwCmdFb3(DI_RC_3_DOWN_END_SWITCH, OpenDrain);
// DigitalIn   HwCmdFb4(DI_RC_4_EMERGENCY_STOP, OpenDrain);
#if (!(REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER))
DigitalIn   HwCmdFb5(DI_RC_5, OpenDrain);
#endif
DigitalIn   HwCmdFb6(DI_RC_6, OpenDrain);
// DigitalIn   HwCmdFb7(DI_RC_7, OpenDrain);
// DigitalIn   HwCmdFb8(DI_RC_8, OpenDrain);
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
#if (!(REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER))
DigitalIn   HwCmdFb1(IP_MK4, OpenDrain);
#endif
DigitalIn   HwCmdFb5(IP_MK4, OpenDrain);
DigitalIn   HwCmdFb6(IP_MK4, OpenDrain);
#endif
//Power
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
 DigitalOut  coilPower(DO_CoilPower, 1);
 DigitalOut  dispSenPower(DO_SSIPower, 1);
#endif
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN
 DigitalOut  coilPower(DO_CoilPower, 1);
#endif
//Relays
DigitalOut  strainAmp(DO_SwitchStrainAmp, 0);//default 0: 100kN
// DigitalOut  strainSenPins(DO_SwitchStrainNumbPins, 0);//default 0: 6wire

#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
DigitalOut SON(ENB); //1
DigitalOut CLR(COM1); //0
DigitalOut CWL(COM2); //1
DigitalOut CCWL(COM3); //1
#endif

//CSs
//DigitalOut  SSICurrentCS(DO_ADC_MCP3201_SSICurrent_CS, 1);
//DigitalOut  StrainSenseCurrentCS(DO_ADC_MCP3201_StrainSenseCurrent_CS, 1);
//DigitalOut  CoilCurrentCS(DO_ADC_MCP3201_CoilCurrent_CS, 1);
//DigitalOut  StrainSenseVoltageCS(DO_ADC_MCP3201_StrainSenseVoltage_CS, 1);

//create displacement encoder class
Encoder displEncoder;
Encoder_Extensia deformEncoder;
#if (PROJECT_NAME == PROJECT_NAME_MPD)
Encoder_Extensia_2 deformEncoder2;
#endif
globalVariables_t GV;
GlobalVariablesInterface GVI(&GV, &internalFlash, &internalFlashDMA);

SpeedCalibration speedCalibration(10);
SpeedCalibration strainSpeedCalibration(10);

/* Direction DO Mail Box */
//Mail<DirectionDOMail_t, 16> DirectionMailBox;
/* Ethernet CMD Mail Box */
Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE> EthernetMailBox;
/* Ethernet answer Mail Box */
Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE> EthernetAnswerMailBox;
/* Task Manager Mail Box */
Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE> TaskManagerMailBox;
/* RemoteController CMD Mail Box */
Mail<UARTMail_t, DEFAULT_MAIL_SIZE> RemoteControllerMailBox;
/* RemoteController answer Mail Box */
Mail<UARTMail_t, DEFAULT_MAIL_SIZE> RemoteControllerAnswerMailBox;
//Protect init
Protect strainProtect;
Protect strainProtectStage2;
Protect strainEdgeProtect;
Protect strainButtonProtect;
Protect displacementProtect;
Protect displacementProtectStage2;
Protect displacementEdgeProtect;
Protect deformationProtect;
Protect deformationProtectStage2;
Protect deformationEdgeProtect;
//Maxs&Mins Calculations
MaxMinCalc displMaxMinCalc(0);
MaxMinCalc strainMaxMinCalc(0);
MaxMinCalc deformationMaxMinCalc(0);

Timeout delayedAction;
Timeout resetEmergencyButtonTimeout;
Timeout delayedSetConstDisplSpeed;

extern void DAC_MCP4921_Thread (void);
extern void Ethernet_protocol_Thread (void);
//extern void direction_DO_Thread (void);
//extern void Ethernet_Parser_Thread (void);
//extern void Ethernet_Debug_Thread (void);
extern void Reference_Voltage_Adjuster (float *setVoltage);
extern void Reference_Voltage_Adjuster_Extens (float *setVoltage);
extern void Reference_Voltage_Adjuster_Displacement (float *setVoltage);
extern void ADCs_Acquisition_Thread (void);
//extern void Amplitude_Tune_Thread (void);
extern void OneWireAcquisition_Thread (void);
//extern void Writing_To_Flash_Thread(FlashWorkThread *flashWorkThreadObj, char *buf, int address_offset_in_bytes, bool is_rewrite_enabled);
extern void CmdMap_Thread(void);

#ifdef __cplusplus
 extern "C" {
#endif
void NMI_Handler(void);
void DebugMon_Handler(void);
#if BOARD_INDEX == 2
// void DMA2_Stream0_IRQHandler(void);
// void SPI5_IRQHandler(void);
#endif
#if BOARD_INDEX == 3
// void DMA2_Stream0_IRQHandler(void);
// void SPI5_IRQHandler(void);
#endif
void WWDG_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif

// functions in main_inits.cpp
int readGV(globalVariables_t &GV);
int initProtects(const globalVariables_t &GV);
