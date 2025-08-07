#include "RefVoltT.h"

void Reference_Voltage_Adjuster (float *setVoltage){
    float _voltage = *setVoltage;
    if(!std::isnan(_voltage)){
        _voltage /= REFERENCE_VOLTAGE_ADJUSTER_VOLTAGE_MULTIPLAYER;
        DACext.setVoltage(_voltage, SS_DAC_CS);
        GV.ReferenceVoltage = *setVoltage;
    }
}

void Reference_Voltage_Adjuster_Extens (float *setVoltage){
    float _voltage = *setVoltage;
    if(!std::isnan(_voltage)){
        _voltage /= REFERENCE_VOLTAGE_ADJUSTER_EXTENS_VOLTAGE_MULTIPLAYER;
        DACext.setVoltage(_voltage, Tenzo_ADC_CS);
        GV.ExtensRefVoltage = *setVoltage;
    }
}

void Reference_Voltage_Adjuster_Displacement (float *setVoltage){
    float _voltage = *setVoltage;
    if(!std::isnan(_voltage)){
        //_voltage /= REFERENCE_VOLTAGE_ADJUSTER_EXTENS_VOLTAGE_MULTIPLAYER;
        //DACext.setVoltage(_voltage, Tenzo_ADC_CS);
        GV.DisplRefVoltage = *setVoltage;
    }
}