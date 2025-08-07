#include "FilteredDataSwitcher.h"

SwitchersSet::SwitchersSet(float* sourseDis, float* targetDis, 
                           float* sourseStr, float* targetStr,
                           float* sourseDef, float* targetDef){
    sourseDisp = sourseDis; 
    sourseStrain = sourseStr; 
    sourseDeform = sourseDef; 
    targetDisp = targetDis; 
    targetStrain = targetStr; 
    targetDeform = targetDef;
};

float SwitchersSet::GetDataByActivity(const float& innData, uint32_t activ){
    if (activ >= DIRECTING && activ <= DISPLAYING){
        if (&innData == sourseDisp){
            if (activityTypes[0][activ] == DATA_WITHOUT_FILTER || isnan(innData)){
                return innData;
            }
            else return targetDisp[activityTypes[0][activ]-1];
        }
        else if (&innData == sourseStrain){
            if (activityTypes[1][activ] == DATA_WITHOUT_FILTER || isnan(innData)){
                return innData;
            }
            else return targetStrain[activityTypes[1][activ]-1];
        }
        else if (&innData == sourseDeform){
            if (activityTypes[2][activ] == DATA_WITHOUT_FILTER || isnan(innData)){
                return innData;
            }
            else return targetDeform[activityTypes[2][activ]-1];
        }
        else return NAN;
    }
    else return NAN;
}

errorCode_t SwitchersSet::SetFilteringActivityUnit(uint32_t dataType, uint32_t activ, uint32_t step){
    bool isFunctionOk = true;
    if (activ >= DIRECTING && activ <= DISPLAYING && step >= DATA_WITHOUT_FILTER && step <= AFTER_ALL_FILTERS){
        switch (dataType)
        {
        case DISPLACEMENT:
            activityTypes[0][activ] = step;
            break;
        case STRAIN:
            activityTypes[1][activ] = step;
            break;
        case DEFORMATION:
            activityTypes[2][activ] = step;
            break;
        default:
            isFunctionOk = false;
            break;
        }
        if (isFunctionOk){
            return NO_ERROR;
        }
        else return ERROR_WRONG_INPUT_DATA;
    }
    else return ERROR_WRONG_INPUT_DATA;
}

errorCode_t SwitchersSet::SetFilteringActivityStepsDataLine(uint32_t dataType, uint32_t step){
    bool isFunctionOk = true;
    if (step >= DATA_WITHOUT_FILTER && step <= AFTER_ALL_FILTERS){
        switch (dataType)
        {
        case DISPLACEMENT:
            for (int i = 0; i <= DISPLAYING; i++){
                activityTypes[0][i] = step;
            }
            break;
        case STRAIN:
            for (int i = 0; i <= DISPLAYING; i++){
                activityTypes[1][i] = step;
            }
            break;
        case DEFORMATION:
            for (int i = 0; i <= DISPLAYING; i++){
                activityTypes[2][i] = step;
            }
            break;
        default:
            isFunctionOk = false;
            break;
        }
        if (isFunctionOk){
            return NO_ERROR;
        }
        else return ERROR_WRONG_INPUT_DATA;
    }
    else return ERROR_WRONG_INPUT_DATA;
}

errorCode_t SwitchersSet::SetFilteringActivityAllSteps(uint32_t step){
    if (step >= DATA_WITHOUT_FILTER && step <= AFTER_ALL_FILTERS){
        for (uint8_t i = 0; i < numberOfData; i++){
            for (uint8_t j = 0; j <= DISPLAYING ; j++){
                activityTypes[i][j] = step;
            }
        }
        return NO_ERROR;
    }
    else return ERROR_WRONG_INPUT_DATA;
}