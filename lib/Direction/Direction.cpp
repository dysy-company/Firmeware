/*
	RSSI.h - Library for getting data from R Series throught SSI interface.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#include <Direction.h>
 
Direction::Direction(DigitalOut &directHigh, DigitalOut &reverseHigh, globalVariables_t *globalVariables){
    direct = &directHigh;
    reverse = &reverseHigh;
    _globalVariables = globalVariables;
}

Direction::~Direction(){
    direct->write(0);
    reverse->write(0);
    _globalVariables->CurrentDirection = 0;
}

int Direction::calculateBoolDirection(long direction){
    if(direction == 0){
        return 0;
    }
    if(direction > 0){
        return 1;   
    }
    if(direction < 0){
        return 0;   
    }
    return 0;
}

void Direction::set(long direction){
    if(direction == 0){
        direct->write(0);
        reverse->write(0);
         _globalVariables->CurrentDirection = 0;    
    }
    if(direction > 0){
        direct->write(1);
        reverse->write(0);
         _globalVariables->CurrentDirection = 1;    
    }
    if(direction < 0){
        direct->write(0);
        reverse->write(1);
         _globalVariables->CurrentDirection = -1;    
    }
}

void Direction::setWithCorrection(double correction){
    if (correction >= 0 ){
      this->set(1);
       _globalVariables->CurrentDirection = 1;
      //directHigh = 1;
      //reverseHigh = 0;
    }
    else {
      this->set(-1);
       _globalVariables->CurrentDirection = -1;
      //directHigh = 0;
      //reverseHigh = 1;
    }
}
