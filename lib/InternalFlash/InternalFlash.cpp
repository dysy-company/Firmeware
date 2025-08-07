#include "InternalFlash.h"

template <> void InternalFlash::Writing_To_Flash_Through_Buf_Sector<std::string>(std::string value, int offset){
    this->setWritingParams(value, offset);
    this->Writing_To_Flash_Through_Buf_Sector();
}

template <> void InternalFlash::setWritingParams<std::string>(std::string value, int offset){
    value.push_back('\0');
    uint32_t size = value.size();
    this->_buf = new char[size];
    std::memset(this->_buf, 0, size);
    basic.writeValueToBytesBuffer(this->_buf, value);
    this->setWritingParams(this->_buf, size, offset, true);

}

template void InternalFlash::Writing_To_Flash_Through_Buf_Sector<std::string>(std::string, int);
template void InternalFlash::setWritingParams<std::string>(std::string, int);

int InternalFlash::readInOneSector(std::string &value, uint32_t offset, uint32_t size){
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
    memset(buffer.get(), 0, size);
    int result = this->readInOneSector(buffer.get(), offset, size);
    std::string dummy;
    basic.writeBytesBufferToValue(buffer.get(), &dummy);
    value = dummy;
    return result;
}

void InternalFlash::setWritingParams(char *buf, uint32_t size_of_buf, int address_offset_in_bytes, bool is_rewrite_enabled){
    this->_buf = buf;
    this->_size_of_buf = size_of_buf;
    this->_address_offset_in_bytes = address_offset_in_bytes;
    this->_is_rewrite_enabled = is_rewrite_enabled;
}

void InternalFlash::Writing_To_Flash_Through_Buf_Sector(char *buf, uint32_t size_of_buf, int address_offset_in_bytes, bool is_rewrite_enabled){
    this->setWritingParams(buf, size_of_buf, address_offset_in_bytes, is_rewrite_enabled);
    this->Writing_To_Flash_Through_Buf_Sector();
}

int InternalFlash::readInOneSector(char *read_buf, uint32_t reading_start_address, uint32_t size){
    int err_code = 0;
    if(this->operationBlock->try_acquire_for(200ms)){
        uint32_t start_of_sector_for_read;
        if ((read_buf != nullptr) && (reading_start_address >= this->_start_of_flash) && (reading_start_address < this->_end_of_flash)){
            start_of_sector_for_read = reading_start_address & FLASH_SECTOR_ADDRESS_MASK;
            if (reading_start_address + size <= start_of_sector_for_read + this->_size_of_sector){
                //err_code = this->_flash.read(read_buf, reading_start_address, size);
                for(uint32_t index = 0; index < size; index++)
                {
                  read_buf[index] = *(uint8_t*)(reading_start_address + index);
                  __DSB();
                }
            }
            else
                err_code = -1;
        }
        else{
            err_code = -1;
        }
        this->operationBlock->release();
    }
    return err_code;
}

/* Старый вариант реализации записи во FLASH-память
void InternalFlash::Writing_To_Flash_Thread(){
    char *read_buf = nullptr, *dop_bytes_at_begin = nullptr, *dop_bytes_at_end = nullptr;
    int err_code;
    uint32_t address, start_of_sector, start_of_program_page_for_write, end_of_program_page_for_write, number_of_dop_bytes_at_begin, number_of_dop_bytes_at_end, current_address, current_size, end_of_buf_address;
    if ((this->_buf != nullptr) && (this->_size_of_buf > 0))
    {
        if  (this->_address_offset_in_bytes >= 0)
            address = this->_start_of_flash + this->_address_offset_in_bytes;
        else
            address = this->_end_of_flash + this->_address_offset_in_bytes;
        end_of_buf_address = address + this->_size_of_buf;
        //половина условий проверки сделаны для исключения неправильной работы при передачи
        //слишком большого размера записываемого буфера или слишком большого смещения в байтах
        if ((address >= this->_start_of_flash) && (address < this->_end_of_flash) && (end_of_buf_address <= this->_end_of_flash) && (end_of_buf_address > this->_start_of_flash)){
            start_of_program_page_for_write = address & FLASH_PAGE_ADDRESS_MASK;
            number_of_dop_bytes_at_begin = address - start_of_program_page_for_write;
            end_of_program_page_for_write = end_of_buf_address & FLASH_PAGE_ADDRESS_MASK;
            number_of_dop_bytes_at_end = this->_size_of_page - (end_of_buf_address - end_of_program_page_for_write);
            if (number_of_dop_bytes_at_begin != 0){
                dop_bytes_at_begin = new char[number_of_dop_bytes_at_begin];
                basic.writeArrayToArray(this->_buf, this->_size_of_buf - number_of_dop_bytes_at_begin, number_of_dop_bytes_at_begin, dop_bytes_at_begin, 0);
            }
            if (number_of_dop_bytes_at_end != 0){
                dop_bytes_at_end = new char[number_of_dop_bytes_at_end];
                basic.writeArrayToArray(this->_buf, 0, number_of_dop_bytes_at_end, dop_bytes_at_end, 0);
                //увеличение на одну страницу адреса последней (незаписываемой) страницы
                end_of_program_page_for_write += this->_size_of_page;
            }
            read_buf = new char[this->_size_of_sector];
            start_of_sector = start_of_program_page_for_write & FLASH_PAGE_ADDRESS_MASK;
            //посекторное чтение данных по нужным адресам с возможностью очистки секторов
            current_address = start_of_program_page_for_write;
            while(current_address < end_of_program_page_for_write){
                start_of_sector += this->_size_of_sector;
                current_size = end_of_program_page_for_write > start_of_sector ? start_of_sector - current_address : end_of_program_page_for_write - current_address;
                err_code = this->_flash.read(read_buf, current_address, current_size);
                if (err_code != 0){
                    err_code = basic.areBytesMatchedSpecificValue(read_buf, this->_size_of_sector, this->_erased_value, 0, current_size);
                    if ((err_code == 0) && (this->_is_rewrite_enabled)){
                        err_code = this->_flash.erase(start_of_sector - this->_size_of_sector, this->_size_of_sector);
                        if (err_code != 0)
                            break;
                    }
                    else if (err_code != 1)
                        break;
                }
                else
                    break;
                current_address = start_of_sector;
            }
            if (((err_code == 0) && (this->_is_rewrite_enabled)) || (err_code == 1)){
                //посекторная запись
                current_address = start_of_program_page_for_write;
                if (dop_bytes_at_begin != nullptr)
                    basic.writeArrayToArray(dop_bytes_at_begin, 0, number_of_dop_bytes_at_begin, read_buf, 0);
                while(current_address < end_of_program_page_for_write){
                    start_of_sector += this->_size_of_sector;
                    current_size = end_of_program_page_for_write > start_of_sector ? start_of_sector - current_address : end_of_program_page_for_write - current_address;
                    err_code = this->_flash.read(read_buf, current_address, current_size);
                    if (err_code != 0){
                        err_code = basic.areBytesMatchedSpecificValue(read_buf, this->_size_of_sector, this->_erased_value, 0, current_size);
                        if ((err_code == 0) && (this->_is_rewrite_enabled)){
                            err_code = this->_flash.erase(start_of_sector - this->_size_of_sector, this->_size_of_sector);
                            if (err_code != 0)
                                break;
                        }
                        else if (err_code != 1)
                            break;
                    }
                    else
                        break;
                    current_address = start_of_sector;
                }    
            }

            if (dop_bytes_at_begin != nullptr)
                delete [] dop_bytes_at_begin;
            if (dop_bytes_at_end != nullptr)
                delete [] dop_bytes_at_end;
            delete [] read_buf;
        }
    }
}*/

void InternalFlash::Writing_To_Flash_Through_Buf_Sector(void){
    if(this->operationBlock->try_acquire_for(200ms)){
        int err_code;
        uint32_t address, start_of_sector_for_write;
        if ((this->_buf != nullptr) && (this->_size_of_buf > 0) && (this->_size_of_buf <= this->_size_of_sector)){
            //if  (this->_address_offset_in_bytes >= 0)
                address = this->_address_offset_in_bytes;//this->_start_of_flash + this->_address_offset_in_bytes;
            //else
                //последний сектор считается буферным, поэтому в него запись не осуществляется
                //и концом FLASH-памяти считается адрес начала этого буферного сектора
            //    address = this->_start_of_buf_sector + this->_address_offset_in_bytes;
            //половина условий проверки сделаны для исключения неправильной работы при передачи
            //слишком большого размера записываемого буфера или слишком большого смещения в байтах
            if ((address >= this->_start_of_flash) && (address < this->_start_of_buf_sector) && (address + this->_size_of_buf <= this->_start_of_buf_sector) && (address + this->_size_of_buf > this->_start_of_flash)){
                start_of_sector_for_write = address & FLASH_SECTOR_ADDRESS_MASK;
                //по договорённости, записываемый массив не может размещаться в нескольких секторах
                if (address + this->_size_of_buf <= start_of_sector_for_write + this->_size_of_sector){
                    //запись текущего сектора в буферный без изменений
                    err_code = this->overwriteOneSectorToAnother(start_of_sector_for_write, this->_start_of_buf_sector);
                    if (err_code == 0){
                        address = (address & (FLASH_OFFSET_OF_PAGE_MASK | FLASH_OFFSET_IN_PAGE_MASK)) + this->_start_of_buf_sector;
                        err_code = this->overwriteOneSectorToAnother(this->_start_of_buf_sector, start_of_sector_for_write, this->_buf, address, address + this->_size_of_buf);
                        //строки для отладки
                        //if (err_code == 0){
                        //    char *read_buf = new char[this->_size_of_buf];
                        //    address = (address & (FLASH_OFFSET_OF_PAGE_MASK | FLASH_OFFSET_IN_PAGE_MASK)) + start_of_sector_for_write;
                        //    this->_flash.read(read_buf, address, this->_size_of_buf);
                        //    basic.viewArr(read_buf, this->_size_of_buf);
                        //    this->_flash.read(read_buf, address - this->_size_of_buf, this->_size_of_buf);
                        //    basic.viewArr(read_buf, this->_size_of_buf);
                        //    this->_flash.read(read_buf, address - 2 * this->_size_of_buf, this->_size_of_buf);
                        //    basic.viewArr(read_buf, this->_size_of_buf);
                        //    delete [] read_buf;
                        //}
                    }
                }
            }
        }
        if(this->clearBuf){
            delete[] this->_buf;
            this->clearBuf = false;
        }
        this->operationBlock->release();
    }
}

InternalFlash::InternalFlash(){
    #if BOARD_INDEX == 2
    this->clearBuf = false;
    this->operationBlock = new Semaphore(1);
    int err_code = this->_flash.init();
    if (err_code == 0){
        this->_start_of_flash = this->_flash.get_flash_start();
        this->_size_of_flash = this->_flash.get_flash_size();
        this->_end_of_flash = this->_start_of_flash + this->_size_of_flash;
        //считается, что размеры FLASH-секторов одинаковые
        this->_size_of_sector = this->_flash.get_sector_size(this->_start_of_flash);
        this->_size_of_page = this->_flash.get_page_size();
        //буферным сектором выбран последний сектор
        this->_start_of_buf_sector = this->_end_of_flash - this->_size_of_sector;
        this->_erased_value = static_cast<char>(this->_flash.get_erase_value());
    }
    #endif
    #if BOARD_INDEX == 3
    this->clearBuf = false;
    this->operationBlock = new Semaphore(1);
    int err_code = this->_flash.init();
    if (err_code == 0){
        this->_start_of_flash = 135397376; //+ this->_size_of_sector; //this->_flash.get_flash_start();
        this->_size_of_flash = 917504;//917504 - this->_size_of_sector; //this->_flash.get_flash_size();
        this->_end_of_flash = this->_start_of_flash + this->_size_of_flash; // - this->_size_of_sector;
        //считается, что размеры FLASH-секторов одинаковые
        this->_size_of_sector = FLASH_SECTOR_SIZE; //131072; //this->_flash.get_sector_size(this->_start_of_flash);
        this->_size_of_page = this->_flash.get_page_size();
        //буферным сектором выбран последний сектор
        this->_start_of_buf_sector = this->_end_of_flash - this->_size_of_sector;
        this->_erased_value = static_cast<char>(this->_flash.get_erase_value());
    }
    #endif
}

InternalFlash::~InternalFlash(){
    this->_flash.deinit();
    if (this->_buf != nullptr){
        delete [] this->_buf;
    }
    delete this->operationBlock;
}

int InternalFlash::overwriteOneSectorToAnother(uint32_t start_of_first_sector, uint32_t start_of_another_sector){
    char *buf_of_page = nullptr;
    int err_code;
    uint32_t addr, end_of_first_sector;
    if ((start_of_first_sector != start_of_another_sector) && ((start_of_first_sector & FLASH_SECTOR_ADDRESS_MASK) == start_of_first_sector) && ((start_of_another_sector & FLASH_SECTOR_ADDRESS_MASK) == start_of_another_sector)){
        err_code = this->_flash.erase(start_of_another_sector, this->_size_of_sector);
        if (err_code == 0){
            end_of_first_sector = start_of_first_sector + this->_size_of_sector;
            buf_of_page = new char[this->_size_of_page];
            for (addr = start_of_first_sector; addr < end_of_first_sector; addr += this->_size_of_page){
                //err_code = this->_flash.read(buf_of_page, addr, this->_size_of_page);
                for(uint32_t index = 0; index < this->_size_of_page; index++)
                {
                  buf_of_page[index] = *(uint8_t*)(addr + index);
                  __DSB();
                }
                if (err_code != 0)
                    break;
                err_code = this->_flash.program(buf_of_page, (addr & FLASH_OFFSET_OF_PAGE_MASK) + start_of_another_sector, this->_size_of_page);
                if (err_code != 0)
                    break;
            }
        }
    }
    else
        err_code = -1;
    if (buf_of_page != nullptr)
        delete [] buf_of_page;
    return err_code;
}

int InternalFlash::overwriteOneSectorToAnother(uint32_t start_of_first_sector, uint32_t start_of_another_sector,  char *changing_buf, uint32_t start_address_for_changing, uint32_t end_address_for_changing){
    char *buf_of_page = nullptr;
    int err_code;
    uint32_t addr, start_of_first_page_for_changing, start_of_last_page_for_changing, offset_in_page, end_of_first_sector, count_of_changed_bytes, changing_buf_ind = 0;
    if ((start_of_first_sector != start_of_another_sector) && (changing_buf != nullptr) &&
            (end_address_for_changing >= start_address_for_changing) && ((start_address_for_changing & FLASH_SECTOR_ADDRESS_MASK) == start_of_first_sector) &&
            (((end_address_for_changing - 1) & FLASH_SECTOR_ADDRESS_MASK) == start_of_first_sector) &&((start_of_another_sector & FLASH_SECTOR_ADDRESS_MASK) == start_of_another_sector)){
        err_code = this->_flash.erase(start_of_another_sector, this->_size_of_sector);
        if (err_code == 0){
            start_of_first_page_for_changing = start_address_for_changing & FLASH_PAGE_ADDRESS_MASK;
            //end_address_for_changing - это адрес ячейки, следующей после записанного массива,
            //поэтому нужно вычитать 1 из end_address_for_changing при вычислении адреса начала последней записываемой страницы
            start_of_last_page_for_changing = (end_address_for_changing - 1) & FLASH_PAGE_ADDRESS_MASK;
            end_of_first_sector = start_of_first_sector + this->_size_of_sector;
            buf_of_page = new char[this->_size_of_page];
            for (addr = start_of_first_sector; addr < end_of_first_sector; addr += this->_size_of_page){
                //err_code = this->_flash.read(buf_of_page, addr, this->_size_of_page);
                for(uint32_t index = 0; index < this->_size_of_page; index++)
                {
                  buf_of_page[index] = *(uint8_t*)(addr + index);
                  __DSB();
                }
                if (err_code != 0)
                    break;
                if ((start_of_first_page_for_changing <= addr) && (addr < end_address_for_changing)){
                    if (start_of_first_page_for_changing == addr){
                        offset_in_page = start_address_for_changing & FLASH_OFFSET_IN_PAGE_MASK;
                        if (start_of_last_page_for_changing == addr){
                            count_of_changed_bytes = end_address_for_changing - start_of_last_page_for_changing - offset_in_page;
                        }
                        else{
                            count_of_changed_bytes = this->_size_of_page - offset_in_page;
                        }
                    }
                    else if (addr == start_of_last_page_for_changing){
                        offset_in_page = 0;
                        count_of_changed_bytes = end_address_for_changing - start_of_last_page_for_changing;
                    }
                    else{
                        offset_in_page = 0;
                        count_of_changed_bytes = this->_size_of_page;
                    }
                    basic.writePartOfArrayToArray(changing_buf, changing_buf_ind, count_of_changed_bytes, buf_of_page, offset_in_page);
                    changing_buf_ind += count_of_changed_bytes;
                }
                err_code = this->_flash.program(buf_of_page, (addr & FLASH_OFFSET_OF_PAGE_MASK) + start_of_another_sector, this->_size_of_page);
                if (err_code != 0)
                    break;
            }
        }
    }
    else
        err_code = -1;
    if (buf_of_page != nullptr)
        delete [] buf_of_page;
    return err_code;
}