#include "EthParserT.h"

EthernetParserThread::EthernetParserThread(
  globalVariables_t               *GV, 
  GlobalVariablesInterface        *GVI, 
  Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE>  *EthernetMailBox,
  Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE>  *EthernetAnswerMailBox,
  Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>  *TaskManagerMailBox,
  ExecutionThread                                 *ExeThr
){
  this->GV = GV;
  this->GVI = GVI;
  this->EthernetMailBox = EthernetMailBox;
  this->EthernetAnswerMailBox = EthernetAnswerMailBox;
  this->TaskManagerMailBox = TaskManagerMailBox;
  this->ethernetParser = new EthernetParser(GV, GVI, ExeThr);
  this->ExeThr = ExeThr;
}

EthernetParserThread::~EthernetParserThread(){
  delete this->ethernetParser;
}

void EthernetParserThread::threadExecute(){
  
  //TaskManagerMail_t *TaskManagerMail;
  //EthernetParser ethernetParser(&GV, &GVI);
  while(1){
    Watchdog::get_instance().kick();
    EthernetMail_t *EthernetMail = this->EthernetMailBox->try_get_for(100ms);
    if (EthernetMail != nullptr){
      //uint64_t uint64Buf = 0;
      //double doubleValue = 0;
      uint32_t error = NO_ERROR;
      //uint32_t command = EthernetMail->command;
      //uint32_t dataLength = EthernetMail->dataLength;
      //char data[sizeof EthernetMail->data];
      //std::copy(EthernetMail->data, EthernetMail->data + sizeof EthernetMail->data, data);
      //basic.writeArrayToArray(EthernetMail->data, 0, sizeof EthernetMail->data, data, 0);
      
      error = ethernetParser->parse(EthernetMail->command, EthernetMail->dataLength, EthernetMail->data);
      
      //TODO ERROR
      if (error){
        //printf("\n\rTask ADC Calibration after parser = %d;\n\r", task);
        //DEPRECATED:
        //TaskManagerMail = TaskManagerMailBox.alloc();
        //TaskManagerMail->task = task;
        //TaskManagerMailBox.put(TaskManagerMail);
      }
      EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox->try_alloc_for(100ms);
      if (EthernetAnswerMail != nullptr){
        EthernetAnswerMail->command = EthernetMail->command;
        EthernetAnswerMail->dataLength = EthernetMail->dataLength;
        std::copy(EthernetMail->data, EthernetMail->data + EthernetMail->dataLength, EthernetAnswerMail->data);
        EthernetMailBox->free(EthernetMail);
        //printf("\nCommand: 0x%X; DataLength: %d;\r\n", command, dataLength);
                
        //for (int i = 0; i < dataLength; i++){
        //  EthernetAnswerMail->data[i] = data[i];
        //}
        EthernetAnswerMailBox->put(EthernetAnswerMail);
      }
    }
    //ThisThread::sleep_for(1ms);
  }
}