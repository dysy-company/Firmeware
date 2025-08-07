#ifndef INTERNAL_FLASH_DMA_T_HPP
#define INTERNAL_FLASH_DMA_T_HPP

template <typename T> void InternalFlashDMA::setParams(T value, uint32_t offset){
    this->_buf = new char[sizeof(T)];
    basic.writeValueToBytesBuffer(this->_buf, value, 0);
    this->writeToFlash(this->_buf, sizeof(T), offset);
    delete[] this->_buf;
}

template<typename T> void InternalFlashDMA::setParamsBuffer(char *buff, uint32_t offset, uint32_t size){
    this->writeToFlash(buff, size, offset);
}

template <typename T> void InternalFlashDMA::setParamsForQueue(T value, uint32_t offset){
    this->_buf = new char[sizeof(T)];
    basic.writeValueToBytesBuffer(this->_buf, value, 0);
    this->addToQueue(this->_buf, sizeof(T), offset);
}

template <typename T> int InternalFlashDMA::readFromFlash(T &value, uint32_t offset){
    char *buffer = new char[sizeof(T)];
    int result = this->readFromFlash(buffer, sizeof(T), offset);
    T dummy;
    basic.writeBytesBufferToValue(buffer, &dummy);
    value = dummy;
    delete[] buffer;
    return result;
}

#endif