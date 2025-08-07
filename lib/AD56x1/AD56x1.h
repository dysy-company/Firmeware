/*
    Library for Microchip MCP4921/MCP4922 DAC chip.
    Created by Grigorii Bragin, March 1, 2020
*/
#ifndef AD56X1_h
#define AD56X1_h

#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define AD56x1_SPIx                             SPI5 //TODO DMA2
//Clocks defines
#define AD56x1_SPIx_CLK_ENABLE()                __HAL_RCC_SPI5_CLK_ENABLE()
#define AD56x1_SPIx_CLK_DISABLE()               __HAL_RCC_SPI5_CLK_DISABLE()
#define AD56x1_DMAx_CLK_ENABLE()                __HAL_RCC_DMA2_CLK_ENABLE()
#define AD56x1_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOF_CLK_ENABLE()
#define AD56x1_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define AD56x1_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOF_CLK_ENABLE()
#define AD56x1_SPIx_FORCE_RESET()               __HAL_RCC_SPI5_FORCE_RESET()
#define AD56x1_SPIx_RELEASE_RESET()             __HAL_RCC_SPI5_RELEASE_RESET()
//DMA defines
//#define AD56x1_SPIx_DMA_TX_IRQHandler           DMA2_Stream0_IRQHandler
#define AD56x1_SPIx_DMA_TX_IRQn                 DMA2_Stream0_IRQn
#define AD56x1_SPIx_DMA_TX_IRQn_PreemptPriority 1
#define AD56x1_SPIx_DMA_TX_IRQn_SubPriority     0
#if BOARD_INDEX == 2
#define AD56x1_SPIx_TX_DMA_REQUEST              DMA_REQUEST_SPI5_TX
#endif
#define AD56x1_SPIx_TX_DMA_STREAM               DMA2_Stream0   //for RX DMA2_Stream0
//SPI IRQ defines
//#ifndef SPI_5_IRQ_Handler
//#define AD56x1_SPIx_IRQHandler                  SPI5_IRQHandler
//#endif
#define AD56x1_SPIx_IRQn                        SPI5_IRQn
#define AD56x1_SPIx_IRQn_PreemptPriority        1
#define AD56x1_SPIx_IRQn_SubPriority            0
//PF7     ------> SPI5_SCK
#define AD56x1_SPIx_SCK_PIN                     GPIO_PIN_7
#define AD56x1_SPIx_SCK_GPIO_PORT               GPIOF
#define AD56x1_SPIx_SCK_AF                      GPIO_AF5_SPI5
//PF9     ------> SPI5_MOSI
#define AD56x1_SPIx_MOSI_PIN                    GPIO_PIN_9
#define AD56x1_SPIx_MOSI_GPIO_PORT              GPIOF
#define AD56x1_SPIx_MOSI_AF                     GPIO_AF5_SPI5
//PF6    ------> SPI5_NSS
#define AD56x1_SPIx_CS_PIN                      GPIO_PIN_6
#define AD56x1_SPIx_CS_GPIO_PORT                GPIOF
//#define AD56x1_SPIx_CS_AF                       GPIO_AF0

#include <mbed.h>

enum AD56x1TransferState{
	AD56x1_DMA_SPI_TRANSFER_WAIT,
	AD56x1_DMA_SPI_TRANSFER_IN_PROGRESS,
	AD56x1_DMA_SPI_TRANSFER_COMPLETE,
	AD56x1_DMA_SPI_TRANSFER_ERROR
};

enum AD56x1Type{
    AD5601,
    AD5611,
    AD5621
};

enum AD56x1PowerDownMode{
    NORMAL_OPERATION,   
    RES_1_KOHM_GND,     //1kOhm to GND
    RES_100_KOHM_GND,   //100kOhm to GND
    THREE_STATE
};

class AD56x1 {

    public:
        /*  spiPrescaler - divider for 10MHz clock. Max rate 10 MHz for AD56x1. So max prescaler 1.  */
        AD56x1(unsigned long spiPrescaler, AD56x1Type type);
        AD56x1(unsigned long spiPrescaler, AD56x1Type type, bool isInit);
        AD56x1(unsigned long spiPrescaler, AD56x1Type type, 
                AD56x1PowerDownMode powerDownMode, 
                float Vdd, 
                bool isInit, 
                DMA_HandleTypeDef *GLOBAL_SPI_DMA_IRQ_HANDLER,
                SPI_HandleTypeDef *GLOBAL_SPI_IRQ_HANDLER);
        /*  run initialize process for DMA channel    */
        int init(void);
        int deInit(void);
        /*  Vdd - power voltage (Volts);    */
        void setConfig(
            AD56x1PowerDownMode powerDownMode,
            float &Vdd);
        
        /*  Set Voltage at output of DAC with blocking operation by CPU   */
        uint32_t    setVoltageBlocking(float &setVoltage);
        uint32_t    setCodeBlocking(uint16_t &code);
        //launch DMA channel for setting DAC value
        uint32_t    startSettingVoltage(float &setVoltage);
        uint32_t    startSettingCode(uint16_t &setVoltage);
        //return status of DMA transaction
        uint32_t    getTransferStatus(void);
        //return last set DAC value
        uint16_t    getLastCode(void);
        float       getLastVoltage(void);
        //clear transfer status of DMA transaction
        void        clearTransferStatus(void);
        // Calculating Voltage via formula: Vout = Vdd * (code/2^n), Vdd - power supply, n - bit range of DAC
        float       calcVoltage(uint16_t &code);
        uint16_t    calcCode(float &voltage);
        //DMA_HandleTypeDef *SPI_DMA_IRQ_HANDLER;
        //SPI_HandleTypeDef *SPI_IRQ_HANDLER;
        void sharedConstructor (unsigned long spiPrescaler, AD56x1Type type);
    private:
        /*  DAC type    */
        AD56x1Type _type = AD5621;
        /*  Power down operation mode   */
        AD56x1PowerDownMode _powerDownMode = NORMAL_OPERATION;
        /*  Power Supply Voltage    */
        float _Vdd = 5;      
        /*  Data bits   */
        uint16_t _DACDataBits = 0x0;
        /*  Send raw data bits*/
        uint16_t _DACRawBits[1] = {0x0};
        /*  Bit weight  */
        float _lsbWeight = 0;
        uint16_t _mask = 0x0FFF;
        uint16_t _shift = 0;
        uint16_t _pwrDwnBits = 0; 
        void buildRawData (float &value);
        void buildRawData (uint16_t &code);
        
};
#endif