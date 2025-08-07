/*
	RSSI.h - Library for getting data from R Series throught SSI interface.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
#ifndef RSSI_h
#define RSSI_h
#include "..//..//include//Shared_Params.h"
#include <mbed.h>
#include "..//..//include//TypeDefs/ParamsTypeDefs.h"
#include "..//Calibration/Calibration.h"
#include "..//BasicElements/BasicElements.h"
#include "..//InternalFlash//InternalFlash.h"
#include "..//InternalFlashDMA//InternalFlashDMA.h"



#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
//SPI define
#define SSI_SPIx                             SPI5
//Clocks defines
#define SSI_SPIx_CLK_ENABLE()                __HAL_RCC_SPI5_CLK_ENABLE()
#define SSI_SPIx_CLK_DISABLE()                __HAL_RCC_SPI5_CLK_DISABLE()
#define SSI_DMAx_CLK_ENABLE()                __HAL_RCC_DMA2_CLK_ENABLE()
#define SSI_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOF_CLK_ENABLE()
#define SSI_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define SSI_SPIx_FORCE_RESET()               __HAL_RCC_SPI5_FORCE_RESET()
#define SSI_SPIx_RELEASE_RESET()             __HAL_RCC_SPI5_RELEASE_RESET()

#if BOARD_INDEX == 2
//DMA defines
#define SSI_SPIx_DMA_RX_IRQHandler           DMA1_Stream0_IRQHandler
#define SSI_SPIx_DMA_RX_IRQn                 DMA1_Stream0_IRQn
#define SSI_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define SSI_SPIx_DMA_RX_IRQn_SubPriority     0

#define SSI_SPIx_RX_DMA_REQUEST              DMA_REQUEST_SPI5_RX
#define SSI_SPIx_RX_DMA_STREAM               DMA1_Stream0//for TX DMA1_Stream2

#define SSI_SPIx_TX_DMA_REQUEST              DMA_REQUEST_SPI5_TX
#define SSI_SPIx_TX_DMA_STREAM               DMA1_Stream2  


//SPI IRQ defines
#define SSI_SPIx_IRQHandler                  SPI5_IRQHandler
#define SSI_SPIx_IRQn                        SPI5_IRQn
#define SSI_SPIx_IRQn_PreemptPriority        1
#define SSI_SPIx_IRQn_SubPriority            0
#endif
#if BOARD_INDEX == 3
//DMA defines
#define SSI_SPIx_DMA_RX_IRQHandler           DMA2_Stream5_IRQHandler
#define SSI_SPIx_DMA_RX_IRQn                 DMA2_Stream5_IRQn
#define SSI_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define SSI_SPIx_DMA_RX_IRQn_SubPriority     0

#define SSI_SPIx_RX_DMA_CHANNEL              DMA_CHANNEL_7
#define SSI_SPIx_RX_DMA_STREAM               DMA2_Stream5

#define SSI_SPIx_TX_DMA_CHANNEL              DMA_CHANNEL_7
#define SSI_SPIx_TX_DMA_STREAM               DMA2_Stream6
//SPI IRQ defines
#define SSI_SPIx_IRQHandler                  SPI5_IRQHandler
#define SSI_SPIx_IRQn                        SPI5_IRQn
#define SSI_SPIx_IRQn_PreemptPriority        1
#define SSI_SPIx_IRQn_SubPriority            0
#endif
//PС10     ------> SPI3_SCK
#define SSI_SPIx_SCK_PIN                     GPIO_PIN_10
#define SSI_SPIx_SCK_GPIO_PORT               GPIOC
#define SSI_SPIx_SCK_AF                      GPIO_AF6_SPI3
//PС11     ------> SPI3_MISO
#define SSI_SPIx_MISO_PIN                    GPIO_PIN_11
#define SSI_SPIx_MISO_GPIO_PORT              GPIOC
#define SSI_SPIx_MISO_AF                     GPIO_AF6_SPI3

#endif

#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED

//SPI define
#define SSI_SPIx                             SPI3
//Clocks defines
#define SSI_SPIx_CLK_ENABLE()                __HAL_RCC_SPI3_CLK_ENABLE()
#define SSI_SPIx_CLK_DISABLE()                __HAL_RCC_SPI3_CLK_DISABLE()
#define SSI_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define SSI_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define SSI_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define SSI_SPIx_FORCE_RESET()               __HAL_RCC_SPI3_FORCE_RESET()
#define SSI_SPIx_RELEASE_RESET()             __HAL_RCC_SPI3_RELEASE_RESET()
//DMA defines
#define SSI_SPIx_DMA_RX_IRQHandler           DMA1_Stream0_IRQHandler
#define SSI_SPIx_DMA_RX_IRQn                 DMA1_Stream0_IRQn
#define SSI_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define SSI_SPIx_DMA_RX_IRQn_SubPriority     0
#define SSI_SPIx_RX_DMA_REQUEST              DMA_REQUEST_SPI3_RX
#define SSI_SPIx_RX_DMA_STREAM               DMA1_Stream0   //for TX DMA1_Stream2
//SPI IRQ defines
#define SSI_SPIx_IRQHandler                  SPI3_IRQHandler
#define SSI_SPIx_IRQn                        SPI3_IRQn
#define SSI_SPIx_IRQn_PreemptPriority        1
#define SSI_SPIx_IRQn_SubPriority            0
// //PС10     ------> SPI3_SCK
// #define SSI_SPIx_SCK_PIN                     GPIO_PIN_10
// #define SSI_SPIx_SCK_GPIO_PORT               GPIOC
// #define SSI_SPIx_SCK_AF                      GPIO_AF6_SPI3
// //PС11     ------> SPI3_MISO
// #define SSI_SPIx_MISO_PIN                    GPIO_PIN_11
// #define SSI_SPIx_MISO_GPIO_PORT              GPIOC
// #define SSI_SPIx_MISO_AF                     GPIO_AF6_SPI3

#endif
extern BasicElements basic;
extern InternalFlash internalFlash;
extern InternalFlashDMA internalFlashDMA;

enum SSITransferState{
	SSI_DMA_SPI_TRANSFER_WAIT,
	SSI_DMA_SPI_TRANSFER_IN_PROGRESS,
	SSI_DMA_SPI_TRANSFER_COMPLETE,
	SSI_DMA_SPI_TRANSFER_ERROR
};

class RSSI {
public:
    //speed in kB/s
	RSSI(
        unsigned long spiPrescaler, 
        int SSINumberOfBits,
        unsigned long numberOfCalibrationPoints,
        PinName SCK,
        PinName MISO);
	~RSSI();
    int init(void);
    float readPositionBlocking();
    //launch DMA channel for receiving SSI value
    uint32_t startGettingPosition(void);
    //return status of DMA transaction
    uint32_t getTransferStatus(void);
    //return last saved SSI value
    float getLastPosition(void);
    float getLastPositionRAW(void);
    void setSSISensorResolution(double resolution);
    void clearTransferStatus(void);
 
    float calcPosition(float code);
    void setCalibrCoefs(double k, double b);
    void getCalibrCoefs(double *k, double *b);
    errorCode_t writeCalibrCoefsInFlash(double k, double b);
    errorCode_t readCalibrCoefsFromFlash(double *k, double *b);
    errorCode_t writeCalibrPointsInFlash(point_t *points, int size);
    errorCode_t readCalibrPointsFromFlash(point_t *points, int size);
    errorCode_t readCalibrPointsSizeFromFlash(int *size);
    void setFlashOperationType(uint32_t flashOperationType);
    Calibration *calibration;

private:
    uint32_t startValue = 0xA2A2;
    #if BOARD_INDEX == 2
    uint32_t SSIRawBits[1] = {0};
    uint16_t SSIRawBitsHalfWord[2] = {0,0};
    #endif
    #if BOARD_INDEX == 3
    uint16_t SSIRawBits[2] = {0};
    #endif
	float position = 0;
	//Shared basic;
    int numberOfBits = 26;
    uint32_t data;
    uint32_t data0;
    uint32_t data1;
    uint32_t graydecode(uint32_t &gray);
    float resolution = 0.0005;

    double _k = 1.0; 
    double _b = 0.0; 
    uint32_t _flashOperationType = FLASH_OPERATION_CPU;

    Timer readPositionTimer;
    std::chrono::microseconds readPositionTimeout = 150us;
    PinName SCK;
    PinName MISO;
};
#endif
