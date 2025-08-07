#include "ExecutionT.h"

// void DAC_MCP4921_Thread(void){
//   ExecutionThread *execution = new ExecutionThread();
//   execution->Execution();
// }

#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
void ExecutionThread::fallEdgeEncoder(void){
  if (GV.WorkMode == WORK_MODE_SETTING_SAMPLE){ 
 if(!HwCmdFb2.read()){
   if (HwCmdFb1.read()){
     EncoderBuffer.push(true);
   }else{
     EncoderBuffer.push(false);
   }
 }
}
}
#endif

#if ((REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION) || REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)

void ExecutionThread::fallMoveUpState(void){
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  fallMoveUpTimeout.attach(callback(this, &ExecutionThread::fallMoveUp), 10ms);
}

void ExecutionThread::fallMoveUp(void){
  if(!moveUp.read()){
    #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
    if(!moveEnable.read()){
      if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
        if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
          GV.ConstDisplacementModeParams.PositionToHold = DBL_MAX * GV.pistonMode;
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.Speed = GV.displButtonRegularSpeed;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          moveUpState = true;
          buttonMode = true;
        }
      }
    }
    #else
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
        GV.ConstDisplacementModeParams.PositionToHold = DBL_MAX * GV.pistonMode;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.Speed = GV.displButtonRegularSpeed;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = true;
      }
    }
    #endif
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ExecutionThread::riseMoveUpState(void){
  // moveUp.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  riseMoveUpTimeout.attach(callback(this, &ExecutionThread::riseMoveUp), 10ms);
}

void ExecutionThread::riseMoveUp(void){
  if(moveUp.read()){
    #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
    if(moveUpState){
      if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
        if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000){
          GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition;
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          moveUpState = false;
          buttonMode = false;
        }
      }
    }
    #else
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000){
        GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = false;
      }
    }
    #endif
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ExecutionThread::fallMoveDownState(void){
  // moveDown.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  fallMoveDownTimeout.attach(callback(this, &ExecutionThread::fallMoveDown), 10ms);
}

void ExecutionThread::fallMoveDown(void){
  // moveDown.enable_irq();
  if(!moveDown.read()){
    #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
    if(!moveEnable.read()){
      if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
        if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
          GV.ConstDisplacementModeParams.PositionToHold = (-1) * DBL_MAX * GV.pistonMode;
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.Speed = GV.displButtonRegularSpeed;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          moveDownState = true;
          buttonMode = true;
        }
      }
    }
    #else
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
        GV.ConstDisplacementModeParams.PositionToHold = (-1) * DBL_MAX * GV.pistonMode;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.Speed = GV.displButtonRegularSpeed;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = true;
      }
    }
    #endif
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ExecutionThread::riseMoveDownState(void){
  // moveDown.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  riseMoveDownTimeout.attach(callback(this, &ExecutionThread::riseMoveDown), 10ms);
}

void ExecutionThread::riseMoveDown(void){
  // moveDown.enable_irq();
  if(moveDown.read()){
    #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION)
    if(moveDownState){
      if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
        if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000){
          GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition;
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          moveDownState = false;
          buttonMode = false;
        }
      }
    }
    #else
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000){
        GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = false;
      }
    }
    #endif
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
#endif

#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)
void ExecutionThread::fallMoveUpFastState(void){
  // moveUpFast.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  fallMoveUpFastTimeout.attach(callback(this, &ExecutionThread::fallMoveUpFast), 1ms);
}

void ExecutionThread::fallMoveUpFast(void){
  // moveUpFast.enable_irq();
  if(!moveUpFast.read()){
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
        GV.ConstDisplacementModeParams.PositionToHold = DBL_MAX * GV.pistonMode;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.Speed = GV.displButtonFastSpeed;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = true;
      }
    }
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ExecutionThread::fallMoveDownFastState(void){
  // moveDownFast.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  fallMoveDownFastTimeout.attach(callback(this, &ExecutionThread::fallMoveDownFast), 1ms);
}

void ExecutionThread::fallMoveDownFast(void){
  // moveDownFast.enable_irq();
  if(!moveDownFast.read()){
    if (GV.WorkMode != WORK_MODE_TEST_IN_PROCESS){
      if((GV.Mode == DAC_STATE_DISP_CONST || GV.Mode == DAC_STATE_NONE) && SystemTimer.elapsed_time().count() >= 10000000 && GV.InternalTask == INTERNAL_TASK_NONE){
        GV.ConstDisplacementModeParams.PositionToHold = (-1) * DBL_MAX * GV.pistonMode;
        GV.ConstDisplacementModeParams.speedEnable = false;
        GV.ConstDisplacementModeParams.Speed = GV.displButtonFastSpeed;
        GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        GV.Mode = DAC_STATE_DISP_CONST;
        buttonMode = true;
      }
    }
  }
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void ExecutionThread::fallStopButtonState(void){
  // StopButton.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
  fallStopButtonTimeout.attach(callback(this, &ExecutionThread::fallStopButton), 1ms);
}

void ExecutionThread::fallStartButtonState(void){
  // StartButton.disable_irq();
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  fallStartButtonTimeout.attach(callback(this, &ExecutionThread::fallStartButton), 1ms);
}

// void ExecutionThread::resetEmergencyFlag(void){
//   emergencyFlag.clear(0x1);
// }

// void ExecutionThread::startButtonFlag(void){
//   startTestProcessFlag.clear(0x1);
// }

void ExecutionThread::fallStopButton(void)
{
  // StopButton.enable_irq();
  if(!StopButton.read()){   
    GV.Mode = DAC_STATE_NONE;
    GV.stopCurrentTestProcess = true;
    GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
    GV.InternalTask = INTERNAL_TASK_NONE;
    sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::STOP_BY_REMOTE_CONTROL);
  }
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ExecutionThread::fallStartButton(void){
  // StartButton.enable_irq();
  if(!StartButton.read()){
    sendNotification(COMMAND::TM_ONCE_START_TEST_PROCESS , (uint32_t)0x0);
  }
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
#endif

void ExecutionThread::Execution (void){
  while(1) {
    Watchdog::get_instance().kick();
    //debugPin.write(1);
    //debugPin.write(0);
    startTimerValue = frequencyTimer.elapsed_time();
    this->averageAndDecimate();
    this->updateValues();
    this->internalTaskManager();
    switch(GV.StrainUnits){
      case STRAIN_UNITS_KN:{
        //strain protection
        this->strainProtectStage1Execute();
        this->strainProtectStage2Execute();
        this->strainProtectEdgeExecute();
        if (buttonMode){
          this->strainButtonProtectExecute();
        }
        break;
      }
      case STRAIN_UNITS_RAW:{
        //protection disable
        break;
      }
      case STRAIN_UNITS_DEFORMATION_RAW:{
        //protection disable
        break;
      }
      default:
        //protection disable
        break;
    }
    switch (GV.PositionUnits)
    {
    case POSITION_UNITS_MM:{
      //displacement protection 
      this->displacementProtectStage1Execute();
      this->displacementProtectStage2Execute();
      this->displacementProtectEdgeExecute();
      break;
    }
    case POSITION_UNITS_STRAIN_MM:{
      //displacement protection 
      this->displacementProtectStage1Execute();
      this->displacementProtectStage2Execute();
      this->displacementProtectEdgeExecute();
      break;
    }
    case POSITION_UNITS_RAW:{
      //protection disable
      break;
    }
    case POSITION_UNITS_STRAIN_RAW:{
      //protection disable
      break;
    }
    default:
      //protection disable
      break;
    }
    switch (GV.DeformationUnits)
    {
    case DEFORMATION_UNITS_MM:
      //deformation protection
      this->deformationProtectStage1Execute();
      this->deformationProtectStage2Execute();
      this->deformationProtectEdgeExecute();
      break;
    case DEFORMATION_UNITS_RAW:
      //protection disable
      break;
    case DEFORMATION_UNITS_STRAIN_RAW:
      //protection disable
      break; 
    default:
      //protection disable
      break;
    }
    
    //update current mode
    DACState = GV.Mode;
    this->modeExecute();
    prevDACState = DACState;
    prevDACVoltage = DACVoltage;
    //GV.DeltaPoints = DACFrequency;
    //debugPin.write(0);
    //debugPin.write(1);
    this->startAcq();
    this->checkTimeAndWait();
    //debugPin.write(1);
    //debugPin.write(0);
    // if(k){
    //   TestOut1.write(1);
    //   TestOut2.write(1);
    //   TestOut3.write(1);
    //   TestOut4.write(1);
    //   TestOut5.write(1);
    //   TestOut6.write(1);
    //   TestOut7.write(1);
    // }else{
    //   TestOut1.write(0);
    //   TestOut2.write(0);
    //   TestOut3.write(0);
    //   TestOut4.write(0);
    //   TestOut5.write(0);
    //   TestOut6.write(0);
    //   TestOut7.write(0);
    // }
    // this->k = !this->k;
  }
}
ExecutionThread::ExecutionThread(){
  this->readParamsFromFlash();
  this->constDisplSpeedToSet = 5.0;//mm/sec by default
  delayedSetConstDisplSpeed.attach(callback(this, &ExecutionThread::setConstDisplSpeed), 5000ms);
  //DEPRECATED:reset emergency stop pin
  //HwCmd5.write(1);
  
  strainButtonProtect.setLowerLimit(GV.strainButtonLowerLimit);
  strainButtonProtect.setUpperLimit(GV.strainButtonUpperLimit);
  strainButtonProtect.setValuesCount(3);
  strainButtonProtect.setMode(PROTECT_MODE_CONTINIUS);
  
  #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
  EncoderA.fall(callback(this, &ExecutionThread::fallEdgeEncoder));
  #endif

  #if ((REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION) || (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION) || REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)
  moveUp.fall(callback(this, &ExecutionThread::fallMoveUpState));
  moveUp.rise(callback(this, &ExecutionThread::riseMoveUpState));
  moveDown.fall(callback(this, &ExecutionThread::fallMoveDownState));
  moveDown.rise(callback(this, &ExecutionThread::riseMoveDownState));
  #endif
  
  #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP)
  moveUpFast.fall(callback(this, &ExecutionThread::fallMoveUpFastState));
  moveUpFast.rise(callback(this, &ExecutionThread::riseMoveUpState));
  moveDownFast.fall(callback(this, &ExecutionThread::fallMoveDownFastState));
  moveDownFast.rise(callback(this, &ExecutionThread::riseMoveDownState));
  
  #if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED

  #else
  StopButton.fall(callback(this, &ExecutionThread::fallStopButtonState));
  #endif
  StartButton.fall(callback(this, &ExecutionThread::fallStartButtonState));
  #endif

  //GV.ConstStrainModeParams.MaxSpeed = GV.ConstStrainModeParams.delta * 1000 / (GV.TcycleTime * 20); //TODO
  //GV.ConstDisplacementModeParams.MaxSpeed = GV.ConstDisplacementModeParams.delta * 1000 / (GV.TcycleTime * 20); //TODO
  //Config DAC
  DACext.setConfig(
                GV.DACOut,  
                GV.DACInBufCtrl, 
                GV.DACGain, 
                GV.DACOutPwrDownCtrl,
                GV.DACVref);
  #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
  ADCext.setVref(GV.ADCVref);
  #else
  ADS869xStrain.setVref(GV.ADCVref1);
  #endif
  ADCextExtens.setVref(GV.ADCExtensVref);
  ADS869xExtens.setVref(GV.ADCExtensVref1);
  //DACext.setVoltage(DACVoltage);
  valveVoltageToSend = DACVoltage;
  sinDispCyclesTrigger = new Trigger(TRIGGER_RISE_EDGE);
  sinStrainCyclesTrigger = new Trigger(TRIGGER_RISE_EDGE);
  sinDeformCyclesTrigger = new Trigger(TRIGGER_RISE_EDGE);
  zeroCrossed = new Trigger(TRIGGER_RISE_EDGE);
  piDivTwoCrossed = new Trigger(TRIGGER_RISE_EDGE);
  piCrossed = new Trigger(TRIGGER_RISE_EDGE);
  treePiDivTwoCrossed = new Trigger(TRIGGER_RISE_EDGE);
  #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
      encoderPermissionButton = new Trigger(TRIGGER_RISE_EDGE);
  #endif
  positiveStrainZeroCrossed = new Trigger(TRIGGER_RISE_EDGE);
  negativeStrainZeroCrossed = new Trigger(TRIGGER_RISE_EDGE);
  constDisplacementPID = new PID(
    GV.ConstDisplacementModeParams.PIDParams.Kp, 
    GV.ConstDisplacementModeParams.PIDParams.Ki, 
    GV.ConstDisplacementModeParams.PIDParams.Kd);
  sinDisplacementPID = new PID(
    GV.SINDisplacementModeParams.PIDParams.Kp,
    GV.SINDisplacementModeParams.PIDParams.Ki,
    GV.SINDisplacementModeParams.PIDParams.Kd
  );
  constStrainPID = new PID(
    GV.ConstStrainModeParams.PIDParams.Kp, 
    GV.ConstStrainModeParams.PIDParams.Ki, 
    GV.ConstStrainModeParams.PIDParams.Kd);
  sinStrainPID = new PID(
    GV.SINStrainModeParams.PIDParams.Kp,
    GV.SINStrainModeParams.PIDParams.Ki,
    GV.SINStrainModeParams.PIDParams.Kd);
  constDeformationPID = new PID(
    GV.ConstDeformationModeParams.PIDParams.Kp, 
    GV.ConstDeformationModeParams.PIDParams.Ki, 
    GV.ConstDeformationModeParams.PIDParams.Kd);
  sinDeformationPID = new PID(
    GV.SINDeformationModeParams.PIDParams.Kp,
    GV.SINDeformationModeParams.PIDParams.Ki,
    GV.SINDeformationModeParams.PIDParams.Kd);
  dataFiltersSet = new FilterCollection(&position, GV.filteredCurrentDisplacement, typeOfData::DISPLACEMENT, 
                                    &strain, GV.filteredCurrentStrain, typeOfData::STRAIN,
                                    &deformation, GV.filteredCurrentDeformation, typeOfData::DEFORMATION);
  switcherFilterSet = new SwitchersSet(&position, GV.filteredCurrentDisplacement, &strain, GV.filteredCurrentStrain, &deformation, GV.filteredCurrentDeformation);
  //initialize direction pins
  //InterruptIn Button(B1);//
  //led2.write(Button.read());
  //Button.rise(callback(this, &ExecutionThread::setConstDisplMode));
  #if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE)
  LimSw = new LimitSwitch(GV.LimitSwitchPolarity1, 1, &switch1);
  #endif
  #if (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO)
  LimSw = new LimitSwitch(GV.LimitSwitchPolarity1, GV.LimitSwitchPolarity2, 2, &switch1, &switch2);
  #endif
  #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
  LimSw->setLimSwFunc(
    callback(this, &ExecutionThread::CheckLimSwState),
    callback(this, &ExecutionThread::LimitSwitchFallMode)
  );
  #endif
  #if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
  LimSwDoors = new LimitSwitch(GV.LimSwLeftDoorPolarity, GV.LimSwRightDoorPolarity, 2, &leftDoorSwitch, &rightDoorSwitch);
  LimSwDoors->setLimSwFunc(
    callback(this, &ExecutionThread::checkLimSwLeftDoorRiseState),
    callback(this, &ExecutionThread::checkLimSwLeftDoorFallState),
    callback(this, &ExecutionThread::checkLimSwRightDoorRiseState),
    callback(this, &ExecutionThread::checkLimSwRightDoorFallState)
  );
  #endif
  #if (EMERGENCY_STOP_TYPE == EMERGENCY_STOP_TYPE_BUTTON)
  if (GV.EmergencyStopPolarity)
  {
    emergencyStopButton.rise(callback(this, &ExecutionThread::CheckEmergencyStopState));
  }else
  {
    emergencyStopButton.fall(callback(this, &ExecutionThread::CheckEmergencyStopState));
  }
  #endif
  directHigh.write(1);
  reverseHigh.write(0);
  debugPin.write(0);
  direction = new Direction(directHigh, reverseHigh, &GV);
  // //create pulse mode class
  // pulseMode = new PulseMode(
  //   DACext, 
  //   directHigh, 
  //   reverseHigh, 
  //   &GV
  // );
  //pulseMode->reset();
  //staticTest = new StaticTest(&GV);
  SBD_MS = new SampleBreakDetection(SBD_MODE_PERCENT_OF_MAX_STRAIN);
  SBD_DF = new SampleBreakDetection(SBD_MODE_DYNAMIC_FALL);
  //start timer for loop
  frequencyTimer.start();
  #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
  ADCext.init();
  #else
  ADS869xStrain.init();
  #endif
  ADCextExtens.init();
  #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    ADS869xExtens.init();
  #endif
  #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
  switch (GV.StrainUnits)
  {
  case STRAIN_UNITS_KN:
    #if (BATTERY == BATTERY_AVAILABLE)
    strain = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getCodeBlocking()) - *BV.strainNullOffset - GV.ADCNullOffset;
    #else
    strain = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getCodeBlocking()) - GV.ADCNullOffset;
    #endif
    break;
  case STRAIN_UNITS_RAW:
    strain = ADCext.getCodeBlocking();
    break;
  //default KN
  default:
    strain = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getCodeBlocking()) - GV.ADCNullOffset;
    break;
  }
  #else
  // switch (GV.StrainUnits)
  // {
  // case STRAIN_UNITS_KN:
  //   ADS869xStrain.startTransfer(true);
  //   strain = GV.strainInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode()) - GV.ADCNullOffset;
  //   break;
  // case STRAIN_UNITS_RAW:
  //   ADS869xStrain.startTransfer(true);
  //   strain = ADS869xStrain.getLastCode();
  //   break;
  // //default KN
  // default:
  //   ADS869xStrain.startTransfer(true);
  //   strain = GV.strainInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode()) - GV.ADCNullOffset;
  //   break;
  // }
  #endif
  GV.roCurrentStrain = strain;
  // GV.roCurrentStrainTime = SystemTimer.elapsed_time().count();
  //DEFORMATION
  switch (GV.DeformationUnits)
  {
  case DEFORMATION_UNITS_MM:
    deformation = GV.deformationInvertAxis * ADCextExtens.calcDeformation(ADCextExtens.getCodeBlocking()) - GV.ADCExtensNullOffset;
    break;
  case DEFORMATION_UNITS_RAW:
    deformation = ADCextExtens.getCodeBlocking();
    break;
  //default MM
  default:
    deformation = ADCextExtens.calcDeformation(ADCextExtens.getCodeBlocking());
    break;
  }
  GV.roCurrentDeformation = deformation_DIRECTING;
  // GV.roCurrentDeformationTime = SystemTimer.elapsed_time().count();
  //POSITION
  if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_DIGITAL_RSSI){
    RSSIReader.init();
    ThisThread::sleep_for(100ms);
    position = GV.positionInvertAxis * RSSIReader.readPositionBlocking() - GV.positionNullOffset;
    ThisThread::sleep_for(100ms);
    position = GV.positionInvertAxis * RSSIReader.readPositionBlocking() - GV.positionNullOffset;
  }
  if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_ENCODER){
    if(!std::isnan(GV.SSINullOffset)){
      RSSIReader.init();
      while(!(GV.SSIPositionOffset > 0.0 && GV.SSIPositionOffset < 10000.0)){
        // RSSIReader.clearTransferStatus();
        // RSSIReader.startGettingPosition();
        // //ThisThread::sleep_for(10ms);
        // while (RSSIReader.getTransferStatus() != SSI_DMA_SPI_TRANSFER_COMPLETE){}
        // if(RSSIReader.getTransferStatus() == SSI_DMA_SPI_TRANSFER_COMPLETE){
        //   RSSIReader.clearTransferStatus();
        //   GV.SSIPositionOffset = RSSIReader.getLastPosition();
        // }else{
        //   RSSIReader.clearTransferStatus();
        // }
        GV.SSIPositionOffset = RSSIReader.readPositionBlocking();
        count++;
        if(count > 1){
           __NVIC_SystemReset();
          break;
        }
        wait_us(100);
      }
       printf("\ncount = %d\n", count);
      position = GV.SSIPositionOffset - GV.SSINullOffset - GV.positionNullOffset;
    }else{
      #if (BATTERY == BATTERY_AVAILABLE)
      displEncoder.setPulesCount(*BV.encoderPulses);
      position = GV.positionInvertAxis * displEncoder.getLastPosition() - GV.positionNullOffset;
      #else
      position = 0;
      #endif
    }
  }
  GV.roCurrentPosition = position;
  // GV.roCurrentPositionTime = SystemTimer.elapsed_time().count();
  //SET HOLD CURRENT POSITION
  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
    GV.ConstDisplacementModeParams.PositionToHold = displacement_DIRECTING;
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
  }
  if((GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE) || (GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE)){
    this->setNoneMode();
  }
  //SET CURRENT POSITION TO AVERAGE
  GV.AveragePosition.set(position);
  GV.AverageStrain.set(strain);
  GV.AverageDeformation.set(deformation);
  //SET NUMBER OF VALUES
  GV.AveragePosition.setNumberOfValues(DEFAULT_DISPLACEMENT_SUM_SIZE);
  GV.AverageStrain.setNumberOfValues(DEFAULT_STRAIN_SUM_SIZE);
  GV.AverageDeformation.setNumberOfValues(DEFAULT_DEFORMATION_SUM_SIZE);

  Watchdog &watchdog = Watchdog::get_instance();
  if (GV.EnabledAcq & ACQ_DISPLACEMENT){
      if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_DIGITAL_RSSI){
        RSSIReader.clearTransferStatus();
        RSSIReader.startGettingPosition();
      }
    }
  if (GV.EnabledAcq & ACQ_STRAIN){
      #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
      ADCext.clearTransferStatus();
      ADCext.startGettingCode();
      #else
      ADS869xStrain.clearTransferStatus();
      // ADS869xStrain.startTransfer(false);
      #endif
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      ADS869xExtens.clearTransferStatus();
      #endif
    }
  if (GV.EnabledAcq & ACQ_DEFORMATION){
      ADCextExtens.clearTransferStatus();
      ADCextExtens.startGettingCode();
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      ADS869xExtens.clearTransferStatus();
      ADS869xExtens.startTransfer(true);
      ADS869xExtens.startTransfer2(true);
      ADS869xExtens.startTransfer3(true);
      #endif
    }
    #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS869x)
    ADS869xStrain.transferBlocking();
    ADS869xStrain.setRange(ADS869xStr_EXTERNAL_REF_DISABLED, ADS869xStr_P_1_25);
    #endif
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    ADS869xExtens.setRange(ADS869xExt_EXTERNAL_REF_DISABLED, ADS869xExt_PM_2_5);
    ADS869xExtens.transferBlocking();
    ADS869xExtens.setRange(ADS869xExt_EXTERNAL_REF_DISABLED, ADS869xExt_PM_2_5);
    ADS869xExtens.transferBlocking2();
    ADS869xExtens.setRange(ADS869xExt_EXTERNAL_REF_DISABLED, ADS869xExt_PM_2_5);
    ADS869xExtens.transferBlocking3();
    #endif
    if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
      DACext.setVoltage(DACVoltage);
    }
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    DACRefVoltage = GV.ReferenceVoltage / REFERENCE_VOLTAGE_ADJUSTER_VOLTAGE_MULTIPLAYER;
    DACExtRefVoltage = GV.ExtensRefVoltage / REFERENCE_VOLTAGE_ADJUSTER_EXTENS_VOLTAGE_MULTIPLAYER;
    DACext.setVoltage(DACRefVoltage, SS_DAC_CS);
    DACext.setVoltage(DACExtRefVoltage, Tenzo_ADC_CS);
    #endif
    watchdog.start(WATCHDOG_TIMEOUT_MS);
    GV.Tcycle.attach(callback(this, &ExecutionThread::calculateNextPoint), 
                                    std::chrono::microseconds(GV.TcycleTime));
                                  //GV.SINDisplacementModeParams.Tcycle*1000);
    // led2.write(1);
    delayedAction.attach(callback(this, &ExecutionThread::disableLED2), 800us);
    ThisThread::sleep_for(100ms);
    // led3.write(1);
    delayedAction.attach(callback(this, &ExecutionThread::disableLED3), 800us);
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
      delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 2000ms);
    #endif
}

/*
Example of using:

delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 2000ms);

*/
void ExecutionThread::setConstDisplMode(void){
  GV.ConstDisplacementModeParams.speedEnable = false;
  GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition;
  GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
  GV.Mode = DAC_STATE_DISP_CONST;
}

void ExecutionThread::setNoneMode(void){
  GV.Mode = DAC_STATE_NONE;
  GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
}

#if (EMERGENCY_STOP_TYPE == EMERGENCY_STOP_TYPE_BUTTON)
void ExecutionThread::CheckEmergencyStopState(void){
  EmergencyStpTimeout.attach(callback(this, &ExecutionThread::emergencyStop), 20ms);
}

void ExecutionThread::emergencyStop(void){
#if (!(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)&&!(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN))
  if(emergencyStopButton.read() == 0){
    // GV.ConstDisplacementModeParams.speedEnable = false;
    // GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
    // GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;

    GV.Mode = DAC_STATE_NONE;
    GV.stopCurrentTestProcess = true;
    GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
    GV.InternalTask = INTERNAL_TASK_NONE;
  }
#else
  if(emergencyStopButton.read() == 1){
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
  } 
#endif
    // if(GV.InternalTask == INTERNAL_TASK_STATIC_TEST){
    //   GV.InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
    // }else{
      sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::EMERGENCY_STOP);
    // }
  
}
#endif

#if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
void ExecutionThread::CheckLimSwState(void){
  LimSw->disableIrq();
  LimSwTimeout.attach(callback(this, &ExecutionThread::LimitSwitchRiseMode), 100ms);
}

void ExecutionThread::LimitSwitchRiseMode(void){
  if(LimSw->getState()){
    if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
      setNoneMode();
      }
    if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
      GV.Mode = DAC_STATE_CLOSE_VALVE;
      GV.closeValveState = CLOSE_VALVE_STATE_RESET;
      GV.LimitSwitchState = LIMIT_SWITCH_STATE_ONE;
    }
    if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
    }
    if(LimSwDirecton > 0){
      GV.LimitSwitchState = LIMIT_SWITCH_STATE_ONE;
    }
    if(LimSwDirecton < 0){
      GV.LimitSwitchState = LIMIT_SWITCH_STATE_TWO;
    }
    GV.stopCurrentTestProcess = true;
    GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
    GV.InternalTask = INTERNAL_TASK_NONE;
    sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::LIMIT_SWITCH);
  }
  LimSw->enableIrq();
}

void ExecutionThread::LimitSwitchFallMode(void){
  GV.LimitSwitchState = LIMIT_SWITCH_STATE_UNDEFINED;
}
#endif

#if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
void ExecutionThread::checkLimSwLeftDoorRiseState(void){
  // HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  // limSwLeftDoorTimeout.attach(callback(this, &ExecutionThread::limSwLeftDoorRiseMode), 100ms);
}

void ExecutionThread::limSwLeftDoorRiseMode(void){
  // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void ExecutionThread::checkLimSwLeftDoorFallState(void){
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  limSwLeftDoorTimeout.attach(callback(this, &ExecutionThread::limSwLeftDoorFallMode), 100ms);
}

void ExecutionThread::limSwLeftDoorFallMode(void){
  if (GV.WorkMode == WORK_MODE_TEST_IN_PROCESS){
    if(!leftDoorSwitch.read()){
      GV.Mode = DAC_STATE_CLOSE_VALVE;
      GV.closeValveState = CLOSE_VALVE_STATE_RESET;
      sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::LIMIT_SWITCH_LEFT_DOOR);
    }
  }
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void ExecutionThread::checkLimSwRightDoorRiseState(void){
  // HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  // limSwRightDoorTimeout.attach(callback(this, &ExecutionThread::limSwRightDoorRiseMode), 100ms);
}

void ExecutionThread::limSwRightDoorRiseMode(void){    
  // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void ExecutionThread::checkLimSwRightDoorFallState(void){
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
  limSwRightDoorTimeout.attach(callback(this, &ExecutionThread::limSwRightDoorFallMode), 100ms);
}

void ExecutionThread::limSwRightDoorFallMode(void){
  if (GV.WorkMode == WORK_MODE_TEST_IN_PROCESS){
    if(!rightDoorSwitch.read()){
      GV.Mode = DAC_STATE_CLOSE_VALVE;
      GV.closeValveState = CLOSE_VALVE_STATE_RESET;
      sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::LIMIT_SWITCH_RIGHT_DOOR);
    }
  }
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
#endif

void ExecutionThread::setConstDisplSpeed(void){
  GV.ConstDisplacementModeParams.Speed = this->constDisplSpeedToSet;//mm/sec by default
}

void ExecutionThread::enableLED2(void){
  led2.write(1);
}
void ExecutionThread::enableLED3(void){
  led3.write(1);
}

void ExecutionThread::disableLED2(void){
  led2.write(0);
}
void ExecutionThread::disableLED3(void){
  led3.write(0);
}
void ExecutionThread::resetEmergencyButton(void){
  HwCmd5.write(1);
  //HwCmd6.write(0);
  //HwCmd4.write(0);
}

void ExecutionThread::strainProtectStage1Execute(void){
    switch (strainProtect.process(strain))
    {
    case PROTECT_STATUS_OVERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.strainOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      strainProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (strainProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    case PROTECT_STATUS_UNDERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.strainUnderrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      strainProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (strainProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    default:

      break;
    }
}
void ExecutionThread::strainProtectStage2Execute(void){
    switch (strainProtectStage2.process(strain))
    {
    case PROTECT_STATUS_OVERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.strainOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      strainProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (strainProtectStage2.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    case PROTECT_STATUS_UNDERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.strainOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      strainProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (strainProtectStage2.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    default:
      break;
    }
}
void ExecutionThread::strainProtectEdgeExecute(void){
  switch (strainEdgeProtect.process(strainWoNO))
  {
  case PROTECT_STATUS_OVERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.strainOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    // strainEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (strainEdgeProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
      this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
      yellowLED.write(1);
      redLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  case PROTECT_STATUS_UNDERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.strainOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    // strainEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (strainEdgeProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
      this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
      yellowLED.write(1);
      redLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  default:
    break;
  }
}

void ExecutionThread::strainButtonProtectExecute(void){
  switch (strainButtonProtect.process(strain))
  {
  case PROTECT_STATUS_OVERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.strainOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    buttonMode = false;
    // strainEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (strainButtonProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
      this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
      yellowLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  case PROTECT_STATUS_UNDERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.strainOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    buttonMode = false;
    // strainEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (strainButtonProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
      this->sendNotification(COMMAND::TM_ONCE_STRAIN_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
      yellowLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  default:
    break;
  }
}

void ExecutionThread::displacementProtectStage1Execute(void){
  switch (displacementProtect.process(position))
    {
    case PROTECT_STATUS_OVERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.displOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      displacementProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    case PROTECT_STATUS_UNDERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.displUnderrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      displacementProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    default:
      break;
    }
}
void ExecutionThread::displacementProtectStage2Execute(void){
  switch (displacementProtectStage2.process(position))
    {
    case PROTECT_STATUS_OVERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.displOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      displacementProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementProtectStage2.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    case PROTECT_STATUS_UNDERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.displOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      displacementProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementProtectStage2.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    default:
      break;
    }
}
void ExecutionThread::displacementProtectEdgeExecute(void){
  switch (displacementEdgeProtect.process(positionWoNO))
    {
    case PROTECT_STATUS_OVERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.displOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      // displacementEdgeProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementEdgeProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        yellowLED.write(1);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    case PROTECT_STATUS_UNDERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.displOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      // displacementEdgeProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (displacementEdgeProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DISP_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        yellowLED.write(1);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    default:
      break;
    }
}
void ExecutionThread::deformationProtectStage1Execute(void){
    switch (deformationProtect.process(deformation))
    {
    case PROTECT_STATUS_OVERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.deformOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      deformationProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (deformationProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    case PROTECT_STATUS_UNDERRUN:{
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.deformUnderrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      deformationProtect.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (deformationProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_1_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        yellowLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    }
    default:
      break;
    }
}
void ExecutionThread::deformationProtectStage2Execute(void){
    switch (deformationProtectStage2.process(deformation))
    {
    case PROTECT_STATUS_OVERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.deformOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      deformationProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (deformationProtectStage2.getPrevStatus() != PROTECT_STATUS_OVERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    case PROTECT_STATUS_UNDERRUN:
      //HwCmd5.write(0);
      //HwCmd6.write(0);
      GV.ConstDisplacementModeParams.speedEnable = false;
      GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.deformOverrunStepBack;
      GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
      GV.Mode = DAC_STATE_DISP_CONST;
      deformationProtectStage2.setMode(PROTECT_MODE_DISABLE);
      //HwCmd4.write(0);
      if (deformationProtectStage2.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
        this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_2_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
        redLED.write(1);
        greenLED.write(0);
        GV.stepID++;
      }
      break;
    default:
      break;
    }
}
void ExecutionThread::deformationProtectEdgeExecute(void){
  switch (deformationEdgeProtect.process(deformationWoNO))
  {
  case PROTECT_STATUS_OVERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition - GV.deformOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    // deformationEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (deformationEdgeProtect.getPrevStatus() != PROTECT_STATUS_OVERRUN){
      this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_OVERRUN);
      yellowLED.write(1);
      redLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  case PROTECT_STATUS_UNDERRUN:{
    //HwCmd5.write(0);
    //HwCmd6.write(0);
    GV.ConstDisplacementModeParams.speedEnable = false;
    GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentPosition + GV.deformOverrunStepBack;
    GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
    GV.Mode = DAC_STATE_DISP_CONST;
    // deformationEdgeProtect.setMode(PROTECT_MODE_DISABLE);
    //HwCmd4.write(0);
    if (deformationEdgeProtect.getPrevStatus() != PROTECT_STATUS_UNDERRUN){
      this->sendNotification(COMMAND::TM_ONCE_DEFORMATION_PROTECT_TRIGGERED_3_STAGE, (uint32_t)PROTECT_STATUS_UNDERRUN);
      yellowLED.write(1);
      redLED.write(1);
      greenLED.write(0);
      GV.stepID++;
    }
    break;
  }
  default:
    break;
  }
}

void ExecutionThread::sendNotification (COMMAND cmd, uint32_t state){
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  if(EthernetAnswerMail != nullptr){
    EthernetAnswerMail->command = cmd;
    EthernetAnswerMail->dataLength = 4;
    //error status 0
    basic.writeValueToBytesBuffer(EthernetAnswerMail->data, state);
    EthernetAnswerMailBox.put(EthernetAnswerMail);
  }
  UARTMail_t *ReCoAnswerMail = RemoteControllerAnswerMailBox.try_alloc_for(0ms);
  if(ReCoAnswerMail != nullptr){
    ReCoAnswerMail->command = cmd;
    ReCoAnswerMail->dataLength = 4;
    //error status 0
    basic.writeValueToBytesBuffer(ReCoAnswerMail->data, state);
    RemoteControllerAnswerMailBox.put(ReCoAnswerMail);
  }
}
void ExecutionThread::sendNotification (COMMAND cmd, uint64_t state){
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  if (EthernetAnswerMail != nullptr){
    EthernetAnswerMail->command = cmd;
    EthernetAnswerMail->dataLength = 8;
    //error status 0
    basic.writeValueToBytesBuffer(EthernetAnswerMail->data, state);
    EthernetAnswerMailBox.put(EthernetAnswerMail);
  }
}
void ExecutionThread::sendNotification (COMMAND cmd, float state){
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  if(EthernetAnswerMail != nullptr){
    EthernetAnswerMail->command = cmd;
    EthernetAnswerMail->dataLength = 4;
    //error status 0
    basic.writeValueToBytesBuffer(EthernetAnswerMail->data, state);
    EthernetAnswerMailBox.put(EthernetAnswerMail);
  }
}

template<typename Key, typename... Args> void ExecutionThread::sendNotification(COMMAND cmd, Key key, Args... args){
  EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
  if(EthernetAnswerMail != nullptr){
    EthernetAnswerMail->command = cmd;
    EthernetAnswerMail->dataLength = sizeof(key);
    basic.writeValueToBytesBuffer(EthernetAnswerMail->data, key);
    makingDataFromParameters(EthernetAnswerMail, args...);
    if (EthernetAnswerMail->dataLength > 1024){
      EthernetAnswerMail->command = COMMAND::TM_ONCE_ANSWER_MAIL_STATUS;
      EthernetAnswerMail->dataLength = 4;
      basic.writeValueToBytesBuffer(EthernetAnswerMail->data, ETHERNET_ERROR_UNEXPECTED_DATA_LENGTH);
    }
    EthernetAnswerMailBox.put(EthernetAnswerMail);
  }
}

template<typename One> void ExecutionThread::makingDataFromParameters(EthernetAnswerMail_t* mailPtr, One one){
    if(mailPtr){
      basic.writeValueToBytesBuffer(mailPtr->data + mailPtr->dataLength, one);
      mailPtr->dataLength = mailPtr->dataLength + sizeof(one);
      //printf(" elem-%f, size of buffer-%ld \n", one, mailPtr->dataLength);
    }
}
template<typename First, typename... Other> void ExecutionThread::makingDataFromParameters(EthernetAnswerMail_t* mailPtr, First first, Other... other){
    if(mailPtr){
      basic.writeValueToBytesBuffer(mailPtr->data + mailPtr->dataLength, first);
      mailPtr->dataLength = mailPtr->dataLength + sizeof(first);
      //printf(" elem-%f, size of buffer-%ld \n", first, mailPtr->dataLength);
      makingDataFromParameters(mailPtr, other...);
    }
}

void ExecutionThread::internalTaskManager(void){
    //Time Measurement
    if(GV.TimeMeasure.enable){
      if(GV.TimeMeasure.startMeasurePosition - GV.TimeMeasure.endMeasurePosition > 0){
        if(GV.roCurrentPosition < GV.TimeMeasure.startMeasurePosition && !GV.TimeMeasure.measuring){
          GV.TimeMeasure.startTime = SystemTimer.elapsed_time().count();
          GV.TimeMeasure.measuring = true;
        }
        if(GV.roCurrentPosition < GV.TimeMeasure.endMeasurePosition && GV.TimeMeasure.measuring){
          GV.TimeMeasure.endTime = SystemTimer.elapsed_time().count();
          GV.TimeMeasure.time = GV.TimeMeasure.endTime - GV.TimeMeasure.startTime;
          GV.TimeMeasure.enable = 0x0;
          GV.TimeMeasure.measuring = false;
          //send notification complete
          this->sendNotification(COMMAND::TM_ONCE_TIME_MEASUREMENT_COMPLETE, GV.TimeMeasure.time);
        }
      }
      if(GV.TimeMeasure.startMeasurePosition - GV.TimeMeasure.endMeasurePosition < 0){
        if(GV.roCurrentPosition > GV.TimeMeasure.startMeasurePosition && !GV.TimeMeasure.measuring){
          GV.TimeMeasure.startTime = SystemTimer.elapsed_time().count();
          GV.TimeMeasure.measuring = true;
        }
        if(GV.roCurrentPosition > GV.TimeMeasure.endMeasurePosition && GV.TimeMeasure.measuring){
          GV.TimeMeasure.endTime = SystemTimer.elapsed_time().count();
          GV.TimeMeasure.time = GV.TimeMeasure.endTime - GV.TimeMeasure.startTime;
          GV.TimeMeasure.enable = 0x0;
          GV.TimeMeasure.measuring = false;
          //send notification complete
          this->sendNotification(COMMAND::TM_ONCE_TIME_MEASUREMENT_COMPLETE, GV.TimeMeasure.time);
        }
      }
      if(GV.TimeMeasure.startMeasurePosition - GV.TimeMeasure.endMeasurePosition == 0){
        GV.TimeMeasure.enable = false;
        //send notification complete
        sendNotification(COMMAND::TM_ONCE_TIME_MEASUREMENT_COMPLETE, (uint64_t)0x0);
      }
    }
    //Sample Hardness Calculation
    switch (GV.InternalTask)
    {
      case INTERNAL_TASK_SAMPLE_HARDNESS_CALCULATION:{
        switch (GV.InternalTaskState)
        {
        case INTERNAL_TASK_STATE_INIT:{
          if(GV.Mode == DAC_STATE_DISP_CONST){
            GV.SampleHardnessInfo.initialPosition = GV.ConstDisplacementModeParams.PositionToHold;
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_1;
          }else{
            this->sendNotification(COMMAND::TM_ONCE_RUNTIME_ERROR, (uint32_t) ETHERNET_ERROR_SAMPLE_HARDNESS_UNEXPECTED_INITIAL_MODE);
            GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_1:{
          //initial state
          GV.ConstModeParams.Voltage = GV.SampleHardnessInfo.speed;
          GV.ConstModeParams.Direction = GV.SampleHardnessInfo.direction;
          GV.SampleHardnessInfo.edgeValue3 = 0.3 * GV.SampleHardnessInfo.Fmax;
          GV.SampleHardnessInfo.edgeValue2 = 0.15 * GV.SampleHardnessInfo.Fmax;
          GV.SampleHardnessInfo.edgeValue4 = 0.15 * GV.SampleHardnessInfo.Fmax;
          GV.SampleHardnessInfo.edgeValue1 = 0.05 * GV.SampleHardnessInfo.edgeValue3;
          GV.SampleHardnessInfo.edgeValue5 = 0.05 * GV.SampleHardnessInfo.edgeValue3;
          GV.SampleHardnessInfo.p1.alpha = 0;
          GV.SampleHardnessInfo.p1.displ = 0;
          GV.SampleHardnessInfo.p1.strain = 0;
          GV.SampleHardnessInfo.p1.time = 0;
          GV.SampleHardnessInfo.p2.alpha = 0;
          GV.SampleHardnessInfo.p2.displ = 0;
          GV.SampleHardnessInfo.p2.strain = 0;
          GV.SampleHardnessInfo.p2.time = 0;
          GV.SampleHardnessInfo.p3.alpha = 0;
          GV.SampleHardnessInfo.p3.displ = 0;
          GV.SampleHardnessInfo.p3.strain = 0;
          GV.SampleHardnessInfo.p3.time = 0;
          GV.SampleHardnessInfo.p4.alpha = 0;
          GV.SampleHardnessInfo.p4.displ = 0;
          GV.SampleHardnessInfo.p4.strain = 0;
          GV.SampleHardnessInfo.p4.time = 0;
          GV.SampleHardnessInfo.p5.alpha = 0;
          GV.SampleHardnessInfo.p5.displ = 0;
          GV.SampleHardnessInfo.p5.strain = 0;
          GV.SampleHardnessInfo.p5.time = 0;
          GV.SampleHardnessInfo.p6.alpha = 0;
          GV.SampleHardnessInfo.p6.displ = 0;
          GV.SampleHardnessInfo.p6.strain = 0;
          GV.SampleHardnessInfo.p6.time = 0;
          GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_2;
          break;
        }
        case INTERNAL_TASK_STATE_STEP_2:{
          GV.Mode = DAC_STATE_CONST_LEVEL;
          GV.SampleHardnessInfo.p1.displ = GV.roCurrentPosition;
          GV.SampleHardnessInfo.p1.strain = GV.roCurrentStrain;
          GV.SampleHardnessInfo.p1.alpha = 0;
          GV.SampleHardnessInfo.p1.time = SystemTimer.elapsed_time().count();
          GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_3;
          break;
        }
        case INTERNAL_TASK_STATE_STEP_3:{
          if(((GV.roCurrentStrain >= GV.SampleHardnessInfo.edgeValue1) && (GV.SampleHardnessInfo.direction < 0)) ||
             ((GV.roCurrentStrain <= GV.SampleHardnessInfo.edgeValue1) && (GV.SampleHardnessInfo.direction > 0))){
            GV.SampleHardnessInfo.p2.displ = GV.roCurrentPosition;
            GV.SampleHardnessInfo.p2.strain = GV.roCurrentStrain;
            GV.SampleHardnessInfo.p2.time = SystemTimer.elapsed_time().count() - GV.SampleHardnessInfo.p1.time;
            GV.SampleHardnessInfo.p2.alpha = 50 * GV.SampleHardnessInfo.p2.strain / 
                                            (GV.ConstModeParams.Voltage * GV.SampleHardnessInfo.p2.time);
            //this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_1_COMPLETE, (uint32_t) 0x0);
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_4;
          }
          else{
            //displacement protect;
            if (abs(GV.roCurrentPosition - GV.SampleHardnessInfo.p1.displ) >= GV.SampleHardnessInfo.maxElongation){
              GV.ConstDisplacementModeParams.speedEnable = false;
              GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              GV.Mode = DAC_STATE_DISP_CONST;
              this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_1_PROTECT_TRIGGERED, (uint32_t) 0x0);
              GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
              GV.InternalTask = INTERNAL_TASK_NONE;
            }
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_4:{
          if(((GV.roCurrentStrain >= GV.SampleHardnessInfo.edgeValue2) && (GV.SampleHardnessInfo.direction < 0)) ||
             ((GV.roCurrentStrain <= GV.SampleHardnessInfo.edgeValue2) && (GV.SampleHardnessInfo.direction > 0))){
            GV.SampleHardnessInfo.p3.displ = GV.roCurrentPosition;
            GV.SampleHardnessInfo.p3.strain = GV.roCurrentStrain;
            GV.SampleHardnessInfo.p3.time = SystemTimer.elapsed_time().count() - GV.SampleHardnessInfo.p2.time;
            GV.SampleHardnessInfo.p3.alpha = 50 * GV.SampleHardnessInfo.p3.strain / 
                                            (GV.ConstModeParams.Voltage * GV.SampleHardnessInfo.p3.time);
            //this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_2_COMPLETE, (uint32_t) 0x0);
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_5;
          }
          else{
            //displacement protect;
            if (abs(GV.roCurrentPosition - GV.SampleHardnessInfo.p1.displ) >= GV.SampleHardnessInfo.maxElongation){
              GV.ConstDisplacementModeParams.speedEnable = false;
              GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              GV.Mode = DAC_STATE_DISP_CONST;
              this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_2_PROTECT_TRIGGERED, (uint32_t) 0x0);
              GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
              GV.InternalTask = INTERNAL_TASK_NONE;
            }
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_5:{
          if(((GV.roCurrentStrain >= GV.SampleHardnessInfo.edgeValue3) && (GV.SampleHardnessInfo.direction < 0)) ||
             ((GV.roCurrentStrain <= GV.SampleHardnessInfo.edgeValue3) && (GV.SampleHardnessInfo.direction > 0))){
            GV.SampleHardnessInfo.p4.displ = GV.roCurrentPosition;
            GV.SampleHardnessInfo.p4.strain = GV.roCurrentStrain;
            GV.SampleHardnessInfo.p4.time = SystemTimer.elapsed_time().count() - GV.SampleHardnessInfo.p3.time;
            GV.ConstModeParams.Direction = GV.ConstModeParams.Direction * (-1);
            GV.SampleHardnessInfo.p4.alpha = 50 * GV.SampleHardnessInfo.p4.strain / 
                                            (GV.ConstModeParams.Voltage * GV.SampleHardnessInfo.p4.time);
            //this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_3_COMPLETE, (uint32_t) 0x0);
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_6;
            
          }
          else{
            //displacement protect;
            if (abs(GV.roCurrentPosition - GV.SampleHardnessInfo.p1.displ) >= GV.SampleHardnessInfo.maxElongation){
              GV.ConstDisplacementModeParams.speedEnable = false;
              GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              GV.Mode = DAC_STATE_DISP_CONST;
              this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_3_PROTECT_TRIGGERED, (uint32_t) 0x0);
              GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
              GV.InternalTask = INTERNAL_TASK_NONE;
            }
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_6:{
          if(((GV.roCurrentStrain <= GV.SampleHardnessInfo.edgeValue4) && (GV.SampleHardnessInfo.direction < 0)) ||
             ((GV.roCurrentStrain >= GV.SampleHardnessInfo.edgeValue4) && (GV.SampleHardnessInfo.direction > 0))){
            GV.SampleHardnessInfo.p5.displ = GV.roCurrentPosition;
            GV.SampleHardnessInfo.p5.strain = GV.roCurrentStrain;
            GV.SampleHardnessInfo.p5.time = SystemTimer.elapsed_time().count() - GV.SampleHardnessInfo.p4.time;
            GV.SampleHardnessInfo.p5.alpha = 50 * GV.SampleHardnessInfo.p5.strain / 
                                            (GV.ConstModeParams.Voltage * GV.SampleHardnessInfo.p5.time);
            //this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_4_COMPLETE, (uint32_t) 0x0);                                            
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_7;
          }
          else{
            //displacement protect;
            if (abs(GV.roCurrentPosition - GV.SampleHardnessInfo.p1.displ) >= GV.SampleHardnessInfo.maxElongation){
              GV.ConstDisplacementModeParams.speedEnable = false;
              GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              GV.Mode = DAC_STATE_DISP_CONST;
              this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_4_PROTECT_TRIGGERED, (uint32_t) 0x0);
              GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
              GV.InternalTask = INTERNAL_TASK_NONE;
            }
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_7:{
          if(((GV.roCurrentStrain <= GV.SampleHardnessInfo.edgeValue5) && (GV.SampleHardnessInfo.direction < 0)) ||
             ((GV.roCurrentStrain >= GV.SampleHardnessInfo.edgeValue5) && (GV.SampleHardnessInfo.direction > 0))){
            GV.SampleHardnessInfo.p6.displ = GV.roCurrentPosition;
            GV.SampleHardnessInfo.p6.strain = GV.roCurrentStrain;
            GV.SampleHardnessInfo.p6.time = SystemTimer.elapsed_time().count() - GV.SampleHardnessInfo.p5.time;
            GV.SampleHardnessInfo.p6.alpha = 50 * GV.SampleHardnessInfo.p6.strain / 
                                            (GV.ConstModeParams.Voltage * GV.SampleHardnessInfo.p6.time);
            //this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_5_COMPLETE, (uint32_t) 0x0);
            GV.InternalTaskState = INTERNAL_TASK_STATE_STEP_8;
          }
          else{
            //displacement protect;
            if (abs(GV.roCurrentPosition - GV.SampleHardnessInfo.p1.displ) >= GV.SampleHardnessInfo.maxElongation){
              GV.ConstDisplacementModeParams.speedEnable = false;
              GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              GV.Mode = DAC_STATE_DISP_CONST;
              this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_STAGE_5_PROTECT_TRIGGERED, (uint32_t) 0x0);
              GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
              GV.InternalTask = INTERNAL_TASK_NONE;
            }
          }
          break;
        }
        case INTERNAL_TASK_STATE_STEP_8:{
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          this->sendNotification(COMMAND::TM_ONCE_HARDNESS_CALC_COMPLETE, (uint32_t) 0x0);
          GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
          GV.InternalTask = INTERNAL_TASK_NONE;
          break;
        }
        case INTERNAL_TASK_STATE_STOP_TASK:{
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.PositionToHold = GV.SampleHardnessInfo.initialPosition;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          GV.Mode = DAC_STATE_DISP_CONST;
          GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
          GV.InternalTask = INTERNAL_TASK_NONE;
          break;
        }
        default:
          break;
        }
        break;
      }
      case INTERNAL_TASK_STATIC_TEST:{
        // switch (GV.InternalTaskState)
        // {
        //   case INTERNAL_TASK_STATE_INIT:{
        //     staticTest->init();
        //     staticTest->setPositionThreshold    (GV.positionUpperThreshold,     GV.positionLowerThreshold);
        //     staticTest->setStrainThreshold      (GV.strainUpperThreshold,       GV.strainLowerThreshold);
        //     staticTest->setDeformationThreshold (GV.deformationUpperThreshold,  GV.deformationLowerThreshold);
        //     break;
        //   }
        //   case INTERNAL_TASK_STATE_STEP_1:{
        //     staticTest->process();
        //     break;
        //   }
        //   case INTERNAL_TASK_STATE_STOP_TASK:{
        //     //GV.ConstDisplacementModeParams.MaxVoltage = staticTest->getInitConstDisplMaxVoltage();
        //     //GV.ConstStrainModeParams.MaxVoltage = staticTest->getInitConstStrainMaxVoltage();
        //     GV.ConstDisplacementModeParams.speedEnable = false;
        //     GV.ConstDisplacementModeParams.Speed = staticTest->getInitConstDisplSpeed();
        //     GV.ConstStrainModeParams.Speed = staticTest->getInitConstStrainSpeed();
        //     GV.ConstDeformationModeParams.Speed = staticTest->getInitConstDeformSpeed();
        //     GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        //     GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
        //     GV.Mode = DAC_STATE_DISP_CONST;
        //     GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
        //     GV.InternalTask = INTERNAL_TASK_NONE;
        //     switch (staticTest->sampleStatus)
        //     {
        //     case SBD_STATUS_BREAK_MAX_STRAIN:
        //       sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::SAMPLE_BREAKED_MAX_STRAIN);
        //       break;
        //     case SBD_STATUS_BREAK_DYNAMIC_FALL:
        //       sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::SAMPLE_BREAKED_DF);
        //       break;
        //     case SBD_STATUS_OK:
        //       sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)TestExecutionCompleteStatus::OK);
        //       break;
        //     default:
        //       break;
        //     }
        //     break;
        //   } 
		    //   case INTERNAL_TASK_STATE_PAUSE_TASK:{
        //     staticTest->stopTimer();
        //     GV.ConstDisplacementModeParams.speedEnable = false;
        //     GV.ConstStrainModeParams.speedEnable = false;
        //     // GV.ConstDeformationModeParams.speedEnable = false;
        //     GV.ConstDisplacementModeParams.Speed = staticTest->getInitConstDisplSpeed();
        //     GV.ConstStrainModeParams.Speed = staticTest->getInitConstStrainSpeed();
        //     // GV.ConstDeformationModeParams.Speed = staticTest->getInitConstDeformSpeed();
        //     switch (GV.Mode)
        //     {
        //       case DAC_STATE_DISP_CONST:{
        //         GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
        //         GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;            
        //         break;
        //       }
        //       case DAC_STATE_STRAIN_CONST:{
        //         GV.ConstStrainModeParams.StrainToHold = GV.roCurrentAvStrain;  
        //         GV.ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;          
        //         break;
        //       }
        //       case DAC_STATE_DEFORMATION_CONST:{
        //         GV.ConstDeformationModeParams.DeformationToHold = GV.roCurrentAvDeformation; 
        //         GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;           
        //         break;
        //       }
        //       default:
        //         break;
        //     }
        //     // GV.InternalTaskState = INTERNAL_TASK_STATE_NONE;
        //     GV.InternalTask = INTERNAL_TASK_NONE;          
        //     break;
        //   }  
        //   default:
        //     break;
        // }
        break;
      }
      case INTERNAL_TASK_SBD:{
        switch (GV.InternalTaskSBD)
        {
        case INTERNAL_TASK_SBD_INIT:{
          this->SBD_MS->init(SBD_MODE_PERCENT_OF_MAX_STRAIN, 1, abs(GV.roCurrentAvStrain));
          this->SBD_DF->init(SBD_MODE_DYNAMIC_FALL, 1, abs(GV.roCurrentAvStrain));
          this->SBD_MS->setModeParams(GV.ExT_SBDProcentOfMaxStrain1, abs(GV.ExT_SBDStartStrain1), GV.Ext_SBDThreshold);
          this->SBD_DF->setModeParams(GV.ExT_SBDProcentOfMaxStrain2, abs(GV.ExT_SBDStartStrain2), GV.ExT_SBDTime);
          this->SBD_MS->setEnable(GV.ExT_SBDStateMaxStrain);
          this->SBD_DF->setEnable(GV.ExT_SBDStateDF);
          GV.InternalTaskSBD = INTERNAL_TASK_SBD_PROCESS;
          break;
        }
        case INTERNAL_TASK_SBD_PROCESS:{
          if(this->SBD_MS->process(abs(GV.roCurrentStrain), std::signbit(GV.roCurrentStrain)) == SBD_STATUS_BREAK_MAX_STRAIN){
            this->sampleStatus = SBD_STATUS_BREAK_MAX_STRAIN;
            GV.InternalTaskSBD = INTERNAL_TASK_SBD_EXIT;
          }
          if(this->SBD_DF->process(abs(GV.roCurrentStrain), std::signbit(GV.roCurrentStrain)) == SBD_STATUS_BREAK_DYNAMIC_FALL){
            this->sampleStatus = SBD_STATUS_BREAK_DYNAMIC_FALL;
            GV.InternalTaskSBD = INTERNAL_TASK_SBD_EXIT;
          }
          break;
        }
        case INTERNAL_TASK_SBD_EXIT:{
          sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)this->sampleStatus);
          GV.InternalTaskSBD = INTERNAL_TASK_SBD_NONE;
          GV.ConstDisplacementModeParams.speedEnable = false;
          GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
          GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
            GV.Mode = DAC_STATE_NONE;
          }
          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
            GV.Mode = DAC_STATE_CLOSE_VALVE;
            GV.closeValveState = CLOSE_VALVE_STATE_RESET;
          }
          if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
            GV.Mode = DAC_STATE_DISP_CONST;
          }
          #if (PROJECT_NAME == PROJECT_NAME_MPD)
          alarmLight.write(1);
          #endif
          GV.stepID++;
          break;
        }
        default:
          break;
        }
        
        break;
      }
      default:
        break;
    }
}
//main methods
void ExecutionThread::averageAndDecimate(void){
  //Average procedure
    GV.AveragePosition.push(position);
    GV.AverageDeformation.push(deformation);
    GV.AverageStrain.push(strain);
    //Decimate points
    if (GV.AverageAcq & ACQ_DISPLACEMENT){
      if(GV.AveragePosition.getStatus() == AVERAGING_STATUS_COMPLETE){
        //RSSIValuesBuffer.push(GV.AveragePosition.get());
        this->positionToSend = GV.AveragePosition.get();
      }
      //dataDecimationCounterDisplacement = 0;
    }else{
      //dataDecimationCounterDisplacement++;
      //if (dataDecimationCounterDisplacement >= GV.DataDecimationCoeff){
        //push current displacemnt position to ethernet thread
        //RSSIValuesBuffer.push(position);
        this->positionToSend = displacement_DISPLAYING;
        //dataDecimationCounterDisplacement = 0;
      //}
    }
    if (GV.AverageAcq & ACQ_STRAIN){
      if(GV.AverageStrain.getStatus() == AVERAGING_STATUS_COMPLETE){
        //StrainBuffer.push(GV.AverageStrain.get());
        this->strainToSend = GV.AverageStrain.get();
      }
      //dataDecimationCounterStrain = 0;
    }else{
      //dataDecimationCounterStrain++;
      //if (dataDecimationCounterStrain >= GV.DataDecimationCoeff){
        //push current displacemnt position to ethernet thread
        //StrainBuffer.push(strain);
        this->strainToSend = strain_DISPLAYING;
        //dataDecimationCounterStrain = 0;
      //}
    }
    if (GV.AverageAcq & ACQ_DEFORMATION){
      if(GV.AverageDeformation.getStatus() == AVERAGING_STATUS_COMPLETE){
        //ExtensBuffer.push(GV.AverageStrain.get());
        this->deformationToSend = GV.AverageDeformation.get();
      }
      //dataDecimationCounterDeformation = 0;
    }else{
      //dataDecimationCounterDeformation++;
      //if (dataDecimationCounterDeformation >= GV.DataDecimationCoeff){
        //push current displacemnt position to ethernet thread
        //ExtensBuffer.push(deformation);
        this->deformationToSend = deformation_DISPLAYING;
        //dataDecimationCounterDeformation = 0;
      //}
    }
}
void ExecutionThread::updateValues(void){
  //wait for the end of DMA transfer
    if (GV.EnabledAcq & ACQ_STRAIN){
      //TODO: timer for checking transfer timeout
      #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
      if (GV.WaitAcqComplete & WAIT_ACQ_COMPLETE_STRAIN){
        std::chrono::microseconds startTime = SystemTimer.elapsed_time();
        while (ADCext.getTransferStatus() != ADS8320_DMA_SPI_TRANSFER_COMPLETE){
          if(SystemTimer.elapsed_time() - startTime >= this->spiTransactionTimeout){
            break;
          }
        }
      }
      if(ADCext.getTransferStatus() == ADS8320_DMA_SPI_TRANSFER_COMPLETE){
        ADCext.clearTransferStatus();
        //TODO: fucking ADC, FIX IT!
        //filtering high amplitude error value
        //float oldStrain = strain;
        switch (GV.StrainUnits)
        {
          case STRAIN_UNITS_KN:
            switch (GV.strainChannel)
            {
            case STRAIN_CHANNEL_1ST:{
              strainWoNO = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getLastCode());
              // strain = strainWoNO - GV.ADCNullOffset;
              break;
            }
            case STRAIN_CHANNEL_2ND:{
              strainWoNO = GV.strainInvertAxis * ADCext.calcStrain2(ADCext.getLastCode());
              // strain = strainWoNO - GV.ADCNullOffset;
              break;
            }
            default:
              strainWoNO = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getLastCode());
              // strain = strainWoNO - GV.ADCNullOffset;
              break;
            }
            #if (BATTERY == BATTERY_AVAILABLE)
            strainWoNO = strainWoNO - *BV.strainNullOffset;
            #endif
            strain = strainWoNO - GV.ADCNullOffset;
            break;
          case STRAIN_UNITS_RAW:
            switch (GV.strainChannel)
            {
            case STRAIN_CHANNEL_1ST:{
              strain = ADCext.getLastCode();
              // strainWoNO = strain;
              break;
            }
            case STRAIN_CHANNEL_2ND:{
              strain = ADCext.getLastCode();
              // strainWoNO = strain;
              break;
            }
            default:
              strain = ADCext.getLastCode();
              // strainWoNO = strain;
              break;
            }
            strainWoNO = strain;
            break;
          case STRAIN_UNITS_POSITION_RAW:
            strain = GV.positionInvertAxis * RSSIReader.getLastPositionRAW();
            strainWoNO = strain;
            break;
          case STRAIN_UNITS_DEFORMATION_RAW:
            switch (GV.machineInfo.deformation.sensorType)
            {
            case SENSOR_TYPE_ANALOG:{
              strain = ADCextExtens.getLastCode();
              break;
            }
            #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
            case SENSOR_TYPE_ANALOG_0_10V:{
              strain = ADS869xExtens.getLastCode();
              break;
            }
            case SENSOR_TYPE_ANALOG_LVDT:{
              strain = ADS869xExtens.getLastCode2();
              break;
            }
            case SENSOR_TYPE_ANALOG_LVDT2:{
              strain = ADS869xExtens.getLastCode3();
              break;
            }
            #endif
            case SENSOR_TYPE_ENCODER:{
              strain = deformEncoder.GetExtendedTimerValue_RAW();
              break;
            }
            default:
              break;
            }
            strainWoNO = strain;
            break;
          case STRAIN_UNITS_DEFORMATION_KN:
            strainWoNO = GV.strainInvertAxis * ADCextExtens.calcDeformation(ADCextExtens.getLastCode());
            strain = strainWoNO - GV.ADCNullOffset;
            break;
          //default KN
          default:
            strainWoNO = GV.strainInvertAxis * ADCext.calcStrain(ADCext.getLastCode());
            strain = strainWoNO - GV.ADCNullOffset;
            //if (abs(strain) > abs(oldStrain) + 30){
            //  strain = oldStrain;
            //}
            break;
        }
        // GV.roCurrentStrainTime = SystemTimer.elapsed_time().count();
      }
      #else
      ADS869xStrain.transferBlocking();
      switch (GV.StrainUnits)
      {
      case STRAIN_UNITS_KN:
        switch (GV.strainChannel)
        {
        case STRAIN_CHANNEL_1ST:{
          strainWoNO = GV.strainInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode());
          // strain = strainWoNO - GV.ADCNullOffset;
          break;
        }
        case STRAIN_CHANNEL_2ND:{
          strainWoNO = GV.strainInvertAxis * ADS869xStrain.calcStrain2(ADS869xStrain.getLastCode());
          // strain = strainWoNO - GV.ADCNullOffset;
          break;
        }
        default:
          strainWoNO = GV.strainInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode());
          // strain = strainWoNO - GV.ADCNullOffset;
          break;
        }
        #if (BATTERY == BATTERY_AVAILABLE)
        strainWoNO = strainWoNO - *BV.strainNullOffset;
        #endif
        strain = strainWoNO - GV.ADCNullOffset;
        break;
      case STRAIN_UNITS_RAW:
        switch (GV.strainChannel)
        {
        case STRAIN_CHANNEL_1ST:{
          strain = ADS869xStrain.getLastCode();
          // strainWoNO = strain;
          break;
        }
        case STRAIN_CHANNEL_2ND:{
          strain = ADS869xStrain.getLastCode();
          // strainWoNO = strain;
          break;
        }
        default:
          strain = ADS869xStrain.getLastCode();
          // strainWoNO = strain;
          break;
        }
        strainWoNO = strain;
        break;
      case STRAIN_UNITS_POSITION_RAW:
        strain = GV.positionInvertAxis * RSSIReader.getLastPositionRAW();
        strainWoNO = strain;
        break;
      case STRAIN_UNITS_DEFORMATION_RAW:
        switch (GV.machineInfo.deformation.sensorType)
        {
        case SENSOR_TYPE_ANALOG:{
          strain = ADCextExtens.getLastCode();
          break;
        }
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        case SENSOR_TYPE_ANALOG_0_10V:{
          strain = ADS869xExtens.getLastCode();
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT:{
          strain = ADS869xExtens.getLastCode2();
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT2:{
          strain = ADS869xExtens.getLastCode3();
          break;
        }
        #endif
        case SENSOR_TYPE_ENCODER:{
          strain = deformEncoder.GetExtendedTimerValue_RAW();
          break;
        }
        default:
          break;
        }
        strainWoNO = strain;
        break;
      case STRAIN_UNITS_DEFORMATION_KN:
        strainWoNO = GV.strainInvertAxis * ADCextExtens.calcDeformation(ADCextExtens.getLastCode());
        strain = strainWoNO - GV.ADCNullOffset;
        break;
      //default KN
      default:
        strainWoNO = GV.strainInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode());
        strain = strainWoNO - GV.ADCNullOffset;
        //if (abs(strain) > abs(oldStrain) + 30){
        //  strain = oldStrain;
        //}
        break;
      }
      #endif
    }
    if (GV.EnabledAcq & ACQ_DISPLACEMENT){
      if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_DIGITAL_RSSI){
        //TODO: timer for checking transfer timeout
        // RSSIReader.startGettingPosition();
        if (GV.WaitAcqComplete & WAIT_ACQ_COMPLETE_DISPLACEMENT){
          std::chrono::microseconds startTime = SystemTimer.elapsed_time();
          while (RSSIReader.getTransferStatus() != SSI_DMA_SPI_TRANSFER_COMPLETE){
            if(SystemTimer.elapsed_time() - startTime >= this->spiTransactionTimeout){
              break;
            }
          }
        }
        if(RSSIReader.getTransferStatus() == SSI_DMA_SPI_TRANSFER_COMPLETE){
          RSSIReader.clearTransferStatus();
          switch (GV.PositionUnits)
          {
          case POSITION_UNITS_MM:
            positionWoNO = GV.positionInvertAxis * RSSIReader.getLastPosition();
            position = positionWoNO - GV.positionNullOffset;
            break;
          case POSITION_UNITS_RAW:
            positionWoNO = GV.positionInvertAxis * RSSIReader.getLastPosition();
            position = positionWoNO - GV.positionNullOffset;
            break;
          case POSITION_UNITS_STRAIN_MM:
            #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
            positionWoNO = GV.positionInvertAxis * ADCext.calcStrain(ADCext.getLastCode());
            #else
            positionWoNO = GV.positionInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode());
            #endif
            position = positionWoNO - GV.positionNullOffset;
            break;
          case POSITION_UNITS_STRAIN_RAW:
            #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
            positionWoNO = ADCext.getLastCode();
            position = ADCext.getLastCode();
            #else
            positionWoNO = ADS869xStrain.getLastCode();
            position = ADS869xStrain.getLastCode();
            #endif
            break;
          default:
            positionWoNO = GV.positionInvertAxis * RSSIReader.getLastPosition();
            position = positionWoNO - GV.positionNullOffset;
            break;
          }
        }
      }
      if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_ENCODER){
        //position = GV.positionInvertAxis * (position + displEncoder.getLastAddition()) - GV.positionNullOffset;
        position = GV.positionInvertAxis * displEncoder.getLastPosition() - GV.positionNullOffset;
        #if (BATTERY == BATTERY_AVAILABLE)
        *BV.encoderPulses = displEncoder.getLastPulsesCount();
        #endif
        switch (GV.PositionUnits)
          {
          case POSITION_UNITS_MM:
            positionWoNO = GV.positionInvertAxis * displEncoder.getLastPosition();
            if(!std::isnan(GV.SSINullOffset)){
              position = positionWoNO + GV.SSIPositionOffset - GV.positionNullOffset - GV.SSINullOffset;
            }else{
              position = positionWoNO - GV.positionNullOffset;
            }
            break;
          case POSITION_UNITS_RAW:
            positionWoNO = displEncoder.getLastPulsesCount();
            position = positionWoNO;
            break;
          case POSITION_UNITS_STRAIN_MM:
            #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
            positionWoNO = GV.positionInvertAxis * ADCext.calcStrain(ADCext.getLastCode());
            #else
            positionWoNO = GV.positionInvertAxis * ADS869xStrain.calcStrain(ADS869xStrain.getLastCode());
            #endif
            position = positionWoNO - GV.positionNullOffset;
            break;
          case POSITION_UNITS_STRAIN_RAW:
            #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
            positionWoNO = ADCext.getLastCode();
            position = ADCext.getLastCode();
            #else
            positionWoNO = ADS869xStrain.getLastCode();
            position = ADS869xStrain.getLastCode();
            #endif
            break;
          default:
            positionWoNO = GV.positionInvertAxis * displEncoder.getLastPosition();
            position = positionWoNO - GV.positionNullOffset;
            break;
          }
      }
	  //switch (GV.PositionUnits)
    //    {
    //    case POSITION_UNITS_MM:
    //      break;
    //    case POSITION_UNITS_RAW:
    //      break;
    //    case POSITION_UNITS_STRAIN_MM:
    //      position = GV.positionInvertAxis * ADCext.calcStrain(ADCext.getLastCode()) - GV.positionNullOffset;
    //      break;
    //    case POSITION_UNITS_STRAIN_RAW:
    //      position = ADCext.getLastCode();
    //      break;
    //    default:
    //      break;
    //    }
	  // GV.roCurrentPositionTime = SystemTimer.elapsed_time().count();
    }
    if (GV.EnabledAcq & ACQ_DEFORMATION){
      switch (GV.DeformationChannel)
      {
      case DEFORMATION_1ST_CHANNEL:
        if ((GV.machineInfo.deformation.activeChannels & DEFORMATION_1ST_CHANNEL_MASK) == 0b0001){
          GV.machineInfo.deformation.sensorType = GV.machineInfo.deformation.sensorTypes[0];
        }else{
          GV.machineInfo.deformation.sensorType = SENSOR_TYPE_UNDEFINED;
        }
        break;
      case DEFORMATION_2ND_CHANNEL:
        if ((GV.machineInfo.deformation.activeChannels & DEFORMATION_2ND_CHANNEL_MASK) == 0b0010){
          GV.machineInfo.deformation.sensorType = GV.machineInfo.deformation.sensorTypes[1];
        }else{
          GV.machineInfo.deformation.sensorType = SENSOR_TYPE_UNDEFINED;
        }
        break;
      case DEFORMATION_3RD_CHANNEL:
        if ((GV.machineInfo.deformation.activeChannels & DEFORMATION_3RD_CHANNEL_MASK) == 0b0100){
          GV.machineInfo.deformation.sensorType = GV.machineInfo.deformation.sensorTypes[2];
        }else{
          GV.machineInfo.deformation.sensorType = SENSOR_TYPE_UNDEFINED;
        }
        break;
      case DEFORMATION_4TH_CHANNEL:
        if ((GV.machineInfo.deformation.activeChannels & DEFORMATION_4TH_CHANNEL_MASK) == 0b1000){
          GV.machineInfo.deformation.sensorType = GV.machineInfo.deformation.sensorTypes[3];
        }else{
          GV.machineInfo.deformation.sensorType = SENSOR_TYPE_UNDEFINED;
        }
        break;
      default:
        break;
      }
      switch (GV.machineInfo.deformation.sensorType)
      {
      case SENSOR_TYPE_ANALOG:{
        if (GV.WaitAcqComplete & WAIT_ACQ_COMPLETE_DEFORMATION){
          std::chrono::microseconds startTime = SystemTimer.elapsed_time();
          while (ADCextExtens.getTransferStatus() != ADS8320_Extens_DMA_SPI_TRANSFER_COMPLETE){
            if(SystemTimer.elapsed_time() - startTime >= this->spiTransactionTimeout){
              break;
            }
          }
        }
        if(ADCextExtens.getTransferStatus() == ADS8320_Extens_DMA_SPI_TRANSFER_COMPLETE){
          ADCextExtens.clearTransferStatus();
          //TODO: fucking ADC, FIX IT!
          //filtering high amplitude error value
          //float oldDeformation = deformation;
          switch (GV.DeformationUnits)
          {
          case DEFORMATION_UNITS_MM:
            deformationWoNO = GV.deformationInvertAxis * ADCextExtens.calcDeformation(ADCextExtens.getLastCode());
            deformation = deformationWoNO - GV.deformationNullOffset;
            //if (abs(deformation) > abs(oldDeformation) + 30){
            //  deformation = oldDeformation;
            //}
            break;
          case DEFORMATION_UNITS_RAW:
            deformationWoNO = ADCextExtens.getLastCode();
            deformation = ADCextExtens.getLastCode();
            break;
          default:
            deformationWoNO = GV.deformationInvertAxis * ADCextExtens.calcDeformation(ADCextExtens.getLastCode());
            deformation = deformationWoNO - GV.deformationNullOffset;
            //if (abs(deformation) > abs(oldDeformation) + 30){
            //  deformation = oldDeformation;
            //}
            break;
          }
        }
        break;
      }
      #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
      case SENSOR_TYPE_ANALOG_0_10V:{
        ADS869xExtens.transferBlocking();
        switch (GV.DeformationUnits)
        {
        case DEFORMATION_UNITS_MM:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation(ADS869xExtens.getLastCode());
          deformation = deformationWoNO - GV.deformationNullOffset;
          //if (abs(deformation) > abs(oldDeformation) + 30){
          //  deformation = oldDeformation;
          //}
          break;
        case DEFORMATION_UNITS_RAW:
          deformationWoNO = ADS869xExtens.getLastCode();
          deformation = ADS869xExtens.getLastCode();
          break;
        default:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation(ADS869xExtens.getLastCode());
          deformation = deformationWoNO - GV.deformationNullOffset;
          //if (abs(deformation) > abs(oldDeformation) + 30){
          //  deformation = oldDeformation;
          //}
          break;
        }
        break;
      }
      case SENSOR_TYPE_ANALOG_LVDT:{
        ADS869xExtens.transferBlocking2();
        switch (GV.DeformationUnits)
        {
        case DEFORMATION_UNITS_MM:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation2(ADS869xExtens.getLastCode2());
          deformation = deformationWoNO - GV.deformationNullOffset;
          //if (abs(deformation) > abs(oldDeformation) + 30){
          //  deformation = oldDeformation;
          //}
          break;
        case DEFORMATION_UNITS_RAW:
          deformationWoNO = ADS869xExtens.getLastCode2();
          deformation = ADS869xExtens.getLastCode2();
          break;
        default:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation2(ADS869xExtens.getLastCode2());
          deformation = deformationWoNO - GV.deformationNullOffset;
          //if (abs(deformation) > abs(oldDeformation) + 30){
          //  deformation = oldDeformation;
          //}
          break;
        }
        break;
      }
      case SENSOR_TYPE_ANALOG_LVDT2:{
       ADS869xExtens.transferBlocking3();
        switch (GV.DeformationUnits)
        {
        case DEFORMATION_UNITS_MM:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation3(ADS869xExtens.getLastCode3());
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        case DEFORMATION_UNITS_RAW:
          deformationWoNO = ADS869xExtens.getLastCode3();
          deformation = ADS869xExtens.getLastCode3();
          break;
        default:
          deformationWoNO = GV.deformationInvertAxis * ADS869xExtens.calcDeformation3(ADS869xExtens.getLastCode3());
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        }
        break;
      }
      case SENSOR_TYPE_ENCODER:{
        #if (PROJECT_NAME != PROJECT_NAME_MPD)
        switch (GV.DeformationUnits)
        {
        case DEFORMATION_UNITS_MM:
          deformationWoNO = GV.deformationInvertAxis * deformEncoder.GetExtendedTimerValue_MM();
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        case DEFORMATION_UNITS_RAW:
          deformationWoNO = GV.deformationInvertAxis * deformEncoder.GetExtendedTimerValue_RAW();
          deformation = deformationWoNO;
          break;
	case DEFORMATION_UNITS_STRAIN_RAW:
          deformation = ADCext.getLastCode();
          deformation = ADCext.getLastCode();
          break;
        case DEFORMATION_UNITS_POSITION_RAW:
          deformation = displEncoder.getLastPulsesCount();
          break;
        default:
          deformationWoNO = GV.deformationInvertAxis * deformEncoder.GetExtendedTimerValue_MM();
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        }
        #else
        switch (GV.DeformationUnits)
        {
        case DEFORMATION_UNITS_MM:
          deformationWoNO = GV.deformationInvertAxis * (deformEncoder.GetExtendedTimerValue_MM() + deformEncoder2.GetExtendedTimerValue_MM())/2;
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        case DEFORMATION_UNITS_RAW:
          deformationWoNO = GV.deformationInvertAxis * (deformEncoder.GetExtendedTimerValue_RAW() + deformEncoder2.GetExtendedTimerValue_RAW())/2;
          deformation = deformationWoNO;
          break;
        case DEFORMATION_UNITS_STRAIN_RAW:
          deformation = ADCext.getLastCode();
          deformation = ADCext.getLastCode();
          break;
        case DEFORMATION_UNITS_POSITION_RAW:
          deformation = displEncoder.getLastPulsesCount();
          break;
        default:
          deformationWoNO = GV.deformationInvertAxis * (deformEncoder.GetExtendedTimerValue_MM() + deformEncoder2.GetExtendedTimerValue_MM())/2;
          deformation = deformationWoNO - GV.deformationNullOffset;
          break;
        }
        #endif
        break;
      }
      #endif
      default:
        break;
      }
      //for calibration
      switch (GV.DeformationUnits)
      {
      case DEFORMATION_UNITS_STRAIN_RAW:
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        deformation = ADCext.getLastCode();
        #else
        deformation = ADS869xStrain.getLastCode();
        #endif
        break;
      case DEFORMATION_UNITS_POSITION_RAW:
        deformation = displEncoder.getLastPulsesCount();
        break;
      case DEFORMATION_UNITS_POSITION_MM:
        deformation = position * GV.deformationInvertAxis;
        break;
      default:
        break;
      }
    }
    this->testSignal();
    GV.roCurrentPosition = displacement_DIRECTING;
    GV.roCurrentStrain = strain_DIRECTING;
    GV.roCurrentDeformation = deformation_DIRECTING;
    if(GV.avCounter < averageNumber){
      GV.avCounter++;
      GV.currentAvPositionSum += GV.roCurrentPosition;
      GV.currentAvStrainSum += GV.roCurrentStrain;
      GV.currentAvDeformationSum += GV.roCurrentDeformation;
    }
    else{
      GV.roCurrentAvPosition = GV.currentAvPositionSum / GV.avCounter;
      GV.roCurrentAvStrain = GV.currentAvStrainSum / GV.avCounter;
      GV.roCurrentAvDeformation = GV.currentAvDeformationSum / GV.avCounter; 
      GV.avCounter = 0;
      GV.currentAvPositionSum = 0.0;
      GV.currentAvStrainSum = 0.0;
      GV.currentAvDeformationSum = 0.0;
    }
    if (getStatusOfUnblokFiltering()){
      setStatusOfFilteringSet(true);
      //debugPin.write(1);
      dataFiltersSet->getFilteredDataFromSet();
      //debugPin.write(0);
    }
    else {
      if (getStatusOfFilteringSet()){
        dataFiltersSet->resetAllFilterCollection();
}
      dataFiltersSet->setRawDataInFiltersSetTargets();
      setStatusOfFilteringSet(false);
    }
    displacement_DIRECTING = getPosition(DIRECTING);
    displacement_MONITORING = getPosition(MONITORING);
    displacement_ANSWERING = getPosition(ANSWERING);
    displacement_DISPLAYING = getPosition(DISPLAYING);
    strain_DIRECTING = getStrain(DIRECTING);
    strain_MONITORING = getStrain(MONITORING);
    strain_ANSWERING = getStrain(ANSWERING);
    strain_DISPLAYING = getStrain(DISPLAYING);
    deformation_DIRECTING = getDeformation(DIRECTING);
    deformation_MONITORING = getDeformation(MONITORING);
    deformation_ANSWERING = getDeformation(ANSWERING);
    deformation_DISPLAYING = getDeformation(DISPLAYING);
}
void ExecutionThread::testSignal(void){
  switch (GV.TestSignalInfo.type){
    case TEST_SIGNAL_NONE:{
      break;
    }
    case TEST_SIGNAL_SIN_GENERATION:{
      position = GV.TestSignalInfo.sinSignalAmplitude/4 * sin(angle) + GV.TestSignalInfo.sinSignalAmplitude/4 + 100 + (((double) rand() / (RAND_MAX)) + 1)/250 - 105;//rand() % 100;
      angle = angle + GV.TestSignalInfo.sinSignalIncrement;
      strain = GV.TestSignalInfo.sinSignalAmplitude/4 * sin(angle) + GV.TestSignalInfo.sinSignalAmplitude/4 + (((double) rand() / (RAND_MAX)) + 1)/50 - 25;
      deformation = GV.TestSignalInfo.sinSignalAmplitude/4 * sin(angle) + GV.TestSignalInfo.sinSignalAmplitude/4 + (((double) rand() / (RAND_MAX)) + 1)/20;
      break;
    }
    case TEST_SIGNAL_CONST_VALUES:{
      position = GV.TestSignalInfo.constSignalPosition;
      strain = GV.TestSignalInfo.constSignalStrain;
      deformation = GV.TestSignalInfo.constSignalDeformation;
      break;
    }
    case TEST_SIGNAL_CONST_VALUES_RANDOM:{
      position = GV.TestSignalInfo.constSignalPosition + (((double) rand() / (RAND_MAX)) + 1)/250;
      strain = GV.TestSignalInfo.constSignalStrain + (((double) rand() / (RAND_MAX)) + 1)/50;
      deformation = GV.TestSignalInfo.constSignalDeformation + (((double) rand() / (RAND_MAX)) + 1)/50;
      break;
    }
    default:
      break;
  }
}
void ExecutionThread::startAcq(void){
    if(GV.EnabledAcq & ACQ_DISPLACEMENT){
      if(GV.machineInfo.displacement.sensorType == SENSOR_TYPE_DIGITAL_RSSI){
        if (RSSIReader.getTransferStatus() == SSI_DMA_SPI_TRANSFER_WAIT){  
          RSSIReader.startGettingPosition();
        }
      }
    }
    #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
    if ((GV.EnabledAcq & ACQ_STRAIN) && (ADCext.getTransferStatus() == ADS8320_DMA_SPI_TRANSFER_WAIT)){
      ADCext.startGettingCode();
    }
    #else
    // if ((GV.EnabledAcq & ACQ_STRAIN) && (ADS869xStrain.getTransferStatus() == ADS869xStr_DMA_SPI_TRANSFER_WAIT)){
    //   ADS869xStrain.clearTransferStatus();
    //   ADS869xStrain.startTransfer(false);
    // }
    #endif
    if ((GV.EnabledAcq & ACQ_DEFORMATION) && (ADCextExtens.getTransferStatus() == ADS8320_Extens_DMA_SPI_TRANSFER_WAIT)){
      ADCextExtens.startGettingCode();
    }
    #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
    if ((GV.EnabledAcq & ACQ_DEFORMATION) && (ADS869xExtens.getTransferStatus() == ADS869xExt_DMA_SPI_TRANSFER_WAIT)){
      ADS869xExtens.clearTransferStatus();
      ADS869xExtens.startTransfer(false);
      ADS869xExtens.startTransfer2(false);
      ADS869xExtens.startTransfer3(false);
    }
    #endif
}
void ExecutionThread::checkTimeAndWait(void){
    endTimerValue = frequencyTimer.elapsed_time();
     std::chrono::microseconds timeDifference = endTimerValue - startTimerValue;
    GV.currentModeFreq = DACFrequency;
    if (timeDifference >=  std::chrono::microseconds(static_cast<us_timestamp_t>(DACFrequency * 1000.0))){
      //continue;
    }
    else{
      std::chrono::microseconds waitTime = std::chrono::microseconds(static_cast<us_timestamp_t>(DACFrequency * 1000.0)) - timeDifference;
      if (waitTime >= 1000us){
        ThisThread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(waitTime));
      }
      else{
        std::chrono::nanoseconds nsTime = std::chrono::duration_cast<std::chrono::nanoseconds>(waitTime);
        if (nsTime > 1000ns){
          //debugPin.write(0);
          wait_ns((nsTime - 1000ns).count());
        }
        //while(frequencyTimer.elapsed_time().count() - waitTime < endTimerValue){}
      }
    }
}
void ExecutionThread::modeExecute(void){
  // GV.PreviousDirection = GV.CurrentDirection;
  //motorDriver.enable(true);
  //motorDriver.oneStep();
  //motorDriver.changeDirection();
  //motorDriver.oneStep();
  //motorDriver.changeDirection();
  //motorDriver.enable(false);
  switch(DACState){
        case DAC_STATE_NONE:{
          //moveEnable.write(0);
          //DACVoltage = 0;
          valveVoltageToSend = DACVoltage;
          DACFrequency = GV.ConstDisplacementModeParams.ModeFrequency;
          //direction->set(0);
          //GV.CurrentDirection = 0;
          if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
            switch (GV.WorkMode){
              case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{ 
                DACext.setVoltage(DACVoltage);
                break;
              }
              default:
                GV.Mode = prevDACState;
                DACState = prevDACState;
                break;
            }
          }
          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
            
          }
          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
            
          }
          break;
        }
        case DAC_STATE_CONST_LEVEL:{
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{ 
              //moveEnable.write(0);
              DACFrequency = GV.ConstModeParams.ConstFrequency;
              if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                DACVoltage = GV.ConstModeParams.Voltage;
                valveVoltageToSend = DACVoltage;
                if (DACVoltage == 0.0){
                  direction->set(0);
                }
                else{ 
                  direction->set(GV.ConstModeParams.Direction * GV.pistonMode * GV.valveDirectionMode);
                }
              }
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                motorDriver.setDirection( direction->calculateBoolDirection(GV.ConstModeParams.Direction * GV.pistonMode * GV.valveDirectionMode));
              }
              #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                LimSwDirecton = GV.ConstModeParams.Direction * GV.pistonMode * GV.valveDirectionMode;
              #endif
              GV.CurrentDirection = GV.ConstModeParams.Direction;
              if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                DACext.setVoltage(DACVoltage);
              }
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                DACVoltage = GV.ConstModeParams.Voltage;
                #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                switch (GV.LimitSwitchState)
                {
                  case LIMIT_SWITCH_STATE_ONE:{
                    if(LimSwDirecton > 0){
                    
                    }else{
                      motorDriver.setSteps(static_cast<int>(DACVoltage * GV.ampCoef * GV.conversionCoef ));
                    }
                    break;
                  }
                  case LIMIT_SWITCH_STATE_TWO:{
                    if(LimSwDirecton < 0){
                    
                    }else{
                      motorDriver.setSteps(static_cast<int>(DACVoltage * GV.ampCoef * GV.conversionCoef ));
                    }
                    break;
                  }
                  case LIMIT_SWITCH_STATE_UNDEFINED:{
                    motorDriver.setSteps(static_cast<int>(DACVoltage * GV.ampCoef * GV.conversionCoef ));
                    break;
                  }
                  default:
                    break;
                }
                #else
                motorDriver.setSteps(static_cast<int>(DACVoltage * GV.ampCoef * GV.conversionCoef ));
                #endif
              }
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                  DACVoltage = GV.ConstModeParams.Voltage;
                  dir = direction->calculateBoolDirection(GV.ConstModeParams.Direction * GV.pistonMode * GV.valveDirectionMode * GV.positionAxisMode);
                  motorDriver.setDirection(dir);
                  motorDriver.setSteps(static_cast<uint32_t>(DACVoltage * GV.ampCoef * GV.conversionCoef ));
                  if(dir)
                    *BV.valvePosition += GV.valveInvertAxis * static_cast<uint32_t>(DACVoltage * GV.ampCoef * GV.conversionCoef );
                  else
                    *BV.valvePosition += (-1) * GV.valveInvertAxis * static_cast<uint32_t>(DACVoltage * GV.ampCoef * GV.conversionCoef );
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_DISP_CONST:{
          DACFrequency = GV.ConstDisplacementModeParams.ModeFrequency;
          switch (GV.ConstDisplacementModeParams.State){
            case CONST_DISPLACEMENT_MODE_STATE_RESET:{
              //moveEnable.write(1);
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)        
              EncoderBuffer.reset();
#endif
              GV.msPositionCounter = 0;
              GV.mmLastPosition = GV.roCurrentPosition;
              //nullPosition = position;
        //      constDisplacementPID->reset();
        //      constDisplacementPID->setCoefs(
        //            GV.ConstDisplacementModeParams.PIDParams.Kp, 
        //            GV.ConstDisplacementModeParams.PIDParams.Ki, 
        //            GV.ConstDisplacementModeParams.PIDParams.Kd);
              //clear variables
              GV.ConstDisplacementModeParams.CurrentPosition = GV.roCurrentAvPosition;//GV.AveragePosition.get();
        //      GV.ConstDisplacementModeParams.PIDCorrection = 0;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_HOLD;
              if(GV.ConstDisplacementModeParams.Speed > GV.ConstDisplacementModeParams.MaxSpeed){
                GV.ConstDisplacementModeParams.Speed = GV.ConstDisplacementModeParams.MaxSpeed;
              }
              //dataDecimationCounter = GV.DataDecimationCoeff;
              //speed calculation
              if(GV.ConstDisplacementModeParams.Speed != 0.0){
                if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                  speedCalibration.getValue(GV.ConstDisplacementModeParams.Speed, 
                                            GV.ConstDisplacementModeParams.PIDParams.Kp, 
                                            GV.ConstDisplacementModeParams.PIDParams.Ki, 
                                            GV.ConstDisplacementModeParams.PIDParams.Kd, 
                                            GV.ConstDisplacementModeParams.MaxDeviation);
                }
                GV.ConstDisplacementModeParams.msCounter = (GV.TcycleTime / 1000);
                double section = GV.ConstDisplacementModeParams.CurrentPosition - GV.ConstDisplacementModeParams.PositionToHold;
                if(abs(section) >= GV.ConstDisplacementModeParams.delta){
                  if (section >= 0){
                    GV.ConstDisplacementModeParams.k = -GV.ConstDisplacementModeParams.Speed;
                  }else{
                    GV.ConstDisplacementModeParams.k = GV.ConstDisplacementModeParams.Speed;
                  }
                  GV.ConstDisplacementModeParams.b = GV.ConstDisplacementModeParams.CurrentPosition;
                  GV.ConstDisplacementModeParams.t = static_cast<uint32_t>((abs(GV.ConstDisplacementModeParams.CurrentPosition - GV.ConstDisplacementModeParams.PositionToHold)
                      /GV.ConstDisplacementModeParams.Speed) * 1000);
                  GV.ConstDisplacementModeParams.nextDesirePoint = GV.ConstDisplacementModeParams.k 
                                                                 * GV.ConstDisplacementModeParams.msCounter / 1000 
                                                                 + GV.ConstDisplacementModeParams.b;
                  GV.ConstDisplacementModeParams.speedEnable = true;
                }
                else{
                  GV.ConstDisplacementModeParams.nextDesirePoint = GV.ConstDisplacementModeParams.PositionToHold;
                }
              }else{
                GV.ConstDisplacementModeParams.msCounter = 0;
                GV.ConstDisplacementModeParams.nextDesirePoint = GV.ConstDisplacementModeParams.PositionToHold;
              }
              positionState = false;
              lastCorrection = percentage;
              break;
            }
            case CONST_DISPLACEMENT_MODE_STATE_HOLD:{
              //moveEnable.write(1);
              constDisplacementPID->setCoefs(
                      GV.ConstDisplacementModeParams.PIDParams.Kp, 
                      GV.ConstDisplacementModeParams.PIDParams.Ki, 
                      GV.ConstDisplacementModeParams.PIDParams.Kd);
              GV.ConstDisplacementModeParams.CurrentPosition = displacement_DIRECTING;
              //double nullPos = GV.ConstDisplacementModeParams.PositionToHold;
              // switch (GV.LimitSwitchState)
              // {
              // case LIMIT_SWITCH_STATE_ONE:
              //   if(GV.ConstDisplacementModeParams.nextDesirePoint > GV.MaxPosition){
              //     GV.ConstDisplacementModeParams.nextDesirePoint = GV.MaxPosition;
              //   }
              //   break;
              // case LIMIT_SWITCH_STATE_TWO:
              //   if(GV.ConstDisplacementModeParams.nextDesirePoint < GV.MaxPosition){
              //     GV.ConstDisplacementModeParams.nextDesirePoint = GV.MaxPosition;
              //   }
              //   break;
              // default:
              //   break;
              // }
              double nullPos = GV.ConstDisplacementModeParams.nextDesirePoint;
              //limit mode stop by theshold crossing
              if (!isnan(GV.strainSharedLowerLimit)&&!isnan(GV.strainSharedUpperLimit)
                  &&!isnan(GV.deformSharedLowerLimit)&&!isnan(GV.deformSharedUpperLimit)){

                if (isStrainCrossed()){
                  GV.ConstDisplacementModeParams.PositionToHold = GV.ConstDisplacementModeParams.CurrentPosition;
                  nullPos = GV.ConstDisplacementModeParams.CurrentPosition;
                  this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_STRAIN);
                  // this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH_VALUES, (uint32_t)LIMIT_REACH_STATUS_STRAIN,
                  //                              displacement_ANSWERING, strain_ANSWERING, deformation_ANSWERING);
                  setAllLimitsNAN();
                  #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
                  setNoneMode();
                  break;
                  #endif
                }
                if (isDeformationCrossed()){
                  GV.ConstDisplacementModeParams.PositionToHold = GV.ConstDisplacementModeParams.CurrentPosition;
                  nullPos = GV.ConstDisplacementModeParams.CurrentPosition;
                  this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DEFORMATION);
                  setAllLimitsNAN();
                  #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
                  setNoneMode();
                  break;
                  #endif
                }
                if (!isnan(GV.displSharedLowerLimit)&&!isnan(GV.displSharedUpperLimit)){

                  if (isDisplacementCrossed()){
                      this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DISPLACEMENT);
                      // this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH_VALUES, (uint32_t)LIMIT_REACH_STATUS_DISPLACEMENT,
                      //                          displacement_ANSWERING, strain_ANSWERING, deformation_ANSWERING);
                      setAllLimitsNAN();
                  }
                }
              }

              //reset PID by max deviation
              if (abs(GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) 
                      >= GV.ConstDisplacementModeParams.MaxDeviation){
                constDisplacementPID->reset();
              }
              //DEPRICATED:protection for overload: auto return piston to upper position
              //if (abs(nullPos - GV.ConstDisplacementModeParams.CurrentPosition) >= 0.1){
                //LimSwDirecton = -1;
              //  direction.set(-1);
                //GV.ConstModeParams.Voltage = 0.5;
              //  DACVoltage = 0.3;
              //  continue;
              //}
              float calculatedVoltage = 0;
              int calculatedSteps = 0;
              int calculatedPosition = 0;
              double correction;
              if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                correction = GV.positionAxisMode * constDisplacementPID->getCorrection(
                        nullPos, GV.ConstDisplacementModeParams.CurrentPosition);
              }
              if((GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE) || (GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE)){
                if(abs(GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) >= displEncoder.getStepValue() * GV.StepValueThreshold){
                  correction = GV.positionAxisMode * constDisplacementPID->getCorrection(
                        nullPos, GV.ConstDisplacementModeParams.CurrentPosition);
                }else{
                  correction = 0;
                  constDisplacementPID->reset();
                }
              }
			        PIDCorrectionToSend = correction;
              if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                calculatedVoltage = (correction / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                if (calculatedVoltage > GV.ConstDisplacementModeParams.MaxVoltage){
                  calculatedVoltage = GV.ConstDisplacementModeParams.MaxVoltage;
                }
                if (calculatedVoltage < -GV.ConstDisplacementModeParams.MaxVoltage){
                  calculatedVoltage = -GV.ConstDisplacementModeParams.MaxVoltage;
                }
                if(calculatedVoltage > 0){
                  LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
              }
                if(calculatedVoltage < 0){
                  LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                }
                if(calculatedVoltage == 0){
                  LimSwDirecton = 0;
                }
                switch (GV.LimitSwitchState)
                {
                  case LIMIT_SWITCH_STATE_ONE:
                    if(LimSwDirecton > 0){
                      // correction = 0;
                      setConstDisplMode();
                    }
                    break;
                  case LIMIT_SWITCH_STATE_TWO:
                    if(LimSwDirecton < 0){
                      // correction = 0;
                      setConstDisplMode();
                    }
                    break;
                  default:
                    break;
                }
              }
              valveVoltageToSend = calculatedVoltage;
              GV.currentModeDACvoltage = calculatedVoltage;
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                calculatedSteps = (correction / GV.motorStepValue * 100);
                stepsTest = calculatedSteps;
                if (calculatedSteps > (int)GV.ConstDisplacementModeParams.MaxSteps){
                  calculatedSteps = (int)GV.ConstDisplacementModeParams.MaxSteps;
                }
                if (calculatedSteps < (-1) * (int)GV.ConstDisplacementModeParams.MaxSteps){
                  calculatedSteps = (-1) * (int)GV.ConstDisplacementModeParams.MaxSteps;
                }
                #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                if(calculatedSteps > 0){
                  LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                }
                if(calculatedSteps < 0){
                  LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                }
                if(calculatedSteps == 0){
                  LimSwDirecton = 0;
                }
                switch (GV.LimitSwitchState)
                {
                  case LIMIT_SWITCH_STATE_ONE:
                    if(LimSwDirecton > 0){
                      correction = 0;
                      if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                      setNoneMode();
                    }
                      if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                        setConstDisplMode();
                      }
                    }
                    break;
                  case LIMIT_SWITCH_STATE_TWO:
                    if(LimSwDirecton < 0){
                      correction = 0;
                      if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                      setNoneMode();
                    }
                      if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                        setConstDisplMode();
                      }
                    }
                    break;
                  default:
                    break;
                }
                #endif
              }
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                calculatedSteps = abs(calculatedSteps);
                if(correction > 0){
                  motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                  if(abs(GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) >= displEncoder.getStepValue() * GV.StepValueThreshold){
                    //motorDriver.oneStep();
                    motorDriver.setSteps(calculatedSteps);
                    //pwm->setPWM(1, -1);
                  }else{
                    //constDisplacementPID->reset();
                    // setNoneMode();
                    // delayedAction.attach(callback(this, &ExecutionThread::setNoneMode), 1ms);
                  }
                }
                if(correction < 0){
                  motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                  if(abs(GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) >= displEncoder.getStepValue() * GV.StepValueThreshold){
                    //motorDriver.oneStep();
                    motorDriver.setSteps(calculatedSteps);
                    //pwm->setPWM(1, -1);
                  }else{
                    //constDisplacementPID->reset();
                    // setNoneMode();
                    // delayedAction.attach(callback(this, &ExecutionThread::setNoneMode), 1ms);
                  }
                }
                if(correction == 0){
                  //delayedAction.attach(callback(this, &ExecutionThread::setNoneMode), 100ms);
                }
              }
              //TMZeroPID.push(calculatedVoltage);
              if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                direction->setWithCorrection(calculatedVoltage * GV.valveDirectionMode);
                calculatedVoltage = abs(calculatedVoltage);
                DACext.setVoltage(calculatedVoltage);
              }
              if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                if(!positionState){
                  correction += lastCorrection;
                  percentage = correction;
                  if(percentage > GV.maxPercentage){
                    percentage = 1;
                  }
                  if(percentage < (-1) * GV.maxPercentage){
                    percentage = -1;
                  }
                  if(percentage > 0){
                    if(((GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) < 0) && 
                      (((uint32_t)*BV.valvePosition) > (GV.middlePosition + GV.middleUpThreshold))){
                      calculatedPosition = GV.middlePosition - GV.middleDownThreshold;
                      lastCorrection = 0;
                    }else{
                    calculatedPosition = (GV.maxPosition - (GV.middlePosition + GV.middleUpThreshold)) * percentage + (GV.middlePosition + GV.middleUpThreshold);
                  }
                  }
                  if(percentage < 0){
                    if(((GV.ConstDisplacementModeParams.PositionToHold - GV.ConstDisplacementModeParams.CurrentPosition) > 0) && 
                      (((uint32_t)*BV.valvePosition) < (GV.middlePosition - GV.middleDownThreshold))){
                      calculatedPosition = GV.middlePosition + GV.middleUpThreshold;
                      lastCorrection = 0;
                    }else{
                    calculatedPosition = (GV.middlePosition - GV.middleDownThreshold) * percentage / GV.positionDivider + (GV.middlePosition - GV.middleDownThreshold);
                  }
                  }
                  positionCounter = (calculatedPosition - *BV.valvePosition);
                  if(positionCounter > 0){
                    dir = direction->calculateBoolDirection(GV.valveDirectionMode);
                  }
                  if(positionCounter < 0){
                    dir = direction->calculateBoolDirection((-1) * GV.valveDirectionMode);
                  }
                  positionCounter = abs(positionCounter);
                  positionState = true;
                }
                else{
                  // if(counter < 5){
                  //   counter++;
                  // }
                  // else{
                    if(positionCounter > 0){
                      if((uint32_t)positionCounter < stepsCountPerCycle){
                        if(dir)
                          *BV.valvePosition += (GV.valveInvertAxis) * positionCounter;
                        else
                          *BV.valvePosition += ((-1) * GV.valveInvertAxis) * positionCounter;
                        motorDriver.setSteps(dir, positionCounter);
                        positionCounter = 0;
                      }else{
                        positionCounter -= stepsCountPerCycle;
                        if(dir)
                          *BV.valvePosition += (GV.valveInvertAxis) * stepsCountPerCycle;
                        else
                          *BV.valvePosition += ((-1) * GV.valveInvertAxis) * stepsCountPerCycle;
                        motorDriver.setSteps(dir, stepsCountPerCycle);
                      }
                    }
                    else{
                      positionState = false;
                    }
                    counter = 0;
                  // }
                  if(correction == 0){
                    percentage = 0;
                    positionState = false;
                    GV.Mode = DAC_STATE_CLOSE_VALVE;
                    GV.closeValveState = CLOSE_VALVE_STATE_RESET;
                  }
                }
              }
              break;
            }
            case CONST_DISPLACEMENT_MODE_STATE_EXIT:{
              //moveEnable.write(0);
              GV.Mode = DAC_STATE_NONE;
              // GV.strokeCounter = 0;
              GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
              break;
            }
            default:
              break;
          }
          break;
        } 
        case DAC_STATE_STRAIN_CONST:{
          //moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{
              DACFrequency = GV.ConstStrainModeParams.ModeFrequency;
              switch (GV.ConstStrainModeParams.State){
                case CONST_STRAIN_MODE_STATE_RESET:{
            //      constStrainPID->reset();
            //      constStrainPID->setCoefs(
            //            GV.ConstStrainModeParams.PIDParams.Kp, 
            //            GV.ConstStrainModeParams.PIDParams.Ki, 
            //            GV.ConstStrainModeParams.PIDParams.Kd);
                  //clear variables
                  GV.ConstStrainModeParams.CurrentStrain = GV.roCurrentAvStrain;//GV.AverageStrain.get();
            //      GV.ConstStrainModeParams.PIDCorrection = 0;
                  GV.ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_HOLD;
                  if(GV.ConstStrainModeParams.Speed > GV.ConstStrainModeParams.MaxSpeed){
                    GV.ConstStrainModeParams.Speed = GV.ConstStrainModeParams.MaxSpeed;
                  }
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  //speed calculation
                  if(GV.ConstStrainModeParams.Speed != 0.0){
                    if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                      strainSpeedCalibration.getValue(GV.ConstStrainModeParams.Speed, 
                                                GV.ConstStrainModeParams.PIDParams.Kp, 
                                                GV.ConstStrainModeParams.PIDParams.Ki, 
                                                GV.ConstStrainModeParams.PIDParams.Kd, 
                                                GV.ConstStrainModeParams.MaxDeviation);
                    }
                    GV.ConstStrainModeParams.msCounter = (GV.TcycleTime / 1000);
                    double section = GV.ConstStrainModeParams.CurrentStrain - GV.ConstStrainModeParams.StrainToHold;
                    if(abs(section) >= GV.ConstStrainModeParams.delta){
                      if (section >= 0){
                        GV.ConstStrainModeParams.k = -GV.ConstStrainModeParams.Speed;
                      }else{
                        GV.ConstStrainModeParams.k = GV.ConstStrainModeParams.Speed;
                      }
                      GV.ConstStrainModeParams.b = GV.ConstStrainModeParams.CurrentStrain;
                      GV.ConstStrainModeParams.t = static_cast<uint32_t>((abs(GV.ConstStrainModeParams.CurrentStrain - GV.ConstStrainModeParams.StrainToHold)
                          /GV.ConstStrainModeParams.Speed) * 1000);
                      GV.ConstStrainModeParams.nextDesirePoint = GV.ConstStrainModeParams.k 
                                                               * GV.ConstStrainModeParams.msCounter / 1000 
                                                               + GV.ConstStrainModeParams.b;
                      GV.ConstStrainModeParams.speedEnable = true;
                    }
                    else{
                      GV.ConstStrainModeParams.nextDesirePoint = GV.ConstStrainModeParams.StrainToHold;
                    }
                  }else{
                    GV.ConstStrainModeParams.msCounter = 0;
                    GV.ConstStrainModeParams.nextDesirePoint = GV.ConstStrainModeParams.StrainToHold;
                  }
                  positionState = false;
                  lastCorrection = percentage;
                  break;
                }
                case CONST_STRAIN_MODE_STATE_HOLD:{
                  constStrainPID->setCoefs(
                          GV.ConstStrainModeParams.PIDParams.Kp, 
                          GV.ConstStrainModeParams.PIDParams.Ki, 
                          GV.ConstStrainModeParams.PIDParams.Kd);
                  GV.ConstStrainModeParams.CurrentStrain = strain_DIRECTING;
                  //double nullStrain = GV.ConstStrainModeParams.StrainToHold;
                  double nullStrain = GV.ConstStrainModeParams.nextDesirePoint;
                  //limit mode stop by theshold crossing
                  if (!isnan(GV.displSharedLowerLimit)&&!isnan(GV.displSharedUpperLimit)
                  &&!isnan(GV.deformSharedLowerLimit)&&!isnan(GV.deformSharedUpperLimit)){

                    if (isDisplacementCrossed()){
                      GV.ConstStrainModeParams.StrainToHold = GV.ConstStrainModeParams.CurrentStrain;
                      nullStrain = GV.ConstStrainModeParams.CurrentStrain;
                      this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DISPLACEMENT);
                      setAllLimitsNAN();
                    }
                    if (isDeformationCrossed()){
                      GV.ConstStrainModeParams.StrainToHold = GV.ConstStrainModeParams.CurrentStrain;
                      nullStrain = GV.ConstStrainModeParams.CurrentStrain;
                      this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DEFORMATION);
                      setAllLimitsNAN();
                    }
                    if (!isnan(GV.strainSharedLowerLimit)&&!isnan(GV.strainSharedUpperLimit)){

                      if (isStrainCrossed()){
                          this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_STRAIN);
                          // this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH_VALUES, (uint32_t)LIMIT_REACH_STATUS_STRAIN,
                          //                      displacement_ANSWERING, strain_ANSWERING, deformation_ANSWERING);
                          setAllLimitsNAN();
                      }
                    }
                  }
                  //reset PID by max deviation
                  if (abs(nullStrain - GV.ConstStrainModeParams.CurrentStrain) 
                          >= GV.ConstStrainModeParams.MaxDeviation){
                    constStrainPID->reset();
                  }
                  //DEPRICATED:protection for overload: auto return piston to upper position
                  //if (abs(nullPos - GV.ConstDisplacementModeParams.CurrentPosition) >= 0.1){
                    //LimSwDirecton = -1;
                  //  direction.set(-1);
                    //GV.ConstModeParams.Voltage = 0.5;
                  //  DACVoltage = 0.3;
                  //  continue;
                  //}
                  int calculatedSteps = 0;
                  int calculatedPosition = 0;
                  double correction = GV.strainAxisMode * constStrainPID->getCorrection(
                          nullStrain, GV.ConstStrainModeParams.CurrentStrain);
                  PIDCorrectionToSend = correction;
                  //float calculatedVoltage = (((((correction) * GV.ConstStrainModeParams.SampleLength)
                  //                            / GV.ConstStrainModeParams.YoungModulus)
                  //                            / GV.ConstStrainModeParams.SampleCut) 
                  //                            / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                  //double Imax = 0.015;//A
                  //double Qv = 0.0005;//m3/sec
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                  float calculatedVoltage = (correction * 50 //* (GV.ConstStrainModeParams.SampleLength/1000) 
                        * GV.ValveParams.Imax) / ((DACFrequency/1000.0) * GV.ValveParams.Qvalve 
                        * GV.ConstStrainModeParams.YoungModulus * 1000000);
                  if (calculatedVoltage > GV.ConstStrainModeParams.MaxVoltage){
                    calculatedVoltage = GV.ConstStrainModeParams.MaxVoltage;
                  }
                  if (calculatedVoltage < -GV.ConstStrainModeParams.MaxVoltage){
                    calculatedVoltage = -GV.ConstStrainModeParams.MaxVoltage;
                  }
                  #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedVoltage > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedVoltage < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedVoltage == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          correction = 0;
                          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                            setNoneMode();
                          }
                          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                            setConstDisplMode();
                          }
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          correction = 0;
                          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                            setNoneMode();
                          }
                          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                            setConstDisplMode();
                          }
                        break;
                      default:
                        break;
                    }
                  #endif
                  GV.currentModeDACvoltage = calculatedVoltage;
                  valveVoltageToSend = calculatedVoltage;
                  //TMZeroPID.push(calculatedVoltage);
                  direction->setWithCorrection(calculatedVoltage * GV.valveDirectionMode);
                  calculatedVoltage = abs(calculatedVoltage);
                  DACext.setVoltage(calculatedVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    // calculatedSteps = (correction / motorStepValue / 50.0);
                    calculatedSteps = (correction / (GV.motorStepValue * GV.ConstStrainModeParams.YoungModulus));
                    if (calculatedSteps > (int)GV.ConstStrainModeParams.MaxSteps){
                      calculatedSteps = (int)GV.ConstStrainModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.ConstStrainModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.ConstStrainModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          correction = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          correction = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(correction > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      // if(abs(correction) >= displEncoder.getStepValue()){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        // motorDriver.setSteps(1);
                      // }
                    }
                    if(correction < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      // if(abs(correction) >= displEncoder.getStepValue()){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        // motorDriver.setSteps(1);
                      // }
                    }
                    if(correction == 0){
                    
                    }
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                    if(!positionState){
                      correction += lastCorrection;
                      percentage = correction;
                      if(percentage > GV.maxPercentage){
                        percentage = 1;
                      }
                      if(percentage < (-1) * GV.maxPercentage){
                        percentage = -1;
                      }
                      if(percentage > 0){
                        calculatedPosition = (GV.maxPosition - (GV.middlePosition + GV.middleUpThreshold)) * percentage + (GV.middlePosition + GV.middleUpThreshold);
                      }
                      if(percentage < 0){
                        calculatedPosition = (GV.middlePosition - GV.middleDownThreshold) * percentage / GV.positionDivider + (GV.middlePosition - GV.middleDownThreshold);
                      }
                      positionCounter = (calculatedPosition - *BV.valvePosition);
                      if(positionCounter > 0){
                        dir = direction->calculateBoolDirection(GV.valveDirectionMode);
                      }
                      if(positionCounter < 0){
                        dir = direction->calculateBoolDirection((-1) * GV.valveDirectionMode);
                      }
                      positionCounter = abs(positionCounter);
                      positionState = true;
                    }
                    else{
                      if(positionCounter > 0){
                        if((uint32_t)positionCounter < stepsCountPerCycle){
                          if(dir)
                            *BV.valvePosition += (GV.valveInvertAxis) * positionCounter;
                          else
                            *BV.valvePosition += ((-1) * GV.valveInvertAxis) * positionCounter;
                          motorDriver.setSteps(dir, positionCounter);
                          positionCounter = 0;
                        }else{
                          positionCounter -= stepsCountPerCycle;
                          if(dir)
                            *BV.valvePosition += (GV.valveInvertAxis) * stepsCountPerCycle;
                          else
                            *BV.valvePosition += ((-1) * GV.valveInvertAxis) * stepsCountPerCycle;
                          motorDriver.setSteps(dir, stepsCountPerCycle);
                        }
                      }
                      else{
                        positionState = false;
                      }
                      if(correction == 0){
                        percentage = 0;
                        positionState = false;
                        GV.Mode = DAC_STATE_CLOSE_VALVE;
                        GV.closeValveState = CLOSE_VALVE_STATE_RESET;
                      }
                    }
                  }
                  break;
                }
                case CONST_STRAIN_MODE_STATE_EXIT:{
                  GV.ConstDisplacementModeParams.speedEnable = false;
                  GV.ConstDisplacementModeParams.PositionToHold = GV.roCurrentAvPosition;
                  GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                  GV.Mode = DAC_STATE_DISP_CONST;
                  // GV.strokeCounter = 0;
                  GV.ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
                  break;
                }
                default:
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_DISP_SIN:{
          //moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS:{
              DACFrequency = GV.SINDisplacementModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SINDisplacementModeParams.State){
                case SIN_DISPLACEMENT_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  //null point deviation minimize
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;
                  
                  //pre mode amplitude and null point attenuation data reset
                  
                  GV.nullPointAttenuationCounter = 0;
                  PrepareForAmplitudeTune(&GV.SINDisplacementModeParams);


                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinDisplacementPID->reset();
                  sinDisplacementPID->setCoefs(
                    GV.SINDisplacementModeParams.PIDParams.Kp, 
                    GV.SINDisplacementModeParams.PIDParams.Ki, 
                    GV.SINDisplacementModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SINDisplacementModeParams.AngleW = 0;
                  GV.SINDisplacementModeParams.AngleWBuffered = 0;
                  GV.SINDisplacementModeParams.CurrentPoint = GV.AveragePosition.get();
                  GV.SINDisplacementModeParams.DesirePoint = GV.AveragePosition.get();
                  GV.SINDisplacementModeParams.DesirePointBuffered = GV.SINDisplacementModeParams.DesirePoint;
                  GV.SINDisplacementModeParams.NullPointDisplacement = GV.AveragePosition.get();
                  GV.SINDisplacementModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SINDisplacementModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SINDisplacementModeParams.InternalCounter = 0;
                  GV.SINDisplacementModeParams.InternalCounterBuffered = 0;
                  GV.SINDisplacementModeParams.PIDCorrection = 0;
                  sinDispCyclesTrigger->push(false);
                  PIDCorrectionToSend = GV.SINDisplacementModeParams.PIDCorrection;
                  GV.SINDisplacementModeParams.DACVoltage = 0;
                  valveVoltageToSend = GV.SINDisplacementModeParams.DACVoltage;
                  GV.SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SINDisplacementModeParams.NullPointDisplacement);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SINDisplacementModeParams.UpAmplitude 
                                                    + 0.01 * GV.SINDisplacementModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SINDisplacementModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(5.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SINDisplacementModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow(5.0);
                  //start timer
                  //GV.SINDisplacementModeParams.Count.start();
                  //GV.SINDisplacementModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
                }
                case SIN_DISPLACEMENT_MODE_STATE_GENERATE:{
                  if(GV.SINDisplacementModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SINDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SINDisplacementModeParams);
                  }
                  //GV.tmpDataForTesting = displacement_MONITORING  + GV.addNullPoint;
                 
                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SINDisplacementModeParams.currentAmplitudeDirection =  GV.SINDisplacementModeParams.currentAmplitudeDirectionBuffered;
                  GV.SINDisplacementModeParams.DesirePoint =                GV.SINDisplacementModeParams.DesirePointBuffered;
                  GV.SINDisplacementModeParams.AngleW =                     GV.SINDisplacementModeParams.AngleWBuffered;
                  GV.SINDisplacementModeParams.InternalCounter =            GV.SINDisplacementModeParams.InternalCounterBuffered;
                  if (GV.SINDisplacementModeParams.waitForPIDReset){
                    sinDisplacementPID->reset();
                    GV.SINDisplacementModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinDisplacementPID->setCoefs(
                    GV.SINDisplacementModeParams.PIDParams.Kp, 
                    GV.SINDisplacementModeParams.PIDParams.Ki, 
                    GV.SINDisplacementModeParams.PIDParams.Kd
                  );
                  //set current position
                  GV.SINDisplacementModeParams.CurrentPoint = displacement_DIRECTING;
                  if (abs(GV.SINDisplacementModeParams.DesirePoint - GV.SINDisplacementModeParams.CurrentPoint) 
                  >= GV.SINDisplacementModeParams.MaxDeviation){
                      sinDisplacementPID->reset();
                  }
                  //set PID correction
                  GV.SINDisplacementModeParams.PIDCorrection = GV.positionAxisMode * sinDisplacementPID->getCorrection(
                    GV.SINDisplacementModeParams.DesirePoint, 
                    GV.SINDisplacementModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SINDisplacementModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    GV.SINDisplacementModeParams.DACVoltage = (GV.SINDisplacementModeParams.PIDCorrection 
                      / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                     GV.SINDisplacementModeParams.DACVoltage += GV.prevModeDACvoltage;  
                    if (GV.SINDisplacementModeParams.DACVoltage > GV.SINDisplacementModeParams.MaxVoltage){
                      GV.SINDisplacementModeParams.DACVoltage = GV.SINDisplacementModeParams.MaxVoltage;
                    }
                    else if (GV.SINDisplacementModeParams.DACVoltage < -GV.SINDisplacementModeParams.MaxVoltage){
                      GV.SINDisplacementModeParams.DACVoltage = -GV.SINDisplacementModeParams.MaxVoltage;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SINDisplacementModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINDisplacementModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINDisplacementModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SINDisplacementModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SINDisplacementModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SINDisplacementModeParams.DACVoltage;
                    //set direction
                    direction->setWithCorrection(GV.SINDisplacementModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SINDisplacementModeParams.DACVoltage = abs(GV.SINDisplacementModeParams.DACVoltage);
                    DACVoltage = GV.SINDisplacementModeParams.DACVoltage + GV.DACConstError;
                    //debugPin.write(0);
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    calculatedSteps = (GV.SINDisplacementModeParams.PIDCorrection / GV.motorStepValue);
                    if (calculatedSteps > (int)GV.SINDisplacementModeParams.MaxSteps){
                      calculatedSteps = (int)GV.SINDisplacementModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SINDisplacementModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SINDisplacementModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SINDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SINDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SINDisplacementModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      // if(abs(GV.SINDisplacementModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SINDisplacementModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      // if(abs(GV.SINDisplacementModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SINDisplacementModeParams.PIDCorrection == 0){
                    
                    }
                  }

                  //exit condition
                  if ((GV.SINDisplacementModeParams.NumberOfCycles > 0) || GV.stopCurrentTestProcess){
                    if(GV.SINDisplacementModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SINDisplacementModeParams.InternalCounter >= 
                          GV.SINDisplacementModeParams.NumberOfCycles - GV.SINDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SINDisplacementModeParams.amplitudeTuneInfo.stop = true;
                        GV.SINDisplacementModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if ((GV.SINDisplacementModeParams.InternalCounter >= GV.SINDisplacementModeParams.NumberOfCycles || GV.stopCurrentTestProcess)){
                        GV.SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if ((GV.SINDisplacementModeParams.InternalCounter >= GV.SINDisplacementModeParams.NumberOfCycles) || GV.stopCurrentTestProcess){
                        GV.SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }
                case SIN_DISPLACEMENT_MODE_STATE_EXIT:{
                  //GV.Mode = DAC_STATE_NONE;
                  //GV.SINDisplacementModeParams.InternalCounter = 1;
                  GV.ConstDisplacementModeParams.PositionToHold = GV.SINDisplacementModeParams.NullPointDisplacement;
                  GV.SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
                  GV.SINDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  GV.ConstDisplacementModeParams.speedEnable = false;
                  GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                  //GV.SINDisplacementModeParams.Count.stop();
                  GV.Mode = DAC_STATE_DISP_CONST;
                  // GV.strokeCounter = 0;
                  break;
                }
                default:
                //GV.Mode = DAC_STATE_DISP_CONST;
                //GV.ConstDisplacementModeParams.PositionToHold = GV.SINDisplacementModeParams.NullPoint;
                //GV.ConstDisplacementModeParams.speedEnable = false;
                //GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                //GV.SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
                //GV.SINDisplacementModeParams.Count.stop();
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_STRAIN_SIN:{
          //moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{
              DACFrequency = GV.SINStrainModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SINStrainModeParams.State){
                case SIN_STRAIN_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;
                  
                  GV.nullPointAttenuationCounter = 0;
                  PrepareForAmplitudeTune(&GV.SINStrainModeParams);
                  if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS){
                    GV.cyclicProtectMode = CYCLIC_PROTECTION_OFF;
                  }


                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinStrainPID->reset();
                  sinStrainPID->setCoefs(
                    GV.SINStrainModeParams.PIDParams.Kp, 
                    GV.SINStrainModeParams.PIDParams.Ki, 
                    GV.SINStrainModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SINStrainModeParams.AngleW = 0;
                  GV.SINStrainModeParams.AngleWBuffered = 0;
                  GV.SINStrainModeParams.CurrentPoint = GV.AverageStrain.get();
                  GV.SINStrainModeParams.DesirePoint = GV.AverageStrain.get();
                  GV.SINStrainModeParams.DesirePointBuffered = GV.SINStrainModeParams.DesirePoint;
                  GV.SINStrainModeParams.NullPointDisplacement = GV.AveragePosition.get();
                  GV.SINStrainModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SINStrainModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SINStrainModeParams.InternalCounter = 0;
                  GV.SINStrainModeParams.InternalCounterBuffered = 0;
                  GV.SINStrainModeParams.PIDCorrection = 0;
                  sinStrainCyclesTrigger->push(false);
                  PIDCorrectionToSend = GV.SINStrainModeParams.PIDCorrection;
                  GV.SINStrainModeParams.DACVoltage = 0;
                  valveVoltageToSend = GV.SINStrainModeParams.DACVoltage;
                  GV.SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SINStrainModeParams.NullPointDisplacement);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SINStrainModeParams.UpAmplitude 
                                                    + 0.01 * GV.SINStrainModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SINStrainModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(1.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SINStrainModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow(5.0);
                  //start timer
                  //GV.SINStrainModeParams.Count.start();
                  //GV.SINStrainModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
            }
                case SIN_STRAIN_MODE_STATE_GENERATE:{
                  if(GV.SINStrainModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SINStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SINStrainModeParams);
                  }

                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SINStrainModeParams.currentAmplitudeDirection =  GV.SINStrainModeParams.currentAmplitudeDirectionBuffered;
                  GV.SINStrainModeParams.DesirePoint =                GV.SINStrainModeParams.DesirePointBuffered;
                  GV.SINStrainModeParams.AngleW =                     GV.SINStrainModeParams.AngleWBuffered;
                  GV.SINStrainModeParams.InternalCounter =            GV.SINStrainModeParams.InternalCounterBuffered;
                  if (GV.SINStrainModeParams.waitForPIDReset){
                    sinStrainPID->reset();
                    GV.SINStrainModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinStrainPID->setCoefs(
                    GV.SINStrainModeParams.PIDParams.Kp, 
                    GV.SINStrainModeParams.PIDParams.Ki, 
                    GV.SINStrainModeParams.PIDParams.Kd
                  );
                  //cyclic protection main process check strain
                  double compare = strain;
                  double desirePointTmp = GV.SINStrainModeParams.DesirePointBuffered;
                  if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS && GV.isBlindeRegion == 0
                    && ((compare < GV.deltaCyclicProtection && compare > -GV.deltaCyclicProtection)
                    || desirePointTmp * compare < 0.0)){
                      // if (desirePointTmp * compare < 0.0){
                      //   GV.diagnosticsStrain = 10 * compare;
                      // }
                      // else GV.diagnosticsStrain = compare;
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
                      setNoneMode();
#else
                      setConstDisplMode();
#endif
                      this -> sendNotification(COMMAND::TM_ONCE_CYCLIC_STRAIN_LIMIT_REACH, (uint32_t)LIMIT_REACH_STATUS_STRAIN);
                  }
                  else GV.diagnosticsStrain = 1;
                  //set current position
                  GV.SINStrainModeParams.CurrentPoint = strain_DIRECTING;
                  if (abs(GV.SINStrainModeParams.DesirePoint - GV.SINStrainModeParams.CurrentPoint) 
                  >= GV.SINStrainModeParams.MaxDeviation){
                      sinStrainPID->reset();
                  }
                  //set PID correction
                  GV.SINStrainModeParams.PIDCorrection = GV.strainAxisMode * sinStrainPID->getCorrection(
                    GV.SINStrainModeParams.DesirePoint, 
                    GV.SINStrainModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SINStrainModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    //GV.SINStrainModeParams.DACVoltage = (((((GV.SINStrainModeParams.PIDCorrection) 
                    //                            * GV.SINStrainModeParams.SampleLength)
                    //                            / GV.SINStrainModeParams.YoungModulus)
                    //                            / GV.SINStrainModeParams.SampleCut) 
                    //                            / (6.773 * (DACFrequency/1000.0)))/62.5;
                    //double Imax = 0.015;//A
                    //double Qv = 0.0005;//m3/sec
                    GV.SINStrainModeParams.DACVoltage = (GV.SINStrainModeParams.PIDCorrection * 50 
                            //* (GV.SINStrainModeParams.SampleLength/1000) 
                            * GV.ValveParams.Imax) 
                            / ((DACFrequency/1000.0) * GV.ValveParams.Qvalve 
                            * GV.SINStrainModeParams.YoungModulus * 1000000);

                    //(GV.SINStrainModeParams.PIDCorrection 
                    //  / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                    GV.SINStrainModeParams.DACVoltage += GV.prevModeDACvoltage;
                    if (GV.SINStrainModeParams.DACVoltage > GV.SINStrainModeParams.MaxVoltage){
                      GV.SINStrainModeParams.DACVoltage = GV.SINStrainModeParams.MaxVoltage;
                    } 
                    else if (GV.SINStrainModeParams.DACVoltage < -GV.SINStrainModeParams.MaxVoltage) {
                      GV.SINStrainModeParams.DACVoltage = -GV.SINStrainModeParams.MaxVoltage;
                    } 
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SINStrainModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINStrainModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINStrainModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SINStrainModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SINStrainModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SINStrainModeParams.DACVoltage;
                    //set direction
                    direction->setWithCorrection(GV.SINStrainModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SINStrainModeParams.DACVoltage = abs(GV.SINStrainModeParams.DACVoltage);
                    DACVoltage = GV.SINStrainModeParams.DACVoltage + GV.DACConstError;
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    calculatedSteps = (GV.SINStrainModeParams.PIDCorrection / (GV.motorStepValue * GV.SINStrainModeParams.YoungModulus));
                    if (calculatedSteps > (int)GV.SINStrainModeParams.MaxSteps){
                      calculatedSteps = (int)GV.SINStrainModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SINStrainModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SINStrainModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SINStrainModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SINStrainModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SINStrainModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      // if(abs(GV.SINStrainModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        //motorDriver.oneStep();
                        //motorDriver.setSteps(calculatedSteps);
                        motorDriver.setSteps(1);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SINStrainModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      // if(abs(GV.SINStrainModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        //motorDriver.oneStep();
                        //motorDriver.setSteps(calculatedSteps);
                        motorDriver.setSteps(1);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SINStrainModeParams.PIDCorrection == 0){
                    
                    }
                  }

                  //exit condition
                  if (GV.SINStrainModeParams.NumberOfCycles > 0 || GV.stopCurrentTestProcess){
                    if(GV.SINStrainModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SINStrainModeParams.InternalCounter >= 
                          GV.SINStrainModeParams.NumberOfCycles - GV.SINStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SINStrainModeParams.amplitudeTuneInfo.stop = true;
                        GV.SINStrainModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if (GV.SINStrainModeParams.InternalCounter >= GV.SINStrainModeParams.NumberOfCycles || GV.stopCurrentTestProcess){
                        GV.SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if (GV.SINStrainModeParams.InternalCounter >= GV.SINStrainModeParams.NumberOfCycles || GV.stopCurrentTestProcess){
                        GV.SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }   
                case SIN_STRAIN_MODE_STATE_EXIT:{
                  GV.ConstStrainModeParams.StrainToHold = GV.SINStrainModeParams.NullPointStrain;
                  GV.ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
                  GV.SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
                  GV.SINStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  GV.Mode = DAC_STATE_STRAIN_CONST;
                  // GV.strokeCounter = 0;
                  if (GV.SINStrainModeParams.holdConstDisplAtEnd) {
                    delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 1000ms);
                  }
                  //GV.SINStrainModeParams.Count.stop();
                  break;
                }
                default:
                  break;
              }
              break;
            }
            default:
            GV.Mode = prevDACState;
            DACState = prevDACState;
              break;
          }    
          break;
        }
        case DAC_STATE_CALIBRATION:{
          //moveEnable.write(0);
          break;
        }
        case DAC_STATE_DISP_USER_DEFINED:{
          //moveEnable.write(0);
          break;
        }
        case DAC_STATE_DISP_SINUS_BASED:{
          //moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS:{
              DACFrequency = GV.SinusBasedDisplacementModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SinusBasedDisplacementModeParams.State){
                case SIN_DISPLACEMENT_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;
                  //pre mode amplitude and null point attenuation data reset

                  PrepareForAmplitudeTune(&GV.SinusBasedDisplacementModeParams);

                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinDisplacementPID->reset();
                  sinDisplacementPID->setCoefs(
                    GV.SinusBasedDisplacementModeParams.PIDParams.Kp, 
                    GV.SinusBasedDisplacementModeParams.PIDParams.Ki, 
                    GV.SinusBasedDisplacementModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SinusBasedDisplacementModeParams.AngleW = 0;
                  GV.SinusBasedDisplacementModeParams.AngleWBuffered = 0;
                  GV.SinusBasedDisplacementModeParams.CurrentPoint = GV.AveragePosition.get();
                  GV.SinusBasedDisplacementModeParams.DesirePoint = GV.AveragePosition.get();
                  GV.SinusBasedDisplacementModeParams.DesirePointBuffered = GV.SinusBasedDisplacementModeParams.DesirePoint;
                  GV.SinusBasedDisplacementModeParams.NullPointDisplacement = GV.AveragePosition.get();
                  GV.SinusBasedDisplacementModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SinusBasedDisplacementModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SinusBasedDisplacementModeParams.InternalCounter = 0;
                  GV.SinusBasedDisplacementModeParams.InternalCounterBuffered = 0;
                  GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                  sinDispCyclesTrigger->push(false);
                  GV.SinusBasedDisplacementModeParams.DACVoltage = 0;
                  GV.SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SinusBasedDisplacementModeParams.NullPointDisplacement);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SinusBasedDisplacementModeParams.UpAmplitude 
                                                    + 0.01 * GV.SinusBasedDisplacementModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SinusBasedDisplacementModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(5.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SinusBasedDisplacementModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow(5.0);
                  //start timer
                  //GV.SinusBasedDisplacementModeParams.Count.start();
                  //GV.SinusBasedDisplacementModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
                }
                case SIN_DISPLACEMENT_MODE_STATE_GENERATE:{
                  if(GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SinusBasedDisplacementModeParams);
                  }
                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SinusBasedDisplacementModeParams.currentAmplitudeDirection =  GV.SinusBasedDisplacementModeParams.currentAmplitudeDirectionBuffered;
                  GV.SinusBasedDisplacementModeParams.DesirePoint =                GV.SinusBasedDisplacementModeParams.DesirePointBuffered;
                  GV.SinusBasedDisplacementModeParams.AngleW =                     GV.SinusBasedDisplacementModeParams.AngleWBuffered;
                  GV.SinusBasedDisplacementModeParams.InternalCounter =            GV.SinusBasedDisplacementModeParams.InternalCounterBuffered;
                  if (GV.SinusBasedDisplacementModeParams.waitForPIDReset){
                    sinDisplacementPID->reset();
                    GV.SinusBasedDisplacementModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinDisplacementPID->setCoefs(
                    GV.SinusBasedDisplacementModeParams.PIDParams.Kp, 
                    GV.SinusBasedDisplacementModeParams.PIDParams.Ki, 
                    GV.SinusBasedDisplacementModeParams.PIDParams.Kd
                  );
                  //set current position
                  GV.SinusBasedDisplacementModeParams.CurrentPoint = displacement_DIRECTING;
                  if (abs(GV.SinusBasedDisplacementModeParams.DesirePoint - GV.SinusBasedDisplacementModeParams.CurrentPoint) 
                  >= GV.SinusBasedDisplacementModeParams.MaxDeviation){
                      sinDisplacementPID->reset();
                  }
                  //set PID correction
                  GV.SinusBasedDisplacementModeParams.PIDCorrection = GV.positionAxisMode * sinDisplacementPID->getCorrection(
                    GV.SinusBasedDisplacementModeParams.DesirePoint, 
                    GV.SinusBasedDisplacementModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SinusBasedDisplacementModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    GV.SinusBasedDisplacementModeParams.DACVoltage = (GV.SinusBasedDisplacementModeParams.PIDCorrection 
                      / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                    GV.SinusBasedDisplacementModeParams.DACVoltage += GV.prevModeDACvoltage;
                    if (GV.SinusBasedDisplacementModeParams.DACVoltage > GV.SinusBasedDisplacementModeParams.MaxVoltage){
                      GV.SinusBasedDisplacementModeParams.DACVoltage = GV.SinusBasedDisplacementModeParams.MaxVoltage;
                    }
                    else if (GV.SinusBasedDisplacementModeParams.DACVoltage < -GV.SinusBasedDisplacementModeParams.MaxVoltage){
                      GV.SinusBasedDisplacementModeParams.DACVoltage = -GV.SinusBasedDisplacementModeParams.MaxVoltage;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SinusBasedDisplacementModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedDisplacementModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedDisplacementModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SinusBasedDisplacementModeParams.DACVoltage;
                    //set direction
                    direction->setWithCorrection(GV.SinusBasedDisplacementModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SinusBasedDisplacementModeParams.DACVoltage = abs(GV.SinusBasedDisplacementModeParams.DACVoltage);
                    DACVoltage = GV.SinusBasedDisplacementModeParams.DACVoltage + GV.DACConstError;
                    //debugPin.write(0);
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    //float motorStepValue = 0.0005; //mm
                    calculatedSteps = (GV.SinusBasedDisplacementModeParams.PIDCorrection / GV.motorStepValue);
                    if (calculatedSteps > (int)GV.SinusBasedDisplacementModeParams.MaxSteps){
                      calculatedSteps = (int)GV.SinusBasedDisplacementModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SinusBasedDisplacementModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SinusBasedDisplacementModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SinusBasedDisplacementModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      // if(abs(GV.SinusBasedDisplacementModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SinusBasedDisplacementModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      // if(abs(GV.SinusBasedDisplacementModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SinusBasedDisplacementModeParams.PIDCorrection == 0){
                    
                    }
                  }

                  //exit condition
                  if ((GV.SinusBasedDisplacementModeParams.NumberOfCycles > 0) || GV.stopCurrentTestProcess){
                    if(GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SinusBasedDisplacementModeParams.InternalCounter >= 
                          GV.SinusBasedDisplacementModeParams.NumberOfCycles - GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.stop = true;
                        GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if ((GV.SinusBasedDisplacementModeParams.InternalCounter >= GV.SinusBasedDisplacementModeParams.NumberOfCycles || GV.stopCurrentTestProcess)){
                        GV.SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if ((GV.SinusBasedDisplacementModeParams.InternalCounter >= GV.SinusBasedDisplacementModeParams.NumberOfCycles) || GV.stopCurrentTestProcess){
                        GV.SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }
                case SIN_DISPLACEMENT_MODE_STATE_EXIT:{
                  //GV.Mode = DAC_STATE_NONE;
                  //GV.SinusBasedDisplacementModeParams.InternalCounter = 1;
                  GV.ConstDisplacementModeParams.PositionToHold = GV.SinusBasedDisplacementModeParams.NullPointDisplacement;
                  GV.ConstDisplacementModeParams.speedEnable = false;
                  GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                  GV.SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
                  GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  //GV.SinusBasedDisplacementModeParams.Count.stop();
                  GV.Mode = DAC_STATE_DISP_CONST;
                  // GV.strokeCounter = 0;
                  break;
                }
                default:
                //GV.Mode = DAC_STATE_DISP_CONST;
                //GV.ConstDisplacementModeParams.PositionToHold = GV.SinusBasedDisplacementModeParams.NullPoint;
                //GV.ConstDisplacementModeParams.speedEnable = false;
                //GV.ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                //GV.SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
                //GV.SinusBasedDisplacementModeParams.Count.stop();
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_STRAIN_SINUS_BASED:{
          //moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{
              DACFrequency = GV.SinusBasedStrainModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SinusBasedStrainModeParams.State){
                case SIN_STRAIN_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;
                  //pre mode amplitude and null point attenuation data reset

                  PrepareForAmplitudeTune(&GV.SinusBasedStrainModeParams);
                  if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS){
                    GV.cyclicProtectMode = CYCLIC_PROTECTION_OFF;
                  }

                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinStrainPID->reset();
                  sinStrainPID->setCoefs(
                    GV.SinusBasedStrainModeParams.PIDParams.Kp, 
                    GV.SinusBasedStrainModeParams.PIDParams.Ki, 
                    GV.SinusBasedStrainModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SinusBasedStrainModeParams.AngleW = 0;
                  GV.SinusBasedStrainModeParams.AngleWBuffered = 0;
                  GV.SinusBasedStrainModeParams.CurrentPoint = GV.AverageStrain.get();
                  GV.SinusBasedStrainModeParams.DesirePoint = GV.AverageStrain.get();
                  GV.SinusBasedStrainModeParams.DesirePointBuffered = GV.SinusBasedStrainModeParams.DesirePoint;
                  GV.SinusBasedStrainModeParams.NullPointDisplacement = GV.AveragePosition.get();
                  GV.SinusBasedStrainModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SinusBasedStrainModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SinusBasedStrainModeParams.InternalCounter = 0;
                  GV.SinusBasedStrainModeParams.InternalCounterBuffered = 0;
                  GV.SinusBasedStrainModeParams.PIDCorrection = 0;
                  sinStrainCyclesTrigger->push(false);
                  PIDCorrectionToSend = GV.SinusBasedStrainModeParams.PIDCorrection;
                  GV.SinusBasedStrainModeParams.DACVoltage = 0;
                  valveVoltageToSend = GV.SinusBasedStrainModeParams.DACVoltage;
                  GV.SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SinusBasedStrainModeParams.NullPointDisplacement);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SinusBasedStrainModeParams.UpAmplitude 
                                                    + 0.01 * GV.SinusBasedStrainModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SinusBasedStrainModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(1.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SinusBasedStrainModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow(5.0);
                  //start timer
                  //GV.SinusBasedStrainModeParams.Count.start();
                  //GV.SinusBasedStrainModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
                }
                case SIN_STRAIN_MODE_STATE_GENERATE:{
                  if(GV.SinusBasedStrainModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SinusBasedStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SinusBasedStrainModeParams);
                  }
                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SinusBasedStrainModeParams.currentAmplitudeDirection =  GV.SinusBasedStrainModeParams.currentAmplitudeDirectionBuffered;
                  GV.SinusBasedStrainModeParams.DesirePoint =                GV.SinusBasedStrainModeParams.DesirePointBuffered;
                  GV.SinusBasedStrainModeParams.AngleW =                     GV.SinusBasedStrainModeParams.AngleWBuffered;
                  GV.SinusBasedStrainModeParams.InternalCounter =            GV.SinusBasedStrainModeParams.InternalCounterBuffered;
                  if (GV.SinusBasedStrainModeParams.waitForPIDReset){
                    sinStrainPID->reset();
                    GV.SinusBasedStrainModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinStrainPID->setCoefs(
                    GV.SinusBasedStrainModeParams.PIDParams.Kp, 
                    GV.SinusBasedStrainModeParams.PIDParams.Ki, 
                    GV.SinusBasedStrainModeParams.PIDParams.Kd
                  );
                  //cyclic protection main process check strain
                  double compare = strain;
                  double desirePointTmp = GV.SinusBasedStrainModeParams.DesirePointBuffered;
                  if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS && GV.isBlindeRegion == 0
                    && ((compare < GV.deltaCyclicProtection && compare > -GV.deltaCyclicProtection)
                    || desirePointTmp * compare < 0.0)){
                      // if (desirePointTmp * compare < 0.0){
                      //   GV.diagnosticsStrain = 10 * compare;
                      // }
                      // else GV.diagnosticsStrain = compare;
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
                      setNoneMode();
#else
                      setConstDisplMode();
#endif
                      this -> sendNotification(COMMAND::TM_ONCE_CYCLIC_STRAIN_LIMIT_REACH, (uint32_t)LIMIT_REACH_STATUS_STRAIN);
                  }

                  //set current position
                  GV.SinusBasedStrainModeParams.CurrentPoint = strain_DIRECTING;
                  if (abs(GV.SinusBasedStrainModeParams.DesirePoint - GV.SinusBasedStrainModeParams.CurrentPoint) 
                  >= GV.SinusBasedStrainModeParams.MaxDeviation){
                      sinStrainPID->reset();
                  }
                  //set PID correction
                  GV.SinusBasedStrainModeParams.PIDCorrection = GV.strainAxisMode * sinStrainPID->getCorrection(
                    GV.SinusBasedStrainModeParams.DesirePoint, 
                    GV.SinusBasedStrainModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SinusBasedStrainModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    //GV.SinusBasedStrainModeParams.DACVoltage = (((((GV.SinusBasedStrainModeParams.PIDCorrection) 
                    //                            * GV.SinusBasedStrainModeParams.SampleLength)
                    //                            / GV.SinusBasedStrainModeParams.YoungModulus)
                    //                            / GV.SinusBasedStrainModeParams.SampleCut) 
                    //                            / (6.773 * (DACFrequency/1000.0)))/62.5;
                    //double Imax = 0.015;//A
                    //double Qv = 0.0005;//m3/sec
                    GV.SinusBasedStrainModeParams.DACVoltage = (GV.SinusBasedStrainModeParams.PIDCorrection * 50 
                                  //* (GV.SinusBasedStrainModeParams.SampleLength/1000) 
                                  * GV.ValveParams.Imax) 
                                  / ((DACFrequency/1000.0) * GV.ValveParams.Qvalve 
                                  * GV.SinusBasedStrainModeParams.YoungModulus * 1000000);
                    GV.SinusBasedStrainModeParams.DACVoltage += GV.prevModeDACvoltage;
                    if (GV.SinusBasedStrainModeParams.DACVoltage > GV.SinusBasedStrainModeParams.MaxVoltage){
                      GV.SinusBasedStrainModeParams.DACVoltage = GV.SinusBasedStrainModeParams.MaxVoltage;
                    }
                    else if (GV.SinusBasedStrainModeParams.DACVoltage < -GV.SinusBasedStrainModeParams.MaxVoltage){
                      GV.SinusBasedStrainModeParams.DACVoltage = -GV.SinusBasedStrainModeParams.MaxVoltage;
                    } 
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SinusBasedStrainModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedStrainModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedStrainModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SinusBasedStrainModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SinusBasedStrainModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SinusBasedStrainModeParams.DACVoltage;
                    //set direction
                    direction->setWithCorrection(GV.SinusBasedStrainModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SinusBasedStrainModeParams.DACVoltage = abs(GV.SinusBasedStrainModeParams.DACVoltage);
                    DACVoltage = GV.SinusBasedStrainModeParams.DACVoltage + GV.DACConstError;
                    //debugPin.write(0);
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    float motorStepValue = 0.0005; //mm
                    calculatedSteps = (GV.SinusBasedStrainModeParams.PIDCorrection / motorStepValue);
                    if (calculatedSteps > (int)GV.SinusBasedStrainModeParams.MaxSteps){
                      calculatedSteps= (int)GV.SinusBasedStrainModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SinusBasedStrainModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SinusBasedStrainModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SinusBasedDisplacementModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SinusBasedStrainModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      // if(abs(GV.SinusBasedStrainModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SinusBasedStrainModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      // if(abs(GV.SinusBasedStrainModeParams.PIDCorrection) >= displEncoder.getStepValue()*2){
                        //motorDriver.oneStep();
                        motorDriver.setSteps(calculatedSteps);
                        //pwm->setPWM(1, -1);
                      // }
                    }
                    if(GV.SinusBasedStrainModeParams.PIDCorrection == 0){
                    
                    }
                  }

                  //exit condition
                  if ((GV.SinusBasedStrainModeParams.NumberOfCycles > 0) || GV.stopCurrentTestProcess){
                    if(GV.SinusBasedStrainModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SinusBasedStrainModeParams.InternalCounter >= 
                          GV.SinusBasedStrainModeParams.NumberOfCycles - GV.SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SinusBasedStrainModeParams.amplitudeTuneInfo.stop = true;
                        GV.SinusBasedStrainModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if ((GV.SinusBasedStrainModeParams.InternalCounter >= GV.SinusBasedStrainModeParams.NumberOfCycles || GV.stopCurrentTestProcess)){
                        GV.SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if ((GV.SinusBasedStrainModeParams.InternalCounter >= GV.SinusBasedStrainModeParams.NumberOfCycles) || GV.stopCurrentTestProcess){
                        GV.SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }
                case SIN_STRAIN_MODE_STATE_EXIT:{
                  GV.ConstStrainModeParams.StrainToHold = GV.SinusBasedStrainModeParams.NullPointStrain;
                  GV.ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
                  GV.SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
                  GV.SinusBasedStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  //GV.SinusBasedStrainModeParams.Count.stop();
                  GV.Mode = DAC_STATE_STRAIN_CONST;
                  // GV.strokeCounter = 0;
                  if (GV.SinusBasedStrainModeParams.holdConstDisplAtEnd) {
                    delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 1000ms);
                  }
                  break;
                }
                default:
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_DEFORMATION_CONST:{
          switch(GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{  
              DACFrequency = GV.ConstDeformationModeParams.ModeFrequency;
              switch (GV.ConstDeformationModeParams.State){
                case CONST_DEFORMATION_MODE_STATE_RESET:{
                  // moveEnable.write(1);
                  //EncoderBuffer.reset();
                  //GV.msPositionCounter = 0;
                  //GV.mmLastPosition = GV.roCurrentDeformation;
                  //nullPosition = position;
        //          constDeformationPID->reset();
        //          constDeformationPID->setCoefs(
        //                GV.ConstDeformationModeParams.PIDParams.Kp, 
        //                GV.ConstDeformationModeParams.PIDParams.Ki, 
        //                GV.ConstDeformationModeParams.PIDParams.Kd);
                  //clear variables
                  GV.ConstDeformationModeParams.CurrentDeformation = GV.roCurrentAvDeformation;//GV.AveragePosition.get();
        //          GV.ConstDeformationModeParams.PIDCorrection = 0;
                  GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_HOLD;
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  //speed calculation
                  if(GV.ConstDeformationModeParams.Speed != 0.0){
                    GV.ConstDeformationModeParams.msCounter = 0;
                    double section = GV.ConstDeformationModeParams.CurrentDeformation - GV.ConstDeformationModeParams.DeformationToHold;
                    if(abs(section) >= GV.ConstDeformationModeParams.delta){
                      if (section >= 0){
                        GV.ConstDeformationModeParams.k = -GV.ConstDeformationModeParams.Speed;
                      }else{
                        GV.ConstDeformationModeParams.k = GV.ConstDeformationModeParams.Speed;
                      }
                      GV.ConstDeformationModeParams.b = GV.ConstDeformationModeParams.CurrentDeformation;
                      GV.ConstDeformationModeParams.t = static_cast<uint32_t>((abs(GV.ConstDeformationModeParams.CurrentDeformation - GV.ConstDeformationModeParams.DeformationToHold)
                          /GV.ConstDeformationModeParams.Speed) * 1000);
                      GV.ConstDeformationModeParams.nextDesirePoint = GV.ConstDeformationModeParams.k 
                                                                     * GV.ConstDeformationModeParams.msCounter / 1000 
                                                                     + GV.ConstDeformationModeParams.b;
                      GV.ConstDeformationModeParams.speedEnable = true;
                    }
                    else{
                      GV.ConstDeformationModeParams.nextDesirePoint = GV.ConstDeformationModeParams.DeformationToHold;
                    }
                  }else{
                    GV.ConstDeformationModeParams.msCounter = 0;
                    GV.ConstDeformationModeParams.nextDesirePoint = GV.ConstDeformationModeParams.DeformationToHold;
                  }
                  break;
                }
                case CONST_DEFORMATION_MODE_STATE_HOLD:{
                  // moveEnable.write(1);
                  constDeformationPID->setCoefs(
                          GV.ConstDeformationModeParams.PIDParams.Kp, 
                          GV.ConstDeformationModeParams.PIDParams.Ki, 
                          GV.ConstDeformationModeParams.PIDParams.Kd);
                  GV.ConstDeformationModeParams.CurrentDeformation = deformation;
                  //double nullPos = GV.ConstDeformationModeParams.DeformationToHold;
                  double nullPos = GV.ConstDeformationModeParams.nextDesirePoint;
                  //limit mode stop by theshold crossing
                  if (!isnan(GV.displSharedLowerLimit)&&!isnan(GV.displSharedUpperLimit)
                      &&!isnan(GV.strainSharedLowerLimit)&&!isnan(GV.strainSharedUpperLimit)){
                      
                        if (isDisplacementCrossed()){
                          GV.ConstDeformationModeParams.DeformationToHold = GV.ConstDeformationModeParams.CurrentDeformation;
                          nullPos = GV.ConstDeformationModeParams.CurrentDeformation;
                          this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DISPLACEMENT);
                          setAllLimitsNAN();
                        }
                        if (isStrainCrossed()){
                          GV.ConstDeformationModeParams.DeformationToHold = GV.ConstDeformationModeParams.CurrentDeformation;
                          nullPos = GV.ConstDeformationModeParams.CurrentDeformation;
                          this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_STRAIN);
                          setAllLimitsNAN();
                        }
                        if (!isnan(GV.deformSharedLowerLimit)&&!isnan(GV.deformSharedUpperLimit)){
                        
                          if (isDeformationCrossed()){
                              this -> sendNotification(COMMAND::TM_ONCE_LIMIT_DISPL_STRAIN_DEFORM_REACH, (uint32_t)LIMIT_REACH_STATUS_DEFORMATION);
                              setAllLimitsNAN();
                          }
                        }
                  }

                  //reset PID by max deviation
                  if (abs(nullPos - GV.ConstDeformationModeParams.CurrentDeformation) 
                          >= GV.ConstDeformationModeParams.MaxDeviation){
                    constDeformationPID->reset();
                  }
                  //DEPRICATED:protection for overload: auto return piston to upper deformation
                  //if (abs(nullPos - GV.ConstDeformationModeParams.CurrentDeformation) >= 0.1){
                    //GV.ConstModeParams.Direction = -1;
                  //  direction.set(-1);
                    //GV.ConstModeParams.Voltage = 0.5;
                  //  DACVoltage = 0.3;
                  //  continue;
                  //}
                  float calculatedVoltage = 0;
                  double correction = GV.deformationAxisMode * constDeformationPID->getCorrection(
                          nullPos, GV.ConstDeformationModeParams.CurrentDeformation);
                  PIDCorrectionToSend = correction;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    calculatedVoltage = (correction / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                    if (calculatedVoltage > GV.ConstDeformationModeParams.MaxVoltage){
                      calculatedVoltage = GV.ConstDeformationModeParams.MaxVoltage;
                    }
                    if (calculatedVoltage < -GV.ConstDeformationModeParams.MaxVoltage){
                      calculatedVoltage = -GV.ConstDeformationModeParams.MaxVoltage;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(calculatedVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                  }
                      if(calculatedVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(calculatedVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            correction = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            correction = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                  }
                  GV.currentModeDACvoltage = calculatedVoltage;
                  valveVoltageToSend = calculatedVoltage;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    calculatedSteps = (correction / GV.motorStepValue);
                    if (calculatedSteps > (int)GV.ConstDeformationModeParams.MaxSteps){
                      calculatedSteps = (int)GV.ConstDeformationModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.ConstDeformationModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.ConstDeformationModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          correction = 0;
                          setConstDisplMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          correction = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(correction > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      if(abs(correction) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }
                    }
                    if(correction < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      if(abs(correction) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }else{

                      }
                    }
                    if(correction == 0){

                    }
                  }
                  //TMZeroPID.push(calculatedVoltage);
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    direction->setWithCorrection(calculatedVoltage * GV.valveDirectionMode);
                    calculatedVoltage = abs(calculatedVoltage);
                    DACext.setVoltage(calculatedVoltage);
                  }
                  break;
                }
                case CONST_DEFORMATION_MODE_STATE_EXIT:{
                  // moveEnable.write(0);
                  GV.Mode = DAC_STATE_NONE;
                  // GV.strokeCounter = 0;
                  GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                  break;
                }
                default:
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
    }
        case DAC_STATE_DEFORMATION_SIN:{
          // moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{
              DACFrequency = GV.SINDeformationModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SINDeformationModeParams.State){
                case SIN_DEFORMATION_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;

                  GV.nullPointAttenuationCounter = 0;
                  PrepareForAmplitudeTune(&GV.SINDeformationModeParams);


                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinDeformationPID->reset();
                  sinDeformationPID->setCoefs(
                    GV.SINDeformationModeParams.PIDParams.Kp, 
                    GV.SINDeformationModeParams.PIDParams.Ki, 
                    GV.SINDeformationModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SINDeformationModeParams.AngleW = 0;
                  GV.SINDeformationModeParams.AngleWBuffered = 0;
                  GV.SINDeformationModeParams.CurrentPoint = GV.AverageDeformation.get();
                  GV.SINDeformationModeParams.DesirePoint = GV.AverageDeformation.get();
                  GV.SINDeformationModeParams.DesirePointBuffered = GV.SINDeformationModeParams.DesirePoint;
                  GV.SINDeformationModeParams.NullPointDisplacement = GV.AveragePosition.get();
                  GV.SINDeformationModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SINDeformationModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SINDeformationModeParams.InternalCounter = 0;
                  GV.SINDeformationModeParams.InternalCounterBuffered = 0;
                  GV.SINDeformationModeParams.PIDCorrection = 0;
                  sinDeformCyclesTrigger->push(false);
                  PIDCorrectionToSend = GV.SINDeformationModeParams.PIDCorrection;
                  GV.SINDeformationModeParams.DACVoltage = 0;
                  valveVoltageToSend = GV.SINDeformationModeParams.DACVoltage;
                  GV.SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SINDisplacementModeParams.NullPointDeformation);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SINDisplacementModeParams.UpAmplitude 
                                                    + 0.01 * GV.SINDisplacementModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SINStrainModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(5.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SINDeformationModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow( 0.01 * GV.SINDeformationModeParams.UpAmplitude 
                                                          + 0.01 * GV.SINDeformationModeParams.DownAmplitude);
                  //start timer
                  //GV.SINDeformationModeParams.Count.start();
                  //GV.SINDeformationModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
                }
                case SIN_DEFORMATION_MODE_STATE_GENERATE:{
                  if(GV.SINDeformationModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SINDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SINDeformationModeParams);
                  }

                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SINDeformationModeParams.currentAmplitudeDirection =  GV.SINDeformationModeParams.currentAmplitudeDirectionBuffered;
                  GV.SINDeformationModeParams.DesirePoint =                GV.SINDeformationModeParams.DesirePointBuffered;
                  GV.SINDeformationModeParams.AngleW =                     GV.SINDeformationModeParams.AngleWBuffered;
                  GV.SINDeformationModeParams.InternalCounter =            GV.SINDeformationModeParams.InternalCounterBuffered;
                  if (GV.SINDeformationModeParams.waitForPIDReset){
                    sinDeformationPID->reset();
                    GV.SINDeformationModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinDeformationPID->setCoefs(
                    GV.SINDeformationModeParams.PIDParams.Kp, 
                    GV.SINDeformationModeParams.PIDParams.Ki, 
                    GV.SINDeformationModeParams.PIDParams.Kd
                  );
                  //set current position
                  GV.SINDeformationModeParams.CurrentPoint = deformation_DIRECTING;
                  if (abs(GV.SINDeformationModeParams.DesirePoint - GV.SINDeformationModeParams.CurrentPoint) 
                  >= GV.SINDeformationModeParams.MaxDeviation){
                      sinDeformationPID->reset();
                  }
                  //set PID correction
                  GV.SINDeformationModeParams.PIDCorrection = GV.deformationAxisMode * sinDeformationPID->getCorrection(
                    GV.SINDeformationModeParams.DesirePoint, 
                    GV.SINDeformationModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SINDeformationModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    GV.SINDeformationModeParams.DACVoltage = (GV.SINDeformationModeParams.PIDCorrection 
                      / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                    GV.SINDeformationModeParams.DACVoltage += GV.prevModeDACvoltage;
                    if (GV.SINDeformationModeParams.DACVoltage > GV.SINDeformationModeParams.MaxVoltage){
                      GV.SINDeformationModeParams.DACVoltage = GV.SINDeformationModeParams.MaxVoltage;
                    }
                    else if (GV.SINDeformationModeParams.DACVoltage < -GV.SINDeformationModeParams.MaxVoltage){
                      GV.SINDeformationModeParams.DACVoltage = -GV.SINDeformationModeParams.MaxVoltage;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SINDeformationModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINDeformationModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SINDeformationModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SINDeformationModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SINDeformationModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SINDeformationModeParams.DACVoltage;
                    //set direction
                    direction->setWithCorrection(GV.SINDeformationModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SINDeformationModeParams.DACVoltage = abs(GV.SINDeformationModeParams.DACVoltage);
                    DACVoltage = GV.SINDeformationModeParams.DACVoltage + GV.DACConstError;
                    //debugPin.write(0);
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    calculatedSteps = (GV.SINDeformationModeParams.PIDCorrection / GV.motorStepValue);
                    if (calculatedSteps > (int)GV.SINDeformationModeParams.MaxSteps){
                      calculatedSteps = (int)GV.SINDeformationModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SINDeformationModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SINDeformationModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SINDeformationModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SINDeformationModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SINDeformationModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      if(abs(GV.SINDeformationModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }
                    }
                    if(GV.SINDeformationModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      if(abs(GV.SINDeformationModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }else{
                        
                      }
                    }
                    if(GV.SINDeformationModeParams.PIDCorrection == 0){
                      
                    }
                  }

                  //exit condition
                  if ((GV.SINDeformationModeParams.NumberOfCycles > 0) || GV.stopCurrentTestProcess){
                    if(GV.SINDeformationModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SINDeformationModeParams.InternalCounter >= 
                          GV.SINDeformationModeParams.NumberOfCycles - GV.SINDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SINDeformationModeParams.amplitudeTuneInfo.stop = true;
                        GV.SINDeformationModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if ((GV.SINDeformationModeParams.InternalCounter >= GV.SINDeformationModeParams.NumberOfCycles || GV.stopCurrentTestProcess)){
                        GV.SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if ((GV.SINDeformationModeParams.InternalCounter >= GV.SINDeformationModeParams.NumberOfCycles) || GV.stopCurrentTestProcess){
                        GV.SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }
                case SIN_DEFORMATION_MODE_STATE_EXIT:{
                  //GV.Mode = DAC_STATE_NONE;
                  //GV.SINDeformationModeParams.InternalCounter = 1;
                  GV.ConstDeformationModeParams.DeformationToHold = GV.SINDeformationModeParams.NullPointDeformation;
                  GV.SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
                  GV.SINDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  GV.ConstDeformationModeParams.speedEnable = false;
                  GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                  //GV.SINDeformationModeParams.Count.stop();
                  GV.Mode = DAC_STATE_DEFORMATION_CONST;
                  // GV.strokeCounter = 0;
                  if (GV.SINDeformationModeParams.holdConstDisplAtEnd) {
                    delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 1000ms);
                  }
                  break;
                }
                default:
                //GV.Mode = DAC_STATE_DISP_CONST;
                //GV.ConstDeformationModeParams.PositionToHold = GV.SINDeformationModeParams.NullPoint;
                //GV.ConstDeformationModeParams.speedEnable = false;
                //GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                //GV.SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
                //GV.SINDeformationModeParams.Count.stop();
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_DEFORMATION_SINUS_BASED:{
          // moveEnable.write(0);
          switch (GV.WorkMode){
            case WORK_MODE_READY_FOR_TESTING ... WORK_MODE_TEST_IN_PROCESS :{
              DACFrequency = GV.SinusBasedDeformationModeParams.ModeFrequency;
              // Ymm = Amm * sin(W) , Wnext = W + (M_PI * Fhz * Tcycle_ms)/500
              switch (GV.SinusBasedDeformationModeParams.State){
                case SIN_DEFORMATION_MODE_STATE_RESET:{
                  GV.stopCurrentTestProcess = false;
                  GV.prevModeDACvoltage = GV.currentModeDACvoltage;

                  PrepareForAmplitudeTune(&GV.SinusBasedDeformationModeParams);

                  displMaxMinCalc.reset();
                  displMaxMinCalc.setEdgeValues(
                    200.0, 0.0,
                    200.0, 0.0
                  );
                  strainMaxMinCalc.reset();
                  strainMaxMinCalc.setEdgeValues(
                    120.0, -120.0,
                    120.0, -120.0
                  );
                  deformationMaxMinCalc.reset();
                  deformationMaxMinCalc.setEdgeValues(
                    100.0, -100.0,
                    100.0, -100.0
                  );
                  sinDeformationPID->reset();
                  sinDeformationPID->setCoefs(
                    GV.SinusBasedDeformationModeParams.PIDParams.Kp, 
                    GV.SinusBasedDeformationModeParams.PIDParams.Ki, 
                    GV.SinusBasedDeformationModeParams.PIDParams.Kd
                  );
                  //clear variables
                  GV.SinusBasedDeformationModeParams.AngleW = 0;
                  GV.SinusBasedDeformationModeParams.AngleWBuffered = 0;
                  GV.SinusBasedDeformationModeParams.CurrentPoint = GV.AverageDeformation.get();
                  GV.SinusBasedDeformationModeParams.DesirePoint = GV.AverageDeformation.get();
                  GV.SinusBasedDeformationModeParams.DesirePointBuffered = GV.SinusBasedDeformationModeParams.DesirePoint;
                  GV.SinusBasedDeformationModeParams.NullPointDeformation = GV.AveragePosition.get();
                  GV.SinusBasedDeformationModeParams.NullPointStrain = GV.AverageStrain.get();
                  GV.SinusBasedDeformationModeParams.NullPointDeformation = GV.AverageDeformation.get();
                  GV.SinusBasedDeformationModeParams.InternalCounter = 0;
                  GV.SinusBasedDeformationModeParams.InternalCounterBuffered = 0;
                  GV.SinusBasedDeformationModeParams.PIDCorrection = 0;
                  sinDeformCyclesTrigger->push(false);
                  PIDCorrectionToSend = GV.SinusBasedDeformationModeParams.PIDCorrection;
                  GV.SinusBasedDeformationModeParams.DACVoltage = 0;
                  valveVoltageToSend = GV.SinusBasedDeformationModeParams.DACVoltage;
                  GV.SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_GENERATE;
                  displMaxMinCalc.setNullPoint((float)GV.SinusBasedDisplacementModeParams.NullPointDeformation);
                  displMaxMinCalc.setNullPointWindow(0.01 * GV.SinusBasedDisplacementModeParams.UpAmplitude 
                                                    + 0.01 * GV.SinusBasedDisplacementModeParams.DownAmplitude);
                  strainMaxMinCalc.setNullPoint((float)GV.SinusBasedStrainModeParams.NullPointStrain);
                  strainMaxMinCalc.setNullPointWindow(5.0);
                  deformationMaxMinCalc.setNullPoint((float)GV.SinusBasedDeformationModeParams.NullPointDeformation);
                  deformationMaxMinCalc.setNullPointWindow(0.01 * GV.SinusBasedDeformationModeParams.UpAmplitude 
                                                    + 0.01 * GV.SinusBasedDeformationModeParams.DownAmplitude);
                  //start timer
                  //GV.SinusBasedDeformationModeParams.Count.start();
                  //GV.SinusBasedDeformationModeParams.Count.reset();
                  //dataDecimationCounter = GV.DataDecimationCoeff;
                  break;
                }
                case SIN_DEFORMATION_MODE_STATE_GENERATE:{
                  if(GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
                    GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
                    CheckUpAndDownAmplitudeSet(&GV.SinusBasedDeformationModeParams);
                  }
                  displMaxMinCalc.pushValue(displacement_MONITORING);
                  strainMaxMinCalc.pushValue(strain_MONITORING);
                  deformationMaxMinCalc.pushValue(deformation_MONITORING);
                  //update values from ticker
                  GV.SinusBasedDeformationModeParams.currentAmplitudeDirection =  GV.SinusBasedDeformationModeParams.currentAmplitudeDirectionBuffered;
                  GV.SinusBasedDeformationModeParams.DesirePoint =                GV.SinusBasedDeformationModeParams.DesirePointBuffered;
                  GV.SinusBasedDeformationModeParams.AngleW =                     GV.SinusBasedDeformationModeParams.AngleWBuffered;
                  GV.SinusBasedDeformationModeParams.InternalCounter =            GV.SinusBasedDeformationModeParams.InternalCounterBuffered;
                  if (GV.SinusBasedDeformationModeParams.waitForPIDReset){
                    sinDeformationPID->reset();
                    GV.SinusBasedDeformationModeParams.waitForPIDReset = false;
                  }
                  //update PID coefs
                  sinDeformationPID->setCoefs(
                    GV.SinusBasedDeformationModeParams.PIDParams.Kp, 
                    GV.SinusBasedDeformationModeParams.PIDParams.Ki, 
                    GV.SinusBasedDeformationModeParams.PIDParams.Kd
                  );
                  //set current position
                  GV.SinusBasedDeformationModeParams.CurrentPoint = deformation_DIRECTING;
                  if (abs(GV.SinusBasedDeformationModeParams.DesirePoint - GV.SinusBasedDeformationModeParams.CurrentPoint) 
                  >= GV.SinusBasedDeformationModeParams.MaxDeviation){
                      sinDeformationPID->reset();
                  }
                  //set PID correction
                  GV.SinusBasedDeformationModeParams.PIDCorrection = GV.deformationAxisMode * sinDeformationPID->getCorrection(
                    GV.SinusBasedDeformationModeParams.DesirePoint, 
                    GV.SinusBasedDeformationModeParams.CurrentPoint
                  );
                  PIDCorrectionToSend = GV.SinusBasedDeformationModeParams.PIDCorrection;
                  if(GV.machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
                    //calculate DAC Voltage
                    GV.SinusBasedDeformationModeParams.DACVoltage = (GV.SinusBasedDeformationModeParams.PIDCorrection 
                      / (6.773 * (DACFrequency/1000.0)))/62.5;//* 10.0 / 10.0; //*10-toVolts, /10-downgradeCoef //maebe need division 10 coef
                    GV.SinusBasedDeformationModeParams.DACVoltage += GV.prevModeDACvoltage;
                    if (GV.SinusBasedDeformationModeParams.DACVoltage > GV.SinusBasedDeformationModeParams.MaxVoltage){
                      GV.SinusBasedDeformationModeParams.DACVoltage = GV.SinusBasedDeformationModeParams.MaxVoltage;
                    }
                    else if (GV.SinusBasedDeformationModeParams.DACVoltage < -GV.SinusBasedDeformationModeParams.MaxVoltage){
                      GV.SinusBasedDeformationModeParams.DACVoltage = -GV.SinusBasedDeformationModeParams.MaxVoltage;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                      if(GV.SinusBasedDeformationModeParams.DACVoltage > 0){
                        LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedDeformationModeParams.DACVoltage < 0){
                        LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                      }
                      if(GV.SinusBasedDeformationModeParams.DACVoltage == 0){
                        LimSwDirecton = 0;
                      }
                      switch (GV.LimitSwitchState)
                      {
                        case LIMIT_SWITCH_STATE_ONE:
                            GV.SinusBasedDeformationModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        case LIMIT_SWITCH_STATE_TWO:
                            GV.SinusBasedDeformationModeParams.PIDCorrection = 0;
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                              setNoneMode();
                            }
                            if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
                              setConstDisplMode();
                            }
                          break;
                        default:
                          break;
                      }
                    #endif
                    GV.currentModeDACvoltage = GV.SinusBasedDeformationModeParams.DACVoltage;  
                    //set direction
                    direction->setWithCorrection(GV.SinusBasedDeformationModeParams.DACVoltage * GV.valveDirectionMode);
                    //abs DAC Voltage
                    GV.SinusBasedDeformationModeParams.DACVoltage = abs(GV.SinusBasedDeformationModeParams.DACVoltage);
                    DACVoltage = GV.SinusBasedDeformationModeParams.DACVoltage + GV.DACConstError;
                    //debugPin.write(0);
                    DACext.setVoltage(DACVoltage);
                  }
                  if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
                    int calculatedSteps = 0;
                    calculatedSteps = (GV.SinusBasedDeformationModeParams.PIDCorrection / GV.motorStepValue);
                    if (calculatedSteps > (int)GV.SinusBasedDeformationModeParams.MaxSteps){
                      calculatedSteps = (int)GV.SinusBasedDeformationModeParams.MaxSteps;
                    }
                    if (calculatedSteps < (-1) * (int)GV.SinusBasedDeformationModeParams.MaxSteps){
                      calculatedSteps = (-1) * (int)GV.SinusBasedDeformationModeParams.MaxSteps;
                    }
                    #if ((LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_ONE) || (LIMIT_SWITCH_TYPE == LIMIT_SWITCH_TYPE_TWO))
                    if(calculatedSteps > 0){
                      LimSwDirecton = 1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps < 0){
                      LimSwDirecton = -1 * GV.pistonMode * GV.valveDirectionMode;
                    }
                    if(calculatedSteps == 0){
                      LimSwDirecton = 0;
                    }
                    switch (GV.LimitSwitchState)
                    {
                      case LIMIT_SWITCH_STATE_ONE:
                          GV.SinusBasedDeformationModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      case LIMIT_SWITCH_STATE_TWO:
                          GV.SinusBasedDeformationModeParams.PIDCorrection = 0;
                          setNoneMode();
                        break;
                      default:
                        break;
                    }
                    #endif
                    calculatedSteps = abs(calculatedSteps);
                    if(GV.SinusBasedDeformationModeParams.PIDCorrection > 0){
                      motorDriver.setDirection( direction->calculateBoolDirection(GV.valveDirectionMode));
                      if(abs(GV.SinusBasedDeformationModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }
                    }
                    if(GV.SinusBasedDeformationModeParams.PIDCorrection < 0){
                      motorDriver.setDirection( direction->calculateBoolDirection((-1) * GV.valveDirectionMode));
                      if(abs(GV.SinusBasedDeformationModeParams.PIDCorrection) >= displEncoder.getStepValue()){
                        motorDriver.setSteps(calculatedSteps);
                      }else{
                        
                      }
                    }
                    if(GV.SinusBasedDeformationModeParams.PIDCorrection == 0){
                      
                    }
                  }

                  //exit condition
                  if ((GV.SinusBasedDeformationModeParams.NumberOfCycles > 0) || GV.stopCurrentTestProcess){
                    if(GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.stopProcess && !GV.stopCurrentTestProcess){
                      if ((GV.SinusBasedDeformationModeParams.InternalCounter >= 
                          GV.SinusBasedDeformationModeParams.NumberOfCycles - GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles) 
                          ){
                        GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.stop = true;
                        GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.stopProcess = false;
                      }
                      if ((GV.SinusBasedDeformationModeParams.InternalCounter >= GV.SinusBasedDeformationModeParams.NumberOfCycles || GV.stopCurrentTestProcess)){
                        GV.SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }else{
                      if ((GV.SinusBasedDeformationModeParams.InternalCounter >= GV.SinusBasedDeformationModeParams.NumberOfCycles) || GV.stopCurrentTestProcess){
                        GV.SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_EXIT;
                        GV.stopCurrentTestProcess = false;
                        //send notification complete
                        sendNotification(COMMAND::TM_ONCE_TEST_EXECUTION_COMPLETE, (uint32_t)0x0);
                      }
                    }
                  }
                  break;
                }
                case SIN_DEFORMATION_MODE_STATE_EXIT:{
                  //GV.Mode = DAC_STATE_NONE;
                  //GV.SinusBasedDeformationModeParams.InternalCounter = 1;
                  GV.ConstDeformationModeParams.DeformationToHold = GV.SinusBasedDeformationModeParams.NullPointDeformation;
                  GV.ConstDeformationModeParams.speedEnable = false;
                  GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                  GV.SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
                  GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_DISABLE;
                  //GV.SinusBasedDeformationModeParams.Count.stop();
                  GV.Mode = DAC_STATE_DEFORMATION_CONST;
                  // GV.strokeCounter = 0;
                  if (GV.SinusBasedDeformationModeParams.holdConstDisplAtEnd) {
                    delayedAction.attach(callback(this, &ExecutionThread::setConstDisplMode), 1000ms);
                  }
                  break;
                }
                default:
                //GV.Mode = DAC_STATE_DISP_CONST;
                //GV.ConstDeformationModeParams.PositionToHold = GV.SinusBasedDeformationModeParams.NullPoint;
                //GV.ConstDeformationModeParams.speedEnable = false;
                //GV.ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                //GV.SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
                //GV.SinusBasedDeformationModeParams.Count.stop();
                  break;
              }
              break;
            }
            default:
              GV.Mode = prevDACState;
              DACState = prevDACState;
              break;
          }
          break;
        }
        case DAC_STATE_DEFORMATION_USER_DEFINED:{
          // moveEnable.write(0);
          break;
        }
        case DAC_STATE_CLOSE_VALVE:{
          DACFrequency = GV.ConstDisplacementModeParams.ModeFrequency;
          if(GV.machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
            switch (GV.closeValveState)
            {
            case CLOSE_VALVE_STATE_RESET:{
              positionCounter = ((int32_t)GV.middlePosition - *BV.valvePosition); // * GV.valveDirectionMode;
              if(positionCounter > 0){
                dir = direction->calculateBoolDirection(GV.valveDirectionMode);
              }
              if(positionCounter < 0){
                dir = direction->calculateBoolDirection((-1) * GV.valveDirectionMode);
              }
              positionCounter = abs(positionCounter);
              GV.closeValveState = CLOSE_VALVE_STATE_HOLD;
              percentage = 0;
              break;
            }
            case CLOSE_VALVE_STATE_HOLD:{
              if(positionCounter > 0){
                if((uint32_t)positionCounter < stepsCountPerCycle){
                  if(dir)
                    *BV.valvePosition += (GV.valveInvertAxis) * positionCounter;
                  else
                    *BV.valvePosition += ((-1) * GV.valveInvertAxis) * positionCounter;
                  motorDriver.setSteps(dir, positionCounter);
                  positionCounter = 0;
                }else{
                  positionCounter -= stepsCountPerCycle;
                  if(dir)
                    *BV.valvePosition += (GV.valveInvertAxis) * stepsCountPerCycle;
                  else
                    *BV.valvePosition += ((-1) * GV.valveInvertAxis) * stepsCountPerCycle;
                  motorDriver.setSteps(dir, stepsCountPerCycle);
                }
              }
              else{
                GV.closeValveState = CLOSE_VALVE_STATE_EXIT;
              }
              break;
            }
            case CLOSE_VALVE_STATE_EXIT:{
              GV.Mode = DAC_STATE_NONE;
              GV.closeValveState = CLOSE_VALVE_STATE_RESET;
              break;
            }
            default:
              break;
            }
          }else{
            GV.Mode = prevDACState;
          }
          break;
        }
        default:
          break;
  }
}
ExecutionThread::~ExecutionThread(){
  delete sinDispCyclesTrigger;
  delete sinStrainCyclesTrigger;
  delete sinDeformCyclesTrigger;
  delete zeroCrossed;
  delete piDivTwoCrossed;
  delete piCrossed;
  delete treePiDivTwoCrossed;
  #if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
      delete encoderPermissionButton;
  #endif
  delete positiveStrainZeroCrossed;
  delete negativeStrainZeroCrossed;
  delete constDisplacementPID;
  delete sinDisplacementPID;
  delete constStrainPID;
  delete sinStrainPID;
  delete constDeformationPID;
  delete sinDeformationPID;
  delete direction;
  //delete pulseMode;
  //delete staticTest;
  delete LimSw;
  delete SBD_MS;
  delete SBD_DF;
  delete dataFiltersSet;
  delete switcherFilterSet;
}
void ExecutionThread::calculateNextPoint(){
    GV.strokeCounter++;
    dataDecimationCounter++;
    if (dataDecimationCounter >= GV.DataDecimationCoeff){
      for(auto channel = dataChannels.begin(); channel != dataChannels.end(); channel++){

        switch ((*channel)->getChannelType()){
          case CHANNEL_TYPE_POSITION:{
            FloatDataChannel<VALUES_BUFFERS_SIZE> *ch = (FloatDataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(this->positionToSend);
            //ch->channel->push(this->positionToSend);
            //ch->channel->push(GV.isBlindeRegion);
            //ch->channel->push(GV.SinusBasedDisplacementModeParams.DesirePointBuffered);
            //ch->channel->push(GV.SINDisplacementModeParams.DesirePointBuffered);
            break;
          }
          case CHANNEL_TYPE_STRAIN:{
            FloatDataChannel<VALUES_BUFFERS_SIZE> *ch = (FloatDataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(this->strainToSend);
            //ch->channel->push((float)GV.tmpDataForTesting);
            //ch->channel->push(displMaxMinCalc.getMaxCount());
            //ch->channel->push(GV.SinusBasedDeformationModeParams.DesirePointBuffered);
            //ch->channel->push(GV.SinusBasedStrainModeParams.DesirePointBuffered);
            //ch->channel->push(GV.SINStrainModeParams.DesirePointBuffered);
            //ch->channel->push(GV.nullPointDelta);
            //ch->channel->push((float)GV.nullPointAttenuationCounter);
            //ch->channel->push(GV.SINDisplacementModeParams.amplitudeTuneInfo.freq);
            break;
          }
          case CHANNEL_TYPE_DEFORMATION:{
            FloatDataChannel<VALUES_BUFFERS_SIZE> *ch = (FloatDataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(this->deformationToSend);
            //ch->channel->push(GV.cyclicProtectMode);
            //ch->channel->push(GV.SINDeformationModeParams.DesirePointBuffered);
            //ch->channel->push(GV.SinusBasedDeformationModeParams.DesirePointBuffered);
            //ch->channel->push(GV.SINDisplacementModeParams.DownAmplitude);
            //ch->channel->push(displMaxMinCalc.getMinCount());
            //ch->channel->push(GV.SINDisplacementModeParams.UpAmplitudeSet);
            //ch->channel->push((float)GV.tmpDataForTesting);
            //ch->channel->push(GV.actualCyclicStrainProtectCounts);
            break;
          }
          //in us
          case CHANNEL_TYPE_TIME:{
            Uint64DataChannel<VALUES_BUFFERS_SIZE> *ch = (Uint64DataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(GV.strokeCounter * GV.TcycleTime /* * GV.DataDecimationCoeff*/);//check
            break;
          }
          case CHANNEL_TYPE_CYCLE:{
            Uint64DataChannel<VALUES_BUFFERS_SIZE> *ch = (Uint64DataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(this->getCurrentCycle());
            break;
          }
          case CHANNEL_TYPE_DIAGNOSTICS:{
            FloatDataChannel<DIAGNOSTICS_BUFFERS_SIZE> *ch = (FloatDataChannel<DIAGNOSTICS_BUFFERS_SIZE>*)(*channel);
            switch (GV.TestDataUnits){
              case CORRECTION_UNITS_RAW:
                  ch->channel->push(this->PIDCorrectionToSend);
                break;
              case VALVE_VOLTAGE_UNITS_V:
                  ch->channel->push(this->valveVoltageToSend);
                break;
              case MOTOR_STEPS_UNITS_RAW:
                  ch->channel->push(this->motorStepToSend);
                break;
              case SINUS_TEST_SIGNAL:
                sinTestSignalArgument += sinTestSignalArgumentsIncrease;
                if (sinTestSignalArgument>twoPi){
                  sinTestSignalArgument = 0.0;
                }
                ch->channel->push(sin(sinTestSignalArgument));
                break;
              default:
                ch->channel->push(0.0);
                break;
            }
            break;
          }
          case CHANNEL_TYPE_VALVE:{
            Int32DataChannel<VALVE_BUFFERS_SIZE> *ch = (Int32DataChannel<VALVE_BUFFERS_SIZE>*)(*channel);
            float percent = 0;
            int32_t sign = 1;
            switch (GV.valveUnits){
              case VALVE_UNITS_PERCENT:{
                if(((*BV.valvePosition) > static_cast<int32_t>(GV.middlePosition + GV.middleUpThreshold)) && ((*BV.valvePosition) > 0)){
                  percent = ((*BV.valvePosition) - (GV.middlePosition + GV.middleUpThreshold));
                  percent = percent / (GV.maxPosition - (GV.middlePosition + GV.middleUpThreshold)) * 100;
                  sign = 1;
                }else{
                  if((*BV.valvePosition) < static_cast<int32_t>(GV.middlePosition - GV.middleDownThreshold)){
                    percent = ((GV.middlePosition - GV.middleDownThreshold) - (*BV.valvePosition));
                    percent = percent / (GV.middlePosition - GV.middleDownThreshold) * 100;
                    sign = -1;
                  }else{
                    percent = 0;
                  }
                }
                ch->channel->push(sign * static_cast<int32_t>(percent));
                break;
              }
              case VALVE_UNITS_RAW:{
                ch->channel->push(*BV.valvePosition);
                break;
              }
              default:
                ch->channel->push(0);
                break;
            }
            break;
          }
          case CHANNEL_TYPE_STEP_ID:{
            Uint32DataChannel<VALUES_BUFFERS_SIZE> *ch = (Uint32DataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(GV.stepID);
            break;
          }
          case CHANNEL_TYPE_CURRENT_MODE:{
            Uint32DataChannel<VALUES_BUFFERS_SIZE> *ch = (Uint32DataChannel<VALUES_BUFFERS_SIZE>*)(*channel);
            ch->channel->push(GV.Mode);
		        break;
		      }
          default:
            break;
        }
      }
      for(auto channel = reCoDataChannels.begin(); channel != reCoDataChannels.end(); channel++) {
        switch ((*channel)->getChannelType()) {
          case CHANNEL_TYPE_POSITION:{
            FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> *ch = (FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>*)(*channel);
            ch->channel->push(this->positionToSend);
            break;
          }
          case CHANNEL_TYPE_STRAIN:{
            FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> *ch = (FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>*)(*channel);
            ch->channel->push(this->strainToSend);
            break;
            }
          case CHANNEL_TYPE_DEFORMATION:{
            FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> *ch = (FloatDataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>*)(*channel);
            ch->channel->push(this->deformationToSend);
            break;
          }
          //in us
          case CHANNEL_TYPE_TIME:{
            Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> *ch = (Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>*)(*channel);
            ch->channel->push(GV.strokeCounter * GV.TcycleTime /* * GV.DataDecimationCoeff*/);//check
            break;
          }
          case CHANNEL_TYPE_CYCLE:{
            Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE> *ch = (Uint64DataChannel<REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE>*)(*channel);
            ch->channel->push(this->getCurrentCycle());
            break;
          }
          case CHANNEL_TYPE_DIAGNOSTICS:{
              FloatDataChannel<1> *ch = (FloatDataChannel<1>*)(*channel);
              switch (GV.TestDataUnits){
                case CORRECTION_UNITS_RAW:
                  ch->channel->push(this->PIDCorrectionToSend);
            	    break;
                case VALVE_VOLTAGE_UNITS_V:
                  ch->channel->push(this->valveVoltageToSend);
                  break;
                case MOTOR_STEPS_UNITS_RAW:
                  ch->channel->push(this->motorStepToSend);
                  break;
                case SINUS_TEST_SIGNAL:
                  sinTestSignalArgument += sinTestSignalArgumentsIncrease;
                  if (sinTestSignalArgument>twoPi){
                    sinTestSignalArgument = 0.0;
          	      }
                  ch->channel->push(sin(sinTestSignalArgument));
                  break;
                default:
                  break;
              }
              break;
          }
          default:
            break;
        }
      }
      dataDecimationCounter = 0;
    }
    switch (DACState){
      case DAC_STATE_DISP_SIN:{
        if (GV.SINDisplacementModeParams.State == SIN_DISPLACEMENT_MODE_STATE_GENERATE){
          SinusModesGenetateTargetPoints(&GV.SINDisplacementModeParams, &displMaxMinCalc, GV.SINDisplacementModeParams.NullPointDisplacement);
          //reset PID memory
          //sinDisplacementPID->reset();
          GV.SINDisplacementModeParams.waitForPIDReset = true;
          //clear timer
          //GV.SINDisplacementModeParams.Count.reset();
        }
        break;
      }
      case DAC_STATE_STRAIN_SIN:{
        if (GV.SINStrainModeParams.State == SIN_STRAIN_MODE_STATE_GENERATE){
          SinusModesGenetateTargetPoints(&GV.SINStrainModeParams, &strainMaxMinCalc, GV.SINStrainModeParams.NullPointStrain);
          //cyclis zero crossed work by strain protection
          if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS || GV.cyclicProtectMode == CYCLIC_PROTECTION_INIT){
            if (GV.cyclicProtectMode == CYCLIC_PROTECTION_INIT){
              GV.isFirstMoove = true;
            }
            double deltaTmpForProtection = (GV.prevAmplitudeDownSet + GV.prevAmplitudeUpSet)*(GV.isSimpleCyclicProtection ? GV.deltaCyclicProtectionDefault
                                        : GV.deltaCyclicProtection);
            bool tmpBool = false;
            if (GV.SINStrainModeParams.DesirePointBuffered > 0.0){
              negativeStrainZeroCrossed->push(false);
              positiveStrainZeroCrossed->push(true);
              double compareData = (GV.isSimpleCyclicProtection ? GV.multiplierDefault : GV.multiplier) * deltaTmpForProtection;
              if (GV.SINStrainModeParams.DesirePointBuffered < compareData){
                tmpBool = true;
              }
            }
            else if (GV.SINStrainModeParams.DesirePointBuffered < 0.0){
              negativeStrainZeroCrossed->push(true);
              positiveStrainZeroCrossed->push(false);
              double compareData = -((GV.isSimpleCyclicProtection ? GV.multiplierDefault : GV.multiplier) * deltaTmpForProtection);
              if (GV.SINStrainModeParams.DesirePointBuffered > compareData){
                tmpBool = true;
              }
            }
            if (negativeStrainZeroCrossed->getState() || positiveStrainZeroCrossed->getState() || GV.isFirstMoove){
              GV.actualCyclicStrainProtectCounts = abs((1.0/(GV.SINStrainModeParams.SINFrequency)) * (1000000/GV.TcycleTime) *
                      (GV.isFirstMoove ? (GV.isSimpleCyclicProtection ? GV.defaultBlindePartOfCyclicStrainProtectionFirst : GV.blindePartOfCyclicStrainProtectionFirst)
                           : (GV.isSimpleCyclicProtection ? GV.defaultBlindePartOfCyclicStrainProtection : GV.blindePartOfCyclicStrainProtection)));
            GV.isFirstMoove = false;
            GV.isBlindeRegion = 1;
          }
          if (GV.actualCyclicStrainProtectCounts > 0){
            GV.actualCyclicStrainProtectCounts --;
            GV.isBlindeRegion = 1;
            }else{ 
              if (tmpBool){ 
                GV.isBlindeRegion = 1;
              }else{
                GV.isBlindeRegion = 0;
          }
            }
        GV.cyclicProtectMode = CYCLIC_PROTECTION_IN_PROCESS;
      }
      //reset PID memory
      //sinStrainPID->reset();
      GV.SINStrainModeParams.waitForPIDReset = true;
      //clear timer
      //GV.SINStrainModeParams.Count.reset();
    }
    break;
  }
    case DAC_STATE_DISP_SINUS_BASED:{
    if (GV.SinusBasedDisplacementModeParams.State == SIN_DISPLACEMENT_MODE_STATE_GENERATE){
      SinusBasedModesGenetateTargetPoints(&GV.SinusBasedDisplacementModeParams, &displMaxMinCalc, GV.SinusBasedDisplacementModeParams.NullPointDisplacement, 
        GV.SinusBasedDisplacementModeParams.ModeType, GV.SinusBasedDisplacementModeParams.baseRatio);
      //reset PID memory
      //sinDisplacementPID->reset();
      GV.SinusBasedDisplacementModeParams.waitForPIDReset = true;
      //clear timer
      //GV.SinusBasedDisplacementModeParams.Count.reset();
    }
    break;
  }
    case DAC_STATE_STRAIN_SINUS_BASED:{
    if (GV.SinusBasedStrainModeParams.State == SIN_STRAIN_MODE_STATE_GENERATE){
      SinusBasedModesGenetateTargetPoints(&GV.SinusBasedStrainModeParams, &strainMaxMinCalc, GV.SinusBasedStrainModeParams.NullPointStrain, 
        GV.SinusBasedStrainModeParams.ModeType, GV.SinusBasedStrainModeParams.baseRatio);
      //cyclis zero crossed work by strain protection
      if (GV.cyclicProtectMode == CYCLIC_PROTECTION_IN_PROCESS || GV.cyclicProtectMode == CYCLIC_PROTECTION_INIT){
        if (GV.cyclicProtectMode == CYCLIC_PROTECTION_INIT){
          GV.isFirstMoove = true;
        }
          double deltaTmpForProtection = (GV.prevAmplitudeDownSet + GV.prevAmplitudeUpSet)*(GV.isSimpleCyclicProtection ? GV.deltaCyclicProtectionDefault
          : GV.deltaCyclicProtection);
          bool tmpBool = false;
          if (GV.SinusBasedStrainModeParams.DesirePointBuffered >= 0.0){
            negativeStrainZeroCrossed->push(false);
            positiveStrainZeroCrossed->push(true);
            double compareData = (GV.isSimpleCyclicProtection ? GV.multiplierDefault : GV.multiplier) * deltaTmpForProtection;
            if (GV.SinusBasedStrainModeParams.DesirePointBuffered < compareData){
              tmpBool = true;
            }
            }else{ 
              if (GV.SinusBasedStrainModeParams.DesirePointBuffered < 0.0){
            negativeStrainZeroCrossed->push(true);
            positiveStrainZeroCrossed->push(false);
            double compareData = -((GV.isSimpleCyclicProtection ? GV.multiplierDefault : GV.multiplier) * deltaTmpForProtection);
            if (GV.SinusBasedStrainModeParams.DesirePointBuffered > compareData){
              tmpBool = true;
            }
          }
            }
          if (negativeStrainZeroCrossed->getState() || positiveStrainZeroCrossed->getState() || GV.isFirstMoove){
            GV.actualCyclicStrainProtectCounts = abs((1.0/(GV.SinusBasedStrainModeParams.SINFrequency)) * (1000000/GV.TcycleTime) *
            (GV.isFirstMoove ? (GV.isSimpleCyclicProtection ? GV.defaultBlindePartOfCyclicStrainProtectionFirst : GV.blindePartOfCyclicStrainProtectionFirst)
                             : (GV.isSimpleCyclicProtection ? GV.defaultBlindePartOfCyclicStrainProtection : GV.blindePartOfCyclicStrainProtection)));
            GV.isFirstMoove = false;
            GV.isBlindeRegion = 1;
          }
          if (GV.actualCyclicStrainProtectCounts > 0){
            GV.actualCyclicStrainProtectCounts --;
            GV.isBlindeRegion = 1;
            }else{ 
              if (tmpBool){
                GV.isBlindeRegion = 1;
              }else{
                GV.isBlindeRegion = 0;
          }
            }
        GV.cyclicProtectMode = CYCLIC_PROTECTION_IN_PROCESS;
      }
      //reset PID memory
      //sinDisplacementPID->reset();
      GV.SinusBasedStrainModeParams.waitForPIDReset = true;
      //clear timer
      //GV.SinusBasedStrainModeParams.Count.reset();
    }
    break;
  }
    case DAC_STATE_STRAIN_CONST:{
    if(GV.ConstStrainModeParams.State == CONST_DISPLACEMENT_MODE_STATE_HOLD){
      ConstModeNextDesirePointCalculating(&GV.ConstStrainModeParams, GV.ConstStrainModeParams.StrainToHold);
    }
    break;
  }
    case DAC_STATE_DISP_CONST:{
    if(GV.ConstDisplacementModeParams.State == CONST_DISPLACEMENT_MODE_STATE_HOLD){//for encoder
      GV.msPositionCounter++;
      if(GV.msPositionCounter >= 20){
       GV.msPositionCounter = 0;
       GV.mmLastPosition = GV.roCurrentPosition;
      }
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
    if(EncoderBuffer.empty()){
        encoderPermissionButton->push(false);
#endif
        ConstModeNextDesirePointCalculating(&GV.ConstDisplacementModeParams, GV.ConstDisplacementModeParams.PositionToHold);
        
#if (REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER)
    }
    else{
       encoderPermissionButton->push(true);
       if (encoderPermissionButton->getState()){
        this->setConstDisplMode();
       }
       // encoder movement;
       GV.ConstDisplacementModeParams.speedEnable = false;
       GV.ConstDisplacementModeParams.msCounter = 0; //??
       bool encoderDirection;
       if (EncoderBuffer.pop(encoderDirection)){
         double nextPosition;
         if (encoderDirection){
           nextPosition = GV.ConstDisplacementModeParams.PositionToHold + (0.010 * (double)GV.positionInvertAxis);
           led2.write(1);
           delayedAction.attach_us(callback(this, &ExecutionThread::disableLED2), 800);
         }else{
           nextPosition = GV.ConstDisplacementModeParams.PositionToHold - (0.010 * (double)GV.positionInvertAxis);
           led3.write(1);
           delayedAction.attach_us(callback(this, &ExecutionThread::disableLED3), 800);
         }
         if (nextPosition > (GV.mmLastPosition + 5) || nextPosition < (GV.mmLastPosition - 5)){
           nextPosition = GV.ConstDisplacementModeParams.PositionToHold;
         }
         GV.ConstDisplacementModeParams.PositionToHold = nextPosition;
         GV.ConstDisplacementModeParams.nextDesirePoint = nextPosition; //??
       }
      }
#endif
    }
    else{
      //reset position checker
      GV.msPositionCounter = 0;
      GV.mmLastPosition = GV.roCurrentPosition;
    }
    break;
  }
    case DAC_STATE_DISP_USER_DEFINED:{
    //if
    break;
  }
    case DAC_STATE_DEFORMATION_CONST:{
      if(GV.ConstDeformationModeParams.State == CONST_DEFORMATION_MODE_STATE_HOLD){
        ConstModeNextDesirePointCalculating(&GV.ConstDeformationModeParams, GV.ConstDeformationModeParams.DeformationToHold);
      }
    break;  
  }
    case DAC_STATE_DEFORMATION_SIN:{
      if (GV.SINDeformationModeParams.State == SIN_DEFORMATION_MODE_STATE_GENERATE){
        SinusModesGenetateTargetPoints(&GV.SINDeformationModeParams, &deformationMaxMinCalc, GV.SINDeformationModeParams.NullPointDeformation);
      //reset PID memory
      //sinDeformationPID->reset();
      GV.SINDeformationModeParams.waitForPIDReset = true;
      //clear timer
      //GV.SINDeformationModeParams.Count.reset();
    }
    break;
  }
    case DAC_STATE_DEFORMATION_SINUS_BASED:{
    if (GV.SinusBasedDeformationModeParams.State == SIN_DEFORMATION_MODE_STATE_GENERATE){
      SinusBasedModesGenetateTargetPoints(&GV.SinusBasedDeformationModeParams, &deformationMaxMinCalc, GV.SinusBasedDeformationModeParams.NullPointDeformation, 
        GV.SinusBasedDeformationModeParams.ModeType, GV.SinusBasedDeformationModeParams.baseRatio);
      //reset PID memory
      //sinDeformationPID->reset();
      GV.SinusBasedDeformationModeParams.waitForPIDReset = true;
      //clear timer
      //GV.SinusBasedDeformationModeParams.Count.reset();
    }
    break;
  }
    case DAC_STATE_DEFORMATION_USER_DEFINED:{
      //if
      break;
    }
    default:
      break;
    }
}

 int ExecutionThread::setTCycle(us_timestamp_t tcycle){
      GV.Tcycle.detach();
      GV.Tcycle.attach(callback(this, &ExecutionThread::calculateNextPoint), 
                                    std::chrono::microseconds(tcycle));
      GV.TcycleTime = tcycle;
    return NO_ERROR;
 }

errorCode_t ExecutionThread::addFilterAtEnd(uint32_t filterType, uint32_t dataType, int rangeOfFilter){
    return dataFiltersSet->addFilterInCollectionAtEnd(dataType, filterType, rangeOfFilter);
}

errorCode_t ExecutionThread::addFilterByIndex(uint32_t filterType, uint32_t dataType, int rangeOfFilter, int index){
    return dataFiltersSet->addFilterInCollectionAtIndex(dataType, filterType, rangeOfFilter, index);
}

errorCode_t ExecutionThread::clearingOfFilterByParameters(uint32_t filterType, uint32_t dataType, uint32_t parametr, int index){
  errorCode_t error = DEFAULT_VALUE;
    switch(parametr){
      case TypeOfClearing::FULL_CLEARING:
        error = dataFiltersSet->clearAllCollection();
        break;
      case TypeOfClearing::LINE_CLEARING:
        error = dataFiltersSet->clearLineCollection(dataType);
        break;
      case TypeOfClearing::INDIVIDUAL_CLEARING:
        error = dataFiltersSet->clearOneFilter(dataType, index);
        break;
      case TypeOfClearing::BY_DATA_AND_FILTERTYPE_CLEARING:
        error = dataFiltersSet->clearFiltersByDataTypeAndFilterType(dataType, filterType);
        break;
      case TypeOfClearing::ALL_DATA_CLEARING_BY_FILTERTYPE:
        error = dataFiltersSet->clearAllLinesByFilterType(filterType);
        break;
      default:
        error = ERROR_WRONG_INPUT_DATA;
        break;
    }
  return error;  
}

errorCode_t ExecutionThread::orderingByParameter(uint32_t dataType){
    return dataFiltersSet->orderingFiltersByParameter(dataType);
}

errorCode_t ExecutionThread::writeAddNullPointSinDispl(double dataType){
    GV.addNullPoint = dataType;
    return NO_ERROR;
}

errorCode_t ExecutionThread::setFilteringActivityCell(uint32_t dataType, uint32_t activ, uint32_t step){
    return switcherFilterSet->SetFilteringActivityUnit(dataType, activ, step);
}
errorCode_t ExecutionThread::setFilteringActivityStepsDataRaw(uint32_t dataType, uint32_t step){
    return switcherFilterSet->SetFilteringActivityStepsDataLine(dataType, step);
}
errorCode_t ExecutionThread::setFilteringActivityAllCells(uint32_t step){
    return switcherFilterSet->SetFilteringActivityAllSteps(step);
}

void ExecutionThread::getFilterSetStatusByDataType(uint32_t dataType){

}
void ExecutionThread::getActivityesSetStatusByDataType(uint32_t dataType){

}

float ExecutionThread::getPosition(uint32_t activity){
    return this->switcherFilterSet->GetDataByActivity(position, activity);
}
float ExecutionThread::getStrain(uint32_t activity){
    return this->switcherFilterSet->GetDataByActivity(strain, activity);
}
float ExecutionThread::getDeformation(uint32_t activity){
    return this->switcherFilterSet->GetDataByActivity(deformation, activity);
}

void ExecutionThread::setAllLimitsNAN(){
  GV.displSharedLowerLimit = NAN;
  GV.displSharedUpperLimit = NAN;
  GV.strainSharedLowerLimit = NAN;
  GV.strainSharedUpperLimit = NAN;
  GV.deformSharedLowerLimit = NAN;
  GV.deformSharedUpperLimit = NAN;
}

bool ExecutionThread::isDisplacementCrossed(){
    return ((GV.isBeginDisplacementHiger && (displacement_MONITORING <= GV.displSharedUpperLimit || displacement_MONITORING <= GV.displSharedLowerLimit))
            ||(!GV.isBeginDisplacementHiger && (displacement_MONITORING >= GV.displSharedLowerLimit || displacement_MONITORING >= GV.displSharedUpperLimit)));
}
bool ExecutionThread::isStrainCrossed(){
    return ((GV.isBeginStrainHiger && (strain_MONITORING <= GV.strainSharedUpperLimit || strain_MONITORING <= GV.strainSharedLowerLimit))
            ||(!GV.isBeginStrainHiger && (strain_MONITORING >= GV.strainSharedLowerLimit || strain_MONITORING >= GV.strainSharedUpperLimit)));
}
bool ExecutionThread::isDeformationCrossed(){
    return ((GV.isBeginDeformationHiger && (deformation_MONITORING <= GV.deformSharedUpperLimit || deformation_MONITORING <= GV.deformSharedLowerLimit))
            ||(!GV.isBeginDeformationHiger && (deformation_MONITORING >= GV.deformSharedLowerLimit || deformation_MONITORING >= GV.deformSharedUpperLimit)));
}

void ExecutionThread::filteringOn(){
  filteringInProcess = true;
}
void ExecutionThread::filteringOff(){
  filteringInProcess = false;
}

void ExecutionThread::makeOrderToUnblockFiltering(bool isWorking){
  filteringInProcess = isWorking;
}

void ExecutionThread::setStatusOfFilteringSet(bool isInFilteringProcess){
  rawFiltering = isInFilteringProcess;
}

bool ExecutionThread::getStatusOfFilteringSet(){
  return rawFiltering;
}

bool ExecutionThread::getStatusOfUnblokFiltering(){
  return filteringInProcess;
}

void ExecutionThread::readParamsFromFlash(void){
  //read axis modes
  GV.positionAxisMode           = GVI.readValue<int>(GLOBAL_VARIABLES_POSITION_AXIS_MODE,           FLASH_MEMORY_TYPE);
  GV.strainAxisMode             = GVI.readValue<int>(GLOBAL_VARIABLES_STRAIN_AXIS_MODE,             FLASH_MEMORY_TYPE);
  GV.deformationAxisMode        = GVI.readValue<int>(GLOBAL_VARIABLES_DEFORMATION_AXIS_MODE,        FLASH_MEMORY_TYPE);
  GV.positionInvertAxis         = GVI.readValue<int>(GLOBAL_VARIABLES_POSITION_INVERT_AXIS,         FLASH_MEMORY_TYPE);
  GV.strainInvertAxis           = GVI.readValue<int>(GLOBAL_VARIABLES_STRAIN_INVERT_AXIS,           FLASH_MEMORY_TYPE);
  GV.deformationInvertAxis      = GVI.readValue<int>(GLOBAL_VARIABLES_DEFORMATION_INVERT_AXIS,      FLASH_MEMORY_TYPE);
  //read piston mode
  GV.pistonMode                 = GVI.readValue<int>(GLOBAL_VARIABLES_PISTON_MODE,                  FLASH_MEMORY_TYPE);
  //read vavle mode
  GV.valveDirectionMode         = GVI.readValue<int>(GLOBAL_VARIABLES_VALVE_DIRECTION_MODE,         FLASH_MEMORY_TYPE);
  //read piston params
  GV.PistonParams.topArea       = GVI.readValue<double>(GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA,       FLASH_MEMORY_TYPE);
  GV.PistonParams.bottomArea    = GVI.readValue<double>(GLOBAL_VARIABLES_PISTON_PARAMS_BOTTOM_AREA,    FLASH_MEMORY_TYPE);
  //read vavle params
  GV.ValveParams.Imax           = GVI.readValue<double>(GLOBAL_VARIABLES_VALVE_PARAMS_IMAX,            FLASH_MEMORY_TYPE);
  GV.ValveParams.Qvalve         = GVI.readValue<double>(GLOBAL_VARIABLES_VALVE_PARAMS_QVALVE,          FLASH_MEMORY_TYPE);

  //read strain sensor power voltage
  char *buffer = new char[sizeof(float)];
  if(internalFlash.readInOneSector(buffer, STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET, sizeof(float)) == 0){
    float voltage = NAN;
    basic.writeBytesBufferToValue(buffer, &voltage);
    uint32_t rawValue = 0xFFFFFFFF;
    basic.writeBytesBufferToValue(buffer, &rawValue);
    if(rawValue != 0xFFFFFFFF){
      if(!TaskManagerMailBox.full()){
        TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
        if (TaskManagerMail != nullptr){
          TaskManagerMail->task = Task::SET_REFERENCE_VOLTAGE;
          TaskManagerMail->dataLength = sizeof(float);
          std::copy(buffer, buffer + sizeof(float), TaskManagerMail->data);
          TaskManagerMailBox.put(TaskManagerMail);
        }
      }
    }
  }
  delete[] buffer;
}

uint64_t ExecutionThread::getCurrentCycle(void){
  uint64_t cycles = 0;
  switch (GV.Mode)
  {
    case DAC_STATE_DISP_SIN:
      cycles = GV.SINDisplacementModeParams.InternalCounter;
      break;
    case DAC_STATE_STRAIN_SIN:
      cycles = GV.SINStrainModeParams.InternalCounter;
      break;
    case DAC_STATE_DISP_SINUS_BASED:
      cycles = GV.SinusBasedDisplacementModeParams.InternalCounter;
      break;
    case DAC_STATE_STRAIN_SINUS_BASED:
      cycles = GV.SinusBasedStrainModeParams.InternalCounter;
      break;  
    case DAC_STATE_DEFORMATION_SIN:
      cycles = GV.SINDeformationModeParams.InternalCounter;
      break;
    case DAC_STATE_DEFORMATION_SINUS_BASED:
      cycles = GV.SinusBasedDeformationModeParams.InternalCounter;
      break;
    default:
      cycles = 0xFFFFFFFFFFFFFFFF;
      break;
  }
  return cycles;
}

void ExecutionThread::angleTriggersStateCalc(double tmpSinus){
  if (tmpSinus >= GV.tresholdForNullPointDeltaAccept){
    piDivTwoCrossed->push(true);
    treePiDivTwoCrossed->push(false);
  }
  else if (tmpSinus <= -GV.tresholdForNullPointDeltaAccept){
    piDivTwoCrossed->push(false);
    treePiDivTwoCrossed->push(true);
  }
  if (tmpSinus >= 0){
    zeroCrossed->push(true);
    piCrossed->push(false);
  }
  else {
    zeroCrossed->push(false);
    piCrossed->push(true);
  }
}

void ExecutionThread::resetAngleTriggers(){
  zeroCrossed->push(false);
  piDivTwoCrossed->push(false);
  piCrossed->push(false);
  treePiDivTwoCrossed->push(false);
}

void ExecutionThread::resetAmplitudeAttenuationCoefs(void){
    GV.nullPointDelta = 0.0;
    GV.prevNullPointDelta = 0.0;
    resetAngleTriggers();
    isUpHalfWaveFirst = false;
    isDownHalfWaveFirst = false;
    GV.preMinMaxCalculatingCountsMainProcess = -1;
    GV.minMaxCountsSwitcher = 0;
}

void ExecutionThread::SinusModesAmplAndSinCalc(SIN* sinusMode, double& currentCalculatedAmplitude, double& sinusCaclulated, MaxMinCalc* minMaxCalc){
      double currentUpAmplitude = 0.0;
      double currentDownAmplitude = 0.0;

      //synchronise values
      sinusMode->currentAmplitudeDirectionBuffered =  sinusMode->currentAmplitudeDirection;
      sinusMode->DesirePointBuffered =                sinusMode->DesirePoint;
      sinusMode->AngleWBuffered =                     sinusMode->AngleW;
      sinusMode->InternalCounterBuffered =            sinusMode->InternalCounter;

      //null point attenuation add
      if (sinusMode->amplitudeTuneInfo.mainProcess){
          if (GV.nullPointDelta < GV.prevNullPointDelta && piDivTwoCrossed->getState()){
            double tmpSetDelta = (GV.prevNullPointDelta - GV.nullPointDelta)/GV.nominalBothAmplAndSetBothAmplRatio;
            sinusMode->DownAmplitudeSet -= tmpSetDelta;
            sinusMode->UpAmplitudeSet += tmpSetDelta;
            GV.prevNullPointDelta = GV.nullPointDelta;
            minMaxCalc->reset();
          }
          else if (GV.nullPointDelta > GV.prevNullPointDelta && treePiDivTwoCrossed->getState()){
            double tmpSetDelta = (GV.nullPointDelta - GV.prevNullPointDelta)/GV.nominalBothAmplAndSetBothAmplRatio;
            sinusMode->UpAmplitudeSet -= tmpSetDelta;
            sinusMode->DownAmplitudeSet += tmpSetDelta;
            GV.prevNullPointDelta = GV.nullPointDelta;
            minMaxCalc->reset();
          }
      }
      //change direction amplitude 

      if (sinusMode->currentAmplitudeDirectionBuffered){
        currentDownAmplitude = GV.prevAmplitudeDownSet;
        if (treePiDivTwoCrossed->getState()){
          GV.prevAmplitudeUpSet = sinusMode->UpAmplitudeSet;
          if (preUpAmplitude != sinusMode->UpAmplitude){
            preUpAmplitude = sinusMode->UpAmplitude;
          }  
        }
        if(sinusMode->amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_DISABLE){
          currentDownAmplitude = preDownAmplitude;
          GV.prevAmplitudeDownSet = currentDownAmplitude;
        }
      }
      else{
        currentUpAmplitude = GV.prevAmplitudeUpSet;
        if (piDivTwoCrossed->getState()){
          GV.prevAmplitudeDownSet = sinusMode->DownAmplitudeSet;
          if (preDownAmplitude != sinusMode->DownAmplitude){
            preDownAmplitude = sinusMode->DownAmplitude;
          } 
        }
        if(sinusMode->amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_DISABLE){
          currentUpAmplitude = preUpAmplitude;
          GV.prevAmplitudeUpSet = currentUpAmplitude;

        }
      }
      //change frequency
      if(piCrossed->getState()||zeroCrossed->getState()){
        if(preModeFrequency != sinusMode->SINFrequency){
          preModeFrequency = sinusMode->SINFrequency;
        }
      } 

      //calculate current amplitude
      sinusCaclulated = sin(sinusMode->AngleWBuffered);
      if (sinusCaclulated > 0.0){
        currentCalculatedAmplitude = currentUpAmplitude;
      }
      else if (sinusCaclulated < 0.0){
        currentCalculatedAmplitude = currentDownAmplitude;
      }
      else currentCalculatedAmplitude = 0.0;
}

void ExecutionThread::SinusModesCalcNextAngle(SIN* sinusMode, double tmpSinus, bool isSinBased){
  //increment angle
  sinusMode->AngleWBuffered = sinusMode->AngleWBuffered 
  + (M_PI * preModeFrequency 
  * GV.TcycleTime / 1000) / 500.0;
  if (isSinBased && sinusMode->AngleWBuffered >= 2*M_PI){
    sinusMode->AngleWBuffered = 0;
  }
  //change amplitude value and min max state
  if (tmpSinus >= 0.0){
    displMaxMinCalc.pushWaveState(WAVESTATE_POSITIVE);
    strainMaxMinCalc.pushWaveState(WAVESTATE_POSITIVE);
    deformationMaxMinCalc.pushWaveState(WAVESTATE_POSITIVE);
    sinusMode->currentAmplitudeDirectionBuffered = 0;
  }
  else if (tmpSinus < 0.0){
    displMaxMinCalc.pushWaveState(WAVESTATE_NEGATIVE);
    strainMaxMinCalc.pushWaveState(WAVESTATE_NEGATIVE);
    deformationMaxMinCalc.pushWaveState(WAVESTATE_NEGATIVE);
    sinusMode->currentAmplitudeDirectionBuffered = 1; 
  }
  if (!isUpHalfWaveFirst && !isDownHalfWaveFirst && piDivTwoCrossed->getState()){
    isUpHalfWaveFirst = true;
  }
  if (!isDownHalfWaveFirst && !isUpHalfWaveFirst && treePiDivTwoCrossed->getState()){
    isDownHalfWaveFirst = true;
  }
  if (isUpHalfWaveFirst && zeroCrossed->getState()){
    sinusMode->InternalCounterBuffered++;
    if (sinusMode->amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_CORRECTION){
      StepByFreqyencyForSmoothStartStop(sinusMode, GV.reserveSinMainFrequency, GV.anchorSinFrequencyStop, sinusMode->amplitudeTuneInfo.amplitudeRiseCycles, sinusMode->amplitudeTuneInfo.amplitudeFallCycles);
    }
  }
  else if (isDownHalfWaveFirst && piCrossed->getState()){
    sinusMode->InternalCounterBuffered++;
    if (sinusMode->amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_CORRECTION){
      StepByFreqyencyForSmoothStartStop(sinusMode, GV.reserveSinMainFrequency, GV.anchorSinFrequencyStop, sinusMode->amplitudeTuneInfo.amplitudeRiseCycles, sinusMode->amplitudeTuneInfo.amplitudeFallCycles);
    }
  }
}

void ExecutionThread::SinusModesGenetateTargetPoints(SIN* sinusMode, MaxMinCalc* minMaxCalc, double nullPoint){
      double currentAmplitude = 0.0;
      double tmpSinus = 0.0;
      SinusModesAmplAndSinCalc(sinusMode, currentAmplitude, tmpSinus, minMaxCalc);
      //calculate desire point
      sinusMode->DesirePointBuffered = currentAmplitude * tmpSinus
                  + nullPoint + GV.prevNullPointDelta;
      angleTriggersStateCalc(tmpSinus);     
      SinusModesCalcNextAngle(sinusMode, tmpSinus, false);
}

void ExecutionThread::SinusBasedModesGenetateTargetPoints(SIN* sinusMode, MaxMinCalc* minMaxCalc, double nullPoint, uint32_t modeType, double baseRatio){
  double currentAmplitude = 0.0;
  double tmpSinus = 0.0;
  SinusModesAmplAndSinCalc(sinusMode, currentAmplitude, tmpSinus, minMaxCalc);
  //calculate desire point
  CalculateDesirePointSINBasedModes(sinusMode, nullPoint, modeType, currentAmplitude, baseRatio);
  angleTriggersStateCalc(tmpSinus);
  SinusModesCalcNextAngle(sinusMode, tmpSinus, true);
}

void ExecutionThread::CalculateDesirePointSINBasedModes(SIN* sinusMode, double nullPointMode, uint32_t modeType, double currentAmplitude, double baseRatio){
      switch (modeType)
      {
      case SINUS_BASED_SQUARE:{
        if (sinusMode->AngleWBuffered < M_PI){
          sinusMode->DesirePointBuffered = currentAmplitude
                  //* sin(sinusMode->AngleWBuffered)
                  + nullPointMode + GV.prevNullPointDelta;
        }else{
          sinusMode->DesirePointBuffered = -currentAmplitude
                    //* sin(sinusMode->AngleWBuffered)
                    + nullPointMode + GV.prevNullPointDelta;
        }
        break;
      }
      case SINUS_BASED_TRIANGLE:{
        //AREA 1
        if(sinusMode->AngleWBuffered >= 0 
            && sinusMode->AngleWBuffered < M_PI/2){
              sinusMode->DesirePointBuffered = (2 * sinusMode->AngleWBuffered 
                                                                          * (currentAmplitude)) / M_PI 
                                                                          + nullPointMode + GV.prevNullPointDelta;
        }else{
          //AREA 2
          if (sinusMode->AngleWBuffered >= M_PI/2
                && sinusMode->AngleWBuffered < M_PI){
                  sinusMode->DesirePointBuffered = (currentAmplitude) - (2 * (currentAmplitude) 
                  * (sinusMode->AngleWBuffered - M_PI/2) / M_PI) + nullPointMode + GV.prevNullPointDelta;
          }else{
            //AREA 3
            if (sinusMode->AngleWBuffered >= M_PI
                  && sinusMode->AngleWBuffered < 3*M_PI/2){
                    sinusMode->DesirePointBuffered = 2 * (-currentAmplitude) 
                                                                                * (sinusMode->AngleWBuffered - M_PI)/M_PI
                                                                                + nullPointMode + GV.prevNullPointDelta;
            }else{
              //AREA 4
              sinusMode->DesirePointBuffered = -currentAmplitude - 2 * (-currentAmplitude) *
                                                                          (sinusMode->AngleWBuffered - 3*M_PI/2)/M_PI
                                                                          + nullPointMode + GV.prevNullPointDelta;
            }
          }
        }
        break;
      }
      case SINUS_BASED_TRAPEZE:{
        double x1 = M_PI * (1 - baseRatio)/2;
        double x2 = M_PI * (1 + baseRatio)/2;
        double x3 = M_PI * (3 - baseRatio)/2;
        double x4 = M_PI * (3 + baseRatio)/2;
        //AREA 1
        if(sinusMode->AngleWBuffered >= 0 
            && sinusMode->AngleWBuffered < x1){
              sinusMode->DesirePointBuffered = (2 * sinusMode->AngleWBuffered 
                                                                          * (currentAmplitude)) / (M_PI * (1 - 
                                                                          baseRatio)) 
                                                                          + nullPointMode + GV.prevNullPointDelta;
        }else{
          //AREA 2
          if (sinusMode->AngleWBuffered >= x1
                && sinusMode->AngleWBuffered < x2){
                  sinusMode->DesirePointBuffered = (currentAmplitude) 
                                              + nullPointMode + GV.prevNullPointDelta;
          }else{
            //AREA 3
            if (sinusMode->AngleWBuffered >= x2
                  && sinusMode->AngleWBuffered < M_PI){
                    sinusMode->DesirePointBuffered = (2 * (currentAmplitude) 
                                                                                * (-sinusMode->AngleWBuffered + M_PI))
                                                                                /(M_PI * (1 - baseRatio))
                                                                                + nullPointMode + GV.prevNullPointDelta;
            }else{
              //AREA 4
              if (sinusMode->AngleWBuffered >= M_PI
                    && sinusMode->AngleWBuffered < x3){
                      sinusMode->DesirePointBuffered = (2 * (-currentAmplitude) *
                                                                                (sinusMode->AngleWBuffered - M_PI))
                                                                                / (M_PI * (1 - baseRatio))
                                                                                + nullPointMode + GV.prevNullPointDelta;
              }else{
                //AREA 5
                if (sinusMode->AngleWBuffered >= x3
                      && sinusMode->AngleWBuffered < x4){
                        sinusMode->DesirePointBuffered = -currentAmplitude
                                                                                  + nullPointMode + GV.prevNullPointDelta;
                }else{
                  //AREA 6
                  sinusMode->DesirePointBuffered = (2 * (-currentAmplitude) *
                                                                                (-sinusMode->AngleWBuffered + 2 * M_PI))
                                                                                / (M_PI * (1 - baseRatio))
                                                                                + nullPointMode + GV.prevNullPointDelta;
                }
                    
              }
            }
          }
        }
        break;
      }
      default:
        break;
      }
}

void ExecutionThread::PrepareForAmplitudeTune(SIN* sinusMode){
  this->resetAmplitudeAttenuationCoefs();              
  // if(sinusMode->amplitudeTuneInfo.startProcess){
  //   sinusMode->DownAmplitudeSet = sinusMode->DownAmplitude/sinusMode->amplitudeTuneInfo.amplitudeRiseCycles;
  //   sinusMode->UpAmplitudeSet = sinusMode->UpAmplitude/sinusMode->amplitudeTuneInfo.amplitudeRiseCycles;
  //   if (sinusMode->DownAmplitudeSet < sinusMode->amplitudeTuneInfo.minDownAmplitude){
  //     sinusMode->DownAmplitudeSet = sinusMode->amplitudeTuneInfo.minDownAmplitude;
  //   }
  //   if (sinusMode->UpAmplitudeSet < sinusMode->amplitudeTuneInfo.minUpAmplitude){
  //     sinusMode->UpAmplitudeSet = sinusMode->amplitudeTuneInfo.minUpAmplitude;
  //   }
  // }
  // else{
    sinusMode->DownAmplitudeSet = sinusMode->DownAmplitude * GV.startStopAmplitudeRatio;
    sinusMode->UpAmplitudeSet = sinusMode->UpAmplitude  * GV.startStopAmplitudeRatio;
    
  // }
  GV.prevAmplitudeDownSet = sinusMode->DownAmplitudeSet;
  GV.prevAmplitudeUpSet = sinusMode->UpAmplitudeSet;

  preDownAmplitude = sinusMode->DownAmplitude;
  preUpAmplitude = sinusMode->UpAmplitude;
  preModeFrequency = sinusMode->ModeFrequency;

  if(sinusMode->amplitudeTuneInfo.state == AMPLITUDE_TUNE_STATE_ENABLE){
    sinusMode->amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_INIT;
    if(sinusMode->amplitudeTuneInfo.startProcess){
      sinusMode->SINFrequency = GV.anchorSinFrequency;
    }
    GV.isStopTuneModeAmplitudeEnabled = false;
  }
  else {
    sinusMode->DownAmplitudeSet = sinusMode->DownAmplitude;
    sinusMode->UpAmplitudeSet = sinusMode->UpAmplitude;
    GV.prevAmplitudeDownSet = sinusMode->DownAmplitudeSet;
    GV.prevAmplitudeUpSet = sinusMode->UpAmplitudeSet;
  }
}

void ExecutionThread::StepByFreqyencyForSmoothStartStop(SIN* sinusMode, double targetFreqMain, double targetFreqStop, uint32_t& numberOfRemainderStepsRise, uint32_t& numberOfRemainderStepsFall){
  uint32_t numbOfCycl = (sinusMode->NumberOfCycles - sinusMode->InternalCounterBuffered);
  if (numberOfRemainderStepsRise >= 0 && sinusMode->amplitudeTuneInfo.startProcess){
    if (numberOfRemainderStepsRise == 0){
      sinusMode->SINFrequency = targetFreqMain;
      numberOfRemainderStepsRise --;
      sinusMode->amplitudeTuneInfo.startProcess = false;
      //GV.minMaxCalculatingCounts = GV.minMaxCalculatingCountsMainProcess;
    }
    else {
      sinusMode->SINFrequency += (targetFreqMain - sinusMode->SINFrequency)/numberOfRemainderStepsRise;
      numberOfRemainderStepsRise --;
    }
  }
  else if (sinusMode->amplitudeTuneInfo.stop && numbOfCycl <= numberOfRemainderStepsFall){
    sinusMode->amplitudeTuneInfo.mainProcess = false;
      if (!GV.isStopTuneModeAmplitudeEnabled){
        GV.isStopTuneModeAmplitudeEnabled = true;
        sinusMode->DownAmplitude = sinusMode->DownAmplitude * GV.stopAmplitudeRatio;
        sinusMode->UpAmplitude = sinusMode->UpAmplitude * GV.stopAmplitudeRatio;
        sinusMode->DownAmplitudeSet = sinusMode->DownAmplitude;
        sinusMode->UpAmplitudeSet = sinusMode->UpAmplitude;
      }
    sinusMode->SINFrequency -= (sinusMode->SINFrequency - GV.anchorSinFrequencyStop)/numberOfRemainderStepsFall;
    numberOfRemainderStepsFall --;
  }
  if (sinusMode->amplitudeTuneInfo.mainProcess && !sinusMode->amplitudeTuneInfo.startProcess && GV.minMaxCountsSwitcher < GV.minMaxCountsSwitcherLimit){
    GV.minMaxCountsSwitcher ++;
  }
}

void ExecutionThread::CheckUpAndDownAmplitudeSet(SIN* sinusMode){
  sinusMode->DownAmplitudeSet = sinusMode->DownAmplitude * GV.startStopAmplitudeRatio;
  sinusMode->UpAmplitudeSet = sinusMode->UpAmplitude * GV.startStopAmplitudeRatio;
  GV.prevAmplitudeDownSet = sinusMode->DownAmplitudeSet;
  GV.prevAmplitudeUpSet = sinusMode->UpAmplitudeSet;
}

void ExecutionThread::ConstModeNextDesirePointCalculating(CONST* constMode, double& dataToHold){
  if(constMode->speedEnable){
    //if (constMode->msCounter >= 40){
      if(constMode->t > constMode->msCounter){
        constMode->msCounter += (GV.TcycleTime / 1000);
        constMode->nextDesirePoint = (constMode->k * constMode->msCounter / 1000) + constMode->b;
      }
      else{
        constMode->nextDesirePoint = dataToHold;
        constMode->speedEnable = false;
      }
    //}
  }else{
    constMode->speedEnable = false;
    constMode->msCounter = 0; //??
    constMode->nextDesirePoint = dataToHold; //??
  }
}
