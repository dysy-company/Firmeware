/*
	DCOSMode.h - Library for set displacement cosinus mode.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#include <DCOSMode.h>
 
PulseMode::PulseMode(MCP492x &DAC, SPI &spiDAC, DigitalOut &directHigh, DigitalOut &reverseHigh){
    pulseModeState = PULSE_MODE_STATE_NONE;
    DACext = &DAC;
    DACSPI = &spiDAC;
    direct = &directHigh;
    reverse = &reverseHigh;
    pulsePID = new PID();
}

PulseMode::~PulseMode(){
    pulseModeState = PULSE_MODE_STATE_NONE;
    pulsePID->reset();
    delete pulsePID;
}

void PulseMode::start(double &Kp, double &Ki, double &Kd, float &amplitude){
    pulseModeState = PULSE_MODE_STATE_MOVING;
    prevPulseModeState = PULSE_MODE_STATE_NONE;
    pulsePID->setCoefs(Kp, Ki, Kd);
    pulsePID->reset();
    _amplitude = amplitude;
}

void PulseMode::reset(){
    pulseModeState = PULSE_MODE_STATE_NONE;
    pulsePID->reset();
}

float PulseMode::calculateVoltage(double &correction, double &frequency){
    calculatedVoltage = (correction / (6.773 * (frequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
    return calculatedVoltage;
}

void PulseMode::process(float &position, double &frequency){
    int bufferedModeState = pulseModeState;
    switch (pulseModeState)
    {
    case PULSE_MODE_STATE_NONE:
        DACVoltage = 0;
        direct->write(0);
        reverse->write(0);
        break;

    case PULSE_MODE_STATE_MOVING:
        if(pulseModeState != prevPulseModeState){
            pulsePID->reset();
            nullPosition = position;
            /*if (movementDirection > 0){
                direct->write(1);
                reverse->write(0);
            }
            if(movementDirection < 0){
                direct->write(0);
                reverse->write(1);
            }*/
            currentPosition = position;
            desirePosition = nullPosition + _amplitude;
            correction = pulsePID->getCorrection(desirePosition, currentPosition);
            DACVoltage = calculateVoltage(correction, frequency);
        }
        else{
            currentPosition = position;
            correction = pulsePID->getCorrection(desirePosition, currentPosition);
            DACVoltage = calculateVoltage(correction, frequency);
        }
        break;

    case PULSE_MODE_STATE_HOLDING:
        
        break;
    
    default:
        break;
    }
    DACext->setVoltage(*DACSPI, DACVoltage);
    prevPulseModeState = bufferedModeState;
}