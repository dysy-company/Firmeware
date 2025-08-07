#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(
    int limitSwitchPolarity1,
    int limitSwitchPolarity2,
    uint8_t LimitSwitchType,
    InterruptIn *switch1,
    InterruptIn *switch2
){
    this->_limitSwitchPolarity1 = limitSwitchPolarity1;
    this->_limitSwitchPolarity2 = limitSwitchPolarity2;
    this->_LimitSwitchType = LimitSwitchType;
    this->_switch1 = switch1;
    this->_switch2 = switch2;
}

LimitSwitch::LimitSwitch(
    int limitSwitchPolarity1,
    uint8_t LimitSwitchType,
    InterruptIn *switch1
){
    this->_limitSwitchPolarity1 = limitSwitchPolarity1;
    this->_LimitSwitchType = LimitSwitchType;
    this->_switch1 = switch1;
}

LimitSwitch::~LimitSwitch(){

}

void LimitSwitch::setLimSwFunc(Callback<void()> func1, Callback<void()> func2){
    switch (this->_LimitSwitchType)
    {
    case LIMIT_SWITCH_TYPE_ONE:
        if(this->_limitSwitchPolarity1){
            this->_switch1->rise(func1);
            this->_switch1->fall(func2);
        }else{
            this->_switch1->fall(func1);
            this->_switch1->rise(func2);
        }
        break;
    case LIMIT_SWITCH_TYPE_TWO:
        if(this->_limitSwitchPolarity1){
            this->_switch1->rise(func1);
            this->_switch1->fall(func2);
        }else{
            this->_switch1->fall(func1);
            this->_switch1->rise(func2);
        }
        if(this->_limitSwitchPolarity2){
            this->_switch2->rise(func1);
            this->_switch2->fall(func2);
        }else{
            this->_switch2->fall(func1);
            this->_switch2->rise(func2);
        }
        break;
    default:
        break;
    }
}

void LimitSwitch::setLimSwFunc(Callback<void()> func1, Callback<void()> func2, Callback<void()> func3, Callback<void()> func4){
    if(this->_limitSwitchPolarity1){
        this->_switch1->rise(func1);
        this->_switch1->fall(func2);
    }else{
        this->_switch1->fall(func1);
        this->_switch1->rise(func2);
    }
    if(this->_limitSwitchPolarity2){
        this->_switch2->rise(func3);
        this->_switch2->fall(func4);
    }else{
        this->_switch2->fall(func3);
        this->_switch2->rise(func4);
    }
}

uint8_t LimitSwitch::getLimitSwitchType(){
    return this->_LimitSwitchType;
}

bool LimitSwitch::getState(){
    bool state1;
    bool state2;
    bool state;
    switch (this->_LimitSwitchType)
    {
    case LIMIT_SWITCH_TYPE_ONE:
        if(this->_limitSwitchPolarity1){
            state = this->_switch1->read();
        }else{
            state = !this->_switch1->read();
        }   
        break;
    case LIMIT_SWITCH_TYPE_TWO:
        if(this->_limitSwitchPolarity1){
            state1 = this->_switch1->read();
        }else{
            state1 = !this->_switch1->read();
        }
        if(this->_limitSwitchPolarity2){
            state2 = this->_switch2->read();
        }else{
            state2 = !this->_switch2->read();
        }
        state = state1 | state2;
        break;
    default:
        state = false;
        break;
    }
    return state;
}

void LimitSwitch::disableIrq(){
    #if (LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_5V || LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_UNDEFINED)
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    #else
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    #endif
}

void LimitSwitch::enableIrq(){
    #if (LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_5V || LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_UNDEFINED)
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    #else
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
    #endif
}