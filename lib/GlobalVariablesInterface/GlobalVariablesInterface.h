#ifndef GLOBAL_VARIABLES_INTERFACE_H
#define GLOBAL_VARIABLES_INTERFACE_H

#include <mbed.h>
#include "..//..//include//Global_Variables.h"
#include "..//..//include//GlobalVariablesDefs.h"
#include "..//..//include//TypeDefs//ParamsTypeDefs.h"
#include "..//..//include//Shared_Params.h"
#include "..//InternalFlash/InternalFlash.h"
#include "..//InternalFlashDMA/InternalFlashDMA.h"


class GlobalVariablesInterface{

public:
    GlobalVariablesInterface(globalVariables_t *GV, InternalFlash *internalFlash, InternalFlashDMA *internalFlashDMA);
    ~GlobalVariablesInterface();
    template <typename T> void writeValue(uint32_t index, T value, memoryType_t memoryType);
    void writeValue(uint32_t index, char *buffer, memoryType_t memoryType);
    template <typename T> T readValue(uint32_t index, memoryType_t memoryType, int &size);
    template <typename T> T readValue(uint32_t index, memoryType_t memoryType, int &size, uint8_t exstraFlashOffset);
    template <typename T> T readValue(uint32_t index, memoryType_t memoryType);
    int readValue(uint32_t index, char *buffer, memoryType_t memoryType);
    uint32_t sizeOfCharBuffer = 0;
    char *ptrOnCharBuffer = nullptr;

private:

    globalVariables_t *_globalVariables;
    InternalFlash *_internalFlash;
    InternalFlashDMA *_internalFlashDMA;
    template <typename T> void writeValueToFlashImplement(T value, T &gvValue);
    template <typename T> void writeValueImplementation(T &gvValue, uint32_t flashOffset, T value, memoryType_t memoryType);
    template <typename T> T readValueImplementation(T &gvValue, uint32_t flashOffset, memoryType_t memoryType, int &size);
    template <typename T> int readValueAnyType(uint32_t index, char *buffer, memoryType_t memoryType);
    template <typename T, typename R = T> int readValueAnyTypeCast(uint32_t index, char *buffer, memoryType_t memoryType);
    template <typename T> void writeValueAnyType(uint32_t index, char *buffer, memoryType_t memoryType, T value);
    template <typename T, typename R = T> void writeValueAnyTypeCast(uint32_t index, char *buffer, memoryType_t memoryType, T value);
};
template <> std::string GlobalVariablesInterface::readValue<std::string>(uint32_t index, memoryType_t memoryType);
template <> std::string GlobalVariablesInterface::readValue<std::string>(uint32_t index, memoryType_t memoryType, int &size);
template <> std::string GlobalVariablesInterface::readValueImplementation<std::string>(std::string &gvValue, uint32_t flashOffset, memoryType_t memoryType, int &size);
template <> int GlobalVariablesInterface::readValueAnyType<std::string>(uint32_t index, char *buffer, memoryType_t memoryType);

template <> void GlobalVariablesInterface::writeValue<std::string>(uint32_t index, std::string value, memoryType_t memoryType);
template <> void GlobalVariablesInterface::writeValueImplementation<std::string>(std::string &gvValue, uint32_t flashOffset, std::string value, memoryType_t memoryType);
template <> void GlobalVariablesInterface::writeValueAnyType<std::string>(uint32_t index, char *buffer, memoryType_t memoryType, std::string value);

#include "GlobalVariablesInterface.t.hpp"
#endif