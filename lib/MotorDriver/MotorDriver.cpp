#include "MotorDriver.h"

MotorDriver::MotorDriver(int initDirection){
    this->_currentDirection = initDirection;
}

void MotorDriver::init(motorDriverType_t motorDriverType, uint32_t pwmFreq){
    this->_motorDriverType = motorDriverType;
    this->_processBlock = new Semaphore(1);
    this->_pwm = new PWM(250);
    this->_pwm->init(motorDriverType, pwmFreq);
}

void MotorDriver::setParams(
    DigitalOut *enable,
    DigitalOut *clear,
    DigitalOut *cwlimit,
    DigitalOut *ccwlimit,
    std::chrono::microseconds enableDelay,
    std::chrono::microseconds clearDelay,
    std::chrono::microseconds cwlimitDelay,
    std::chrono::microseconds ccwlimitDelay,
    uint8_t enableActiveLevel,
    uint8_t clearActiveLevel,
    uint8_t cwlimitActiveLevel,
    uint8_t ccwlimitActiveLevel
){
    this->enable = enable;
    this->clear = clear;
    this->cwlimit = cwlimit;
    this->ccwlimit = ccwlimit;
    this->enableDelay = enableDelay;
    this->clearDelay = clearDelay;  
    this->cwlimitDelay = cwlimitDelay;
    this->ccwlimitDelay = ccwlimitDelay;
    this->enableActiveLevel = enableActiveLevel;
    this->clearActiveLevel = clearActiveLevel;
    this->cwlimitActiveLevel = cwlimitActiveLevel;
    this->ccwlimitActiveLevel = ccwlimitActiveLevel;
}

MotorDriver::~MotorDriver(){

    delete this->_processBlock;
    delete this->_pwm;
}

motorDriverType_t MotorDriver::getMotorDriverMode(){
    return this->_motorDriverType;
}

void MotorDriver::setPinState(bool state, uint8_t activeLevel, DigitalOut *pin){
    if(state){
        switch (activeLevel)
        {
        case ACTIVE_LEVEL_LOW:
            pin->write(0);
            break;
        case ACTIVE_LEVEL_HIGH:
            pin->write(1);
            break;
        
        default:
            break;
        }
    }else{
       switch (activeLevel)
        {
        case ACTIVE_LEVEL_LOW:
            pin->write(1);
            break;
        case ACTIVE_LEVEL_HIGH:
            pin->write(0);
            break;
        
        default:
            break;
        } 
    }
}

int MotorDriver::invertDirection(int direction){
    if (direction > 0){
        return 0;
    }else{
        return 1;
    }
}

void MotorDriver::setDirection(int direction){
    if((this->_currentDirection > 0 && direction <= 0) ||(this->_currentDirection <= 0 && direction > 0)){
        this->_currentDirection = direction;
    }
}

void MotorDriver::setEnable(bool state){
    this->setPinState(state, this->enableActiveLevel, this->enable);
}

void MotorDriver::setCLR(bool state){
    this->setPinState(state, this->clearActiveLevel, this->clear);
}

void MotorDriver::setCWLimit(bool state){
    this->setPinState(state, this->cwlimitActiveLevel, this->cwlimit);
}

void MotorDriver::setCCWLimit(bool state){
    this->setPinState(state, this->ccwlimitActiveLevel, this->ccwlimit);
}   

void MotorDriver::setSteps(uint32_t stepCount){
    //if(this->_processBlock->try_acquire_for(this->_msSemaphoreAcquireTime)){
        this->_pwm->resetPWM();
        this->_pwm->setPWM(this->_motorDriverType, this->_currentDirection, stepCount);
    //}
}

void MotorDriver::setSteps(int direction, uint32_t stepCount){
    //if(this->_processBlock->try_acquire_for(this->_msSemaphoreAcquireTime)){
        this->_pwm->resetPWM();
        this->_pwm->setPWM(this->_motorDriverType, direction, stepCount);
    //}
}

void MotorDriver::enableEnd(){
    this->_processBlock->release();
}