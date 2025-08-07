/*
    Abstract class describe mode of machine
    Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#ifndef MODE_H
#define MODE_H
#include <mbed.h>

class Mode{
    public:
        Mode();
        virtual ~Mode();
        virtual void start(double &Kp, double &Ki, double &Kd, float &amplitude);
        virtual float process(float &position, double &frequency, double &PIDKp, double &PIDKi, double &PIDKd);
};


#endif