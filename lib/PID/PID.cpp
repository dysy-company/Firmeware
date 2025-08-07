#include "PID.h"

PID::PID(double &_Kp, double &_Ki, double &_Kd){
    I = 0;
    Eprev = 0;
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
}

//create PID with
PID::PID(){
    I = 0;
    Eprev = 0;
    Kp = 1;
    Ki = 0;
    Kd = 0;
}

//destroy PID
PID::~PID(){
  
}

double PID::getCorrection(double &desireValue, double &currentValue){
    E = desireValue - currentValue;
    U = 0;
    if (Ki)
    {
      U = I + Ki * E;
      I = U;
    }
    if (Kp)
    {
      U += Kp * E;
    }
    if (Kd)
    {
      U += Kd * (E - Eprev);
      Eprev = E;
    }
    return U;
}

void PID::setCoefs(double &_Kp, double &_Ki, double &_Kd){
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
}

void PID::reset(void){
    I = 0;
    Eprev = 0;
}