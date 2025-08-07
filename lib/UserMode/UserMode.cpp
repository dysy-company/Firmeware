#include "UserMode.h"

UserMode::UserMode(UserDefinedModeParams_t *userModeParams){
    userDefinedModeParams = userModeParams;
    _PID = new PID();
    this->reset();
    
}

UserMode::~UserMode(){
    userDefinedModeParams = nullptr;
    delete _PID;
}

void UserMode::reset(){
    userDefinedModeParams->_Tcycle = GV.TcycleTime;
    userDefinedModeParams->_period = (1 / userDefinedModeParams->freq) * 1000;
    userDefinedModeParams->numberOfPoints = 40;
    userDefinedModeParams->numberOfAllPoints = 1000 / (userDefinedModeParams->freq * userDefinedModeParams->_Tcycle);
    userDefinedModeParams->_TcycleCount = 0;
    userDefinedModeParams->_TsectionCount = 0;
    userDefinedModeParams->_Tsection = 1000 / (userDefinedModeParams->freq * userDefinedModeParams->numberOfPoints);
    userDefinedModeParams->_modeFreq = 0.1;
    _PID->setCoefs(
        userDefinedModeParams->PIDParams.Kp,
        userDefinedModeParams->PIDParams.Ki,
        userDefinedModeParams->PIDParams.Kd);
    _PID->reset();
    userDefinedModeParams->state = USER_DEFINED_STRAIN_MODE_STATE_RESET;
}

void UserMode::calculateNextPoint(){
    
}

void UserMode::process(
                            uint8_t &prevDACState, 
                            uint8_t &currentDACState,
                            double &DACFrequency,
                            uint32_t &dataDecimationCounterDisplacement,
                            uint32_t &dataDecimationCounterStrain){
    _DACState = currentDACState;
    switch (GV.WorkMode){
        case WORK_MODE_READY_FOR_TESTING:{
            DACFrequency = GV.UserDefinedModeParams._modeFreq;
            switch (userDefinedModeParams->state)
            {
            case USER_DEFINED_STRAIN_MODE_STATE_RESET:{
                GV.stopCurrentTestProcess = false;
                //TODO amplitude tune enable if nessesary
                //TODO MAX MIN CALCULATION enable
                this->reset();
                //TODO set nullpoint max min calcs
                dataDecimationCounterDisplacement = GV.DataDecimationCoeff;
                dataDecimationCounterStrain = GV.DataDecimationCoeff;
                break;
            }
            case USER_DEFINED_STRAIN_MODE_STATE_GENERATE:{
                //TODO AMPLITUDE TUNE STATE ENABLE
                //TODO MAX MIN PUSHS

                break;
            }
            case USER_DEFINED_STRAIN_MODE_STATE_EXIT:{
                /* code */
                break;
            }
            default:
                break;
            }
            break;
        }
        default:
            _DACState = prevDACState;
            break;
    }
    //return _DACState;
}