#include "ADS869xExt.h"
#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   ADS869xExt_SPI;
DMA_HandleTypeDef   ADS869xExt_DMA_SPI_RX;
DMA_HandleTypeDef   ADS869xExt_DMA_SPI_TX;
static volatile uint32_t trADS869xExtSPITransferState = ADS869xExt_DMA_SPI_TRANSFER_WAIT;

#if (CONTROLLER_BOARD_TYPE != CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)

void ADS869xExt_SPIx_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&ADS869xExt_DMA_SPI_RX);
}

void ADS869xExt_SPIx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&ADS869xExt_DMA_SPI_TX);
}

void ADS869xExt_SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&ADS869xExt_SPI);
}

#endif

void ADS869xExt_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==ADS869xExt_SPIx){
    /* SPIx clock enable */
    ADS869xExt_SPIx_SCK_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_MISO_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_MOSI_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_CS_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_CS2_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_CS3_GPIO_CLK_ENABLE();
    ADS869xExt_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    ADS869xExt_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_NSS
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_CS_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    //GPIO_InitStruct.Alternate = ADS869xExt_SPIx_CS_AF;
    HAL_GPIO_Init(ADS869xExt_SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_NSS2
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_CS2_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(ADS869xExt_SPIx_CS2_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_NSS3
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_CS3_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(ADS869xExt_SPIx_CS3_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_SCK
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_SCK_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS869xExt_SPIx_SCK_AF;
    HAL_GPIO_Init(ADS869xExt_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MISO
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_MISO_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS869xExt_SPIx_MISO_AF;
    HAL_GPIO_Init(ADS869xExt_SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);
    //SPIx_MOSI
    GPIO_InitStruct.Pin =       ADS869xExt_SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = ADS869xExt_SPIx_MOSI_AF;
    HAL_GPIO_Init(ADS869xExt_SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_RX Init */
    #if BOARD_INDEX == 2
    ADS869xExt_DMA_SPI_RX.Instance =                 ADS869xExt_SPIx_RX_DMA_STREAM;
    ADS869xExt_DMA_SPI_RX.Init.Request =             ADS869xExt_SPIx_RX_DMA_REQUEST;
    ADS869xExt_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    ADS869xExt_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS869xExt_DMA_SPI_RX.Init.MemInc =              DMA_MINC_DISABLE;
    ADS869xExt_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    ADS869xExt_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_WORD;
    ADS869xExt_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    ADS869xExt_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_LOW;
    ADS869xExt_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS869xExt_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS869xExt_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS869xExt_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC4;
    #endif
    #if BOARD_INDEX == 3
    ADS869xExt_DMA_SPI_RX.Instance =                 ADS869xExt_SPIx_RX_DMA_STREAM;
    ADS869xExt_DMA_SPI_RX.Init.Channel =             ADS869xExt_SPIx_RX_DMA_CHANNEL;
    ADS869xExt_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    ADS869xExt_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS869xExt_DMA_SPI_RX.Init.MemInc =              DMA_MINC_ENABLE;
    ADS869xExt_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    ADS869xExt_DMA_SPI_RX.Init.MemDataAlignment =    DMA_PDATAALIGN_HALFWORD;
    ADS869xExt_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    ADS869xExt_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_LOW;
    ADS869xExt_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS869xExt_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS869xExt_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS869xExt_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC16;
    #endif
    
    if (HAL_DMA_Init(&ADS869xExt_DMA_SPI_RX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_RX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmarx, ADS869xExt_DMA_SPI_RX);
    /* SPIx DMA Init */
    /* SPIx_TX Init */
    #if BOARD_INDEX == 2
    ADS869xExt_DMA_SPI_TX.Instance =                 ADS869xExt_SPIx_TX_DMA_STREAM;
    ADS869xExt_DMA_SPI_TX.Init.Request =             ADS869xExt_SPIx_TX_DMA_REQUEST;
    ADS869xExt_DMA_SPI_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    ADS869xExt_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS869xExt_DMA_SPI_TX.Init.MemInc =              DMA_MINC_DISABLE;
    ADS869xExt_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    ADS869xExt_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_WORD;
    ADS869xExt_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    ADS869xExt_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_LOW;
    ADS869xExt_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS869xExt_DMA_SPI_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS869xExt_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS869xExt_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC4;
    ADS869xExt_DMA_SPI_TX.Instance =                 ADS869xExt_SPIx_TX_DMA_STREAM;
    #endif
    #if BOARD_INDEX == 3
    ADS869xExt_DMA_SPI_TX.Instance =                 ADS869xExt_SPIx_TX_DMA_STREAM;
    ADS869xExt_DMA_SPI_TX.Init.Channel =             ADS869xExt_SPIx_TX_DMA_CHANNEL;    
    ADS869xExt_DMA_SPI_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    ADS869xExt_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    ADS869xExt_DMA_SPI_TX.Init.MemInc =              DMA_MINC_ENABLE;
    ADS869xExt_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    ADS869xExt_DMA_SPI_TX.Init.MemDataAlignment =    DMA_PDATAALIGN_HALFWORD;
    ADS869xExt_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    ADS869xExt_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_LOW;
    ADS869xExt_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    ADS869xExt_DMA_SPI_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    ADS869xExt_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    ADS869xExt_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC16;
    #endif
    if (HAL_DMA_Init(&ADS869xExt_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, ADS869xExt_DMA_SPI_TX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( ADS869xExt_SPIx_DMA_RX_IRQn, 
                          ADS869xExt_SPIx_DMA_RX_IRQn_PreemptPriority, 
                          ADS869xExt_SPIx_DMA_RX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(ADS869xExt_SPIx_DMA_RX_IRQn);
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( ADS869xExt_SPIx_DMA_TX_IRQn, 
                          ADS869xExt_SPIx_DMA_TX_IRQn_PreemptPriority, 
                          ADS869xExt_SPIx_DMA_TX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(ADS869xExt_SPIx_DMA_TX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( ADS869xExt_SPIx_IRQn, 
                          ADS869xExt_SPIx_IRQn_PreemptPriority, 
                          ADS869xExt_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(ADS869xExt_SPIx_IRQn);
  }
}

void ADS869xExt_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==ADS869xExt_SPIx)
  {
    /* Peripheral clock disable */
    ADS869xExt_SPIx_CLK_ENABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MISO
    */
    HAL_GPIO_DeInit(ADS869xExt_SPIx_SCK_GPIO_PORT, ADS869xExt_SPIx_SCK_PIN);
    HAL_GPIO_DeInit(ADS869xExt_SPIx_CS_GPIO_PORT, ADS869xExt_SPIx_CS_PIN);
    HAL_GPIO_DeInit(ADS869xExt_SPIx_MISO_GPIO_PORT, ADS869xExt_SPIx_MISO_PIN);
    HAL_GPIO_DeInit(ADS869xExt_SPIx_MOSI_GPIO_PORT, ADS869xExt_SPIx_MOSI_PIN);
    /* SPIx DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmarx);
    HAL_DMA_DeInit(spiHandle->hdmatx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADS869xExt_SPIx_IRQn);
  }
}

void ADS869xExt_HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  ADS869xExt_SPIx_CS_GPIO_PORT->BSRR  = ADS869xExt_SPIx_CS_PIN;
  ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS2_PIN;
  ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS3_PIN;
  trADS869xExtSPITransferState = ADS869xExt_DMA_SPI_TRANSFER_COMPLETE;
  hspi->hdmatx->State = HAL_DMA_STATE_READY;
}

void ADS869xExt_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  ADS869xExt_SPIx_CS_GPIO_PORT->BSRR  = ADS869xExt_SPIx_CS_PIN;
  ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS2_PIN;
  ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS3_PIN;
  trADS869xExtSPITransferState = ADS869xExt_DMA_SPI_TRANSFER_ERROR;
}
#ifdef __cplusplus
 }
#endif

ADS869xExt::ADS869xExt(unsigned long spiPrescaler, unsigned long numberOfCalibrationPoints){
    this->getPFSNFS(this->PFS, this->NFS);
    this->setVref(this->Vref);
    #if BOARD_INDEX == 2
    ADS869xExt_SPI.Instance = ADS869xExt_SPIx;
    ADS869xExt_SPI.Init.Mode = SPI_MODE_MASTER;
    ADS869xExt_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    ADS869xExt_SPI.Init.DataSize = SPI_DATASIZE_32BIT;
    ADS869xExt_SPI.Init.CLKPolarity = SPI_POLARITY_LOW;
    ADS869xExt_SPI.Init.CLKPhase = SPI_PHASE_1EDGE;
    ADS869xExt_SPI.Init.NSS = SPI_NSS_SOFT;
    ADS869xExt_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    ADS869xExt_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    ADS869xExt_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    ADS869xExt_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    ADS869xExt_SPI.Init.CRCPolynomial = 0x0;
    ADS869xExt_SPI.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    ADS869xExt_SPI.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    ADS869xExt_SPI.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    ADS869xExt_SPI.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    ADS869xExt_SPI.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    ADS869xExt_SPI.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    ADS869xExt_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    ADS869xExt_SPI.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    ADS869xExt_SPI.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    ADS869xExt_SPI.Init.IOSwap = SPI_IO_SWAP_DISABLE;
    #endif
    #if BOARD_INDEX == 3
    ADS869xExt_SPI.Instance = ADS869xExt_SPIx;
    ADS869xExt_SPI.Init.Mode = SPI_MODE_MASTER;
    ADS869xExt_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    ADS869xExt_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
    ADS869xExt_SPI.Init.CLKPolarity = SPI_POLARITY_LOW;
    ADS869xExt_SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
    ADS869xExt_SPI.Init.NSS = SPI_NSS_SOFT;
    ADS869xExt_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    ADS869xExt_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    ADS869xExt_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    ADS869xExt_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    ADS869xExt_SPI.Init.CRCPolynomial = 0x0;
    ADS869xExt_SPI.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
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
    this->readCalibrCoefsFromFlash2(&k2, &b2);
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

    this->calibration3 = new Calibration((int)numberOfCalibrationPoints);
    this->readFromFlashSemaphore3 = new Semaphore(0);
    double k3 = 0;
    double b3 = 0;
    this->readCalibrCoefsFromFlash3(&k3, &b3);
    if((uint64_t)k3 != 0xFFFFFFFFFFFFFFFF && (uint64_t)b3 != 0xFFFFFFFFFFFFFFFF){
      this->_k3 = k3;
      this->_b3 = b3;
    }
    int size3 = 0;
    this->readCalibrPointsSizeFromFlash3(&size3);
    if(size3 >= 2 && size3 <= 256){
      point_t *points3 = new point_t[size3];
      this->readCalibrPointsFromFlash3(points3, size3);
      //this->calibration->setNumberOfPoints(size);
      this->calibration3->setPoints(points3, size3);
      this->calibration3->calculateSections();
      delete[] points3;
    }
}

ADS869xExt::~ADS869xExt(){
    delete this->calibration;
    delete this->calibration2;
    delete this->calibration3;
    delete this->readFromFlashSemaphore;
    delete this->readFromFlashSemaphore2;
    delete this->readFromFlashSemaphore3;
}

int ADS869xExt::init(void){
    HAL_SPI_RegisterCallback(&ADS869xExt_SPI, HAL_SPI_MSPINIT_CB_ID, ADS869xExt_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&ADS869xExt_SPI, HAL_SPI_MSPDEINIT_CB_ID,ADS869xExt_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&ADS869xExt_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_SPI_RegisterCallback(&ADS869xExt_SPI, HAL_SPI_TX_RX_COMPLETE_CB_ID, ADS869xExt_HAL_SPI_TxRxCpltCallback);
    HAL_SPI_RegisterCallback(&ADS869xExt_SPI, HAL_SPI_ERROR_CB_ID,ADS869xExt_HAL_SPI_ErrorCallback);
    ADS869xExt_SPIx_CS_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS_PIN;
    ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS2_PIN;
    ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS3_PIN;
    return HAL_OK;
}

void ADS869xExt::setVref(double Vref){
        this->Vref = Vref;
        this->getPFSNFS(this->PFS, this->NFS);
        this->LSBWeight = (this->PFS - this->NFS) / 262144.0;
}

/**
 * @brief Prepare set the Device Address of current ADC. Data will send while next SPI transfer.
 * 
 * @param[in] deviceAddress Use only 4 LSB bits. Addresses ranges from 0x0 to 0xF;
 */
void ADS869xExt::setDeviceAddress(uint8_t deviceAddress){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_DEVICE_ID_REG + (uint32_t)ADS869xExt_REG_SECOND_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = (uint32_t)0x0F & deviceAddress;
    sendQueue.push(packet);
}
/**
 * @brief Prepare set Reset Power Control Register. Data will send while next SPI transfer.
 * 
 * @param[in] VDDAlDis Set VDD alarm. Disabled if false. Enabled if true. 
 * @param[in] InAlDis Set Input alarm. Disabled if false. Enabled if true. 
 * @param[in] RSTnApp nRST pin function. If false nRST pin functions as a POR class reset (causes full device initialization). If true nRST pin functions as an application reset (only user-programmed modes are cleared).
 * @param[in] NAPEN NAP mode. If false NAP mode of converter is disable. True enables  the converter to enter NAP mode if CONVST/nCS is held high after the current conversion completes.
 * @param[in] PWRDN Converter mode. False - converter into active mode. True - converter into power-down mode.
 */
void ADS869xExt::setResetPwrCtl(bool VDDAlDis, bool InAlDis, bool RSTnApp, bool NAPEN, bool PWRDN){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_RST_PWRCTL_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    ///set WKEY value for disable write protection
    uint32_t temp = 0x00006900;
    if(VDDAlDis){
      temp |= ADS869xExt_RST_PWRCTL_REG_VDD_AL_DIS;
    }
    if(InAlDis){
      temp |= ADS869xExt_RST_PWRCTL_REG_IN_AL_DIS;
    }
    if(RSTnApp){
      temp |= ADS869xExt_RST_PWRCTL_REG_RSTN_APP;
    }
    if(NAPEN){
      temp |= ADS869xExt_RST_PWRCTL_REG_NAP_EN;
    }
    if(PWRDN){
      temp |= ADS869xExt_RST_PWRCTL_REG_PWRDN;
    }
    packet.data = (uint32_t)0xFF37 & temp;
    sendQueue.push(packet);
}

/**
 * @brief Prepare set Data Out Register. Data will send while next SPI transfer. 
 * @details This command sets ADC Output Word content.
 * 
 * @param[in] deviceAddr True - include Device Address in output word.
 * @param[in] vddActiveAlarm 0b00 - do not include. 0b01 - include ACTIVE_VDD_H_FLAG. 0b01 - include ACTIVE_VDD_H_FLAG. 0b11 - include both flags.
 * @param[in] inActiveAlarm 0b00 - do not include. 0b01 - include ACTIVE_IN_H_FLAG. 0b01 - include ACTIVE_IN_H_FLAG. 0b11 - include both flags.
 * @param[in] range True - include 4-bit input range setting in output word.
 * @param[in] parity True - include parity bits in output word. Two parity bits(ADC output and output data frame) are appended to the LSBs of the output data.
 * @param[in] dataVal These bits control the data value output by the converter. Bits corresponding ADS869xExtDataVal type values.
 */
void ADS869xExt::setDataOut(bool deviceAddr, ADS869xExtActiveAlarm vddActiveAlarm, ADS869xExtActiveAlarm inActiveAlarm, bool range, bool parity, ADS869xExtDataVal dataVal){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_RANGE_SEL_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = 0x0;
    if(deviceAddr){
      packet.data |= ADS869xExt_DATAOUT_CTL_REG_DEVICE_ADDR_INCL;
    }
    packet.data |= ADS869xExt_DATAOUT_CTL_REG_VDD_ACTIVE_ALARM_INCL & (((uint16_t)vddActiveAlarm) << 12);
    packet.data |= ADS869xExt_DATAOUT_CTL_REG_IN_ACTIVE_ALARM_INCL & (((uint16_t)inActiveAlarm) << 10);
    if(range){
      packet.data |= ADS869xExt_DATAOUT_CTL_REG_RANGE_INCL;
    }
    if(parity){
      packet.data |= ADS869xExt_DATAOUT_CTL_REG_PAR_EN;
    }
    packet.data |= ADS869xExt_DATAOUT_CTL_REG_DATA_VAL & ((uint16_t)dataVal);
    sendQueue.push(packet);
}

/**
 * @brief Prepare set the Input Range Register
 * @details This command control source of reference voltage and input voltage reference.
 * 
 * @param externalRef False - internal reference enable. True - internal reference disable, used external reference.
 * @param range These bits control input voltage range. Values corresponding ADS869xExtRange type;
 */
void ADS869xExt::setRange(ADS869xExtExternalRef externalRef, ADS869xExtRange range){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_RANGE_SEL_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE_LSB;
    packet.data     = (ADS869xExt_RANGE_SEL_REG_INTREF_DIS & externalRef) | (range & ADS869xExt_RANGE_SEL_REG_RANGE_SEL);
    sendQueue.push(packet);
}

/**
 * @brief Prepare set ADC SPI Mode
 * @details This command set ADC SPI Mode into the SDI_CTL_REG Register
 * 
 * @param spiMode 2 bits to set CPOL (correspond MSB bit) and CPHASE (correspond LSB bit).
 */
void ADS869xExt::setADCSPIMode(ADS869xExtSPIMode spiMode){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_SDI_CTL_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE_LSB;
    packet.data     = 0x0003 & (uint16_t)spiMode;
    sendQueue.push(packet);
}

/**
 * @brief Prepare set ADC SDO Mode
 * @details This command set SDO Mode Register. This register controls the data protocol used to transmit data out from the SDO-x pins.
 * 
 * @param SDO1Config Two bits are used to configure ALARM/SDO-1/GPO.
 * @param SSyncClk This bit controls the source of the clock selected for source-synchronous transmission. This bit takes effect ONLY in the ADC master clock of source-synchronous mode of operation.
 * @param SDOMode These bits control the data output modes of the device.
 */
void ADS869xExt::setADCSDOMode(ADS869xExtSDO1Config SDO1Config, ADS869xExtSSyncClk SSyncClk, ADS869xExtSDOMode SDOMode){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_SDO_CTL_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = SDO1Config | SSyncClk | SDOMode;
    sendQueue.push(packet);
}

/**
 * @brief Prepare set the Alarm Register
 * @details This command control output alarm flags (active and tripped) for the input and AVDD alarm.
 * 
 * @param activeVDDLFlag Active Alarm output flag for low AVDD voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param activeVDDHFlag Active Alarm output flag for high AVDD voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param activeInLFlag Active Alarm output flag for low input voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param activeInHFlag Active Alarm output flag for high input voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param TrpVDDLFlag Tripped Alarm output flag for low VDD voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param TrpVDDHFlag Tripped Alarm output flag for high VDD voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param TrpInLFlag Tripped Alarm output flag for low input voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param TrpInHFlag Tripped Alarm output flag for high input voltage. 0 - no alarm. 1 - alarm condition exists.
 * @param OVW Logical OR outputs all tripped alarm flags. 0 - no alarm. 1 - alarm condition exists.
 */
void ADS869xExt::setActiveAlarm(
    bool activeVDDLFlag, 
    bool activeVDDHFlag, 
    bool activeInLFlag, 
    bool activeInHFlag, 
    bool TrpVDDLFlag, 
    bool TrpVDDHFlag,
    bool TrpInLFlag,
    bool TrpInHFlag,
    bool OVW
){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_ALARM_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = 0x0;
    if(activeVDDLFlag){
      packet.data |= ADS869xExt_ALARM_REG_ACTIVE_VDD_L_FLAG;
    }
    if(activeVDDHFlag){
      packet.data |= ADS869xExt_ALARM_REG_ACTIVE_VDD_H_FLAG;
    }
    if(activeInLFlag){
      packet.data |= ADS869xExt_ALARM_REG_ACTIVE_IN_L_FLAG;
    }
    if(activeInHFlag){
      packet.data |= ADS869xExt_ALARM_REG_ACTIVE_IN_H_FLAG;
    }
    if(TrpVDDLFlag){
      packet.data |= ADS869xExt_ALARM_REG_TRP_VDD_L_FLAG;
    }
    if(TrpVDDHFlag){
      packet.data |= ADS869xExt_ALARM_REG_TRP_VDD_H_FLAG;
    }
    if(TrpInLFlag){
      packet.data |= ADS869xExt_ALARM_REG_TRP_IN_L_FLAG;
    }
    if(TrpInHFlag){
      packet.data |= ADS869xExt_ALARM_REG_TRP_IN_H_FLAG;
    }
    if(OVW){
      packet.data |= ADS869xExt_ALARM_REG_OVW_ALARM;
    }
    sendQueue.push(packet);
}

/**
 * @brief Prepare set alarm hysteresis and high threshold for the input alarm
 * @details This command set ALARM_H_TH_REG Register. After this command need to complete 2 transfers.
 * 
 * @param hystVoltage 6-bit[7:2] hysteresis value for the input alarm. Bits [1:0] will set to 0b00.
 * @param highVoltage Threshold for comparison. Will appended with 0b00.
 */
void ADS869xExt::setHystAndHighAlarm(uint8_t hystVoltage, uint16_t highVoltage){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_ALARM_H_TH_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = highVoltage;
    sendQueue.push(packet);
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_ALARM_H_TH_REG + (uint32_t)ADS869xExt_REG_THIRD_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE_LSB;
    packet.data     = hystVoltage & 0xFC;
    sendQueue.push(packet);
}

/**
 * @brief Prepare set alarm low threshold for the input alarm
 * @details This command set ALARM_L_TH_REG Register. 
 * 
 * @param lowVoltage Threshold for comparison. Will appended with 0b00.
 */
void ADS869xExt::setLowAlarm(uint16_t lowVoltage){
    ADS869xExtSendDataPacket_t packet;
    packet.address  = (ADS869xExtRegisterAddress)((uint32_t)ADS869xExt_ALARM_L_TH_REG + (uint32_t)ADS869xExt_REG_NULL_BYTE);
    packet.cmd      = ADS869xExt_CMD_WRITE;
    packet.data     = lowVoltage;
    sendQueue.push(packet);
}

/**
 * @brief Prepare and calculate bits for sending
 * 
 * @param packet data struct 
 */
void ADS869xExt::prepareSendBits(ADS869xExtSendDataPacket_t *packet){
    
    ADS869xExtSendDataPacket_t temp;
    #if BOARD_INDEX == 2
    if(sendQueue.pop(temp)){
        packet->cmd      = (ADS869xExtCmd)((uint32_t)temp.cmd & 0xFE000000);
        packet->address  = (ADS869xExtRegisterAddress)((uint32_t)temp.address & 0x01FF0000);
        packet->data     = temp.data & 0x0000FFFF;
        SendRawBits[0] = packet->cmd | packet->address | packet->data;
    }else{
        packet->address = ADS869xExt_DEVICE_ID_REG;
        packet->cmd = ADS869xExt_CMD_NOP;
        packet->data = 0x0;
        SendRawBits[0] = 0x0;
    }
    #endif
    #if BOARD_INDEX == 3
    if(sendQueue.pop(temp)){
        packet->cmd      = (ADS869xExtCmd)((uint32_t)temp.cmd & 0xFE000000);
        packet->address  = (ADS869xExtRegisterAddress)((uint32_t)temp.address & 0x01FF0000);
        packet->data     = temp.data & 0x0000FFFF;
        SendRawBits[0] = packet->cmd | packet->address;
        SendRawBits[1] = packet->data;
    }else{
        packet->address = ADS869xExt_DEVICE_ID_REG;
        packet->cmd = ADS869xExt_CMD_NOP;
        packet->data = 0x0;
        SendRawBits[0] = 0x0;
        SendRawBits[1] = 0x0;
    }
    #endif
}

/**
 * @brief Parse receiving bits
 * 
 * @param packet data struct
 */
void ADS869xExt::parseReceiveBits(ADS869xExtSendDataPacket_t *packet){
    if(lastCmd == ADS869xExt_CMD_READ_HWORD || lastCmd == ADS869xExt_CMD_READ_BYTE){
      #if BOARD_INDEX == 2
        lastAnswer = RecvRawBits[0];
      #endif
      #if BOARD_INDEX == 3
        lastAnswer = (0xFFFF0000 & RecvRawBits[0] << 16) | (0x0000FFFF & RecvRawBits[1]);
      #endif
    }else{
        #if BOARD_INDEX == 2
        outputWord.conversionResult = RecvRawBits[0] >> 14;
        uint32_t data = RecvRawBits[0] << 18;
        #endif
        #if BOARD_INDEX == 3
        outputWord.conversionResult = ((0xFFFF0000 & RecvRawBits[0] << 16) | (0x0000FFFF & RecvRawBits[1])) >> 14;
        uint32_t data = ((0xFFFF0000 & RecvRawBits[0] << 16) | (0x0000FFFF & RecvRawBits[1])) << 18;
        #endif
        if(registers.DATAOUT_CTL_REG & ADS869xExt_DATAOUT_CTL_REG_DEVICE_ADDR_INCL){
            outputWord.deviceAddress = data >> 28;
            data <<= 4;
        }
        switch(registers.DATAOUT_CTL_REG & ADS869xExt_DATAOUT_CTL_REG_VDD_ACTIVE_ALARM_INCL){
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_H_FLAG:
                outputWord.AVDDAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_H_FLAG;
                data <<= 2;
                break;
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_L_FLAG:
                outputWord.AVDDAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_L_FLAG;
                data <<= 2;
                break;
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_BOTH:
                outputWord.AVDDAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_BOTH;
                data <<= 2;
                break;
            default:
                break;
        }
        switch(registers.DATAOUT_CTL_REG & ADS869xExt_DATAOUT_CTL_REG_IN_ACTIVE_ALARM_INCL){
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_H_FLAG:
                outputWord.inputAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_H_FLAG;
                data <<= 2;
                break;
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_L_FLAG:
                outputWord.inputAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_L_FLAG;
                data <<= 2;
                break;
            case ADS869xExt_ACTIVE_ALARM_INCLUDE_BOTH:
                outputWord.inputAlarmFlags = (data >> 30) & ADS869xExt_ACTIVE_ALARM_INCLUDE_BOTH;
                data <<= 2;
                break;
            default:
                break;
        }
        if(registers.DATAOUT_CTL_REG & ADS869xExt_DATAOUT_CTL_REG_RANGE_INCL){
            outputWord.inputRange = data >> 28;
            data <<= 4;
        }
        if(registers.DATAOUT_CTL_REG & ADS869xExt_DATAOUT_CTL_REG_PAR_EN){
            outputWord.parityBits = data >> 30;
            data <<= 2;
        }
        
    }
    if(packet->cmd != ADS869xExt_CMD_NOP){
        lastCmd = packet->cmd;
    }
}

/**
 * @brief This method start SPI transfer.
 * @details This method using blocking mode. Send command if it was prepared in queue.
 * 
 * @return HAL_StatusTypeDef - status of transfer. HAL_OK if transfer complete successful.
 */
HAL_StatusTypeDef ADS869xExt::transferBlocking(void){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket);
    ADS869xExt_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1, 100);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2, 100);
    #endif
    ADS869xExt_SPIx_CS_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS_PIN;
    this->parseReceiveBits(&lastPacket);
    return result;
}

HAL_StatusTypeDef ADS869xExt::transferBlocking2(void){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket2);
    ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS2_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1, 100);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2, 100);
    #endif
    ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS2_PIN;
    this->parseReceiveBits(&lastPacket2);
    return result;
}

HAL_StatusTypeDef ADS869xExt::transferBlocking3(void){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket3);
    ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS3_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1, 100);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2, 100);
    #endif
    ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ADS869xExt_SPIx_CS3_PIN;
    this->parseReceiveBits(&lastPacket3);
    return result;
}

/**
 * @brief Launch DMA channel for receiving ADC value.
 * @details This method using non-blocking mode. Send command if it was prepared in queue.
 * 
 * @return HAL_StatusTypeDef - status of transfer. HAL_OK if start transfer complete successful. 
 */
HAL_StatusTypeDef ADS869xExt::startTransfer(bool firstStart){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket);
    ADS869xExt_SPIx_CS_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2);
    #endif
    return result;
}

HAL_StatusTypeDef ADS869xExt::startTransfer2(bool firstStart){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket2);
    ADS869xExt_SPIx_CS2_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS2_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2);
    #endif
    return result;
}

HAL_StatusTypeDef ADS869xExt::startTransfer3(bool firstStart){
    HAL_StatusTypeDef result;
    this->prepareSendBits(&lastPacket3);
    ADS869xExt_SPIx_CS3_GPIO_PORT->BSRR = ((uint32_t)ADS869xExt_SPIx_CS3_PIN) << 16;
    #if BOARD_INDEX == 2
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 1);
    #endif
    #if BOARD_INDEX == 3
    result = HAL_SPI_TransmitReceive_DMA(&ADS869xExt_SPI, (uint8_t *)SendRawBits, (uint8_t *)RecvRawBits, 2);
    #endif
    return result;
}

/**
 * @brief Get the Transfer Status of DMA transaction
 * 
 * @return uint32_t Status
 */
uint32_t ADS869xExt::getTransferStatus(void){
    return trADS869xExtSPITransferState;
}

/**
 * @brief Clear the Transfer Status of DMA transaction
 * 
 */
void ADS869xExt::clearTransferStatus(void){
    trADS869xExtSPITransferState = ADS869xExt_DMA_SPI_TRANSFER_WAIT;
}

/**
 * @brief Calculate PFS, NFS
 * @details This method calculate Positive Full-Scale, Negative Full-Scale. Units is Volts. Reference voltage must be set before calculate.
 * 
 * @param PFS Positive Full-Scale (V)
 * @param NFS Negative Full-Scale (V)
 */
void ADS869xExt::getPFSNFS(double &PFS, double &NFS){
    switch (this->range)
    {
    case ADS869xExt_PM_3:
        PFS = this->Vref * 3.0;
        NFS = this->Vref * (-3.0);
        break;
    case ADS869xExt_PM_2_5:
        PFS = this->Vref * 2.5;
        NFS = this->Vref * (-2.5);
        break;
    case ADS869xExt_PM_1_5:
        PFS = this->Vref * 1.5;
        NFS = this->Vref * (-1.5);
        break;
    case ADS869xExt_PM_1_25:
        PFS = this->Vref * 1.25;
        NFS = this->Vref * (-1.25);
        break;
    case ADS869xExt_PM_0_625:
        PFS = this->Vref * 0.625;
        NFS = this->Vref * (-0.625);
        break;
    case ADS869xExt_P_3:
        PFS = this->Vref * 3.0;
        NFS = 0.0;
        break;
    case ADS869xExt_P_2_5:
        PFS = this->Vref * 2.5;
        NFS = 0.0;
        break;
    case ADS869xExt_P_1_5:
        PFS = this->Vref * 1.5;
        NFS = 0.0;
        break;
    case ADS869xExt_P_1_25:
        PFS = this->Vref * 1.25;
        NFS = 0.0;
        break;

    default:
        PFS = this->Vref * 3.0;
        NFS = this->Vref * (-3.0);
        break;
    }
}

double ADS869xExt::calcVoltage(uint32_t &DataBits){
    return this->LSBWeight * DataBits + this->NFS;
}

uint32_t ADS869xExt::calcCode(double voltage){
    return (uint32_t)(std::round((voltage - this->NFS) / LSBWeight));
}

double ADS869xExt::calcDeformation(uint32_t code){
    int sections;
    if(this->calibration->getNumberOfSections(sections)){
      return this->calibration->getCalibratedValue(code);
    }
    return (this->_k * code) + this->_b;
}

double ADS869xExt::calcDeformation2(uint32_t code){
    int sections;
    if(this->calibration2->getNumberOfSections(sections)){
      return this->calibration2->getCalibratedValue(code);
    }
    return (this->_k2 * code) + this->_b2;
}

double ADS869xExt::calcDeformation3(uint32_t code){
    int sections;
    if(this->calibration3->getNumberOfSections(sections)){
      return this->calibration3->getCalibratedValue(code);
    }
    return (this->_k3 * code) + this->_b3;
}

uint32_t ADS869xExt::getLastCode(){
  return  this->getLastCode(false);
}

uint32_t ADS869xExt::getLastCode2(){
  return  this->getLastCode2(false);
}

uint32_t ADS869xExt::getLastCode3(){
  return  this->getLastCode3(false);
}

uint32_t ADS869xExt::getLastCode(bool parseResult){
  if(parseResult){
    this->parseReceiveBits(&lastPacket);
  }
  return  outputWord.conversionResult;
}

uint32_t ADS869xExt::getLastCode2(bool parseResult){
  if(parseResult){
    this->parseReceiveBits(&lastPacket2);
  }
  return  outputWord.conversionResult;
}

uint32_t ADS869xExt::getLastCode3(bool parseResult){
  if(parseResult){
    this->parseReceiveBits(&lastPacket3);
  }
  return  outputWord.conversionResult;
}

float ADS869xExt::getVoltage(void){
  uint32_t value = this->getLastCode(false);
  return (float)this->calcVoltage(value);
}

void ADS869xExt::setCalibrCoefs(double k, double b){
  this->_k = k;
  this->_b = b;
}

void ADS869xExt::getCalibrCoefs(double *k, double *b){
  *k = this->_k;
  *b = this->_b;
}


void ADS869xExt::setFlashOperationType(uint32_t flashOperationType){
  this->_flashOperationType = flashOperationType;
}

errorCode_t ADS869xExt::writeCalibrCoefsInFlash(double k, double b){
    //TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    //if (TaskManagerMail != nullptr){
    //    TaskManagerMail->task = TASK_WRITE_TO_FLASH_STRAIN_CALIBRATION_COEFS;
    //    //������ ������������� � ���������
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
    internalFlash.setWritingParams(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, true);
    internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
      break;
    default:
      break;
    }
    delete[] buffer;
    return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrCoefsFromFlash(double *k, double *b){
  //errorCode_t error = NO_ERROR;
  //read
  int size = 2 * sizeof(double);
  char *buffer = new char[size];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, size);
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(buffer, k);
  basic.writeBytesBufferToValue(buffer + 8, b);
  delete[] buffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::writeCalibrPointsInFlash(point_t *points, int size){
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.setWritingParams(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET);
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
  internalFlash.setWritingParams(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET);
    break;
  default:
    break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrPointsSizeFromFlash(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.readInOneSector(sizeBuffer, DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET, sizeof(int));
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

//TODO 
errorCode_t ADS869xExt::readCalibrPointsFromFlash(point_t *points, int size){
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
    internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET, arraySize);
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET);
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

void ADS869xExt::setCalibrCoefs2(double k, double b){
  this->_k2 = k;
  this->_b2 = b;
}

void ADS869xExt::getCalibrCoefs2(double *k, double *b){
  *k = this->_k2;
  *b = this->_b2;
}


errorCode_t ADS869xExt::writeCalibrCoefsInFlash2(double k, double b){
    //TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    //if (TaskManagerMail != nullptr){
    //    TaskManagerMail->task = TASK_WRITE_TO_FLASH_STRAIN_CALIBRATION_COEFS;
    //    //������ ������������� � ���������
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
    internalFlash.setWritingParams(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, true);
    internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
      break;
    default:
      break;
    }
    delete[] buffer;
    return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrCoefsFromFlash2(double *k, double *b){
  //errorCode_t error = NO_ERROR;
  //read
  int size = 2 * sizeof(double);
  char *buffer = new char[size];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, size);
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(buffer, k);
  basic.writeBytesBufferToValue(buffer + 8, b);
  delete[] buffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::writeCalibrPointsInFlash2(point_t *points, int size){
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.setWritingParams(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET);
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
  internalFlash.setWritingParams(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET);
    break;
  default:
    break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrPointsSizeFromFlash2(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.readInOneSector(sizeBuffer, DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET, sizeof(int));
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

//TODO 
errorCode_t ADS869xExt::readCalibrPointsFromFlash2(point_t *points, int size){
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
    internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET, arraySize);
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET);
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

void ADS869xExt::setCalibrCoefs3(double k, double b){
  this->_k3 = k;
  this->_b3 = b;
}

void ADS869xExt::getCalibrCoefs3(double *k, double *b){
  *k = this->_k3;
  *b = this->_b3;
}

errorCode_t ADS869xExt::writeCalibrCoefsInFlash3(double k, double b){
    int size = 2 * sizeof(double);
    char *buffer = new char[size];
    basic.writeValueToBytesBuffer(buffer, k);
    basic.writeValueToBytesBuffer(buffer, b, sizeof(double));
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
    internalFlash.setWritingParams(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, true);
    internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
      break;
    default:
      break;
    }
    delete[] buffer;
    return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrCoefsFromFlash3(double *k, double *b){
  int size = 2 * sizeof(double);
  char *buffer = new char[size];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET, size);
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(buffer, size, DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(buffer, k);
  basic.writeBytesBufferToValue(buffer + 8, b);
  delete[] buffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrPointsSizeFromFlash3(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
    internalFlash.readInOneSector(sizeBuffer, DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET, sizeof(int));
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET);
    break;
  default:
    break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t ADS869xExt::readCalibrPointsFromFlash3(point_t *points, int size){
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
    internalFlash.readInOneSector(buffer, DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_OFFSET, arraySize);
      break;
    case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_OFFSET);
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

errorCode_t ADS869xExt::writeCalibrPointsInFlash3(point_t *points, int size){
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
  internalFlash.setWritingParams(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(buffer, arraySize, DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_OFFSET);
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
  internalFlash.setWritingParams(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET, true);
  internalFlash.Writing_To_Flash_Through_Buf_Sector();
    break;
  case FLASH_OPERATION_DMA:
    internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET);
    break;
  default:
    break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}