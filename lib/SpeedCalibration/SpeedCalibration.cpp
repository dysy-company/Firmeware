#include "SpeedCalibration.h"

SpeedCalibration::SpeedCalibration(int maxPoints){
    _maxPoints = maxPoints;
    _sizeOfPoints = -1;
    _params = new speedCalibrationParams_t[2];
}

SpeedCalibration::~SpeedCalibration(){
    delete[] _params;
}

void SpeedCalibration::getPositionPoints(void){
    int size = 0;
    this->getPointsSizeFromFlash(&size);
    if(size >= 2 && size <= 256){
      speedCalibrationParams_t *params = new speedCalibrationParams_t[size];
      this->getPointsFromFlash(params, size);
      //this->calibration->setNumberOfPoints(size);
      this->setPoints(params, size);
      delete[] params;
    }
}

void SpeedCalibration::getStrainPoints(void){
    int size = 0;
    this->getStrainPointsSizeFromFlash(&size);
    if(size >= 2 && size <= 256){
      speedCalibrationParams_t *params = new speedCalibrationParams_t[size];
      this->getStrainPointsFromFlash(params, size);
      //this->calibration->setNumberOfPoints(size);
      this->setPoints(params, size);
      delete[] params;
    }
}

bool SpeedCalibration::checkSize(int size){
    if (size >= 0 && size <= (int)_maxPoints){
        return true;
    }else{
        return false;
    }
}

bool SpeedCalibration::setNumberOfPoints(int numberOfPoints){
    if (checkSize(numberOfPoints)){
        delete[] this->_params;
        _params = new speedCalibrationParams_t[numberOfPoints];
        _sizeOfPoints = numberOfPoints;
        return true;
    }else{
        return false;
    }
}

bool SpeedCalibration::getNumberOfPoints(int &numberOfPoints){
    numberOfPoints = this->_sizeOfPoints;
    if(_sizeOfPoints > 0){
        return true;
    }else{
        return false;
    }
}

bool SpeedCalibration::setPoints(speedCalibrationParams_t *params, int length){
    if (this->setNumberOfPoints(length)){
        for(int i = 0; i < length; i++){
            this->_params[i].speed = params[i].speed;
            this->_params[i].Kp = params[i].Kp;
            this->_params[i].Ki = params[i].Ki;
            this->_params[i].Kd = params[i].Kd;
            this->_params[i].maxDeviation = params[i].maxDeviation;
        }
        return true;
    }
    return false;
}

bool SpeedCalibration::getPoints(speedCalibrationParams_t *params, int &length){
    if(this->_sizeOfPoints >= 2){
        for(int i = 0; i < length; i++){
            params[i].speed = this->_params[i].speed;
            params[i].Kp = this->_params[i].Kp;
            params[i].Ki = this->_params[i].Ki;
            params[i].Kd = this->_params[i].Kd;
            params[i].maxDeviation = this->_params[i].maxDeviation;
        }
        return true;
    }else{
        return false;
    }
}

void SpeedCalibration::setFlashOperationType(uint32_t flashOperationType){
    this->_flashOperationType = flashOperationType;
}

void SpeedCalibration::setPointsToFlash(speedCalibrationParams_t *params, int size){
    int arraySize = size * sizeof(speedCalibrationParams_t);
    char *buffer = new char[arraySize];
    for (int i = 0; i < size; i++){
        basic.writeValueToBytesBuffer(buffer, params[i].speed, 5 * i * sizeof params[i].speed);
        basic.writeValueToBytesBuffer(buffer, params[i].Kp, 5 * i * sizeof params[i].Kp + sizeof params[i].speed);
        basic.writeValueToBytesBuffer(buffer, params[i].Ki, 5 * i * sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
        basic.writeValueToBytesBuffer(buffer, params[i].Kd, 5 * i * sizeof params[i].Kd + sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
        basic.writeValueToBytesBuffer(buffer, params[i].maxDeviation, 5 * i * sizeof params[i].maxDeviation + sizeof params[i].Kd + sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
    }
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.setWritingParams(buffer, arraySize, POSITION_SPEED_CALIBRATION_POINTS_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(buffer, arraySize, POSITION_SPEED_CALIBRATION_POINTS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] buffer;
    char *sizeBuffer = new char[sizeof(int)];
    basic.writeValueToBytesBuffer(sizeBuffer, size);
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.setWritingParams(sizeBuffer, sizeof(int), POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] sizeBuffer;
}

void SpeedCalibration::getPointsSizeFromFlash(int *size){
    char *sizeBuffer = new char[sizeof(int)];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(sizeBuffer, POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, sizeof(int));
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
        break;
    default:
        break;
    }
    basic.writeBytesBufferToValue(sizeBuffer, size);
    delete[] sizeBuffer;
}

void SpeedCalibration::getPointsFromFlash(speedCalibrationParams_t *params, int size){
    if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(speedCalibrationParams_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(buffer, POSITION_SPEED_CALIBRATION_POINTS_FLASH_OFFSET, arraySize);
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(buffer, arraySize, POSITION_SPEED_CALIBRATION_POINTS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    for(int i = 0; i < size; i++){
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double),                      &params[i].speed);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double),     &params[i].Kp);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 2, &params[i].Ki);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 3, &params[i].Kd);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 4, &params[i].maxDeviation);  
    }
    delete[] buffer;
  }
}

void SpeedCalibration::setStrainPointsToFlash(speedCalibrationParams_t *params, int size){
    int arraySize = size * sizeof(speedCalibrationParams_t);
    char *buffer = new char[arraySize];
    for (int i = 0; i < size; i++){
        basic.writeValueToBytesBuffer(buffer, params[i].speed, 5 * i * sizeof params[i].speed);
        basic.writeValueToBytesBuffer(buffer, params[i].Kp, 5 * i * sizeof params[i].Kp + sizeof params[i].speed);
        basic.writeValueToBytesBuffer(buffer, params[i].Ki, 5 * i * sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
        basic.writeValueToBytesBuffer(buffer, params[i].Kd, 5 * i * sizeof params[i].Kd + sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
        basic.writeValueToBytesBuffer(buffer, params[i].maxDeviation, 5 * i * sizeof params[i].maxDeviation + sizeof params[i].Kd + sizeof params[i].Ki + sizeof params[i].speed + sizeof params[i].Kp);
    }
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.setWritingParams(buffer, arraySize, STRAIN_SPEED_CALIBRATION_POINTS_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(buffer, arraySize, STRAIN_SPEED_CALIBRATION_POINTS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] buffer;
    char *sizeBuffer = new char[sizeof(int)];
    basic.writeValueToBytesBuffer(sizeBuffer, size);
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.setWritingParams(sizeBuffer, sizeof(int), STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] sizeBuffer;
}

void SpeedCalibration::getStrainPointsSizeFromFlash(int *size){
    char *sizeBuffer = new char[sizeof(int)];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(sizeBuffer, STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, sizeof(int));
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
        break;
    default:
        break;
    }
    basic.writeBytesBufferToValue(sizeBuffer, size);
    delete[] sizeBuffer;
}

void SpeedCalibration::getStrainPointsFromFlash(speedCalibrationParams_t *params, int size){
    if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(speedCalibrationParams_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(buffer, STRAIN_SPEED_CALIBRATION_POINTS_FLASH_OFFSET, arraySize);
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(buffer, arraySize, STRAIN_SPEED_CALIBRATION_POINTS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    for(int i = 0; i < size; i++){
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double),                      &params[i].speed);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double),     &params[i].Kp);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 2, &params[i].Ki);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 3, &params[i].Kd);
        basic.writeBytesBufferToValue(buffer + i * 5 * sizeof(double) + sizeof(double) * 4, &params[i].maxDeviation);  
    }
    delete[] buffer;
  }
}

void SpeedCalibration::sortBySpeed(void){
    for(int i = 0; i < this->_sizeOfPoints - 1; i++){
        for(int j = i + 1; j < this->_sizeOfPoints; j++){
            if(this->_params[i].speed > this->_params[j].speed){
                speedCalibrationParams_t tmp = this->_params[i];
                this->_params[i] = this->_params[j];
                this->_params[j] = tmp;
            }
        }
    }
}

void SpeedCalibration::getValue(double speed, double &Kp, double &Ki, double &Kd, double &maxDeviation){
    if(this->getCalculatingProcess()){
        this->sortBySpeed();
        for(int i = 0; i < this->_sizeOfPoints; i++){
            if(speed <= this->_params[i].speed){
                Kp = this->_params[i].Kp;
                Ki = this->_params[i].Ki;
                Kd = this->_params[i].Kd;
                maxDeviation = this->_params[i].maxDeviation;
                return;
            }
        }
    }
}

uint32_t SpeedCalibration::getMaxPoints(){
    return _maxPoints;
}

void SpeedCalibration::setCalculatingProcess(uint8_t calculatingProcess){
    this->calculatingProcess = calculatingProcess;
}

uint8_t SpeedCalibration:: getCalculatingProcess(void){
    return this->calculatingProcess;
}