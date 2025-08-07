#include <AD56x1.h>

#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   *AD56x1_SPI;
//DMA_HandleTypeDef  AD56x1_DMA_SPI_RX;
DMA_HandleTypeDef   *AD56x1_DMA_SPI_TX;

static volatile uint32_t tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_WAIT;

void AD56x1_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==AD56x1_SPIx){
    /* SPIx clock enable */
    AD56x1_SPIx_SCK_GPIO_CLK_ENABLE();
    AD56x1_SPIx_MOSI_GPIO_CLK_ENABLE();
    AD56x1_SPIx_CS_GPIO_CLK_ENABLE();
    AD56x1_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    AD56x1_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    GPIO_InitStruct.Pin =       AD56x1_SPIx_CS_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    //GPIO_InitStruct.Alternate = AD56x1_SPIx_CS_AF;
    HAL_GPIO_Init(AD56x1_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_SCK
    GPIO_InitStruct.Pin =       AD56x1_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = AD56x1_SPIx_SCK_AF;
    HAL_GPIO_Init(AD56x1_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MOSI
    GPIO_InitStruct.Pin =       AD56x1_SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP; //old NO PULLUP
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = AD56x1_SPIx_MOSI_AF;
    HAL_GPIO_Init(AD56x1_SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_TX Init */
    AD56x1_DMA_SPI_TX->Instance =                 AD56x1_SPIx_TX_DMA_STREAM;
    #if BOARD_INDEX == 2
    AD56x1_DMA_SPI_TX->Init.Request =             AD56x1_SPIx_TX_DMA_REQUEST;
    #endif
    AD56x1_DMA_SPI_TX->Init.Direction =           DMA_MEMORY_TO_PERIPH;
    AD56x1_DMA_SPI_TX->Init.PeriphInc =           DMA_PINC_DISABLE;
    AD56x1_DMA_SPI_TX->Init.MemInc =              DMA_MINC_ENABLE;
    AD56x1_DMA_SPI_TX->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    AD56x1_DMA_SPI_TX->Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    AD56x1_DMA_SPI_TX->Init.Mode =                DMA_NORMAL;
    AD56x1_DMA_SPI_TX->Init.Priority =            DMA_PRIORITY_MEDIUM;
    AD56x1_DMA_SPI_TX->Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    AD56x1_DMA_SPI_TX->Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    AD56x1_DMA_SPI_TX->Init.MemBurst =            DMA_MBURST_INC16;
    AD56x1_DMA_SPI_TX->Init.PeriphBurst =         DMA_PBURST_INC4;
    if (HAL_DMA_Init(AD56x1_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, *AD56x1_DMA_SPI_TX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( AD56x1_SPIx_DMA_TX_IRQn, 
                          AD56x1_SPIx_DMA_TX_IRQn_PreemptPriority, 
                          AD56x1_SPIx_DMA_TX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(AD56x1_SPIx_DMA_TX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( AD56x1_SPIx_IRQn, 
                          AD56x1_SPIx_IRQn_PreemptPriority, 
                          AD56x1_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(AD56x1_SPIx_IRQn);
  }
}

void AD56x1_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==AD56x1_SPIx)
  {
    /* Peripheral clock disable */
    //AD56x1_SPIx_CLK_DISABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MOSI
    */
    AD56x1_SPIx_CLK_DISABLE();
    HAL_GPIO_DeInit(AD56x1_SPIx_SCK_GPIO_PORT, AD56x1_SPIx_SCK_PIN);
    HAL_GPIO_DeInit(AD56x1_SPIx_CS_GPIO_PORT, AD56x1_SPIx_CS_PIN);
    HAL_GPIO_DeInit(AD56x1_SPIx_MOSI_GPIO_PORT, AD56x1_SPIx_MOSI_PIN);
    /* SPIx DMA DeInit */
    //HAL_GPIO_DeInit(AD56x1_SPIx_SCK_GPIO_PORT, AD56x1_SPIx_SCK_PIN);
    //HAL_GPIO_DeInit(AD56x1_SPIx_MOSI_GPIO_PORT, AD56x1_SPIx_MOSI_PIN);
    //HAL_GPIO_DeInit(AD56x1_SPIx_CS_GPIO_PORT, AD56x1_SPIx_CS_PIN);
    HAL_DMA_DeInit(spiHandle->hdmatx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(AD56x1_SPIx_IRQn);
  }
}

void AD56x1_HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_COMPLETE;
  AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
}

void AD56x1_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_ERROR;
  AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
}
#ifdef __cplusplus
 }
#endif

void AD56x1::sharedConstructor(unsigned long spiPrescaler, AD56x1Type type){
    #if BOARD_INDEX == 2
    _type = type;
    AD56x1_SPI->Instance = AD56x1_SPIx;
    AD56x1_SPI->Init.Mode = SPI_MODE_MASTER;
    AD56x1_SPI->Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
    AD56x1_SPI->Init.DataSize = SPI_DATASIZE_16BIT;
    AD56x1_SPI->Init.CLKPolarity = SPI_POLARITY_HIGH;
    AD56x1_SPI->Init.CLKPhase = SPI_PHASE_1EDGE;
    AD56x1_SPI->Init.NSS = SPI_NSS_SOFT;
    AD56x1_SPI->Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    AD56x1_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
    AD56x1_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
    AD56x1_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    AD56x1_SPI->Init.CRCPolynomial = 0x0;
    AD56x1_SPI->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    AD56x1_SPI->Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    AD56x1_SPI->Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    AD56x1_SPI->Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    AD56x1_SPI->Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    AD56x1_SPI->Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    AD56x1_SPI->Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    AD56x1_SPI->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    AD56x1_SPI->Init.IOSwap = SPI_IO_SWAP_DISABLE;
    
    switch (_type)
    {
    case AD5601:
        this->_mask = 0xFF;
        this->_shift = 6;
        break;
    case AD5611:
        this->_mask = 0x03FF;
        this->_shift = 4;
        break;
    case AD5621:
        this->_mask = 0x0FFF;
        this->_shift = 2;
        break;
    default:
        this->_mask = 0x0FFF;
        this->_shift = 2;
        break;
    }
    #endif
    #if BOARD_INDEX == 3
    _type = type;
    AD56x1_SPI->Instance = AD56x1_SPIx;
    AD56x1_SPI->Init.Mode = SPI_MODE_MASTER;
    AD56x1_SPI->Init.Direction = SPI_DIRECTION_2LINES;
    AD56x1_SPI->Init.DataSize = SPI_DATASIZE_16BIT;
    AD56x1_SPI->Init.CLKPolarity = SPI_POLARITY_HIGH;
    AD56x1_SPI->Init.CLKPhase = SPI_PHASE_1EDGE;
    AD56x1_SPI->Init.NSS = SPI_NSS_SOFT;
    AD56x1_SPI->Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    AD56x1_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
    AD56x1_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
    AD56x1_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    AD56x1_SPI->Init.CRCPolynomial = 0x0;
    AD56x1_SPI->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    
    switch (_type)
    {
    case AD5601:
        this->_mask = 0xFF;
        this->_shift = 6;
        break;
    case AD5611:
        this->_mask = 0x03FF;
        this->_shift = 4;
        break;
    case AD5621:
        this->_mask = 0x0FFF;
        this->_shift = 2;
        break;
    default:
        this->_mask = 0x0FFF;
        this->_shift = 2;
        break;
    }
    #endif
}

AD56x1::AD56x1(unsigned long spiPrescaler, AD56x1Type type){
    sharedConstructor(spiPrescaler, type);
}

AD56x1::AD56x1(unsigned long spiPrescaler, AD56x1Type type, bool isInit){
    sharedConstructor(spiPrescaler, type);
    if (isInit){
        this->init();
    }
}

AD56x1::AD56x1(unsigned long spiPrescaler, AD56x1Type type, AD56x1PowerDownMode powerDownMode, float Vdd, bool isInit, DMA_HandleTypeDef *GLOBAL_SPI_DMA_IRQ_HANDLER,
            SPI_HandleTypeDef *GLOBAL_SPI_IRQ_HANDLER){
    AD56x1_DMA_SPI_TX = GLOBAL_SPI_DMA_IRQ_HANDLER;
    AD56x1_SPI = GLOBAL_SPI_IRQ_HANDLER;
    sharedConstructor(spiPrescaler, type);
    if (isInit){
        this->init();
    }
    this->setConfig(powerDownMode, Vdd);
    
}

int AD56x1::init(void){
    //*SPI_DMA_IRQ_HANDLER = AD56x1_DMA_SPI_TX;
    //*SPI_IRQ_HANDLER = AD56x1_SPI;
    HAL_SPI_RegisterCallback(AD56x1_SPI, HAL_SPI_MSPINIT_CB_ID, AD56x1_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(AD56x1_SPI, HAL_SPI_MSPDEINIT_CB_ID,AD56x1_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(AD56x1_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_SPI_RegisterCallback(AD56x1_SPI, HAL_SPI_TX_COMPLETE_CB_ID, AD56x1_HAL_SPI_TxCpltCallback);
    HAL_SPI_RegisterCallback(AD56x1_SPI, HAL_SPI_ERROR_CB_ID,AD56x1_HAL_SPI_ErrorCallback);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
    return HAL_OK;
}

int AD56x1::deInit(void){
    
    HAL_SPI_UnRegisterCallback(AD56x1_SPI, HAL_SPI_TX_COMPLETE_CB_ID);
    HAL_SPI_UnRegisterCallback(AD56x1_SPI, HAL_SPI_ERROR_CB_ID);
    uint32_t errorState = 0;//HAL_SPI_DeInit(AD56x1_SPI);
    HAL_SPI_UnRegisterCallback(AD56x1_SPI, HAL_SPI_MSPINIT_CB_ID);
    HAL_SPI_UnRegisterCallback(AD56x1_SPI, HAL_SPI_MSPDEINIT_CB_ID);
    return errorState;
}

void AD56x1::setConfig(AD56x1PowerDownMode powerDownMode, float &Vdd){
    _powerDownMode = powerDownMode;
    _Vdd = Vdd;
    _lsbWeight = Vdd / (this->_mask + 1);
    switch (_powerDownMode)
    {
    case NORMAL_OPERATION:
        this->_pwrDwnBits = 0x0000;
        break;
    case RES_1_KOHM_GND:
        this->_pwrDwnBits = 0x4000;
        break;
    case RES_100_KOHM_GND:
        this->_pwrDwnBits = 0x8000;
        break;
    case THREE_STATE:
        this->_pwrDwnBits = 0xC000;
        break;
    default:
        break;
    }
}

uint32_t AD56x1::setVoltageBlocking(float &setVoltage){
    buildRawData(setVoltage); 
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)AD56x1_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Transmit(AD56x1_SPI, (uint8_t *)_DACRawBits, 1, 100);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
    //wait_us(12);
    //while (tAD56x1SPITransferState == AD56x1_DMA_SPI_TRANSFER_WAIT){}
    //if(tAD56x1SPITransferState == AD56x1_DMA_SPI_TRANSFER_COMPLETE){
        //_DACRawBits[0] &= 0xFFFF;   
        //_DACDataBits = DACRawBits[0];
    //    tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_WAIT;
    //}
    return errorState;
}

uint32_t AD56x1::setCodeBlocking(uint16_t &code){
    buildRawData(code);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)AD56x1_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Transmit(AD56x1_SPI, (uint8_t *)_DACRawBits, 1, 100);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
    //wait_us(12);
    //while (tAD56x1SPITransferState == AD56x1_DMA_SPI_TRANSFER_WAIT){}
    //if(tAD56x1SPITransferState == AD56x1_DMA_SPI_TRANSFER_COMPLETE){
        //_DACRawBits[0] &= 0xFFFF;   
        //_DACDataBits = DACRawBits[0];
    //    tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_WAIT;
    //}
    return errorState;
}

uint16_t AD56x1::calcCode(float &voltage){
    float dummy = voltage / _lsbWeight;
    uint16_t code = round(dummy) - 1;
    return code;
}
float AD56x1::calcVoltage(uint16_t &code){
    return code*_lsbWeight;
}

uint32_t AD56x1::startSettingVoltage(float &setVoltage){
    buildRawData(setVoltage);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)AD56x1_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Transmit_DMA(AD56x1_SPI, (uint8_t *)_DACRawBits, 1);
    return errorState;
}

uint32_t AD56x1::startSettingCode(uint16_t &code){
    buildRawData(code);
    AD56x1_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)AD56x1_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Transmit_DMA(AD56x1_SPI, (uint8_t *)_DACRawBits, 1);
    return errorState;
}

uint32_t AD56x1::getTransferStatus(void){
  uint32_t status = tAD56x1SPITransferState;
  return status;
}

void AD56x1::clearTransferStatus(void){
  tAD56x1SPITransferState = AD56x1_DMA_SPI_TRANSFER_WAIT;
  AD56x1_SPIx_CS_GPIO_PORT->BSRR = AD56x1_SPIx_CS_PIN;
}

uint16_t AD56x1::getLastCode(void){
  return _DACDataBits;
}

float AD56x1::getLastVoltage(void){
    return calcVoltage(_DACDataBits);
}

void AD56x1::buildRawData(float &value){
    _DACDataBits = _mask & calcCode(value);
    //printf("shift:%d\n\r", _shift);
    //printf("pwrdwn:%d\n\r", _pwrDwnBits);
    _DACRawBits[0] = (_DACDataBits << _shift) | _pwrDwnBits;
}
void AD56x1::buildRawData(uint16_t &value){
    _DACDataBits = _mask & value;
    _DACRawBits[0] = (_DACDataBits << _shift) | _pwrDwnBits;
}



