#include <MCP492xPWR.h>

#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   *MCP492x_PWR_SPI;
    //DMA_HandleTypeDef   MCP492x_PWR_DMA_SPI_RX;
    DMA_HandleTypeDef   *MCP492x_PWR_DMA_SPI_TX;
    DigitalOut* csPin;
static volatile uint32_t tMCP492x_PWRSPITransferState = MCP492x_PWR_DMA_SPI_TRANSFER_WAIT;

void MCP492x_PWR_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==MCP492x_PWR_SPIx){
    /* SPIx clock enable */
    MCP492x_PWR_SPIx_SCK_GPIO_CLK_ENABLE();
    MCP492x_PWR_SPIx_MOSI_GPIO_CLK_ENABLE();
    MCP492x_PWR_SPIx_CS_GPIO_CLK_ENABLE();
    MCP492x_PWR_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    MCP492x_PWR_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    GPIO_InitStruct.Pin =       MCP492x_PWR_SPIx_CS_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    //GPIO_InitStruct.Alternate = MCP492x_PWR_SPIx_CS_AF;
    HAL_GPIO_Init(MCP492x_PWR_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_SCK
    GPIO_InitStruct.Pin =       MCP492x_PWR_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_PWR_SPIx_SCK_AF;
    HAL_GPIO_Init(MCP492x_PWR_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MOSI
    GPIO_InitStruct.Pin =       MCP492x_PWR_SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP; //old NO PULLUP
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = MCP492x_PWR_SPIx_MOSI_AF;
    HAL_GPIO_Init(MCP492x_PWR_SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_TX Init */
    
    MCP492x_PWR_DMA_SPI_TX->Instance =                 MCP492x_PWR_SPIx_TX_DMA_STREAM;
    #if BOARD_INDEX == 2
    MCP492x_PWR_DMA_SPI_TX->Init.Request =             MCP492x_PWR_SPIx_TX_DMA_REQUEST;
    #endif
    MCP492x_PWR_DMA_SPI_TX->Init.Direction =           DMA_MEMORY_TO_PERIPH;
    MCP492x_PWR_DMA_SPI_TX->Init.PeriphInc =           DMA_PINC_DISABLE;
    MCP492x_PWR_DMA_SPI_TX->Init.MemInc =              DMA_MINC_ENABLE;
    MCP492x_PWR_DMA_SPI_TX->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    MCP492x_PWR_DMA_SPI_TX->Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    MCP492x_PWR_DMA_SPI_TX->Init.Mode =                DMA_NORMAL;
    MCP492x_PWR_DMA_SPI_TX->Init.Priority =            DMA_PRIORITY_MEDIUM;
    MCP492x_PWR_DMA_SPI_TX->Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    MCP492x_PWR_DMA_SPI_TX->Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    MCP492x_PWR_DMA_SPI_TX->Init.MemBurst =            DMA_MBURST_INC16;
    MCP492x_PWR_DMA_SPI_TX->Init.PeriphBurst =         DMA_PBURST_INC4;
    if (HAL_DMA_Init(MCP492x_PWR_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, *MCP492x_PWR_DMA_SPI_TX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( MCP492x_PWR_SPIx_DMA_TX_IRQn, 
                          MCP492x_PWR_SPIx_DMA_TX_IRQn_PreemptPriority, 
                          MCP492x_PWR_SPIx_DMA_TX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP492x_PWR_SPIx_DMA_TX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( MCP492x_PWR_SPIx_IRQn, 
                          MCP492x_PWR_SPIx_IRQn_PreemptPriority, 
                          MCP492x_PWR_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP492x_PWR_SPIx_IRQn);
  }
}

void MCP492x_PWR_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==MCP492x_PWR_SPIx)
  {
    /* Peripheral clock disable */
    MCP492x_PWR_SPIx_CLK_DISABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MOSI
    */
    HAL_GPIO_DeInit(MCP492x_PWR_SPIx_SCK_GPIO_PORT, MCP492x_PWR_SPIx_SCK_PIN);
    HAL_GPIO_DeInit(MCP492x_PWR_SPIx_CS_GPIO_PORT, MCP492x_PWR_SPIx_CS_PIN);
    HAL_GPIO_DeInit(MCP492x_PWR_SPIx_MOSI_GPIO_PORT, MCP492x_PWR_SPIx_MOSI_PIN);
    /* SPIx DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmatx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(MCP492x_PWR_SPIx_IRQn);
  }
}

void MCP492x_PWR_HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  tMCP492x_PWRSPITransferState = MCP492x_PWR_DMA_SPI_TRANSFER_COMPLETE;
  csPin->write(1);
  //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = MCP492x_PWR_SPIx_CS_PIN;
}

void MCP492x_PWR_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  tMCP492x_PWRSPITransferState = MCP492x_PWR_DMA_SPI_TRANSFER_ERROR;
  csPin->write(1);
  //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = MCP492x_PWR_SPIx_CS_PIN;
}
#ifdef __cplusplus
 }
#endif
void MCP492x_PWR::sharedConstructor(int spiBaudRatePrescaler){
    #if BOARD_INDEX == 2
    MCP492x_PWR_SPI->Instance = MCP492x_PWR_SPIx;
    MCP492x_PWR_SPI->Init.Mode = SPI_MODE_MASTER;
    MCP492x_PWR_SPI->Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
    MCP492x_PWR_SPI->Init.DataSize = SPI_DATASIZE_16BIT;
    MCP492x_PWR_SPI->Init.CLKPolarity = SPI_POLARITY_HIGH;
    MCP492x_PWR_SPI->Init.CLKPhase = SPI_PHASE_2EDGE;
    MCP492x_PWR_SPI->Init.NSS = SPI_NSS_SOFT;
    MCP492x_PWR_SPI->Init.BaudRatePrescaler = spiBaudRatePrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    MCP492x_PWR_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
    MCP492x_PWR_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
    MCP492x_PWR_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    MCP492x_PWR_SPI->Init.CRCPolynomial = 0x0;
    MCP492x_PWR_SPI->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    MCP492x_PWR_SPI->Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    MCP492x_PWR_SPI->Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    MCP492x_PWR_SPI->Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP492x_PWR_SPI->Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP492x_PWR_SPI->Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    MCP492x_PWR_SPI->Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    MCP492x_PWR_SPI->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    MCP492x_PWR_SPI->Init.IOSwap = SPI_IO_SWAP_DISABLE;
    #endif
    #if BOARD_INDEX == 3
    MCP492x_PWR_SPI->Instance = MCP492x_PWR_SPIx;
    MCP492x_PWR_SPI->Init.Mode = SPI_MODE_MASTER;
    MCP492x_PWR_SPI->Init.Direction = SPI_DIRECTION_2LINES;
    MCP492x_PWR_SPI->Init.DataSize = SPI_DATASIZE_16BIT;
    MCP492x_PWR_SPI->Init.CLKPolarity = SPI_POLARITY_HIGH;
    MCP492x_PWR_SPI->Init.CLKPhase = SPI_PHASE_2EDGE;
    MCP492x_PWR_SPI->Init.NSS = SPI_NSS_SOFT;
    MCP492x_PWR_SPI->Init.BaudRatePrescaler = spiBaudRatePrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    MCP492x_PWR_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
    MCP492x_PWR_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
    MCP492x_PWR_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    MCP492x_PWR_SPI->Init.CRCPolynomial = 0x0;
    MCP492x_PWR_SPI->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    #endif
}

MCP492x_PWR::MCP492x_PWR(int spiBaudRatePrescaler){
    this->sharedConstructor(spiBaudRatePrescaler);
}
MCP492x_PWR::MCP492x_PWR(int spiBaudRatePrescaler, 
            bool output, 
            bool inputBufferCtrl,
            bool gain,
            bool outPwrDownCtrl,
            float Vref,
            DMA_HandleTypeDef *GLOBAL_SPI_DMA_IRQ_HANDLER,
            SPI_HandleTypeDef *GLOBAL_SPI_IRQ_HANDLER){
    MCP492x_PWR_SPI = GLOBAL_SPI_IRQ_HANDLER;
    MCP492x_PWR_DMA_SPI_TX = GLOBAL_SPI_DMA_IRQ_HANDLER;
    this->sharedConstructor(spiBaudRatePrescaler);
    this->setConfig(output, inputBufferCtrl, gain, outPwrDownCtrl, Vref);
    csPin = new DigitalOut(PB_10, 1);
    //SPI_DMA_IRQ_HANDLER = GLOBAL_SPI_DMA_IRQ_HANDLER;
    //SPI_IRQ_HANDLER = GLOBAL_SPI_IRQ_HANDLER;
}

int MCP492x_PWR::init(){
  //*SPI_DMA_IRQ_HANDLER = MCP492x_PWR_DMA_SPI_TX;
  //*SPI_IRQ_HANDLER = MCP492x_PWR_SPI;
  HAL_SPI_RegisterCallback(MCP492x_PWR_SPI, HAL_SPI_MSPINIT_CB_ID, MCP492x_PWR_HAL_SPI_MspInit);
  HAL_SPI_RegisterCallback(MCP492x_PWR_SPI, HAL_SPI_MSPDEINIT_CB_ID,MCP492x_PWR_HAL_SPI_MspDeInit);
  uint32_t errorState = HAL_SPI_Init(MCP492x_PWR_SPI);
  if (errorState != HAL_OK)
  {   
      printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
      //return errorState;
  }
  HAL_SPI_RegisterCallback(MCP492x_PWR_SPI, HAL_SPI_TX_COMPLETE_CB_ID, MCP492x_PWR_HAL_SPI_TxCpltCallback);
  HAL_SPI_RegisterCallback(MCP492x_PWR_SPI, HAL_SPI_ERROR_CB_ID,MCP492x_PWR_HAL_SPI_ErrorCallback);
  //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = MCP492x_PWR_SPIx_CS_PIN;
  return HAL_OK;
}

int MCP492x_PWR::deInit(){
  HAL_SPI_UnRegisterCallback(MCP492x_PWR_SPI, HAL_SPI_TX_COMPLETE_CB_ID);
  HAL_SPI_UnRegisterCallback(MCP492x_PWR_SPI, HAL_SPI_ERROR_CB_ID);
  uint32_t errorState = 0;//HAL_SPI_DeInit(MCP492x_PWR_SPI);
  HAL_SPI_UnRegisterCallback(MCP492x_PWR_SPI, HAL_SPI_MSPINIT_CB_ID);
  HAL_SPI_UnRegisterCallback(MCP492x_PWR_SPI, HAL_SPI_MSPDEINIT_CB_ID);
  return errorState;
}

void MCP492x_PWR::setConfig(
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

void MCP492x_PWR::setVoltageBlocking(float &setVoltage){
    DACRawBits = buildRawData(setVoltage);
    uint16_t sendBits[1] = {DACRawBits};
    //MCP492x_PWRSPI.lock();
    //MCP492x_PWRSPI.write(DACRawBits);
    //MCP492x_PWRSPI.unlock();
    //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)MCP492x_PWR_SPIx_CS_PIN) << 16;
    csPin->write(0);
    HAL_SPI_Transmit(MCP492x_PWR_SPI, (uint8_t *)sendBits, 1, 10);
    //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = MCP492x_PWR_SPIx_CS_PIN;
    csPin->write(1);
} 
void MCP492x_PWR::startSettingVoltage(float &setVoltage){
    DACRawBits = buildRawData(setVoltage);
    uint16_t sendBits[1] = {DACRawBits};
    //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)MCP492x_PWR_SPIx_CS_PIN) << 16;
    csPin->write(0);
    HAL_SPI_Transmit_DMA(MCP492x_PWR_SPI, (uint8_t *)sendBits, 1);
}

uint32_t MCP492x_PWR::getTransferStatus(){
  uint32_t status = tMCP492x_PWRSPITransferState;
  return status;
}

void MCP492x_PWR::clearTransferStatus(){
  tMCP492x_PWRSPITransferState = MCP492x_PWR_DMA_SPI_TRANSFER_WAIT;
  csPin->write(1);
  //MCP492x_PWR_SPIx_CS_GPIO_PORT->BSRR = MCP492x_PWR_SPIx_CS_PIN;
}

uint16_t MCP492x_PWR::calcDataBits(float &setVoltage){
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

uint16_t MCP492x_PWR::buildRawData(float &setVoltage){
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



