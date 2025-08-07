/*
            This class used for physical protect of sample
*/
#ifndef PROTECT_H
#define PROTECT_H

#include <mbed.h>

#define PROTECT_STATUS_NOT_DEFINED                              0xFFFF
#define PROTECT_STATUS_NORMAL                                   0x0000
#define PROTECT_STATUS_OVERRUN                                  0x0001
#define PROTECT_STATUS_UNDERRUN                                 0x0002

#define PROTECT_MODE_DISABLE                                    0x0000
#define PROTECT_MODE_ONE_VALUE                                  0x0001
#define PROTECT_MODE_CONTINIUS                                  0x0002

#define LIMIT_REACH_STATUS_DISPLACEMENT                         0x0001
#define LIMIT_REACH_STATUS_STRAIN                               0x0003
#define LIMIT_REACH_STATUS_DEFORMATION                          0x0005

class Protect{
    public:
        //mode disable
        Protect();
        //mode one value
        Protect(float upperLimit, float lowerLimit);
        //mode continius
        Protect(float upperLimit, float lowerLimit, int valuesCount);
        ~Protect();
        int process(float currentValue);
        void setLimits(float upperLimit, float lowerLimit);
        void setUpperLimit(float upperLimit);
        void setLowerLimit(float lowerLimit);
        void setMode(int mode);
        void setValuesCount(int count);
        void clearStatus();
        int getPrevStatus();
		float getUpperLimit() { return _upperLimit; }
		float getLowerLimit() { return _lowerLimit; }
		int getMode() { return _mode; }
        us_timestamp_t lastNotification = 0;
    private:
        int _valuesCount = 4;
        int _currentUpperCount = 0;
        int _currentLowerCount = 0;
        int _mode = PROTECT_MODE_DISABLE;
        float _upperLimit = __FLT_MAX__;
        float _lowerLimit = -__FLT_MAX__;
        int _status = PROTECT_STATUS_NOT_DEFINED;
        int _prevStatus = PROTECT_STATUS_NOT_DEFINED;

};

#endif