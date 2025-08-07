#ifndef AMPLITUDE_TUNE_H
#define AMPLITUDE_TUNE_H

#include <mbed.h>
#include "PID.h"
#include "Global_Variables.h"

extern Timer SystemTimer;
extern globalVariables_t GV;


class AmplitudeTune{
    public:
        AmplitudeTune();
        AmplitudeTune(bool start);
        void pushCurrentValue(double value);
        double getMaxValue(void);
        double getMinValue(void);
        void enable(void);
        void disable(void);
    private:
        void init(bool start);
        bool runningState;
        double maxValue;
        double minValue;
        PID *amplitudePID;
};

#endif