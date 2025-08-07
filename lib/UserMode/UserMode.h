#ifndef USER_MODE_H
#define USER_MODE_H

#include <mbed.h>
#include "TypeDefs\ParamsTypeDefs.h"
#include "Global_Variables.h"
#include "Shared_Params.h"
#include "PID.h"

extern globalVariables_t GV;

class UserMode{

public:
    UserMode(UserDefinedModeParams_t *userModeParams); // from GV
    ~UserMode();
    void calculateNextPoint(void);
    void process(
                            uint8_t &prevDACState, 
                            uint8_t &currentDACState,
                            double &DACFrequency,
                            uint32_t &dataDecimationCounterDisplacement,
                            uint32_t &dataDecimationCounterStrain); 
    void reset(void);
private:
    UserDefinedModeParams_t *userDefinedModeParams;
    uint8_t _DACState;
    PID *_PID;
};

#endif