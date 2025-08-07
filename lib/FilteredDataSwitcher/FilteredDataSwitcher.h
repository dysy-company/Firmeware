#ifndef FILTERED_DATA_SWITCHER_H
#define FILTERED_DATA_SWITCHER_H
#include <cfloat>
#include <mbed.h>
#include "../include/Global_Variables.h"
#include "../include/Shared_Params.h"
#include "../Filter/Filter.h"

enum activityes {
    DIRECTING = 0,
    MONITORING = 1,
    ANSWERING = 2,
    DISPLAYING = 3
};

enum steps {
    DATA_WITHOUT_FILTER = 0,
    AFTER_FILTER_ONE = 1,
    AFTER_FILTER_TWO = 2,
    AFTER_ALL_FILTERS = 3
};

class SwitchersSet{
    public:
    SwitchersSet(float* sourseDis, float* targetDis, 
                 float* sourseStr, float* targetStr,
                 float* sourseDef, float* targetDef);

    float GetDataByActivity(const float& innData, uint32_t activ);
    errorCode_t SetFilteringActivityUnit(uint32_t dataType, uint32_t activ, uint32_t step);
    errorCode_t SetFilteringActivityStepsDataLine(uint32_t dataType, uint32_t step);
    errorCode_t SetFilteringActivityAllSteps(uint32_t step);

    uint8_t activityTypes[3] [4] {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}; 

    private:
    float* sourseDisp = nullptr;
    float* sourseStrain = nullptr;
    float* sourseDeform = nullptr;
    float* targetDisp = nullptr;
    float* targetStrain = nullptr;
    float* targetDeform = nullptr;
    uint8_t numberOfData = 3;
    //                           displacement    strain         deformation
    
};

#endif