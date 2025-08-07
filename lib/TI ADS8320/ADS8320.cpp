#include <ADS8320.h>

#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   ADS8320_SPI;
DMA_HandleTypeDef   ADS8320_DMA_SPI_RX;
DMA_HandleTypeDef   ADS8320_DMA_SPI_TX;
static volatile uint32_t rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_WAIT;

void ADS8320_SPIx_DMA_RX_IRQHandler(void)
{
  #if BOARD_INDEX == 2
  HAL_DMA_IRQHandler(&ADS8320_DMA_SPI_RX);
  #endif
  #if BOARD_INDEX == 3
  HAL_DMA_IRQHandler(ADS8320_SPI.hdmatx);
  HAL_DMA_IRQHandler(ADS8320_SPI.hdmarx);
  #endif
}

void ADS8320_SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&ADS8320_SPI);
}

void ADS8320_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==ADS8320_SPIx){
    /* SPIx clock enable */
    ADS8320_SPIx_SCK_GPIO_CLK_ENABLE();
    ADS8320_SPIx_MISO_GPIO_CLK_ENABLE();
    ADS8320_SPIx_CS_GPIO_CLK_ENABLE();
    ADS8320_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    ADS8320_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    GPIO_InitStruct.Pin =       ADS8320_SPIx_CS_PIN;
    #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    #else
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    #endif
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS8320_SPIx_CS_AF;
    HAL_GPIO_Init(ADS8320_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_SCK
    GPIO_InitStruct.Pin =       ADS8320_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS8320_SPIx_SCK_AF;
    HAL_GPIO_Init(ADS8320_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MISO
    GPIO_InitStruct.Pin =       ADS8320_SPIx_MISO_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS8320_SPIx_MISO_AF;
    HAL_GPIO_Init(ADS8320_SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_RX Init */
    #if BOARD_INDEX == 2
    ADS8320_DMA_SPI_RX.Instance =                 ADS8320_SPIx_RX_DMA_STREAM;
    ADS8320_DMA_SPI_RX.Init.Request =             ADS8320_SPIx_RX_DMA_REQUEST;
    ADS8320_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    ADS8320_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS8320_DMA_SPI_RX.Init.MemInc =              DMA_MINC_DISABLE;
    ADS8320_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    ADS8320_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_WORD;
    ADS8320_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    ADS8320_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_LOW;
    ADS8320_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS8320_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS8320_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS8320_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC4;
    #endif
    #if BOARD_INDEX == 3
    ADS8320_DMA_SPI_RX.Instance =                 ADS8320_SPIx_RX_DMA_STREAM;
    ADS8320_DMA_SPI_RX.Init.Channel =             DMA_CHANNEL_3;
    ADS8320_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    ADS8320_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS8320_DMA_SPI_RX.Init.MemInc =              DMA_MINC_ENABLE;
    ADS8320_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    ADS8320_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    ADS8320_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    ADS8320_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_HIGH;
    ADS8320_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS8320_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS8320_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS8320_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC16;
    #endif
    if (HAL_DMA_Init(&ADS8320_DMA_SPI_RX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_RX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmarx, ADS8320_DMA_SPI_RX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( ADS8320_SPIx_DMA_RX_IRQn, 
                          ADS8320_SPIx_DMA_RX_IRQn_PreemptPriority, 
                          ADS8320_SPIx_DMA_RX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(ADS8320_SPIx_DMA_RX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( ADS8320_SPIx_IRQn, 
                          ADS8320_SPIx_IRQn_PreemptPriority, 
                          ADS8320_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(ADS8320_SPIx_IRQn);
    #if BOARD_INDEX == 3
    ADS8320_DMA_SPI_TX.Instance =                 DMA2_Stream3;
    ADS8320_DMA_SPI_TX.Init.Channel =             DMA_CHANNEL_3;
    ADS8320_DMA_SPI_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    ADS8320_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS8320_DMA_SPI_TX.Init.MemInc =              DMA_MINC_ENABLE;
    ADS8320_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    ADS8320_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    ADS8320_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    ADS8320_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_HIGH;
    ADS8320_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS8320_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS8320_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS8320_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC16;
    if (HAL_DMA_Init(&ADS8320_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, ADS8320_DMA_SPI_TX);
    #endif
  }
}

void ADS8320_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==ADS8320_SPIx)
  {
    /* Peripheral clock disable */
    ADS8320_SPIx_CLK_ENABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MISO
    */
    HAL_GPIO_DeInit(ADS8320_SPIx_SCK_GPIO_PORT, ADS8320_SPIx_SCK_PIN);
    HAL_GPIO_DeInit(ADS8320_SPIx_CS_GPIO_PORT, ADS8320_SPIx_CS_PIN);
    HAL_GPIO_DeInit(ADS8320_SPIx_MISO_GPIO_PORT, ADS8320_SPIx_MISO_PIN);
    /* SPIx DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmarx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADS8320_SPIx_IRQn);
  }
}

void ADS8320_HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_COMPLETE;
  #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
  #else
  ADS8320_SPIx_CS_GPIO_PORT->BSRR = ADS8320_SPIx_CS_PIN;
  #endif
}

void ADS8320_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_ERROR;
}
#ifdef __cplusplus
 }
#endif

//mode 3, freq in prescaler: 64 is ~2MHz TODO: add parameters for overload msp init
ADS8320::ADS8320(unsigned long spiPrescaler, unsigned long numberOfCalibrationPoints){
  #if BOARD_INDEX == 2
    ADS8320_SPI.Instance = ADS8320_SPIx;
    ADS8320_SPI.Init.Mode = SPI_MODE_MASTER;
    ADS8320_SPI.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
    ADS8320_SPI.Init.DataSize = SPI_DATASIZE_22BIT;
    ADS8320_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    ADS8320_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    ADS8320_SPI.Init.NSS = SPI_NSS_HARD_OUTPUT;
    ADS8320_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    ADS8320_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    ADS8320_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    ADS8320_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    ADS8320_SPI.Init.CRCPolynomial = 0x0;
    ADS8320_SPI.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    ADS8320_SPI.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    ADS8320_SPI.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    ADS8320_SPI.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    ADS8320_SPI.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    ADS8320_SPI.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    ADS8320_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    ADS8320_SPI.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    ADS8320_SPI.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    ADS8320_SPI.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  #endif

  #if BOARD_INDEX == 3
    ADS8320_SPI.Instance = ADS8320_SPIx;
    ADS8320_SPI.Init.Mode = SPI_MODE_MASTER;
    ADS8320_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    ADS8320_SPI.Init.DataSize = SPI_DATASIZE_11BIT;
    ADS8320_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    ADS8320_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    ADS8320_SPI.Init.NSS = SPI_NSS_SOFT;
    ADS8320_SPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;//spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    ADS8320_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    ADS8320_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    ADS8320_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    ADS8320_SPI.Init.CRCPolynomial = 0x0;
    ADS8320_SPI.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    ADS8320_SPI.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  #endif

  this->calibration = new Calibration((int)numberOfCalibrationPoints);
  this->readFromFlashSemaphore = new Semaphore(0);
  double k = 0;
  double b = 0;
  this->readCalibrCoefsFromFlash(&k, &b);
  if((uint64_t)k != 0xFFFFFFFFFFFFFFFF && (uint64_t)b != 0xFFFFFFFFFFFFFFFF){
    this->_k = k;
    this->_b = b;
  }
  int size = 0;
  this->readCalibrPointsSizeFromFlash(&size);
  if(size >= 2 && size <= 256){
    point_t *points = new point_t[size];
    this->readCalibrPointsFromFlash(points, size);
    //this->calibration->setNumberOfPoints(size);
    this->calibration->setPoints(points, size);
    this->calibration->calculateSections();
    delete[] points;
  }

  this->calibration2 = new Calibration((int)numberOfCalibrationPoints);
  this->readFromFlashSemaphore2 = new Semaphore(0);
  double k2 = 0;
  double b2 = 0;
  this->readCalibrCoefsFromFlash(&k2, &b2);
  if((uint64_t)k2 != 0xFFFFFFFFFFFFFFFF && (uint64_t)b2 != 0xFFFFFFFFFFFFFFFF){
    this->_k2 = k2;
    this->_b2 = b2;
  }
  int size2 = 0;
  this->readCalibrPointsSizeFromFlash2(&size2);
  if(size2 >= 2 && size2 <= 256){
    point_t *points2 = new point_t[size2];
    this->readCalibrPointsFromFlash2(points2, size2);
    //this->calibration->setNumberOfPoints(size);
    this->calibration2->setPoints(points2, size2);
    this->calibration2->calculateSections();
    delete[] points2;
  }
}

ADS8320::~ADS8320(){
  delete this->calibration;
  delete this->readFromFlashSemaphore;
  delete this->calibration2;
  delete this->readFromFlashSemaphore2;
}

int ADS8320::init(void){
    HAL_SPI_RegisterCallback(&ADS8320_SPI, HAL_SPI_MSPINIT_CB_ID, ADS8320_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&ADS8320_SPI, HAL_SPI_MSPDEINIT_CB_ID,ADS8320_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&ADS8320_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_SPI_RegisterCallback(&ADS8320_SPI, HAL_SPI_RX_COMPLETE_CB_ID, ADS8320_HAL_SPI_RxCpltCallback);
    HAL_SPI_RegisterCallback(&ADS8320_SPI, HAL_SPI_ERROR_CB_ID,ADS8320_HAL_SPI_ErrorCallback);
    return HAL_OK;
}

void ADS8320::setVref(float &Vref){
        ADCVref = Vref;
        ADCLSBWeight = ADCVref / 65536.0;
}

float ADS8320::getVoltage(void){
    ADCDataBits = this->getCodeBlocking();
    return calcVoltage(ADCDataBits);
}

uint16_t ADS8320::getCodeBlocking(void){
  #if BOARD_INDEX == 2
    #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
    HAL_SPI_Receive(&ADS8320_SPI, (uint8_t *)ADCRawBits, 1, 100);
    #else
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS8320_SPIx_CS_PIN) << 16;
    HAL_SPI_Receive(&ADS8320_SPI, (uint8_t *)ADCRawBits, 1, 100);
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ADS8320_SPIx_CS_PIN;
    #endif
    //wait_us(12);
    //while (rADS8320SPITransferState == ADS8320_DMA_SPI_TRANSFER_WAIT){}
    //if(rADS8320SPITransferState == ADS8320_DMA_SPI_TRANSFER_COMPLETE){
        ADCRawBits[0] &= 0xFFFF;   
        ADCDataBits = ADCRawBits[0];
    //    rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_WAIT;
    //}
  #endif
  #if BOARD_INDEX == 3
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS8320_SPIx_CS_PIN) << 16;
    HAL_SPI_Receive(&ADS8320_SPI, (uint8_t *)ADCRawBits, 2, 100);
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ADS8320_SPIx_CS_PIN;
    //wait_us(12);
    //while (rADS8320SPITransferState == ADS8320_DMA_SPI_TRANSFER_WAIT){}
    //if(rADS8320SPITransferState == ADS8320_DMA_SPI_TRANSFER_COMPLETE){
    ADCDataBits = (0xF800 & (ADCRawBits[0] << 11)) | (0x07FF & (ADCRawBits[1]));
    //    rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_WAIT;
    //}
  #endif
    return ADCDataBits;
}

uint32_t ADS8320::startGettingCode(void){
    //ADS8320_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS8320_SPIx_CS_PIN) << 16;
  #if BOARD_INDEX == 2
    #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED
    uint32_t errorState = HAL_SPI_Receive_DMA(&ADS8320_SPI, (uint8_t *)ADCRawBits, 1);
    #else
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS8320_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Receive_DMA(&ADS8320_SPI, (uint8_t *)ADCRawBits, 1);
    #endif
  #endif
  #if BOARD_INDEX == 3
    ADS8320_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS8320_SPIx_CS_PIN) << 16;
    uint32_t errorState = HAL_SPI_Receive_DMA(&ADS8320_SPI, (uint8_t *)ADCRawBits, 2);
  #endif
    return errorState;
}

uint32_t ADS8320::getTransferStatus(void){
  uint32_t status = rADS8320SPITransferState;
  return status;
}
void ADS8320::clearTransferStatus(void){
  rADS8320SPITransferState = ADS8320_DMA_SPI_TRANSFER_WAIT;
}
uint16_t ADS8320::getLastCode(void){
  #if BOARD_INDEX == 2
  ADCDataBits = 0xFFFF & ADCRawBits[0];
  #endif
  #if BOARD_INDEX == 3
  ADCDataBits = (0xF800 & (ADCRawBits[0] << 11)) | (0x07FF & (ADCRawBits[1]));
  #endif
  return ADCDataBits;
}

float ADS8320::getStrain(void){
    return this->calcStrain(this->getCodeBlocking());
}

float ADS8320::calcVoltage(uint16_t &DataBits){
    return ADCLSBWeight * DataBits;
}

uint16_t ADS8320::setNullPoint(){
    //this->clearTransferStatus();
    ADCNullPointDataBits = this->getCodeBlocking();
    return ADCNullPointDataBits;
}

void ADS8320::setCalibrCoefs(double k, double b){
  this->_k = k;
  this->_b = b;
}

void ADS8320::getCalibrCoefs(double *k, double *b){
  *k = this->_k;
  *b = this->_b;
}

float ADS8320::calcStrain(uint16_t code){
    //return (code - ADCNullPointDataBits) * 5.042868 * 0.0001;
    int sections;
    if(this->calibration->getNumberOfSections(sections)){
      return this->calibration->getCalibratedValue(code);
    }
    return (this->_k * code) + this->_b;
}

float ADS8320::calcStrain2(uint16_t code){
  //return (code - ADCNullPointDataBits) * 5.042868 * 0.0001;
  int sections;
  if(this->calibration2->getNumberOfSections(sections)){
    return this->calibration2->getCalibratedValue(code);
  }
  return (this->_k2 * code) + this->_b2;
}

void ADS8320::setFlashOperationType(uint32_t flashOperationType){
  this->_flashOperationType = flashOperationType;
}

errorCode_t ADS8320::writeCalibrCoefsInFlash(double k, double b){
    //TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    //if (TaskManagerMail != nullptr){
    //    TaskManagerMail->task = Task::WRITE_TO_FLASH_STRAIN_CALIBRATION_COEFS;
    //    //запись коэффициентов в сообщение
    //    basic.writeValueToBytesBuffer(TaskManagerMail->data, k, 0);
    //    basic.writeValueToBytesBuffer(TaskManagerMail->data, b, sizeof k);
    //    TaskManagerMail->dataLength = sizeof k + sizeof b;
    //    TaskManagerMailBox.put(TaskManagerMail);
    //    return NO_ERROR;
    //}else{
    //  return SYSTEM_ERROR_DURING_ALLOC_MEMORY;
    //}
    int size = 2 * sizeof(double);
    char *buffer = new char[size];
    basic.writeValueToBytesBuffer(buffer, k);
    basic.writeValueToBytesBuffer(buffer, b, sizeof(double));
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.setWritingParams(buffer, size, STRAIN_CALIBRATION_COEFS_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(buffer, size, STRAIN_CALIBRATION_COEFS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] buffer;
    return NO_ERROR;
}

errorCode_t ADS8320::readCalibrCoefsFromFlash(double *k, double *b){
  //errorCode_t error = NO_ERROR;
  //read
  int size = 2 * sizeof(double);
  char *buffer = new char[size];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.readInOneSector(buffer, STRAIN_CALIBRATION_COEFS_FLASH_OFFSET, size);
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(buffer, size, STRAIN_CALIBRATION_COEFS_FLASH_OFFSET);
      break;
  default:
      break;
  }
  basic.writeBytesBufferToValue(buffer, k);
  basic.writeBytesBufferToValue(buffer + 8, b);
  delete[] buffer;
  return NO_ERROR;
}

errorCode_t ADS8320::writeCalibrPointsInFlash(point_t *points, int size){
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.setWritingParams(buffer, arraySize, STRAIN_CALIBRATION_POINTS_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, arraySize, STRAIN_CALIBRATION_POINTS_FLASH_OFFSET);
      break;
  default:
      break;
  }
  delete[] buffer;
  char *sizeBuffer = new char[sizeof(int)];
  basic.writeValueToBytesBuffer(sizeBuffer, size);
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.setWritingParams(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
      break;
  default:
      break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t ADS8320::readCalibrPointsSizeFromFlash(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.readInOneSector(sizeBuffer, STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, sizeof(int));
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
      break;
  default:
      break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

//TODO 
errorCode_t ADS8320::readCalibrPointsFromFlash(point_t *points, int size){
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(buffer, STRAIN_CALIBRATION_POINTS_FLASH_OFFSET, arraySize);
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(buffer, arraySize, STRAIN_CALIBRATION_POINTS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    for(int i = 0; i < size; i++){
      basic.writeBytesBufferToValue(buffer + i * 2 * sizeof(double)                 , &points[i].xRAW);
      basic.writeBytesBufferToValue(buffer + i * 2 * sizeof(double) + sizeof(double), &points[i].yPhy);
    }
    delete[] buffer;
  }
  return NO_ERROR;
}

errorCode_t ADS8320::writeCalibrPointsInFlash2(point_t *points, int size){
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.setWritingParams(buffer, arraySize, STRAIN_CALIBRATION_POINTS_2_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, arraySize, STRAIN_CALIBRATION_POINTS_2_FLASH_OFFSET);
      break;
  default:
      break;
  }
  delete[] buffer;
  char *sizeBuffer = new char[sizeof(int)];
  basic.writeValueToBytesBuffer(sizeBuffer, size);
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.setWritingParams(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_2_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_2_FLASH_OFFSET);
      break;
  default:
      break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t ADS8320::readCalibrPointsSizeFromFlash2(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.readInOneSector(sizeBuffer, STRAIN_CALIBRATION_POINTS_SIZE_2_FLASH_OFFSET, sizeof(int));
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), STRAIN_CALIBRATION_POINTS_SIZE_2_FLASH_OFFSET);
      break;
  default:
      break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

//TODO 
errorCode_t ADS8320::readCalibrPointsFromFlash2(point_t *points, int size){
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(buffer, STRAIN_CALIBRATION_POINTS_2_FLASH_OFFSET, arraySize);
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(buffer, arraySize, STRAIN_CALIBRATION_POINTS_2_FLASH_OFFSET);
        break;
    default:
        break;
    }
    for(int i = 0; i < size; i++){
      basic.writeBytesBufferToValue(buffer + i * 2 * sizeof(double)                 , &points[i].xRAW);
      basic.writeBytesBufferToValue(buffer + i * 2 * sizeof(double) + sizeof(double), &points[i].yPhy);
    }
    delete[] buffer;
  }
  return NO_ERROR;
}