#include "Trigger.h"

Trigger::Trigger(int triggerType){
    _triggerType = triggerType;
}

Trigger::~Trigger(){

}

bool Trigger::push(bool currentState){
    _prevState = _currentState;
    _currentState = currentState;
    switch (_triggerType)
    {
    case TRIGGER_RISE_EDGE:
        if (!_prevState && _currentState){
            _triggerState = true;
        }else{
            _triggerState = false;
        }
        break;
    case TRIGGER_FALL_EDGE:
        if (_prevState && !_currentState){
            _triggerState = true;
        }else{
            _triggerState = false;
        }
        break;
    default:
        break;
    }
    return _triggerState;
}

bool Trigger::getState(){
    return _triggerState;
}