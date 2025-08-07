/*
    Library for calculating Maxs & Mins of periodic signal.
    Created by Grigorii Bragin, October 28, 2021
      ------------------------------------------
        Maxsimums     max____             max____
                        /    \              /    \
                     --/------\------------/------\---------------------
        NullPoint ____/ _   _  \  _   _   / _   _  \  _   _   ____   | NullPoint Window
                                \        /          \        /       |
                     ------------\------/------------\------/-----------
        Minimums               min\____/           min\____/
      ------------------------------------------
*/
#ifndef MAX_MIN_CALCULATION_H
#define MAX_MIN_CALCULATION_H
#include <cfloat>
#include <mbed.h>
#define MAX_MIN_BUFFER_SIZE     128
#define PLUS_INFINITE           FLT_MAX
#define MINUS_INFINITE          -FLT_MAX
#include "..//Trigger/Trigger.h"


enum WaveState{
    WAVESTATE_UNDEFINED,
    WAVESTATE_NULLPOINT,
    WAVESTATE_POSITIVE,
    WAVESTATE_NEGATIVE
};

class MaxMinCalc{
  public:
    MaxMinCalc(void);
    MaxMinCalc(float nullPoint);
    ~MaxMinCalc();
    void pushValue(float value);
    float getLastMaxValue();
    float getLastMinValue();
    float getAverageMaxValue();
    float getAverageMinValue();
    void setNullPoint(float nullPoint);
    void setNullPointWindow(float nullPointWindow);
    void setEdgeValues( float positiveEdgeMax, 
                        float negativeEdgeMax,
                        float positiveEdgeMin,
                        float negativeEdgeMin);
    uint32_t getMaxCount(void);
    uint32_t getMinCount(void);

    void pushWaveState(int state);
    uint32_t getWaveState(void);
    uint32_t getPrevWaveState(void);
    float getLastMax();
    float getLastMin();
    float getLastValue();
  
    
    void reset();
  private:  
    CircularBuffer<float, MAX_MIN_BUFFER_SIZE> _maxs;
    CircularBuffer<float, MAX_MIN_BUFFER_SIZE> _mins;
    float _currentMax = MINUS_INFINITE;
    float _currentMin = PLUS_INFINITE;
    float _nullPoint = 0;
    float _nullPointWindowDelta = 0;
    int _waveState = WAVESTATE_UNDEFINED;
    int _prevWaveState = WAVESTATE_UNDEFINED;
    int _positiveCount = 0;
    int _negativeCount = 0;
    float _positiveEdgeMax = PLUS_INFINITE;
    float _negativeEdgeMax = MINUS_INFINITE;
    float _positiveEdgeMin = PLUS_INFINITE;
    float _negativeEdgeMin = MINUS_INFINITE;
    float _lastMin = 0.0;
    float _lastMax = 0.0;
    float _lastValue = 0.0;
    uint8_t _counterUp = 0;
    uint8_t _counterDown = 0;
    Trigger* upTr = new Trigger(TRIGGER_RISE_EDGE);
    Trigger* downTr = new Trigger(TRIGGER_RISE_EDGE);
    bool _firstPart = false;

};

#endif