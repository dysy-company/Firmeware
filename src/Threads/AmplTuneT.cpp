#include "AmplTuneT.h"

// void Amplitude_Tune_Thread(void){
//     AmplitudeTuneThread *execution = new AmplitudeTuneThread();
//     execution->execute();
// }

AmplitudeTuneThread::AmplitudeTuneThread(globalVariables_t *GV, MaxMinCalc *displMaxMinCalc, MaxMinCalc *strainMaxMinCalc, MaxMinCalc *deformationMaxMinCalc){
    this->GV = GV;
    this->displMaxMinCalc = displMaxMinCalc;
    this->strainMaxMinCalc = strainMaxMinCalc;
    this->deformationMaxMinCalc = deformationMaxMinCalc;
    this->upAmplitudePID = new PID();
    this->downAmplitudePID = new PID();
    this->nullPointPID = new PID();
}

AmplitudeTuneThread::~AmplitudeTuneThread(){
    delete this->upAmplitudePID;
    delete this->downAmplitudePID;
    delete this->nullPointPID;
}

void AmplitudeTuneThread::threadExecute(){ 
    while(1){
        switch (GV->Mode)
        {
        case DAC_STATE_DISP_SIN:{
            this->AnySinAmplTune(&GV->SINDisplacementModeParams);
            break;
        }
        case DAC_STATE_STRAIN_SIN:{
            this->AnySinAmplTune(&GV->SINStrainModeParams);
            break;
        }
        case DAC_STATE_DEFORMATION_SIN:{
            this->AnySinAmplTune(&GV->SINDeformationModeParams);
            break;
        }
        case DAC_STATE_DISP_SINUS_BASED:{
            this->AnySinAmplTune(&GV->SinusBasedDisplacementModeParams);
            break;
        }
        case DAC_STATE_STRAIN_SINUS_BASED:{
            this->AnySinAmplTune(&GV->SinusBasedStrainModeParams);
            break;
        }
        case DAC_STATE_DEFORMATION_SINUS_BASED:{
            this->AnySinAmplTune(&GV->SinusBasedDeformationModeParams);
            break;
        }
        default:
            _freq = 200;
            break;
        }
        ThisThread::sleep_for(std::chrono::milliseconds(_freq));
    }
}

double AmplitudeTuneThread::getRealNullPointOffset(double UpAmplitude, double DownAmplitude, double UpAmplitudeSet, double DownAmplitudeSet){
    GV->nominalBothAmplAndSetBothAmplRatio = (UpAmplitude + DownAmplitude) / (UpAmplitudeSet + DownAmplitudeSet);
    double normalizedUpAmplitude = UpAmplitudeSet * GV->nominalBothAmplAndSetBothAmplRatio;
    double normalizedDownAmplitude = DownAmplitudeSet * GV->nominalBothAmplAndSetBothAmplRatio;
    double result = 0.0;
    result = ((UpAmplitude * normalizedDownAmplitude) - (DownAmplitude * normalizedUpAmplitude)) / (UpAmplitude + DownAmplitude);
    return result;
}

void AmplitudeTuneThread::AnySinAmplTune(SIN* modeParams){
    _freq = modeParams->amplitudeTuneInfo.freq;
    switch (modeParams->amplitudeTuneInfo.state)
    {
        case AMPLITUDE_TUNE_STATE_DISABLE:
            break;
        case AMPLITUDE_TUNE_STATE_ENABLE:
            break;
        case AMPLITUDE_TUNE_STATE_INIT:{

            this->upAmplitudePID->reset();
            this->upAmplitudePID->setCoefs( modeParams->amplitudeTuneInfo.UpKP,
                                            modeParams->amplitudeTuneInfo.UpKI,
                                            modeParams->amplitudeTuneInfo.UpKD);
            this->downAmplitudePID->reset();
            this->downAmplitudePID->setCoefs(   modeParams->amplitudeTuneInfo.DownKP,
                                                modeParams->amplitudeTuneInfo.DownKI,
                                                modeParams->amplitudeTuneInfo.DownKD);
            this->nullPointPID->reset();
            this->nullPointPID->setCoefs(   modeParams->amplitudeTuneInfo.NullPointKP,
                                            modeParams->amplitudeTuneInfo.NullPointKI,
                                            modeParams->amplitudeTuneInfo.NullPointKD);

            modeParams->amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_CORRECTION;
            
            //calculating steps
            
            riseStepUpAmplitude = modeParams->UpAmplitude / modeParams->amplitudeTuneInfo.amplitudeRiseCycles;
            riseStepDownAmplitude = modeParams->DownAmplitude / modeParams->amplitudeTuneInfo.amplitudeRiseCycles;
            fallStepUpAmplitude = modeParams->UpAmplitude / modeParams->amplitudeTuneInfo.amplitudeFallCycles;
            fallStepDownAmplitude = modeParams->DownAmplitude / modeParams->amplitudeTuneInfo.amplitudeFallCycles;
            riseSteps = modeParams->amplitudeTuneInfo.amplitudeRiseCycles/modeParams->amplitudeTuneInfo.waitCycles;
            fallSteps = modeParams->amplitudeTuneInfo.amplitudeFallCycles/modeParams->amplitudeTuneInfo.waitCycles;
            riseStepUpCounter = modeParams->amplitudeTuneInfo.amplitudeRiseCycles;
            riseStepDownCounter = modeParams->amplitudeTuneInfo.amplitudeRiseCycles;
            fallStepUpCounter = modeParams->amplitudeTuneInfo.amplitudeFallCycles;
            fallStepDownCounter = modeParams->amplitudeTuneInfo.amplitudeFallCycles;
            fallStepCounter = 0;        

            if(modeParams->amplitudeTuneInfo.startProcess){
                currentUpAmplitude = modeParams->UpAmplitude;
                currentDownAmplitude = modeParams->DownAmplitude;
                modeParams->DownAmplitudeSet = modeParams->DownAmplitude * GV->startStopAmplitudeRatio;
                modeParams->UpAmplitudeSet = modeParams->UpAmplitude * GV->startStopAmplitudeRatio;
                GV->prevAmplitudeDownSet = modeParams->DownAmplitudeSet;
                GV->prevAmplitudeUpSet = modeParams->UpAmplitudeSet;
                modeParams->amplitudeTuneInfo.freq = (1/GV->reserveSinMainFrequency) * 1000 * 0.96 * GV->minMaxCalculatingCounts;
                _freq = 1;//ms to next iteration       
            }
            else{
                currentUpAmplitude = modeParams->UpAmplitude;
                currentDownAmplitude = modeParams->DownAmplitude;
                modeParams->DownAmplitudeSet = modeParams->DownAmplitude * GV->startStopAmplitudeRatio;
                modeParams->UpAmplitudeSet = modeParams->UpAmplitude * GV->startStopAmplitudeRatio;
                GV->prevAmplitudeDownSet = modeParams->DownAmplitudeSet;
                GV->prevAmplitudeUpSet = modeParams->UpAmplitudeSet;
                modeParams->amplitudeTuneInfo.freq = (1/modeParams->SINFrequency) * 1000 * 0.96 * GV->minMaxCalculatingCounts;
                _freq = 1;//ms to next iteration
            }
            modeParams->amplitudeTuneInfo.stop = false;
            break;
        }
        case AMPLITUDE_TUNE_STATE_CORRECTION:{
            
            switch(modeParams->amplitudeTuneInfo.correctionType){
                case CORRECTION_TYPE_DISPLACEMENT:{
                    AmplCorrection(modeParams, modeParams->NullPointDisplacement, displMaxMinCalc, GV->minAmplForDisplNullPointAttenuating);
                    break;
                }
                case CORRECTION_TYPE_DEFORMATION:{
                    AmplCorrection(modeParams, modeParams->NullPointDeformation, deformationMaxMinCalc, GV->minAmplForDeformNullPointAttenuating);
                    break;
                }
                case CORRECTION_TYPE_STRAIN:{
                    AmplCorrection(modeParams, modeParams->NullPointStrain, strainMaxMinCalc, GV->minAmplForStrainNullPointAttenuating);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case AMPLITUDE_TUNE_STATE_EXIT:{
            modeParams->amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
            break;
        }
        default:
            break;
    }
}

void AmplitudeTuneThread::AmplCorrection(SIN* modeParams, double currentModeNullPoint, MaxMinCalc* currentMinMaxCalc, double minValueForNullPoint){
    
    if (modeParams->amplitudeTuneInfo.mainProcess || modeParams->amplitudeTuneInfo.startProcess){
        if(currentMinMaxCalc->getMaxCount()){
            double currentAmpl = currentMinMaxCalc->getAverageMaxValue() - currentModeNullPoint;
            if (modeParams->UpAmplitude!=0 && abs(currentAmpl - modeParams->UpAmplitude)/modeParams->UpAmplitude > GV->amplitudePrecision){
                modeParams->UpAmplitudeSet += upAmplitudePID->getCorrection(modeParams->UpAmplitude, currentAmpl);
                GV->nullPointAttenuationCounter++;
            }
            else upAmplitudePID->reset();
            //printf("upSet %f \n", currentAmpl);
        }
        if(currentMinMaxCalc->getMinCount()){
            float avgAmpl = currentMinMaxCalc->getAverageMinValue();
            double currentAmpl = abs(currentModeNullPoint - avgAmpl);
            if (modeParams->DownAmplitude!=0 && abs(currentAmpl - modeParams->DownAmplitude)/modeParams->DownAmplitude > GV->amplitudePrecision){
                modeParams->DownAmplitudeSet += downAmplitudePID->getCorrection(modeParams->DownAmplitude, currentAmpl);
                GV->nullPointAttenuationCounter++;
            }
            else downAmplitudePID->reset();
            //printf("downAmp %f \n", avgAmpl);
        }
        if (!modeParams->amplitudeTuneInfo.startProcess && GV->minMaxCalculatingCountsMainProcess > 0){
            if (GV->minMaxCountsSwitcher < GV->minMaxCountsSwitcherLimit && GV->startStopAmplitudeRatio <= GV->edgeAmplitudeRatioForTuneStepsNumbChange){
                if (GV->preMinMaxCalculatingCountsMainProcess != GV->minMaxCalculatingCounts){
                    GV->preMinMaxCalculatingCountsMainProcess = GV->minMaxCalculatingCounts;
                    modeParams->amplitudeTuneInfo.freq = (1/modeParams->SINFrequency) * 1000 * 0.96 * GV->preMinMaxCalculatingCountsMainProcess;
                    _freq = 1;//ms to next iteration
                }
            }
            else {
                if (GV->preMinMaxCalculatingCountsMainProcess != GV->minMaxCalculatingCountsMainProcess){
                    GV->preMinMaxCalculatingCountsMainProcess = GV->minMaxCalculatingCountsMainProcess;
                    modeParams->amplitudeTuneInfo.freq = (1/modeParams->SINFrequency) * 1000 * 0.96 * GV->preMinMaxCalculatingCountsMainProcess;
                    _freq = 1;//ms to next iteration
                }
            }
        }
    }
    else{
        modeParams->UpAmplitudeSet = modeParams->UpAmplitude;
        modeParams->DownAmplitudeSet = modeParams->DownAmplitude;
    }

    //Null point attenuation
    double ampLower = 0.0;
    double nullPointOffset = 0.0;
    ampLower = modeParams->UpAmplitude <= modeParams->DownAmplitude ? modeParams->UpAmplitude : modeParams->DownAmplitude;
    GV->nullPointAttenuationCounter++;
    if (ampLower >= minValueForNullPoint){                  //GV->minAmplForDisplNullPointAttenuating
        if (GV->nullPointAttenuationCounter > GV->stepForNullPointGetCorrection){
            nullPointOffset = getRealNullPointOffset(modeParams->UpAmplitude, modeParams->DownAmplitude, GV->prevAmplitudeUpSet, GV->prevAmplitudeDownSet);
            double upTargetNullPointOffset = modeParams->UpAmplitude * GV->minDeltaRatioForNullPointAttenuating;
            double downTargetNullPointOffset =  -modeParams->DownAmplitude * GV->minDeltaRatioForNullPointAttenuating;
            if ( nullPointOffset >= upTargetNullPointOffset){
                GV->nullPointDelta += nullPointPID->getCorrection(upTargetNullPointOffset, nullPointOffset);
                this->upAmplitudePID->reset();
                this->downAmplitudePID->reset();
            }
            else if (nullPointOffset <= downTargetNullPointOffset){
                GV->nullPointDelta += nullPointPID->getCorrection(downTargetNullPointOffset, nullPointOffset);
                this->upAmplitudePID->reset();
                this->downAmplitudePID->reset();
            }
            else this->nullPointPID->reset();                                
            GV->nullPointAttenuationCounter = 0;
        }  
    }
}
