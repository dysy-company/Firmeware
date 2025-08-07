#ifndef SAMPLE_BREAK_DETECTION_H
#define SAMPLE_BREAK_DETECTION_H

#include <mbed.h>
#include "..//..//include//Global_Variables.h"
#include "..//..//include//TypeDefs/ParamsTypeDefs.h"
#include "float.h"

#define SBD_MODE_PERCENT_OF_MAX_STRAIN   0x00
#define SBD_MODE_DYNAMIC_FALL            0x01

#define SBD_STATUS_OK                   0x00
//#define SBD_STATUS_BREAK                0x01
#define SBD_STATUS_BREAK_MAX_STRAIN     0x01
#define SBD_STATUS_BREAK_DYNAMIC_FALL   0x02

#define SBD_DYNAMIC_FALL_STATE_INIT         0x00
#define SBD_DYNAMIC_FALL_STATE_WAIT_FALL    0x01
#define SBD_DYNAMIC_FALL_STATE_FALL         0x02
#define SBD_DYNAMIC_FALL_STATE_CLEAR_STATE  0x03

#define SAMPLE_BREAK_DETECTION_DISABLE                                          0x00
#define SAMPLE_BREAK_DETECTION_ENABLE                                           0x01

extern Timer SystemTimer;

class SampleBreakDetection{

public:
    SampleBreakDetection();
    SampleBreakDetection(uint8_t mode);
    ~SampleBreakDetection();
    void setEnable(uint8_t state);
    void init(uint8_t mode, int tensionDirection, float currentStrainValue);
    void setModeParams(double procentOfMaxStrain, double Fstart, uint32_t threshold);
    void setModeParams(double procentOfMaxStrain, double Fstart, std::chrono::microseconds Time);
    void setModeParams(double procentOfMaxStrain, double Fstart, uint32_t threshold, globalVariables_t *globalVariables);
    SBDStatus_t process(float value, bool valueSign);

private:
    uint8_t _mode;
    double _Fstart;
    double _procentOfMaxStrain;
    double _maxStrain;
    double _prevValue;
    int _tensionDirection;
    uint8_t _dynamicFallState;
    float _initialStrain;
    bool _firstBlood;

    uint32_t _sampleBreakStatusCounter;
    uint32_t _threshold;

    bool _valueSign;

    uint8_t _state;
    std::chrono::microseconds _startTime;
    std::chrono::microseconds _Time;
    std::chrono::microseconds _SBDTime;
    globalVariables_t *_globalVariables;

    SBDStatus_t checkValueByMaxStrain(float value, bool valueSign);
};

#endif