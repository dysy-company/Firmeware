#ifndef LIMITSWITCH_h
#define LIMITSWITCH_h

#include <mbed.h>
#include "..//..//include//Global_Variables.h"
#include "..//..//include//Shared_Params.h"

// #define LIMIT_SWITCH_TYPE_UNDEFINED     0x00
// #define LIMIT_SWITCH_TYPE_ONE           0x01
// #define LIMIT_SWITCH_TYPE_TWO           0x02 

#define LIMIT_SWITVH_UP                 0x00
#define LIMIT_SWITCH_DOWN               0x01

class LimitSwitch{
    public:
        LimitSwitch(
            int limitSwitchPolarity1,
            int limitSwitchPolarity2,
            uint8_t LimitSwitchType,
            InterruptIn *switch1,
            InterruptIn *switch2
        );
        LimitSwitch(
            int limitSwitchPolarity1,
            uint8_t LimitSwitchType,
            InterruptIn *switch1
        );
        ~LimitSwitch();

        void setLimSwFunc(
            Callback<void()> func1, 
            Callback<void()> func2
        );
        void setLimSwFunc(
            Callback<void()> func1,
            Callback<void()> func2,
            Callback<void()> func3,
            Callback<void()> func4
        );
        uint8_t getLimitSwitchType();
        bool getState();

        void disableIrq();
        void enableIrq();

    private:
        int _limitSwitchPolarity1 = true;
        int _limitSwitchPolarity2 = true;
        uint8_t _LimitSwitchType;
        InterruptIn *_switch1;
        InterruptIn *_switch2;

};
#endif