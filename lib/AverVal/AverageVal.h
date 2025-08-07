#ifndef AVERAGE_VALUE_H
#define AVERAGE_VALUE_H
#include <mbed.h>

#define AVERAGING_STATUS_OFF            0
#define AVERAGING_STATUS_IN_PROGRESS    1
#define AVERAGING_STATUS_READY          2
#define AVERAGING_STATUS_COMPLETE       3

class AverageValue{
    private:
        float _sum = 0;
        int _numberOfValues = 0;
        int _count = 0;
        float _value = 0;
        int _status = AVERAGING_STATUS_OFF;
        int _completeCount = 0;
        //calculate average value and return calculated value
        float calculate();
    public:
        AverageValue();
        ~AverageValue();
        //0-Averaging off, 1-averaging in progress, 2-averaging ready, 3-averaging complete
        int getStatus();
        void setNumberOfValues(int numberOfValues);
        int getNumberOfValues();
        //return average value without calculating
        float get();
        //return counter value
        int getCount();
        //setup average value without calculating
        void set(float value);
        //add value to sum and calculate, return status of averaging
        int push(float value);
        //reset averaging process
        void reset();
        //get count of complete calculations
        int getCompleteCount();
        
};

#endif