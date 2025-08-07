#ifndef EXECUTION_THREAD_H
#define EXECUTION_THREAD_H
#include <mbed.h>
//#include "Shared_Definitions.h"
#include "..//..//include/Global_Variables.h"
#include "..//..//include/BackupVariables.h"
#include "..//..//include/Shared_Params.h"
#include "..//..//lib/PID/PID.h"
#include "..//..//lib/MCP492x/MCP492x.h"
#include "..//..//lib/RSSI/RSSI.h"
#include "..//..//lib/TI ADS8320/ADS8320.h"
#include "..//..//lib/TI ADS8320 Extens/ADS8320Extens.h"
#include "..//..//lib/TEDs/TEDs.h"
#include "..//..//lib/MotorDriver/MotorDriver.h"
#include "..//..//lib/Encoder/Encoder.h"
#include "..//..//lib/Encoder extensia/Encoder_Extensia.h"
#if (PROJECT_NAME == PROJECT_NAME_MPD)
#include "..//lib/Encoder extensia 2/Encoder_Extensia_2.h"
#endif
#include "..//..//lib/Direction/Direction.h"
//#include "PulseMode.h"
#include "..//..//lib/Protect/Protect.h"
#include "..//..//lib/Trigger/Trigger.h"
#include "..//..//include/Typedefs/Threads_Mail_Types.h"
#include "..//..//lib/BasicElements/BasicElements.h"
#include "..//..//lib/MaxMinCalc/MaxMinCalc.h"
//#include "StaticTest.h"
#include "..//..//lib/GlobalVariablesInterface/GlobalVariablesInterface.h"
#include "..//..//lib/LimitSwitch/LimitSwitch.h"
#include "..//..//lib/ADS869xExt/ADS869xExt.h"
#include "..//..//lib/SampleBreakDetection/SBD.h"
#include "..//..//lib/DataChannel/DataChannel.h"
#include <list>
#include "..//..//include/Boards/Board.h"
#include "..//..//lib/Filter/Filter.h"
#include "..//..//include//Tasks.h"
#include "..//..//lib/SpeedCalibration/SpeedCalibration.h"
#include "..//..//lib/ADS869xStr/ADS869xStr.h"
#include "..//..//lib/FilteredDataSwitcher/FilteredDataSwitcher.h"
// #include "ADS869xExt_LVDT.h"
//Define external variables and class instances
extern globalVariables_t GV;
extern backupVariables_t BV;
extern GlobalVariablesInterface GVI;
extern MCP492x DACext;
#if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
extern ADS8320 ADCext;
#else
extern ADS869xStr ADS869xStrain;
#endif
extern ADS8320_Extens ADCextExtens;
extern ADS869xExt ADS869xExtens;
extern TEDs TEDsAcq;
extern RSSI RSSIReader;
extern SPI spiDAC;
extern std::list<AnyDataChannel*> dataChannels;
extern std::list<AnyDataChannel*> reCoDataChannels;
extern Mail<TaskManagerMail_t, 16> TaskManagerMailBox;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> RSSIValuesBuffer;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> StrainBuffer;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> ExtensBuffer1;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> TMPulsePID;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> TMCOSPID;
//extern DataChannel<float, ETHERNET_VALUES_BUFFERS_SIZE> TMZeroPID; 
extern DigitalOut directHigh;
extern DigitalOut reverseHigh;
extern DigitalOut debugPin;
extern DigitalOut HwCmd0;
extern DigitalOut HwCmd1;
extern DigitalOut HwCmd2;
extern DigitalOut HwCmd3;
extern DigitalOut HwCmd4;
extern DigitalOut HwCmd5;
extern DigitalOut HwCmd6;
extern Protect strainProtect;
extern Protect displacementProtect;
extern Protect deformationProtect;
extern Protect strainProtectStage2;
extern Protect displacementProtectStage2;
extern Protect deformationProtectStage2;
extern Protect strainEdgeProtect;
extern Protect displacementEdgeProtect;
extern Protect deformationEdgeProtect;
extern Protect strainButtonProtect;
extern MaxMinCalc displMaxMinCalc;
extern MaxMinCalc strainMaxMinCalc;
extern MaxMinCalc deformationMaxMinCalc;
/* Ethernet answer Mail Box */
extern Mail<EthernetAnswerMail_t, DEFAULT_MAIL_SIZE> EthernetAnswerMailBox;
extern Mail<UARTMail_t, DEFAULT_MAIL_SIZE> RemoteControllerAnswerMailBox;
extern BasicElements basic;
extern Timer SystemTimer;
extern Timeout delayedAction;

const uint32_t WATCHDOG_TIMEOUT_MS = DEFAULT_WATCHDOG_TIMEOUT;

extern CircularBuffer<bool,DEFAULT_ENCODER_BUFFER_SIZE> EncoderBuffer;
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
//channel b of encoder
extern DigitalIn   HwCmdFb1;
//permission of encoder work
extern DigitalIn   HwCmdFb2;
#endif
//chsnnel a of encoder
// extern InterruptIn moveEnable;
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
extern DigitalIn moveEnable;
#endif
#if ((REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP))
extern InterruptIn moveUp;
extern InterruptIn moveDown;
#endif
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)
extern InterruptIn moveUpFast;
extern InterruptIn moveDownFast;
extern InterruptIn StartButton;
extern InterruptIn StopButton;
extern EventFlags emergencyFlag;
extern EventFlags startTestProcessFlag; 
#endif
#if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE)
extern InterruptIn switch1;
#endif
#if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO)
extern InterruptIn switch1;
extern InterruptIn switch2;
#endif
#if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
extern InterruptIn leftDoorSwitch;
extern InterruptIn rightDoorSwitch;
#endif
#if (EMERGENCY_STOP_TYPE == EMERGENCY_STOP_TYPE_BUTTON)
extern InterruptIn emergencyStopButton;
#endif
// extern InterruptIn Test1;
// extern InterruptIn Test2;
// extern InterruptIn Test3;
// extern InterruptIn Test4;
// extern InterruptIn Test5;
// extern InterruptIn Test6;
// extern InterruptIn Test7;
// extern InterruptIn Test8;
// extern InterruptIn Test9;
// extern InterruptIn Test10;
// extern DigitalOut TestOut1;
// extern DigitalOut TestOut2;
// extern DigitalOut TestOut3;
// extern DigitalOut TestOut4;
// extern DigitalOut TestOut5;
// extern DigitalOut TestOut6;
// extern DigitalOut TestOut7;
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
extern InterruptIn EncoderA;
#endif
extern DigitalOut led2;
extern DigitalOut led3;

extern DigitalOut greenLED;
extern DigitalOut yellowLED;
extern DigitalOut redLED; 

extern Timeout resetEmergencyButtonTimeout;
extern Timeout delayedSetConstDisplSpeed;

extern MotorDriver motorDriver;
extern Encoder displEncoder;
extern Encoder_Extensia deformEncoder;
#if (PROJECT_NAME == PROJECT_NAME_MPD)
extern Encoder_Extensia_2 deformEncoder2;
extern DigitalOut alarmLight;
#endif

extern SpeedCalibration speedCalibration;
extern SpeedCalibration strainSpeedCalibration;

class ExecutionThread{
    
    public:
        ExecutionThread();
        ~ExecutionThread();
        void Execution(void);
        void setConstDisplMode(void);
        void setConstDisplSpeed(void);
        int setTCycle(us_timestamp_t tcycle);
        void resetAmplitudeAttenuationCoefs(void);
        errorCode_t addFilterAtEnd(uint32_t filterType, uint32_t dataType, int rangeOfFilter);
        errorCode_t addFilterByIndex(uint32_t filterType, uint32_t dataType, int rangeOfFilter, int index);
        errorCode_t clearingOfFilterByParameters(uint32_t filterType, uint32_t dataType, uint32_t parametr, int index);
        errorCode_t orderingByParameter(uint32_t dataType);
        errorCode_t writeAddNullPointSinDispl(double dataType);
        errorCode_t setFilteringActivityCell(uint32_t dataType, uint32_t activ, uint32_t step);
        errorCode_t setFilteringActivityStepsDataRaw(uint32_t dataType, uint32_t step);
        errorCode_t setFilteringActivityAllCells(uint32_t step);
        void getFilterSetStatusByDataType(uint32_t dataType);
        void getActivityesSetStatusByDataType(uint32_t dataType);
        void filteringOn();
        void filteringOff();
        void calculateNextPoint(void);
        SwitchersSet* switcherFilterSet;
        void setAllLimitsNAN();
        bool isDisplacementCrossed();
        bool isStrainCrossed();
        bool isDeformationCrossed();

        
        FilterCollection* dataFiltersSet;
        void makeOrderToUnblockFiltering(bool isWorking);
        void setStatusOfFilteringSet(bool isInFilteringProcess);
        bool getStatusOfFilteringSet();
        bool getStatusOfUnblokFiltering();
        float displacement_DIRECTING = 0.0;
        float displacement_MONITORING = 0.0;
        float displacement_ANSWERING = 0.0;
        float displacement_DISPLAYING = 0.0;
        float strain_DIRECTING = 0.0;
        float strain_MONITORING = 0.0;
        float strain_ANSWERING = 0.0;
        float strain_DISPLAYING = 0.0;
        float deformation_DIRECTING = 0.0;
        float deformation_MONITORING = 0.0;
        float deformation_ANSWERING = 0.0;
        float deformation_DISPLAYING = 0.0;

        
    private:
        void modeExecute(void);
        void sendNotification(COMMAND cmd, uint32_t state);
        void sendNotification(COMMAND cmd, uint64_t state);
        void sendNotification(COMMAND cmd, float state);
        template<typename Key, typename... Args> void sendNotification(COMMAND cmd, Key key, Args... args);
        template<typename One> void makingDataFromParameters(EthernetAnswerMail_t* mailPtr, One one);
        template<typename First, typename... Other> void makingDataFromParameters(EthernetAnswerMail_t* mailPtr, First first, Other... other);
        void strainProtectStage1Execute(void);
        void strainProtectStage2Execute(void);
        void strainProtectEdgeExecute(void);
        void strainButtonProtectExecute(void);
        void displacementProtectStage1Execute(void);
        void displacementProtectStage2Execute(void);
        void displacementProtectEdgeExecute(void);
        void deformationProtectStage1Execute(void);
        void deformationProtectStage2Execute(void);
        void deformationProtectEdgeExecute(void);
        void internalTaskManager(void);
        void averageAndDecimate(void);
        void updateValues(void);
        void startAcq(void);
        void checkTimeAndWait(void);
        // void calculateNextPoint();
        void testSignal(void);
        
        uint64_t getCurrentCycle(void);
        
        void fallEdgeEncoder(void);
        void fallMoveUp(void);
        void fallMoveDown(void);
        void riseMoveUp(void);
        void riseMoveDown(void);
        void fallMoveUpFast(void);
        void fallMoveDownFast(void);
        //
        void fallStartButton(void);
        void fallStopButton(void);
        void resetEmergencyFlag(void);
        void startButtonFlag(void);
        void enableLED2(void);
        void enableLED3(void);
        void disableLED2(void);
        void disableLED3(void);
        void resetEmergencyButton(void);
        void setNoneMode(void);

        void readParamsFromFlash(void);
        
        void CheckLimSwState(void);
        void LimitSwitchRiseMode(void);
        void LimitSwitchFallMode(void);

        void checkLimSwLeftDoorRiseState(void);
        void checkLimSwLeftDoorFallState(void);
        void checkLimSwRightDoorRiseState(void);
        void checkLimSwRightDoorFallState(void);
        void limSwLeftDoorRiseMode(void);
        void limSwLeftDoorFallMode(void);
        void limSwRightDoorRiseMode(void);
        void limSwRightDoorFallMode(void);

        void CheckEmergencyStopState(void);
        void emergencyStop(void);
        
        void fallMoveUpState();
        void riseMoveDownState();
        void fallMoveDownState();
        void riseMoveUpState();
        void fallMoveUpFastState();
        void fallMoveDownFastState();
        void fallStartButtonState();
        void fallStopButtonState();

        void resetAngleTriggers();
        void angleTriggersStateCalc(double tmpSinus);
        float getPosition(uint32_t activity);
        float getStrain(uint32_t activity);
        float getDeformation(uint32_t activity);

        void SinusModesGenetateTargetPoints(SIN* sinusMode, MaxMinCalc* minMaxCalc, double nullPoint);
        void SinusModesAmplAndSinCalc(SIN* sinusMode, double& currentCalculatedAmplitude, double& sinusCaclulated, MaxMinCalc* minMaxCalc);
        void SinusModesCalcNextAngle(SIN* sinusMode, double tmpSinus, bool isSinBased);
        void SinusBasedModesGenetateTargetPoints(SIN* sinusMode, MaxMinCalc* minMaxCalc, double nullPoint, uint32_t modeType, double baseRatio);
        void CalculateDesirePointSINBasedModes(SIN* sinusMode, double nullPointMode, uint32_t modeType, double currentAmplitude, double baseRatio);
        void PrepareForAmplitudeTune(SIN* sinusMode);
        void StepByFreqyencyForSmoothStartStop(SIN* sinusMode, double targetFreq, double targetFreqStop, uint32_t& numberOfRemainderStepsRise, uint32_t& numberOfRemainderStepsFall);
        void CheckUpAndDownAmplitudeSet(SIN* sinusMode);
        void ConstModeNextDesirePointCalculating(CONST* constMode, double& dataToHold);
        
        Timeout fallMoveUpTimeout;
        Timeout fallMoveDownTimeout;
        Timeout riseMoveUpTimeout;
        Timeout riseMoveDownTimeout;
        Timeout fallMoveUpFastTimeout;
        Timeout fallMoveDownFastTimeout;
        Timeout fallStartButtonTimeout;
        Timeout fallStopButtonTimeout;

        Timeout emergencyTimeout;
        //
        Timeout LimSwTimeout;
        Timeout EmergencyStpTimeout;
        Timeout startButtonTimeout;

        Timeout limSwLeftDoorTimeout;
        Timeout limSwRightDoorTimeout;
        //PulseMode *pulseMode;
        Trigger *sinDispCyclesTrigger;
        Trigger *sinStrainCyclesTrigger;
        Trigger *sinDeformCyclesTrigger;
        Trigger *zeroCrossed;
        Trigger *piDivTwoCrossed;
        Trigger *piCrossed;
        Trigger *treePiDivTwoCrossed;
        #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
        Trigger *encoderPermissionButton;
        #endif
        Trigger *positiveStrainZeroCrossed;
        Trigger *negativeStrainZeroCrossed;
        //create PID for HOLD position
        PID *constDisplacementPID;
        //create PID for Sin mode
        PID *sinDisplacementPID;
        //create PID for HOLD strain
        PID *constStrainPID;
        //create PID for Sin Strain mode
        PID *sinStrainPID;
        //create PID for HOLD deformation
        PID *constDeformationPID;
        //create PID for Sin Deformation mode
        PID *sinDeformationPID;       
        Direction *direction;
        //StaticTest *staticTest;
        LimitSwitch *LimSw;
        LimitSwitch *LimSwDoors;
        //create SBD
        SampleBreakDetection *SBD_MS;
        SampleBreakDetection *SBD_DF;
        SBDStatus_t sampleStatus;
        
        //initialize current variables and set 
        float DACVoltage = 2.7;
        float DACRefVoltage = 10 / 3.5;
        float DACExtRefVoltage = 10 / 3.5;
        float prevDACVoltage = -100000;
        uint8_t DACState = DEFAULT_DAC_THREAD_STATE;
        uint8_t prevDACState = DAC_STATE_UNDEFINED;
        double DACFrequency = DEFAULT_DAC_THREAD_FREQUENCY;
        //float nullPosition = 0;
        float position = 0.0;
        float positionWoNO = 0.0;
        //float positionOffset = 0.0;
        //float ADCVoltage = 0;
        //uint16_t ADCCode = 0x0;
        float strain = 0.0;
        float strainWoNO = 0.0;
        float deformation = 0.0;
        float deformationWoNO = 0.0;
        double angle = 0;
        //uint16_t strain = 0;
        uint32_t dataDecimationCounter = 0;
        // uint32_t dataDecimationCounterStrain = 0;
        // uint32_t dataDecimationCounterDeformation = 0;
        //values for timing loop
        Timer frequencyTimer;
        std::chrono::microseconds  startTimerValue = 0us;
        std::chrono::microseconds  endTimerValue = 0us;
        //us_timestamp_t  startDebugTimerValue = 0;
        //us_timestamp_t  endDebugTimerValue = 0;
        double constDisplSpeedToSet = 5.0;
        double preUpAmplitude = 0.0;
        double preDownAmplitude = 0.0;
        double preModeFrequency = 0.0;

        //cyclic strain sample broke protection
        double sinCalculated = 0.0;
        double cosCalculated = 0.0;
        double currentAmplitude = 0.0;
        float positionToSend = 0.0;
        float strainToSend = 0.0;
        float deformationToSend = 0.0;

        int LimSwDirecton = 0;
        double correctionTest = 0;
        int stepsTest = 0;

        bool moveUpState = false;
        bool moveDownState = false;
        bool buttonMode = false;
        bool isPreModeConst = false;
        bool isUpHalfWaveFirst = false;
        bool isDownHalfWaveFirst = false;

        volatile bool filteringInProcess = true;
        bool rawFiltering = false;

        uint8_t averageNumber       = 10;
        uint8_t counterFirstHalfWave = 0;
        uint8_t counterSecondHalfWave = 0;

		        //Diagnostics data to send
        float PIDCorrectionToSend = 0.0;
        float valveVoltageToSend = 0.0;
        float motorStepToSend = 0.0;

        float DACVoltageTmp = 0.0;

        float sinTestSignalArgument = 0;
        float sinTestSignalArgumentsIncrease = 0.01;
        float const twoPi = 2 * M_PI; 
        int count = 0;
        std::chrono::microseconds spiTransactionTimeout = 10000us;

        int positionCounter = 0;
        uint32_t dir = 0;
        uint32_t stepsCountPerCycle = 50;
        uint32_t cycleDuration = 1;
        int newPosition;
        bool positionState = false;
        double percentage = 0;
        uint8_t counter = 0;
        double lastCorrection = 0;
};

#endif