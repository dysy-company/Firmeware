#include "Encoder_Extensia_2.h"

#ifdef __cplusplus
 extern "C" {
#endif

      
/* LPTIM handle declaration */
TIM_HandleTypeDef             timHandle_Extensia_2;
int8_t timerOverflowCounter1;
uint32_t delta1;
int curr_d1;
int prev_d1;
void Encoder_HAL_TIM_IC_MspInit_MPD(TIM_HandleTypeDef* htim_ic)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(htim_ic->Instance == ENCODER_EXTENSIA_2_TIMx)
    {
        /* Peripheral clock enable */
        ENCODER_EXTENSIA_2_TIMx_CLK_ENABLE();
        ENCODER_EXTENSIA_2_TIMx_GPIO_CH2_CLK_ENABLE();
        /* CH1 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_EXTENSIA_2_TIMx_CH1_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_EXTENSIA_2_TIMx_CH1_AF;
        HAL_GPIO_Init(ENCODER_EXTENSIA_2_TIMx_CH1_GPIO_PORT, &GPIO_InitStruct);
        /* CH2 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_EXTENSIA_2_TIMx_CH2_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_EXTENSIA_2_TIMx_CH2_AF;
        HAL_GPIO_Init(ENCODER_EXTENSIA_2_TIMx_CH2_GPIO_PORT, &GPIO_InitStruct);
        /* TIMx interrupt Init */
        HAL_NVIC_SetPriority(ENCODER_EXTENSIA_2_TIMx_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(ENCODER_EXTENSIA_2_TIMx_IRQn);
    }
    
}
void Encoder_HAL_TIM_IC_MspDeInit_MPD(TIM_HandleTypeDef* htim_ic){
    if(htim_ic->Instance == ENCODER_EXTENSIA_2_TIMx){
        /* Peripheral clock disable */
        ENCODER_EXTENSIA_2_TIMx_CLK_DISABLE();
        HAL_GPIO_DeInit(ENCODER_EXTENSIA_2_TIMx_CH2_GPIO_PORT, ENCODER_EXTENSIA_2_TIMx_CH2_PIN);
        HAL_GPIO_DeInit(ENCODER_EXTENSIA_2_TIMx_CH1_GPIO_PORT, ENCODER_EXTENSIA_2_TIMx_CH1_PIN);
        /* TIM3 interrupt DeInit */
        HAL_NVIC_DisableIRQ(ENCODER_EXTENSIA_2_TIMx_IRQn);
    }
}

void ENCODER_EXTENSIA_2_TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandle_Extensia_2);
}

void Encoder_HAL_TIM_PeriodElapsedCallback_MPD(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == ENCODER_EXTENSIA_2_TIMx)
    {
        uint32_t direction = (htim->Instance->CR1 & TIM_CR1_DIR) ? TIM_COUNTERMODE_DOWN : TIM_COUNTERMODE_UP;
        if (direction == TIM_COUNTERMODE_UP)
        {
            timerOverflowCounter1++;
             __HAL_TIM_SetCounter(htim,100);
            delta1=-100;
        }
        else
        {
             __HAL_TIM_SetCounter(htim,65436);
            timerOverflowCounter1--;
            delta1=100;
        }
    }
}
#ifdef __cplusplus
 }
#endif

void Encoder_Extensia_2::sharedConstructor(){
    TIM_Encoder_InitTypeDef sConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    /* reset handle state */
    __HAL_TIM_RESET_HANDLE_STATE(&timHandle_Extensia_2);
  
    /* Definition of TIM2 */
    timHandle_Extensia_2.Instance = ENCODER_EXTENSIA_2_TIMx;
    timHandle_Extensia_2.Init.Prescaler = 0;
    // timHandle_Extensia_2.Init.CounterMode = TIM_COUNTERMODE_UP;
    timHandle_Extensia_2.Init.Period = 0xffff;
    timHandle_Extensia_2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timHandle_Extensia_2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_RegisterCallback(&timHandle_Extensia_2, HAL_TIM_ENCODER_MSPINIT_CB_ID, Encoder_HAL_TIM_IC_MspInit_MPD);
    HAL_TIM_RegisterCallback(&timHandle_Extensia_2, HAL_TIM_ENCODER_MSPDEINIT_CB_ID, Encoder_HAL_TIM_IC_MspDeInit_MPD);
    sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
    sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC1Filter = 0xF;
    sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC2Filter = 0xF;
    uint32_t errorState = HAL_TIM_Encoder_Init(&timHandle_Extensia_2, &sConfig);
    
    HAL_TIM_RegisterCallback(&timHandle_Extensia_2, HAL_TIM_PERIOD_ELAPSED_CB_ID, Encoder_HAL_TIM_PeriodElapsedCallback_MPD);

    if (errorState != HAL_OK)
    {
      printf("\n\rError during HAL_TIM_Encoder_Init!Error code = %d;\n\r", (int)errorState);
    }else{
        __HAL_TIM_ENABLE_IT(&timHandle_Extensia_2, TIM_IT_UPDATE);
        __HAL_TIM_CLEAR_IT(&timHandle_Extensia_2 ,TIM_IT_UPDATE);
        errorState= HAL_TIM_Encoder_Start_IT(&timHandle_Extensia_2, TIM_CHANNEL_ALL);
        if(HAL_OK != errorState)
        {
          printf("\n\rError during HAL_TIM_Encoder_Start!Error code = %d;\n\r", (int)errorState);
        }else{
            __HAL_TIM_SetCounter(&timHandle_Extensia_2, 5);
            delta1=-5;
        }
    }
}

Encoder_Extensia_2::Encoder_Extensia_2(){
    this->sharedConstructor();
    timerOverflowCounter1=0;
    delta1=0;
    curr_d1=0;
    prev_d1=0;
    this->_encoderType = ENCODER_EXTENSIA_2_TYPE_RELATIVE_A_B;
    this->_enable = true;
    this->_stepValue = 0.0002;//1;
}
Encoder_Extensia_2::Encoder_Extensia_2(PinName pinEnable, uint32_t pinEnableActiveLevel){
    this->sharedConstructor();
    this->_pinEnable = pinEnable;
    this->_pinEnableActiveLevel = pinEnableActiveLevel;
    this->_encoderType = ENCODER_EXTENSIA_2_TYPE_RELATIVE_A_B_ENABLE;
    this->_enable = false;
    this->_stepValue = 0.0002;//1;
    int val;
    if(pinEnableActiveLevel == ENCODER_EXTENSIA_2_ACTIVE_LEVEL_LOW){
        val = 1;
    }else{
        val = 0;
    }
    this->_enablePin = new DigitalOut(this->_pinEnable, val);
}

Encoder_Extensia_2::~Encoder_Extensia_2(){
    delete this->_enablePin;
}

void Encoder_Extensia_2::setEnable(bool state){
    if (this->_encoderType == ENCODER_EXTENSIA_2_TYPE_RELATIVE_A_B_ENABLE){
        if(this->_enablePin != nullptr){
            if(state){
                int value = 0;
                if (this->_pinEnableActiveLevel == ENCODER_EXTENSIA_2_ACTIVE_LEVEL_HIGH){
                    value = 1;
                }
                _enablePin->write(value);
            }else{
                int value = 1;
                if (this->_pinEnableActiveLevel == ENCODER_EXTENSIA_2_ACTIVE_LEVEL_HIGH){
                    value = 0;
                }
                _enablePin->write(value);
            }
            this->_enable = state;
        }
    }
}
bool Encoder_Extensia_2::EdgeDetected(int extendedValue){
    if(curr_d1!=extendedValue){
        curr_d1=extendedValue;
        return true;
    }else{
        curr_d1=extendedValue;
        return false;
    }
}
int Encoder_Extensia_2::GetExtendedTimerValue_RAW()
{
    uint16_t timerValue = (uint16_t)__HAL_TIM_GetCounter(&timHandle_Extensia_2);
    int8_t overflowValue = timerOverflowCounter1;
    int extendedValue = ((overflowValue * (65535 + 1)) + timerValue+delta1);
    delta1=0;
    return extendedValue;
}
double Encoder_Extensia_2::GetExtendedTimerValue_MM()
{
    return GetExtendedTimerValue_RAW() * this->_stepValue;
}
int Encoder_Extensia_2::getLastPulsesCount(){
    int currentPulses = (int) __HAL_TIM_GetCounter(&timHandle_Extensia_2);
    return currentPulses;
}

double Encoder_Extensia_2::getLastPosition(){
    return this->getLastPulsesCount() * this->_stepValue;
}

void Encoder_Extensia_2::setStepValue(double stepValue){
    this->_stepValue = stepValue;
}

double Encoder_Extensia_2::getStepValue(){
    return this->_stepValue;
}

void Encoder_Extensia_2::resetPosition(){
    __HAL_TIM_SetCounter(&timHandle_Extensia_2, 0);
}

void Encoder_Extensia_2::resetPosition(int resetToPosition){
    __HAL_TIM_SetCounter(&timHandle_Extensia_2, (uint32_t)resetToPosition);
}

void Encoder_Extensia_2::HardSetLastPulsesCount(){
    int currentPulses = (int) __HAL_TIM_SetCounter(&timHandle_Extensia_2, 0);
}
