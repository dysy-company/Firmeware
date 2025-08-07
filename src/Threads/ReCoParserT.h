#ifndef RECOPARSERT_H
#define RECOPARSERT_H

#include "EthParserT.h"
#include "ReCoParser.h"

class RemoteControllerParserThread {
public:
    RemoteControllerParserThread(
        globalVariables_t               *GV,
        GlobalVariablesInterface        *GVI,
        Mail<UARTMail_t,        DEFAULT_MAIL_SIZE>  *ReCoMailBox,
        Mail<UARTMail_t,  DEFAULT_MAIL_SIZE>  *ReCoAnswerMailBox,
        Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>  *TaskManagerMailBox,
		ExecutionThread                                 *ExeThr
    );
    ~RemoteControllerParserThread() {delete this->reCoParser;}
    void threadExecute();
    void setBlock();
private:
    int blocking;
    globalVariables_t           *GV;
    GlobalVariablesInterface    *GVI;
    Mail<UARTMail_t,        DEFAULT_MAIL_SIZE> *ReCoMailBox;
    Mail<UARTMail_t,  DEFAULT_MAIL_SIZE> *ReCoAnswerMailBox;
    Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE> *TaskManagerMailBox;
    RemoteControllerParser              *reCoParser;
};

#endif // RECOPARSERT_H