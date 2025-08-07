#include <mbed.h>
#include "Shared_Definitions.h"
#include "..//lib/FilterTasks/FilterTasks.h"

HAL_StatusTypeDef EnableBackupRAM(){
  #if (BOARD_INDEX == 2)
  /* Enable write access to Backup domain */
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
  /* Wait for Backup domain Write protection disable */
  uint32_t tickstart = HAL_GetTick();
  HAL_StatusTypeDef ret = HAL_OK;
  while((PWR->CR1 & PWR_CR1_DBP) == 0U)
  {
    if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
    {
      ret = HAL_TIMEOUT;
      break;
    }
  }
  /* Enable backup regulator */
  SET_BIT(PWR->CR2, PWR_CR2_BREN);
  tickstart = HAL_GetTick();
  /* Wait for backup regulator is ready */
  while((PWR->CR2 & PWR_CR2_BRRDY) == 0U)
  {
    if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
    {
      ret = HAL_TIMEOUT;
      break;
    }
  }
  /* Enable Vbat and temperature monitoring */
  SET_BIT(PWR->CR2, PWR_CR2_MONEN);
  /* Enable backup RAM clocks */
   __HAL_RCC_BKPRAM_CLK_ENABLE();
  #endif
  #if (BOARD_INDEX == 3)
   __HAL_RCC_PWR_CLK_ENABLE();
  /* Enable write access to Backup domain */
  SET_BIT(PWR->CR1, PWR_CR1_DBP);
  /* Wait for Backup domain Write protection disable */
  uint32_t tickstart = HAL_GetTick();
  HAL_StatusTypeDef ret = HAL_OK;
  while((PWR->CR1 & PWR_CR1_DBP) == 0U)
  {
    if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
    {
      ret = HAL_TIMEOUT;
      break;
    }
  }
  /* Enable backup regulator */
  SET_BIT(PWR->CSR1, PWR_CSR1_BRE);
  tickstart = HAL_GetTick();
  /* Wait for backup regulator is ready */
  while((PWR->CSR1 & PWR_CSR1_BRR) == 0U)
  {
    if((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE + 100)
    {
      ret = HAL_TIMEOUT;
      break;
    }
  }
  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  #endif
  return ret;
} 

void ADC_ADS8320_Calibration_Thread (void){
  //disable any mode
  //GV.Mode = DAC_STATE_NONE;
  //enable strain acquisition
  uint32_t oldEnabledAcq = GV.EnabledAcq;
  GV.EnabledAcq |= ACQ_STRAIN;
  //enable averaging mode
  int oldNumberOfValues = GV.AverageStrain.getNumberOfValues();
  GV.AverageStrain.setNumberOfValues(DEFAULT_STRAIN_ADC_NULL_OFFSET_SUM_SIZE);
  uint32_t oldAverageAcq = GV.AverageAcq;
  GV.AverageAcq |= ACQ_STRAIN;
  //reset averaging process
  GV.AverageStrain.reset();
  //sleep until average value complete
  while (!GV.AverageStrain.getCompleteCount()){
    double time = DEFAULT_STRAIN_ADC_NULL_OFFSET_SUM_SIZE * GV.ConstDisplacementModeParams.ModeFrequency;
    time += time * 0.25;
    ThisThread::sleep_for(std::chrono::milliseconds(static_cast<uint32_t>(time)));
  }
  //save average null value
  GV.ADCNullOffset = GV.AverageStrain.get();
  GV.ConstStrainModeParams.StrainToHold = GV.ConstStrainModeParams.StrainToHold - GV.ADCNullOffset;
  //return values
  GV.EnabledAcq = oldEnabledAcq;
  GV.AverageStrain.setNumberOfValues(oldNumberOfValues);
  GV.AverageAcq = oldAverageAcq;
  GV.AverageStrain.reset();
  //send notification complete adc calibration
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  EthernetAnswerMail->command = COMMAND::TM_ONCE_ADC_CALIBRATION_COMPLETE;
  EthernetAnswerMail->dataLength = 4;
  //error status 0
  basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)0x0);
  EthernetAnswerMailBox.put(EthernetAnswerMail);
}

void Position_Calibration_Thread (void){
  #if(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
  GV.Mode = DAC_STATE_NONE;
  #endif
  uint32_t oldEnabledAcq = GV.EnabledAcq;
  GV.EnabledAcq |= ACQ_DISPLACEMENT;
  //enable averaging mode
  int oldNumberOfValues = GV.AveragePosition.getNumberOfValues();
  GV.AveragePosition.setNumberOfValues(DEFAULT_DISPLACEMENT_NULL_OFFSET_SUM_SIZE);
  uint32_t oldAverageAcq = GV.AverageAcq;
  GV.AverageAcq |= ACQ_DISPLACEMENT;
  //reset averaging process
  GV.AveragePosition.reset();
  //sleep until average value complete
  while (!GV.AveragePosition.getCompleteCount()){
    double time = DEFAULT_DISPLACEMENT_NULL_OFFSET_SUM_SIZE * GV.ConstDisplacementModeParams.ModeFrequency;
    time += time * 0.25;
    ThisThread::sleep_for(std::chrono::milliseconds(static_cast<uint32_t>(time)));
  }
  //save average null value
  GV.positionNullOffset = GV.AveragePosition.get();
  GV.ConstDisplacementModeParams.PositionToHold = GV.ConstDisplacementModeParams.PositionToHold - GV.positionNullOffset;
  //return values
  GV.EnabledAcq = oldEnabledAcq;
  GV.AveragePosition.setNumberOfValues(oldNumberOfValues);
  GV.AverageAcq = oldAverageAcq;
  GV.AveragePosition.reset();
  //send notification complete adc calibration
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  EthernetAnswerMail->command = COMMAND::TM_ONCE_POSITION_CALIBRATION_COMPLETE;
  EthernetAnswerMail->dataLength = 4;
  //error status 0
  basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)0x0);
  EthernetAnswerMailBox.put(EthernetAnswerMail);
}

void Deformation_Calibration_Thread (void){
  uint32_t oldEnabledAcq = GV.EnabledAcq;
  GV.EnabledAcq |= ACQ_DEFORMATION;
  //enable averaging mode
  int oldNumberOfValues = GV.AverageDeformation.getNumberOfValues();
  GV.AverageDeformation.setNumberOfValues(DEFAULT_DEFORMATION_ADC_NULL_OFFSET_SUM_SIZE);
  uint32_t oldAverageAcq = GV.AverageAcq;
  GV.AverageAcq |= ACQ_DEFORMATION;
  //reset averaging process
  GV.AverageDeformation.reset();
  //sleep until average value complete
  while (!GV.AverageDeformation.getCompleteCount()){
    double time = (double)DEFAULT_DEFORMATION_ADC_NULL_OFFSET_SUM_SIZE * GV.ConstDisplacementModeParams.ModeFrequency;
    time += time * 0.25;
    ThisThread::sleep_for(std::chrono::milliseconds(static_cast<uint32_t>(time)));
  }
  //save average null value
  GV.deformationNullOffset = GV.AverageDeformation.get();
  GV.ConstDeformationModeParams.DeformationToHold = GV.ConstDeformationModeParams.DeformationToHold - GV.deformationNullOffset;
  //return values
  GV.EnabledAcq = oldEnabledAcq;
  GV.AverageDeformation.setNumberOfValues(oldNumberOfValues);
  GV.AverageAcq = oldAverageAcq;
  GV.AverageDeformation.reset();
  //send notification complete deformation calibration
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  EthernetAnswerMail->command = COMMAND::TM_ONCE_DEFORMATION_CALIBRATION_COMPLETE;
  EthernetAnswerMail->dataLength = 4;
  //error status 0
  basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)0x0);
  EthernetAnswerMailBox.put(EthernetAnswerMail);
}

void Encoder_and_Motor_Calibration_Thread(void){
  GV.Mode = DAC_STATE_NONE;
  GV.DeformationUnits = DEFORMATION_UNITS_POSITION_RAW;
  uint32_t direction = GV.directionForCalibration;
  uint32_t steps = GV.stepsForCalibration;
  double startPosition = GV.roCurrentDeformation;
  uint32_t calibratinStopped = 0;
  GV.stopCalibration = 0;
  while(steps > 0){
    if(GV.stopCalibration == 0){
      if(steps <= 10){
        if(direction)
          *BV.valvePosition += steps;
        else
          *BV.valvePosition += (-1) * steps;
        motorDriver.setSteps(direction, steps);
        steps = 0;
      }else{
        steps -= 10;
        if(direction)
          *BV.valvePosition += 10;
        else
          *BV.valvePosition += (-1) * 10;
        motorDriver.setSteps(direction, 10);
        ThisThread::sleep_for(1ms);
      }
    }else{
      calibratinStopped = 1;
      steps = 0;
    }
  }
  ThisThread::sleep_for(100ms);
  double endPosition = GV.roCurrentDeformation;
  // GV.DeformationUnits = DEFORMATION_UNITS_MM;
  
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  EthernetAnswerMail->command = COMMAND::TM_ONCE_ENCODER_AND_MOTOR_CALIBRATION_COMPLETE;
  // EthernetAnswerMail->dataLength = 8;
  EthernetAnswerMail->dataLength =  basic.writeValueToBytesBuffer(EthernetAnswerMail->data    , abs(startPosition - endPosition));
  EthernetAnswerMail->dataLength += basic.writeValueToBytesBuffer(EthernetAnswerMail->data + 8, calibratinStopped);
  EthernetAnswerMailBox.put(EthernetAnswerMail);
  calibratinStopped = 0;
  GV.stopCalibration = 0;
}

void setSteps(stepsParams *a){
  // if(taskSemaphore.try_acquire_for(5ms)){
    GV.Mode = DAC_STATE_NONE;
    while(a->steps > 0){
      if(a->steps < a->stepsCountPerCycle){
        if(!a->direction)
          *BV.valvePosition += (GV.valveInvertAxis) * a->steps;
        else
          *BV.valvePosition += ((-1) * GV.valveInvertAxis) * a->steps;
        motorDriver.setSteps(a->direction, a->steps);
        a->steps = 0;
      }else{
        a->steps -= a->stepsCountPerCycle;
        if(!a->direction)
          *BV.valvePosition += (GV.valveInvertAxis) * a->stepsCountPerCycle;
        else
          *BV.valvePosition += ((-1) * GV.valveInvertAxis) * a->stepsCountPerCycle;
        motorDriver.setSteps(a->direction, a->stepsCountPerCycle);
        ThisThread::sleep_for(a->cycleDuration);
      }
    }
    // taskSemaphore.release();
  // }
}

int main() {

  HAL_StatusTypeDef ret = EnableBackupRAM();
  if(ret != HAL_OK){
    printf("Failed to enable Backup RAM!; HAL Error: 0x%X;\n\r", ret);
  }

  /* Enable I-Cache */
  //SCB_EnableICache();

  /* Enable D-Cache */
  //SCB_EnableDCache();
  //SCB_DisableDCache();
  //SCB_DisableICache();
  
  {DeepSleepLock lock;
  SystemTimer.reset();
  SystemTimer.start();

  debug_pc.set_baud(9600);
  printf(
      "Mbed OS version %d.%d.%d;\n",
      MBED_MAJOR_VERSION,
      MBED_MINOR_VERSION,
      MBED_PATCH_VERSION
    );
  printf("Firmware: %s %.1f;\n", FIRMWARE_NAME, FIRMWARE_VERSION);
  
  readGV(GV); // read Global Variables from flash

  printf("S/N: %lld;\n", GV.machineInfo.serialNumber);
  switch (GV.machineInfo.machineType)
  {
  case MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE:
    printf("Machine type: %s;\n", "UniversalHydraulic");
    break;
  case MACHINE_TYPE_ELECTRO_STATIC_MACHINE:
    printf("Machine type: %s;\n", "ElectroStatic");
    break;
  case MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE:
    printf("Machine type: %s;\n", "ElectroHydraulic");
    break;
  default:
    printf("Machine type: %s;\n", "Undefined");
    break;
  }
  
  printf("ProtocolVersion: %#x;\n", GV.machineInfo.ethernetProtocolVersion);

  speedCalibration.getPositionPoints();
  strainSpeedCalibration.getStrainPoints();
  
  displEncoder.setStepValue(GV.encoderStepValue);
  motorDriver.init(GV.motorDriverType, GV.PWMFreq);
  deformEncoder.setStepValue(GV.encoderExtensiaStepValue);
  #if (PROJECT_NAME == PROJECT_NAME_MPD)
  deformEncoder2.setStepValue(GV.encoderExtensiaStepValue);
  #endif
  RSSIReader.setSSISensorResolution(GV.SSISensorResolution);

// #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
//     DigitalOut Com_1_mk_sh(COM_1_MK_PIN); 
//     DigitalOut Com_2_mk_sh(COM_2_MK_PIN);
//     DigitalOut Com_3_mk_sh(COM_3_MK_PIN);
//     DigitalOut Com_4_mk_sh(COM_4_MK_PIN);

//     DigitalOut Command_1_sh(COMMAND_1_PIN);
//     DigitalOut Command_2_sh(COMMAND_2_PIN);
//     DigitalOut Command_3_sh(COMMAND_3_PIN);
//     DigitalOut Command_4_sh(COMMAND_4_PIN);
//     DigitalOut Command_5_sh(COMMAND_5_PIN);
//     DigitalOut Command_6_sh(COMMAND_6_PIN);
//     DigitalOut Command_7_sh(COMMAND_7_PIN);
//     DigitalOut Command_8_sh(COMMAND_8_PIN);

//     DigitalIn Ip_mk_1_sh(IP_MK_1_PIN);
//     DigitalIn Ip_mk_2_sh(IP_MK_2_PIN);
//     DigitalIn Ip_mk_3_sh(IP_MK_3_PIN);
//     DigitalIn Ip_mk_4_sh(IP_MK_4_PIN);
//     DigitalIn Ip_mk_5_sh(IP_MK_5_PIN);
//     DigitalIn Ip_mk_7_sh(IP_MK_7_PIN);
//     DigitalIn Ip_mk_9_sh(IP_MK_9_PIN);
//     DigitalIn Ip_mk_10_sh(IP_MK_10_PIN);
//     cmdMap.registerCommand(COM_1_MK, &Com_1_mk_sh);
//     cmdMap.registerCommand(COM_2_MK, &Com_2_mk_sh);
//     cmdMap.registerCommand(COM_3_MK, &Com_3_mk_sh);
//     cmdMap.registerCommand(COM_4_MK, &Com_4_mk_sh);
//     cmdMap.registerCommand(COMMAND_1, &Command_1_sh);
//     cmdMap.registerCommand(COMMAND_2, &Command_2_sh);
//     cmdMap.registerCommand(COMMAND_3, &Command_3_sh);
//     cmdMap.registerCommand(COMMAND_4, &Command_4_sh);
//     cmdMap.registerCommand(COMMAND_5, &Command_5_sh);
//     cmdMap.registerCommand(COMMAND_6, &Command_6_sh);
//     cmdMap.registerCommand(COMMAND_7, &Command_7_sh);
//     cmdMap.registerCommand(COMMAND_8, &Command_8_sh);

//     cmdMap.registerCommand(IP_MK_1, &Ip_mk_1_sh);
//     cmdMap.registerCommand(IP_MK_2, &Ip_mk_2_sh);
//     cmdMap.registerCommand(IP_MK_3, &Ip_mk_3_sh);
//     cmdMap.registerCommand(IP_MK_4, &Ip_mk_4_sh);
//     cmdMap.registerCommand(IP_MK_5, &Ip_mk_5_sh);
//     cmdMap.registerCommand(IP_MK_7, &Ip_mk_7_sh);
//     cmdMap.registerCommand(IP_MK_9, &Ip_mk_9_sh);
//     cmdMap.registerCommand(IP_MK_10, &Ip_mk_10_sh);
// #endif
// #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN
//     DigitalOut Com_1_mk_sm(COM_1_MK_PIN);
//     DigitalOut Com_2_mk_sm(COM_2_MK_PIN);
//     DigitalOut Com_3_mk_sm(COM_3_MK_PIN);

//     DigitalIn Ip_mk_1_sm(IP_MK_1_PIN);
//     DigitalIn Ip_mk_2_sm(IP_MK_2_PIN);
//     DigitalIn Ip_mk_3_sm(IP_MK_3_PIN);
//     DigitalIn Ip_mk_4_sm(IP_MK_4_PIN);
//     DigitalIn Ip_mk_5_sm(IP_MK_5_PIN);
//     DigitalIn Ip_mk_6_sm(IP_MK_6_PIN);
//     DigitalIn Ip_mk_7_sm(IP_MK_7_PIN);
//     DigitalIn Ip_mk_8_sm(IP_MK_8_PIN);
//     DigitalIn Ip_mk_9_sm(IP_MK_9_PIN);
//     DigitalIn Ip_mk_10_sm(IP_MK_10_PIN);
//     cmdMap.registerCommand(COM_1_MK, &Com_1_mk_sm);
//     cmdMap.registerCommand(COM_2_MK, &Com_2_mk_sm);
//     cmdMap.registerCommand(COM_3_MK, &Com_3_mk_sm);

//     cmdMap.registerCommand(IP_MK_1, &Ip_mk_1_sm);
//     cmdMap.registerCommand(IP_MK_2, &Ip_mk_2_sm);
//     cmdMap.registerCommand(IP_MK_3, &Ip_mk_3_sm);
//     cmdMap.registerCommand(IP_MK_4, &Ip_mk_4_sm);
//     cmdMap.registerCommand(IP_MK_5, &Ip_mk_5_sm);
//     cmdMap.registerCommand(IP_MK_6, &Ip_mk_6_sm);
//     cmdMap.registerCommand(IP_MK_7, &Ip_mk_7_sm);
//     cmdMap.registerCommand(IP_MK_8, &Ip_mk_8_sm);
//     cmdMap.registerCommand(IP_MK_9, &Ip_mk_9_sm);
//     cmdMap.registerCommand(IP_MK_10, &Ip_mk_10_sm);
// #endif

  #if(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
  motorDriver.setParams(&SON, &CLR, &CWL, &CCWL, 10us, 10us, 10us, 10us, GV.enableActiveLevel, GV.CLRActiveLevel, GV.CWLActiveLevel, GV.CCWLActiveLevel);
  motorDriver.setEnable(true);
  motorDriver.setCLR(false);
  motorDriver.setCWLimit(false);
  motorDriver.setCCWLimit(false);
  #endif

  //read chanel

  //Protect init
  initProtects(GV);

  // dataChannels.push_back(RSSIValuesBuffer);
  // dataChannels.push_back(StrainBuffer);
  // dataChannels.push_back(ExtensBuffer1);
  // dataChannels.push_back(TimeBuffer);
  // dataChannels.push_back(CyclesBuffer);

  dataChannels.push_back(new FloatDataChannel<VALUES_BUFFERS_SIZE>(&RSSIValuesBuffer, COMMAND::TM_DISPLACEMENT_VALUES));
  dataChannels.push_back(new FloatDataChannel<VALUES_BUFFERS_SIZE>(&StrainBuffer, COMMAND::TM_LOAD_VALUES));
  dataChannels.push_back(new FloatDataChannel<VALUES_BUFFERS_SIZE>(&ExtensBuffer1, COMMAND::TM_DEFORMATION_VALUES));
  dataChannels.push_back(new Uint64DataChannel<VALUES_BUFFERS_SIZE>(&TimeBuffer, COMMAND::TM_TIME));
  dataChannels.push_back(new Uint64DataChannel<VALUES_BUFFERS_SIZE>(&CyclesBuffer, COMMAND::TM_CYCLE));
  dataChannels.push_back(new FloatDataChannel<DIAGNOSTICS_BUFFERS_SIZE>(&DiagnosticsBuffer, COMMAND::TM_DIAGNOSTICS_VALUES));
  dataChannels.push_back(new Int32DataChannel<VALVE_BUFFERS_SIZE>(&ValveBuffer, COMMAND::TM_VALVE_VALUES));

  if (GV.machineInfo.ethernetProtocolVersion >= DATA_EXCHANGE_PROTOCOL_VERSION_1_2){
    dataChannels.push_back(new Uint32DataChannel<VALUES_BUFFERS_SIZE>(&StepIDBuffer, COMMAND::TM_STEP_ID_VALUES));
    dataChannels.push_back(new Uint32DataChannel<VALUES_BUFFERS_SIZE>(&ModeBuffer, COMMAND::TM_CURRENT_MODE_VALUES));
  }
	reCoDataChannels.push_back(new FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>(&reCoRSSIValuesBuffer, COMMAND::TM_DISPLACEMENT_VALUES));
	reCoDataChannels.push_back(new FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>(&reCoStrainBuffer, COMMAND::TM_LOAD_VALUES));
	reCoDataChannels.push_back(new FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>(&reCoExtensBuffer, COMMAND::TM_DEFORMATION_VALUES));
	reCoDataChannels.push_back(new Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>(&reCoTimeBuffer, COMMAND::TM_TIME));
	reCoDataChannels.push_back(new Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>(&reCoCyclesBuffer, COMMAND::TM_CYCLE));


  ExecutionThread *mainThread = new ExecutionThread();
  EthernetParserThread *ethernetParserThread = new EthernetParserThread(&GV, &GVI, &EthernetMailBox, &EthernetAnswerMailBox, &TaskManagerMailBox, mainThread);
  RemoteControllerParserThread *reCoParserThread
      = new RemoteControllerParserThread(
        &GV, &GVI,
        &RemoteControllerMailBox, &RemoteControllerAnswerMailBox, &TaskManagerMailBox, mainThread);
  AmplitudeTuneThread *amplitudeTuneThread = new AmplitudeTuneThread(&GV, &displMaxMinCalc, &strainMaxMinCalc, &deformationMaxMinCalc);
  EthernetProtocolThread *ethernetProtocolThread = new EthernetProtocolThread(
    &net,
    &GV,
    &dataChannels,
    &EthernetMailBox,
    &EthernetAnswerMailBox,
    &TaskManagerMailBox,
    GV.machineInfo.ethernetProtocolVersion
  );
	RemoteControllerProtocolThread *remotecontrollerProtocolThread = new RemoteControllerProtocolThread(
        DI_UART2_RX_REMOTECONTROLLER,
        DO_UART2_TX_REMOTECONTROLLER,
        115200,
        &GV,
        &reCoDataChannels,
        &RemoteControllerMailBox,
        &RemoteControllerAnswerMailBox,
        &TaskManagerMailBox);


  ThisThread::sleep_for(1000ms);
  //create DACext thread
  Thread MainThread(osPriorityNormal, 4096*4, nullptr, "MainThread");// * 4);
  //create direction DO thread
  //Thread direction_DO;
  //create Ethernet protocol thread
  Thread Ethernet_protocol(osPriorityNormal, 4096*5, nullptr, "EthernetProtocol");// * 4);
  //create Ethernet Parser thread
  Thread Ethernet_Parser(osPriorityNormal, 4096*2, nullptr, "EthernetParser");// * 4);
  //Thread ADCsTM(osPriorityNormal, 4096);
  //create ADC thread
  //Thread ADC_ADS8320;
  //Thread Ethernet_Debug;
  Thread Amplitude_Tune(osPriorityNormal, 1024, nullptr, "AmplitudeTune");
  Thread OneWire_Acquisition(osPriorityAboveNormal, 4096, nullptr, ".OneWireAcq");
    Thread RemoteController_protocol(osPriorityNormal, 4096 * 5, nullptr, "RemoteControllerProtocol");
    Thread RemoteControllerParser(osPriorityNormal, 4096 * 2, nullptr, "RemoteControllerParser");

  //start threads
  osStatus startResult = MainThread.start(callback(mainThread, &ExecutionThread::Execution));
  if(startResult == osErrorNoMemory) printf("Main thread start failed. Out of memory\n");
  //printf("DAC_MCP4921_ThreadPriority: %d;", DAC_MCP4921.get_priority());
  //direction_DO.start(&direction_DO_Thread);
  //printf("direction_DO_ThreadPriority: %d;", direction_DO.get_priority());
  startResult = Ethernet_protocol.start(callback(ethernetProtocolThread, &EthernetProtocolThread::threadExecute));
  if(startResult == osErrorNoMemory) printf("Ethernet protocol thread start failed. Out of memory\n");
  //printf("Ethernet_protocol_ThreadPriority: %d;", Ethernet_protocol.get_priority());
  startResult = Ethernet_Parser.start(callback(ethernetParserThread, &EthernetParserThread::threadExecute));
  if(startResult == osErrorNoMemory) printf("Ethernet parser thread start failed. Out of memory\n");
  //ADCsTM.start(&ADCs_Acquisition_Thread);
  startResult = Amplitude_Tune.start(callback(amplitudeTuneThread, &AmplitudeTuneThread::threadExecute));
  if(startResult == osErrorNoMemory) printf("Amplitude tune thread start failed. Out of memory\n");

  startResult = OneWire_Acquisition.start(&OneWireAcquisition_Thread);
  if(startResult == osErrorNoMemory) printf("Main thread start failed. Out of memory\n");
  
  //printf("Ethernet_Parser_ThreadPriority: %d;", Ethernet_Parser.get_priority());
  //ADC_ADS8320.start(&ADC_ADS8320_Thread);
  //Ethernet_Debug.start(&Ethernet_Debug_Thread);
  //DAC_MCP4921.set_priority(osPriorityRealtime7);
    startResult = RemoteControllerParser.start(callback(reCoParserThread, &RemoteControllerParserThread::threadExecute));
    if (startResult == osErrorNoMemory)
      printf("RemoteController parser thread start failed. Out of memory\n");
    startResult = RemoteController_protocol.start(callback(remotecontrollerProtocolThread, &RemoteControllerProtocolThread::threadExecute));
    if (startResult == osErrorNoMemory)
      printf("RemoteController protocol thread start failed. Out of memory\n");

  //wait for threads end
  while (1){
    TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_get_for(Kernel::wait_for_u32_forever);
    if (TaskManagerMail != nullptr){
      Thread *currentTask = new Thread(osPriorityNormal, 1024);
      switch (TaskManagerMail->task)
      {
      case Task::ADD_FILTER_TYPE_AND_RANGE_AT_END:{
        uint32_t filterType;
        uint32_t dataType;
        int rangeOfFilterBuffer;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &filterType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &dataType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 8, &rangeOfFilterBuffer);
        addFilterAtEnd* addAtEnd;
        addAtEnd = new addFilterAtEnd(dataType, filterType, rangeOfFilterBuffer, mainThread);
        void (addFilterAtEnd::*ptrAdd)() = &addFilterAtEnd::operator();
        currentTask->start(callback(addAtEnd, ptrAdd));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_FILTER_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, addAtEnd->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", addAtEnd->error);
        delete addAtEnd;
        break;
      }
      case Task::ADD_FILTER_TYPE_AND_RANGE_AT_INDEX:{
        uint32_t filterType;
        uint32_t dataType;
        int rangeOfFilterBuffer;
        int index;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &filterType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &dataType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 8, &rangeOfFilterBuffer);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 12, &index);
        addFilterByIndex* addAtIndex;
        addAtIndex = new addFilterByIndex(dataType, filterType, rangeOfFilterBuffer, index, mainThread);
        void (addFilterByIndex::*ptrAdd)() = &addFilterByIndex::operator();
        currentTask->start(callback(addAtIndex, ptrAdd));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_FILTER_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, addAtIndex->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", addAtIndex->error);
        delete addAtIndex;
        break;
      }
      case Task::REMOOVE_FILTER_BY_PARAMETER:{
        uint32_t filterType;
        uint32_t dataType;
        uint32_t parameter;
        int index;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &filterType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &dataType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 8, &parameter);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 12, &index);
        remooveFilterByParameter* remooveByParameter;
        remooveByParameter = new remooveFilterByParameter(dataType, filterType, parameter, index, mainThread);
        void (remooveFilterByParameter::*ptrAdd)() = &remooveFilterByParameter::operator();
        currentTask->start(callback(remooveByParameter, ptrAdd));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_DELETE_FILTER_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, remooveByParameter->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", remooveByParameter->error);
        delete remooveByParameter;
        break;
      }

      case Task::ORDERING_ONE_AFTER_ANOTHER_BY_PARAMETER:{
        uint32_t dataType;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &dataType);
        orderingByParameter* orderingFilters;
        orderingFilters = new orderingByParameter(dataType, mainThread);
        void (orderingByParameter::*ptrAdd)() = &orderingByParameter::operator();
        currentTask->start(callback(orderingFilters, ptrAdd));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_FILTER_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, orderingFilters->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", orderingFilters->error);
        delete orderingFilters;
        break;
      }

      case Task::ADD_SIN_DISPL_NULL_POINT:{
        double dataType;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &dataType);
        sinusDisplNullPointAddDelta* ptrTmp;
        ptrTmp = new sinusDisplNullPointAddDelta(dataType, mainThread);
        void (sinusDisplNullPointAddDelta::*ptrMethod)() = &sinusDisplNullPointAddDelta::operator();
        currentTask->start(callback(ptrTmp, ptrMethod));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_DELTA_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, ptrTmp->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", orderingFilters->error);
        delete ptrTmp;
        break;
      }

      case Task::SET_FILTERING_ACTIVITY_UNIT:{
        uint32_t dataType;
        uint32_t activ;
        uint32_t step;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &dataType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &activ);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 8, &step);
        setFilterActivityUnit* classPtr;
        classPtr = new setFilterActivityUnit(dataType, activ, step, mainThread);
        void (setFilterActivityUnit::*metodPtr)() = &setFilterActivityUnit::operator();
        currentTask->start(callback(classPtr, metodPtr));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_ACTIVITY_STEP_CPMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, classPtr->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", addAtEnd->error);
        delete classPtr;
        break;
      }

      case Task::SET_FILTERING_ACTIVITY_DATA_LINE:{
        uint32_t dataType;
        uint32_t step;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &dataType);
        basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &step);
        setFilterActivityDataLine* classPtr;
        classPtr = new setFilterActivityDataLine(dataType, step, mainThread);
        void (setFilterActivityDataLine::*metodPtr)() = &setFilterActivityDataLine::operator();
        currentTask->start(callback(classPtr, metodPtr));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_ACTIVITY_STEP_CPMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, classPtr->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", addAtEnd->error);
        delete classPtr;
        break;
      }

      case Task::SET_FILTERING_ACTIVITY_ALL:{
        uint32_t step;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &step);
        setFilterActivityAllSteps* classPtr;
        classPtr = new setFilterActivityAllSteps(step, mainThread);
        void (setFilterActivityAllSteps::*metodPtr)() = &setFilterActivityAllSteps::operator();
        currentTask->start(callback(classPtr, metodPtr));        
        currentTask->join();
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_ACTIVITY_STEP_CPMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, classPtr->error);
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        //printf(" errorType-%d \n", addAtEnd->error);
        delete classPtr;
        break;
      }

      case Task::SET_TCYCLE:{
        us_timestamp_t tcycle;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &tcycle);
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_TCYCLE_COMPLETE;
        EthernetAnswerMail->dataLength = 4;
        basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)(mainThread->setTCycle(tcycle)));
        EthernetAnswerMailBox.put(EthernetAnswerMail);
        break;
      }
      case Task::ADC_CALIBRATION:
        //printf("\n\rTask ADC Calibration below case = %d;\n\r", task);
        currentTask->start(&ADC_ADS8320_Calibration_Thread);
        currentTask->join();
        //printf("\n\rTask ADC Calibration after case = %d;\n\r", task);
        break;
      case Task::POSITION_CALIBRATION:
        currentTask->start(&Position_Calibration_Thread);
        currentTask->join();
        break;
      case Task::DEFORMATION_CALIBRATION:
        currentTask->start(&Deformation_Calibration_Thread);
        currentTask->join();
        break;
      case Task::SET_REFERENCE_VOLTAGE:{
        float setVoltage;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &setVoltage);
        //printf("task set volt: %.3f\n\r", setVoltage);
        currentTask->start(callback( Reference_Voltage_Adjuster, &setVoltage));
        currentTask->join();
        break;
      }
      case Task::SET_DISPL_REF_VOLTAGE:{
        float setVoltage;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &setVoltage);
        //printf("task set volt: %.3f\n\r", setVoltage);
        currentTask->start(callback( Reference_Voltage_Adjuster_Displacement, &setVoltage));
        currentTask->join();
        break;
      }
      case Task::CHANGE_ETHERNET_PROTOCOL_VERSION:{
        auto version = ethernetProtocolThread->getProtocolVersion();
        basic.writeBytesBufferToValue(TaskManagerMail->data, &version);
        ethernetProtocolThread->setProtocolVersion(version);
        GV.machineInfo.ethernetProtocolVersion = version;
        break;
      }
      case Task::WRITE_TO_FLASH_STRAIN_CALIBRATION_COEFS:{
        //DEPRECATED
        int offset_write_address = -TaskManagerMail->dataLength;// - 76 - 31;
        //char for_check[] = {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        //                    'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
        //                    'e', 'e', 'e', 'e', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f',
        //                    'f', 'f', 'f', 'f', 'f', 'f', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd',
        //                    'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd',
        //                    'd', 'd', 'd', 'd', 'd', 'd'};
        char *flash_buf = new char[TaskManagerMail->dataLength];// + 76];
        //переменная для старых реализаций (оставлена на всякий случай)
        bool is_rewriting = true;
        //void (*write_func)(char*, int, bool);
        //write_func = &
        basic.writeArrayToArray(TaskManagerMail->data, 0, TaskManagerMail->dataLength, flash_buf, 0);
        //basic.writeArrayToArray(for_check, 0, 76, flash_buf, TaskManagerMail->dataLength);
        internalFlash.setWritingParams(flash_buf, TaskManagerMail->dataLength,//+ 76, 
                                          offset_write_address, is_rewriting);
        //currentTask->start(callback(&internalFlash, &InternalFlash::Writing_To_Flash_Through_Buf_Sector));
        //currentTask->join();
        //send notification complete adc calibration
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        if(EthernetAnswerMail != nullptr){
          EthernetAnswerMail->command = COMMAND::TM_ONCE_WRITE_TO_FLASH_COMPLETE;
          EthernetAnswerMail->dataLength = 4;
          //error status 0
          basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)NO_ERROR);
          EthernetAnswerMailBox.put(EthernetAnswerMail);
        }
        delete[] flash_buf;
        break;
      }
      case Task::SET_EXTENS_REF_VOLTAGE:{
        float setVoltage;
        basic.writeBytesBufferToValue(TaskManagerMail->data, &setVoltage);
        //printf("task set volt: %.3f\n\r", setVoltage);
        currentTask->start(callback( Reference_Voltage_Adjuster_Extens, &setVoltage));
        currentTask->join();
        break;
      }
      case Task::ENCODER_AND_MOTOR_CALIBRATION:{
        currentTask->start(&Encoder_and_Motor_Calibration_Thread);
        currentTask->join();
        break;
      }
      case Task::SET_STEPS:{
        // stepsParams a;
        // basic.writeBytesBufferToValue(TaskManagerMail->data, &a.steps);
        // basic.writeBytesBufferToValue(TaskManagerMail->data + 4, &a.direction);
        // basic.writeBytesBufferToValue(TaskManagerMail->data + 8, &a.stepsCountPerCycle);
        // basic.writeBytesBufferToValue(TaskManagerMail->data + 12, &a.cycleDuration);
        // currentTask->start(callback(setSteps, &a));
        // currentTask->join();
        break;
      }
      case Task::START_TEST_BY_REMOTE_CONTROLLER: {
			EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(5ms);
			if(EthernetAnswerMail != nullptr) {
				EthernetAnswerMail->command = COMMAND::TM_ONCE_START_TEST_PROCESS;
				EthernetAnswerMail->dataLength = 4;
				//error status 0
				basic.writeValueToBytesBuffer(EthernetAnswerMail->data, 0);
				EthernetAnswerMailBox.put(EthernetAnswerMail);
			}
			break;
      }
      case Task::STOP_TEST_BY_REMOTE_CONTROLLER: {
			GV.Mode = DAC_STATE_NONE;
			GV.stopCurrentTestProcess = true;
			GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
			GV.InternalTask = INTERNAL_TASK_NONE;
			EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(5ms);
			if(EthernetAnswerMail != nullptr) {
				EthernetAnswerMail->command = COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE;
				EthernetAnswerMail->dataLength = 4;
				//error status 0
				basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)TestExecutionCompleteStatus::STOP_BY_REMOTE_CONTROL);
				EthernetAnswerMailBox.put(EthernetAnswerMail);
			}
			break;
      }
      default:
        break;
      }
      currentTask->terminate();
      currentTask->free_stack();
      delete currentTask;
      TaskManagerMailBox.free(TaskManagerMail);
    }
    
    ThisThread::sleep_for(10ms);
  }
  MainThread.join();
//    CmdMap.join();
  //direction_DO.join();
  Ethernet_protocol.join();
  Ethernet_Parser.join();
  //ADCsTM.join();
  //Ethernet_Debug.join();
  //ADC_ADS8320.join();
  RemoteController_protocol.join();
  RemoteControllerParser.join();
  }
}
#if BOARD_INDEX == 2
// void DMA2_Stream0_IRQHandler(void)
// {
//   HAL_DMA_IRQHandler(&SPI5_DMA_IRQ_HANDLER);
// }

// void SPI5_IRQHandler(void)
// {
//   HAL_SPI_IRQHandler(&SPI5_IRQ_HANDLER);
// }
#endif
#if BOARD_INDEX == 3
// void DMA2_Stream0_IRQHandler(void)
// {
//   HAL_DMA_IRQHandler(&SPI5_DMA_IRQ_HANDLER);
// }

// void SPI5_IRQHandler(void)
// {
//   HAL_SPI_IRQHandler(&SPI5_IRQ_HANDLER);
// }
#endif
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  printf("Non Maskable Interrupt! Reset \n\r");
  ThisThread::sleep_for(1000ms);
  __NVIC_SystemReset();
  /* USER CODE END NonMaskableInt_IRQn 1 */
}
/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

void WWDG_IRQHandler(void){
  printf("Watchdog Reset \n\r");
  ThisThread::sleep_for(1000ms);
  __NVIC_SystemReset();
}