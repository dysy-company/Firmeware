#include <MCP492x.h>

#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   MCP492x_SPI;
//DMA_HandleTypeDef   MCP492x_DMA_SPI_RX;
//DMA_HandleTypeDef   MCP492x_DMA_SPI_TX;
static volatile uint32_t tMCP492xSPITransferState = MCP492x_DMA_SPI_TRANSFER_WAIT;

//void MCP492x_SPIx_DMA_TX_IRQHandler(void)
//{
//  HAL_DMA_IRQHandler(&MCP492x_DMA_SPI_TX);
//}

void MCP492x_SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&MCP492x_SPI);
}

void MCP492x_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==MCP492x_SPIx){
    /* SPIx clock enable */
    MCP492x_SPIx_SCK_GPIO_CLK_ENABLE();
    MCP492x_SPIx_MOSI_GPIO_CLK_ENABLE();
    MCP492x_SPIx_CS_GPIO_CLK_ENABLE();
    MCP492x_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    //MCP492x_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    GPIO_InitStruct.Pin =       MCP492x_SPIx_CS_PIN;
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    #endif
    #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    #endif
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_SPIx_CS_AF;
    HAL_GPIO_Init(MCP492x_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    //SPIx_NSS2
    GPIO_InitStruct.Pin =       MCP492x_SPIx_CS2_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_SPIx_CS2_AF;
    HAL_GPIO_Init(MCP492x_SPIx_CS2_GPIO_PORT, &GPIO_InitStruct);
     //SPIx_NSS3
    GPIO_InitStruct.Pin =       MCP492x_SPIx_CS3_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_SPIx_CS3_AF;
    HAL_GPIO_Init(MCP492x_SPIx_CS3_GPIO_PORT, &GPIO_InitStruct);
    #endif
    //SPIx_SCK
    GPIO_InitStruct.Pin =       MCP492x_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_SPIx_SCK_AF;
    
    HAL_GPIO_Init(MCP492x_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MOSI
    GPIO_InitStruct.Pin =       MCP492x_SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP; //old NO PULLUP
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_SPIx_MOSI_AF;
    HAL_GPIO_Init(MCP492x_SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_TX Init */
    /*
    MCP492x_DMA_SPI_TX.Instance =                 MCP492x_SPIx_TX_DMA_STREAM;
    MCP492x_DMA_SPI_TX.Init.Request =             MCP492x_SPIx_TX_DMA_REQUEST;
    MCP492x_DMA_SPI_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    MCP492x_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    MCP492x_DMA_SPI_TX.Init.MemInc =              DMA_MINC_ENABLE;
    MCP492x_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    MCP492x_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    MCP492x_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    MCP492x_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_MEDIUM;
    MCP492x_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    MCP492x_DMA_SPI_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    MCP492x_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    MCP492x_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC4;
    
    if (HAL_DMA_Init(&MCP492x_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, MCP492x_DMA_SPI_TX);*/
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    /*
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( MCP492x_SPIx_DMA_TX_IRQn, 
                          MCP492x_SPIx_DMA_TX_IRQn_PreemptPriority, 
                          MCP492x_SPIx_DMA_TX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP492x_SPIx_DMA_TX_IRQn);*/
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( MCP492x_SPIx_IRQn, 
                          MCP492x_SPIx_IRQn_PreemptPriority, 
                          MCP492x_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP492x_SPIx_IRQn);
  }
}

void MCP492x_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==MCP492x_SPIx)
  {
    /* Peripheral clock disable */
    MCP492x_SPIx_CLK_DISABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MOSI
    */
    HAL_GPIO_DeInit(MCP492x_SPIx_SCK_GPIO_PORT, MCP492x_SPIx_SCK_PIN);
    HAL_GPIO_DeInit(MCP492x_SPIx_CS_GPIO_PORT, MCP492x_SPIx_CS_PIN);
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    HAL_GPIO_DeInit(MCP492x_SPIx_CS2_GPIO_PORT, MCP492x_SPIx_CS2_PIN);
    HAL_GPIO_DeInit(MCP492x_SPIx_CS3_GPIO_PORT, MCP492x_SPIx_CS3_PIN);
    #endif
    HAL_GPIO_DeInit(MCP492x_SPIx_MOSI_GPIO_PORT, MCP492x_SPIx_MOSI_PIN);
    /* SPIx DMA DeInit */
    //HAL_DMA_DeInit(spiHandle->hdmatx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(MCP492x_SPIx_IRQn);
  }
}

void MCP492x_HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  tMCP492xSPITransferState = MCP492x_DMA_SPI_TRANSFER_COMPLETE;
}

void MCP492x_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  tMCP492xSPITransferState = MCP492x_DMA_SPI_TRANSFER_ERROR;
}
#ifdef __cplusplus
 }
#endif
//mode 0 or 3, freq in Hz
MCP492x::MCP492x(int spiMode, int spiBaudRatePrescaler){
    #if BOARD_INDEX == 2
    MCP492x_SPI.Instance = MCP492x_SPIx;
    MCP492x_SPI.Init.Mode = SPI_MODE_MASTER;
    MCP492x_SPI.Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
    MCP492x_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
    MCP492x_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    MCP492x_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      MCP492x_SPI.Init.NSS = SPI_NSS_SOFT;
    #endif
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
    MCP492x_SPI.Init.NSS = SPI_NSS_HARD_OUTPUT;
    #endif
    MCP492x_SPI.Init.BaudRatePrescaler = spiBaudRatePrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    MCP492x_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    MCP492x_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    MCP492x_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    MCP492x_SPI.Init.CRCPolynomial = 0x0;
    MCP492x_SPI.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    MCP492x_SPI.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    MCP492x_SPI.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    MCP492x_SPI.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP492x_SPI.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP492x_SPI.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    MCP492x_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    MCP492x_SPI.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    MCP492x_SPI.Init.IOSwap = SPI_IO_SWAP_DISABLE;
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_MSPINIT_CB_ID, MCP492x_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_MSPDEINIT_CB_ID,MCP492x_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&MCP492x_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        //return errorState;
    }
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_TX_COMPLETE_CB_ID, MCP492x_HAL_SPI_TxCpltCallback);
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_ERROR_CB_ID,MCP492x_HAL_SPI_ErrorCallback);
    #endif
    #if BOARD_INDEX == 3
    MCP492x_SPI.Instance = MCP492x_SPIx;
    MCP492x_SPI.Init.Mode = SPI_MODE_MASTER;
    MCP492x_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    MCP492x_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
    MCP492x_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    MCP492x_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    MCP492x_SPI.Init.NSS = SPI_NSS_SOFT;
    MCP492x_SPI.Init.BaudRatePrescaler = spiBaudRatePrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    MCP492x_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    MCP492x_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    MCP492x_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    MCP492x_SPI.Init.CRCPolynomial = 0x0;
    MCP492x_SPI.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;

    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_MSPINIT_CB_ID, MCP492x_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_MSPDEINIT_CB_ID,MCP492x_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&MCP492x_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        //return errorState;
    }
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_TX_COMPLETE_CB_ID, MCP492x_HAL_SPI_TxCpltCallback);
    HAL_SPI_RegisterCallback(&MCP492x_SPI, HAL_SPI_ERROR_CB_ID,MCP492x_HAL_SPI_ErrorCallback);
    #endif
    
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    MCP492x_SPIx_CS_GPIO_PORT->BSRR = MCP492x_SPIx_CS_PIN;
    MCP492x_SPIx_CS2_GPIO_PORT->BSRR = MCP492x_SPIx_CS2_PIN;
    MCP492x_SPIx_CS3_GPIO_PORT->BSRR = MCP492x_SPIx_CS3_PIN;
    #endif
}


void MCP492x::setConfig(
    bool &output, 
    bool &inputBufferCtrl,
    bool &gain,
    bool &outPwrDownCtrl,
    float &Vref
    ){
        DACOutput = (uint16_t) output;
        DACInputBufferControl = (uint16_t) inputBufferCtrl;
        DACGain = (uint16_t) gain;
        DACSHDN = (uint16_t) outPwrDownCtrl;
        DACVref = Vref;
}

void MCP492x::setVoltage(float &setVoltage){
    DACRawBits = buildRawData(setVoltage);
    uint16_t sendBits[1] = {DACRawBits};
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    MCP492x_SPIx_CS3_GPIO_PORT->BSRR = ((uint32_t)MCP492x_SPIx_CS3_PIN) << 16;
    HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
    MCP492x_SPIx_CS3_GPIO_PORT->BSRR = MCP492x_SPIx_CS3_PIN;
    #else
    //MCP492x_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)MCP492x_SPIx_CS_PIN) << 16;
    HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
    //MCP492x_SPIx_CS_GPIO_PORT->BSRR = MCP492x_SPIx_CS_PIN;
    #endif
} 

void MCP492x::setVoltage(float &setVoltage, uint8_t DAC_CS){
    DACRawBits = buildRawData(setVoltage);
    uint16_t sendBits[1] = {DACRawBits};
    switch (DAC_CS)
    {
    case SS_DAC_CS:{
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      MCP492x_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)MCP492x_SPIx_CS_PIN) << 16;
      HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
      MCP492x_SPIx_CS_GPIO_PORT->BSRR = MCP492x_SPIx_CS_PIN;
      #endif
      break;
    }
    case Tenzo_ADC_CS:{
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      MCP492x_SPIx_CS2_GPIO_PORT->BSRR = ((uint32_t)MCP492x_SPIx_CS2_PIN) << 16;
      HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
      MCP492x_SPIx_CS2_GPIO_PORT->BSRR = MCP492x_SPIx_CS2_PIN;
      #endif
      break;
    }
    case COIL_DAC_CS:{
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN || CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      MCP492x_SPIx_CS3_GPIO_PORT->BSRR = ((uint32_t)MCP492x_SPIx_CS3_PIN) << 16;
      HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
      MCP492x_SPIx_CS3_GPIO_PORT->BSRR = MCP492x_SPIx_CS3_PIN;
      #endif
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
      HAL_SPI_Transmit(&MCP492x_SPI, (uint8_t *)sendBits, 1, 10);
      #endif
      break;
    }
    default:
      break;
    }
}

uint16_t MCP492x::calcDataBits(float &setVoltage){
    float rawValue = 0;
    switch (DACGain){
        case 0:
            rawValue = 2048;
        break;
        case 1:
            rawValue = 4096;
        break;
        default:
            rawValue = 4096;
        break;
    }
    rawValue = rawValue * setVoltage / DACVref;
    DACDataBits = round (rawValue);
    if (DACDataBits >= 0x1000){ //4096
        DACDataBits = 0xFFF;    //4095
    }
    return DACDataBits;
}

uint16_t MCP492x::buildRawData(float &setVoltage){
    DACDataBits = calcDataBits(setVoltage);
    uint16_t rawValue = 0;
    rawValue = (0x1 & DACOutput) << 15;
    DACRawBits = 0;
    DACRawBits |= rawValue;
    rawValue = DACInputBufferControl << 14;
    DACRawBits |= rawValue;
    rawValue = DACGain << 13;
    DACRawBits |= rawValue;
    rawValue = DACSHDN << 12;
    DACRawBits |= rawValue;
    DACRawBits |= DACDataBits;
    return DACRawBits;
}



