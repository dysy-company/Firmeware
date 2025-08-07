#include "ADCsT.h"
/*
static CurrentADC currentADC = SSICurrent;

void ADCs_Acquisition_Thread (void){
    ADCMCP3201.init();
    SensorTM_t sensorsTM;
    float w = 0;
    while (1)
    {
        Watchdog::get_instance().kick();
        if(GV.EnabledAcq & ACQ_SENSORS_TM){   
            switch (currentADC)
            {
            case SSICurrent:
                ADCMCP3201.setCSPin(GPIO_PIN_12,GPIOF);//PF_12
                ADCMCP3201.clearTransferStatus();
                ADCMCP3201.startGettingCode();
                break;
            case StrainSenseCurrent:
                ADCMCP3201.setCSPin(GPIO_PIN_13,GPIOF);//PF_13
                ADCMCP3201.clearTransferStatus();
                ADCMCP3201.startGettingCode();
                break;
            case CoilCurrent:
                ADCMCP3201.setCSPin(GPIO_PIN_14,GPIOF);//PF_14
                ADCMCP3201.clearTransferStatus();
                ADCMCP3201.startGettingCode();
                break;
            case StrainSenseVoltage:
                ADCMCP3201.setCSPin(GPIO_PIN_15,GPIOF);//PF_15
                ADCMCP3201.clearTransferStatus();
                ADCMCP3201.startGettingCode();
                break;
    
            default:
                break;
            }
        }
        ThisThread::sleep_for(100ms);
        if(GV.EnabledAcq & ACQ_SENSORS_TM){
            if(ADCMCP3201.getTransferStatus() == MCP3201_DMA_SPI_TRANSFER_COMPLETE){
                switch (currentADC)
                {
                case SSICurrent:
                    //GV.SensorTM.DisplSensorCurrent = 0.1 * ADCMCP3201.getVoltageBlocking();//ADCMCP3201.getLastVoltage();////
                    currentADC = StrainSenseCurrent;
                    if (GV.TestSignalInfo.type){
                        sensorsTM.DisplSensorCurrent = cos(w) + 1;
                        w += 0.1;
                    }
                    else{
                        sensorsTM.DisplSensorCurrent = GV.SensorTM.DisplSensorCurrent;
                    }
                    break;
                case StrainSenseCurrent:
                    //GV.SensorTM.StrainSensorCurrent = 50 * ADCMCP3201.getVoltageBlocking();//ADCMCP3201.getLastVoltage();
                    currentADC = CoilCurrent;
                    if (GV.TestSignalInfo.type){
                        sensorsTM.StrainSensorCurrent = cos(w) + 1;
                        w += 0.1;
                    }
                    else{
                        sensorsTM.StrainSensorCurrent = GV.SensorTM.StrainSensorCurrent;
                    }
                    break;
                case CoilCurrent:
                    //GV.SensorTM.CoilCurrent = 20 * ADCMCP3201.getVoltageBlocking();//ADCMCP3201.getLastVoltage();
                    currentADC = StrainSenseVoltage;
                    if (GV.TestSignalInfo.type){
                        sensorsTM.CoilCurrent = cos(w) + 1;
                        w += 0.1;
                    }
                    else{
                        sensorsTM.CoilCurrent = GV.SensorTM.CoilCurrent;
                    }
                    break;
                case StrainSenseVoltage:
                    //GV.SensorTM.StrainSensorVoltage = 5 * ADCMCP3201.getVoltageBlocking();//ADCMCP3201.getLastVoltage();
                    currentADC = SSICurrent;
                    if (GV.TestSignalInfo.type){
                        sensorsTM.StrainSensorVoltage = cos(w) + 1;
                        w += 0.1;
                    }
                    else{
                        sensorsTM.StrainSensorVoltage = GV.SensorTM.StrainSensorVoltage;
                    }
                    ADCTMBuffer.push(sensorsTM);
                    break;
    
                default:
                    currentADC = SSICurrent;
                    break;
                }
            }
        }
        //ThisThread::sleep_for(400ms);
    }
    
}*/