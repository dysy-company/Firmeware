#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
#include <mbed.h>
#include "..//PWM//PWM.h"

#define MOTOR_DRIVER_TYPE_UNDEFINED     0x00000000
#define MOTOR_DRIVER_TYPE_STEP_DIR      0x00000001
#define MOTOR_DRIVER_TYPE_CW_CCW        0x00000002

#define ACTIVE_LEVEL_LOW   0x00
#define ACTIVE_LEVEL_HIGH  0x01

extern Timer SystemTimer;

typedef uint32_t motorDriverType_t;

class MotorDriver{
    public:
        MotorDriver(int initDirection);
        ~MotorDriver();
        void init(motorDriverType_t motorDriverType, uint32_t pwmFreq);

        void setParams(
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
        );

        void setSteps(uint32_t stepCount);
        void setSteps(int direction, uint32_t stepCount);
        void setDirection(int direction);
        void setEnable(bool state);
        void setCLR(bool state);
        void clearPulses();
        void setCWLimit(bool state);
        void setCCWLimit(bool state);
        motorDriverType_t getMotorDriverMode();

    private:
        motorDriverType_t _motorDriverType;
        PWM *_pwm;
        Semaphore *_processBlock;
        std::chrono::milliseconds _msSemaphoreAcquireTime = 1ms;

        Timeout enableEndTimeout;
        Timeout clearEndTimeout;
        Timeout cwlimitEndTimeout;
        Timeout ccwlimitEndTimeout;

        DigitalOut *enable;
        DigitalOut *clear;
        DigitalOut *cwlimit;
        DigitalOut *ccwlimit;
        std::chrono::microseconds enableDelay;
        std::chrono::microseconds clearDelay;
        std::chrono::microseconds cwlimitDelay;
        std::chrono::microseconds ccwlimitDelay;
        uint8_t enableActiveLevel;
        uint8_t clearActiveLevel;
        uint8_t cwlimitActiveLevel;
        uint8_t ccwlimitActiveLevel;

        int _currentDirection;
        void setPinState(bool state, uint8_t activeLevel, DigitalOut *pin);
        int invertDirection(int direction);
        //handles
        // void pulseEnd();
        // void pauseEnd();
        // // void dirDelayEnd();
        void enableEnd();
};


#endif