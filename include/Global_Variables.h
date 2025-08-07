#include <mbed.h>
#include "Typedefs/ParamsTypeDefs.h"
#include "Shared_Params.h"


#ifndef Global_Variables_h
#define Global_Variables_h
#include "../lib/AverVal/AverageVal.h"
#include "../lib/MotorDriver/MotorDriver.h"

    //     SINDisplacementModeParams_t SINDisplacementModeParams = {
//         //UpAmplitude,mm  DownAmplitude,mm     Freq, Hz    modeFreq,ms
//         50.000,           50.000,50.000,50.000, 1.000,      0.100,       
//         //Kp                Ki              Kd     AngleW   CurrentPoint   
// /*0.080*/0.024, /*0.010*/0.002, /*0.005*/0.002,     0.000,      0.000,     
//         //NumberOfCycles            State                    InternalCounter
//             -1,           SIN_DISPLACEMENT_MODE_STATE_RESET,        0,
//         //DesirePoint       PIDCorrection MaxVoltage  MaxSteps   NullPoint           MaxDeviation
//             0.000,             0.000,       4.096,        0.0,    0.000,0.000,0.000,      0.020,        
//         //DesirePointBuf    InternalCounterBuf     DACVoltage   AmplitudeDirection  AmplitudeDirectionBuf  waitForPIDReset AngleWBuf  
//             0.000,              0,                   0.000,          false,               false,               false,       0.000,      
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE, 
//         //AmplitudeCorrectionType           freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_DISPLACEMENT,    200,                       10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,mm minDownAmplitude,mm
//             5,              2.0,                2.0,                0.05,                0.1
//     };


typedef struct SINDisplacementMode:SIN{
    SINDisplacementMode(){
        UpAmplitude = 50.0;
        DownAmplitude = 50.0;
        UpAmplitudeSet = 50.0;
        DownAmplitudeSet = 50.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.024;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.002;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_DISPLACEMENT_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_DISPLACEMENT;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.05;
        amplitudeTuneInfo.minDownAmplitude = 0.1;
    };
} SINDisplacementModeParams_t;

//     SinusBasedDisplacementModeParams_t SinusBasedDisplacementModeParams = {
//         //UpAmplitude,mm  DownAmplitude,mm      Freq, Hz    modeFreq,ms
//         50.000,           50.000,50.000,50.000, 1.000,      0.100,       
//         //Kp                Ki              Kd     AngleW   CurrentPoint   
// /*0.080*/0.024, /*0.010*/0.002, /*0.005*/0.002,    0.000,      0.000,     
//         //NumberOfCycles  InternalCounter
//             -1,             0,
//         //DesirePoint       PIDCorrection  MaxVoltage  MaxSteps    NullPoint           MaxDeviation
//             0.000,             0.000,        4.096,        0.0,    0.000,0.000,0.000,      0.020,        
//         //DesirePointBuf    InternalCounterBuf   DACVoltage   AmplitudeDirection  AmplitudeDirectionBuf  waitForPIDReset  
//             0.000,              0,                 0.000,           false,              false,               false,
//         //AngleWBuf  DesireSINPoint      ModeType                       State                    BaseRatio
//             0.000,       0.000,      SINUS_BASED_SQUARE,   SIN_DISPLACEMENT_MODE_STATE_RESET,      0.50,
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE,  
//         //AmplitudeCorrectionType           freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_DISPLACEMENT,    200,                       10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,mm minDownAmplitude,mm
//             5,              2.0,                2.0,                0.1,                0.1
//     };



typedef struct SINBasedDisplacementMode:SIN{
    SINBasedDisplacementMode(){
        UpAmplitude = 50.0;
        DownAmplitude = 50.0;
        UpAmplitudeSet = 50.0;
        DownAmplitudeSet = 50.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.024;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.002;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_DISPLACEMENT_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_DISPLACEMENT;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.1;
        amplitudeTuneInfo.minDownAmplitude = 0.1;
    };
    double SINPoint = 0.0; //sin desire point
    double baseRatio = 0.5; //for trapeze
    uint32_t ModeType = SINUS_BASED_SQUARE; //square, triangle, trapeze
} SinusBasedDisplacementModeParams_t;

//     SINStrainModeParams_t SINStrainModeParams = {
//         //UpAmplitude,kN  DownAmplitude,mm  Freq, Hz    modeFreq,ms
//         1.000,           1.000, 1.000,1.000,  1.000,      0.100,       
//         //Kp                Ki              Kd    AngleW   CurrentPoint   
// /*0.080*/0.100, /*0.010*/0.002, /*0.005*/0.010,   0.000,      0.000,     
//         //NumberOfCycles            State                    InternalCounter
//             -1,           SIN_STRAIN_MODE_STATE_RESET,        0,
//         //DesirePoint       PIDCorrection    MaxVoltage  MaxSteps     NullPoint           MaxDeviation
//             0.000,             0.000,          4.096,          0.0,     0.000,0.000,0.000,      0.020,
//         //SampleLength, mms     SampleCut, mm^2 != 0    Young Modulus, GPa
//         200.0,                    78.5,                    210.0,
//         //DesirePointBuf    InternalCounterBuf    DACVoltage  AmplitudeDirection  AmplitudeDirectionBuf  waitForPIDReset holdConstDisplAtEnd  AngleWBuf
//             0.000,              0,                  0.000,          false,               false,              false,          true,              0.000,
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE,
//         //AmplitudeCorrectionType       freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_STRAIN,      200,                        10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,kN minDownAmplitude,kN
//             5,              2.0,                2.0,                5.0,                5.0
//     };

typedef struct SINStrainMode:SIN{
    SINStrainMode(){
        UpAmplitude = 1.0;
        DownAmplitude = 1.0;
        UpAmplitudeSet = 1.0;
        DownAmplitudeSet = 1.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.1;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.01;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_STRAIN_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_STRAIN;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.3;
        amplitudeTuneInfo.minDownAmplitude = 0.3;
    };
    double SampleLength = 200.0; //mm length of current sample
    double SampleCut = 78.5; //mm^2 cut of current sample
    double YoungModulus = 210.0;
    bool holdConstDisplAtEnd = true;
} SINStrainModeParams_t;


//     SinusBasedStrainModeParams_t SinusBasedStrainModeParams = {
//         //UpAmplitude,kN  DownAmplitude,mm   Freq, Hz    modeFreq,ms
//         1.000,           1.000, 1.000,1.000,  1.000,      0.100,       
//         //Kp                Ki              Kd      AngleW   CurrentPoint   
// /*0.080*/0.100, /*0.010*/0.002, /*0.005*/0.010,     0.000,      0.000,     
//         //NumberOfCycles     InternalCounter
//             -1,                   0,
//         //DesirePoint       PIDCorrection  MaxVoltage  MaxSteps   NullPoint               MaxDeviation
//             0.000,             0.000,        4.096,        0.0,    0.000,0.000,0.000,      0.020,
//         //SampleLength, mms     SampleCut, mm^2 != 0    Young Modulus, GPa
//         200.0,                    78.5,                    210.0,
//         //DesirePointBuf    InternalCounterBuf  DACVoltage   AmplitudeDirection   AmplitudeDirectionBuf  waitForPIDReset   holdConstDisplAtEnd
//             0.000,              0,                0.000,            false,            false,                    false,          true,
//         //AngleWBuf DesireSINPoint      ModeType                State                    BaseRatio
//             0.000,    0.000,      SINUS_BASED_SQUARE,   SIN_STRAIN_MODE_STATE_RESET,        0.50,
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE,
//         //AmplitudeCorrectionType       freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_STRAIN,      200,                        10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,kN minDownAmplitude,kN
//             5,              2.0,                2.0,                5.0,                5.0
//     };

typedef struct SINBasedStrainMode:SIN{
    SINBasedStrainMode(){
        UpAmplitude = 1.0;
        DownAmplitude = 1.0;
        UpAmplitudeSet = 1.0;
        DownAmplitudeSet = 1.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.1;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.01;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_STRAIN_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_STRAIN;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.3;
        amplitudeTuneInfo.minDownAmplitude = 0.3;
    };
    double SampleLength = 200.0; //mm length of current sample
    double SampleCut = 78.5; //mm^2 cut of current sample
    double YoungModulus = 210.0;
    double SINPoint = 0.0; //sin desire point
    double baseRatio = 0.5; //for trapeze
    uint32_t ModeType = SINUS_BASED_SQUARE; //square, triangle, trapeze
    bool holdConstDisplAtEnd = true;
} SinusBasedStrainModeParams_t;

//     SINDeformationModeParams_t SINDeformationModeParams = {
//         //UpAmplitude,mm  DownAmplitude,mm     Freq, Hz    modeFreq,ms
//         50.000,           50.000,50.000,50.000, 1.000,      0.100,       
//         //Kp                Ki              Kd     AngleW   CurrentPoint   
// /*0.080*/0.024, /*0.010*/0.002, /*0.005*/0.002,     0.000,      0.000,     
//         //NumberOfCycles            State                    InternalCounter
//             -1,           SIN_DEFORMATION_MODE_STATE_RESET,        0,
//         //DesirePoint       PIDCorrection MaxVoltage  MaxSteps   NullPoint           MaxDeviation
//             0.000,             0.000,       4.096,        0.0,    0.000,0.000,0.000,      0.020,        
//         //DesirePointBuf    InternalCounterBuf     DACVoltage   AmplitudeDirection  AmplitudeDirectionBuf  waitForPIDReset holdConstDisplAtEnd AngleWBuf  
//             0.000,              0,                   0.000,          false,               false,               false,           true,                   0.000,      
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE, 
//         //AmplitudeCorrectionType           freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_DEFORMATION,    200,                       10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,mm minDownAmplitude,mm
//             5,              2.0,                2.0,                0.05,                0.1
//     };    

typedef struct SINDeformationMode:SIN{
    SINDeformationMode(){
        UpAmplitude = 50.0;
        DownAmplitude = 50.0;
        UpAmplitudeSet = 50.0;
        DownAmplitudeSet = 50.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.024;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.002;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_DEFORMATION_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_DEFORMATION;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.05;
        amplitudeTuneInfo.minDownAmplitude = 0.1;
    };
    bool holdConstDisplAtEnd = true;
} SINDeformationModeParams_t;


//     SinusBasedDeformationModeParams_t SinusBasedDeformationModeParams = {
//         //UpAmplitude,mm  DownAmplitude,mm      Freq, Hz    modeFreq,ms
//         50.000,           50.000,50.000,50.000, 1.000,      0.100,       
//         //Kp                Ki              Kd    AngleW   CurrentPoint   
// /*0.080*/0.024, /*0.010*/0.002, /*0.005*/0.002,    0.000,      0.000,     
//         //NumberOfCycles  InternalCounter
//             -1,             0,
//         //DesirePoint       PIDCorrection  MaxVoltage  MaxSteps    NullPoint           MaxDeviation
//             0.000,             0.000,        4.096,        0.0,    0.000,0.000,0.000,      0.020,        
//         //DesirePointBuf    InternalCounterBuf   DACVoltage   AmplitudeDirection  AmplitudeDirectionBuf  waitForPIDReset  holdConstDisplAtEnd
//             0.000,              0,                 0.000,           false,              false,               false,             true,
//         //AngleWBuf  DesireSINPoint      ModeType                       State                    BaseRatio
//             0.000,       0.000,      SINUS_BASED_SQUARE,   SIN_DEFORMATION_MODE_STATE_RESET,      0.50,
//         //amplTuneUpP  amplTuneUpI  amplTuneUpD  amplTuneDownP amplTuneDownI  amplTuneDownD     AmplitudeTuneState
//             0.35,         0.002,       0.01,        0.35,         0.002,           0.01,    AMPLITUDE_TUNE_STATE_DISABLE,  
//         //AmplitudeCorrectionType           freqThread,ms       RiseTime,cycles     FallTime,cycles
//             CORRECTION_TYPE_DEFORMATION,    200,                       10,                 10,
//         //WaitCycles    IncrementMultiplier DecrementMultiplier minUpAmlitude,mm minDownAmplitude,mm
//             5,              2.0,                2.0,                0.1,                0.1
//     };

typedef struct SINBasedDeformationMode:SIN{
    SINBasedDeformationMode(){
        UpAmplitude = 50.0;
        DownAmplitude = 50.0;
        UpAmplitudeSet = 50.0;
        DownAmplitudeSet = 50.0;
        SINFrequency = 1.0;
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.024;
        PIDParams.Ki = 0.002;
        PIDParams.Kd = 0.002;
        AngleW = 0.0;
        CurrentPoint = 0.0;
        NumberOfCycles = -1;
        State = SIN_DEFORMATION_MODE_STATE_RESET;
        InternalCounter = 0;
        DesirePoint = 0.0;
        PIDCorrection = 0.0;
        MaxVoltage = 4.096;
        MaxSteps = 10;
        NullPointDisplacement = 0.0;
        NullPointStrain = 0.0;
        NullPointDeformation = 0.0;
        MaxDeviation = 0.02;
        DesirePointBuffered = 0.0;
        InternalCounterBuffered = 0.0;
        DACVoltage = 0.0;
        currentAmplitudeDirection = false;
        currentAmplitudeDirectionBuffered = false;
        waitForPIDReset = false;
        AngleWBuffered = 0.0;
        amplitudeTuneInfo.UpKP = 0.35;
        amplitudeTuneInfo.UpKI = 0.002;
        amplitudeTuneInfo.UpKD = 0.01;
        amplitudeTuneInfo.DownKP = 0.35;
        amplitudeTuneInfo.DownKI = 0.002;
        amplitudeTuneInfo.DownKD = 0.01;
        amplitudeTuneInfo.NullPointKP = 0.5;
        amplitudeTuneInfo.NullPointKI = 0.0005;
        amplitudeTuneInfo.NullPointKD = 0.3;
        amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
        amplitudeTuneInfo.correctionType = CORRECTION_TYPE_DEFORMATION;
        amplitudeTuneInfo.freq = 200;
        amplitudeTuneInfo.amplitudeRiseCycles = 10;
        amplitudeTuneInfo.amplitudeFallCycles = 10;
        amplitudeTuneInfo.waitCycles = 5;
        amplitudeTuneInfo.incrementMultiplier = 2.0;
        amplitudeTuneInfo.decrementMultiplier = 2.0;
        amplitudeTuneInfo.minUpAmplitude = 0.1;
        amplitudeTuneInfo.minDownAmplitude = 0.1;
    };
    double SINPoint = 0.0; //sin desire point
    uint32_t ModeType = SINUS_BASED_SQUARE; //square, triangle, trapeze
    double baseRatio = 0.5; //for trapeze
    bool holdConstDisplAtEnd = true;
} SinusBasedDeformationModeParams_t;

// ConstDisplacementModeParams_t ConstDisplacementModeParams = {
//     //Position to hold, mm  ModeFrequency, ms   CurrentPosition
//     0.000,                  0.100,              0.000,          
//     //Kp     Ki     Kd                      PIDCorrection       MaxDeviation, mm                            
//     0.0001, /*0.0006*/0.00000001, /*0.0000001*/0.0000001,    0.000,              0.005,              
//     //State                              MaxVoltage  MaxSteps  Speed mm/sec   MaxSpeed    delta,mm
//     CONST_DISPLACEMENT_MODE_STATE_RESET, 1,            0.0,        0.0,        10.0,       0.01,
//     //StrainUpperLimit  DeformUpperLimit   StrainLowerLimit  DeformLowerLimit
//     //NAN,                NAN,                NAN,              NAN
// };

typedef struct CONSTDisplacementModeParams:CONST{
    CONSTDisplacementModeParams(){
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.0001;
        PIDParams.Ki = 0.00000001;
        PIDParams.Kd = 0.0000001;
        PIDCorrection = 0.0;
        MaxDeviation = 0.005;
        State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        MaxVoltage = 1;
        MaxSteps = 10;
        Speed = 0.0;
        MaxSpeed = 10.0;
        delta = 0.01;
        nextDesirePoint = 0.0;
        msCounter = 0;
        k = 0.0;
        b = 0.0;
        speedEnable = false;
        t = 0;
    };
    double PositionToHold = 0.0;
    double CurrentPosition = 0.0;
    bool waitForPIDReset = false;
} ConstDisplacementModeParams_t;

// ConstStrainModeParams_t ConstStrainModeParams = {
//     //Strain to hold, kN  ModeFrequency, ms   CurrentStrain
//     0.000,                  0.100,              0.000,          
//     //Kp     Ki     Kd      PIDCorrection       MaxDeviation, kN
//     //0.100, 0.001, 0.010,    0.000,              0.025,              
//     0.400,  0.0001, 0.400,      0.000,              1.0,
//     //SampleLength, mms     SampleCut, mm^2 != 0    Young Modulus, GPa
//     200.0,                    78.5,                    0.1,
//     //State                         MaxVoltage, V  MaxSteps   Speed, kN/sec   MaxSpeed    delta,kN
//     CONST_STRAIN_MODE_STATE_RESET,   3.072,         0.0,          0.0,            100.0,      0.1,
//     //DisplacementUpperLimit   DeformUpperLimit   DisplacementLowerLimit   DeformLowerLimit
//     //NAN,                       NAN,                 NAN,                    NAN
// };

typedef struct CONSTStrainModeParams:CONST{
    CONSTStrainModeParams(){
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.4;
        PIDParams.Ki = 0.0001;
        PIDParams.Kd = 0.4;
        PIDCorrection = 0.0;
        MaxDeviation = 1.0;
        State = CONST_STRAIN_MODE_STATE_RESET;
        MaxVoltage = 3.072;
        MaxSteps = 10;
        Speed = 0.0;
        MaxSpeed = 100.0;
        delta = 0.1;
        nextDesirePoint = 0.0;
        msCounter = 0;
        k = 0.0;
        b = 0.0;
        speedEnable = false;
        t = 0;
    };
    double StrainToHold = 0.0;
    double CurrentStrain = 0.0;
    double SampleLength = 200.0;
    double SampleCut = 78.5;
    double YoungModulus = 0.1;
} ConstStrainModeParams_t;

// ConstDeformationModeParams_t ConstDeformationModeParams = {
//     //Position to hold, mm  ModeFrequency, ms   CurrentPosition
//     0.000,                  0.100,              0.000,          
//     //Kp     Ki     Kd                      PIDCorrection       MaxDeviation, mm                            
//     0.0100, /*0.400*/0.000002, /*0.050*/0.0010,    0.000,              0.5,              
//     //State                              MaxVoltage  MaxSteps  Speed mm/sec   MaxSpeed    delta,mm
//     CONST_DEFORMATION_MODE_STATE_RESET,    3.072,      0.0,        0.0,        10.0,       0.01,
//     //
//     //NAN,                NAN,                NAN,              NAN
// };

typedef struct CONSTDeformationModeParams:CONST{
    CONSTDeformationModeParams(){
        ModeFrequency = 0.1;
        PIDParams.Kp = 0.01;
        PIDParams.Ki = 0.000002;
        PIDParams.Kd = 0.001;
        PIDCorrection = 0.0;
        MaxDeviation = 0.5;
        State = CONST_DEFORMATION_MODE_STATE_RESET;
        MaxVoltage = 3.072;
        MaxSteps = 10;
        Speed = 0.0;
        MaxSpeed = 10.0;
        delta = 0.01;
        nextDesirePoint = 0.0;
        msCounter = 0;
        k = 0.0;
        b = 0.0;
        speedEnable = false;
        t = 0;
    };
    double DeformationToHold = 0.0;
    double CurrentDeformation = 0.0;
} ConstDeformationModeParams_t;

    //global struct
    typedef struct globalVariables{
        machineType_t machineType = MACHINE_TYPE_ELECTRO_STATIC_MACHINE;
    //WORKING PARAMS:
        int positionAxisMode = POSITION_INCREASE_PISTON_PULL;
        int strainAxisMode = STRAIN_INCREASE_PISTON_PULL;
        int deformationAxisMode = DEFORMATION_INCREASE_PISTON_PUSH;

        int positionInvertAxis = POSITION_INVERTED_AXIS;
        int strainInvertAxis = STRAIN_INVERTED_AXIS;
        int deformationInvertAxis = DEFORMATION_NOT_INVERTED_AXIS;

        int pistonMode = PISTON_UP_PISTON_PUSH;

        int valveDirectionMode = VALVE_NOT_INVERTED_DIRECTION;

        int controllerOnlineMode = CONTROLLER_MODE_STOP_IF_NOT_CONNECTED;

        testStatus_t testStatus = TEST_STATUS_TEST_IS_OFF;
        //                              TopArea,mm2     BottomArea,mm2
        pistonParams_t PistonParams = {     0.000,          0.000 }; //////////////// ?????????????? ////////////////
        //                              Imax,A          Qvalve,m3/sec
        valveParams_t   ValveParams = {     0.015,          0.0005 };
        //                              Type  sinAmpl  sinIncr  constPosition  constStrain  constDeformation
        TestSignal_t TestSignalInfo = { TEST_SIGNAL_NONE,   100.0,  0.001,      100.0,          10.0 ,  5.0};
        //uint32_t TestSinSignal = 0;//0-disable,1-sin, 2 - const value
        //double TestSinSignalAmplitude = 100;//mm
        //double TestSinSignalIncrement = 0.001;//radian
        //Pulse mode global params           Freq   Kp      Ki      Kd   Amplit
        //pulseModeParams_t PulseModeParams = {0.100, 0.200, 0.000, 0.010, 0.000};
        //Constant mode global variables     Freq  Voltage Dir
        constModeParams_t ConstModeParams = {0.100, 0.000, 0};
        

        SINDisplacementModeParams_t SINDisplacementModeParams;
        SINDeformationModeParams_t SINDeformationModeParams;  
        SinusBasedDisplacementModeParams_t SinusBasedDisplacementModeParams;
        SinusBasedDeformationModeParams_t SinusBasedDeformationModeParams;
        SINStrainModeParams_t SINStrainModeParams;
        SinusBasedStrainModeParams_t SinusBasedStrainModeParams;

        ConstDisplacementModeParams_t ConstDisplacementModeParams;
        ConstStrainModeParams_t ConstStrainModeParams;
        ConstDeformationModeParams_t ConstDeformationModeParams;
        
        SINVoltageModeParams_t SINVoltageModeParams = {
            //MaxVoltage
            0.0
        };
        //Mode settings
        uint32_t Mode = DAC_STATE_DISP_CONST;
    //PARAMETERS ONLY FOR READING:
        // long PreviousDirection = 0;
        long CurrentDirection= 0;
    //DAC PARAMS:
        int DACSpiMode = 0; // ????
        // int DACSpiFreq = 200000000;
        bool DACOut = 0;
        bool DACInBufCtrl = 1;
        bool DACGain = 1;
        bool DACOutPwrDownCtrl = 1;
        float DACVref = 4.096;
    //ADC PARAMS:
        // int ADCSpiMode = 3;
        // int ADCSpiFreq = 2400000;
        // for ADC TI ADS8320
        float ADCVref = 5;
        // for ADC TI ADS8691
        float ADCVref1 = 4.096;
        // float ADCNullPoint = 0;
        float ADCNullOffset = 0;
        uint8_t strainChannel = STRAIN_CHANNEL_1ST;
    //ADC Extens PARAMS:
        float ADCExtensVref = 5;
        float ADCExtensVref1 = 4.096;
        // float ADCExtensNullPoint = 0;
        float ADCExtensNullOffset = 0;
        int DeformationChannel = DEFORMATION_UNDEFINED_CHANNEL;
    //Data decimation of stream to PC
        uint32_t DataDecimationCoeff = 1;
    //DAC constant addition voltage
        float DACConstError = 0;//0.036f;
    //TM Params;
    // Enabled TM Flags:
    //  MSB 31 30 29 28 27 26 25 24 
    //     |        Reserved
    //      23 22 21 20 19 18 17 16 
    //              Reserved
    //      15 14 13 12 11 10 9 8 
    //              Reserved
    //      7 6     5                4       3       2       1            0        LSB
    //              Deformation|SENSORS_TM|PID_SIN|PID_ZERO| Strain  | Displacement  |
        uint32_t EnabledAcq = 0x23;
        uint32_t AverageAcq = 0x0;
        AverageValue AveragePosition;
        AverageValue AverageStrain;
        AverageValue AverageDeformation;
        //global work mode:
        //          0 - setting sample
        //          1 - ready fot testing
        //          2 - testing
        uint32_t WorkMode = WORK_MODE_SETTING_SAMPLE;
        uint32_t InternalTask = INTERNAL_TASK_NONE;
        uint32_t InternalTaskState = INTERNAL_TASK_STATE_NONE;
        uint32_t InternalTaskSBD = INTERNAL_TASK_SBD_NONE;
        //current delta between acq points
        // double DeltaPoints = TcycleTime;
        //Reference voltage (volts)
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
        float ReferenceVoltage = 3.0;
        float ExtensRefVoltage = 3.0;
        float DisplRefVoltage = 3.0;
        #else
        float ReferenceVoltage = 10.0;
        float ExtensRefVoltage = 10.0;
        float DisplRefVoltage = 10.0;
        #endif
                            //displ sens current    strain sens current   coil current  strain sens voltage
        // SensorTM_t SensorTM = {55.0,                55.0,                   55.0,          55.0};
        uint32_t StrainUnits = STRAIN_UNITS_KN; 
        // uint32_t StrainAmpCoef = STRAIN_AMP_COEF_70;
        uint32_t DeformationUnits = DEFORMATION_UNITS_MM; 
        // uint32_t DeformationAmpCoef = DEFORMATION_AMP_COEF_70;
        uint32_t PositionUnits = POSITION_UNITS_MM;
        
        PIDParams_t AmplitudePID = {0.5, 0.001, 0.01};
        TimeMeasure_t TimeMeasure = {0.0, 0.0, 0x0, 0x0, 0x0, 0x0, false};
        // Wait Acquisition Complete TM Flags:
        //  MSB 31 30 29 28 27 26 25 24 
        //     |        Reserved
        //      23 22 21 20 19 18 17 16 
        //              Reserved
        //      15 14 13 12 11 10 9 8 
        //              Reserved
        //      7 6 5           4       3       2       1            0        LSB
        //              |    Reserv|  Reserv|  Reserv| Strain  | Displacement  |
        UserDefinedModeParams_t UserDefinedModeParams = {
            //Freq, Hz      Type                                     NoP
            1.0,         USER_DEFINED_DISPLACEMENT_MODE_STATE_EXIT,   40,
            //Kp    Ki      Kd      Tsection,ms 
            0.024, 0.002,   0.002,     25.0,
            //TcycleCount   TsectionCount   Period, ms  ModeFreq, ms    NoAllP
            0.0,            0.0,             1000.0,        0.1,        1000,
            //state
            USER_DEFINED_STRAIN_MODE_STATE_RESET
        };
        uint32_t WaitAcqComplete = WAIT_ACQ_COMPLETE_DISPLACEMENT | WAIT_ACQ_COMPLETE_STRAIN | WAIT_ACQ_COMPLETE_DEFORMATION;//0x03;
        float roCurrentPosition = 0.0;
        float positionNullOffset = 0.0;
        float deformationNullOffset = 0.0;
        float roCurrentAvPosition = 0.0;
        float currentAvPositionSum = 0.0;
        // us_timestamp_t roCurrentPositionTime = 0;
        float roCurrentStrain = 0.0;
        float roCurrentAvStrain = 0.0;
        float currentAvStrainSum = 0.0;
        // us_timestamp_t roCurrentStrainTime = 0;
        float roCurrentDeformation = 0.0;
        float roCurrentAvDeformation = 0.0;
        float currentAvDeformationSum = 0.0;
        // us_timestamp_t roCurrentDeformationTime = 0;
        float filteredCurrentStrain[3] {0.0, 0.0, 0.0};
        float filteredCurrentDisplacement[3] {0.0, 0.0, 0.0};
        float filteredCurrentDeformation[3] {0.0, 0.0, 0.0};

        //button strain protection
        float strainButtonUpperLimit = 0.5;
        float strainButtonLowerLimit = -0.5;

        //cyclic delta for protection
        float strainCyclicDelta = 1000;
        float displacementCyclicDelta = 1000;
        float deformationCyclicDelta = 1000;

        //speed by button
        float displButtonRegularSpeed = 1.0;
        float displButtonFastSpeed = 5.0;

        uint8_t readingAndWritingFlashTrash = 0;
        uint8_t avCounter = 0;
        bool stopCurrentTestProcess = false;
        //uint64_t serialNumber = 0x80000001;
        //0x1122334455667788
        //7788 - type of controller:
        //          0x8001 - universal hydro machine (UHM) with 1 vertical cylinder
        //uint64_t id = 0x8000 | machineType;
        SampleHardness_t SampleHardnessInfo;
        Ticker Tcycle;
        us_timestamp_t TcycleTime = 10000;//us
        us_timestamp_t prevTcycleTime = 10000;
        us_timestamp_t TcycleTimeFlashWriting = 100000;
        bool isTcycleForFlashWriting = false;
        
        uint64_t strokeCounter = 0;
        //TTask_t staticTestSteps[255];
        //int currentStaticTestStep;
        //int staticTestStepsCount;
        double positionUpperThreshold = 0.02;
        double positionLowerThreshold = 0.02;
        double strainUpperThreshold = 1.0;
        double strainLowerThreshold = 1.0;
        double deformationUpperThreshold = 0.1;
        double deformationLowerThreshold = 0.1;
        // float firstStepPosition;
        // float firstStepStrain;
        // float currentDesirePosition;
        // float currentDesireStrain;
        // double SBDProcentOfMaxStrain1 = 50;
        // double SBDStartStrain1 = 10;
        // double SBDProcentOfMaxStrain2 = 50;
        // double SBDStartStrain2 = 10;
        // std::chrono::microseconds SBDTime = 10us;
        // uint8_t SBDStateMaxStrain = 1;
        // uint8_t SBDStateDF = 1;
        // uint32_t SBDThreshold = 3;
        double currentModeFreq = 0.1;
        //Const displacement
        uint32_t  msPositionCounter = 0;
        float     mmLastPosition = 0;
        double    SSISensorResolution = 0.001;
        uint32_t SensorsConnectionsAcq = 0x01;
        uint32_t StrainSensorIsConnect = SENSOR_TEDS_UNDEFINED;
        //float initPosition;
        //float initStrain;
        //uint8_t displacementSensorType = SENSOR_TYPE_DIGITAL_RSSI;
        motorDriverType_t motorDriverType = MOTOR_DRIVER_TYPE_CW_CCW;
        uint8_t LimitSwitchType = LIMIT_SWITCH_TYPE_ONE;
        int LimitSwitchState = LIMIT_SWITCH_STATE_UNDEFINED;
        double MaxPosition;
        double encoderStepValue = 0.0005;//mm
        double encoderExtensiaStepValue= 0.0002;//mm
        double motorStepValue = 0.0005;
        int StepValueThreshold = 2;
        uint32_t stepsForCalibration = 25;
        uint32_t directionForCalibration = 1;
        double displValueForCalibration = 0;
        uint32_t stopCalibration = 0;
        int LimitSwitchPolarity1 = true;
        int LimitSwitchPolarity2 = true;
        int EmergencyStopPolarity = false;
        machineInfo_t machineInfo;
        // bool _nextIndex = false;

        double displOverrunStepBack = 0;
        double displUnderrunStepBack = 0;
        double strainOverrunStepBack = 0;
        double strainUnderrunStepBack = 0;
        double deformOverrunStepBack = 0;
        double deformUnderrunStepBack = 0;

        double displSharedUpperLimit = NAN;
        double displSharedLowerLimit = NAN;
        double strainSharedUpperLimit = NAN;
        double strainSharedLowerLimit = NAN;
        double deformSharedUpperLimit = NAN;
        double deformSharedLowerLimit = NAN;

        uint32_t TestDataUnits = NA;

        //cyclic without step start hydraulic variables
        float prevModeDACvoltage = 0.0;
        float currentModeDACvoltage = 0.0;

        //amplitude attenuation variables

        double prevAmplitudeUpSet = 0.0;
        double prevAmplitudeDownSet = 0.0;
        double nullPointDelta = 0.0;
        double prevNullPointDelta = 0.0;
        uint32_t nullPointAttenuationCounter = 0;
        double minDeltaRatioForNullPointAttenuating = 0.2;//0.1
        double minAmplForDisplNullPointAttenuating = 0.01; //0.01 mm
        double minAmplForDeformNullPointAttenuating = 0.001; //0.001 mm
        double minAmplForStrainNullPointAttenuating = 0.2; //0.1 kN
        uint32_t stepForNullPointGetCorrection = 9;
        uint32_t minMaxCalculatingCounts = 3;
        uint32_t minMaxCountsSwitcher = 0;
        uint32_t minMaxCountsSwitcherLimit = 21;
        int minMaxCalculatingCountsMainProcess = 6;
        int preMinMaxCalculatingCountsMainProcess = -1;
        float tresholdForNullPointDeltaAccept = 0.92;
        double startStopAmplitudeRatio = 0.9;
        double stopAmplitudeRatio = 0.9;
        double edgeAmplitudeRatioForTuneStepsNumbChange = 0.95;
        double amplitudePrecision = 0.005;
        double angleForTrigger = -(M_PI);
        //float smoothStartFrequencyRatio = 0.25;
        bool isStopTuneModeAmplitudeEnabled = false;
        double nominalBothAmplAndSetBothAmplRatio = 1.0;
        double anchorSinFrequencyStop = 0.3;
        double reserveSinMainFrequency = 0.0;
        double anchorSinFrequency = 0.3;

        //cyclic strain protection coefs
        bool isFirstMoove = true;
        bool isSimpleCyclicProtection = false;
        uint32_t isBlindeRegion = 0;
        double blindePartOfCyclicStrainProtection = 0.2;
        double defaultBlindePartOfCyclicStrainProtection = 0.25;
        double blindePartOfCyclicStrainProtectionFirst = 0.25;
        double defaultBlindePartOfCyclicStrainProtectionFirst = 0.3;
        double deltaCyclicProtection = 0.05;
        double multiplier = 3;
        double diagnosticsStrain = 0.0;
        double deltaCyclicProtectionDefault = 0.025;
        double multiplierDefault = 4;
        uint32_t actualCyclicStrainProtectCounts = 0;
        uint32_t cyclicProtectMode = CYCLIC_PROTECTION_OFF;
        
        
        //
        double middlePistonPosition = NAN;
        double addNullPoint = 0.0;

        // ExT_SBD
        uint8_t ExT_SBDStateMaxStrain = 0;
        uint8_t ExT_SBDStateDF = 0;
        double ExT_SBDProcentOfMaxStrain1 = 50;
        double ExT_SBDStartStrain1 = 10;
        uint32_t Ext_SBDThreshold = 3;
        double ExT_SBDProcentOfMaxStrain2 = 50;
        double ExT_SBDStartStrain2 = 10;
        std::chrono::microseconds ExT_SBDTime = 10us;
        
        double SSINullOffset = 0.0;
        float  SSIPositionOffset = 0.0;

        uint32_t PWMFreq = 100000;

        uint32_t flashOperationType = FLASH_OPERATION_DMA;

        // Limit modes variables
        bool isBeginStrainHiger = false;
        bool isBeginDeformationHiger = false;
        bool isBeginDisplacementHiger = false;

        uint8_t enableActiveLevel = 1;
        uint8_t CLRActiveLevel = 1;
        uint8_t CWLActiveLevel = 0;
        uint8_t CCWLActiveLevel = 0;

        template <typename B>
        void flashWriteModeTcycleSet(B* ptrB, void (B::*ptrMethodOfB)()){
            if (TcycleTime < TcycleTimeFlashWriting){
                prevTcycleTime = TcycleTime;
                Tcycle.detach();
                Tcycle.attach(callback(ptrB, ptrMethodOfB), 
                                        std::chrono::microseconds(TcycleTimeFlashWriting));
                TcycleTime = TcycleTimeFlashWriting;
                isTcycleForFlashWriting = true;
            }
        }

        template <typename B>
        void flashWriteModeTcycleReset(B* ptrB, void (B::*ptrMethodOfB)()){
            if (isTcycleForFlashWriting){
                Tcycle.detach();
                Tcycle.attach(callback(ptrB, ptrMethodOfB), 
                                        std::chrono::microseconds(prevTcycleTime));
                TcycleTime = prevTcycleTime;
                isTcycleForFlashWriting = false;
            }
        }
        
        //Params for digital valve
        uint32_t maxPosition = 77800;
        uint32_t middlePosition = 40000;
        uint32_t middleUpThreshold = 1000;
        uint32_t middleDownThreshold = 2000;
        uint32_t positionDivider = 2;
        int valveInvertAxis = 1;
        double maxPercentage = 1;

        uint32_t closeValveState = CLOSE_VALVE_STATE_RESET;
        uint32_t valveUnits = VALVE_UNITS_PERCENT;

        int LimSwLeftDoorPolarity = true;
        int LimSwRightDoorPolarity = true;

        std::string ipAddress = ETHERNET_DEFAULT_BOARD_IP_ADDRESS;
        std::string netMask = ETHERNET_DEFAULT_NET_MASK;
        std::string gateway = ETHERNET_DEFAULT_GATEWAY;
        uint16_t port = ETHERNET_DEFAULT_PORT;

        uint32_t stepID = 0;
        //For control panel, converting to I, mA
        float ampCoef = 0.02; //From V to A
        float conversionCoef = 1000; //From A to mA

        testProcessPause_t testProcessPause;

    }   globalVariables_t;
 
#endif
