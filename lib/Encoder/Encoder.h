#ifndef ENCODER_H
#define ENCODER_H
#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define ENCODER_TYPE_UNDEFINED                                                  0x00000000
#define ENCODER_TYPE_RELATIVE_A_B                                               0x00000001
#define ENCODER_TYPE_RELATIVE_A_B_ENABLE                                        0x00000002

#define ENCODER_ACTIVE_LEVEL_LOW                                                0x00000000
#define ENCODER_ACTIVE_LEVEL_HIGH                                               0x00000001

#define USE_HAL_TIM_REGISTER_CALLBACKS                                          1U

#define ENCODER_TIMx                                                            TIM2

#define ENCODER_TIMx_IRQHandler                                                 TIM2_IRQHandler
#define ENCODER_TIMx_IRQn                                                       TIM2_IRQn
#define ENCODER_TIMx_IRQn_PreemptPriority                                       1
#define ENCODER_TIMx_IRQn_SubPriority                                           0

#define ENCODER_TIMx_CH1_PIN                                                    GPIO_PIN_0
#define ENCODER_TIMx_CH1_GPIO_PORT                                              GPIOA
#define ENCODER_TIMx_CH1_AF                                                     GPIO_AF1_TIM2

#define ENCODER_TIMx_CH2_PIN                                                    GPIO_PIN_3
#define ENCODER_TIMx_CH2_GPIO_PORT                                              GPIOB
#define ENCODER_TIMx_CH2_AF                                                     GPIO_AF1_TIM2

#define __HAL_RCC_ENCODER_TIMx_CLK_ENABLE                                       __HAL_RCC_TIM2_CLK_ENABLE
#define __HAL_RCC_ENCODER_TIMx_GPIO_CH1_CLK_ENABLE                              __HAL_RCC_GPIOA_CLK_ENABLE
#define __HAL_RCC_ENCODER_TIMx_GPIO_CH2_CLK_ENABLE                              __HAL_RCC_GPIOB_CLK_ENABLE

#define __HAL_RCC_ENCODER_TIMx_CLK_DISABLE                                      __HAL_RCC_TIM2_CLK_DISABLE
#define __HAL_RCC_ENCODER_TIMx_GPIO_CH1_CLK_DISABLE                             __HAL_RCC_GPIOA_CLK_DISABLE
#define __HAL_RCC_ENCODER_TIMx_GPIO_CH2_CLK_DISABLE                             __HAL_RCC_GPIOB_CLK_DISABLE

class Encoder{
    public:
        Encoder();
        Encoder(PinName pinEnable, uint32_t pinEnableActiveLevel);
        ~Encoder();

        void setEnable(bool state);
        void setStepValue(double stepValue);
        double getStepValue();
        int getLastPulsesCount();
        void setPulesCount(int pulses);
        void HardSetLastPulsesCount();
        double getLastPosition();
        void resetPosition();
        void resetPosition(int resetToPosition);

    private:
        
        PinName _pinEnable;
        bool _enable;
        uint32_t _pinEnableActiveLevel;
        uint32_t _encoderType;

        DigitalOut *_enablePin;
        
        double _stepValue;

        void sharedConstructor();
};


#endif