#include "AmplTune.h"

void AmplitudeTune::init(bool start){
    runningState = start;
    amplitudePID = new PID(
            GV.AmplitudePID.Kp,
            GV.AmplitudePID.Ki,
            GV.AmplitudePID.Kd
        );
}

AmplitudeTune::AmplitudeTune(){
    this->init(false);
}
AmplitudeTune::AmplitudeTune(bool start){
    this->init(start);
}
AmplitudeTune::~AmplitudeTune(){
    this->runningState = false;
    delete amplitudePID;
}
void AmplitudeTune::disable(void){
    runningState = false;
}
void AmplitudeTune::enable(void){
    runningState = true;
}
void AmplitudeTune::pushCurrentValue(double value){
    
}
