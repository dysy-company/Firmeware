#include "Encoder.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* LPTIM handle declaration */
TIM_HandleTypeDef             timHandle;

void Encoder_HAL_TIM_IC_MspInit(TIM_HandleTypeDef* htim_ic)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(htim_ic->Instance == ENCODER_TIMx)
    {
        /* Peripheral clock enable */
        __HAL_RCC_ENCODER_TIMx_CLK_ENABLE();
        __HAL_RCC_ENCODER_TIMx_GPIO_CH1_CLK_ENABLE();
        __HAL_RCC_ENCODER_TIMx_GPIO_CH2_CLK_ENABLE();
        /* CH1 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_TIMx_CH1_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_TIMx_CH1_AF;
        HAL_GPIO_Init(ENCODER_TIMx_CH1_GPIO_PORT, &GPIO_InitStruct);
        /* CH2 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_TIMx_CH2_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_TIMx_CH2_AF;
        HAL_GPIO_Init(ENCODER_TIMx_CH2_GPIO_PORT, &GPIO_InitStruct);
        /* TIMx interrupt Init */
        HAL_NVIC_SetPriority(ENCODER_TIMx_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ENCODER_TIMx_IRQn);
    }
}
void Encoder_HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* htim_ic){
    if(htim_ic->Instance == ENCODER_TIMx){
        /* Peripheral clock disable */
        __HAL_RCC_ENCODER_TIMx_CLK_DISABLE();
        HAL_GPIO_DeInit(ENCODER_TIMx_CH2_GPIO_PORT, ENCODER_TIMx_CH2_PIN);
        HAL_GPIO_DeInit(ENCODER_TIMx_CH1_GPIO_PORT, ENCODER_TIMx_CH1_PIN);
        /* TIM3 interrupt DeInit */
        HAL_NVIC_DisableIRQ(ENCODER_TIMx_IRQn);
    }
}

void ENCODER_TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandle);
}

#ifdef __cplusplus
 }
#endif

void Encoder::sharedConstructor(){
    TIM_Encoder_InitTypeDef sConfig = {0};
    /* reset handle state */
    __HAL_TIM_RESET_HANDLE_STATE(&timHandle);
    /* Definition of TIM2 */
    timHandle.Instance = ENCODER_TIMx;
    timHandle.Init.Prescaler = 0;
    timHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    timHandle.Init.Period = 0xFFFFFFFF;
    timHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    HAL_TIM_RegisterCallback(&timHandle, HAL_TIM_ENCODER_MSPINIT_CB_ID, Encoder_HAL_TIM_IC_MspInit);
    HAL_TIM_RegisterCallback(&timHandle, HAL_TIM_ENCODER_MSPDEINIT_CB_ID, Encoder_HAL_TIM_IC_MspDeInit);
    
    sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
    sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC1Filter = 0xF;
    sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC2Filter = 0xF;
    uint32_t errorState = HAL_TIM_Encoder_Init(&timHandle, &sConfig);
    if (errorState != HAL_OK)
    {
      printf("\n\rError during HAL_TIM_Encoder_Init!Error code = %d;\n\r", (int)errorState);
    }else{
        errorState = HAL_TIM_Encoder_Start(&timHandle, TIM_CHANNEL_ALL);
        if(HAL_OK != errorState)
        {
          printf("\n\rError during HAL_TIM_Encoder_Start!Error code = %d;\n\r", (int)errorState);
        }else{
            __HAL_TIM_SetCounter(&timHandle, 0);
        }
    }
}

Encoder::Encoder(){
    this->sharedConstructor();
    this->_encoderType = ENCODER_TYPE_RELATIVE_A_B;
    this->_enable = true;
    this->_stepValue = 0.0005;//1;
}
Encoder::Encoder(PinName pinEnable, uint32_t pinEnableActiveLevel){
    this->sharedConstructor();
    this->_pinEnable = pinEnable;
    this->_pinEnableActiveLevel = pinEnableActiveLevel;
    this->_encoderType = ENCODER_TYPE_RELATIVE_A_B_ENABLE;
    this->_enable = false;
    this->_stepValue = 0.0005;//1;
    int val;
    if(pinEnableActiveLevel == ENCODER_ACTIVE_LEVEL_LOW){
        val = 1;
    }else{
        val = 0;
    }
    this->_enablePin = new DigitalOut(this->_pinEnable, val);
}

Encoder::~Encoder(){
    delete this->_enablePin;
}

void Encoder::setEnable(bool state){
    if (this->_encoderType == ENCODER_TYPE_RELATIVE_A_B_ENABLE){
        if(this->_enablePin != nullptr){
            if(state){
                int value = 0;
                if (this->_pinEnableActiveLevel == ENCODER_ACTIVE_LEVEL_HIGH){
                    value = 1;
                }
                _enablePin->write(value);
            }else{
                int value = 1;
                if (this->_pinEnableActiveLevel == ENCODER_ACTIVE_LEVEL_HIGH){
                    value = 0;
                }
                _enablePin->write(value);
            }
            this->_enable = state;
        }
    }
}


int Encoder::getLastPulsesCount(){
    int currentPulses = (int) __HAL_TIM_GetCounter(&timHandle);
    return currentPulses;
}

void Encoder::setPulesCount(int pulses){
    __HAL_TIM_SetCounter(&timHandle, pulses);
}

void Encoder::HardSetLastPulsesCount(){
    //int currentPulses = (int) 
    __HAL_TIM_SetCounter(&timHandle, 0);
}

double Encoder::getLastPosition(){
    return this->getLastPulsesCount() * this->_stepValue;
}

void Encoder::setStepValue(double stepValue){
    this->_stepValue = stepValue;
}

double Encoder::getStepValue(){
    return this->_stepValue;
}

void Encoder::resetPosition(){
    __HAL_TIM_SetCounter(&timHandle, 0);
}

void Encoder::resetPosition(int resetToPosition){
    __HAL_TIM_SetCounter(&timHandle, (uint32_t)resetToPosition);
}