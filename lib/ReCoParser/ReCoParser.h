#ifndef RECOPARSER_H
#define RECOPARSER_H

#include "EthParser.h"

class RemoteControllerParser : public EthernetParser {
public:
    RemoteControllerParser(globalVariables_t *globalVariables, GlobalVariablesInterface *globalVariablesInterface, ExecutionThread* ExeThr) 
        : EthernetParser(globalVariables, globalVariablesInterface, ExeThr)
        {}
    ~RemoteControllerParser() {}
};

#endif // RECOPARSER_H