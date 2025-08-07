#include "OneWireT.h"

void OneWireAcquisition_Thread (){
    
    // uint8_t readROM[1] = {0x33};
    // while(true){
    //     if(GV.SensorsConnectionsAcq){
    //         uint8_t ROM_ID[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    //         //TEDsAcq.resetWire();
    //         if(TEDsAcq.sendCmd(OW_SEND_RESET, readROM, (uint8_t)1) == TEDS_TRANSFER_OK){ 
    //             if(TEDsAcq.readData(ROM_ID, 8) == TEDS_TRANSFER_OK){
    //                 uint64_t romID = 0; 
    //                 basic.writeBytesBufferToValue((char*)ROM_ID, &romID);
    //                 if(GV.StrainSensorIsConnect != SENSOR_TEDS_WAS_READ && GV.StrainSensorIsConnect != SENSOR_TEDS_UNDEFINED){
    //                     //send notification
    //                     EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
    //                     if(EthernetAnswerMail != nullptr){
    //                         EthernetAnswerMail->command = ETHERNET_COMMAND::TM_ONCE_CHANGE_STRAIN_SENSOR_CONNECTION;
    //                         EthernetAnswerMail->dataLength = 4;
    //                         //error status 0
    //                         basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)SENSOR_TEDS_WAS_READ);
    //                         EthernetAnswerMailBox.put(EthernetAnswerMail);
    //                     }
    //                 }
    //                 GV.StrainSensorIsConnect = SENSOR_TEDS_WAS_READ;
    //             }else{
    //                 if(GV.StrainSensorIsConnect != SENSOR_TEDS_NOT_FOUND && GV.StrainSensorIsConnect != SENSOR_TEDS_UNDEFINED){
    //                     //send notification
    //                     EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
    //                     if(EthernetAnswerMail != nullptr){
    //                         EthernetAnswerMail->command = ETHERNET_COMMAND::TM_ONCE_CHANGE_STRAIN_SENSOR_CONNECTION;
    //                         EthernetAnswerMail->dataLength = 4;
    //                         //error status 0
    //                         basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)SENSOR_TEDS_NOT_FOUND);
    //                         EthernetAnswerMailBox.put(EthernetAnswerMail);
    //                     }
    //                 }
    //                 GV.StrainSensorIsConnect = SENSOR_TEDS_NOT_FOUND;
    //             }
    //         }else{
    //             if(GV.StrainSensorIsConnect != SENSOR_TEDS_NOT_FOUND && GV.StrainSensorIsConnect != SENSOR_TEDS_UNDEFINED){
    //                     //send notification
    //                     EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
    //                     if(EthernetAnswerMail != nullptr){
    //                         EthernetAnswerMail->command = ETHERNET_COMMAND::TM_ONCE_CHANGE_STRAIN_SENSOR_CONNECTION;
    //                         EthernetAnswerMail->dataLength = 4;
    //                         //error status 0
    //                         basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)SENSOR_TEDS_NOT_FOUND);
    //                         EthernetAnswerMailBox.put(EthernetAnswerMail);
    //                     }
    //             }
    //             GV.StrainSensorIsConnect = SENSOR_TEDS_NOT_FOUND;
    //         }
    //     }else{
    //         GV.StrainSensorIsConnect = SENSOR_TEDS_WAS_READ;
    //     }
    //     ThisThread::sleep_for(500ms);
    // }
}