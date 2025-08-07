#include "Encoder_Extensia.h"

#ifdef __cplusplus
 extern "C" {
#endif

      
/* LPTIM handle declaration */
TIM_HandleTypeDef             timHandle_Extensia;
int8_t timerOverflowCounter;
uint32_t delta;
int curr_d;
int prev_d;
void Encoder_HAL_TIM_IC_MspInit_Extensia(TIM_HandleTypeDef* htim_ic)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(htim_ic->Instance == ENCODER_EXTENSIA_TIMx)
    {
        /* Peripheral clock enable */
        __HAL_RCC_ENCODER_EXTENSIA_TIMx_CLK_ENABLE();
        __HAL_RCC_ENCODER_EXTENSIA_TIMx_GPIO_CH2_CLK_ENABLE();
        /* CH1 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_EXTENSIA_TIMx_CH1_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_EXTENSIA_TIMx_CH1_AF;
        HAL_GPIO_Init(ENCODER_EXTENSIA_TIMx_CH1_GPIO_PORT, &GPIO_InitStruct);
        /* CH2 GPIO Initialiaze */
        GPIO_InitStruct.Pin = ENCODER_EXTENSIA_TIMx_CH2_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = ENCODER_EXTENSIA_TIMx_CH2_AF;
        HAL_GPIO_Init(ENCODER_EXTENSIA_TIMx_CH2_GPIO_PORT, &GPIO_InitStruct);
        /* TIMx interrupt Init */
        HAL_NVIC_SetPriority(ENCODER_EXTENSIA_TIMx_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ENCODER_EXTENSIA_TIMx_IRQn);
    }
    
}
void Encoder_HAL_TIM_IC_MspDeInit_Extensia(TIM_HandleTypeDef* htim_ic){
    if(htim_ic->Instance == ENCODER_EXTENSIA_TIMx){
        /* Peripheral clock disable */
        __HAL_RCC_ENCODER_EXTENSIA_TIMx_CLK_DISABLE();
        HAL_GPIO_DeInit(ENCODER_EXTENSIA_TIMx_CH2_GPIO_PORT, ENCODER_EXTENSIA_TIMx_CH2_PIN);
        HAL_GPIO_DeInit(ENCODER_EXTENSIA_TIMx_CH1_GPIO_PORT, ENCODER_EXTENSIA_TIMx_CH1_PIN);
        /* TIM3 interrupt DeInit */
        HAL_NVIC_DisableIRQ(ENCODER_EXTENSIA_TIMx_IRQn);
    }
}

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&timHandle_Extensia);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == ENCODER_EXTENSIA_TIMx)
    {
        uint32_t direction = (htim->Instance->CR1 & TIM_CR1_DIR) ? TIM_COUNTERMODE_DOWN : TIM_COUNTERMODE_UP;
        //__HAL_TIM_SetCounter(htim, 0x7FFF);
        //uint32_t currVal=(uint32_t)__HAL_TIM_GetCounter(htim);
        if (direction == TIM_COUNTERMODE_UP)
        {
            timerOverflowCounter++;
             __HAL_TIM_SetCounter(htim,100);
            delta=-100;
        }
        else
        {
             __HAL_TIM_SetCounter(htim,65436);
            timerOverflowCounter--;
            delta=100;
        }
       // printf("Counter: %d",timerOverflowCounter);
    }
}
#ifdef __cplusplus
 }
#endif

void Encoder_Extensia::sharedConstructor(){
    TIM_Encoder_InitTypeDef sConfig = {0};
    /* reset handle state */
    __HAL_TIM_RESET_HANDLE_STATE(&timHandle_Extensia);
    
   // HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_ENCODER_MSPINIT_CB_ID, Encoder_HAL_TIM_IC_MspInit);
   
   // HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_ENCODER_MSPDEINIT_CB_ID, HAL_TIM_PeriodElapsedCallback);
  
    /* Definition of TIM2 */
    timHandle_Extensia.Instance = ENCODER_EXTENSIA_TIMx;
    timHandle_Extensia.Init.Prescaler = 0;
   // timHandle_Extensia.Init.CounterMode = TIM_COUNTERMODE_UP;
    timHandle_Extensia.Init.Period = 0xffff;
    timHandle_Extensia.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timHandle_Extensia.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_ENCODER_MSPINIT_CB_ID, Encoder_HAL_TIM_IC_MspInit_Extensia);
    HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_ENCODER_MSPDEINIT_CB_ID, Encoder_HAL_TIM_IC_MspDeInit_Extensia);
    //HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_PERIOD_ELAPSED_CB_ID, HAL_TIM_PeriodElapsedCallback);
    sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
    sConfig.IC1Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC1Filter = 0xF;
    sConfig.IC2Polarity = TIM_ICPOLARITY_FALLING;
    sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
    sConfig.IC2Filter = 0xF;
    uint32_t errorState = HAL_TIM_Encoder_Init(&timHandle_Extensia, &sConfig);
    
    //int err=HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_PERIOD_ELAPSED_CB_ID, HAL_TIM_PeriodElapsedCallback);
    
    //HAL_TIM_RegisterCallback(&timHandle_Extensia, HAL_TIM_OC_DELAY_ELAPSED_CB_ID, HAL_TIM_EmptyElapsedCallback);
    
    if (errorState != HAL_OK)
    {
      printf("\n\rError during HAL_TIM_Encoder_Init!Error code = %d;\n\r", (int)errorState);
    }else{
        __HAL_TIM_ENABLE_IT(&timHandle_Extensia, TIM_IT_UPDATE);
        __HAL_TIM_CLEAR_IT(&timHandle_Extensia ,TIM_IT_UPDATE);
        errorState= HAL_TIM_Encoder_Start_IT(&timHandle_Extensia, TIM_CHANNEL_ALL);
        if(HAL_OK != errorState)
        {
          printf("\n\rError during HAL_TIM_Encoder_Start!Error code = %d;\n\r", (int)errorState);
        }else{
            __HAL_TIM_SetCounter(&timHandle_Extensia, 5);
            delta=-5;
        }
    }
}

Encoder_Extensia::Encoder_Extensia(){
    this->sharedConstructor();
    timerOverflowCounter=0;
    delta=0;
    curr_d=0;
    prev_d=0;
    this->_encoderType = ENCODER_EXTENSIA_TYPE_RELATIVE_A_B;
    this->_enable = true;
    this->_stepValue = 0.0002;//1;
}
Encoder_Extensia::Encoder_Extensia(PinName pinEnable, uint32_t pinEnableActiveLevel){
    this->sharedConstructor();
    this->_pinEnable = pinEnable;
    this->_pinEnableActiveLevel = pinEnableActiveLevel;
    this->_encoderType = ENCODER_EXTENSIA_TYPE_RELATIVE_A_B_ENABLE;
    this->_enable = false;
    this->_stepValue = 0.0002;//1;
    int val;
    if(pinEnableActiveLevel == ENCODER_EXTENSIA_ACTIVE_LEVEL_LOW){
        val = 1;
    }else{
        val = 0;
    }
    this->_enablePin = new DigitalOut(this->_pinEnable, val);
}

Encoder_Extensia::~Encoder_Extensia(){
    delete this->_enablePin;
}

void Encoder_Extensia::setEnable(bool state){
    if (this->_encoderType == ENCODER_EXTENSIA_TYPE_RELATIVE_A_B_ENABLE){
        if(this->_enablePin != nullptr){
            if(state){
                int value = 0;
                if (this->_pinEnableActiveLevel == ENCODER_EXTENSIA_ACTIVE_LEVEL_HIGH){
                    value = 1;
                }
                _enablePin->write(value);
            }else{
                int value = 1;
                if (this->_pinEnableActiveLevel == ENCODER_EXTENSIA_ACTIVE_LEVEL_HIGH){
                    value = 0;
                }
                _enablePin->write(value);
            }
            this->_enable = state;
        }
    }
}
bool Encoder_Extensia::EdgeDetected(int extendedValue){
    if(curr_d!=extendedValue){
        curr_d=extendedValue;
        return true;
    }else{
        curr_d=extendedValue;
        return false;
    }
}
int Encoder_Extensia::GetExtendedTimerValue_RAW()
{
    uint16_t timerValue = (uint16_t)__HAL_TIM_GetCounter(&timHandle_Extensia);
    int8_t overflowValue = timerOverflowCounter;
    int extendedValue = ((overflowValue * (65535 + 1)) + timerValue+delta);
    delta=0;
    return extendedValue;
}
double Encoder_Extensia::GetExtendedTimerValue_MM()
{
    return GetExtendedTimerValue_RAW() * this->_stepValue;
}
int Encoder_Extensia::getLastPulsesCount(){
    int currentPulses = (int) __HAL_TIM_GetCounter(&timHandle_Extensia);
    return currentPulses;
}

double Encoder_Extensia::getLastPosition(){
    return this->getLastPulsesCount() * this->_stepValue;
}

void Encoder_Extensia::setStepValue(double stepValue){
    this->_stepValue = stepValue;
}

double Encoder_Extensia::getStepValue(){
    return this->_stepValue;
}

void Encoder_Extensia::resetPosition(){
    __HAL_TIM_SetCounter(&timHandle_Extensia, 0);
}

void Encoder_Extensia::resetPosition(int resetToPosition){
    __HAL_TIM_SetCounter(&timHandle_Extensia, (uint32_t)resetToPosition);
}

void Encoder_Extensia::HardSetLastPulsesCount(){
   // int currentPulses = (int) 
    __HAL_TIM_SetCounter(&timHandle_Extensia, 0);
}
