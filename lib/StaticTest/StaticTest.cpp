#include "StaticTest.h"

StaticTest::StaticTest(globalVariables_t *globalVariable){
    this->_globalVariable = globalVariable;
    SBD = new SampleBreakDetection();
    SBD_Mode = new SampleBreakDetection(SBD_MODE_DYNAMIC_FALL);
    sampleStatus = SBD_STATUS_OK;
}

StaticTest::~StaticTest(void){
    this->_globalVariable = nullptr;
    delete SBD;
    delete SBD_Mode;
}

void StaticTest::convertValuesInSteps(void){
  for(int i = 0; i < _globalVariable->staticTestStepsCount; i++){
    if (_globalVariable->staticTestSteps[i].panel_type == STATIC_TEST_PANEL_TYPE_ACTION){
      if (_globalVariable->staticTestSteps[i].isp_type == STATIC_TEST_ISP_TYPE_TEST){
        if (_globalVariable->staticTestSteps[i].id_boolparam == STATIC_TEST_BOOLPARAM_DISPL_VELOCITY){
          _globalVariable->staticTestSteps[i].value = _globalVariable->staticTestSteps[i].value / 60.0;
        }
        if (_globalVariable->staticTestSteps[i].id_boolparam == STATIC_TEST_BOOLPARAM_DEFORMATION){
          _globalVariable->staticTestSteps[i].value = _globalVariable->staticTestSteps[i].value / 60.0;
        }
      }
    }
  }
}

void StaticTest::init(void){
  StatTestTimer.reset();
  StatTestTimer.start();
  this->convertValuesInSteps();
  this->_globalVariable->currentStaticTestStep = 0;
  this->_globalVariable->InternalTaskState = INTERNAL_TASK_STATE_STEP_1;
  //this->_globalVariable->ConstModeParams.ConstFrequency = 0.1;
  //this->initConstDisplMaxVoltage = _globalVariable->ConstDisplacementModeParams.MaxVoltage;
  //this->initConstStrainMaxVoltage = _globalVariable->ConstStrainModeParams.MaxVoltage;
  this->initConstDisplSpeed = _globalVariable->ConstDisplacementModeParams.Speed;
  this->initConstStrainSpeed = _globalVariable->ConstStrainModeParams.Speed;
  this->initConstDeformSpeed = _globalVariable->ConstDeformationModeParams.Speed;
  this->_globalVariable->staticTestSteps[0].initPosition = this->_globalVariable->roCurrentAvPosition;
  this->_globalVariable->staticTestSteps[0].initStrain = this->_globalVariable->roCurrentAvStrain;
  this->_globalVariable->staticTestSteps[0].initDeformation = this->_globalVariable->roCurrentAvDeformation;
  this->_globalVariable->staticTestSteps[0].initTime = StatTestTimer.elapsed_time();
  this->_globalVariable->staticTestSteps[0].currentCycleCount = this->_globalVariable->staticTestSteps[0].cycle;
  //Sample Break Detection
  sampleStatus = SBD_STATUS_OK;
  this->SBD->setModeParams(_globalVariable->SBDProcentOfMaxStrain1, _globalVariable->SBDStartStrain1, _globalVariable->SBDThreshold);
  this->SBD_Mode->setModeParams(_globalVariable->SBDProcentOfMaxStrain2, _globalVariable->SBDStartStrain2, _globalVariable->SBDTime);
  this->SBD->init(SBD_MODE_PERCENT_OF_MAX_STRAIN, 1, _globalVariable->roCurrentAvStrain);//TODO: tension direction
  this->SBD_Mode->init(SBD_MODE_DYNAMIC_FALL, 1, _globalVariable->roCurrentAvStrain);
          //this->_globalVariable->ConstModeParams.Direction = -1;
  this->SBD->setEnable(_globalVariable->SBDStateMaxStrain);
  this->SBD_Mode->setEnable(_globalVariable->SBDStateDF);
}

void StaticTest::process(void){
      if (this->_globalVariable->staticTestStepsCount > this->_globalVariable->currentStaticTestStep){
        //this->updateValues();
        switch (this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].panel_type)
          {
          case STATIC_TEST_PANEL_TYPE_ACTION:{
            switch (this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].isp_type)
            {
            case STATIC_TEST_ISP_TYPE_TEST:
              switch (this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].id_boolparam)
              {
              case STATIC_TEST_BOOLPARAM_DISPL_VELOCITY:
                //TODO change speed to voltage
                //this->_globalVariable->ConstModeParams.Voltage = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                //this->_globalVariable->Mode = DAC_STATE_CONST_LEVEL;
                //this->_globalVariable->ConstDisplacementModeParams.MaxVoltage = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                this->_globalVariable->ConstDisplacementModeParams.Speed = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                break;
              case STATIC_TEST_BOOLPARAM_STRAIN_VELOCITY:
                //TODO change speed to voltage
                //this->_globalVariable->ConstModeParams.Voltage = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                //this->_globalVariable->Mode = DAC_STATE_CONST_LEVEL;
               // this->_globalVariable->ConstStrainModeParams.MaxVoltage = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                this->_globalVariable->ConstStrainModeParams.Speed = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                break;
              case STATIC_TEST_BOOLPARAM_CHANGE_DIRECTION:
                if (this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value <= 0){
                  this->_globalVariable->ConstModeParams.Direction = 1 * _globalVariable->pistonMode * _globalVariable->valveDirectionMode;
                }else{
                  this->_globalVariable->ConstModeParams.Direction = -1 * _globalVariable->pistonMode * _globalVariable->valveDirectionMode;
                }
                break;
              case STATIC_TEST_BOOLPARAM_DEFORMATION:
                this->_globalVariable->ConstDeformationModeParams.Speed = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                break;
              default:
                break;
              }
              break;
            case STATIC_TEST_ISP_TYPE_EXPOSURE:
              switch (this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].id_boolparam)
              {
                case STATIC_TEST_BOOLPARAM_DISPL_HOLD:
                  //this->_globalVariable->ConstDisplacementModeParams.MaxVoltage = this->initConstDisplMaxVoltage;
                //this->_globalVariable->ConstDisplacementModeParams.Speed = this->initConstDisplSpeed;
                  //this->_globalVariable->ConstDisplacementModeParams.PositionToHold = this->_globalVariable->roCurrentPosition;//this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                  //this->_globalVariable->Mode = DAC_STATE_DISP_CONST;
                  break;
                case STATIC_TEST_BOOLPARAM_STRAIN_HOLD:
                  //this->_globalVariable->ConstStrainModeParams.MaxVoltage = this->initConstStrainMaxVoltage;
                //this->_globalVariable->ConstDisplacementModeParams.Speed = this->initConstStrainSpeed;
                  //this->_globalVariable->ConstStrainModeParams.StrainToHold = this->_globalVariable->roCurrentStrain;//this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].value;
                  //this->_globalVariable->Mode = DAC_STATE_STRAIN_CONST;
                  break;
                default://TODO HOLD_TO_CONFIRM
                  break;
              }
              break;
            default:
              break;
            }
            
            
           break;
          }
          case STATIC_TEST_PANEL_TYPE_CONDITION:{
            
            break;
          }

          default:
            break;
          }
        for(int i = 0; i < maxConditionsSteps; i++){
              int nextIndex = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].rel_arr[i] - 1;
              if(this->_globalVariable->_nextIndex){
                StatTestTimer.start();
                this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
                this->_globalVariable->_nextIndex = false;
              }
              //this->_globalVariable->_nextIndex = nextIndex + 1;
              switch (this->_globalVariable->staticTestSteps[nextIndex].panel_type)
              {
              case STATIC_TEST_PANEL_TYPE_CONDITION:
                switch (this->_globalVariable->staticTestSteps[nextIndex].isp_type)
                {
                case STATIC_TEST_ISP_TYPE_TEST:
                  switch (this->_globalVariable->staticTestSteps[nextIndex].id_boolparam)
                  {
                  case STATIC_TEST_BOOLPARAM_MOVE_TO:
                    if(!this->_globalVariable->staticTestSteps[nextIndex].firstTime){
                      this->_globalVariable->staticTestSteps[nextIndex].firstTime = true;
                      this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount = 
                        this->_globalVariable->staticTestSteps[nextIndex].cycle;
                      this->_globalVariable->ConstDisplacementModeParams.speedEnable = false;
                      //this->_globalVariable->ConstDisplacementModeParams.Speed = this->initConstDisplSpeed;
                      this->_globalVariable->ConstDisplacementModeParams.PositionToHold = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initPosition + this->_globalVariable->staticTestSteps[nextIndex].value * this->_globalVariable->ConstModeParams.Direction;
                      this->_globalVariable->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                      this->_globalVariable->Mode = DAC_STATE_DISP_CONST;
                    }
                    if((abs(this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initPosition - this->_globalVariable->roCurrentAvPosition)) <= (this->_globalVariable->staticTestSteps[nextIndex].value + this->positionUpperThreshold) &&
                       (abs(this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initPosition - this->_globalVariable->roCurrentAvPosition)) >= (this->_globalVariable->staticTestSteps[nextIndex].value - this->positionLowerThreshold)){
                         //this->_globalVariable->ConstDisplacementModeParams.PositionToHold = this->_globalVariable->roCurrentPosition;
                         //this->_globalVariable->Mode = DAC_STATE_DISP_CONST;
                         
                         this->checkCycles(nextIndex);
                    }
                    break;
                  case STATIC_TEST_BOOLPARAM_LOAD_ON:
                    if(!this->_globalVariable->staticTestSteps[nextIndex].firstTime){
                      this->_globalVariable->staticTestSteps[nextIndex].firstTime = true;
                      this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount = 
                        this->_globalVariable->staticTestSteps[nextIndex].cycle;
                      this->_globalVariable->ConstStrainModeParams.speedEnable = false;
                      //this->_globalVariable->ConstStrainModeParams.Speed = this->initConstDisplSpeed;
                      this->_globalVariable->ConstStrainModeParams.StrainToHold = 
                              /*this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initStrain + */
                              this->_globalVariable->staticTestSteps[nextIndex].value * this->_globalVariable->ConstModeParams.Direction;
                     this->_globalVariable->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
                      this->_globalVariable->Mode = DAC_STATE_STRAIN_CONST;
                    }
                    if ((abs(this->_globalVariable->roCurrentAvStrain)) <= (this->_globalVariable->staticTestSteps[nextIndex].value + this->strainUpperThreshold) &&
                        (abs(this->_globalVariable->roCurrentAvStrain)) >= (this->_globalVariable->staticTestSteps[nextIndex].value - this->strainUpperThreshold)){
                          //this->_globalVariable->ConstStrainModeParams.StrainToHold = this->_globalVariable->roCurrentStrain;
                          //this->_globalVariable->Mode = DAC_STATE_STRAIN_CONST;
                          this->checkCycles(nextIndex);
                        }
                    break;
                  case STATIC_TEST_BOOLPARAM_DEFORM_TO:{
                    if(!this->_globalVariable->staticTestSteps[nextIndex].firstTime){
                      this->_globalVariable->staticTestSteps[nextIndex].firstTime = true;
                      this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount = 
                        this->_globalVariable->staticTestSteps[nextIndex].cycle;
                      this->_globalVariable->ConstDeformationModeParams.speedEnable = false;
                      //this->_globalVariable->ConstDeformationModeParams.Speed = this->initConstDeformSpeed;
                      this->_globalVariable->ConstDeformationModeParams.DeformationToHold = this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initDeformation + this->_globalVariable->staticTestSteps[nextIndex].value * this->_globalVariable->ConstModeParams.Direction;
                      this->_globalVariable->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                      this->_globalVariable->Mode = DAC_STATE_DEFORMATION_CONST;
                    }
                    if((abs(this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initDeformation - this->_globalVariable->roCurrentAvDeformation)) <= (this->_globalVariable->staticTestSteps[nextIndex].value + this->deformationUpperThreshold) &&
                       (abs(this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initDeformation - this->_globalVariable->roCurrentAvDeformation)) >= (this->_globalVariable->staticTestSteps[nextIndex].value - this->deformationLowerThreshold)){
                         //this->_globalVariable->ConstDeformationModeParams.DeformationToHold = this->_globalVariable->roCurrentDeformation;
                         //this->_globalVariable->Mode = DAC_STATE_DEFORMATION_CONST;
                         
                         this->checkCycles(nextIndex);
                    }                    
                    break;
                  }
                  case STATIC_TEST_BOOLPARAM_CHANGE_DIRECTION:{
                    this->checkCycles(nextIndex);
                    break;
                  }
                  default://TODO angle
                    this->checkCycles(nextIndex);
                    break;
                  }
                  break;
                case STATIC_TEST_ISP_TYPE_EXPOSURE:
                  if (StatTestTimer.elapsed_time() - this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].initTime
                      >= std::chrono::microseconds(static_cast<uint64_t>(this->_globalVariable->staticTestSteps[nextIndex].value * 1000000))){
                        if(!this->_globalVariable->staticTestSteps[nextIndex].firstTime){
                          this->_globalVariable->staticTestSteps[nextIndex].firstTime = true;
                          this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount = 
                            this->_globalVariable->staticTestSteps[nextIndex].cycle;
                        }
                        //this->_globalVariable->ConstDisplacementModeParams.PositionToHold = this->_globalVariable->roCurrentPosition;
                        //this->_globalVariable->Mode = DAC_STATE_DISP_CONST;
                        this->checkCycles(nextIndex);
                      }
                  break;
                case STATIC_TEST_ISP_TYPE_STOP_UNTIL_CONFIRM:
                  //TODO
                  this->checkCycles(nextIndex);
                  break;
                default:
                  this->checkCycles(nextIndex);
                  break;
                }
                break;
              default:
                break;
              }
            
            }
        if(this->SBD->process(_globalVariable->roCurrentStrain) == SBD_STATUS_BREAK_MAX_STRAIN){
          //DigitalOut led1(LED1);
          //led1.write(1);
          //delayedAction.attach(callback(_caller, &ExecutionThread::setConstDisplMode), 200ms);
          //_globalVariable->ConstDisplacementModeParams.PositionToHold = _globalVariable->roCurrentPosition;
          //_globalVariable->Mode = DAC_STATE_DISP_CONST;
          this->sampleStatus = SBD_STATUS_BREAK_MAX_STRAIN;
          this->_globalVariable->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
        }
        if(this->SBD_Mode->process(_globalVariable->roCurrentStrain) == SBD_STATUS_BREAK_DYNAMIC_FALL){
          //DigitalOut led1(LED1);
          //led1.write(1);
          //delayedAction.attach(callback(_caller, &ExecutionThread::setConstDisplMode), 200ms);
          //_globalVariable->ConstDisplacementModeParams.PositionToHold = _globalVariable->roCurrentPosition;
          //_globalVariable->Mode = DAC_STATE_DISP_CONST;
          this->sampleStatus = SBD_STATUS_BREAK_DYNAMIC_FALL;
          this->_globalVariable->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
        }
      }
      else{
        this->_globalVariable->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
      }
}

//PRIVATE
void StaticTest::checkCycles(int nextIndex){
  if(this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount > 0){
   this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount--;
   //return
   this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].vozvrat - 1;
   _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].firstTime = false;
   _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].currentCycleCount = _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].cycle;
   this->fixCurrentState();
  }else{
   this->findNextPair(nextIndex);
  }
}

void StaticTest::fixCurrentState(void){
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initPosition = _globalVariable->roCurrentAvPosition;
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initStrain = _globalVariable->roCurrentAvStrain;
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initDeformation = _globalVariable->roCurrentAvDeformation;
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initTime = StatTestTimer.elapsed_time();
}

void StaticTest::updateValues(void){
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initPosition = _globalVariable->roCurrentAvPosition;
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initStrain = _globalVariable->roCurrentAvStrain;
  _globalVariable->staticTestSteps[_globalVariable->currentStaticTestStep].initDeformation = _globalVariable->roCurrentAvDeformation;
}

void StaticTest::findNextPair(int nextIndex){
    if (this->_globalVariable->staticTestSteps[nextIndex].rel_arr[0] == 0){
       if (this->_globalVariable->staticTestSteps[nextIndex].rel_arr[1] == 0){
         if (this->_globalVariable->staticTestSteps[nextIndex].rel_arr[2] == 0){
           if (this->_globalVariable->staticTestSteps[nextIndex].rel_arr[3] == 0){
             if (this->_globalVariable->staticTestSteps[nextIndex].rel_arr[4] == 0){
               this->_globalVariable->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
             }else{
               this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].firstTime = false;
               this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].currentCycleCount =
                this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].cycle;
               this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
               this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount =
                this->_globalVariable->staticTestSteps[nextIndex].cycle;
               this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].rel_arr[4] - 1;
               this->fixCurrentState();
             }
           }else{
              this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].firstTime = false;
              this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].currentCycleCount =
                this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].cycle;
              this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
              this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount =
                this->_globalVariable->staticTestSteps[nextIndex].cycle;
              this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].rel_arr[3] - 1;
              this->fixCurrentState();
           }
         }else{
            this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].firstTime = false;
            this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].currentCycleCount =
                this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].cycle;
            this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
            this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount =
                this->_globalVariable->staticTestSteps[nextIndex].cycle;
            this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].rel_arr[2] - 1;
            this->fixCurrentState();
         }
       }else{
         this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].firstTime = false;
         this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].currentCycleCount =
                this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].cycle;
         this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
         this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount =
                this->_globalVariable->staticTestSteps[nextIndex].cycle;
         this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].rel_arr[1] - 1;
         this->fixCurrentState();
       }
    }else{
      this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].firstTime = false;
      this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].currentCycleCount =
                this->_globalVariable->staticTestSteps[this->_globalVariable->currentStaticTestStep].cycle;
      this->_globalVariable->staticTestSteps[nextIndex].firstTime = false;
      this->_globalVariable->staticTestSteps[nextIndex].currentCycleCount =
                this->_globalVariable->staticTestSteps[nextIndex].cycle;
      this->_globalVariable->currentStaticTestStep = this->_globalVariable->staticTestSteps[nextIndex].rel_arr[0] - 1;
      this->fixCurrentState();
    }
}

//double StaticTest::getInitConstDisplMaxVoltage(void){
//  return this->initConstDisplMaxVoltage;
//}
//
//double StaticTest::getInitConstStrainMaxVoltage(void){
//  return this->initConstStrainMaxVoltage;
//}

double StaticTest::getInitConstDisplSpeed(void){
  return this->initConstDisplSpeed;
}

double StaticTest::getInitConstStrainSpeed(void){
  return this->initConstStrainSpeed;
}

double StaticTest::getInitConstDeformSpeed(void){
  return this->initConstDeformSpeed;
}

void StaticTest::setPositionThreshold(double upperThreshold, double lowerThreshold){
  this->positionUpperThreshold = upperThreshold;
  this->positionLowerThreshold = lowerThreshold;
}
void StaticTest::setStrainThreshold(double upperThreshold, double lowerThreshold){
  this->strainUpperThreshold = upperThreshold;
  this->strainLowerThreshold = lowerThreshold;
}
void StaticTest::setDeformationThreshold(double upperThreshold, double lowerThreshold){
  this->deformationUpperThreshold = upperThreshold;
  this->deformationLowerThreshold = lowerThreshold;
}
void StaticTest::getPositionThreshold(double &upperThreshold, double &lowerThreshold){
  upperThreshold = this->positionUpperThreshold;
  lowerThreshold = this->positionLowerThreshold;
}
void StaticTest::getStrainThreshold(double &upperThreshold, double &lowerThreshold){
  upperThreshold = this->strainUpperThreshold;
  lowerThreshold = this->strainLowerThreshold;
}
void StaticTest::getDeformationThreshold(double &upperThreshold, double &lowerThreshold){
  upperThreshold = this->deformationUpperThreshold;
  lowerThreshold = this->deformationLowerThreshold;
}

void StaticTest::stopTimer(){
  StatTestTimer.stop();
}