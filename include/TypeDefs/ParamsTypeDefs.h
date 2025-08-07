#include <mbed.h>
#include "../Shared_Params.h"

#ifndef ParamsTypeDef_h
#define ParamsTypeDef_h

#define SIN_DISPLACEMENT_MODE_STATE_RESET               0
#define SIN_DISPLACEMENT_MODE_STATE_GENERATE            1
#define SIN_DISPLACEMENT_MODE_STATE_EXIT                2

#define CONST_DISPLACEMENT_MODE_STATE_RESET             0
#define CONST_DISPLACEMENT_MODE_STATE_HOLD              1
#define CONST_DISPLACEMENT_MODE_STATE_EXIT              2

#define CONST_STRAIN_MODE_STATE_RESET             0
#define CONST_STRAIN_MODE_STATE_HOLD              1
#define CONST_STRAIN_MODE_STATE_EXIT              2

#define SIN_STRAIN_MODE_STATE_RESET               0
#define SIN_STRAIN_MODE_STATE_GENERATE            1
#define SIN_STRAIN_MODE_STATE_EXIT                2

#define SIN_DEFORMATION_MODE_STATE_RESET                0
#define SIN_DEFORMATION_MODE_STATE_GENERATE             1
#define SIN_DEFORMATION_MODE_STATE_EXIT                 2

#define CONST_DEFORMATION_MODE_STATE_RESET              0
#define CONST_DEFORMATION_MODE_STATE_HOLD               1
#define CONST_DEFORMATION_MODE_STATE_EXIT               2

#define USER_DEFINED_DISPLACEMENT_MODE_STATE_RESET      0
#define USER_DEFINED_DISPLACEMENT_MODE_STATE_GENERATE   1
#define USER_DEFINED_DISPLACEMENT_MODE_STATE_EXIT       2

#define USER_DEFINED_STRAIN_MODE_STATE_RESET            0
#define USER_DEFINED_STRAIN_MODE_STATE_GENERATE         1
#define USER_DEFINED_STRAIN_MODE_STATE_EXIT             2

#define CLOSE_VALVE_STATE_RESET                         0
#define CLOSE_VALVE_STATE_HOLD                          1
#define CLOSE_VALVE_STATE_EXIT                          2

#define USER_DEFINED_TYPE_DISPLACEMENT                  0
#define USER_DEFINED_TYPE_STRAIN                        1

#define RAM_MEMORY_TYPE                                 0x00
#define FLASH_MEMORY_TYPE                               0x01
#define FLASH_MEMORY_QUEUE                              0x02
#define FLASH_MEMORY_SET                                0x03
#define FLASH_MEMORY_CHAR_ARRAY                         0x04

#define TEST_STATUS_TEST_IS_OFF                         0x00
#define TEST_STATUS_TEST_IN_PROCESS                     0x01

    typedef uint32_t machineType_t;
    //PID params struct
    typedef struct {
        double Kp;
        double Ki;
        double Kd;
    } PIDParams_t;

    typedef struct AmplitudeTuneInfo{
        double UpKP;
        double UpKI;
        double UpKD;
        double DownKP;
        double DownKI;
        double DownKD;
        double NullPointKP;
        double NullPointKI;
        double NullPointKD;
        uint32_t state;
        uint32_t correctionType;
        uint32_t freq;//msec
        uint32_t amplitudeRiseCycles;//cycles
        uint32_t amplitudeFallCycles;//cycles
        uint32_t waitCycles;
        double incrementMultiplier;
        double decrementMultiplier;
        double minUpAmplitude;
        double minDownAmplitude;
        uint32_t startProcess;
        uint32_t stopProcess;
        bool stop;
        uint32_t mainProcess;
        //us_timestamp_t stepTime;//usec
        //Timer incrementCounter;
    }   AmplitudeTuneInfo_t;

    //Constant mode params struct
    typedef struct constModeParams{
        double ConstFrequency;//ms   Add to flash
        double Voltage;//V
        //If ==0 keys are closed direct=0,reverse=0, if >0 direct=1,reverse=0, if <0 direct=0,reverse=1
        long Direction;
    }   constModeParams_t;
    
    // //Constant displacement mode params struct
    // typedef struct ConstDisplacementModeParams{
    //     double PositionToHold;//mm position, which level is support
    //     double ModeFrequency;//ms min = 0,1 ms
    //     double CurrentPosition;// mm
    //     PIDParams_t PIDParams; //PID regulator coeffs
    //     double PIDCorrection; //current PID correction
    //     double MaxDeviation; //mm max value of deviation for PID resset
    //     uint32_t State; // state of PID workflow
    //     double MaxVoltage;
    //     double MaxSteps;
    //     double Speed;// mm/sec
    //     double MaxSpeed;
    //     double delta; //minimum delta between values for speed
    //     double nextDesirePoint;
    //     uint32_t msCounter;
    //     double k;
    //     double b;
    //     bool speedEnable;
    //     bool waitForPIDReset;
    //     uint32_t t;
    // } ConstDisplacementModeParams_t;

    // //Constant strain mode params struct
    // typedef struct ConstStrainModeParams{
    //     double StrainToHold;//kN strain, which level is support
    //     double ModeFrequency;//ms min = 0,1 ms
    //     double CurrentStrain;// kN
    //     PIDParams_t PIDParams; //PID regulator coeffs
    //     double PIDCorrection; //current PID correction
    //     double MaxDeviation; //kN max value of deviation for PID resset
    //     double SampleLength; //mm length of current sample
    //     double SampleCut; //mm^2 cut of current sample
    //     double YoungModulus; //GPa modulus of Young
    //     uint32_t State; // state of PID workflow
    //     double MaxVoltage;
    //     double MaxSteps;
    //     double Speed;// kN/sec
    //     double MaxSpeed;
    //     double delta; //minimum delta between values for speed
    //     double nextDesirePoint;
    //     uint32_t msCounter;
    //     double k;
    //     double b;
    //     bool speedEnable;
    //     uint32_t t;
    // } ConstStrainModeParams_t;
    
    // //Constant deformation mode params struct
    // typedef struct ConstDeformationModeParams{
    //     double DeformationToHold;//mm position, which level is support
    //     double ModeFrequency;//ms min = 0,1 ms
    //     double CurrentDeformation;// mm
    //     PIDParams_t PIDParams; //PID regulator coeffs
    //     double PIDCorrection; //current PID correction
    //     double MaxDeviation; //mm max value of deviation for PID resset
    //     uint32_t State; // state of PID workflow
    //     double MaxVoltage;
    //     double MaxSteps;
    //     double Speed;// mm/sec
    //     double MaxSpeed;
    //     double delta; //minimum delta between values for speed
    //     double nextDesirePoint;
    //     uint32_t msCounter;
    //     double k;
    //     double b;
    //     bool speedEnable;
    //     uint32_t t;
    // } ConstDeformationModeParams_t;

    struct SIN{
        double UpAmplitude;//mm
        double DownAmplitude;//mm
        double UpAmplitudeSet;//mm
        double DownAmplitudeSet;//mm
        double SINFrequency;//Hz
        double ModeFrequency;//ms min = 0,1 ms
        PIDParams_t PIDParams;
        // double Tcycle;//ms min = 1 ms
        double AngleW;// angle in rad
        double CurrentPoint; // current Y value
        long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
        uint32_t State; // state of Sin generating
        long long InternalCounter; // count cycles of sinus
        double DesirePoint; // desire Y value
        double PIDCorrection; //current PID correction
        double MaxVoltage; //valve max voltage
        uint64_t MaxSteps; 
        double NullPointDisplacement; // null position at start of generating
        double NullPointStrain;       // 
        double NullPointDeformation;
        double MaxDeviation;
        double DesirePointBuffered;
        double InternalCounterBuffered;
        float DACVoltage; //current DAC Voltage in Volts
        bool currentAmplitudeDirection;// 0 - Up, 1 - Down
        bool currentAmplitudeDirectionBuffered;
        bool waitForPIDReset;
        double AngleWBuffered;
        AmplitudeTuneInfo_t amplitudeTuneInfo;
        //Timer Count; // Timer for discovering 1 count of Sin signal
    };

    struct CONST{
        double ModeFrequency;//ms min = 0,1 ms
        PIDParams_t PIDParams; //PID regulator coeffs
        double PIDCorrection; //current PID correction
        double MaxDeviation; //mm max value of deviation for PID resset
        uint32_t State; // state of PID workflow
        double MaxVoltage;
        uint64_t MaxSteps;
        double Speed;// mm/sec
        double MaxSpeed;
        double delta; //minimum delta between values for speed
        double nextDesirePoint;
        uint32_t msCounter;
        double k;
        double b;
        bool speedEnable;
        uint32_t t;
    };

    // //SIN displacement mode params struct
    // typedef struct SINDisplacementModeParams{
    //     double UpAmplitude;//mm
    //     double DownAmplitude;//mm
    //     double UpAmplitudeSet;//mm
    //     double DownAmplitudeSet;//mm
    //     double SINFrequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     uint32_t State; // state of Sin generating
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps; 
    //     double NullPointDisplacement; // null position at start of generating
    //     double NullPointStrain;       // 
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     double AngleWBuffered;
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SINDisplacementModeParams_t;

    // //SIN strain mode params struct
    // typedef struct SINStrainModeParams{
    //     double UpAmplitude;//kN
    //     double DownAmplitude;//kN
    //     double UpAmplitudeSet;//kN
    //     double DownAmplitudeSet;//kN
    //     double SINFrequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     uint32_t State; // state of Sin generating
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps;
    //     double NullPointDisplacement;
    //     double NullPointStrain; // null stain at start of generating
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double SampleLength; //mm length of current sample
    //     double SampleCut; //mm^2 cut of current sample
    //     double YoungModulus; //GPa modulus of Young
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     bool holdConstDisplAtEnd;
    //     double AngleWBuffered;
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SINStrainModeParams_t;

    // //SIN deformation mode params struct
    // typedef struct SINDeformationModeParams{
    //     double UpAmplitude;//mm
    //     double DownAmplitude;//mm
    //     double UpAmplitudeSet;//mm
    //     double DownAmplitudeSet;//mm
    //     double SINFrequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     uint32_t State; // state of Sin generating
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps; 
    //     double NullPointDisplacement; // null position at start of generating
    //     double NullPointStrain;       // 
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     bool holdConstDisplAtEnd;
    //     double AngleWBuffered;
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SINDeformationModeParams_t;

    //SIN Voltage mode params struct
    typedef struct SINVoltageModeParams{
        double MaxVoltage; //valve max voltage
    }   SINVoltageModeParams_t;

    //SIN load mode params struct
    typedef struct SINLoadModeParams{
        double Amplitude;//kN
        double SINFrequency;//Hz
        double ModeFrequency;//ms
        PIDParams_t PIDParams;
    }   SINLoadModeParams_t;

    typedef struct SensorsTM{
        float DisplSensorCurrent;
        float StrainSensorCurrent;
        float CoilCurrent;
        float StrainSensorVoltage;
    }   SensorTM_t;

    enum StrainUnits{
        STRAIN_UNITS_KN,
        STRAIN_UNITS_RAW,
        STRAIN_UNITS_DEFORMATION_RAW,
        STRAIN_UNITS_POSITION_RAW,
        STRAIN_UNITS_DEFORMATION_KN
    };

    //Data for testing during set up mashine 
    enum TestDataUnits{
        NA,
        CORRECTION_UNITS_RAW,
        VALVE_VOLTAGE_UNITS_V,
        MOTOR_STEPS_UNITS_RAW,
        SINUS_TEST_SIGNAL
    };
    
    enum ValveUnits{
        VALVE_UNITS_RAW,
        VALVE_UNITS_PERCENT
    };

    enum CyclicProtectionState{
        CYCLIC_PROTECTION_OFF,
        CYCLIC_PROTECTION_INIT,
        CYCLIC_PROTECTION_IN_PROCESS
    };

    enum DeformationUnits{
        DEFORMATION_UNITS_MM,
        DEFORMATION_UNITS_RAW,
        DEFORMATION_UNITS_STRAIN_RAW,
        DEFORMATION_UNITS_POSITION_RAW,
        DEFORMATION_UNITS_POSITION_MM
    };
    enum PositionUnits{
        POSITION_UNITS_MM,
        POSITION_UNITS_RAW,
        POSITION_UNITS_STRAIN_RAW,
        POSITION_UNITS_STRAIN_MM  
    };
    enum TypeOfClearing{
        FULL_CLEARING,
        LINE_CLEARING,
        INDIVIDUAL_CLEARING,
        BY_DATA_AND_FILTERTYPE_CLEARING,
        ALL_DATA_CLEARING_BY_FILTERTYPE
    };
    // enum StrainAmpCoef{
    //     STRAIN_AMP_COEF_70,
    //     STRAIN_AMP_COEF_700
    // };
    // enum DeformationAmpCoef{
    //     DEFORMATION_AMP_COEF_70,
    //     DEFORMATION_AMP_COEF_700
    // };
    typedef struct TMValue{
        float value;
        us_timestamp_t time;
    }   TMValue_t;
    typedef struct TimeMeasure{
        double startMeasurePosition;
        double endMeasurePosition;
        us_timestamp_t time;
        us_timestamp_t startTime;
        us_timestamp_t endTime;
        uint32_t enable;
        bool measuring;
    }   TimeMeasure_t;
    typedef struct SampleHardnessPoint{
        us_timestamp_t time;
        double strain;
        double displ;
        double alpha;
    }   SampleHardnessPoint_t;
    typedef struct SampleHardness{
        double Fmax;//kN
        long direction; // 1 - compression, -1 - tension
        double speed;//volts
        double edgeValue1;//5% edgeValue3
        double edgeValue2;//15% Fmax
        double edgeValue3;//30% Fmax
        double edgeValue4;//15% Fmax
        double edgeValue5;//5% edgeValue3
        double maxElongation; // max delta displacement
        SampleHardnessPoint_t p1;
        SampleHardnessPoint_t p2;
        SampleHardnessPoint_t p3;
        SampleHardnessPoint_t p4;
        SampleHardnessPoint_t p5;
        SampleHardnessPoint_t p6;
        SampleHardnessPoint_t p7;
        double initialPosition;
    }   SampleHardness_t;
    typedef struct TestSignal{
        uint32_t type;
        double sinSignalAmplitude;//mm
        double sinSignalIncrement;//radian
        double constSignalPosition;//mm
        double constSignalStrain;//kN
        double constSignalDeformation;//mm
    }   TestSignal_t;
    typedef struct UserDefinedModeParams{
        //public
        double freq;//Hz
        uint32_t type;
        uint32_t numberOfPoints;
        
        //private
        PIDParams_t PIDParams;
        double _Tsection;
        double _TcycleCount;
        double _TsectionCount;
        double _period;//ms
        double _modeFreq; //0.1
        uint32_t numberOfAllPoints;
        uint32_t state;
        
        //public
        double points[40];
        double points2[40];
        //private
        float _allPoints[100];
    }   UserDefinedModeParams_t;

    // //SinusBased displacement mode params struct
    // typedef struct SinusBasedDisplacementModeParams{
    //     double UpAmplitude;//mm
    //     double DownAmplitude;//mm
    //     double UpAmplitudeSet;//mm
    //     double DownAmplitudeSet;//mm
    //     double Frequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps;
    //     double NullPointDisplacement; // null position at start of generating
    //     double NullPointStrain;       // 
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     double AngleWBuffered;
    //     double SINPoint; //sin desire point
    //     uint32_t ModeType; //square, triangle, trapeze
    //     uint32_t State; // state of sin generating
    //     double baseRatio; //for trapeze
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SinusBasedDisplacementModeParams_t;

    // //Sinus Based strain mode params struct
    // typedef struct SinusBasedStrainModeParams{
    //     double UpAmplitude;//kN
    //     double DownAmplitude;//kN
    //     double UpAmplitudeSet;//kN
    //     double DownAmplitudeSet;//kN
    //     double Frequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps;
    //     double NullPointDisplacement;
    //     double NullPointStrain; // null stain at start of generating
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double SampleLength; //mm length of current sample
    //     double SampleCut; //mm^2 cut of current sample
    //     double YoungModulus; //GPa modulus of Young
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     bool holdConstDisplAtEnd;
    //     double AngleWBuffered;
    //     double SINPoint; //sin desire point
    //     uint32_t ModeType; //square, triangle, trapeze
    //     uint32_t State; // state of Sin generating
    //     double baseRatio; //for trapeze
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SinusBasedStrainModeParams_t;

    // //SinusBased deformation mode params struct
    // typedef struct SinusBasedDeformationModeParams{
    //     double UpAmplitude;//mm
    //     double DownAmplitude;//mm
    //     double UpAmplitudeSet;//mm
    //     double DownAmplitudeSet;//mm
    //     double Frequency;//Hz
    //     double ModeFrequency;//ms min = 0,1 ms
    //     PIDParams_t PIDParams;
    //     // double Tcycle;//ms min = 1 ms
    //     double AngleW;// angle in rad
    //     double CurrentPoint; // current Y value
    //     long long NumberOfCycles; // number of sinus cycles, <0 mean infinite
    //     long long InternalCounter; // count cycles of sinus
    //     double DesirePoint; // desire Y value
    //     double PIDCorrection; //current PID correction
    //     double MaxVoltage; //valve max voltage
    //     double MaxSteps;
    //     double NullPointDisplacement; // null position at start of generating
    //     double NullPointStrain;       // 
    //     double NullPointDeformation;
    //     double MaxDeviation;
    //     double DesirePointBuffered;
    //     double InternalCounterBuffered;
    //     float DACVoltage; //current DAC Voltage in Volts
    //     bool currentAmplitudeDirection;// 0 - Up, 1 - Down
    //     bool currentAmplitudeDirectionBuffered;
    //     bool waitForPIDReset;
    //     bool holdConstDisplAtEnd;
    //     double AngleWBuffered;
    //     double SINPoint; //sin desire point
    //     uint32_t ModeType; //square, triangle, trapeze
    //     uint32_t State; // state of sin generating
    //     double baseRatio; //for trapeze
    //     AmplitudeTuneInfo_t amplitudeTuneInfo;
    //     Timer Count; // Timer for discovering 1 count of Sin signal
    // }   SinusBasedDeformationModeParams_t;

    // //Структура статической программы испытания
    // typedef struct TTask
    // {
    //  uint8_t id_tag;
    //  uint8_t rel_arr[5];
    //  //Испытание, параметры
    //  uint8_t panel_type;
    //  uint8_t isp_type;
    //  uint8_t id_boolparam;
    //  double value; 
    //  int cycle;
    //  uint8_t vozvrat;
    //  //double reserved[10];      //Зарезервированно

    //  //private
    //  int currentCycleCount;
    //  float initPosition;
    //  float initStrain;
    //  float initDeformation;
    //  std::chrono::microseconds initTime;
    //  bool firstTime;
    // } TTask_t;
    typedef uint8_t SBDStatus_t;

    typedef struct pistonParams{
        double topArea;//mm2
        double bottomArea;//mm2
    } pistonParams_t;
    typedef struct valveParams{
        double Imax;//A
        double Qvalve;//m3/sec
    } valveParams_t;

    typedef uint32_t errorCode_t;

    typedef struct error{
        bool status;
        errorCode_t code;
        char *description;
    } error_t;

    typedef uint8_t memoryType_t;
    typedef uint8_t sensorType_t;

    typedef struct channelInfo{
        double maxValue;
        double maxValueOverloadPercent;
        double minValue;
        double minValueOverloadPercent;
        sensorType_t sensorType;
    } channelInfo_t;

    typedef struct channelsInfo{
        double maxValue;
        double maxValueOverloadPercent;
        double minValue;
        double minValueOverloadPercent;
        sensorType_t sensorType;
        sensorType_t sensorTypes[4];
        uint8_t activeChannels;
    } channelsInfo_t;

    typedef struct machineInfo{
        machineType_t machineType;
        uint64_t serialNumber;
        uint64_t id;
        uint16_t ethernetProtocolVersion;
        SocketAddress EthernetBoardIPAddress;
        SocketAddress EthernetNetMask;
        SocketAddress EthernetGateway;
        uint16_t EthernetPort;
        uint32_t ethernetConnectionTimeoutStopTest;
        
        channelInfo_t displacement;
        channelInfo_t strain;
        channelsInfo_t deformation;
    } machineInfo_t;

    typedef uint8_t testStatus_t;

    typedef struct stepsParams{
        int direction;
        uint32_t steps;
        uint32_t stepsCountPerCycle;
        uint32_t cycleDuration;
    } stepsParams_t;

    typedef struct testProcessPause{
        testProcessPause(){
          status = TEST_PROCESS_CONTINUE;
          modeBeforePause = DAC_STATE_UNDEFINED;
          constMode = nullptr;
          sinMode = nullptr;
          displSharedLowerLimit = NAN;
          displSharedUpperLimit = NAN;
          strainSharedLowerLimit = NAN;
          strainSharedUpperLimit = NAN;
          deformSharedLowerLimit = NAN;
          deformSharedUpperLimit = NAN;
        }
        void resetState(){
          delete constMode;
          delete sinMode;
          status = TEST_PROCESS_CONTINUE;
          modeBeforePause = DAC_STATE_UNDEFINED;  
          displSharedLowerLimit = NAN;
          displSharedUpperLimit = NAN;
          strainSharedLowerLimit = NAN;
          strainSharedUpperLimit = NAN;
          deformSharedLowerLimit = NAN;
          deformSharedUpperLimit = NAN;
        }
        uint8_t status;
        uint32_t modeBeforePause;
        CONST *constMode;
        SIN *sinMode;

        double displSharedLowerLimit;
        double displSharedUpperLimit;
        double strainSharedLowerLimit;
        double strainSharedUpperLimit;
        double deformSharedLowerLimit;
        double deformSharedUpperLimit;
    } testProcessPause_t;
#endif