#include "Filter.h"

//=====================================  FilterCollection ====================================

FilterCollection::FilterCollection(float* _sourse1, float* _target1, uint32_t kindOfData1, float* _sourse2, float* _target2, uint32_t kindOfData2,
    float* _sourse3, float* _target3, uint32_t kindOfData3) {
    setOfFilters.filtersMatrix[0].sourse = _sourse1;
    setOfFilters.filtersMatrix[1].sourse = _sourse2;
    setOfFilters.filtersMatrix[2].sourse = _sourse3;
    setOfFilters.filtersMatrix[0].target = _target1;
    setOfFilters.filtersMatrix[1].target = _target2;
    setOfFilters.filtersMatrix[2].target = _target3;
    setOfFilters.filtersMatrix[0].dataType = kindOfData1;
    setOfFilters.filtersMatrix[1].dataType = kindOfData2;
    setOfFilters.filtersMatrix[2].dataType = kindOfData3;
}

int FilterCollection::numberOfDataTypeCalculating(uint32_t dataType){
    int i = 0;
    for (; i != getNumberOfDataTypes(); i++) {
        if (setOfFilters.filtersMatrix[i].dataType == dataType) {
            break;
        }
    } 
    return i;
}

errorCode_t FilterCollection::clearAllCollection() {
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        for (int j = 0; j < getNumberOfFilterInLine(); j++) {
            if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
                delete setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter;
                setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter = nullptr;
                done = true;
            }
        }
    }
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_NOTHING_TO_DO;
    return error;
}

errorCode_t FilterCollection::clearOneFilter(uint32_t dataType, int ind) {
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    int i = numberOfDataTypeCalculating(dataType);
    if (setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter && ind < getNumberOfFilterInLine()) {
        delete setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter;
        setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter = nullptr;
        done = true;
    }
    else if (!setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter && ind < getNumberOfFilterInLine()){
        error = ERROR_NOTHING_TO_DO;
    }
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::clearLineCollection(uint32_t dataType) {
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    int i = numberOfDataTypeCalculating(dataType);
    for (int j = 0; j < getNumberOfFilterInLine() && i < getNumberOfDataTypes(); j++) {
        if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
            delete setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter;
            setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter = nullptr;
            done = true;
        }
        error = ERROR_NOTHING_TO_DO;
    }
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::clearFiltersByDataTypeAndFilterType(uint32_t dataType, uint32_t filterType){
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    int i = numberOfDataTypeCalculating(dataType);
    for (int j = 0; j < getNumberOfFilterInLine() && i < getNumberOfDataTypes(); j++) {
        if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
            if(setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter->getTypeOfFilter()==filterType){
                delete setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter;
                setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter = nullptr;
                done = true;
            }
        }
        error = ERROR_NOTHING_TO_DO;
    }
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::clearAllLinesByFilterType(uint32_t filterType){
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        for (int j = 0; j < getNumberOfFilterInLine(); j++){
            if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
                if(setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter->getTypeOfFilter()==filterType){
                    delete setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter;
                    setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter = nullptr;
                    done = true;
                }
            }
            error = ERROR_NOTHING_TO_DO;
        }
    }
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::orderingFilter(int filtIndex){
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    bool isReplaced = false;
    for (int i = 1; i < getNumberOfFilterInLine() && filtIndex < getNumberOfDataTypes(); i++){
        for (int j = 0; j < getNumberOfFilterInLine() - 1; j++){
            if(setOfFilters.filtersMatrix[filtIndex].filtersLine[j].ptrFilter==nullptr){
                setOfFilters.filtersMatrix[filtIndex].filtersLine[j].ptrFilter = setOfFilters.filtersMatrix[filtIndex].filtersLine[j + 1].ptrFilter;
                isReplaced = true;
                if (setOfFilters.filtersMatrix[filtIndex].filtersLine[j].ptrFilter) {
                    done = true;
                }
                else if (!done) {
                    error = ERROR_NOTHING_TO_DO;
                }
                setOfFilters.filtersMatrix[filtIndex].filtersLine[j + 1].ptrFilter = nullptr;    
            }
        }
    }
    if (!done && !isReplaced) error = ERROR_NOTHING_TO_DO;
    if (done) error = NO_ERROR;
    //if (setOfFilters.filtersMatrix[filtIndex].filtersLine[getNumberOfFilterInLine() - 1].ptrFilter) error = ERROR_NOTHING_TO_DO;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA; 
    return error;
}

errorCode_t FilterCollection::orderingFiltersByParameter(uint32_t dataType){
    errorCode_t error = DEFAULT_VALUE;
    bool done = false;
    bool notToDo = false;
    int i = numberOfDataTypeCalculating(dataType);
    if (i == getNumberOfDataTypes()){
        for (int n = 0; n < getNumberOfDataTypes(); n++){
            error = orderingFilter(n);
            if (error == NO_ERROR) done = true;
            else if (error == ERROR_NOTHING_TO_DO) notToDo = true;
        }
    }
    else error = orderingFilter(i);
    if (notToDo) error = ERROR_NOTHING_TO_DO;
    if (done) error = NO_ERROR;
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

void FilterCollection::getFilteredDataFromSet() {
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        float tmp = *(setOfFilters.filtersMatrix[i].sourse);
        if (!isnan(tmp)){   
            for (int j = 0; j < getNumberOfFilterInLine(); j++) {
                if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
                    tmp = setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter->getFilteredData(tmp);
                    //printf("%d\n", j);
                }
                if (j < (sizeOfTarget - 1)){
                    setOfFilters.filtersMatrix[i].target[j] = tmp;
                }
            }
        }
        (setOfFilters.filtersMatrix[i].target[sizeOfTarget - 1]) = tmp;
    }
}

void FilterCollection::setRawDataInFiltersSetTargets(){
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        float tmp = *(setOfFilters.filtersMatrix[i].sourse);
        if (!isnan(tmp)){
            for (int j = 0; j < getSizeOfTarget(); j++) {
                setOfFilters.filtersMatrix[i].target[j] = tmp;
            }
        }
    }
}

FilterCollection::~FilterCollection(){
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        for (int j = 0; j < getNumberOfFilterInLine(); j++) {
            if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
                delete setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter;
            }
        }
    }
}

void FilterCollection::resetFilterInSet(uint32_t dataType, int ind, int newRangeOfFilter){
    int i = numberOfDataTypeCalculating(dataType);
    if (setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter && i < getNumberOfDataTypes()) {
        setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter ->resetFilter(newRangeOfFilter);
    }
}

void FilterCollection::resetAllFilterCollection(){
    for (int i = 0; i < getNumberOfDataTypes(); i++) {
        int tmp = 0;
        for (int j = 0; j < getNumberOfFilterInLine(); j++) {
            if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter) {
                tmp = setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter->getRangeOfFilter();
                setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter->resetFilter(tmp);
            }
        }
    }
}

int FilterCollection::getRangeOfFilterFromSet(uint32_t dataType, int ind){
    int i = numberOfDataTypeCalculating(dataType);
    if (setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter && i < getNumberOfDataTypes()) {
        return setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter->getRangeOfFilter();
    }
    else return -1;
}

errorCode_t FilterCollection::addFilterInCollectionAtEnd(uint32_t dataType, uint32_t filterType, int rangeOfFilter){
    errorCode_t error = DEFAULT_VALUE;
    int i = numberOfDataTypeCalculating(dataType);
    for (int j = 0; j < getNumberOfFilterInLine() && i < getNumberOfDataTypes(); j++) {
        if (setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter == nullptr){
            error = addFilterRaw(filterType, setOfFilters.filtersMatrix[i].filtersLine[j].ptrFilter, rangeOfFilter);
            // for (int k = 0; k < getNumberOfFilterInLine(); k++){
            //     printf("%d %d\n", setOfFilters.filtersMatrix[i].filtersLine[k].ptrFilter, j);
            // }
            break;
        }
        if (error == DEFAULT_VALUE) error = ERROR_ALL_PLACES_TAKED;
    }
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::addFilterRaw(uint32_t filterType, Filter*& filterPtr, int rangeOfFilter){
    errorCode_t error =  DEFAULT_VALUE;
    if (filterType == typeOfFilter::MEDIAN_FILTER){
        MedianFilter* ptr = new MedianFilter(rangeOfFilter);
        if (!ptr){
            error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
        }
        else if(ptr->getRangeOfFilter()!=rangeOfFilter){
            error = ERROR_WRONG_INPUT_DATA;
            delete ptr;
        }
        else {error = NO_ERROR;
            filterPtr = ptr;
        }
    }
    else if (filterType == typeOfFilter::AVERAGE_FILTER){
        AverageFilter* ptr = new AverageFilter(rangeOfFilter);
        if (!ptr){
            error = SYSTEM_ERROR_DURING_ALLOC_MEMORY;
        }
        else if(ptr->getRangeOfFilter()!=rangeOfFilter){
            error = ERROR_WRONG_INPUT_DATA;
            delete ptr;
        }
        else {error = NO_ERROR;
            filterPtr = ptr;
        }        
    }
    else error = ERROR_WRONG_INPUT_DATA;
    return error;
}

errorCode_t FilterCollection::addFilterInCollectionAtIndex(uint32_t dataType, uint32_t filterType, int rangeOfFilter, int ind){
    errorCode_t error = DEFAULT_VALUE;
    int i = numberOfDataTypeCalculating(dataType);
    if ( i < getNumberOfDataTypes() && ind < getNumberOfFilterInLine()){
        if (setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter){
            delete setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter;
            error = addFilterRaw(filterType, setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter, rangeOfFilter); 
        }
        else error = addFilterRaw(filterType, setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter, rangeOfFilter);
    }
    if (error == DEFAULT_VALUE) error = ERROR_WRONG_INPUT_DATA;
    return error;
}

uint32_t FilterCollection::getTypeOfFilterInSet(uint32_t dataType, int ind){
    int i = numberOfDataTypeCalculating(dataType);
    if ( i < getNumberOfDataTypes() && ind < getNumberOfFilterInLine() && setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter){
        return setOfFilters.filtersMatrix[i].filtersLine[ind].ptrFilter ->getTypeOfFilter();
    }
    else return (uint32_t)typeOfFilter::EMPTYCELL;  
}

int FilterCollection::getNumberOfDataTypes(){
    return numberOfDataTypes;
}

int FilterCollection::getNumberOfFilterInLine(){
    return numberOfFiltersInLine;
}

int FilterCollection::getSizeOfTarget(){
    return sizeOfTarget;
}

void FilterCollection::setNotBusyStatus(){
    isBusy = false;
}
bool FilterCollection::getBusinessStatus(){
    return isBusy;
}
void FilterCollection::setBusyStatus(){
    isBusy = true;
}

//=====================================  MedianFilter ==========================================

MedianFilter::MedianFilter() {
    this->sizeOfFilterBuffer = 1;
    index = bufferArray;
}

MedianFilter::MedianFilter(int sz) {
    resetFilter(sz);
}

int MedianFilter::getRangeOfFilter() {
    return sizeOfFilterBuffer;
}

uint32_t MedianFilter::getTypeOfFilter(){
    return typeFilter;
}

void MedianFilter::resetFilter(int sz) {
    if(sz % 2 == 0){
        sz = sz - 1;
    }
    if (sz > 0 && sz <= MAX_SIZE_OF_BUFFER) {
        sizeOfFilterBuffer = sz;
        middlePosition = sizeOfFilterBuffer / 2;
        middleValue = nullptr;
        smallValue = nullptr;
        bigValue = nullptr;
        indexOfNextElem = 0;
        numberOfElements = 0;
        middlePositionCounter = 0;
        middleSet = false;
        atBegin = false;
        bigSet = false;
        index = bufferArray;
        for (int i = 0; i < sz; i++) {
            index->postNode = nullptr;
            index->preNode = nullptr;
            index++;
        }
        index = bufferArray;
    }
    else resetFilter(1);
}

void MedianFilter::findePositionAndInsert() {
    index->postNode = nullptr;
    index->preNode = nullptr;
    if (index->value <= smallValue->value) {
        index->postNode = smallValue;
        smallValue->preNode = index;
        smallValue = index;
    }
    else {
        finding = smallValue->postNode;
        if (finding == nullptr) {
            smallValue->postNode = index;
            index->preNode = smallValue;
        }
        else {
            while (finding != nullptr) {
                if (index->value <= finding->value) {
                    index->preNode = finding->preNode;
                    finding->preNode = index;
                    index->preNode->postNode = index;
                    index->postNode = finding;
                    break;
                }
                else if (finding->postNode == nullptr && index->value > finding->value) {
                    finding->postNode = index;
                    index->preNode = finding;
                    break;
                }
                finding = finding->postNode;
            }
        }
    }
}

void MedianFilter::fillingOfBuffer(double newVal) {
    index = bufferArray + indexOfNextElem;
    index->value = newVal;
    index->postNode = nullptr;
    index->preNode = nullptr;
    if (smallValue == nullptr) {
        smallValue = bufferArray;
    }
    else {
        findePositionAndInsert();
    }
    numberOfElements++;
    indexOfNextElem++;
}

void MedianFilter::insertNode(Node* targetNode, typeOfActionPlace ins) {
    index->postNode = nullptr;
    index->preNode = nullptr;
    switch (ins)
    {
    case BEGIN:
        targetNode ->preNode = index;
        index->postNode = targetNode;
        smallValue = index; //correct small value ptr
        break;
    case REGULAR:
        index->preNode = targetNode->preNode;
        targetNode->preNode = index;
        index->preNode->postNode = index;
        index->postNode = targetNode;
        break;
    case END:
        targetNode->postNode = index;
        index->preNode = targetNode;
        bigValue = index; //correct big value ptr
        break;
    default:
        break;
    }
}

void MedianFilter::checkDeletedElement() {
    if (index->value < middleValue->value) {
        middleValue = middleValue->postNode;
    }
    else if (index->value == middleValue->value) {
        middleSet = false;
    }
}

void MedianFilter::deleteElement() {
    if (index == smallValue) {
        smallValue = smallValue->postNode;
        smallValue->preNode = nullptr;
    }
    else if (index == bigValue) {
        bigValue = bigValue->preNode;
        bigValue->postNode = nullptr;
    }
    else if (index == middleValue) {
        middleValue = middleValue->postNode;
        middleSet = true;
        index->postNode->preNode = index->preNode;
        index->preNode->postNode = index->postNode;
    }
    else {
        index->postNode->preNode = index->preNode;
        index->preNode->postNode = index->postNode;
    }
}

Node* MedianFilter::findeStepBack(Node* start) {
    Node* tmp = start;
    while (tmp) {
        if (index->value <= tmp->value && (tmp->preNode == nullptr || index->value > tmp->preNode->value)) {
            return tmp;
        }
        tmp = tmp->preNode;
    }
    return smallValue;
}

Node* MedianFilter::findeStepForward(Node* start) {
    Node* tmp = start;
    while (tmp) {
        if (index->value <= tmp->value) {
            return tmp;
        }
        tmp = tmp->postNode;
    }
    return nullptr;
}

void MedianFilter::insertElementInCompletedBuffer(double newVal) {
    if (indexOfNextElem >= sizeOfFilterBuffer) {
        indexOfNextElem = 0;
    }
    index = bufferArray + indexOfNextElem;
    if (sizeOfFilterBuffer < 9) {
        middleSet = false;
        index->value = newVal;
        if (index == smallValue) {
            atBegin = true;
            smallValue = smallValue->postNode;
            smallValue->preNode = nullptr;
            findePositionAndInsert();
        }
        else if (index != nullptr) {
            atBegin = false;
            if (index->postNode) {
                index->postNode->preNode = index->preNode;
                index->preNode->postNode = index->postNode;
            }
            else {
                index->preNode->postNode = nullptr;
            }
            findePositionAndInsert();
        }
    }
    else {
        checkDeletedElement();
        deleteElement();
        index->value = newVal;
        if (newVal <= smallValue->value) {
            insertNode(smallValue, BEGIN);
            middleValue = middleValue->preNode;
        }
        else if (newVal > bigValue->value) {
            insertNode(bigValue, END);
        }
        else if (newVal < ((middleValue->value - smallValue->value) / 2.0 + smallValue->value)) {
            insertNode(findeStepForward(smallValue), REGULAR);
            middleValue = middleValue->preNode;
        }
        else if (newVal > ((bigValue->value - middleValue->value) / 2.0 + middleValue->value)) {
            insertNode(findeStepBack(bigValue), REGULAR);
        }
        else if (newVal <= middleValue->value) {
            insertNode(findeStepBack(middleValue), REGULAR);
            middleValue = middleValue->preNode;
        }
        else if (newVal > middleValue->value) {
            insertNode(findeStepForward(middleValue), REGULAR);
        }
    }
    indexOfNextElem++;
}

void MedianFilter::setPointerOnMiddleAndEnd() {
    middlePositionCounter = 0;
    middleValue = smallValue;
    while (middlePositionCounter < middlePosition) {
        middleValue = middleValue->postNode;
        middlePositionCounter++;
    }
    bigValue = middleValue;
    while (bigValue->postNode) {
        bigValue = bigValue->postNode;
    }
    middleSet = true;
    bigSet = true;
}

void MedianFilter::setPointerOnMiddle() {
    middlePositionCounter = 0;
    middleValue = smallValue;
    while (middlePositionCounter < middlePosition) {
        middleValue = middleValue->postNode;
        middlePositionCounter ++;
    }
    middleSet = true;
}

double MedianFilter::getFilteredData(double newData) {
    double data = newData;
    if (sizeOfFilterBuffer == 1) {
        data = newData;
    }
    else if (sizeOfFilterBuffer < 1 || sizeOfFilterBuffer > MAX_SIZE_OF_BUFFER) {
        resetFilter(1);
        data = newData;
    }
    else if (numberOfElements < sizeOfFilterBuffer) {
        fillingOfBuffer(newData);
        data = newData;
    }
    else if (numberOfElements == sizeOfFilterBuffer) {
        if (!bigSet) {
            setPointerOnMiddleAndEnd();
        }
        insertElementInCompletedBuffer(newData);
        if (!middleSet) {
            setPointerOnMiddle();
        }
        data = middleValue->value;
    }
    else data = newData;
    return data;
}

//========================================== AverageFilter ============================================
AverageFilter::AverageFilter() {
    avgCounter = 0;
    avgCounterLimit = 1;
    averageSum = 0.0;
    sizeOfFilterBuffer = 1;
}

AverageFilter::AverageFilter(int sz) {
    resetFilter(sz);
}

void AverageFilter::resetFilter(int sz) {
    if (sz > 0 && sz <= 100) {
        avgCounter = 0;
        avgCounterLimit = sz;
        averageSum = 0.0;
        sizeOfFilterBuffer = sz;
        first = false;
    }
    else resetFilter(1);
}

int AverageFilter::getRangeOfFilter() {
    return sizeOfFilterBuffer;
}

uint32_t AverageFilter::getTypeOfFilter(){
    return typeFilter;
}

double AverageFilter::getFilteredData(double newData) {
    if (!first) {
        lastData = newData;
        first = true;
    }
    else if (avgCounterLimit == 1) {
        lastData = newData;
    }
    else if (avgCounter < avgCounterLimit) {
        avgCounter++;
        averageSum += newData;
    }
    else {
        lastData = averageSum / avgCounter;
        avgCounter = 0;
        averageSum = 0.0;
        sizeOfFilterBuffer = avgCounterLimit;
    }
    return lastData;
}