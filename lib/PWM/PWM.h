#ifndef PWM_h
#define PWM_h

#include <mbed.h>
#include "..//..//include//Shared_Params.h"
//TIM define
#define PWM_TIMx                        TIM4
//Clock defines
#define PWM_GPIOx_CLK_ENABLE()          __HAL_RCC_GPIOD_CLK_ENABLE();
#define PWM_TIMx_CLK_ENABLE()           __HAL_RCC_TIM4_CLK_ENABLE();
#define DMAx_CLK_ENABLE                 __HAL_RCC_DMA1_CLK_ENABLE

#if BOARD_INDEX == 2
#define TIMx_CC1_DMA_REQUEST            DMA_REQUEST_TIM4_CH1
#define TIMx_CC2_DMA_REQUEST            DMA_REQUEST_TIM4_CH2
#define TIMx_CC1_DMA_INST               DMA1_Stream7
#define TIMx_CC2_DMA_INST               DMA1_Stream6
#endif
#if BOARD_INDEX == 3
#define TIMx_CC1_DMA_INST               DMA1_Stream0
#define TIMx_CC2_DMA_INST               DMA1_Stream3
#endif

#if BOARD_INDEX == 2
/* Definition for ADCx's NVIC */
#define TIMx_DMA_IRQn                   DMA1_Stream7_IRQn
#define TIMx_DMA_IRQHandler             DMA1_Stream7_IRQHandler
#define TIMx_DMA_IRQn1                  DMA1_Stream6_IRQn
#define TIMx_DMA_IRQHandler1            DMA1_Stream6_IRQHandler
#endif
#if BOARD_INDEX == 3
/* Definition for ADCx's NVIC */
#define TIMx_DMA_IRQn                   DMA1_Stream0_IRQn
#define TIMx_DMA_IRQHandler             DMA1_Stream0_IRQHandler
#define TIMx_DMA_IRQn1                  DMA1_Stream3_IRQn
#define TIMx_DMA_IRQHandler1            DMA1_Stream3_IRQHandler
#endif
//PWM defines
#define PWM_PRESCALER                   4
#define PWM_PERIOD                      500-1
//PD12
#define PWM_TIMx_CH3_PIN                GPIO_PIN_12
#define PWM_TIMx_CH3_GPIO_PORT          GPIOD
#define PWM_TIMx_CH3_AF                 GPIO_AF2_TIM4
//PD13
#define PWM_TIMx_CH4_PIN                GPIO_PIN_13
#define PWM_TIMx_CH4_GPIO_PORT          GPIOD
#define PWM_TIMx_CH4_AF                 GPIO_AF2_TIM4

#define MOTOR_DRIVER_TYPE_UNDEFINED     0x00000000
#define MOTOR_DRIVER_TYPE_STEP_DIR      0x00000001
#define MOTOR_DRIVER_TYPE_CW_CCW        0x00000002

class PWM {

    public:
        PWM(uint16_t pwm_value);
        ~PWM();
        void init(uint8_t motorDriverType, uint32_t pwmFreq);
        void resetPWM();
        void setPWM(uint8_t motorDriverType, int direction, uint16_t count);
        void stopPWM(uint8_t motorDriverType, int direction);
        void initGPIOPort(uint8_t motorDriverType);
    private:
        //TIM_HandleTypeDef    TimHandle;

        TIM_OC_InitTypeDef sConfig;
        
        uint16_t _pwm_value = 250;
        ALIGN_32BYTES( uint32_t aCCValue_Buffer[850])= {0};
        uint32_t uwTimerPeriod  = 0;
        uint16_t _prevCount = 0;

};
#endif