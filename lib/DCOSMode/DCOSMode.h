/*
	COSMode.h - Library for cosinus mode of machine.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#ifndef DCOSMode_h
#define DCOSMode_h
#include <BasicElements.h>
#include <MCP492x.h>
#include "PID.h"
#include <mbed.h>

class DCOSMode {
public:
    //speed in kB/s
	DCOSMode(MCP492x &DAC, SPI &spiDAC, DigitalOut &directHigh, DigitalOut &reverseHigh);
	~DCOSMode();
    /*  Processing pulse mode;
    */
    void process(float &position, double &frequency);
    /*  Start pulse working mode:
             PID coef:   Kp - proportional coef,
                         Ki - integral coef,
                         Kd - differencial coef;
    */
    void start(double &Kp, double &Ki, double &Kd, float &amplitude);
    /*  Reset mode
    */
    void reset(void);
    
private:
	Shared basic;
    int pulseModeState = PULSE_MODE_STATE_NONE;
    int prevPulseModeState = PULSE_MODE_STATE_NONE;
    PID *pulsePID;
    float DACVoltage = 0;
    MCP492x *DACext;
    SPI *DACSPI;
    DigitalOut *direct, *reverse;
    float nullPosition = 0;
    float _amplitude = 0;
    double desirePosition = 0;
    double currentPosition = 0;
    double correction = 0;
    float calculatedVoltage = 0;
    float calculateVoltage (double &correction, double &frequency);
};
#endif
