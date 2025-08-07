#ifndef TEDS_H
#define TEDS_H

#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define  USE_HAL_USART_REGISTER_CALLBACKS 1U

//USART define
#define TEDs_USARTx                             USART1 //TODO DMA2
//Clocks defines
#define TEDs_USARTx_CLK_ENABLE()                __HAL_RCC_USART1_CLK_ENABLE()
#define TEDs_USARTx_CLK_DISABLE()               __HAL_RCC_USART1_CLK_DISABLE()
#define TEDs_DMAx_CLK_ENABLE()                 __HAL_RCC_DMA2_CLK_ENABLE()
#define TEDs_USARTx_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define TEDs_USARTx_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define TEDs_USARTx_FORCE_RESET()               __HAL_RCC_USART1_FORCE_RESET()
#define TEDs_USARTx_RELEASE_RESET()             __HAL_RCC_USART1_RELEASE_RESET()
//DMA defines
#define TEDs_USARTx_DMA_TX_IRQHandler           DMA2_Stream7_IRQHandler
#define TEDs_USARTx_DMA_TX_IRQn                 DMA2_Stream7_IRQn
#define TEDs_USARTx_DMA_TX_IRQn_PreemptPriority 1
#define TEDs_USARTx_DMA_TX_IRQn_SubPriority     0

#if BOARD_INDEX == 2
#define TEDs_USARTx_TX_DMA_REQUEST              DMA_REQUEST_USART1_TX
#endif
#define TEDs_USARTx_TX_DMA_STREAM               DMA2_Stream7  
#if BOARD_INDEX == 2
#define TEDs_USARTx_DMA_RX_IRQHandler           DMA2_Stream6_IRQHandler
#define TEDs_USARTx_DMA_RX_IRQn                 DMA2_Stream6_IRQn
#endif
#if BOARD_INDEX == 3
#define TEDs_USARTx_DMA_RX_IRQHandler           DMA2_Stream2_IRQHandler
#define TEDs_USARTx_DMA_RX_IRQn                 DMA2_Stream2_IRQn
#endif
#define TEDs_USARTx_DMA_RX_IRQn_PreemptPriority 1
#define TEDs_USARTx_DMA_RX_IRQn_SubPriority     0
#if BOARD_INDEX == 2
#define TEDs_USARTx_RX_DMA_REQUEST              DMA_REQUEST_USART1_RX
#define TEDs_USARTx_RX_DMA_STREAM               DMA2_Stream2 
#endif
#if BOARD_INDEX == 3
#define TEDs_USARTx_RX_DMA_STREAM               DMA2_Stream2 
#endif
//USART IRQ defines
#define TEDs_USARTx_IRQn                        USART1_IRQn
#define TEDs_USARTx_IRQn_PreemptPriority        1
#define TEDs_USARTx_IRQn_SubPriority            0
//PA8    ------> USART1_CK
#define TEDs_USARTx_CK_PIN                     GPIO_PIN_8
#define TEDs_USARTx_CK_GPIO_PORT               GPIOA
#define TEDs_USARTx_CK_AF                      GPIO_AF7_USART1
//PA9     ------> USART1_TX
#define TEDs_USARTx_TX_PIN                     GPIO_PIN_9
#define TEDs_USARTx_TX_GPIO_PORT               GPIOA
#define TEDs_USARTx_TX_AF                      GPIO_AF7_USART1
//PA10    ------> USART1_RX
#define TEDs_USARTx_RX_PIN                     GPIO_PIN_10
#define TEDs_USARTx_RX_GPIO_PORT               GPIOA
#define TEDs_USARTx_RX_AF                      GPIO_AF7_USART1
#ifdef __cplusplus
 extern "C" {
#endif
void USART1_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
#ifdef __cplusplus
}
#endif
enum TEDsTransferState{
	TEDs_DMA_USART_TRANSFER_WAIT,
	TEDs_DMA_USART_TRANSFER_IN_PROGRESS,
	TEDs_DMA_USART_TRANSFER_COMPLETE,
	TEDs_DMA_USART_TRANSFER_ERROR
};

#define TEDS_UNDEFINED                  -1
#define TEDS_TRANSFER_OK                0
#define TEDS_NOT_DETECTED               1
#define TEDS_DETECTED                   2
#define TEDS_RESET_TRANSFER_ERROR       3
#define TEDS_RESET_TRANSFER_TIMEOUT     4
#define TEDS_CMD_TRANSFER_ERROR         5
#define TEDS_CMD_TRANSFER_TIMEOUT       6
#define TEDS_READ_TRANSFER_ERROR        7
#define TEDS_READ_TRANSFER_TIMEOUT      8

#define OW_0	0x00
#define OW_1	0xff
#define OW_R_1	0xff

#define OW_SEND_RESET		1
#define OW_NO_RESET		2

#define OW_NO_READ		0xff

#define OW_READ_SLOT	0xff

class TEDs{
    public:
        TEDs(void);
        ~TEDs(void);
        int init(void);
        int deInit(void);
        //1 - presence not detected, 2 - presence pulse detected
        int resetWire(void);
        int sendCmd(uint8_t sendReset, uint8_t *command, uint8_t cmdLength);
        int readData(uint8_t *data, uint8_t dataLength);
        uint8_t calculateCRC(uint8_t *rom, uint32_t startIndex);
    private:
        void fillUSARTParams(uint32_t baudRate);
        void sharedConstructor(uint32_t baudRate);
        void getBitsFromByte(uint8_t byte, uint8_t *bits);
        uint8_t getByteFromBits(uint8_t *bits);
        int lastStatus;
        int waitEndOfTransfer(int error, int timeout, int ok);
        //Semaphore *transmitBlock;
};

#endif