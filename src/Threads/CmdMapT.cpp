#include "CmdMapT.h"

void CmdMap_Thread()
{
    while (true)
    {
        // force Hard fault
        // uint32_t *ptr = (uint32_t *)0x00000000;
        // *ptr = 0xDEADBEEF;

        // COUT("size list of cmdMap: ");
        // COUT(cmdMap.get_size());
        
        //-------------------
        //TEST GET ALL PINS AND COMMAND        
        // char data1[400];
        // cmdMap.getAllPins(data1);
        // cout << "data1: " << data1 << endl;

        // cmdMap.replaceCommand(IP_MK_10, IP_MK_1);
        // cmdMap.getAllPins(data1);
        // cout << "data1: " << data1 << endl;

        ThisThread::sleep_for(100ms);
    }
}