#ifndef ETHERNET_PARSER_THREAD_H
#define ETHERNET_PARSER_THREAD_H
#include <mbed.h>
#include "..//..//include/TypeDefs/Threads_Mail_Types.h"
#include "..//..//lib/EthParser/EthParser.h"
#include "..//..//include/Ethernet/Ethernet_Errors.h"
#include "..//..//include/Global_Variables.h"
#include "..//..//lib/GlobalVariablesInterface/GlobalVariablesInterface.h"
#include "..//..//include/Shared_Params.h"
#include "ExecutionT.h"

// extern globalVariables_t GV;
// extern GlobalVariablesInterface GVI;
// extern Mail<EthernetMail_t, 16> EthernetMailBox;
// extern Mail<EthernetAnswerMail_t, 16> EthernetAnswerMailBox;
// extern Mail<TaskManagerMail_t, 16> TaskManagerMailBox;

class EthernetParserThread{
    public:
        EthernetParserThread(
            globalVariables_t               *GV, 
            GlobalVariablesInterface        *GVI, 
            Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE>  *EthernetMailBox,
            Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE>  *EthernetAnswerMailBox,
            Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>  *TaskManagerMailBox,
            ExecutionThread                 *ExeThr
        );
        ~EthernetParserThread();
        void threadExecute();
    private:
        globalVariables_t           *GV;
        GlobalVariablesInterface    *GVI;
        Mail<EthernetMail_t,        DEFAULT_MAIL_SIZE> *EthernetMailBox;
        Mail<EthernetAnswerMail_t,  DEFAULT_MAIL_SIZE> *EthernetAnswerMailBox;
        Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE> *TaskManagerMailBox;
        EthernetParser              *ethernetParser;
        ExecutionThread             *ExeThr;
};

#endif