#include "VoltageCalc.h"

VoltageCalculation::VoltageCalculation(){

}

VoltageCalculation::~VoltageCalculation(){

}

void VoltageCalculation::setDisplCoefs(double k, double b){
    this->displK = k;
    this->displB = b;
}

void VoltageCalculation::setStrainCoefs(double k, double b){
    this->strainK = k;
    this->strainB = b;
}

double VoltageCalculation::calcDisplToVoltage(double displVelocity){
    return this->displK * displVelocity + this->displB;
}

double VoltageCalculation::calcStrainToVoltage(double strainVelocity){
    return this->strainK * strainVelocity + this->strainB;
}