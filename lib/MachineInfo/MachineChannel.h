#ifndef MACHINE_CHANNEL_H
#define MACHINE_CHANNEL_H

#include <mbed.h>

#include "Shared_Params.h"
#include "Ethernet/Ethernet_Config.h"

class machineChannel{
    private:

    public:
        machineChannel();
        ~machineChannel();

        CircularBuffer<float, ETHERNET_VALUES_BUFFERS_SIZE> valuesBuffer;
        double maxValue;
        double maxValueOverloadPercent;
        double minValue;
        double minValueOverloadPercent;
        uint8_t sensorType;
};

#endif