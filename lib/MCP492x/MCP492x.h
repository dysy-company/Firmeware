/*
    Library for Microchip MCP4921/MCP4922 DAC chip.
    Created by Grigorii Bragin, March 1, 2020
*/
#ifndef MCP492_h
#define MCP492_h

#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define MCP492x_SPIx                             SPI4 //TODO DMA2
//Clocks defines
#define MCP492x_SPIx_CLK_ENABLE()                __HAL_RCC_SPI4_CLK_ENABLE()
#define MCP492x_SPIx_CLK_DISABLE()               __HAL_RCC_SPI4_CLK_DISABLE()
#define MCP492x_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOE_CLK_ENABLE()
#define MCP492x_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()
#define MCP492x_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOE_CLK_ENABLE()
#define MCP492x_SPIx_FORCE_RESET()               __HAL_RCC_SPI4_FORCE_RESET()
#define MCP492x_SPIx_RELEASE_RESET()             __HAL_RCC_SPI4_RELEASE_RESET()
//SPI IRQ defines
#define MCP492x_SPIx_IRQHandler                  SPI4_IRQHandler
#define MCP492x_SPIx_IRQn                        SPI4_IRQn
#define MCP492x_SPIx_IRQn_PreemptPriority        1
#define MCP492x_SPIx_IRQn_SubPriority            0
//PE_2     ------> SPI4_SCK
#define MCP492x_SPIx_SCK_PIN                     GPIO_PIN_2
#define MCP492x_SPIx_SCK_GPIO_PORT               GPIOE
#define MCP492x_SPIx_SCK_AF                      GPIO_AF5_SPI4
//PE_6     ------> SPI4_MOSI
#define MCP492x_SPIx_MOSI_PIN                    GPIO_PIN_6
#define MCP492x_SPIx_MOSI_GPIO_PORT              GPIOE
#define MCP492x_SPIx_MOSI_AF                     GPIO_AF5_SPI4
//PE_11     ------> SPI4_NSS
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
#define MCP492x_SPIx_CS_PIN                      GPIO_PIN_11
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
#define MCP492x_SPIx_CS_PIN                      GPIO_PIN_0
#endif

#define MCP492x_SPIx_CS_GPIO_PORT                GPIOE
#define MCP492x_SPIx_CS_AF                       GPIO_AF5_SPI4

#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
#define MCP492x_SPIx_CS2_PIN                     GPIO_PIN_3
#define MCP492x_SPIx_CS2_GPIO_PORT               GPIOE
#define MCP492x_SPIx_CS2_AF                      GPIO_AF5_SPI4

#define MCP492x_SPIx_CS3_PIN                     GPIO_PIN_4
#define MCP492x_SPIx_CS3_GPIO_PORT               GPIOE
#define MCP492x_SPIx_CS3_AF                      GPIO_AF5_SPI4
#endif

// CS defines
#define SS_DAC_CS                                0
#define Tenzo_ADC_CS                             1
#define COIL_DAC_CS                              2

enum MCP492xTransferState{
	MCP492x_DMA_SPI_TRANSFER_WAIT,
	MCP492x_DMA_SPI_TRANSFER_IN_PROGRESS,
	MCP492x_DMA_SPI_TRANSFER_COMPLETE,
	MCP492x_DMA_SPI_TRANSFER_ERROR
};

class MCP492x {

    public:
        /*  SPI - reference to SPI class instance,
            spiMode - DAC support 2 modes:  mode 0: CPOL=0,CPHA=0
                                            mode 3: CPOL=1,CPHA=1
            spiFreq - DAC support up to 20 MHz (value is 20000000)  */
        MCP492x(int spiMode, int spiBaudRatePrescaler);
        
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
        void setVoltage(float &setVoltage);

        void setVoltage(float &setVoltage, uint8_t DAC_CS);

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