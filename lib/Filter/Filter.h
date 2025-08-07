#ifndef FILTER_H
#define FILTER_H
#include <cfloat>
#include <mbed.h>
#include "../include/Global_Variables.h"
#include "../include/Shared_Params.h"

#define MAX_SIZE_OF_BUFFER                 99

enum typeOfActionPlace {
    BEGIN,
    REGULAR,
    END
};

struct Node {
    double value = 0.0;
    Node* preNode = nullptr;
    Node* postNode = nullptr; 
};

enum typeOfData {
    UNKNOWN,
    DISPLACEMENT,
    STRAIN,
    DEFORMATION
};

enum typeOfFilter {
    EMPTYCELL,
    MEDIAN_FILTER,
    AVERAGE_FILTER
};

class Filter {
public:
    virtual void resetFilter(int) = 0;
    virtual int getRangeOfFilter() = 0;
    virtual double getFilteredData(double) = 0;
    virtual uint32_t getTypeOfFilter() = 0;
    virtual ~Filter() {};
};

struct FilterPropertiesNode {
    Filter* ptrFilter = nullptr;
};

struct FilterPropertiesLine {
    float* sourse = nullptr;
    float* target = nullptr;
    uint32_t dataType = typeOfData::UNKNOWN;
    FilterPropertiesNode filtersLine[5];
};

struct FilterPropertiesMatrix {
    FilterPropertiesLine filtersMatrix[3];
};

class FilterCollection {
public:
    FilterCollection(float* _sourse1, float* _target1, uint32_t kindOfData1, float* _sourse2, float* _target2, uint32_t kindOfData2,
                     float* _sourse3, float* _target3, uint32_t kindOfData3);
    errorCode_t clearFiltersByDataTypeAndFilterType(uint32_t dataType, uint32_t filterType);
    errorCode_t clearOneFilter(uint32_t dataType, int ind);
    errorCode_t clearLineCollection(uint32_t dataType);
    errorCode_t clearAllCollection();
    errorCode_t clearAllLinesByFilterType(uint32_t filterType);
    errorCode_t orderingFiltersByParameter(uint32_t dataType);
    void getFilteredDataFromSet();
    void resetFilterInSet(uint32_t dataType, int ind, int newRangeOfFilter);
    void resetAllFilterCollection();
    void setRawDataInFiltersSetTargets();
    int getRangeOfFilterFromSet(uint32_t dataType, int ind);
    errorCode_t addFilterInCollectionAtEnd(uint32_t dataType, uint32_t filterType, int rangeOfFilter);
    errorCode_t addFilterInCollectionAtIndex(uint32_t dataType, uint32_t filterType, int rangeOfFilter, int ind);
    uint32_t getTypeOfFilterInSet(uint32_t dataType, int ind);
    int getNumberOfDataTypes();
    int getNumberOfFilterInLine();
    int getSizeOfTarget();
    void setNotBusyStatus();
    bool getBusinessStatus();
    void setBusyStatus();
    ~FilterCollection();

private:
    errorCode_t orderingFilter(int filtIndex);
    int numberOfDataTypeCalculating(uint32_t dataType);
    errorCode_t addFilterRaw(uint32_t filterType, Filter*& filterPtr, int rangeOfFilter);
    int numberOfFilters = 0;
    int numberOfFiltersInLine = 5;
    int numberOfDataTypes = 3;
    FilterPropertiesMatrix setOfFilters;
    double* sourse1 = nullptr;
    double* target1 = nullptr;
    uint32_t dataType1;
    double* sourse2 = nullptr;
    double* target2 = nullptr;
    uint32_t dataType2;
    double* sourse3 = nullptr;
    double* target3 = nullptr;
    uint32_t dataType3;
    uint8_t sizeOfTarget = 3;
    bool isBusy = false;
};

class MedianFilter : public Filter {
public:
    MedianFilter();
    MedianFilter(int sz);
    ~MedianFilter() {
        //printf("%s\n", "medianDestroyed");
    };


    void resetFilter(int) override;
    int getRangeOfFilter() override;
    double getFilteredData(double) override;
    uint32_t getTypeOfFilter() override;

    void fillingOfBuffer(double);
    void insertElementInCompletedBuffer(double);
    void findePositionAndInsert();
    void setPointerOnMiddle();
    void setPointerOnMiddleAndEnd();
    void insertNode(Node* targetNode, typeOfActionPlace ins);
    void checkDeletedElement();
    void deleteElement();
    Node* findeStepBack(Node* start);
    Node* findeStepForward(Node* start);

private:
    uint32_t typeFilter = typeOfFilter::MEDIAN_FILTER;
    int sizeOfFilterBuffer = 1;
    int prevSizeOfFilterBuffer = 1;
    int numberOfElements = 0;
    int indexOfNextElem = 0;
    int middlePosition = 0;
    uint8_t middlePositionCounter = 0;
    Node* middleValue = nullptr;
    Node* smallValue = nullptr;
    Node* bigValue = nullptr;
    Node* index = nullptr;
    Node* finding = nullptr;
    Node bufferArray[MAX_SIZE_OF_BUFFER + 1];
    bool middleSet = false;
    bool atBegin = false;
    bool bigSet = false;
};


class AverageFilter : public Filter {
public:
    AverageFilter();
    AverageFilter(int sz);
    ~AverageFilter() {
        //printf("%s\n", "averageDestroyed");
    };

    void resetFilter(int) override;
    int getRangeOfFilter() override;
    double getFilteredData(double) override;
    uint32_t getTypeOfFilter() override;

private:
    uint32_t typeFilter = typeOfFilter::AVERAGE_FILTER;
    double lastData = 0;
    double averageSum = 0.0;
    uint8_t avgCounter = 0;
    uint8_t avgCounterLimit = 1;
    int sizeOfFilterBuffer = 1;
    bool first = false;
};

#endif