/*
    Library for Texas Instruments ADS8320 ADC chip.
    Created by Grigorii Bragin, March 8, 2020
*/
#ifndef ADS8320_h
#define ADS8320_h

#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define ADS8320_SPIx                             SPI1
//Clocks defines
#define ADS8320_SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
#define ADS8320_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#else
#define ADS8320_DMAx_CLK_ENABLE()                __HAL_RCC_DMA2_CLK_ENABLE()
#endif
#define ADS8320_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS8320_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS8320_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS8320_SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define ADS8320_SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()
//DMA defines
#if BOARD_INDEX == 2
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
#define ADS8320_SPIx_DMA_RX_IRQHandler           DMA1_Stream1_IRQHandler
#define ADS8320_SPIx_DMA_RX_IRQn                 DMA1_Stream1_IRQn
#define ADS8320_SPIx_RX_DMA_STREAM               DMA1_Stream1   //for TX DMA1_Stream2
#else
#define ADS8320_SPIx_DMA_RX_IRQHandler           DMA2_Stream1_IRQHandler
#define ADS8320_SPIx_DMA_RX_IRQn                 DMA2_Stream1_IRQn
#define ADS8320_SPIx_RX_DMA_STREAM               DMA2_Stream1   //for TX DMA2_Stream2
#endif
#define ADS8320_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define ADS8320_SPIx_DMA_RX_IRQn_SubPriority     0
#define ADS8320_SPIx_RX_DMA_REQUEST              DMA_REQUEST_SPI1_RX

#endif
#if BOARD_INDEX == 3
#define ADS8320_SPIx_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler
#define ADS8320_SPIx_DMA_RX_IRQn                 DMA2_Stream2_IRQn
#define ADS8320_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define ADS8320_SPIx_DMA_RX_IRQn_SubPriority     0
#define ADS8320_SPIx_RX_DMA_STREAM               DMA2_Stream2   
#define ADS8320_SPIx_TX_DMA_STREAM               DMA2_Stream3
#endif
//SPI IRQ defines
#define ADS8320_SPIx_IRQHandler                  SPI1_IRQHandler
#define ADS8320_SPIx_IRQn                        SPI1_IRQn
#define ADS8320_SPIx_IRQn_PreemptPriority        1
#define ADS8320_SPIx_IRQn_SubPriority            0
//PA5     ------> SPI1_SCK
#define ADS8320_SPIx_SCK_PIN                     GPIO_PIN_5
#define ADS8320_SPIx_SCK_GPIO_PORT               GPIOA
#define ADS8320_SPIx_SCK_AF                      GPIO_AF5_SPI1
//PA6     ------> SPI1_MISO
#define ADS8320_SPIx_MISO_PIN                    GPIO_PIN_6
#define ADS8320_SPIx_MISO_GPIO_PORT              GPIOA
#define ADS8320_SPIx_MISO_AF                     GPIO_AF5_SPI1

#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
//PA4     ------> SPI1_NSS
#define ADS8320_SPIx_CS_PIN                      GPIO_PIN_4
#define ADS8320_SPIx_CS_GPIO_PORT                GPIOA
#define ADS8320_SPIx_CS_AF                       GPIO_AF5_SPI1
#endif
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
//PA3     ------> SPI1_NSS
#define ADS8320_SPIx_CS_PIN                      GPIO_PIN_3
#define ADS8320_SPIx_CS_GPIO_PORT                GPIOA
#define ADS8320_SPIx_CS_AF                       GPIO_AF5_SPI1
#endif
//NOT USED: PB5     ------> SPI1_MOSI

#include <mbed.h>
#include "..//Calibration/Calibration.h"
#include "..//..//include//Tasks.h"
#include "..//BasicElements/BasicElements.h"
#include "..//InternalFlash/InternalFlash.h"
#include "..//InternalFlashDMA/InternalFlashDMA.h"
#include "..//..//include//Typedefs/Threads_Mail_Types.h"
#include "..//..//include//TypeDefs/ParamsTypeDefs.h"
#include "..//..//include//Ethernet/Ethernet_Errors.h"
#include "..//..//include//Shared_Params.h"

extern BasicElements basic;
extern Mail<TaskManagerMail_t, 16> TaskManagerMailBox;
extern InternalFlash internalFlash;
extern InternalFlashDMA internalFlashDMA;

enum ADS8320TransferState{
	ADS8320_DMA_SPI_TRANSFER_WAIT,
	ADS8320_DMA_SPI_TRANSFER_IN_PROGRESS,
	ADS8320_DMA_SPI_TRANSFER_COMPLETE,
	ADS8320_DMA_SPI_TRANSFER_ERROR
};

class ADS8320 {

    public:
        /*  SPI - reference to SPI class instance,
            DAC support 1 mode: mode 3: CPOL=1,CPHA=1
            spiFreq - DAC support up to 100 kHz (value is 100000)  */
        ADS8320(unsigned long spiPrescaler, unsigned long numberOfCalibrationPoints);
        ~ADS8320();
        int init(void);
        /*  Vref - Vref voltage;    */
        void setVref(float &Vref);

        uint16_t setNullPoint(void);
        
        /*  Get Voltage at input of ADC    */
        float getVoltage(void);
        //get ADC value in blocking mode
        uint16_t getCodeBlocking(void);
        //launch DMA channel for receiving ADC value
        uint32_t startGettingCode(void);
        //return status of DMA transaction
        uint32_t getTransferStatus(void);
        //return last saved ADC value
        uint16_t getLastCode(void);
        void clearTransferStatus(void);
        float getStrain(void);
        /* calculating Strain via formula:
            (code - ADCNullPointDataBits) * 5.042868 * 0.0001 
                                                                */
        float calcStrain(uint16_t code);
        float calcStrain2(uint16_t code);
        void setCalibrCoefs(double k, double b);
        void getCalibrCoefs(double *k, double *b);
        errorCode_t writeCalibrCoefsInFlash(double k, double b);
        errorCode_t readCalibrCoefsFromFlash(double *k, double *b);
        errorCode_t waitReadCompleteCalibrCoefsFromFlash(int timeout);
        errorCode_t writeCalibrPointsInFlash(point_t *points, int size);
        errorCode_t readCalibrPointsFromFlash(point_t *points, int size);
        errorCode_t readCalibrPointsSizeFromFlash(int *size);
        errorCode_t writeCalibrPointsInFlash2(point_t *points, int size);
        errorCode_t readCalibrPointsFromFlash2(point_t *points, int size);
        errorCode_t readCalibrPointsSizeFromFlash2(int *size);
        void setFlashOperationType(uint32_t flashOperationType);
        Calibration *calibration;
        Calibration *calibration2;
    private:
        Semaphore *readFromFlashSemaphore;
        Semaphore *readFromFlashSemaphore2;
        //DMA_HandleTypeDef *_DMASPI;
        /*  Get Data bits   */
        uint16_t ADCDataBits = 0x0;
        uint16_t ADCNullPointDataBits = 0x0;
        /*  Get raw data bits*/
        #if BOARD_INDEX == 2
        uint32_t ADCRawBits[1];
        #endif
        #if BOARD_INDEX == 3
        uint16_t ADCRawBits[2] = {0};
        #endif
        /*  Send dummy values   */
        uint8_t ADCdummy[4];
        /*  Vref voltage    */
        float ADCVref = 0.5;

        float ADCLSBWeight = 0;
        //for Vishay psd sjjt 10t
        //double _k = -0.0029640168;
        //double _b = 110.0895133077;
        //for Chinese sensor 100kN ZLF-A S/N:2421 D/C:2021.06
        double _k = 0.00341142;//0.0035078;//-0.00334599;//-0.00396559;
        double _b = -108.929;//-111.626;//111.752;//123.595;
        double _k2 = 0.00341142;//0.0035078;//-0.00334599;//-0.00396559;
        double _b2 = -108.929;//-111.626;//111.752;//123.595;
        //for KVZ sensor 100kN :2022.04
        //double _k = 0.00411212;//0.0048;//0.00760456;//0.00308461;
        //double _b = -136.344;//-157.296;//-249.992;//-101.243;
        /*  Calculating input voltage via formula:
                Vin = ADCLSBWeight * ADCDataBits,
                where ADCLSBWeight = Vref / 65536;  
                                                        */
        float calcVoltage(uint16_t &DataBits);
        
        uint32_t _flashOperationType = FLASH_OPERATION_CPU;
};
#endif