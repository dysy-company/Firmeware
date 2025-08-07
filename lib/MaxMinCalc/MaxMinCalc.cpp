#include "MaxMinCalc.h"

MaxMinCalc::MaxMinCalc(void){

}

MaxMinCalc::MaxMinCalc(float nullPoint){
    _nullPoint = nullPoint;
}

MaxMinCalc::~MaxMinCalc(){
    delete upTr;
    delete downTr;
}

void MaxMinCalc::setNullPoint(float nullPoint){
    _nullPoint = nullPoint;
}

void MaxMinCalc::setNullPointWindow(float nullPointWindow){
    _nullPointWindowDelta = nullPointWindow / 2;
}

void MaxMinCalc::setEdgeValues( float positiveEdgeMax,
                                float negativeEdgeMax,
                                float positiveEdgeMin,
                                float negativeEdgeMin){
    _positiveEdgeMax = positiveEdgeMax;
    _negativeEdgeMax = negativeEdgeMax;
    _positiveEdgeMin = positiveEdgeMin;
    _negativeEdgeMin = negativeEdgeMin;
}

void MaxMinCalc::reset(){
    _currentMax = MINUS_INFINITE;
    _currentMin = PLUS_INFINITE;
    _waveState = WAVESTATE_UNDEFINED;
    _prevWaveState = WAVESTATE_UNDEFINED;
    _maxs.reset();
    _mins.reset();
    _firstPart = false;
}

float MaxMinCalc::getLastMaxValue(){
    float value = MINUS_INFINITE;
    if(_maxs.pop(value)){
        return value;
    }
    return MINUS_INFINITE;
}

float MaxMinCalc::getLastMinValue(){
    float value = PLUS_INFINITE;
    if(_mins.pop(value)){
        return value;
    }
    return PLUS_INFINITE;
}

float MaxMinCalc::getAverageMaxValue(){
    uint32_t size = _maxs.size();
    if (size){
        float buf = 0;
        float average = 0;
        for (uint32_t i = 0; i < size; i++){
            _maxs.pop(buf);
            average += buf;
        }
        average /= size;
        return average;
    }
    return MINUS_INFINITE;
}

float MaxMinCalc::getAverageMinValue(){
    uint32_t size = _mins.size();
    if (size){
        float buf = 0;
        float average = 0;
        for (uint32_t i = 0; i < size; i++){
            _mins.pop(buf);
            average += buf;
        }
        average /= size;
        return average;
    }
    return PLUS_INFINITE;
}

uint32_t MaxMinCalc::getMaxCount(){
    return _maxs.size();
}

uint32_t MaxMinCalc::getMinCount(){
    return _mins.size();
}

void MaxMinCalc::pushWaveState(int state){
    _waveState = state;
}

uint32_t MaxMinCalc::getWaveState(){
    return _waveState;
}

uint32_t MaxMinCalc::getPrevWaveState(){
    return _prevWaveState;
}

float MaxMinCalc::getLastMax(){
    return _lastMax;
}

float MaxMinCalc::getLastMin(){
    return _lastMin;
}

float MaxMinCalc::getLastValue(){
    return _lastValue;
}

void MaxMinCalc::pushValue(float value){
    if (_waveState == WAVESTATE_POSITIVE){
        upTr->push(true);
        downTr->push(false);
    }else if (_waveState == WAVESTATE_NEGATIVE){
        upTr->push(false);
        downTr->push(true);
    }
    if (!_firstPart && upTr->getState()){
        _firstPart = true;
        _currentMax = MINUS_INFINITE;
        _currentMin = PLUS_INFINITE;
        upTr->push(true);
    }
    else if (!_firstPart && downTr->getState()){
        _firstPart = true;
        _currentMax = MINUS_INFINITE;
        _currentMin = PLUS_INFINITE;
        downTr->push(true);
    }
    
    if (_firstPart){
        if (_waveState == WAVESTATE_POSITIVE && value > _currentMax){
            _currentMax = value;
        }
        else if (_waveState == WAVESTATE_NEGATIVE && value < _currentMin){
            _currentMin = value;
        }
        if (upTr->getState()){
            _mins.push(_currentMin);
            _currentMin = PLUS_INFINITE;
            upTr->push(true);
        }
        else if (downTr->getState()){
            _maxs.push(_currentMax);
            _currentMax = MINUS_INFINITE;
            downTr->push(true);
        }
    }
}