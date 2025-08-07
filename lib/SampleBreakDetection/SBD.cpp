#include "SBD.h"

void SampleBreakDetection::setEnable(uint8_t state){
    this->_state = state;
}

SampleBreakDetection::SampleBreakDetection(){
    _mode = SBD_MODE_PERCENT_OF_MAX_STRAIN;
    _Fstart = 0;
    _procentOfMaxStrain = 5;
    _maxStrain = 0;
    _tensionDirection = 1;
    _initialStrain = 0;
    _firstBlood = false;
    _sampleBreakStatusCounter = 0;
    _threshold = 3;
    _Time = 0us;
    _state = SAMPLE_BREAK_DETECTION_ENABLE;
}

SampleBreakDetection::SampleBreakDetection(uint8_t mode){
    _mode = mode;
    _Fstart = 0;
    _procentOfMaxStrain = 5;
    _maxStrain = 0;
    _tensionDirection = 1;
    _initialStrain = 0;
    _firstBlood = false;
    _sampleBreakStatusCounter = 0;
    _threshold = 3;
    _Time = 0us;
    _state = SAMPLE_BREAK_DETECTION_ENABLE;
}

SampleBreakDetection::~SampleBreakDetection(){

}

void SampleBreakDetection::init(uint8_t mode, int tensionDirection, float currentStrainValue){
    this->_mode = mode;
    this->_tensionDirection = tensionDirection;
    if(this->_tensionDirection > 0){
        this->_maxStrain = DBL_MIN;
        this->_prevValue = DBL_MIN;
    }
    else{
        this->_maxStrain = DBL_MAX;
        this->_prevValue = DBL_MAX;
    }
    this->_dynamicFallState = SBD_DYNAMIC_FALL_STATE_INIT;
    this->_initialStrain = currentStrainValue;
    this->_firstBlood = false;
    this->_valueSign = false;
    this->_sampleBreakStatusCounter = 0;
}

void SampleBreakDetection::setModeParams(double procentOfMaxStrain, double Fstart, uint32_t threshold){
    this->_procentOfMaxStrain = procentOfMaxStrain / 100;
    this->_Fstart = Fstart;
    this->_threshold = threshold;
}

void SampleBreakDetection::setModeParams(double procentOfMaxStrain, double Fstart, std::chrono::microseconds Time){
    this->_procentOfMaxStrain = procentOfMaxStrain / 100;
    this->_Fstart = Fstart;
    this->_SBDTime = Time;
}

void SampleBreakDetection::setModeParams(double procentOfMaxStrain, double Fstart, uint32_t threshold, globalVariables_t *globalVariables){
    this->_procentOfMaxStrain = procentOfMaxStrain / 100;
    this->_Fstart = Fstart;
    this->_threshold = threshold;
    this->_globalVariables = globalVariables;
}

SBDStatus_t SampleBreakDetection::process(float value, bool valueSign){
    SBDStatus_t status = SBD_STATUS_OK;
    if(this->_state != SAMPLE_BREAK_DETECTION_DISABLE){
        switch (this->_mode)
        {
        
        case SBD_MODE_DYNAMIC_FALL:{
        
        //start
        if(value >= this->_Fstart){
            switch (this->_dynamicFallState)
            {
            case SBD_DYNAMIC_FALL_STATE_INIT:
                if(this->_tensionDirection > 0){
                    this->_maxStrain = DBL_MIN;
                    this->_prevValue = DBL_MIN;
                }
                else{
                    this->_maxStrain = DBL_MAX;
                    this->_prevValue = DBL_MAX;
                }
                this->_dynamicFallState = SBD_DYNAMIC_FALL_STATE_WAIT_FALL;
                break;
            case SBD_DYNAMIC_FALL_STATE_WAIT_FALL:
                if(value >= this->_prevValue){
                    
                }
                else{
                    this->_startTime = SystemTimer.elapsed_time();
                    
                    this->_maxStrain = this->_prevValue;
                    this->_dynamicFallState = SBD_DYNAMIC_FALL_STATE_FALL;
                    //if(value < this->_maxStrain - this->_maxStrain * this->_procentOfMaxStrain){
                        //status = SBD_STATUS_BREAK_DYNAMIC_FALL;
                        //}    
                }
                break;
            case SBD_DYNAMIC_FALL_STATE_FALL:{
                std::chrono::microseconds Time_Now = SystemTimer.elapsed_time(); //duration_cast<milliseconds>(SystemTimer.elapsed_time().count());
                this->_Time = Time_Now - this->_startTime;
                if(this->_Time >= this->_SBDTime){
                    if(value > this->_maxStrain){
                        this->_dynamicFallState = SBD_DYNAMIC_FALL_STATE_WAIT_FALL;
                    }else{
                        if(value < this->_maxStrain - this->_maxStrain * this->_procentOfMaxStrain){
                            status = SBD_STATUS_BREAK_DYNAMIC_FALL;
                        }
                        else
                        {
                            this->_dynamicFallState = SBD_DYNAMIC_FALL_STATE_WAIT_FALL;
                        }
                    }
                }else{

                }
                break;
            }    
            default:
                break;
            }
            
        }else{

        }
        this->_prevValue = value;
        return status;
        break;
    }
        case SBD_MODE_PERCENT_OF_MAX_STRAIN:
            //start detection
            if(value >= this->_Fstart){
                this->_firstBlood = true;
                if(value > this->_maxStrain){
                    this->_maxStrain = value;
                    this->_valueSign = valueSign;
                }
                else{
                    status = checkValueByMaxStrain(value, valueSign);
                }

            }else{
                if(this->_firstBlood){
                    status = checkValueByMaxStrain(value, valueSign);
                }
            }
            break;
        default:
            break;
        }
    }
    return status;
}

SBDStatus_t SampleBreakDetection::checkValueByMaxStrain(float value, bool valueSign){
    if ((value < this->_maxStrain - this->_maxStrain * this->_procentOfMaxStrain) || (valueSign != this->_valueSign)){
        this->_sampleBreakStatusCounter++;
        if(this->_sampleBreakStatusCounter >= this->_threshold){
            return SBD_STATUS_BREAK_MAX_STRAIN;
        }
        return SBD_STATUS_OK;
    }
    else{
        return SBD_STATUS_OK;
    }
}