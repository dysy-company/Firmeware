/*
    Library for Microchip MCP4921/MCP4922 DAC chip.
    Created by Grigorii Bragin, March 1, 2020
*/
#ifndef MCP492_PWR_h
#define MCP492_PWR_h

#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define MCP492x_PWR_SPIx                             SPI5 //TODO DMA2
//Clocks defines
#define MCP492x_PWR_SPIx_CLK_ENABLE()                __HAL_RCC_SPI5_CLK_ENABLE()
#define MCP492x_PWR_SPIx_CLK_DISABLE()               __HAL_RCC_SPI5_CLK_DISABLE()
#define MCP492x_PWR_DMAx_CLK_ENABLE()                __HAL_RCC_DMA2_CLK_ENABLE()
#define MCP492x_PWR_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOF_CLK_ENABLE()
#define MCP492x_PWR_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define MCP492x_PWR_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define MCP492x_PWR_SPIx_FORCE_RESET()               __HAL_RCC_SPI5_FORCE_RESET()
#define MCP492x_PWR_SPIx_RELEASE_RESET()             __HAL_RCC_SPI5_RELEASE_RESET()
//DMA defines
//#define MCP492x_PWR_SPIx_DMA_TX_IRQHandler           DMA2_Stream0_IRQHandler
#define MCP492x_PWR_SPIx_DMA_TX_IRQn                 DMA2_Stream0_IRQn
#define MCP492x_PWR_SPIx_DMA_TX_IRQn_PreemptPriority 1
#define MCP492x_PWR_SPIx_DMA_TX_IRQn_SubPriority     0
#if BOARD_INDEX == 2
#define MCP492x_PWR_SPIx_TX_DMA_REQUEST              DMA_REQUEST_SPI5_TX
#endif
#define MCP492x_PWR_SPIx_TX_DMA_STREAM               DMA2_Stream0   //for RX DMA2_Stream0
//SPI IRQ defines
//#ifndef SPI_5_IRQ_Handler
//#define MCP492x_PWR_SPIx_IRQHandler                  SPI5_IRQHandler
//#endif
#define MCP492x_PWR_SPIx_IRQn                        SPI5_IRQn
#define MCP492x_PWR_SPIx_IRQn_PreemptPriority        1
#define MCP492x_PWR_SPIx_IRQn_SubPriority            0
//PF7     ------> SPI5_SCK
#define MCP492x_PWR_SPIx_SCK_PIN                     GPIO_PIN_7
#define MCP492x_PWR_SPIx_SCK_GPIO_PORT               GPIOF
#define MCP492x_PWR_SPIx_SCK_AF                      GPIO_AF5_SPI5
//PF9     ------> SPI5_MOSI
#define MCP492x_PWR_SPIx_MOSI_PIN                    GPIO_PIN_9
#define MCP492x_PWR_SPIx_MOSI_GPIO_PORT              GPIOF
#define MCP492x_PWR_SPIx_MOSI_AF                     GPIO_AF5_SPI5
//PB_10     ------> SPI5_NSS
#define MCP492x_PWR_SPIx_CS_PIN                      GPIO_PIN_10
#define MCP492x_PWR_SPIx_CS_GPIO_PORT                GPIOB
//#define MCP492x_PWR_SPIx_CS_AF                       GPIO_AF0

#include <mbed.h>

enum MCP492x_PWRTransferState{
	MCP492x_PWR_DMA_SPI_TRANSFER_WAIT,
	MCP492x_PWR_DMA_SPI_TRANSFER_IN_PROGRESS,
	MCP492x_PWR_DMA_SPI_TRANSFER_COMPLETE,
	MCP492x_PWR_DMA_SPI_TRANSFER_ERROR
};
    

class MCP492x_PWR {

    public:
        /*  SPI - reference to SPI class instance,
            spiMode - DAC support 2 modes:  mode 0: CPOL=0,CPHA=0
                                            mode 3: CPOL=1,CPHA=1
            spiFreq - DAC support up to 20 MHz (value is 20000000)  */
        MCP492x_PWR(int spiBaudRatePrescaler);
        MCP492x_PWR(int spiBaudRatePrescaler, 
            bool output, 
            bool inputBufferCtrl,
            bool gain,
            bool outPwrDownCtrl,
            float Vref,
            DMA_HandleTypeDef *GLOBAL_SPI_DMA_IRQ_HANDLER,
            SPI_HandleTypeDef *GLOBAL_SPI_IRQ_HANDLER
        );
        void sharedConstructor(int spiBaudRatePrescaler);
        int init(void);
        int deInit(void);
        /*  output - DAC_A or DAC_B select bit:
                0 = write to DAC_A; 
                1 = write to DAC_B;
            inputBufferCtrl - Vref Input Buffer Control Bit:
                0 = unbuffered;
                1 = buffered;
            gain - Output Gain Select bit:
                0 = 2x (Vout = 2*Vref*D/4096);
                1 = 1x (Vout = Vref*D/4096);
            outPwrDownCtrl - Output Power Down Control bit:
                0 = Output buffer disabled, Output is high impedance;
                1 = Output Power Down Control bit;
            Vref - Vref voltage;    */
        void setConfig(
            bool &output, 
            bool &inputBufferCtrl,
            bool &gain,
            bool &outPwrDownCtrl,
            float &Vref);
        
        /*  Set Voltage at output of DAC    */
        void setVoltageBlocking(float &setVoltage);
        void startSettingVoltage(float &setVoltage);
        //return status of DMA transaction
        uint32_t    getTransferStatus(void);
        //clear transfer status of DMA transaction
        void        clearTransferStatus(void);
        //DMA_HandleTypeDef  *SPI_DMA_IRQ_HANDLER;
        //SPI_HandleTypeDef  *SPI_IRQ_HANDLER;
        
    private:
        
        /*  DAC_A or DAC_B select bit:
                0 = write to DAC_A; 
                1 = write to DAC_B; */
        uint16_t DACOutput = 0x0;
        
        /*  Vref Input Buffer Control Bit:
                0 = unbuffered;
                1 = buffered;    */
        uint16_t DACInputBufferControl = 0x0;

        /*  Output Gain Select bit:
                0 = 2x (Vout = 2*Vref*D/4096);
                1 = 1x (Vout = Vref*D/4096);   */
        uint16_t DACGain = 0x1;

        /*  Output Power Down Control bit:
                0 = Output buffer disabled, Output is high impedance;
                1 = Output Power Down Control bit;  */
        uint16_t DACSHDN = 0x1;

        /*  Data bits   */
        uint16_t DACDataBits = 0x0;

        /*  Send raw data bits*/
        uint16_t DACRawBits = 0x0;

        static char DACRAWBuffer[2];

        /*  Vref voltage    */
        float DACVref = 0.0001;
        
        /*  Calculating Data Bits via formula:
                GAIN = 1:
	                VOUT = VREF * D/4096;
	                D = 4096 * VOUT/VREF, VREF!=0;
                GAIN = 2:
	                VOUT = 2* VREF * D/4096;
	                D = 2048 * VOUT/VREF, VREF!=0;  */
        uint16_t calcDataBits(float &setVoltage);

        /*  Build packet to send via SPI interface  */
        uint16_t buildRawData(float &setVoltage);
        //DMA usage
        //DMAUsage _DMAusage;
        // const event_callback_t writeCallBack;
        //void writeCallBackHandler(void);
        //int spiEvent = SPI_EVENT_COMPLETE ;
};
#endif