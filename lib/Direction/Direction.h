/*
	PulseMode.h - Library for pulse mode of machine.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#ifndef Direction_h
#define Direction_h

#include <mbed.h>
#include "..//..//include//Global_Variables.h"

class Direction {
public:
    
	Direction(DigitalOut &directHigh, DigitalOut &reverseHigh, globalVariables_t *globalVariables);
	~Direction();
    /*  Processing pulse mode;
    */

    void set(long direction);
	void setWithCorrection(double correction);
	int  calculateBoolDirection(long direction);
    
private:
	globalVariables_t *_globalVariables;
    DigitalOut *direct, *reverse;
};
#endif
