#ifndef ENCODER_EXTENSIA_2_H
#define ENCODER_EXTENSIA_2_H
#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define ENCODER_EXTENSIA_2_TYPE_UNDEFINED                                                  0x00000000
#define ENCODER_EXTENSIA_2_TYPE_RELATIVE_A_B                                               0x00000001
#define ENCODER_EXTENSIA_2_TYPE_RELATIVE_A_B_ENABLE                                        0x00000002

#define ENCODER_EXTENSIA_2_ACTIVE_LEVEL_LOW                                                0x00000000
#define ENCODER_EXTENSIA_2_ACTIVE_LEVEL_HIGH                                               0x00000001

#define ENCODER_EXTENSIA_2_HALF_COUNTER_REGISTR                                            0x7FFF     

#define USE_HAL_TIM_REGISTER_CALLBACKS                                                   1U

#define ENCODER_EXTENSIA_2_TIMx                                                            TIM1

#define ENCODER_EXTENSIA_2_TIMx_IRQHandler                                                 TIM1_CC_IRQHandler
#define ENCODER_EXTENSIA_2_TIMx_IRQn                                                       TIM1_CC_IRQn
#define ENCODER_EXTENSIA_2_TIMx_IRQn_PreemptPriority                                       1
#define ENCODER_EXTENSIA_2_TIMx_IRQn_SubPriority                                           0

#define ENCODER_EXTENSIA_2_TIMx_CH1_PIN                                                    GPIO_PIN_9
#define ENCODER_EXTENSIA_2_TIMx_CH1_GPIO_PORT                                              GPIOE
#define ENCODER_EXTENSIA_2_TIMx_CH1_AF                                                     GPIO_AF1_TIM1

#define ENCODER_EXTENSIA_2_TIMx_CH2_PIN                                                    GPIO_PIN_11
#define ENCODER_EXTENSIA_2_TIMx_CH2_GPIO_PORT                                              GPIOE
#define ENCODER_EXTENSIA_2_TIMx_CH2_AF                                                     GPIO_AF1_TIM1

#define ENCODER_EXTENSIA_2_TIMx_CLK_ENABLE                                       __HAL_RCC_TIM1_CLK_ENABLE
#define ENCODER_EXTENSIA_2_TIMx_GPIO_CH2_CLK_ENABLE                              __HAL_RCC_GPIOE_CLK_ENABLE

#define ENCODER_EXTENSIA_2_TIMx_CLK_DISABLE                                      __HAL_RCC_TIM1_CLK_DISABLE
#define ENCODER_EXTENSIA_2_TIMx_GPIO_CH2_CLK_DISABLE                             __HAL_RCC_GPIOE_CLK_DISABLE

class Encoder_Extensia_2{
    public:
        Encoder_Extensia_2();
        Encoder_Extensia_2(PinName pinEnable, uint32_t pinEnableActiveLevel);
        ~Encoder_Extensia_2();
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