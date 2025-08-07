/*
	PulseMode.h - Library for pulse mode of machine.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/


#ifndef EthParser_h
#define EthParser_h
#include <mbed.h>
#include "..//..//include//Global_Variables.h"
#include "..//..//include//BackupVariables.h"
#include "..//..//include//Typedefs/ParamsTypeDefs.h"
#include "..//BasicElements/BasicElements.h"
#include "..//..//include//Shared_Params.h"
#include "..//..//include//Ethernet/Ethernet_Config.h"
#include "..//..//include//Enums/Commands.h"
#include "..//Protect/Protect.h"
#include "..//..//include//TypeDefs/Threads_Mail_Types.h"
//#include "Threads_Mail_Config.h"
#include "..//..//include//Tasks.h"
#include "..//MaxMinCalc/MaxMinCalc.h"
#include "..//TI ADS8320/ADS8320.h"
#include "..//TI ADS8320 Extens/ADS8320Extens.h"
#include "..//Calibration/Calibration.h"
#include "..//Encoder/Encoder.h"
#include "..//GlobalVariablesInterface/GlobalVariablesInterface.h"
#include "..//..//include//Version.h"
#include "..//ADS869xExt/ADS869xExt.h"
#include "..//CommandMap/CmdMap.h"
#include "..//RSSI/RSSI.h"   
#include "..//InternalFlashDMA/InternalFlashDMA.h"
#include "..//..//src/Threads/ExecutionT.h"
#include "..//..//lib/SpeedCalibration/SpeedCalibration.h"
#include "..//ADS869xStr/ADS869xStr.h"
//#include "Threads_Mail_Config.h"
//#include <Shared_Definitions.h>

extern backupVariables_t BV;
extern CommandMap cmdMap;
extern Protect strainProtect;
extern Protect strainProtectStage2;
extern Protect strainEdgeProtect;
extern Protect displacementProtect;
extern Protect displacementProtectStage2;
extern Protect displacementEdgeProtect;
extern Protect deformationProtect;
extern Protect deformationProtectStage2;
extern Protect deformationEdgeProtect;
/* Task Manager Mail Box */
extern Mail<TaskManagerMail_t, 16> TaskManagerMailBox;

extern DigitalOut  strainAmp;

extern DigitalOut  HwCmd0;
extern DigitalOut  HwCmd1;
extern DigitalOut  HwCmd2;
extern DigitalOut  HwCmd3;
extern DigitalOut  HwCmd4;
extern DigitalOut  HwCmd5;
extern DigitalOut  HwCmd6;

#if (PROJECT_NAME == PROJECT_NAME_MPD)
extern DigitalOut alarmLight;
#endif

extern DigitalIn   HwCmdFb0;
extern DigitalIn   HwCmdFb1;
// extern DigitalIn   HwCmdFb2;
// extern DigitalIn   HwCmdFb3;
// extern DigitalIn   HwCmdFb4;
#if (!(REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER))
extern DigitalIn   HwCmdFb5;
#endif
extern DigitalIn   HwCmdFb6;

extern DigitalOut greenLED;
extern DigitalOut yellowLED;
extern DigitalOut redLED;

#if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
extern InterruptIn leftDoorSwitch;
extern InterruptIn rightDoorSwitch;
#endif

extern MaxMinCalc displMaxMinCalc;
extern MaxMinCalc strainMaxMinCalc;
extern MaxMinCalc deformationMaxMinCalc;
extern Timer SystemTimer;

extern Timeout resetEmergencyButtonTimeout;
#if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
extern ADS8320 ADCext;
#else
extern ADS869xStr ADS869xStrain;
#endif
extern ADS8320_Extens ADCextExtens;
extern ADS869xExt ADS869xExtens;
extern Encoder displEncoder;
extern RSSI RSSIReader;

/* Ethernet answer Mail Box */
extern Mail<EthernetAnswerMail_t, 16> EthernetAnswerMailBox;

extern InternalFlashDMA internalFlashDMA;

extern SpeedCalibration speedCalibration;
extern SpeedCalibration strainSpeedCalibration;

class EthernetParser {
public:

	EthernetParser(globalVariables_t *globalVariables, GlobalVariablesInterface *globalVariablesInterface, ExecutionThread* ExeThr);
	~EthernetParser();

    uint32_t parse(COMMAND &command, uint32_t &dataLength, char *data);
    void writeValueLikeCharBuffer(uint32_t limit, uint32_t dataLength, char *data);
    void readValueLikeCharBuffer(uint32_t& dataLength, char *data);
    
private:
    globalVariables_t *_globalVariables;
    GlobalVariablesInterface *_globalVariablesInterface;
    ExecutionThread* ExeThr;
    
    BasicElements basic;
    float floatValue = 0;
    double doubleValue = 0;
    long long longLongValue = 0;
    uint8_t uint8Value = 0;
    uint16_t uint16Value = 0;
    uint32_t uint32Value = 0;
    uint64_t uint64Value = 0;
    long int32Value = 0;
    long int32Value2 = 0;
    //uint32_t copyValueToArray(double value, char *data);
    //uint32_t copyValueToArray(uint32_t value, char *data);
    //uint32_t copyValueToArray(int32_t value, char *data);
    //uint32_t copyValueToArray(long long value, char *data);
    //uint32_t copyValueToArray(float value, char *data);
    int writeValue(char *data, uint32_t &dataLength, double &value);
    int writeValue(char *data, uint32_t &dataLength, uint32_t &value);
    int writeValue(char *data, uint32_t &dataLength, uint64_t &value);
    int writeValue(char *data, uint32_t &dataLength, uint8_t &value);
    int writeValue(char *data, uint32_t &dataLength, long &value);
    int writeValue(char *data, uint32_t &dataLength, long long &value);
    int writeValue(char *data, uint32_t &dataLength, int &value);
    int writeValue(char *data, uint32_t &dataLength, char *value);
    int writeValue(char *data, uint32_t &dataLength, std::chrono::microseconds &value);
    //check next mode state to reset
    void checkResetMode(uint32_t nextMode);
    void addTask(Task &task, char *data, uint32_t &dataLength);
    void addTask(Task &task);
    void resetEmergencyButton(void);
	Timeout *positionToHoldTimeout;
	void stopPiston(void);
    void stopPistonAtStrain(void);
    void stopPistonAtDeformation(void);
};
#endif
