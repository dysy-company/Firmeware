#include <BasicElements.h>

double BasicElements::uint64ToDouble (uint64_t value){
    //writing 8 bytes to double type
  double *ref = (double*)&value;
  //double result = *ref;
  return *ref;
}

float BasicElements::uint32ToFloat (uint32_t value){
    //writing 4 bytes to float type
  float *ref = (float*)&value;
  //float result = *ref;
  return *ref;
}

uint32_t BasicElements::floatToUint32 (float value){
    //writing 4 bytes to float type
  uint32_t *ref = (uint32_t*)&value;
  //uint32_t result = *ref;
  return *ref;
}

uint64_t BasicElements::doubleToUint64 (double value){
    //writing 4 bytes to float type
  uint64_t *ref = (uint64_t*)&value;
  //uint64_t result = *ref;
  return *ref;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint64_t value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint64_t value, int offset){
  buffer[offset + 7] = value & 0xFF;
  buffer[offset + 6] = (value >> 8) & 0xFF;
  buffer[offset + 5] = (value >> 16) & 0xFF;
  buffer[offset + 4] = (value >> 24) & 0xFF;
  buffer[offset + 3] = (value >> 32) & 0xFF;
  buffer[offset + 2] = (value >> 40) & 0xFF;
  buffer[offset + 1] = (value >> 48) & 0xFF;
  buffer[offset + 0] = (value >> 56) & 0xFF; 
  return 8;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint32_t value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint32_t value, int offset){
  buffer[offset + 3] = value & 0xFF;
  buffer[offset + 2] = (value >> 8) & 0xFF;
  buffer[offset + 1] = (value >> 16) & 0xFF;
  buffer[offset + 0] = (value >> 24) & 0xFF; 
  return 4;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, int32_t value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, int32_t value, int offset){
  buffer[offset + 3] = value & 0xFF;
  buffer[offset + 2] = (value >> 8) & 0xFF;
  buffer[offset + 1] = (value >> 16) & 0xFF;
  buffer[offset + 0] = (value >> 24) & 0xFF; 
  return 4;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, int value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, int value, int offset){
  buffer[offset + 3] = value & 0xFF;
  buffer[offset + 2] = (value >> 8) & 0xFF;
  buffer[offset + 1] = (value >> 16) & 0xFF;
  buffer[offset + 0] = (value >> 24) & 0xFF; 
  return 4;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, double value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, double value, int offset){
  uint64_t doubleValue = doubleToUint64(value);
  buffer[offset + 7] = doubleValue & 0xFF;
  buffer[offset + 6] = (doubleValue >> 8) & 0xFF;
  buffer[offset + 5] = (doubleValue >> 16) & 0xFF;
  buffer[offset + 4] = (doubleValue >> 24) & 0xFF;
  buffer[offset + 3] = (doubleValue >> 32) & 0xFF;
  buffer[offset + 2] = (doubleValue >> 40) & 0xFF;
  buffer[offset + 1] = (doubleValue >> 48) & 0xFF;
  buffer[offset + 0] = (doubleValue >> 56) & 0xFF;
  return 8;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, long long value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, long long value, int offset){
  buffer[offset + 7] = value & 0xFF;
  buffer[offset + 6] = (value >> 8) & 0xFF;
  buffer[offset + 5] = (value >> 16) & 0xFF;
  buffer[offset + 4] = (value >> 24) & 0xFF;
  buffer[offset + 3] = (value >> 32) & 0xFF;
  buffer[offset + 2] = (value >> 40) & 0xFF;
  buffer[offset + 1] = (value >> 48) & 0xFF;
  buffer[offset + 0] = (value >> 56) & 0xFF;
  return 8;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, float value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, float value, int offset){
  uint32_t floatValue = floatToUint32(value);
  buffer[offset + 3] = floatValue & 0xFF;
  buffer[offset + 2] = (floatValue >> 8) & 0xFF;
  buffer[offset + 1] = (floatValue >> 16) & 0xFF;
  buffer[offset + 0] = (floatValue >> 24) & 0xFF; 
  return 4;
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, std::string value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, std::string value, int offset){
  memcpy(buffer + offset, value.c_str(), value.length());
  return value.length();
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint16_t value){
  return this->writeValueToBytesBuffer(buffer, value, 0);
}
uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, uint16_t value, int offset){
  buffer[offset + 1] = value & 0xFF;
  buffer[offset + 0] = (value >> 8) & 0xFF;
  return 2;
}

void BasicElements::writeBytesBufferToValue (char *buffer, uint64_t *value){
  uint64_t dummy = 0;
  for(int i = 0; i < 8; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, long long *value){
  long long dummy = 0;
  for(int i = 0; i < 8; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, uint32_t *value){
  uint32_t dummy = 0;
  for(int i = 0; i < 4; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, int32_t *value){
  int32_t dummy = 0;
  for(int i = 0; i < 4; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, int *value){
  int dummy = 0;
  for(int i = 0; i < 4; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, uint8_t *value){
  uint8_t dummy = 0;
  for(int i = 0; i < 1; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeBytesBufferToValue (char *buffer, double *value){
  uint64_t buf = 0;
  for(int i = 0; i < 8; i++){
    buf = buf << 8;
    buf = buf | buffer[i];
  }
  *value = uint64ToDouble(buf);
}

void BasicElements::writeBytesBufferToValue (char *buffer, float *value){
  uint32_t buf = 0;
  for(int i = 0; i < 4; i++){
    buf = buf << 8;
    buf = buf | buffer[i];
  }
  *value = uint32ToFloat(buf);
}

void BasicElements::writeBytesBufferToValue (char* buffer, std::string *value){
  value->assign(buffer);
}

void BasicElements::writeBytesBufferToValue (char *buffer, uint16_t *value){
  uint16_t dummy = 0;
  for(int i = 0; i < 2; i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

void BasicElements::writeArrayToArray (char *array1, int startIndexArray1, int sizeOfArray1, char *array2, int startIndexArray2){
  std::copy(array1 + startIndexArray1, array1 + sizeOfArray1 - startIndexArray1, array2 + startIndexArray2);
  /*int counter = 0;
  for(int i = startIndexArray1; i < sizeOfArray1; i++){
    array2[counter + startIndexArray2] = array1[i];
    counter++;
  }*/
}

void BasicElements::writePartOfArrayToArray(char *array1, int startIndexArray1, int sizeOfArray1, char *array2, int startIndexArray2){
  int counter = 0;
  for(int i = startIndexArray1; i < startIndexArray1 + sizeOfArray1; i++){
    array2[counter + startIndexArray2] = array1[i];
    counter++;
  }
}

string BasicElements::modeToString(uint32_t mode){
  string tempStr = "\n";
  switch (mode)
  {
  case DAC_STATE_NONE:
    tempStr += "DAC_STATE_NONE";
    break;
  case DAC_STATE_CONST_LEVEL:
    tempStr += "DAC_STATE_CONST_LEVEL";
    break;
  case DAC_STATE_DISP_PULSE:
    tempStr += "DAC_STATE_PULSE";
    break;
  case DAC_STATE_DISP_SIN:
    tempStr += "DAC_STATE_DISP_SIN";
    break;
  case DAC_STATE_CALIBRATION:
    tempStr += "DAC_STATE_CALIBRATION";
    break;
  case DAC_STATE_COS:
    tempStr += "DAC_STATE_COS";
    break;
  case DAC_STATE_SIN:
    tempStr += "DAC_STATE_SIN";
    break;
  case DAC_STATE_UNDEFINED:
    tempStr += "DAC_STATE_UNDEFINED";
    break;
  case DAC_STATE_EXPERIMENTAL:
    tempStr += "DAC_STATE_EXPERIMENTAL";
    break;
  
  default:
    tempStr += "Unknown mode"; 
    break;
  }
  tempStr += "\n\r";
  return tempStr;
}

int BasicElements::areBytesMatchedSpecificValue(char *buf, uint32_t size_of_buf, char specific_value, uint32_t index_for_start_checking, uint32_t size_of_checked_subbuf){
    int are_matched = 1;
    uint32_t end_index = index_for_start_checking + size_of_checked_subbuf;
    if ((buf != nullptr) && (end_index <= size_of_buf) && (index_for_start_checking < size_of_buf) && (size_of_checked_subbuf <= size_of_buf)){
        for (uint32_t i = index_for_start_checking; i < end_index; i++){
            if (buf[i] != specific_value){
                are_matched = 0;
                break;
            }
        }
    }
    else{
        are_matched = -1;
    }
    return are_matched;
}

void BasicElements::viewArr(char *arr, int size_of_arr){
  char symb;
  int counter = 0;
  for (int i = 0; i < size_of_arr; i++){
    symb = arr[i];
    counter++;
  }
}

uint_least32_t BasicElements::Crc32(const unsigned char * buf, size_t len){
  uint_least32_t crc = 0xFFFFFFFF;
  while (len--)
      crc = (crc >> 8) ^ this->Crc32Table[(crc ^ *buf++) & 0xFF];
  return crc ^ 0xFFFFFFFF;
}

void BasicElements::writeBytesBufferToValue(char* buffer, COMMAND *value){
  uint32_t dummy = 0;
  for(int i = 0; i < (int)(sizeof(COMMAND)); i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = static_cast<COMMAND>(dummy);
}

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, COMMAND value, int offset){
    int size = sizeof(COMMAND);
    int shift = 0;
    for (int i = size - 1; i >= 0; i-- ){
      buffer[offset + i] = (static_cast<uint32_t>(value) >> shift) & 0xFF;
      shift += 8;
    }
    return (uint32_t)size;
};

uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, COMMAND value){
    int size = sizeof(COMMAND);
    int shift = 0;
    for (int i = size - 1; i >= 0; i-- ){
      buffer[i] = (static_cast<uint32_t>(value) >> shift) & 0xFF;
      shift += 8;
    }
    return (uint32_t)size;
};