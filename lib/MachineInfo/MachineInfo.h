#ifndef MACHINE_INFO_H
#define MACHINE_INFO_H

#include <mbed.h>
#include "MachineChannel.h"
#include "..//..//include//Typedefs//ParamsTypeDefs.h"

class MachineInfo{
    public:
        int loadParamsFromFlash(void);

        uint64_t getSerialNumber(void);
        uint64_t getID(void);
    private:
        uint64_t serialNumber;
        uint64_t id;
        channelInfo_t displacement;
        channelInfo_t strain;
        channelInfo_t deformation;
};

#endif