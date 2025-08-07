#include "Protect.h"

Protect::Protect(){

}

Protect::Protect(float upperLimit, float lowerLimit){
    _upperLimit = upperLimit;
    _lowerLimit = lowerLimit;
    _mode  = PROTECT_MODE_ONE_VALUE;
}

Protect::Protect(float upperLimit, float lowerLimit, int valuesCount){
    _upperLimit = upperLimit;
    _lowerLimit = lowerLimit;
    _valuesCount = valuesCount;
    _mode  = PROTECT_MODE_DISABLE;
}

Protect::~Protect(){

}

void Protect::setLimits(float upperLimit, float lowerLimit){
    _upperLimit = upperLimit;
    _lowerLimit = lowerLimit;
}

void Protect::setUpperLimit(float upperLimit){
    _upperLimit = upperLimit;
}

void Protect::setLowerLimit(float lowerLimit){
    _lowerLimit = lowerLimit;
}

void Protect::setMode(int mode){
    _mode = mode;
}

void Protect::setValuesCount(int count){
    _valuesCount = count;
}

int Protect::process(float currentValue){
    switch (_mode)
    {
    case PROTECT_MODE_DISABLE:
        _prevStatus = _status;
        _status = PROTECT_STATUS_NORMAL;
        break;
    case PROTECT_MODE_ONE_VALUE:
        _prevStatus = _status;
        if (currentValue >= _upperLimit){
            _status = PROTECT_STATUS_OVERRUN;
        }
        if (currentValue <= _lowerLimit){
            _status = PROTECT_STATUS_UNDERRUN;
        }
        break;
    case PROTECT_MODE_CONTINIUS:
        _prevStatus = _status;
        if (currentValue >= _upperLimit){
            _currentUpperCount++;
            _currentLowerCount = 0;
            if (_currentUpperCount >= _valuesCount){
                _status = PROTECT_STATUS_OVERRUN;
            }else{
                _status = PROTECT_STATUS_NORMAL;
            }
        }else{
            if (currentValue <= _lowerLimit){
                _currentLowerCount++;
                _currentUpperCount = 0;
                if (_currentLowerCount >= _valuesCount){
                    _status = PROTECT_STATUS_UNDERRUN;
                }else{
                    _status = PROTECT_STATUS_NORMAL;
                }
            }else{
                _status = PROTECT_STATUS_NORMAL;
                _currentUpperCount = 0;
                _currentLowerCount = 0;
            }
        }
        break;
    default:
        _prevStatus = _status;
        _status = PROTECT_STATUS_NOT_DEFINED;
        break;
    }
    return _status;
}

void Protect::clearStatus(){
    _prevStatus = _status;
    _status = PROTECT_STATUS_NOT_DEFINED;
}

int Protect::getPrevStatus(){
    return _prevStatus;
}