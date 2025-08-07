/*
	RSSI.cpp - Library for getting data from R Series throught SSI interface.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
 
 #include <RSSI.h>
 
#ifdef __cplusplus
 extern "C" {
#endif
SPI_HandleTypeDef   SSI_SPI;
DMA_HandleTypeDef   SSI_DMA_SPI_RX;
DMA_HandleTypeDef   SSI_DMA_SPI_TX;
/*
SPI PORT PINS CONFIG
*/
GPIO_TypeDef    *_sckPort   = GPIOC;
uint16_t         _sckPin    = GPIO_PIN_10;
uint8_t          _sckAF     = GPIO_AF6_SPI3;
GPIO_TypeDef    *_misoPort  = GPIOC;
uint16_t         _misoPin   = GPIO_PIN_11;
uint8_t          _misoAF    = GPIO_AF6_SPI3;

static volatile uint32_t rSSISPITransferState = SSI_DMA_SPI_TRANSFER_WAIT;

void SSI_SPIx_SCK_GPIO_CLK_Enable(void){
    if (_sckPort == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }else{
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
}

void SSI_SPIx_MISO_GPIO_CLK_Enable(void){
    if (_misoPort == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }else{
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
}

void SSI_SPIx_DMA_RX_IRQHandler(void)
{
    #if BOARD_INDEX == 2
    HAL_DMA_IRQHandler(&SSI_DMA_SPI_RX);
    #endif
    #if BOARD_INDEX == 3
    HAL_DMA_IRQHandler(SSI_SPI.hdmatx);
    HAL_DMA_IRQHandler(SSI_SPI.hdmarx);
    #endif
}

void SSI_SPIx_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&SSI_SPI);
}

void SSI_HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle){
  GPIO_InitTypeDef GPIO_InitStruct;
  if(spiHandle->Instance==SSI_SPIx){
    /* SPIx clock enable */
    // SSI_SPIx_SCK_GPIO_CLK_Enable();
    // SSI_SPIx_MISO_GPIO_CLK_Enable();
    SSI_SPIx_SCK_GPIO_CLK_ENABLE();
    SSI_SPIx_MISO_GPIO_CLK_ENABLE();
    SSI_SPIx_CLK_ENABLE();
    /* DMA controller clock enable */
    SSI_DMAx_CLK_ENABLE();
    /**SPIx GPIO Configuration*/
    //SPIx_SCK
    GPIO_InitStruct.Pin =       _sckPin;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLUP;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = _sckAF;
    HAL_GPIO_Init(_sckPort, &GPIO_InitStruct);
    //SPIx_MISO
    GPIO_InitStruct.Pin =       _misoPin;
    #if BOARD_INDEX == 3
        GPIO_InitStruct.Mode =      GPIO_MODE_AF_OD;
    #else 
        GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    #endif
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = _misoAF;
    HAL_GPIO_Init(_misoPort, &GPIO_InitStruct);
    /* SPIx DMA Init */
    /* SPIx_RX Init */
    #if BOARD_INDEX == 2
    SSI_DMA_SPI_RX.Instance =                 SSI_SPIx_RX_DMA_STREAM;
    SSI_DMA_SPI_RX.Init.Request =             SSI_SPIx_RX_DMA_REQUEST;
    SSI_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    SSI_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    
    if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
    SSI_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    SSI_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_WORD;
        SSI_DMA_SPI_RX.Init.MemInc =              DMA_MINC_DISABLE;
    }else{
        SSI_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        SSI_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
        SSI_DMA_SPI_RX.Init.MemInc =              DMA_MINC_ENABLE;
    }
    SSI_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    SSI_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_HIGH;
    SSI_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    SSI_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    SSI_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    SSI_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC4;
    #endif

    #if BOARD_INDEX == 3
    SSI_DMA_SPI_RX.Instance =                 SSI_SPIx_RX_DMA_STREAM;
    SSI_DMA_SPI_RX.Init.Channel =             SSI_SPIx_RX_DMA_CHANNEL;
    SSI_DMA_SPI_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    SSI_DMA_SPI_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    SSI_DMA_SPI_RX.Init.MemInc =              DMA_MINC_ENABLE;
    SSI_DMA_SPI_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    SSI_DMA_SPI_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    SSI_DMA_SPI_RX.Init.Mode =                DMA_NORMAL;
    SSI_DMA_SPI_RX.Init.Priority =            DMA_PRIORITY_HIGH;
    SSI_DMA_SPI_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    SSI_DMA_SPI_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    SSI_DMA_SPI_RX.Init.MemBurst =            DMA_MBURST_INC16;
    SSI_DMA_SPI_RX.Init.PeriphBurst =         DMA_PBURST_INC16;
    #endif
    if (HAL_DMA_Init(&SSI_DMA_SPI_RX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_RX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmarx, SSI_DMA_SPI_RX);
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( SSI_SPIx_DMA_RX_IRQn, 
                          SSI_SPIx_DMA_RX_IRQn_PreemptPriority, 
                          SSI_SPIx_DMA_RX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(SSI_SPIx_DMA_RX_IRQn);
    /* SPIx interrupt Init */
    HAL_NVIC_SetPriority( SSI_SPIx_IRQn, 
                          SSI_SPIx_IRQn_PreemptPriority, 
                          SSI_SPIx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(SSI_SPIx_IRQn);

    #if BOARD_INDEX == 3
    SSI_DMA_SPI_TX.Instance =                 SSI_SPIx_TX_DMA_STREAM;
    SSI_DMA_SPI_TX.Init.Channel =             SSI_SPIx_TX_DMA_CHANNEL;
    SSI_DMA_SPI_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    SSI_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    SSI_DMA_SPI_TX.Init.MemInc =              DMA_MINC_ENABLE;
    SSI_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    SSI_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
    SSI_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    SSI_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_HIGH;
    SSI_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    SSI_DMA_SPI_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    SSI_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    SSI_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC16;
    if (HAL_DMA_Init(&SSI_DMA_SPI_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(spiHandle,hdmatx, SSI_DMA_SPI_TX);
    #endif
    #if (BOARD_INDEX == 2)
    SSI_DMA_SPI_TX.Instance =                 SSI_SPIx_RX_DMA_STREAM;
    SSI_DMA_SPI_TX.Init.Request =             SSI_SPIx_RX_DMA_REQUEST;
    SSI_DMA_SPI_TX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    SSI_DMA_SPI_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    
    if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
        SSI_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
        SSI_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_WORD;
        SSI_DMA_SPI_TX.Init.MemInc =              DMA_MINC_DISABLE;
    }else{
        SSI_DMA_SPI_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        SSI_DMA_SPI_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_HALFWORD;
        SSI_DMA_SPI_TX.Init.MemInc =              DMA_MINC_ENABLE;
  }
    SSI_DMA_SPI_TX.Init.Mode =                DMA_NORMAL;
    SSI_DMA_SPI_TX.Init.Priority =            DMA_PRIORITY_HIGH;
    SSI_DMA_SPI_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    SSI_DMA_SPI_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    SSI_DMA_SPI_TX.Init.MemBurst =            DMA_MBURST_INC16;
    SSI_DMA_SPI_TX.Init.PeriphBurst =         DMA_PBURST_INC4;
        if (HAL_DMA_Init(&SSI_DMA_SPI_TX) != HAL_OK)
        {
          printf("\n\rError during HAL_DMA_TX_Init!\n\r");
        }
        __HAL_LINKDMA(spiHandle,hdmatx, SSI_DMA_SPI_TX);
    #endif
  }
}

void SSI_HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SSI_SPIx)
  {
    /* Peripheral clock disable */
    SSI_SPIx_CLK_DISABLE();
    /**SPIx GPIO Configuration
    SPIx_NSS
    SPIx_SCK
    SPIx_MISO
    */
    HAL_GPIO_DeInit(_sckPort, _sckPin);
    HAL_GPIO_DeInit(_misoPort, _misoPin);
    /* SPIx DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmarx);
    /* SPIx interrupt Deinit */
    HAL_NVIC_DisableIRQ(SSI_SPIx_IRQn);
  }
}

void SSI_HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  rSSISPITransferState = SSI_DMA_SPI_TRANSFER_COMPLETE;
}

void SSI_HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  rSSISPITransferState = SSI_DMA_SPI_TRANSFER_ERROR;
}

#ifdef __cplusplus
 }
#endif


#if BOARD_INDEX == 2
 RSSI::RSSI(
     unsigned long spiPrescaler, 
     int SSINumberOfBits,
     unsigned long numberOfCalibrationPoints,
     PinName SCK,
     PinName MISO){
    
    this->SCK = SCK;
    this->MISO = MISO;
    switch(SCK)
    {
        case PB_3:
            _sckPort   = GPIOB;
            _sckPin    = GPIO_PIN_3;
            _sckAF     = GPIO_AF6_SPI3;
            break;
        case PC_10:
            _sckPort   = GPIOC;
            _sckPin    = GPIO_PIN_10;
            _sckAF     = GPIO_AF6_SPI3;
            break;
        case PF_7:
            _sckPort   = GPIOF;
            _sckPin    = GPIO_PIN_7;
            _sckAF     = GPIO_AF5_SPI5;
            break;
        default:
            //default PC_10
            break;
    }
    switch(MISO)
    {
        case PB_4:
            _misoPort   = GPIOB;
            _misoPin    = GPIO_PIN_4;
            _misoAF     = GPIO_AF6_SPI3;
            break;
        case PC_11:
            _misoPort   = GPIOC;
            _misoPin    = GPIO_PIN_11;
            _misoAF     = GPIO_AF6_SPI3;
            break;
        case PF_8:
            _misoPort   = GPIOF;
            _misoPin    = GPIO_PIN_8;
            _misoAF     = GPIO_AF5_SPI5;
            break;
        default:
            //default PC_11
            break;
    }

    numberOfBits = SSINumberOfBits + 1;

    SSI_SPI.Instance = SSI_SPIx;
    SSI_SPI.Init.Mode = SPI_MODE_MASTER;
    SSI_SPI.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
    if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
    switch (numberOfBits)
    {
    case 16:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
        break;
    case 17:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_17BIT;
        break;
    case 18:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_18BIT;
        break;
    case 19:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_19BIT;
        break;
    case 20:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_20BIT;
        break;
    case 21:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_21BIT;
        break;
    case 22:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_22BIT;
        break;
    case 23:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_23BIT;
        break;
    case 24:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_24BIT;
        break;
    case 25:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_25BIT;
        break;
    case 26:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_26BIT;
        break;
    case 27:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_27BIT;
        break;
    case 28:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_28BIT;
        break;
    case 29:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_29BIT;
        break;
    case 30:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_30BIT;
        break;
    case 31:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_31BIT;
        break;
    case 32:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_32BIT;
        break;

    default:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_24BIT;
        break;
        }       
    }
    else{
        switch (numberOfBits)
        {
        case 16:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
            break;
        case 17:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_9BIT;
            break;
        case 18:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_9BIT;
            break;
        case 19:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_10BIT;
            break;
        case 20:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_10BIT;
            break;
        case 21:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_11BIT;
            break;
        case 22:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_11BIT;
            break;
        case 23:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
            break;
        case 24:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
            break;
        case 25:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_13BIT;
            break;
        case 26:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_13BIT;
            break;
        case 27:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_14BIT;
            break;
        case 28:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_14BIT;
            break;
        case 29:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_15BIT;
            break;
        case 30:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_15BIT;
            break;
        case 31:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
            break;
        case 32:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
            break;

        default:
            SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
            break;
        }
    }
    SSI_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    SSI_SPI.Init.CLKPhase = SPI_PHASE_1EDGE;
    SSI_SPI.Init.NSS = SPI_NSS_SOFT;
    SSI_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    SSI_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SSI_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    SSI_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    SSI_SPI.Init.CRCPolynomial = 0x0;
    SSI_SPI.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    SSI_SPI.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    SSI_SPI.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    SSI_SPI.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    SSI_SPI.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    SSI_SPI.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    if ((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3))
    SSI_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    else
        SSI_SPI.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_03CYCLE;
    
    SSI_SPI.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    SSI_SPI.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;/* Recommanded setting to avoid glitches */
    SSI_SPI.Init.IOSwap = SPI_IO_SWAP_DISABLE; 

    this->readPositionTimer.reset();
    this->readPositionTimer.start();
    this->calibration = new Calibration((int)numberOfCalibrationPoints);
    double k = 0;
    double b = 0;
    this->readCalibrCoefsFromFlash(&k, &b);
    if (!isnan(k) && !isnan(b))
    {
        this->_k = k;
        this->_b = b;
    }
    int size = 0;
    this->readCalibrPointsSizeFromFlash(&size);
    if (size >= 2 && size <= 256)
    {
        point_t *points = new point_t[size];
        this->readCalibrPointsFromFlash(points, size);
        this->calibration->setPoints(points, size);
        this->calibration->calculateSections();
        delete[] points;
    }
    }
    #endif

#if BOARD_INDEX == 3
    RSSI::RSSI(
     unsigned long spiPrescaler, 
     int SSINumberOfBits,
     unsigned long numberOfCalibrationPoints,
     PinName SCK,
     PinName MISO){
    
    switch(SCK)
    {
        case PB_3:
            _sckPort   = GPIOB;
            _sckPin    = GPIO_PIN_3;
            _sckAF     = GPIO_AF6_SPI3;
            break;
        case PC_10:
            _sckPort   = GPIOC;
            _sckPin    = GPIO_PIN_10;
            _sckAF     = GPIO_AF6_SPI3;
            break;
        case PF_7:
            _sckPort   = GPIOF;
            _sckPin    = GPIO_PIN_7;
            _sckAF     = GPIO_AF5_SPI5;
            break;
        default:
            //default PC_10
            break;
    }
    switch(MISO)
    {
        case PB_4:
            _misoPort   = GPIOB;
            _misoPin    = GPIO_PIN_4;
            _misoAF     = GPIO_AF6_SPI3;
            break;
        case PC_11:
            _misoPort   = GPIOC;
            _misoPin    = GPIO_PIN_11;
            _misoAF     = GPIO_AF6_SPI3;
            break;
        case PF_8:
            _misoPort   = GPIOF;
            _misoPin    = GPIO_PIN_8;
            _misoAF     = GPIO_AF5_SPI5;
            break;
        default:
            //default PC_11
            break;
    }

    numberOfBits = SSINumberOfBits + 1;

    SSI_SPI.Instance = SSI_SPIx;
    SSI_SPI.Init.Mode = SPI_MODE_MASTER;
    SSI_SPI.Init.Direction = SPI_DIRECTION_2LINES;
    switch (numberOfBits)
    {
    case 16:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
        break;
    case 17:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_9BIT;
        break;
    case 18:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_9BIT;
        break;
    case 19:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_10BIT;
        break;
    case 20:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_10BIT;
        break;
    case 21:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_11BIT;
        break;
    case 22:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_11BIT;
        break;
    case 23:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
        break;
    case 24:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
        break;
    case 25:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_13BIT;
        break;
    case 26:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_13BIT;
        break;
    case 27:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_14BIT;
        break;
    case 28:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_14BIT;
        break;
    case 29:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_15BIT;
        break;
    case 30:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_15BIT;
        break;
    case 31:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
        break;
    case 32:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
        break;

    default:
        SSI_SPI.Init.DataSize = SPI_DATASIZE_12BIT;
        break;
    }
    SSI_SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
    SSI_SPI.Init.CLKPhase = SPI_PHASE_1EDGE;
    SSI_SPI.Init.NSS = SPI_NSS_SOFT;
    SSI_SPI.Init.BaudRatePrescaler = spiPrescaler;//SPI_BAUDRATEPRESCALER_64;~2Mhz
    SSI_SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SSI_SPI.Init.TIMode = SPI_TIMODE_DISABLE;
    SSI_SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    SSI_SPI.Init.CRCPolynomial = 0x0;
    SSI_SPI.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    SSI_SPI.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    
    this->readPositionTimer.reset();
    this->readPositionTimer.start();
    this->calibration = new Calibration((int)numberOfCalibrationPoints);
    double k = 0;
    double b = 0;
    this->readCalibrCoefsFromFlash(&k, &b);
    if (!isnan(k) && !isnan(b))
    {
        this->_k = k;
        this->_b = b;
    }
    int size = 0;
    this->readCalibrPointsSizeFromFlash(&size);
    if (size >= 2 && size <= 256)
    {
        point_t *points = new point_t[size];
        this->readCalibrPointsFromFlash(points, size);
        this->calibration->setPoints(points, size);
        this->calibration->calculateSections();
        delete[] points;
    }
}
#endif
RSSI::~RSSI(){
  delete this->calibration;
}

int RSSI::init(void){
    HAL_SPI_RegisterCallback(&SSI_SPI, HAL_SPI_MSPINIT_CB_ID, SSI_HAL_SPI_MspInit);
    HAL_SPI_RegisterCallback(&SSI_SPI, HAL_SPI_MSPDEINIT_CB_ID, SSI_HAL_SPI_MspDeInit);
    uint32_t errorState = HAL_SPI_Init(&SSI_SPI);
    if (errorState != HAL_OK)
    {   
        printf("\n\rRSSI Error during HAL_SPI_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_SPI_RegisterCallback(&SSI_SPI, HAL_SPI_RX_COMPLETE_CB_ID, SSI_HAL_SPI_RxCpltCallback); 
    HAL_SPI_RegisterCallback(&SSI_SPI, HAL_SPI_ERROR_CB_ID, SSI_HAL_SPI_ErrorCallback);
    return HAL_OK;
}

//Decode function from gray code to binary code
uint32_t RSSI::graydecode(uint32_t &gray) 
{
    uint32_t bin;
    for (bin = 0; gray; gray >>= 1) {
      bin ^= gray;
    }
    return bin;
}

float RSSI::readPositionBlocking(){
    std::chrono::microseconds startTime = this->readPositionTimer.elapsed_time();
    #if BOARD_INDEX == 2
        if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
    HAL_SPI_Receive(&SSI_SPI, (uint8_t *)SSIRawBits, 1, 100);
    //wait_us(16);
    //         startTime = this->readPositionTimer.elapsed_time();
    // while (rSSISPITransferState == SSI_DMA_SPI_TRANSFER_WAIT){
    //     if(this->readPositionTimer.elapsed_time() - startTime >= this->readPositionTimeout){
    //         break;
    //     }
    // }
    // if(rSSISPITransferState == SSI_DMA_SPI_TRANSFER_COMPLETE){
        SSIRawBits[0] &= 0x1FFFFFF;   
        data = SSIRawBits[0];
        rSSISPITransferState = SSI_DMA_SPI_TRANSFER_WAIT;
    // }
    uint32_t result = graydecode(data);
            position = result * resolution;
        }
        else{
            HAL_SPI_Receive(&SSI_SPI, (uint8_t *)SSIRawBitsHalfWord, 2, 100);
            // while (rSSISPITransferState == SSI_DMA_SPI_TRANSFER_WAIT){
            //     if(this->readPositionTimer.elapsed_time() - startTime >= this->readPositionTimeout){
            //         break;
            //     }
            // }
            // if(rSSISPITransferState == SSI_DMA_SPI_TRANSFER_COMPLETE){
                data0 = SSIRawBitsHalfWord[0];
                data1 = SSIRawBitsHalfWord[1];
                data = ((0xFFF & data0) << 13) | (0x1FFF & data1);
                rSSISPITransferState = SSI_DMA_SPI_TRANSFER_WAIT;
            // }
            uint32_t result = graydecode(data);
            position = result * resolution;
        }
    #endif
    #if BOARD_INDEX == 3
    HAL_SPI_Receive(&SSI_SPI, (uint8_t *)SSIRawBits, 2, 100);
    // startTime = this->readPositionTimer.elapsed_time();
    // while (rSSISPITransferState == SSI_DMA_SPI_TRANSFER_WAIT){
    //     if(this->readPositionTimer.elapsed_time() - startTime >= this->readPositionTimeout){
    //         break;
    //     }
    // }
    // if(rSSISPITransferState == SSI_DMA_SPI_TRANSFER_COMPLETE){
        data0 = SSIRawBits[0];
        data1 = SSIRawBits[1];
        data = ((0xFFF & data0) << 13) | (0x1FFF & data1);
        rSSISPITransferState = SSI_DMA_SPI_TRANSFER_WAIT;
    // }
    uint32_t result = graydecode(data);
    position = result * resolution;
    #endif
    return position;
}

uint32_t RSSI::startGettingPosition(void){
    uint32_t errorState = HAL_ERROR;
    #if BOARD_INDEX == 2
        if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
            errorState = HAL_SPI_Receive_DMA(&SSI_SPI, (uint8_t *)SSIRawBits, 1);
        }
        else{
            errorState = HAL_SPI_Receive_DMA(&SSI_SPI, (uint8_t *)SSIRawBitsHalfWord, 2);
        }
        //uint32_t errorState = HAL_SPI_Receive_DMA(&SSI_SPI, (uint8_t *)SSIRawBits, 1);
    #endif
    #if BOARD_INDEX == 3
    errorState = HAL_SPI_Receive_DMA(&SSI_SPI, (uint8_t *)SSIRawBits, 2);
    #endif
    return errorState;
}

uint32_t RSSI::getTransferStatus(void){
  uint32_t status = rSSISPITransferState;
  return status;
}

void RSSI::clearTransferStatus(void){
  rSSISPITransferState = SSI_DMA_SPI_TRANSFER_WAIT;
}
float RSSI::getLastPosition(void){
    return this->calcPosition(this->getLastPositionRAW());
}

float RSSI::getLastPositionRAW(void){
    #if BOARD_INDEX == 2
        if((SSI_SPIx == SPI1) || (SSI_SPIx == SPI2) || (SSI_SPIx == SPI3)){
    data = 0x1FFFFFF & SSIRawBits[0];
        }
        else{
            data0 = SSIRawBitsHalfWord[0];
            data1 = SSIRawBitsHalfWord[1];
            data = ((0xFFF & data0) << 13) | (0x1FFF & data1);
        }
    #endif
    #if BOARD_INDEX == 3
    data0 = SSIRawBits[0];
    data1 = SSIRawBits[1];
    data = ((0xFFF & data0) << 13) | (0x1FFF & data1);
    #endif
    uint32_t result = graydecode(data);
    position = result * resolution;
    return position;
}


void RSSI::setCalibrCoefs(double k, double b){
  this->_k = k;
  this->_b = b;
}

void RSSI::getCalibrCoefs(double *k, double *b){
  *k = this->_k;
  *b = this->_b;
}

errorCode_t RSSI::writeCalibrCoefsInFlash(double k, double b){

    //TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    //if (TaskManagerMail != nullptr){
    //    TaskManagerMail->task = Task::WRITE_TO_FLASH_STRAIN_CALIBRATION_COEFS;
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
        internalFlash.setWritingParams(buffer, size, POSITION_CALIBRATION_COEFS_FLASH_OFFSET, true);
        internalFlash.Writing_To_Flash_Through_Buf_Sector();
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.writeToFlash(buffer, size, POSITION_CALIBRATION_COEFS_FLASH_OFFSET);
        break;
    default:
        break;
    }
    delete[] buffer;
    return NO_ERROR;
}

errorCode_t RSSI::readCalibrCoefsFromFlash(double *k, double *b){
  //errorCode_t error = NO_ERROR;
  //read
  int size = 2 * sizeof(double);
  char *buffer = new char[size];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.readInOneSector(buffer, POSITION_CALIBRATION_COEFS_FLASH_OFFSET, size);
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(buffer, size, POSITION_CALIBRATION_COEFS_FLASH_OFFSET);
      break;
  default:
      break;
  }
  basic.writeBytesBufferToValue(buffer, k);
  basic.writeBytesBufferToValue(buffer + 8, b);
  delete[] buffer;
  return NO_ERROR;
}

errorCode_t RSSI::writeCalibrPointsInFlash(point_t *points, int size){ 
  int arraySize = size * sizeof(point_t);
  char *buffer = new char[arraySize];
  for (int i = 0; i < size; i++){
    basic.writeValueToBytesBuffer(buffer, points[i].xRAW, 2 * i * sizeof points[i].xRAW);
    basic.writeValueToBytesBuffer(buffer, points[i].yPhy, 2 * i * sizeof points[i].yPhy + sizeof points[i].yPhy);
  }
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.setWritingParams(buffer, arraySize, POSITION_CALIBRATION_POINTS_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(buffer, arraySize, POSITION_CALIBRATION_POINTS_FLASH_OFFSET);
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
      internalFlash.setWritingParams(sizeBuffer, sizeof(int), POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, true);
      internalFlash.Writing_To_Flash_Through_Buf_Sector();
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.writeToFlash(sizeBuffer, sizeof(int), POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
      break;
  default:
      break;
  }
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t RSSI::readCalibrPointsSizeFromFlash(int *size){
  char *sizeBuffer = new char[sizeof(int)];
  switch (this->_flashOperationType)
  {
  case FLASH_OPERATION_CPU:
      internalFlash.readInOneSector(sizeBuffer, POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET, sizeof(int));
      break;
  case FLASH_OPERATION_DMA:
      internalFlashDMA.readFromFlash(sizeBuffer, sizeof(int), POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET);
      break;
  default:
      break;
  }
  basic.writeBytesBufferToValue(sizeBuffer, size);
  delete[] sizeBuffer;
  return NO_ERROR;
}

errorCode_t RSSI::readCalibrPointsFromFlash(point_t *points, int size){ 
  if (size > 0 && ((uint32_t)size) != 0xFFFFFFFF){
    int arraySize = size * sizeof(point_t);
    char *buffer = new char[arraySize];
    switch (this->_flashOperationType)
    {
    case FLASH_OPERATION_CPU:
        internalFlash.readInOneSector(buffer, POSITION_CALIBRATION_POINTS_FLASH_OFFSET, arraySize);
        break;
    case FLASH_OPERATION_DMA:
        internalFlashDMA.readFromFlash(buffer, arraySize, POSITION_CALIBRATION_POINTS_FLASH_OFFSET);
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

void RSSI::setFlashOperationType(uint32_t flashOperationType){
  this->_flashOperationType = flashOperationType;
}

float RSSI::calcPosition(float code){
    //return (code - ADCNullPointDataBits) * 5.042868 * 0.0001;
    int sections;
    if(this->calibration->getNumberOfSections(sections)){
      return this->calibration->getCalibratedValue(code);
    }
    return (this->_k * code) + this->_b;
}

void RSSI::setSSISensorResolution(double resolution){
    this->resolution = (float)resolution;
}