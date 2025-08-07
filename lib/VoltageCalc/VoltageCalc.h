/* 
**  This class will be used for convertion velocity mm/s or kN/s to Volts on valve
**  2022, GRIGORII BRAGIN
*/

#ifndef VOLTAGE_CALCULATION_H
#define VOLTAGE_CALCULATION_H

#include <mbed.h>

class VoltageCalculation{
    public:
        VoltageCalculation();
        ~VoltageCalculation();
        double calcDisplToVoltage(double displVelocity);
        double calcStrainToVoltage(double strainVelocity);
        void setDisplCoefs(double k, double b);
        void setStrainCoefs(double k, double b);
        void calDisplCoefs(double velocity1, double RAWValue1, double velocity2, double RAWValue2);
        void calStrainCoefs(double velocity1, double RAWValue1, double velocity2, double RAWValue2);
    private:
        double strainK = 1;
        double displK = 1;
        double strainB = 0;
        double displB = 0;
};

#endif