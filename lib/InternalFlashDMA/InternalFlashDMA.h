#ifndef INTERNAL_FLASH_DMA_H
#define INTERNAL_FLASH_DMA_H

#include <mbed.h>
#include <FlashIAP.h>

#include "..//..//include//Boards//Board.h"
#include "..//BasicElements/BasicElements.h"
#if BOARD_INDEX == 2
#define DMA_INSTANCE               DMA2_Stream0
#define DMA_REQUEST                DMA_REQUEST_MEM2MEM
#define DMA_INSTANCE_IRQ           DMA2_Stream0_IRQn
#define DMA_INSTANCE_IRQHANDLER    DMA2_Stream0_IRQHandler
#endif
#if BOARD_INDEX == 3
#define DMA_INSTANCE               DMA2_Stream0
#define DMA_CHANNEL                DMA_CHANNEL_0
#define DMA_REQUEST                DMA_REQUEST_MEM2MEM
#define DMA_INSTANCE_IRQ           DMA2_Stream0_IRQn
#define DMA_INSTANCE_IRQHANDLER    DMA2_Stream0_IRQHandler

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes */

#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes */

#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

#define ADDR_FLASH_SECTOR_12    ((uint32_t)0x08100000) /* Base address of Sector 12, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13    ((uint32_t)0x08104000) /* Base address of Sector 13, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14    ((uint32_t)0x08108000) /* Base address of Sector 14, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15    ((uint32_t)0x0810C000) /* Base address of Sector 15, 16 Kbytes */

#define ADDR_FLASH_SECTOR_16    ((uint32_t)0x08110000) /* Base address of Sector 16, 64 Kbytes */

#define ADDR_FLASH_SECTOR_17    ((uint32_t)0x08120000) /* Base address of Sector 17, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18    ((uint32_t)0x08140000) /* Base address of Sector 18, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19    ((uint32_t)0x08160000) /* Base address of Sector 19, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20    ((uint32_t)0x08180000) /* Base address of Sector 20, 128 Kbytes */
#define ADDR_FLASH_SECTOR_21    ((uint32_t)0x081A0000) /* Base address of Sector 21, 128 Kbytes */
#define ADDR_FLASH_SECTOR_22    ((uint32_t)0x081C0000) /* Base address of Sector 22, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23    ((uint32_t)0x081E0000) /* Base address of Sector 23, 128 Kbytes */
#endif

typedef struct {
    char *buf;
    uint32_t size_of_buf;
    uint32_t flashOffset;
} gV_t;

class InternalFlashDMA{
    public:
        InternalFlashDMA();
        ~InternalFlashDMA();
        template <typename T> void setParams(T value, uint32_t offset);
        template <typename T> void setParamsForQueue(T value, uint32_t offset);
        void addToQueue(char *buf, uint32_t size_of_buf, uint32_t flashOffset);
        void writeToFlashViaQueue(void);
        int readFromFlash(char *buf, uint32_t size_of_buf, uint32_t flashOffset);
        void writeToFlash(char *buf, uint32_t size_of_buf, uint32_t flashOffset);
        template <typename T> int readFromFlash(T &value, uint32_t offset);
        int readFromFlash(std::string &value, uint32_t offset, uint32_t size);
        template<typename T> void setParamsBuffer(char *buff, uint32_t offset, uint32_t size);
    private:
        void eraseSector(uint32_t addr, uint32_t size);
        void setPGBit(bool state);
        void getSector(uint32_t addr);
        BasicElements basic;
        FlashIAP _flash;
        MemoryPool<gV_t, 200> mpool;
        Queue <gV_t, 200> GV;
        Semaphore *block;
        uint32_t data;
        int _size;
        uint32_t _index;
        char *_buf;
        uint32_t VoltageRange = FLASH_VOLTAGE_RANGE_3;
        uint32_t sector;

};

template <> void InternalFlashDMA::setParams<std::string>(std::string value, uint32_t offset);
template <> void InternalFlashDMA::setParamsForQueue<std::string>(std::string value, uint32_t offset);
#include "InternalFlashDMA.t.hpp"
#endif