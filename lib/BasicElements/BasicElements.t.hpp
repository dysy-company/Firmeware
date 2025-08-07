#ifndef Basic_Elements_t_hpp
#define Basic_Elements_t_hpp
#include "BasicElements.h"

template <typename T> void BasicElements::writeBytesBufferToValue(char* buffer, T *value){
  T dummy = 0;
  for(int i = 0; i < (int)(sizeof(T)); i++){
    dummy = dummy << 8;
    dummy = dummy | buffer[i];
  }
  *value = dummy;
}

template <typename T> uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, T value, int offset){
    int size = sizeof(T);
    int shift = 0;
    for (int i = size - 1; i >= 0; i-- ){
      buffer[offset + i] = (value >> shift) & 0xFF;
      shift += 8;
    }
    return (uint32_t)size;
};

template <typename T> uint32_t BasicElements::writeValueToBytesBuffer (char *buffer, T value){
    int size = sizeof(T);
    int shift = 0;
    for (int i = size - 1; i >= 0; i-- ){
      buffer[i] = (value >> shift) & 0xFF;
      shift += 8;
    }
    return (uint32_t)size;
};
//template <> uint32_t BasicElements<float>::writeValueToBytesBuffe (char *buffer, float value, int offset){
//    int size = sizeof(T);
//    int shift = 0;
//    for (int i = size - 1; i >= 0; i-- ){
//      buffer[offset + i] = (value >> shift) & 0xFF;
//      shift += 8;
//    }
//    return (uint32_t)size;
//};
#endif