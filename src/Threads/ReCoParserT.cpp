#include "ReCoParserT.h"

RemoteControllerParserThread::RemoteControllerParserThread(
        globalVariables_t               *_GV,
        GlobalVariablesInterface        *_GVI,
        Mail<UARTMail_t,        DEFAULT_MAIL_SIZE>  *_ReCoMailBox,
        Mail<UARTMail_t,  DEFAULT_MAIL_SIZE>  *_ReCoAnswerMailBox,
        Mail<TaskManagerMail_t,     DEFAULT_MAIL_SIZE>  *_TaskManagerMailBox,
		ExecutionThread                                 *ExeThr
        )
{
  this->GV = _GV;
  this->GVI = _GVI;
  this->ReCoMailBox = _ReCoMailBox;
  this->ReCoAnswerMailBox = _ReCoAnswerMailBox;
  this->TaskManagerMailBox = _TaskManagerMailBox;
  this->reCoParser = new RemoteControllerParser(GV, GVI, ExeThr);
}

void RemoteControllerParserThread::setBlock()
{
    this->blocking = GV->testStatus;
}

void RemoteControllerParserThread::threadExecute()
{
    while(1) {
        Watchdog::get_instance().kick();
        UARTMail_t *ReCoMail = this->ReCoMailBox->try_get_for(5ms);
        if(ReCoMail == nullptr) {
			ThisThread::sleep_for(10ms);
			continue;
		}
        uint32_t error = NO_ERROR;
        error = reCoParser->parse(ReCoMail->command, ReCoMail->dataLength, ReCoMail->data);
		if(ReCoMail->command == COMMAND::SET_CONST_DISP_POSITION_TO_HOLD_WITH_ACCEPT) {
			ReCoMailBox->free(ReCoMail);
			continue;
		}
        if (error) {
            // TO DO
			ReCoMailBox->free(ReCoMail);
            continue;
        }
        UARTMail_t *ReCoAnswerMail;
		ReCoAnswerMail = ReCoAnswerMailBox->try_alloc_for(5ms);
		if(ReCoAnswerMail == nullptr) {
			ThisThread::sleep_for(10ms);
			continue;
		}
        ReCoAnswerMail->command = ReCoMail->command;
        ReCoAnswerMail->dataLength = ReCoMail->dataLength;
        std::copy(ReCoMail->data, ReCoMail->data + ReCoMail->dataLength,  ReCoAnswerMail->data);
        ReCoAnswerMailBox->put(ReCoAnswerMail);
        ReCoMailBox->free(ReCoMail);
		ThisThread::sleep_for(3ms);
    }
}
