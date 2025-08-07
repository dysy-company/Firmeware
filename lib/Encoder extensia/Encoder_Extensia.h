#ifndef ENCODER_EXTENSIA_H
#define ENCODER_EXTENSIA_H
#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define ENCODER_EXTENSIA_TYPE_UNDEFINED                                                  0x00000000
#define ENCODER_EXTENSIA_TYPE_RELATIVE_A_B                                               0x00000001
#define ENCODER_EXTENSIA_TYPE_RELATIVE_A_B_ENABLE                                        0x00000002

#define ENCODER_EXTENSIA_ACTIVE_LEVEL_LOW                                                0x00000000
#define ENCODER_EXTENSIA_ACTIVE_LEVEL_HIGH                                               0x00000001

#define ENCODER_EXTENSIA_HALF_COUNTER_REGISTR                                            0x7FFF     

#define USE_HAL_TIM_REGISTER_CALLBACKS                                                   1U

#define ENCODER_EXTENSIA_TIMx                                                            TIM3

#define ENCODER_EXTENSIA_TIMx_IRQHandler                                                 TIM3_IRQHandler
#define ENCODER_EXTENSIA_TIMx_IRQn                                                       TIM3_IRQn
#define ENCODER_EXTENSIA_TIMx_IRQn_PreemptPriority                                       1
#define ENCODER_EXTENSIA_TIMx_IRQn_SubPriority                                           0

#define ENCODER_EXTENSIA_TIMx_CH1_PIN                                                    GPIO_PIN_6
#define ENCODER_EXTENSIA_TIMx_CH1_GPIO_PORT                                              GPIOC
#define ENCODER_EXTENSIA_TIMx_CH1_AF                                                     GPIO_AF2_TIM3

#define ENCODER_EXTENSIA_TIMx_CH2_PIN                                                    GPIO_PIN_7
#define ENCODER_EXTENSIA_TIMx_CH2_GPIO_PORT                                              GPIOC
#define ENCODER_EXTENSIA_TIMx_CH2_AF                                                     GPIO_AF2_TIM3

#define __HAL_RCC_ENCODER_EXTENSIA_TIMx_CLK_ENABLE                                       __HAL_RCC_TIM3_CLK_ENABLE
//#define __HAL_RCC_ENCODER_TIMx_GPIO_CH1_CLK_ENABLE                              __HAL_RCC_GPIOA_CLK_ENABLE
#define __HAL_RCC_ENCODER_EXTENSIA_TIMx_GPIO_CH2_CLK_ENABLE                              __HAL_RCC_GPIOC_CLK_ENABLE

#define __HAL_RCC_ENCODER_EXTENSIA_TIMx_CLK_DISABLE                                      __HAL_RCC_TIM3_CLK_DISABLE
//#define __HAL_RCC_ENCODER_TIMx_GPIO_CH1_CLK_DISABLE                             __HAL_RCC_GPIOA_CLK_DISABLE
#define __HAL_RCC_ENCODER_EXTENSIA_TIMx_GPIO_CH2_CLK_DISABLE                             __HAL_RCC_GPIOC_CLK_DISABLE

class Encoder_Extensia{
    public:
        Encoder_Extensia();
        Encoder_Extensia(PinName pinEnable, uint32_t pinEnableActiveLevel);
        ~Encoder_Extensia();
        void setEnable(bool state);
        void setStepValue(double stepValue);
        double getStepValue();
        int getLastPulsesCount();
        double getLastPosition();
        void resetPosition();
        void resetPosition(int resetToPosition);
        bool EdgeDetected(int extendedValue);
        int GetExtendedTimerValue_RAW();
        double GetExtendedTimerValue_MM();
        void HardSetLastPulsesCount();
       // static  void HAL_TIM_EmptyElapsedCallback(TIM_HandleTypeDef *htim);
       // void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
    private:
        uint32_t _encoderCounterForDummies;
        PinName _pinEnable;
        bool _enable;
        uint32_t _pinEnableActiveLevel;
        uint32_t _encoderType;
        DigitalOut *_enablePin;
        
        double _stepValue;

        void sharedConstructor();
};


#endif