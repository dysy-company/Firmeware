#ifndef INTERNAL_FLASH_T_HPP
#define INTERNAL_FLASH_T_HPP

template <typename T> void InternalFlash::setWritingParams(T value, int offset){
    this->_buf = new char[sizeof(T)];
    this->clearBuf = true;
    basic.writeValueToBytesBuffer(this->_buf, value, 0);
    this->setWritingParams(this->_buf, sizeof(T), offset, true);

}


template <typename T> void InternalFlash::Writing_To_Flash_Through_Buf_Sector(T value, int offset){
    this->setWritingParams(value, offset);
    this->Writing_To_Flash_Through_Buf_Sector();
    delete[] this->_buf;
}

template <typename T> int InternalFlash::readInOneSector(T &value, uint32_t offset){
    char *buffer = new char[sizeof(T)];
    int result = this->readInOneSector(buffer, offset, sizeof(T));
    T dummy;
    basic.writeBytesBufferToValue(buffer, &dummy);
    value = dummy;
    delete[] buffer;
    return result;
}

#endif