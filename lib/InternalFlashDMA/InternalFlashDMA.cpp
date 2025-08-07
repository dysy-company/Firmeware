#include "InternalFlashDMA.h"

#ifdef __cplusplus
 extern "C" {
#endif

DMA_HandleTypeDef   DmaHandle;
Semaphore *flashOperation;

void DMA_INSTANCE_IRQHANDLER(void)
{
  /* Check the interrupt and clear flag */
  HAL_DMA_IRQHandler(&DmaHandle);
}

static void TransferComplete(DMA_HandleTypeDef *DmaHandle)
{
  flashOperation->release();
}

static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef __cplusplus
 }
#endif

InternalFlashDMA::InternalFlashDMA(){
    CPU_CACHE_Enable();
    HAL_Init();
    __HAL_RCC_DMA2_CLK_ENABLE();

  /*##-2- Select the DMA functional Parameters ###############################*/
  #if BOARD_INDEX == 2
  DmaHandle.Instance = DMA_INSTANCE;
  DmaHandle.Init.Request = DMA_REQUEST;
  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data alignment : Word */
  DmaHandle.Init.MemDataAlignment = DMA_PDATAALIGN_WORD;    /* memory data alignment : Word     */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;            /* FIFO mode enabled                */
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;   /* FIFO threshold: 1/4 full   */
  DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;              /* Memory burst                     */
  DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;           /* Peripheral burst                 */
  #endif
  #if BOARD_INDEX == 3
  DmaHandle.Init.Channel = DMA_CHANNEL;                     /* DMA_CHANNEL_0                    */
  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; /* Peripheral data alignment : Word */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;    /* memory data alignment : Word     */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;            /* FIFO mode enabled                */
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL; /* FIFO threshold: 1/4 full   */
  DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;              /* Memory burst                     */
  DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;           /* Peripheral burst                 */
  DmaHandle.Instance = DMA_INSTANCE;
  #endif
  
  /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
  

  /*##-4- Initialize the DMA stream ##########################################*/
  if (HAL_DMA_Init(&DmaHandle) != HAL_OK)
  {
    /* Initialization Error */
    printf("Error HAL_DMA_Init\n");
  }

  /*##-5- Select Callbacks functions called after Transfer complete and Transfer error */
  HAL_DMA_RegisterCallback(&DmaHandle, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
  
  /*##-6- Configure NVIC for DMA transfer complete/error interrupts ##########*/
  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriority(DMA_INSTANCE_IRQ, 0, 0);

  /* Enable the DMA STREAM global Interrupt */
  HAL_NVIC_EnableIRQ(DMA_INSTANCE_IRQ);

  /*##-7- Start the DMA transfer using the interrupt mode ####################*/
  /* Configure the source, destination and buffer size DMA fields and Start DMA Stream transfer */
  /* Enable All the DMA interrupts */
  
  this->_flash.init();
  flashOperation = new Semaphore(0);
  this->block = new Semaphore(1);
}

InternalFlashDMA::~InternalFlashDMA(){
  delete flashOperation;
  delete this->block;
}

int InternalFlashDMA::readFromFlash(char *buf, uint32_t size_of_buf, uint32_t flashOffset){
  if(this->block->try_acquire_for(200ms)){
    if((flashOffset + size_of_buf <= END_OF_FLASH) && (flashOffset >= GLOBAL_VARIABLES_FLASH_OFFSET)){
      for (uint32_t i = 0; i < size_of_buf; i++ ){
        buf[i] = *(uint8_t*)(flashOffset + i);
        __DSB();
      }
    }
    this->block->release();
  }else{
    printf("Error during readFromFlash\n");
  }
  return 0;
}

int InternalFlashDMA::readFromFlash(std::string &value, uint32_t offset, uint32_t size){
  std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
  memset(buffer.get(), 0, size);
  int result = this->readFromFlash(buffer.get(), size, offset);
  std::string dummy;
  basic.writeBytesBufferToValue(buffer.get(), &dummy);
  value = dummy;
  return result;
}

template <> void InternalFlashDMA::setParams<std::string>(std::string value, uint32_t offset){
  value.push_back('\0');
  uint32_t size = value.size();
  this->_buf = new char[size];
  std::memset(this->_buf, 0, size);
  basic.writeValueToBytesBuffer(this->_buf, value);
  this->writeToFlash(this->_buf, size, offset);
  delete[] this->_buf;
}

template <> void InternalFlashDMA::setParamsForQueue<std::string>(std::string value, uint32_t offset){
  value.push_back('\0');
  uint32_t size = value.size();
  this->_buf = new char[size];
  std::memset(this->_buf, 0, size);
  basic.writeValueToBytesBuffer(this->_buf, value);
  this->addToQueue(this->_buf, size, offset);
}

template void InternalFlashDMA::setParams<std::string>(std::string, uint32_t);
template void InternalFlashDMA::setParamsForQueue<std::string>(std::string, uint32_t);

void InternalFlashDMA::writeToFlash(char *buf, uint32_t size_of_buf, uint32_t flashOffset){
  this->_size = ((END_OF_FLASH) - (GLOBAL_VARIABLES_FLASH_OFFSET));
  if((this->_size % 4) != 0){
    this->_size = this->_size - (this->_size % 4) + 4;
  }
  uint8_t *data = new uint8_t[this->_size]{};
  if(!data){
    printf("Memory allocation error\n");
  }
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)GLOBAL_VARIABLES_FLASH_OFFSET, (uint32_t)data, (this->_size / 4)) != HAL_OK){
    printf("Error HAL_DMA_Start_IT\n");
  }
  if(!flashOperation->try_acquire_for(1000ms)){
    printf("Error during HAL_DMA_Start_IT\n");
  }
  this->_index = (flashOffset - (GLOBAL_VARIABLES_FLASH_OFFSET));
  for (uint32_t i = 0; i <= size_of_buf - 1; i++ ){
    data[this->_index + i] = buf[i];
  }
  this->eraseSector(GLOBAL_VARIABLES_FLASH_OFFSET & FLASH_SECTOR_ADDRESS_MASK, FLASH_SECTOR_SIZE);
  if (HAL_FLASH_Unlock() != HAL_OK) {
    printf("Error HAL_FLASH_UNLOCK\n");
  }
  this->setPGBit(1);
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)data, (uint32_t)GLOBAL_VARIABLES_FLASH_OFFSET, (this->_size / 4)) != HAL_OK){
    printf("Error HAL_DMA_Start_IT\n");
  }
  if(!flashOperation->try_acquire_for(1000ms)){
    printf("Error during HAL_DMA_Start_IT\n");
  }
  delete[] data;
  this->setPGBit(0);
  if (HAL_FLASH_Lock() != HAL_OK) {
    printf("Error HAL_FLASH_LOCK\n");
  }
}

void InternalFlashDMA::addToQueue(char *buf, uint32_t size_of_buf, uint32_t flashOffset){
  gV_t *gV = mpool.try_alloc_for(10000ms);
  gV->buf = buf;
  gV->size_of_buf = size_of_buf;
  gV->flashOffset = flashOffset;
  GV.try_put_for(10000ms, gV);
}

void InternalFlashDMA::writeToFlashViaQueue(void){
  this->_size = ((END_OF_FLASH) - (GLOBAL_VARIABLES_FLASH_OFFSET));
  if((this->_size % 4) != 0){
    this->_size = this->_size - (this->_size % 4) + 4;
  }
  uint8_t *data = new uint8_t[this->_size]{};
  if(!data){
    printf("Memory allocation error\n");
  }
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)GLOBAL_VARIABLES_FLASH_OFFSET, (uint32_t)data, (this->_size / 4)) != HAL_OK){
    printf("Error HAL_DMA_Start_IT\n");
  }
  if(!flashOperation->try_acquire_for(1000ms)){
    printf("Error during HAL_DMA_Start_IT\n");
  }
  while(!GV.empty()){
    //osEvent evt;
    gV_t *gV;
    if(GV.try_get_for(10000ms, &gV)){
    //if (evt.status == osEventMessage){
      //gV_t *gV = (gV_t*)evt.value.p;
      this->_index = (gV->flashOffset - (GLOBAL_VARIABLES_FLASH_OFFSET));
      for (uint32_t i = 0; i <= gV->size_of_buf - 1; i++ ){
        data[this->_index + i] = gV->buf[i];
      }
      mpool.free(gV);
    }
  }
  this->eraseSector(GLOBAL_VARIABLES_FLASH_OFFSET & FLASH_SECTOR_ADDRESS_MASK, FLASH_SECTOR_SIZE);
  if (HAL_FLASH_Unlock() != HAL_OK) {
    printf("Error HAL_FLASH_UNLOCK\n");
  }
  this->setPGBit(1);
  if (HAL_DMA_Start_IT(&DmaHandle, (uint32_t)data, (uint32_t)GLOBAL_VARIABLES_FLASH_OFFSET, (this->_size / 4)) != HAL_OK){
    printf("Error HAL_DMA_Start_IT\n");
  }
  if(!flashOperation->try_acquire_for(1000ms)){
    printf("Error during HAL_DMA_Start_IT\n");
  }
  delete[] data;
  this->setPGBit(0);
  if (HAL_FLASH_Lock() != HAL_OK) {
    printf("Error HAL_FLASH_LOCK\n");
  }
  delete[] this->_buf;
}

void InternalFlashDMA::eraseSector(uint32_t addr, uint32_t size){
  this->getSector(addr);
  #if BOARD_INDEX == 2
    if (HAL_FLASH_Unlock() != HAL_OK) {
      printf("Error HAL_FLASH_UNLOCK\n");
    }
    FLASH->CR2 &= ~(FLASH_CR_PSIZE | FLASH_CR_SNB);
    FLASH->CR2 |= (FLASH_CR_SER | VoltageRange | (sector << FLASH_CR_SNB_Pos) | FLASH_CR_START);
    while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_QW_BANK2)){}
    FLASH->CR2 &= (~(FLASH_CR_SER | FLASH_CR_SNB));

    SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(GLOBAL_VARIABLES_FLASH_OFFSET & FLASH_SECTOR_ADDRESS_MASK), FLASH_SECTOR_SIZE);
    SCB_InvalidateICache();
    
    if (HAL_FLASH_Lock() != HAL_OK) {
      printf("Error HAL_FLASH_LOCK\n");
    }
  #endif
  #if BOARD_INDEX == 3 
    uint32_t scb_itcmcr = SCB->ITCMCR;
    SCB->ITCMCR &= ~SCB_ITCMCR_EN_Msk;
    __ISB();
    if (HAL_FLASH_Unlock() != HAL_OK) {
      printf("Error HAL_FLASH_UNLOCK\n");
    }

    FLASH->CR &= CR_PSIZE_MASK;
    FLASH->CR |= FLASH_PSIZE_WORD;
    CLEAR_BIT(FLASH->CR, FLASH_CR_SNB);
    FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);
    FLASH->CR |= FLASH_CR_STRT;

    while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET){}

    CLEAR_BIT(FLASH->CR, (FLASH_CR_SER | FLASH_CR_SNB)); 

    SCB_CleanInvalidateDCache_by_Addr((uint32_t *)(GLOBAL_VARIABLES_FLASH_OFFSET & FLASH_SECTOR_ADDRESS_MASK), FLASH_SECTOR_SIZE);
    SCB_InvalidateICache();
    if (HAL_FLASH_Lock() != HAL_OK) {
      printf("Error HAL_FLASH_LOCK\n");
    }
    SCB->ITCMCR = scb_itcmcr;
    __ISB();
    sector = 0;
  #endif
}

void InternalFlashDMA::setPGBit(bool state){
  if(state){
    #if BOARD_INDEX == 2
      FLASH->CR2 |= FLASH_CR_PG;
    #endif
    #if BOARD_INDEX == 3
      FLASH->CR |= FLASH_CR_PG;
    #endif
  }else{
    #if BOARD_INDEX == 2
      FLASH->CR2 &= ~FLASH_CR_PG;
    #endif
    #if BOARD_INDEX == 3
      FLASH->CR &= ~FLASH_CR_PG;
    #endif
  }
}

void InternalFlashDMA::getSector(uint32_t addr){
  #if BOARD_INDEX == 2
    if (addr < (FLASH_BASE + FLASH_BANK_SIZE)) {
            sector = (addr - FLASH_BASE) / FLASH_SECTOR_SIZE;
      } else {
            sector = (addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_SECTOR_SIZE;
    }
  #endif
  #if BOARD_INDEX == 3
    uint32_t tmp = addr - ADDR_FLASH_SECTOR_0;
    if (addr < ADDR_FLASH_SECTOR_4) { // Sectors 0 to 3
        sector += tmp >> 14;
    } else if (addr < ADDR_FLASH_SECTOR_5) { // Sector 4
        sector += FLASH_SECTOR_4;
    } else if (addr < ADDR_FLASH_SECTOR_12) { // Sectors 5 to 11
        sector += 4 + (tmp >> 17);
    } else if (addr < ADDR_FLASH_SECTOR_16) { // Sectors 12 to 15
        tmp = addr - ADDR_FLASH_SECTOR_12;
        sector += 12 + (tmp >> 14);
    } else if (addr < ADDR_FLASH_SECTOR_17) { // Sector 16
        sector += FLASH_SECTOR_16;
    } else { // Sectors 17 to 23
        tmp = addr - ADDR_FLASH_SECTOR_12;
        sector += 16 + (tmp >> 17);
    }
    if(sector > FLASH_SECTOR_11) 
    {
    sector += 4;
    } 
  #endif
}