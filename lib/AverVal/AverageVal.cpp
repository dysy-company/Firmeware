#include "AverageVal.h"

AverageValue::AverageValue(){
}

AverageValue::~AverageValue(){

}

//get average value
float AverageValue::get(){
    return _value;
}

//calculate average value and complete status
float AverageValue::calculate(){
    _value = _sum / _count;
    _sum = 0;
    _count = 0;
    _status = AVERAGING_STATUS_COMPLETE;
    _completeCount++;
    return _value;
}

//push value to sum and check count to calculate average value, return current status of averaging
int AverageValue::push(float value){
    _sum += value;
    _count++;
    if (_count >= _numberOfValues){
        this->calculate();
    }else{
        _status = AVERAGING_STATUS_IN_PROGRESS;
    }
    return _status;
}

//get current count of values
int AverageValue::getCount(){
    return _count;
}

//overwrite current average value
void AverageValue::set(float value){
    _value = value;
}

//get status of averaging
int AverageValue::getStatus(){
    return _status;
}

//set number of values to average
void AverageValue::setNumberOfValues(int numberOfValues){
    _numberOfValues = numberOfValues;
}

//get number of values to average
int AverageValue::getNumberOfValues(){
    return _numberOfValues;
}

//reset averaging process
void AverageValue::reset(){
    _sum = 0;
    _count = 0;
    _status = AVERAGING_STATUS_IN_PROGRESS;
    _completeCount = 0;
}

//get complete calculations count
int AverageValue::getCompleteCount(){
    return _completeCount;
}