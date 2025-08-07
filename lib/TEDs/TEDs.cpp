#include <TEDs.h>

#ifdef __cplusplus
 extern "C" {
#endif
USART_HandleTypeDef  TEDs_USART;
DMA_HandleTypeDef   TEDs_DMA_USART_RX;
DMA_HandleTypeDef   TEDs_DMA_USART_TX;

static volatile uint32_t tTEDsUSARTTransferState = TEDs_DMA_USART_TRANSFER_WAIT;

Semaphore *transmitBlock;

void TEDs_HAL_USART_MspInit(USART_HandleTypeDef* USARTHandle){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(USARTHandle->Instance == TEDs_USARTx){
    /* USARTx clock enable */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    #if BOARD_INDEX == 2
    PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
    #endif
    #if BOARD_INDEX == 3
    PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
    #endif
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      printf("\n\rError during HAL_RCCEx_PeriphCLKConfig!\n\r");
    }
    TEDs_USARTx_TX_GPIO_CLK_ENABLE();
    TEDs_USARTx_RX_GPIO_CLK_ENABLE();

    TEDs_USARTx_CLK_ENABLE();
    /* DMA controller clock enable */
    TEDs_DMAx_CLK_ENABLE();
    /**USARTx GPIO Configuration*/
    //USARTx_TX
    GPIO_InitStruct.Pin =       TEDs_USARTx_TX_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = TEDs_USARTx_TX_AF;
    HAL_GPIO_Init(TEDs_USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
    //USARTx_RX
    GPIO_InitStruct.Pin =       TEDs_USARTx_RX_PIN;
    GPIO_InitStruct.Mode =      GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull =      GPIO_NOPULL;
    GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = TEDs_USARTx_RX_AF;
    HAL_GPIO_Init(TEDs_USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    //USARTx_CK
    //GPIO_InitStruct.Pin =       TEDs_USARTx_CK_PIN;
    //GPIO_InitStruct.Mode =      GPIO_MODE_AF_PP;
    //GPIO_InitStruct.Pull =      GPIO_PULLUP;
    //GPIO_InitStruct.Speed =     GPIO_SPEED_FREQ_LOW;
    //GPIO_InitStruct.Alternate = TEDs_USARTx_CK_AF;
    //HAL_GPIO_Init(TEDs_USARTx_CK_GPIO_PORT, &GPIO_InitStruct);

    /* USARTx DMA Init */

    /* USARTx_TX Init */
    TEDs_DMA_USART_TX.Instance =                 TEDs_USARTx_TX_DMA_STREAM;
    #if BOARD_INDEX == 2
    TEDs_DMA_USART_TX.Init.Request =             TEDs_USARTx_TX_DMA_REQUEST;
    #endif
    #if BOARD_INDEX == 3
    TEDs_DMA_USART_TX.Init.Channel =             DMA_CHANNEL_4;
    #endif
    TEDs_DMA_USART_TX.Init.Direction =           DMA_MEMORY_TO_PERIPH;
    TEDs_DMA_USART_TX.Init.PeriphInc =           DMA_PINC_DISABLE;
    TEDs_DMA_USART_TX.Init.MemInc =              DMA_MINC_ENABLE;
    TEDs_DMA_USART_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    TEDs_DMA_USART_TX.Init.MemDataAlignment =    DMA_MDATAALIGN_BYTE;
    TEDs_DMA_USART_TX.Init.Mode =                DMA_NORMAL;
    TEDs_DMA_USART_TX.Init.Priority =            DMA_PRIORITY_LOW;
    TEDs_DMA_USART_TX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    //TEDs_DMA_USART_TX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    //TEDs_DMA_USART_TX.Init.MemBurst =            DMA_MBURST_INC16;
    //TEDs_DMA_USART_TX.Init.PeriphBurst =         DMA_PBURST_INC4;
    if (HAL_DMA_Init(&TEDs_DMA_USART_TX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_TX_Init!\n\r");
    }
    __HAL_LINKDMA(USARTHandle, hdmatx, TEDs_DMA_USART_TX);

    /* USARTx_RX Init */
    TEDs_DMA_USART_RX.Instance =                 TEDs_USARTx_RX_DMA_STREAM;
    #if BOARD_INDEX == 2
    TEDs_DMA_USART_RX.Init.Request =             TEDs_USARTx_RX_DMA_REQUEST;
    #endif
    #if BOARD_INDEX == 3
    TEDs_DMA_USART_RX.Init.Channel =             DMA_CHANNEL_4;
    #endif
    TEDs_DMA_USART_RX.Init.Direction =           DMA_PERIPH_TO_MEMORY;
    TEDs_DMA_USART_RX.Init.PeriphInc =           DMA_PINC_DISABLE;
    TEDs_DMA_USART_RX.Init.MemInc =              DMA_MINC_ENABLE;
    TEDs_DMA_USART_RX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    TEDs_DMA_USART_RX.Init.MemDataAlignment =    DMA_MDATAALIGN_BYTE;
    TEDs_DMA_USART_RX.Init.Mode =                DMA_NORMAL;
    TEDs_DMA_USART_RX.Init.Priority =            DMA_PRIORITY_LOW;
    TEDs_DMA_USART_RX.Init.FIFOMode =            DMA_FIFOMODE_DISABLE;
    //TEDs_DMA_USART_RX.Init.FIFOThreshold =       DMA_FIFO_THRESHOLD_FULL;
    //TEDs_DMA_USART_RX.Init.MemBurst =            DMA_MBURST_INC16;
    //TEDs_DMA_USART_RX.Init.PeriphBurst =         DMA_PBURST_INC4;
   // LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    if (HAL_DMA_Init(&TEDs_DMA_USART_RX) != HAL_OK)
    {
      printf("\n\rError during HAL_DMA_RX_Init!\n\r");
    }
    __HAL_LINKDMA(USARTHandle, hdmarx, TEDs_DMA_USART_RX);
    
    /* DMA interrupt init */
    /* DMAx interrupt configuration */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
    HAL_NVIC_SetPriority( TEDs_USARTx_DMA_TX_IRQn, 
                          TEDs_USARTx_DMA_TX_IRQn_PreemptPriority, 
                          TEDs_USARTx_DMA_TX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(TEDs_USARTx_DMA_TX_IRQn);
    HAL_NVIC_SetPriority( TEDs_USARTx_DMA_RX_IRQn, 
                          TEDs_USARTx_DMA_RX_IRQn_PreemptPriority, 
                          TEDs_USARTx_DMA_RX_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(TEDs_USARTx_DMA_RX_IRQn);
    /* USARTx interrupt Init */
    HAL_NVIC_SetPriority( TEDs_USARTx_IRQn, 
                          TEDs_USARTx_IRQn_PreemptPriority, 
                          TEDs_USARTx_IRQn_SubPriority);
    HAL_NVIC_EnableIRQ(TEDs_USARTx_IRQn);
  }
}

void TEDs_HAL_USART_MspDeInit(USART_HandleTypeDef* USARTHandle)
{

  if(USARTHandle->Instance==TEDs_USARTx)
  {
    /* Peripheral clock disable */
    //TEDs_USARTx_CLK_DISABLE();
    /**USARTx GPIO Configuration
    USARTx_NSS
    USARTx_SCK
    USARTx_MOSI
    */
    TEDs_USARTx_CLK_DISABLE();
    HAL_GPIO_DeInit(TEDs_USARTx_TX_GPIO_PORT, TEDs_USARTx_TX_PIN);
    HAL_GPIO_DeInit(TEDs_USARTx_RX_GPIO_PORT, TEDs_USARTx_RX_PIN);
    /* USARTx DMA DeInit */
    //HAL_GPIO_DeInit(TEDs_USARTx_SCK_GPIO_PORT, TEDs_USARTx_SCK_PIN);
    //HAL_GPIO_DeInit(TEDs_USARTx_MOSI_GPIO_PORT, TEDs_USARTx_MOSI_PIN);
    //HAL_GPIO_DeInit(TEDs_USARTx_CS_GPIO_PORT, TEDs_USARTx_CS_PIN);
    HAL_DMA_DeInit(USARTHandle->hdmatx);
    /* USARTx interrupt Deinit */
    HAL_NVIC_DisableIRQ(TEDs_USARTx_IRQn);
  }
}

void TEDs_HAL_USART_TxCpltCallback(USART_HandleTypeDef *hUSART)
{
  tTEDsUSARTTransferState = TEDs_DMA_USART_TRANSFER_COMPLETE;
  transmitBlock->release();
}
void TEDs_HAL_USART_RxCpltCallback(USART_HandleTypeDef *hUSART)
{
  tTEDsUSARTTransferState = TEDs_DMA_USART_TRANSFER_COMPLETE;
  transmitBlock->release();
}
void TEDs_HAL_USART_TxRxCpltCallback(USART_HandleTypeDef *hUSART)
{
  tTEDsUSARTTransferState = TEDs_DMA_USART_TRANSFER_COMPLETE;
  transmitBlock->release();
}
void TEDs_HAL_USART_ErrorCallback(USART_HandleTypeDef *hUSART)
{
  tTEDsUSARTTransferState = TEDs_DMA_USART_TRANSFER_ERROR;
  transmitBlock->release();
}

#ifdef __cplusplus
 }
#endif

void TEDs::fillUSARTParams(uint32_t baudRate){
    TEDs_USART.Instance = TEDs_USARTx;
    TEDs_USART.Init.BaudRate =  baudRate;
    TEDs_USART.Init.WordLength = USART_WORDLENGTH_8B;
    TEDs_USART.Init.StopBits = USART_STOPBITS_1;
    TEDs_USART.Init.Parity = USART_PARITY_NONE;
    TEDs_USART.Init.Mode = USART_MODE_TX_RX;
    TEDs_USART.Init.CLKPolarity = USART_POLARITY_LOW;
    TEDs_USART.Init.CLKPhase = USART_PHASE_2EDGE;
    TEDs_USART.Init.CLKLastBit = USART_LASTBIT_ENABLE;
    #if BOARD_INDEX == 2
    TEDs_USART.Init.ClockPrescaler = USART_PRESCALER_DIV1;
    TEDs_USART.SlaveMode = USART_SLAVEMODE_DISABLE;
    #endif
}

void TEDs::sharedConstructor(uint32_t baudRate){
    fillUSARTParams(baudRate); 
    this->lastStatus = TEDS_UNDEFINED;
}

TEDs::TEDs(){
    sharedConstructor((uint32_t) 115200);
    init();
    transmitBlock = new Semaphore(0);
}

TEDs::~TEDs(){
    delete transmitBlock;
}

int TEDs::init(void){
  #if BOARD_INDEX == 2
    //*USART_DMA_IRQ_HANDLER = TEDs_DMA_USART_TX;
    //*USART_IRQ_HANDLER = TEDs_USART;
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_MSPINIT_CB_ID, TEDs_HAL_USART_MspInit);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_MSPDEINIT_CB_ID,TEDs_HAL_USART_MspDeInit);
    uint32_t errorState = HAL_USART_Init(&TEDs_USART);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_USART_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_TX_COMPLETE_CB_ID, TEDs_HAL_USART_TxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_RX_COMPLETE_CB_ID, TEDs_HAL_USART_RxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_TX_RX_COMPLETE_CB_ID, TEDs_HAL_USART_TxRxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_ERROR_CB_ID,TEDs_HAL_USART_ErrorCallback);
    
    if (HAL_USARTEx_SetTxFifoThreshold(&TEDs_USART, USART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
      printf("\n\rError during HAL_USARTEx_SetTxFifoThreshold!\n\r");
    }
    if (HAL_USARTEx_SetRxFifoThreshold(&TEDs_USART, USART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
      printf("\n\rError during HAL_USARTEx_SetRxFifoThreshold!\n\r");
    }
    if (HAL_USARTEx_DisableFifoMode(&TEDs_USART) != HAL_OK)
    {
      printf("\n\rError during HAL_USARTEx_DisableFifoMode!\n\r");
    }
    return HAL_OK;
  #endif

  #if BOARD_INDEX == 3
    //*USART_DMA_IRQ_HANDLER = TEDs_DMA_USART_TX;
    //*USART_IRQ_HANDLER = TEDs_USART;
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_MSPINIT_CB_ID, TEDs_HAL_USART_MspInit);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_MSPDEINIT_CB_ID,TEDs_HAL_USART_MspDeInit);
    uint32_t errorState = HAL_USART_Init(&TEDs_USART);
    if (errorState != HAL_OK)
    {   
        printf("\n\rError during HAL_USART_Init!Error code = %d;\n\r", (int)errorState);
        return errorState;
    }
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_TX_COMPLETE_CB_ID, TEDs_HAL_USART_TxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_RX_COMPLETE_CB_ID, TEDs_HAL_USART_RxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_TX_RX_COMPLETE_CB_ID, TEDs_HAL_USART_TxRxCpltCallback);
    HAL_USART_RegisterCallback(&TEDs_USART, HAL_USART_ERROR_CB_ID,TEDs_HAL_USART_ErrorCallback);
    
    return HAL_OK;
  #endif
}

int TEDs::deInit(void){
    
    HAL_USART_UnRegisterCallback(&TEDs_USART, HAL_USART_TX_COMPLETE_CB_ID);
    HAL_USART_UnRegisterCallback(&TEDs_USART, HAL_USART_ERROR_CB_ID);
    uint32_t errorState = 0;//HAL_USART_DeInit(TEDs_USART);
    HAL_USART_UnRegisterCallback(&TEDs_USART, HAL_USART_MSPINIT_CB_ID);
    HAL_USART_UnRegisterCallback(&TEDs_USART, HAL_USART_MSPDEINIT_CB_ID);
    return errorState;
}

void DMA2_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&TEDs_DMA_USART_RX);
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&TEDs_DMA_USART_TX);
}

void USART1_IRQHandler(void){
  //while(1){}
  HAL_USART_IRQHandler(&TEDs_USART);
}

int TEDs::waitEndOfTransfer(int error, int timeout, int ok){
  if(transmitBlock->try_acquire_for(500ms)){
    if(tTEDsUSARTTransferState != TEDs_DMA_USART_TRANSFER_COMPLETE){
      //transmit error
      this->lastStatus = error;
    }
    else{
      //transmit complete
      this->lastStatus = ok;
    }
  }
  else{
    //transmit timeout
    this->lastStatus = timeout;
  }
  return lastStatus;
}

int TEDs::resetWire(void){
    lastStatus = TEDS_UNDEFINED;
    fillUSARTParams(9600);
    HAL_USART_Init(&TEDs_USART);
    uint8_t resetCmd[1] = {0xF0};
    uint8_t presence[1] = {0x00};
    HAL_USART_TransmitReceive_DMA(&TEDs_USART, resetCmd, presence, 1);
    lastStatus = waitEndOfTransfer(TEDS_RESET_TRANSFER_ERROR, TEDS_RESET_TRANSFER_TIMEOUT, TEDS_TRANSFER_OK);
    fillUSARTParams(115200);
    HAL_USART_Init(&TEDs_USART);
    if(lastStatus != TEDS_TRANSFER_OK){
        return lastStatus;
    }
    if (presence[0] == 0xF0){
        lastStatus = TEDS_NOT_DETECTED;
        return lastStatus;
    }
    if (presence[0] == 0xE0){
        lastStatus = TEDS_DETECTED;
        return lastStatus;
    }
    lastStatus = TEDS_NOT_DETECTED;
    return lastStatus;
}

uint8_t TEDs::calculateCRC(uint8_t *rom, uint32_t startIndex = 0){
  uint8_t initCRC = 0;
  for(int i = 0; i < 8; i++){
    uint8_t xorValue = initCRC ^ rom[startIndex + i];
    for(int j = 0; j < 8; j++){
      if((xorValue & ((uint8_t)0x01)) == ((uint8_t)0x01)){
        xorValue = xorValue >> 1;
        xorValue = xorValue ^ 0x8C;
      }else{
        xorValue = xorValue >> 1;
      }
    }
    initCRC = xorValue;
  }
  return initCRC;
}

//bits must have 8 elements length
void TEDs::getBitsFromByte(uint8_t byte, uint8_t *bits) {
	//uint8_t i;
  uint8_t *value = bits;
	for (int i = 0; i < 8; i++) {
		if (byte & 0x01) {
			*value = OW_1;
		} else {
			*value = OW_0;
		}
		value++;
		byte = byte >> 1;
	}
}
//bits must have 8 elements length
uint8_t TEDs::getByteFromBits(uint8_t *bits) {
	uint8_t byte = 0;
  uint8_t *value = bits;
	for (int i = 0; i < 8; i++) {
		byte = byte >> 1;
		if (*value == OW_R_1) {
			byte |= 0x80;
		}
		value++;
	}
	return byte;
}

int TEDs::sendCmd(uint8_t sendReset, uint8_t *command, uint8_t cmdLength) {
	if (sendReset == OW_SEND_RESET) {
		if (this->resetWire() != TEDS_DETECTED) {
			return TEDS_NOT_DETECTED;
		}
	}
  uint16_t size = 8 * cmdLength;
  uint8_t *sendBuf = new uint8_t[size];
	uint8_t *cmdRef = command;
  for (int i = 0; i < cmdLength; i++){
    this->getBitsFromByte(*(cmdRef + i), sendBuf + i);
  }
  HAL_USART_Transmit_DMA(&TEDs_USART, sendBuf, size);
  lastStatus = this->waitEndOfTransfer(TEDS_CMD_TRANSFER_ERROR, TEDS_CMD_TRANSFER_TIMEOUT, TEDS_TRANSFER_OK);
  delete[] sendBuf;
  return lastStatus;
}
//TODO
int TEDs::readData(uint8_t *data, uint8_t dataLength){
  uint16_t size = 8 * dataLength;
  uint8_t *sendBuf = new uint8_t[size];
  uint8_t *recvBuf = new uint8_t[size];
	//uint8_t *dataRef = data;
  for (int i = 0; i < dataLength; i++){
    this->getBitsFromByte(OW_READ_SLOT, sendBuf + i);
  }
  HAL_USART_TransmitReceive_DMA(&TEDs_USART, sendBuf, recvBuf, size);
  lastStatus = this->waitEndOfTransfer(TEDS_READ_TRANSFER_ERROR, TEDS_READ_TRANSFER_TIMEOUT, TEDS_TRANSFER_OK);
  for (int i = 0; i < dataLength; i++){
    data[i] = this->getByteFromBits(recvBuf + i);
  }
  delete[] sendBuf;
  delete[] recvBuf;
  return lastStatus;
}