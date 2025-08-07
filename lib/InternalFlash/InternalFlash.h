#ifndef INTERNAL_FLASH_H
#define INTERNAL_FLASH_H
#include <mbed.h>
#include <FlashIAP.h>

#include "..//BasicElements/BasicElements.h"

#include "..//..//include//Boards/Board.h"

extern BasicElements basic;

class InternalFlash{

    public:
        InternalFlash();
        ~InternalFlash();
        //функция установки параметров для записи данных во FLASH-память
        void setWritingParams(char *buf, uint32_t size_of_buf, int address_offset_in_bytes, bool is_rewrite_enabled);
        template <typename T> void setWritingParams(T value, int offset);
        //Старый вариант реализации записи во FLASH-память
        //void Writing_To_Flash_Thread();
        //Функция записи данных через буферный сектор через отдельный поток
        void Writing_To_Flash_Through_Buf_Sector(void);
        void Writing_To_Flash_Through_Buf_Sector(char *buf, uint32_t size_of_buf, int address_offset_in_bytes, bool is_rewrite_enabled);
        template <typename T> void Writing_To_Flash_Through_Buf_Sector(T value, int offset);
        //функция считывания в пределах одного сектора
        int readInOneSector(char *read_buf, uint32_t reading_start_address, uint32_t size);
        template <typename T> int readInOneSector(T &value, uint32_t offset);
        int readInOneSector(std::string &value, uint32_t offset, uint32_t size);
        
    private:
        FlashIAP _flash;
        Semaphore *operationBlock;
        uint32_t _start_of_flash;
        uint32_t _size_of_flash;
        uint32_t _end_of_flash;
        uint32_t _size_of_sector;
        uint32_t _size_of_page;
        uint32_t _start_of_buf_sector;
        char _erased_value;
        // Params for write
        char *_buf;
        bool clearBuf;
        uint32_t _size_of_buf;
        int _address_offset_in_bytes;
        bool _is_rewrite_enabled;
        
        
        /**Функция записи данных из одного сектора в другой сектор без возможности изменения части данных
         * 
         * @param start_of_first_sector Начальный адрес сектора, с которого считываются данные
         * @param start_of_another_sector Начальный адрес сектора, в который записываются данные
         * @return 0 при отсутствии ошибок,
         * -1 при обнаружении какой либо ошибки
         */
        int overwriteOneSectorToAnother(uint32_t start_of_first_sector, uint32_t start_of_another_sector);
        /**Функция записи данных из одного сектора в другой сектор с возможностью изменения части данных
         * 
         * @param start_of_first_sector Начальный адрес сектора, с которого считываются данные
         * @param start_of_another_sector Начальный адрес сектора, в который записываются данные
         * @param changing_buf Указатель на буфер, содержащий новое значение изменяемых байт
         * @param start_address_for_changing Начальный адрес в считываемом секторе, с которого начинается считывание данных не из сектора, а из буфера changing_buf
         * @param end_address_for_changing Адрес в считываемом секторе, с которого снова начинается считывание данных из сектора
         * @return 0 при отсутствии ошибок,
         * -1 при обнаружении какой либо ошибки
         */
        int overwriteOneSectorToAnother(uint32_t start_of_first_sector, uint32_t start_of_another_sector, char *changing_buf, uint32_t start_address_for_changing, uint32_t end_address_for_changing);
};

template <> void InternalFlash::Writing_To_Flash_Through_Buf_Sector<std::string>(std::string value, int offset);
template <> void InternalFlash::setWritingParams<std::string>(std::string value, int offset);
#include "InternalFlash.t.hpp"
#endif