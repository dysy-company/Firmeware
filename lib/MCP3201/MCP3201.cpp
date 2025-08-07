#include <MCP3201.h>

#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   MCP3201_SPI;
DMA_HandleTypeDef   MCP3201_DMA_SPI_RX;
DMA_HandleTypeDef   MCP3201_DMA_SPI_TX;
static volatile uint32_t rMCP3201SPITransferState = MCP3201_DMA_SPI_TRANSFER_WAIT;
uint16_t _CSpin;
GPIO_TypeDef *_CSport;

void MCP3201_SPIx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&MCP3201_DMA_SPI_RX);
}

void MCP3201_SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&MCP3201_SPI);
}

void MCP3201_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==MCP3201_SPIx){
    /* SPIx clock enable */
    MCP3201_SPIx_SCK_GPIO_CLK_ENABLE();
    MCP3201_SPIx_MISO_GPIO_CLK_ENABLE();
    //MCP3201_SPIx_CS_GPIO_CLK_ENABLE();
    MCP3201_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    MCP3201_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    //GPIO_InitStruct.Pin =       MCP3201_SPIx_CS_PIN;
    //GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    //GPIO_InitStruct.Pull =      GPIO_PULLUP;
    //GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    //GPIO_InitStruct.Alternate = MCP3201_SPIx_CS_AF;
    //HAL_GPIO_Init(MCP3201_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_SCK
    GPIO_InitStruct.Pin =       MCP3201_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = MCP3201_SPIx_SCK_AF;
    HAL_GPIO_Init(MCP3201_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MISO
    GPIO_InitStruct.Pin =       MCP3201_SPIx_MISO_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = MCP3201_SPIx_MISO_AF;
    HAL_GPIO_Init(MCP3201_SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_RX Init */
    MCP3201_DMA_SPI_RX.Instance =                 MCP3201_SPIx_RX_DMA_STREAM;
    MCP3201_DMA_SPI_RX.Init.Request =             MCP3201_SPIx_RX_DMA_REQUEST;
    MCP3201_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    MCP3201_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    MCP3201_DMA_SPI_RX.Init.MemInc =              DMA_MINC_DISABLE;
    MCP3201_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_MDATAALIGN_HALFWORD;
    MCP3201_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    MCP3201_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    MCP3201_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_LOW;
    MCP3201_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    MCP3201_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    MCP3201_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    MCP3201_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC4;
    if (HAL_DMA_Init(&MCP3201_DMA_SPI_RX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_RX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmarx, MCP3201_DMA_SPI_RX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( MCP3201_SPIx_DMA_RX_IRQn, 
                          MCP3201_SPIx_DMA_RX_IRQn_PreemptPriority, 
                          MCP3201_SPIx_DMA_RX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP3201_SPIx_DMA_RX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( MCP3201_SPIx_IRQn, 
                          MCP3201_SPIx_IRQn_PreemptPriority, 
                          MCP3201_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(MCP3201_SPIx_IRQn);
  }
}

void MCP3201_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==MCP3201_SPIx)
  {
    /* Peripheral clock disable */
    MCP3201_SPIx_CLK_DISABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MISO
    */
    HAL_GPIO_DeInit(MCP3201_SPIx_SCK_GPIO_PORT, MCP3201_SPIx_SCK_PIN);
    //HAL_GPIO_DeInit(MCP3201_SPIx_CS_GPIO_PORT, MCP3201_SPIx_CS_PIN);
    HAL_GPIO_DeInit(MCP3201_SPIx_MISO_GPIO_PORT, MCP3201_SPIx_MISO_PIN);
    /* SPIx DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmarx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(MCP3201_SPIx_IRQn);
  }
}

void MCP3201_HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  //_CS->write(1);
  _CSport->BSRR = _CSpin;
  rMCP3201SPITransferState = MCP3201_DMA_SPI_TRANSFER_COMPLETE;
}

void MCP3201_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  _CSport->BSRR = _CSpin;
  rMCP3201SPITransferState = MCP3201_DMA_SPI_TRANSFER_ERROR;
}
#ifdef __cplusplus
 }
#endif

void MCP3201::fillSettings(unsigned long spiPrescaler){
    MCP3201_SPI.Instance = MCP3201_SPIx;
    MCP3201_SPI.Init.Mode = SPI_MODE_MASTER;
    MCP3201_SPI.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
    MCP3201_SPI.Init.DataSize = SPI_DATASIZE_15BIT;
    MCP3201_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    MCP3201_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    MCP3201_SPI.Init.NSS = SPI_NSS_SOFT;
    MCP3201_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_8;~1,25Mhz
    MCP3201_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    MCP3201_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    MCP3201_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    MCP3201_SPI.Init.CRCPolynomial = 0x0;
    MCP3201_SPI.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    MCP3201_SPI.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    MCP3201_SPI.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    MCP3201_SPI.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP3201_SPI.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    MCP3201_SPI.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    MCP3201_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    MCP3201_SPI.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    MCP3201_SPI.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    MCP3201_SPI.Init.IOSwap = SPI_IO_SWAP_DISABLE;
}

//mode 0,3, freq in prescaler: 8 is ~1,25MHz TODO: add parameters for overload msp init
MCP3201::MCP3201(unsigned long spiPrescaler){
    this->fillSettings(spiPrescaler);
}
MCP3201::MCP3201(unsigned long spiPrescaler, float Vref){
    this->fillSettings(spiPrescaler);
    this->setVref(Vref);
}

void MCP3201::setCSPin(uint16_t pin, GPIO_TypeDef *port){
    _CSpin = pin;
    _CSport = port;
}

int MCP3201::init(void){
    HAL_SPI_RegisterCallback(&MCP3201_SPI, HAL_SPI_MSPINIT_CB_ID, MCP3201_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&MCP3201_SPI, HAL_SPI_MSPDEINIT_CB_ID,MCP3201_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&MCP3201_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_SPI_RegisterCallback(&MCP3201_SPI, HAL_SPI_RX_COMPLETE_CB_ID, MCP3201_HAL_SPI_RxCpltCallback);
    HAL_SPI_RegisterCallback(&MCP3201_SPI, HAL_SPI_ERROR_CB_ID,MCP3201_HAL_SPI_ErrorCallback);
    return HAL_OK;
}

void MCP3201::setVref(float &Vref){
        ADCVref = Vref;
        ADCLSBWeight = ADCVref / 4096;
}

float MCP3201::getVoltageBlocking(void){
    ADCDataBits = this->getCodeBlocking();
    return calcVoltage(ADCDataBits);
}

uint16_t MCP3201::getCodeBlocking(void){
    //_CS->write(0);
    _CSport->BSRR = ((uint32_t)_CSpin) << 16;
    HAL_SPI_Receive(&MCP3201_SPI, (uint8_t *)ADCRawBits, 1, 100);
    _CSport->BSRR = _CSpin;
    //_CS->write(1);
    //wait_us(12);
    //while (rMCP3201SPITransferState == MCP3201_DMA_SPI_TRANSFER_WAIT){}
    //if(rMCP3201SPITransferState == MCP3201_DMA_SPI_TRANSFER_COMPLETE){
        ADCRawBits[0] &= 0xFFF;   
        ADCDataBits = ADCRawBits[0];
    //    rMCP3201SPITransferState = MCP3201_DMA_SPI_TRANSFER_WAIT;
    //}
    return ADCDataBits;
}

uint32_t MCP3201::startGettingCode(void){
    //_CS->write(0);
    //GPIOx->BSRR = (uint32_t)GPIO_Pin << GPIO_NUMBER;
    //_CS->gpio->BSRR = (uint32_t)_CS->pin << GPIO_NUMBER;
    _CSport->BSRR = ((uint32_t)_CSpin) << 16;
    uint32_t errorState = HAL_SPI_Receive_DMA(&MCP3201_SPI, (uint8_t *)ADCRawBits, 1);
    return errorState;
}

uint32_t MCP3201::getTransferStatus(void){
  uint32_t status = rMCP3201SPITransferState;
  return status;
}
void MCP3201::clearTransferStatus(void){
  rMCP3201SPITransferState = MCP3201_DMA_SPI_TRANSFER_WAIT;
}
uint16_t MCP3201::getLastCode(void){
  ADCDataBits = 0xFFF & ADCRawBits[0];
  return ADCDataBits;
}
float MCP3201::getLastVoltage(void){
  ADCDataBits = 0xFFF & ADCRawBits[0];
  return ADCLSBWeight * ADCDataBits;
}
float MCP3201::calcVoltage(uint16_t &DataBits){
  return ADCLSBWeight * DataBits;
}

uint16_t MCP3201::setNullPoint(){
    //this->clearTransferStatus();
    ADCNullPointDataBits = this->getCodeBlocking();
    return ADCNullPointDataBits;
}




