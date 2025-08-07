/*
    Amplitude Auto Tune Thread
    Created 20-10-2021. By Grigorii Bragin.
*/
#ifndef AMPLITUDE_TUNE_THREAD_H
#define AMPLITUDE_TUNE_THREAD_H

#include <mbed.h>
#include "..//..//include/Global_Variables.h"
#include "..//..//include/Typedefs/Threads_Mail_Types.h"
#include "..//..//lib/BasicElements/BasicElements.h"
#include "..//..//include/Shared_Params.h"
#include "..//..//lib/PID/PID.h"
#include "..//..//lib/MaxMinCalc/MaxMinCalc.h"



extern globalVariables_t GV;
//extern MaxMinCalc displMaxMinCalc;
//extern MaxMinCalc strainMaxMinCalc;



class AmplitudeTuneThread{
    public:
        AmplitudeTuneThread(globalVariables_t *GV, MaxMinCalc *displMaxMinCalc, MaxMinCalc *strainMaxMinCalc, MaxMinCalc *deformationMaxMinCalc);
        ~AmplitudeTuneThread();
        void threadExecute(void);
    private:
        PID *upAmplitudePID;
        PID *downAmplitudePID;
        PID *nullPointPID;

        uint32_t _freq = 200;
        double getRealNullPointOffset(double UpAmplitude, double DownAmplitude, double UpAmplitudeSet, double DownAmplitudeSet);
        void AnySinAmplTune(SIN* modeParams);
        void AmplCorrection(SIN* modeParams, double currentModeNullPoint, MaxMinCalc* currentMinMaxCalc, double minValueForNullPoint);

        uint32_t riseStepUpCounter;
        uint32_t riseStepDownCounter;
        uint32_t fallStepDownCounter;
        uint32_t fallStepUpCounter;
        uint32_t riseStepCounter;
        uint32_t riseSteps;
        uint32_t fallStepCounter;
        uint32_t fallSteps;
        bool start;
        bool stop;
        double currentUpAmplitude;
        double currentDownAmplitude;
        double riseStepUpAmplitude;
        double riseStepDownAmplitude;
        double fallStepUpAmplitude;
        double fallStepDownAmplitude;

        globalVariables_t *GV; 
        MaxMinCalc *displMaxMinCalc; 
        MaxMinCalc *strainMaxMinCalc;
        MaxMinCalc *deformationMaxMinCalc;
};

#endif