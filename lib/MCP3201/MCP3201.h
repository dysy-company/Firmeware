/*
    Library for Microchip MCP3201 ADC chip.
    Created by Grigorii Bragin, September 14, 2021
*/
#ifndef MCP3201_h
#define MCP3201_h

#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define MCP3201_SPIx                             SPI5
//Clocks defines
#define MCP3201_SPIx_CLK_ENABLE()                __HAL_RCC_SPI5_CLK_ENABLE()
#define MCP3201_SPIx_CLK_DISABLE()               __HAL_RCC_SPI5_CLK_DISABLE()
#define MCP3201_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define MCP3201_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOF_CLK_ENABLE()
#define MCP3201_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define MCP3201_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
//#define MCP3201_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOF_CLK_ENABLE()
#define MCP3201_SPIx_FORCE_RESET()               __HAL_RCC_SPI5_FORCE_RESET()
#define MCP3201_SPIx_RELEASE_RESET()             __HAL_RCC_SPI5_RELEASE_RESET()
//DMA defines
#define MCP3201_SPIx_DMA_RX_IRQHandler           DMA1_Stream3_IRQHandler
#define MCP3201_SPIx_DMA_RX_IRQn                 DMA1_Stream3_IRQn
#define MCP3201_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define MCP3201_SPIx_DMA_RX_IRQn_SubPriority     0
#define MCP3201_SPIx_RX_DMA_REQUEST              DMA_REQUEST_SPI5_RX
#define MCP3201_SPIx_RX_DMA_STREAM               DMA1_Stream3   //for TX DMA2_Stream2
//SPI IRQ defines
#define MCP3201_SPIx_IRQHandler                  SPI5_IRQHandler
#define MCP3201_SPIx_IRQn                        SPI5_IRQn
#define MCP3201_SPIx_IRQn_PreemptPriority        1
#define MCP3201_SPIx_IRQn_SubPriority            0
//PF7     ------> SPI5_SCK
#define MCP3201_SPIx_SCK_PIN                     GPIO_PIN_7
#define MCP3201_SPIx_SCK_GPIO_PORT               GPIOF
#define MCP3201_SPIx_SCK_AF                      GPIO_AF5_SPI5
//PF8     ------> SPI5_MISO
#define MCP3201_SPIx_MISO_PIN                    GPIO_PIN_8
#define MCP3201_SPIx_MISO_GPIO_PORT              GPIOF
#define MCP3201_SPIx_MISO_AF                     GPIO_AF5_SPI5
//PF9     ------> SPI5_MOSI
#define MCP3201_SPIx_MOSI_PIN                    GPIO_PIN_9
#define MCP3201_SPIx_MOSI_GPIO_PORT              GPIOF
#define MCP3201_SPIx_MOSI_AF                     GPIO_AF5_SPI5
//NOT USED: PF6     ------> SPI5_NSS
//#define MCP3201_SPIx_CS_PIN                      GPIO_PIN_6
//#define MCP3201_SPIx_CS_GPIO_PORT                GPIOF
//#define MCP3201_SPIx_CS_AF                       GPIO_AF5_SPI5
//NOT USED: PB5     ------> SPI5_MOSI

#include <mbed.h>

enum MCP3201TransferState{
	MCP3201_DMA_SPI_TRANSFER_WAIT,
	MCP3201_DMA_SPI_TRANSFER_IN_PROGRESS,
	MCP3201_DMA_SPI_TRANSFER_COMPLETE,
	MCP3201_DMA_SPI_TRANSFER_ERROR
};

class MCP3201 {

    public:
        /*  SPI - reference to SPI class instance,
            ADC support 2 mode: mode 0,3: CPOL=0,CPHA=0, CPOL=1,CPHA=1
            spiFreq - ADC support up to 1,6 MHz (value is 100000)  */
        MCP3201(unsigned long spiPrescaler); //
        MCP3201(unsigned long spiPrescaler, float Vref);
        
        int init(void);
        int deInit(void);
        /*  Vref - Vref voltage;    */
        void setVref(float &Vref);

        uint16_t setNullPoint(void);
        
        /*  Get Voltage at input of ADC    */
        float getVoltageBlocking(void);
        //get ADC value in blocking mode
        uint16_t getCodeBlocking(void);
        //launch DMA channel for receiving ADC value
        uint32_t startGettingCode(void);
        //return status of DMA transaction
        uint32_t getTransferStatus(void);
        //return last saved ADC value
        uint16_t getLastCode(void);
        float getLastVoltage(void);
        void clearTransferStatus(void);
        float calcVoltage(uint16_t &DataBits);
        void setCSPin(uint16_t pin, GPIO_TypeDef *port);
    private:
        //DMA_HandleTypeDef *_DMASPI;
        /*  Get Data bits   */
        uint16_t ADCDataBits = 0x0;
        uint16_t ADCNullPointDataBits = 0x0;
        /*  Get raw data bits*/
        uint16_t ADCRawBits[1];
        /*  Send dummy values   */
        uint8_t ADCdummy[4];
        /*  Vref voltage    */
        float ADCVref = 0.5;

        float ADCLSBWeight = 0;

        /*  Calculating input voltage via formula:
                Vin = ADCLSBWeight * ADCDataBits,
                where ADCLSBWeight = Vref / 4096;  
                                                        */
        void fillSettings(unsigned long spiPrescaler);        
        //DigitalOut *_CS;
        
};
#endif