#include <PWM.h>

#ifdef __cplusplus
 extern "C" {
#endif
//TIM_HandleTypeDef PWM_TIMx_;
TIM_HandleTypeDef    TimHandle;
static DMA_HandleTypeDef  hdma_tim1;
static DMA_HandleTypeDef  hdma_tim2;
GPIO_InitTypeDef   GPIO_InitStruct;
uint8_t MDT;

static void Error_Handler1(void)
{
  /* Turn LED2 on */
  //BSP_LED_On(LED2);
  printf("\n\rPWM Error Handler!!!!\n\r");
  while (1)
  {
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    switch (MDT)
    {
    case MOTOR_DRIVER_TYPE_STEP_DIR:{
        GPIO_InitStruct.Pin = PWM_TIMx_CH3_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH3_AF;
        HAL_GPIO_Init(PWM_TIMx_CH3_GPIO_PORT , &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PWM_TIMx_CH4_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH4_AF;
        HAL_GPIO_Init(PWM_TIMx_CH4_GPIO_PORT , &GPIO_InitStruct);
        break;
    }
    case MOTOR_DRIVER_TYPE_CW_CCW:{
        GPIO_InitStruct.Pin = PWM_TIMx_CH3_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH3_AF;
        HAL_GPIO_Init(PWM_TIMx_CH3_GPIO_PORT , &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PWM_TIMx_CH4_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH4_AF;
        HAL_GPIO_Init(PWM_TIMx_CH4_GPIO_PORT , &GPIO_InitStruct);
        break;
    }
    default:
        break;
    }
    PWM_TIMx_CLK_ENABLE();
    PWM_GPIOx_CLK_ENABLE()
    DMAx_CLK_ENABLE();

	#if BOARD_INDEX == 2
    hdma_tim1.Init.Request  = TIMx_CC1_DMA_REQUEST;//|TIMx_CC2_DMA_REQUEST;
    #endif
    #if BOARD_INDEX == 3
    hdma_tim1.Init.Channel = DMA_CHANNEL_2;
    #endif
    hdma_tim1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;
    hdma_tim1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;
    hdma_tim1.Init.Mode = DMA_NORMAL;
    hdma_tim1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_tim1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_tim1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_tim1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_tim1.Init.PeriphBurst = DMA_PBURST_SINGLE;

    /* Set hdma_tim1 instance */
    hdma_tim1.Instance = TIMx_CC1_DMA_INST;

    /* Link hdma_tim1 to hdma[TIM_DMA_ID_CC1] (channel1) */
    __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_CC1], hdma_tim1);

    /* Initialize TIMx DMA handle */
    //HAL_DMA_Init(htim->hdma[TIM_DMA_ID_CC2]);
    HAL_DMA_Init(&hdma_tim1);

    #if BOARD_INDEX == 2
    hdma_tim2.Init.Request  = TIMx_CC2_DMA_REQUEST;
    #endif
    #if BOARD_INDEX == 3
    hdma_tim2.Init.Channel = DMA_CHANNEL_2;
    #endif
    hdma_tim2.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;
    hdma_tim2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;
    hdma_tim2.Init.Mode = DMA_NORMAL;
    hdma_tim2.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_tim2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_tim2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_tim2.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_tim2.Init.PeriphBurst = DMA_PBURST_SINGLE;

    /* Set hdma_tim2 instance */
    hdma_tim2.Instance = TIMx_CC2_DMA_INST;

    /* Link hdma_tim2 to hdma[TIM_DMA_ID_CC1] (channel1) */
    __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_CC2], hdma_tim2);

    /* Initialize TIMx DMA handle */
    //HAL_DMA_Init(htim->hdma[TIM_DMA_ID_CC2]);
    HAL_DMA_Init(&hdma_tim2);


    /*##-2- Configure the NVIC for DMA #########################################*/
    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(TIMx_DMA_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIMx_DMA_IRQn);
    HAL_NVIC_SetPriority(TIMx_DMA_IRQn1, 0, 0);
    HAL_NVIC_EnableIRQ(TIMx_DMA_IRQn1);
}

void TIMx_DMA_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_tim1);
}

void TIMx_DMA_IRQHandler1(void)
{
  //HAL_DMA_IRQHandler(TimHandle.hdma[TIM_DMA_ID_CC1]);
  HAL_DMA_IRQHandler(&hdma_tim2);
}

#ifdef __cplusplus
 }
#endif

PWM::PWM(uint16_t pwm_value){
    this->_pwm_value = pwm_value;
}

PWM::~PWM(){

}

void PWM::init(uint8_t motorDriverType, uint32_t pwmFreq){
    MDT = motorDriverType;
    uwTimerPeriod = (uint32_t)(((SystemCoreClock/2) / pwmFreq) - 1); //500000
    for (uint16_t i = 0; i < 200; i++)
    {
        //if(i == 4)
        //    this->aCCValue_Buffer[i] = 0;
        //else
        this->aCCValue_Buffer[i] = (uint32_t)(((uint32_t) 50 * (uwTimerPeriod - 1)) / 100);
    }
    
    SCB_CleanDCache_by_Addr((uint32_t *) aCCValue_Buffer, sizeof(aCCValue_Buffer) );

    TimHandle.Instance = PWM_TIMx;
    #if BOARD_INDEX == 2
    TimHandle.Init.Period            = uwTimerPeriod;
    TimHandle.Init.RepetitionCounter = 3;
    TimHandle.Init.Prescaler         = 0;
    TimHandle.Init.ClockDivision     = 0;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    #endif
    #if BOARD_INDEX == 3
    TimHandle.Init.Period            = uwTimerPeriod;
    TimHandle.Init.RepetitionCounter = 3;
    TimHandle.Init.Prescaler         = 0;
    TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    #endif
    if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler1();
    }
    sConfig.OCMode       = TIM_OCMODE_PWM1;
    sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
    sConfig.Pulse        = aCCValue_Buffer[0];
    sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
    sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
    sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
    sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
    {
        /* Configuration Error */
        Error_Handler1();
    }
    if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
    {
        /* Configuration Error */
        Error_Handler1();
    }
}

void PWM::resetPWM(){
    this->aCCValue_Buffer[_prevCount] = (uint32_t)(((uint32_t) 50 * (uwTimerPeriod - 1)) / 100);
}

void PWM::setPWM(uint8_t motorDriverType, int direction, uint16_t count){
    
    if(count > 0){
        this->aCCValue_Buffer[count] = 0;
        
        switch (motorDriverType)
        {
        case MOTOR_DRIVER_TYPE_STEP_DIR:{
            if (direction){
                PWM_TIMx_CH4_GPIO_PORT->BSRR = ((uint32_t)PWM_TIMx_CH4_PIN) << 16;
            }else{
                PWM_TIMx_CH4_GPIO_PORT->BSRR = PWM_TIMx_CH4_PIN;
            }
            wait_us(100);
            HAL_TIM_PWM_Start_DMA(&TimHandle, TIM_CHANNEL_1, aCCValue_Buffer, count + 1);
            break;
        }
        case MOTOR_DRIVER_TYPE_CW_CCW:{
            if (direction){
                HAL_TIM_PWM_Start_DMA(&TimHandle, TIM_CHANNEL_1, aCCValue_Buffer, count + 1);
            }else{
                HAL_TIM_PWM_Start_DMA(&TimHandle, TIM_CHANNEL_2, aCCValue_Buffer, count + 1);
            }
        }
        default:
            break;
        }
        this->_prevCount = count;
    }
}

void PWM::stopPWM(uint8_t motorDriverType, int direction){
    switch (motorDriverType)
    {
    case MOTOR_DRIVER_TYPE_STEP_DIR:{
        HAL_TIM_PWM_Stop_DMA(&TimHandle, TIM_CHANNEL_1);
        break;
    }
    // case MOTOR_DRIVER_TYPE_CW_CCW:{
    //     if (direction){
    //         HAL_TIM_PWM_Stop_DMA(&TimHandle, TIM_CHANNEL_1);
    //     }else{
    //         HAL_TIM_PWM_Stop_DMA(&TimHandle, TIM_CHANNEL_2);
    //     }
    // }
    default:
        break;
    }
}

void PWM::initGPIOPort(uint8_t motorDriverType){
    switch (motorDriverType)
    {
    case MOTOR_DRIVER_TYPE_STEP_DIR:{
        GPIO_InitStruct.Pin = PWM_TIMx_CH3_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH3_AF;
        HAL_GPIO_Init(PWM_TIMx_CH3_GPIO_PORT , &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PWM_TIMx_CH4_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH4_AF;
        HAL_GPIO_Init(PWM_TIMx_CH4_GPIO_PORT , &GPIO_InitStruct);
        break;
    }
    case MOTOR_DRIVER_TYPE_CW_CCW:{
        GPIO_InitStruct.Pin = PWM_TIMx_CH3_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH3_AF;
        HAL_GPIO_Init(PWM_TIMx_CH3_GPIO_PORT , &GPIO_InitStruct);

        GPIO_InitStruct.Pin = PWM_TIMx_CH4_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = PWM_TIMx_CH4_AF;
        HAL_GPIO_Init(PWM_TIMx_CH4_GPIO_PORT , &GPIO_InitStruct);
        break;
    }
    default:
        break;
    }
}