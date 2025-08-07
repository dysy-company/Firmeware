#ifndef FILTER_TASKS_H
#define FILTER_TASKS_H
#include <cfloat>
#include <mbed.h>
#include "..//../src/threads/ExecutionT.h"

#define COUNTS_DELAY  150000

class addFilterAtEnd{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    uint32_t filterType;
    int rangeOfFilter;
    ExecutionThread* execTreadPtr;
    addFilterAtEnd(uint32_t dType, uint32_t fType, int range, ExecutionThread* execPtr){
        dataType = dType; 
        filterType = fType;
        rangeOfFilter = range;
        execTreadPtr = execPtr;
        //printf("%s filtType-%d dataType-%d\n", "Filter add begin", filterType, dataType);
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr ->addFilterAtEnd(filterType, dataType, rangeOfFilter);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
    ~addFilterAtEnd(){
        //printf("%s filtType-%d dataType-%d\n", "Filter add end", filterType, dataType);
    }
};

class addFilterByIndex{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    uint32_t filterType;
    int rangeOfFilter;
    int index;
    ExecutionThread* execTreadPtr;
    addFilterByIndex(uint32_t dType, uint32_t fType, int range, int ind, ExecutionThread* execPtr){
        dataType = dType;
        filterType = fType;
        rangeOfFilter = range;
        index = ind;
        execTreadPtr = execPtr;
        //printf("%s filtType-%d dataType-%d\n", "Filter add index begin", filterType, dataType);
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr ->addFilterByIndex(filterType, dataType, rangeOfFilter, index);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
    ~addFilterByIndex(){
        //printf("%s filtType-%d dataType-%d\n", "Filter add index end", filterType, dataType);
    }
};

class remooveFilterByParameter{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    uint32_t filterType;
    uint32_t parameter;
    int index;
    ExecutionThread* execTreadPtr;
    remooveFilterByParameter(uint32_t dType, uint32_t fType, uint32_t param, int ind, ExecutionThread* execPtr){
        dataType = dType;
        filterType = fType;
        parameter = param;
        index = ind;
        execTreadPtr = execPtr;
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr ->clearingOfFilterByParameters(filterType, dataType, parameter, index);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
};

class orderingByParameter{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    ExecutionThread* execTreadPtr;
    orderingByParameter(uint32_t dType, ExecutionThread* execPtr){
        dataType = dType;
        execTreadPtr = execPtr;
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr ->orderingByParameter(dataType);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
};

class sinusDisplNullPointAddDelta{
    public:
    errorCode_t error = NO_ERROR;
    double dataType;
    ExecutionThread* execTreadPtr;
    sinusDisplNullPointAddDelta(double dType, ExecutionThread* execPtr){
        dataType = dType;
        execTreadPtr = execPtr;
    };
    void operator()(){
        if (execTreadPtr){
            error = execTreadPtr ->writeAddNullPointSinDispl(dataType);
        }
    }
};

class setFilterActivityUnit{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    uint32_t activ;
    uint32_t step;
    ExecutionThread* execTreadPtr;
    setFilterActivityUnit(uint32_t dType, uint32_t activity, uint32_t st, ExecutionThread* execPtr){
        dataType = dType; 
        activ = activity;
        step = st;
        execTreadPtr = execPtr;
        //printf("%s filtType-%d dataType-%d\n", "Filter add begin", filterType, dataType);
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr->setFilteringActivityCell(dataType, activ, step);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
    ~setFilterActivityUnit(){
        //printf("%s filtType-%d dataType-%d\n", "Filter add end", filterType, dataType);
    }
};

class setFilterActivityDataLine{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t dataType;
    uint32_t step;
    ExecutionThread* execTreadPtr;
    setFilterActivityDataLine(uint32_t dType, uint32_t st, ExecutionThread* execPtr){
        dataType = dType;
        step = st;
        execTreadPtr = execPtr;
        //printf("%s filtType-%d dataType-%d\n", "Filter add begin", filterType, dataType);
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr->setFilteringActivityStepsDataRaw(dataType, step);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
    ~setFilterActivityDataLine(){
        //printf("%s filtType-%d dataType-%d\n", "Filter add end", filterType, dataType);
    }
};

class setFilterActivityAllSteps{
    public:
    errorCode_t error = NO_ERROR;
    uint32_t step;
    ExecutionThread* execTreadPtr;
    setFilterActivityAllSteps(uint32_t st, ExecutionThread* execPtr){
        step = st;
        execTreadPtr = execPtr;
        //printf("%s filtType-%d dataType-%d\n", "Filter add begin", filterType, dataType);
    };
    void operator()(){
        if (execTreadPtr){
            execTreadPtr->makeOrderToUnblockFiltering(false);
            uint32_t counter = 0;
            while (execTreadPtr->getStatusOfFilteringSet()){
                counter ++;
                if (counter >= COUNTS_DELAY){
                    break;
                }
            }
            if (counter < COUNTS_DELAY){
                error = execTreadPtr->setFilteringActivityAllCells(step);
            }
            else error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
            execTreadPtr->makeOrderToUnblockFiltering(true);
        }
    }
    ~setFilterActivityAllSteps(){
        //printf("%s filtType-%d dataType-%d\n", "Filter add end", filterType, dataType);
    }
};


#endif