/*
    Library for simple PID Regulator.
    Created by Grigorii Bragin, March 1, 2020
*/
#ifndef PID_h
#define PID_h

#include <mbed.h>

class PID {

    public:
        /*  PID Regulator class constructor:
                Kp - proportional coef, Ki - integral coef, Kd - differential coef
            */
        PID(double &_Kp, double &_Ki, double &_Kd);
        /*  PID Regulator class constructor:
                Kp = 1, Ki = 0, Kd = 0;
            */
        PID();
        ~PID();
        /*  PID Regulator correction calculation   */
        double getCorrection(double &desireValue, double &currentValue);
        /*  PID Regulator coef setting  */
        void setCoefs(double &Kp, double &Ki, double &Kd);
        /*  PID Regulator reset */
        void reset(void);
    private:
        /*  Proportional coef   */
        double Kp = 0;
        /*  Integral coef   */
        double Ki = 0;
        /*  Differential coef   */
        double Kd = 0;
        /*  Calculation value   */
        double U = 0;
        /*  Accumulator value   */
        double I = 0;
        /*  Error value */
        double E = 0;
        /*  Previous error value    */
        double Eprev = 0;

       
};
#endif