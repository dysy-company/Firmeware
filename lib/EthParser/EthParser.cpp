/*
	RSSI.h - Library for getting data from R Series throught SSI interface.
	Created by Bragin Grigorii. 2020
	Release to nothing. GGGG.
*/
//#include "Threads_Mail_Config.h"
#include <EthParser.h>
#include <DataExchangeProtocol.h>
 
EthernetParser::EthernetParser(globalVariables_t *globalVariables, GlobalVariablesInterface *globalVariablesInterface, ExecutionThread* ExeThr){
  this->_globalVariables = globalVariables;
  this->_globalVariablesInterface = globalVariablesInterface;
  this->ExeThr = ExeThr;
  positionToHoldTimeout = new Timeout;
}

EthernetParser::~EthernetParser(){
	delete positionToHoldTimeout;
}

int EthernetParser::writeValue(char *data, uint32_t &dataLength, char *value)
{
  if (dataLength > 500) // error if packet > ~600 bytes
  {
    return -1;
  }
  else
  {
    basic.writeArrayToArray(value, 0, dataLength, data, 0);
    return 1;
  }
}


int EthernetParser::writeValue(char *data, uint32_t &dataLength, double &value){
  if (dataLength == 8){
    basic.writeBytesBufferToValue(data, &doubleValue);
    value = doubleValue;
    //debugMessage = "\n" + debugMessage + " %.3f\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}
int EthernetParser::writeValue(char *data, uint32_t &dataLength, uint32_t &value){
  if (dataLength == 4){
    basic.writeBytesBufferToValue(data, &uint32Value);
    value = uint32Value;
    //debugMessage = "\n" + debugMessage + " %d\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}

int EthernetParser::writeValue(char *data, uint32_t &dataLength, std::chrono::microseconds &value){
  uint64Value = (uint64_t)value.count();
  return this->writeValue(data, dataLength, uint64Value);
}

int EthernetParser::writeValue(char *data, uint32_t &dataLength, uint64_t &value){
  if (dataLength == 8){
    basic.writeBytesBufferToValue(data, &uint64Value);
    value = uint64Value;
    //debugMessage = "\n" + debugMessage + " %i\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}
int EthernetParser::writeValue(char *data, uint32_t &dataLength, long &value){
  if (dataLength == 4){
    basic.writeBytesBufferToValue(data, &int32Value);
    value = int32Value;
    //debugMessage = "\n" + debugMessage + " %d\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}
int EthernetParser::writeValue(char *data, uint32_t &dataLength, long long &value){
  if (dataLength == 8){
    basic.writeBytesBufferToValue(data, &longLongValue);
    value = longLongValue;
    //debugMessage = "\n" + debugMessage + " %i\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}

int EthernetParser::writeValue(char *data, uint32_t &dataLength, uint8_t &value){
  if (dataLength == 1){
    basic.writeBytesBufferToValue(data, &uint8Value);
    value = uint8Value;
    //debugMessage = "\n" + debugMessage + " %i\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}

int EthernetParser::writeValue(char *data, uint32_t &dataLength, int &value){
  if (dataLength == 4){
    basic.writeBytesBufferToValue(data, &int32Value);
    value = int32Value;
    //debugMessage = "\n" + debugMessage + " %i\n\r";
    //printf(debugMessage.c_str(), value);
    return 1;
  }
  else{
    return -1;
  }
}

void EthernetParser::addTask(Task &task, char *data, uint32_t &dataLength){
  if(!TaskManagerMailBox.full()){
    TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    if (TaskManagerMail != nullptr){
      TaskManagerMail->task = task;
      TaskManagerMail->dataLength = dataLength;
      std::copy(data, data + dataLength, TaskManagerMail->data);
      TaskManagerMailBox.put(TaskManagerMail);
    }
  }
}
void EthernetParser::addTask(Task &task){
  if(!TaskManagerMailBox.full()){
    TaskManagerMail_t *TaskManagerMail = TaskManagerMailBox.try_alloc_for(0ms);
    if (TaskManagerMail != nullptr){
      TaskManagerMail->task = task;
      TaskManagerMail->dataLength = 0;
      TaskManagerMailBox.put(TaskManagerMail);
    }
  }
}

uint32_t EthernetParser::parse(COMMAND &command, uint32_t &dataLength, char *data){
    Task task = Task::NONE;
    uint32_t error = ETHERNET_NO_ERROR;
    //TaskManagerMail_t *TaskManagerMail;
    switch (command)
      {
      case COMMAND::GET_FIRMWARE_NAME:
      {
        dataLength = uint32_t(sizeof FIRMWARE_NAME);
        writeValue(data, dataLength, FIRMWARE_NAME); //
        break;
      }
      case COMMAND::GET_FIRMWARE_VERSION:
      {
        dataLength = uint32_t(sizeof(double));
        double version = FIRMWARE_VERSION;
        basic.writeValueToBytesBuffer(data, version);
        break;
      }
      case COMMAND::GET_CONTROLLER_BOARD_TYPE:
      {
        dataLength = 30;
        char* machine_type = new char[dataLength];

        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
          strncpy(machine_type, "SERVO_MECHANICAL", sizeof(machine_type) - 1);
        #else
          #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
            strncpy(machine_type, "SERVO_HYDRAULIC_GREEN", sizeof(machine_type) - 1);
          #else
            #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)
              strncpy(machine_type, "SERVO_HYDRAULIC_RED", sizeof(machine_type) - 1);
            #else  
              strncpy(machine_type, "UNDEFINED", sizeof(machine_type) - 1);
            #endif
          #endif
        #endif

        writeValue(data, dataLength, machine_type);
        delete[] machine_type;
        break;
      }
      case COMMAND::GET_PIN_TYPES:
      {
        dataLength = 400;
        char* dataChar = new char[dataLength];
        cmdMap.getAllPins(dataChar);
        writeValue(data, dataLength, dataChar); //
        delete[] dataChar;
        break;
      }
      case COMMAND::GET_STATIC_TEST_THRESHOLDS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->positionUpperThreshold);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->positionLowerThreshold);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->strainUpperThreshold);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->strainLowerThreshold);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->deformationUpperThreshold);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->deformationLowerThreshold);
        break;
      }
      //SETMODE
      case COMMAND::SET_MODE:
        basic.writeBytesBufferToValue(data, &uint32Value);
        //reset next mode
        this->checkResetMode(uint32Value);
        writeValue(data, dataLength, _globalVariables->Mode);
        //printf(basic.modeToString(_globalVariables->Mode).c_str());
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      case COMMAND::SET_PAUSE:{
        uint8_t dummy = 0;
        basic.writeBytesBufferToValue(data, &dummy);
        if(dummy == TEST_PROCESS_PAUSE){
          if(_globalVariables->testProcessPause.status == TEST_PROCESS_CONTINUE){
            //task to pause
            _globalVariables->testProcessPause.status = TEST_PROCESS_PAUSE;
            _globalVariables->testProcessPause.modeBeforePause = _globalVariables->Mode;
            _globalVariables->testProcessPause.displSharedLowerLimit = _globalVariables->displSharedLowerLimit;
            _globalVariables->testProcessPause.displSharedUpperLimit = _globalVariables->displSharedUpperLimit;
            _globalVariables->testProcessPause.strainSharedLowerLimit = _globalVariables->strainSharedLowerLimit;
            _globalVariables->testProcessPause.strainSharedUpperLimit = _globalVariables->strainSharedUpperLimit;
            _globalVariables->testProcessPause.deformSharedLowerLimit = _globalVariables->deformSharedLowerLimit;
            _globalVariables->testProcessPause.deformSharedUpperLimit = _globalVariables->deformSharedUpperLimit;
            switch (_globalVariables->Mode)
            {
            case DAC_STATE_DISP_CONST:
              _globalVariables->testProcessPause.constMode = new CONSTDisplacementModeParams();
              *((ConstDisplacementModeParams_t*)_globalVariables->testProcessPause.constMode) = _globalVariables->ConstDisplacementModeParams;
              this->stopPiston();
              break;
            case DAC_STATE_STRAIN_CONST:
              _globalVariables->testProcessPause.constMode = new CONSTStrainModeParams();
              *((ConstStrainModeParams_t*)_globalVariables->testProcessPause.constMode) = _globalVariables->ConstStrainModeParams;
              this->stopPistonAtStrain();
              break;
            case DAC_STATE_DEFORMATION_CONST:
              _globalVariables->testProcessPause.constMode = new CONSTDeformationModeParams();
              *((ConstDeformationModeParams_t*)_globalVariables->testProcessPause.constMode) = _globalVariables->ConstDeformationModeParams;
              this->stopPistonAtDeformation();
              break;
            case DAC_STATE_DISP_SIN:
              _globalVariables->testProcessPause.sinMode = new SINDisplacementMode();
              *((SINDisplacementModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SINDisplacementModeParams;
              this->stopPiston();
              break;
            case DAC_STATE_DISP_SINUS_BASED:
              _globalVariables->testProcessPause.sinMode = new SINBasedDisplacementMode();
              *((SinusBasedDisplacementModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SinusBasedDisplacementModeParams;
              this->stopPiston();
              break;
            case DAC_STATE_STRAIN_SIN:
              _globalVariables->testProcessPause.sinMode = new SINStrainMode();
              *((SINStrainModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SINStrainModeParams;
              this->stopPistonAtStrain();
              break;
             case DAC_STATE_STRAIN_SINUS_BASED:
              _globalVariables->testProcessPause.sinMode = new SINBasedStrainMode();
              *((SinusBasedStrainModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SinusBasedStrainModeParams;
              this->stopPistonAtStrain();
              break;
            case DAC_STATE_DEFORMATION_SIN:
              _globalVariables->testProcessPause.sinMode = new SINDeformationMode();
              *((SINDeformationModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SINDeformationModeParams;
              this->stopPistonAtDeformation();
              break;
            case DAC_STATE_DEFORMATION_SINUS_BASED:
              _globalVariables->testProcessPause.sinMode = new SINBasedDeformationMode();
              *((SinusBasedDeformationModeParams_t*)_globalVariables->testProcessPause.sinMode) = _globalVariables->SinusBasedDeformationModeParams;
              this->stopPistonAtDeformation();
              break;
            default:
              break;
            }
          }else{
            //nothing to do
          }
        }else{
          if(_globalVariables->testProcessPause.status == TEST_PROCESS_PAUSE){
            //task to continue
            _globalVariables->displSharedLowerLimit = _globalVariables->testProcessPause.displSharedLowerLimit;
            _globalVariables->displSharedUpperLimit = _globalVariables->testProcessPause.displSharedUpperLimit;
            _globalVariables->strainSharedLowerLimit = _globalVariables->testProcessPause.strainSharedLowerLimit;
            _globalVariables->strainSharedUpperLimit = _globalVariables->testProcessPause.strainSharedUpperLimit;
            _globalVariables->deformSharedLowerLimit = _globalVariables->testProcessPause.deformSharedLowerLimit;
            _globalVariables->deformSharedUpperLimit = _globalVariables->testProcessPause.deformSharedUpperLimit;
            switch (_globalVariables->testProcessPause.modeBeforePause)
            {
              case DAC_STATE_DISP_CONST:
                _globalVariables->ConstDisplacementModeParams = *((ConstDisplacementModeParams_t*)_globalVariables->testProcessPause.constMode);
                _globalVariables->ConstDisplacementModeParams.speedEnable = false;
                _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
                _globalVariables->ConstDisplacementModeParams.waitForPIDReset = true;
                delete _globalVariables->testProcessPause.constMode;
                break;
              case DAC_STATE_STRAIN_CONST:
                _globalVariables->ConstStrainModeParams = *((ConstStrainModeParams_t*)_globalVariables->testProcessPause.constMode);
                _globalVariables->ConstStrainModeParams.speedEnable = false;
                _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
                delete _globalVariables->testProcessPause.constMode;
                break;
              case DAC_STATE_DEFORMATION_CONST:
                _globalVariables->ConstDeformationModeParams = *((ConstDeformationModeParams_t*)_globalVariables->testProcessPause.constMode);
                _globalVariables->ConstDeformationModeParams.speedEnable = false;
                _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
                delete _globalVariables->testProcessPause.constMode;
                break;
              case DAC_STATE_DISP_SIN:
                _globalVariables->SINDisplacementModeParams = *((SINDisplacementModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              case DAC_STATE_DISP_SINUS_BASED:
                _globalVariables->SinusBasedDisplacementModeParams = *((SinusBasedDisplacementModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              case DAC_STATE_STRAIN_SIN:
                _globalVariables->SINStrainModeParams = *((SINStrainModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              case DAC_STATE_STRAIN_SINUS_BASED:
                _globalVariables->SinusBasedStrainModeParams = *((SinusBasedStrainModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              case DAC_STATE_DEFORMATION_SIN:
                _globalVariables->SINDeformationModeParams = *((SINDeformationModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              case DAC_STATE_DEFORMATION_SINUS_BASED:
                _globalVariables->SinusBasedDeformationModeParams = *((SinusBasedDeformationModeParams_t*)_globalVariables->testProcessPause.sinMode);
                _globalVariables->SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_GENERATE;
                delete _globalVariables->testProcessPause.sinMode;
                break;
              default:
                break;
            }
            _globalVariables->Mode = _globalVariables->testProcessPause.modeBeforePause;
            _globalVariables->testProcessPause.status = TEST_PROCESS_CONTINUE;
            _globalVariables->testProcessPause.modeBeforePause = DAC_STATE_UNDEFINED;
          }else{
            //nothing to do
          }
        }
        break;
      }
      //UNUSED
      case COMMAND::SET_DIRECTION_INDEPEND:
        /*if (writeValue(data, dataLength, *_currentDirection, "Current Direction:")){
          //send message to Direction thread
          //DirectionDOMail_t *DirectionMail = DirectionMailBox.alloc();
          //DirectionMail->direction = CurrentDirection;
          //DirectionMail->counter = 0; 
          //DirectionMailBox.put(DirectionMail);
        }*/
        break;
      case COMMAND::SET_REFERENCE_VOLTAGE:{
        task = Task::SET_REFERENCE_VOLTAGE;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_EXTENS_REFERENCE_VOLTAGE:{
        task = Task::SET_EXTENS_REF_VOLTAGE;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_DISPL_REFERENCE_VOLTAGE:{
        task = Task::SET_DISPL_REF_VOLTAGE;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_DISPL_ENCODER_STEP_VALUE:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        _globalVariables->encoderStepValue = value;
        displEncoder.setStepValue(value);
        break;
      }
      case COMMAND::SET_DEFORM_ENCODER_STEP_VALUE:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        _globalVariables->encoderExtensiaStepValue = value;
        #if(PROJECT_NAME == PROJECT_NAME_MPD)
        deformEncoder.setStepValue(value);
        deformEncoder2.setStepValue(value);
        #else
        deformEncoder.setStepValue(value);
        #endif
        break;
      }
      case COMMAND::SET_DISPL_ENCODER_STEP_VALUE_THRESHOLD:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        _globalVariables->StepValueThreshold = value;
        break;
	    }
      case COMMAND::SET_DISPL_ENCODER_NULL_OFFSET:{
        _globalVariables->Mode = DAC_STATE_NONE;
        displEncoder.HardSetLastPulsesCount();
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        _globalVariables->ConstDisplacementModeParams.PositionToHold = 0;
        if(_globalVariables->LimitSwitchState == LIMIT_SWITCH_STATE_ONE || _globalVariables->LimitSwitchState == LIMIT_SWITCH_STATE_TWO)
          _globalVariables->MaxPosition = 0;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_DISPL_ENCODER_PULSES_OFFSET:{
        _globalVariables->Mode = DAC_STATE_NONE;
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        double doubleValue;
        int intValue = 0;
        basic.writeBytesBufferToValue(data, &doubleValue);
        intValue = static_cast<int>(doubleValue / _globalVariables->encoderStepValue);
        displEncoder.setPulesCount(intValue * _globalVariables->positionInvertAxis);
        break;
      }
      //switch strain amp
      // case COMMAND::SET_STRAIN_AMP:{
      //   writeValue(data, dataLength, _globalVariables->StrainAmpCoef);
      //   strainAmp.write(_globalVariables->StrainAmpCoef);
      // }
      //switch strain units
      //   break;
      case COMMAND::SWITCH_STRAIN_SENSOR_UNITS:{
        writeValue(data, dataLength, _globalVariables->StrainUnits);
        break;
      }
      //switch diagnostics units
      case COMMAND::TM_DIAGNOSTICS_VALUES:{
        writeValue(data, dataLength, _globalVariables->TestDataUnits);
        break;
      }
      //switch deformation units
      case COMMAND::SWITCH_DEFORMATION_SENSOR_UNITS:{
        writeValue(data, dataLength, _globalVariables->DeformationUnits);
        break;
      }
      //switch position units
      case COMMAND::SWITCH_POSITION_SENSOR_UNITS:{
        writeValue(data, dataLength, _globalVariables->PositionUnits);
        break;
      }
      //CONST MODE
      case COMMAND::SET_CONST_VOLTAGE:
        writeValue(data, dataLength, _globalVariables->ConstModeParams.Voltage);
        break;
      case COMMAND::SET_CONST_DIRECTION:
        writeValue(data, dataLength, _globalVariables->ConstModeParams.Direction);
        break;
      case COMMAND::SET_CONST_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->ConstModeParams.ConstFrequency);
        break;
      case COMMAND::SET_CONST_PID_KP:
        // writeValue(data, dataLength, _globalVariables->ConstModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_CONST_PID_KI:
        // writeValue(data, dataLength, _globalVariables->ConstModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_CONST_PID_KD:
        // writeValue(data, dataLength, _globalVariables->ConstModeParams.PIDParams.Kd);
        break;

      //PULSE MODE
      case COMMAND::SET_PULSE_AMPLITUDE:
        //DEPRECATED
        //writeValue(data, dataLength, _globalVariables->PulseModeParams.Amplitude);
        break;
      case COMMAND::SET_PULSE_FREQUENCY:
        //DEPRECATED
        //writeValue(data, dataLength, _globalVariables->PulseModeParams.PulseFrequency);
        break;
      case COMMAND::SET_PULSE_PID_KP:
        //DEPRECATED
        //writeValue(data, dataLength, _globalVariables->PulseModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_PULSE_PID_KI:
        //DEPRECATED
        //writeValue(data, dataLength, _globalVariables->PulseModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_PULSE_PID_KD:
        //DEPRECATED
        //writeValue(data, dataLength, _globalVariables->PulseModeParams.PIDParams.Kd);
        break;

      //EMERGENCY STOP
      case COMMAND::EMERGENCY_STOP:
        //HwCmd5.write(0);
        //HwCmd6.write(0);
        #if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED)||(CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN))
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        _globalVariables->ConstDisplacementModeParams.Speed = 0.0;
        _globalVariables->ConstDisplacementModeParams.PositionToHold = _globalVariables->roCurrentAvPosition;
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DISP_CONST;
        #else
        if(_globalVariables->machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
          _globalVariables->Mode = DAC_STATE_NONE;
          _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        }
        if(_globalVariables->machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
          _globalVariables->Mode = DAC_STATE_CLOSE_VALVE;
          _globalVariables->closeValveState = CLOSE_VALVE_STATE_RESET;   
        }
        #endif
        _globalVariables->stopCurrentTestProcess = true;
        if(_globalVariables->InternalTask == INTERNAL_TASK_STATIC_TEST){
          _globalVariables->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
        }
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        //disable pump and high pressure
        //HwCmd4.write(0);
        //resetEmergencyButtonTimeout.attach(callback(this, &EthernetParser::resetEmergencyButton), 10000ms);
        break;
      case COMMAND::STOP_CURRENT_TEST_PROCESS:
        _globalVariables->stopCurrentTestProcess = true;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      
      case COMMAND::SET_MIDDLE_PISTON_POSITION:{
        //printf("Get middle position command.Good job!\n\r");
        if(!std::isnan(_globalVariables->middlePistonPosition)){
          _globalVariables->ConstDisplacementModeParams.speedEnable = false;
          
          if(!std::isnan(_globalVariables->SSINullOffset)){
              _globalVariables->ConstDisplacementModeParams.PositionToHold = _globalVariables->middlePistonPosition 
                                                                            - _globalVariables->positionNullOffset
                                                                            - _globalVariables->SSINullOffset
                                                                            + _globalVariables->SSIPositionOffset;
              //position = positionWoNO + GV.SSIPositionOffset - GV.positionNullOffset - GV.SSINullOffset;
              //printf("set middle position with SSI null offset: %.3f\n\r", _globalVariables->ConstDisplacementModeParams.PositionToHold);
          }else{
              _globalVariables->ConstDisplacementModeParams.PositionToHold = _globalVariables->middlePistonPosition - _globalVariables->positionNullOffset;
              //position = positionWoNO - GV.positionNullOffset;
              //printf("set middle position: %.3f\n\r", _globalVariables->ConstDisplacementModeParams.PositionToHold);
          }
          _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
          _globalVariables->ConstDisplacementModeParams.waitForPIDReset = true;
          _globalVariables->Mode = DAC_STATE_DISP_CONST;
        }else{
          //printf("set middle position failed (middle pos isNAN)\n\r");
        }
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::INCREMENT_STEP_ID:
        _globalVariables->stepID++;
        break;
      case COMMAND::STOP_PISTON_WO_INC_STEP_ID:
        this->stopPiston();
        _globalVariables->testProcessPause.resetState();
        break;
      case COMMAND::STOP_PISTON:
        this->stopPiston();
        //TODO:: check behavior
        _globalVariables->testProcessPause.resetState();
        //END TODO
        _globalVariables->stepID++;
		this->positionToHoldTimeout->detach();
        break; 
      case COMMAND::ADC_CALIBRATION:
        task = Task::ADC_CALIBRATION;
        this->addTask(task);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      case COMMAND::ADC_CALIBRATION_RESET:
        _globalVariables->ConstStrainModeParams.StrainToHold += _globalVariables->ADCNullOffset;
        _globalVariables->ADCNullOffset = 0;
        _globalVariables->testProcessPause.resetState();
        break;
      case COMMAND::POSITION_CALIBRATION:
        task = Task::POSITION_CALIBRATION;
        this->addTask(task);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      case COMMAND::POSITION_CALIBRATION_RESET:
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        _globalVariables->Mode = DAC_STATE_NONE;
        #endif
        _globalVariables->ConstDisplacementModeParams.PositionToHold += _globalVariables->positionNullOffset;
        _globalVariables->positionNullOffset = 0;
        _globalVariables->testProcessPause.resetState();
        break;
      case COMMAND::DEFORMATION_CALIBRATION:
        task = Task::DEFORMATION_CALIBRATION;
        this->addTask(task);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      case COMMAND::ENCODER_AND_MOTOR_CALIBRATION:{
        uint32_t _dataLength = 4;
        writeValue(data     , _dataLength, _globalVariables->stepsForCalibration);
        writeValue(data +  4, _dataLength, _globalVariables->directionForCalibration);
        task = Task::ENCODER_AND_MOTOR_CALIBRATION;
        this->addTask(task);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_STEPS:{
        task = Task::SET_STEPS;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::CLOSE_VALVE:{
        // uint32_t _dataLength;
        // stepsParams a;
        // a.stepsCountPerCycle = 10;
        // a.cycleDuration = 5;
        // int newPosition;
        // newPosition = (GV.currentPosition - GV.middlePosition) * GV.valveDirectionMode;
        // if(newPosition > 0){
        //   a.direction = 1;
        // }
        // if(newPosition < 0){
        //   a.direction = 0;
        // }
        // a.steps = abs(newPosition);
        // char b[32];
        // _dataLength  = basic.writeValueToBytesBuffer(b, a.steps);
        // _dataLength += basic.writeValueToBytesBuffer(b + 4, a.direction);
        // _dataLength += basic.writeValueToBytesBuffer(b + 8, a.stepsCountPerCycle);
        // _dataLength += basic.writeValueToBytesBuffer(b + 12, a.cycleDuration);
        // task = Task::SET_STEPS;
        // this->addTask(task, b, _dataLength);
        GV.Mode = DAC_STATE_CLOSE_VALVE;
        GV.closeValveState = CLOSE_VALVE_STATE_RESET;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::RESET_VALVE_POSITION:
        *BV.valvePosition = 0;
        break;
      case COMMAND::SET_POSITION_SPEED_CALIBRATION:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(speedCalibration.getMaxPoints() >= pointsLength && pointsLength != 1){
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 5 * i * doubleLength,                    doubleLength, params[i].speed);
            writeValue(data + uint32Length + 5 * i * doubleLength +     doubleLength, doubleLength, params[i].Kp);
            writeValue(data + uint32Length + 5 * i * doubleLength + 2 * doubleLength, doubleLength, params[i].Ki);
            writeValue(data + uint32Length + 5 * i * doubleLength + 3 * doubleLength, doubleLength, params[i].Kd);
            writeValue(data + uint32Length + 5 * i * doubleLength + 4 * doubleLength, doubleLength, params[i].maxDeviation);
          }
          speedCalibration.setPoints(params, pointsLength);
          delete[] params;
        }
        break;
      }
      case COMMAND::GET_POSITION_SPEED_CALIBRATION:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        if(speedCalibration.getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          if(speedCalibration.getPoints(params, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, params[i].speed, uint32Length + 5 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Kp, uint32Length + 5 * i * doubleLength + doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Ki, uint32Length + 5 * i * doubleLength + 2 * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Kd, uint32Length + 5 * i * doubleLength + 3 * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].maxDeviation, uint32Length + 5 * i * doubleLength + 4 * doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] params;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        break;
      }
      case COMMAND::SET_TO_FLASH_POSITION_SPEED_CALIBRATION:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(speedCalibration.getMaxPoints() >= pointsLength && pointsLength != 1){
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 5 * i * doubleLength,                    doubleLength, params[i].speed);
            writeValue(data + uint32Length + 5 * i * doubleLength +     doubleLength, doubleLength, params[i].Kp);
            writeValue(data + uint32Length + 5 * i * doubleLength + 2 * doubleLength, doubleLength, params[i].Ki);
            writeValue(data + uint32Length + 5 * i * doubleLength + 3 * doubleLength, doubleLength, params[i].Kd);
            writeValue(data + uint32Length + 5 * i * doubleLength + 4 * doubleLength, doubleLength, params[i].maxDeviation);
          }
          speedCalibration.setPointsToFlash(params, pointsLength);
          delete[] params;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_POSITION_SPEED_CALIBRATION:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        speedCalibration.getPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          speedCalibration.getPointsFromFlash(params, dummy);
          for (int i = 0; i < dummy; i++){
            _datalength += basic.writeValueToBytesBuffer(data, params[i].speed, uint32Length + 5 * i * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Kp, uint32Length + 5 * i * doubleLength + doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Ki, uint32Length + 5 * i * doubleLength + 2 * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Kd, uint32Length + 5 * i * doubleLength + 3 * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].maxDeviation, uint32Length + 5 * i * doubleLength + 4 * doubleLength);
          }
          dataLength = _datalength; 
          delete[] params;
        }else{
          dataLength = 0;
        }
        break;        
      }
      case COMMAND::GET_DOORS_SWITCH_STATUS:{
        #if ((LIMIT_SWITCH_DOORS_TYPE == LIMIT_SWITCH_DOORS_TYPE_TWO) && !(LIMIT_SWITCH_POWER == LIMIT_SWITCH_POWER_24V))
        int leftDoorSwitchStatus = leftDoorSwitch.read();
        int rightDoorSwitchStatus = rightDoorSwitch.read();
        #else
        int leftDoorSwitchStatus = 0;
        int rightDoorSwitchStatus = 0;
        #endif
        dataLength =  basic.writeValueToBytesBuffer(data    , leftDoorSwitchStatus);
        dataLength += basic.writeValueToBytesBuffer(data + 4, rightDoorSwitchStatus);
        break;
      }
      case COMMAND::SET_CALCULATION_PROCESS:{
        uint32_t _dataLength = sizeof(uint8_t);
        uint8_t dummy = 0;
        writeValue(data, _dataLength, dummy);
        speedCalibration.setCalculatingProcess(dummy);
        break;
      }
      case COMMAND::GET_CALCULATION_PROCESS:{
        dataLength =  basic.writeValueToBytesBuffer(data, speedCalibration.getCalculatingProcess());
        break;
      }
      case COMMAND::SET_STRAIN_SPEED_CALIBRATION:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(strainSpeedCalibration.getMaxPoints() >= pointsLength && pointsLength != 1){
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 5 * i * doubleLength,                    doubleLength, params[i].speed);
            writeValue(data + uint32Length + 5 * i * doubleLength +     doubleLength, doubleLength, params[i].Kp);
            writeValue(data + uint32Length + 5 * i * doubleLength + 2 * doubleLength, doubleLength, params[i].Ki);
            writeValue(data + uint32Length + 5 * i * doubleLength + 3 * doubleLength, doubleLength, params[i].Kd);
            writeValue(data + uint32Length + 5 * i * doubleLength + 4 * doubleLength, doubleLength, params[i].maxDeviation);
          }
          strainSpeedCalibration.setPoints(params, pointsLength);
          delete[] params;
        }
        break;
      }
      case COMMAND::GET_STRAIN_SPEED_CALIBRATION:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        if(strainSpeedCalibration.getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          if(strainSpeedCalibration.getPoints(params, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, params[i].speed, uint32Length + 5 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Kp, uint32Length + 5 * i * doubleLength + doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Ki, uint32Length + 5 * i * doubleLength + 2 * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].Kd, uint32Length + 5 * i * doubleLength + 3 * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, params[i].maxDeviation, uint32Length + 5 * i * doubleLength + 4 * doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] params;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        break;
      }
      case COMMAND::SET_TO_FLASH_STRAIN_SPEED_CALIBRATION:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(strainSpeedCalibration.getMaxPoints() >= pointsLength && pointsLength != 1){
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 5 * i * doubleLength,                    doubleLength, params[i].speed);
            writeValue(data + uint32Length + 5 * i * doubleLength +     doubleLength, doubleLength, params[i].Kp);
            writeValue(data + uint32Length + 5 * i * doubleLength + 2 * doubleLength, doubleLength, params[i].Ki);
            writeValue(data + uint32Length + 5 * i * doubleLength + 3 * doubleLength, doubleLength, params[i].Kd);
            writeValue(data + uint32Length + 5 * i * doubleLength + 4 * doubleLength, doubleLength, params[i].maxDeviation);
          }
          strainSpeedCalibration.setStrainPointsToFlash(params, pointsLength);
          delete[] params;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_STRAIN_SPEED_CALIBRATION:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof(uint32_t);
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        strainSpeedCalibration.getStrainPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          speedCalibrationParams_t *params = new speedCalibrationParams_t[pointsLength];
          strainSpeedCalibration.getStrainPointsFromFlash(params, dummy);
          for (int i = 0; i < dummy; i++){
            _datalength += basic.writeValueToBytesBuffer(data, params[i].speed, uint32Length + 5 * i * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Kp, uint32Length + 5 * i * doubleLength + doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Ki, uint32Length + 5 * i * doubleLength + 2 * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].Kd, uint32Length + 5 * i * doubleLength + 3 * doubleLength);
            _datalength += basic.writeValueToBytesBuffer(data, params[i].maxDeviation, uint32Length + 5 * i * doubleLength + 4 * doubleLength);
          }
          dataLength = _datalength; 
          delete[] params;
        }else{
          dataLength = 0;
        }
        break;        
      }
      case COMMAND::SET_STRAIN_CALCULATION_PROCESS:{
        uint32_t _dataLength = sizeof(uint8_t);
        uint8_t dummy = 0;
        writeValue(data, _dataLength, dummy);
        strainSpeedCalibration.setCalculatingProcess(dummy);
        break;
      }
      case COMMAND::GET_STRAIN_CALCULATION_PROCESS:{
        dataLength =  basic.writeValueToBytesBuffer(data, strainSpeedCalibration.getCalculatingProcess());
        break;
      }
      case COMMAND::SWITCH_VALVE_UNITS:{
        writeValue(data, dataLength, _globalVariables->valveUnits);
        break;
      }
      case COMMAND::SET_STRAIN_NULL_OFFSET:{
        writeValue(data, dataLength, *BV.strainNullOffset);
        break;
      }
      case COMMAND::GET_STRAIN_NULL_OFFSET:{
        dataLength =  basic.writeValueToBytesBuffer(data, *BV.strainNullOffset);
        break;
      }
      case COMMAND::STOP_CALIBRATION:
        writeValue(data, dataLength, _globalVariables->stopCalibration);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      case COMMAND::GET_VALUES_AFTER_CALIBRATION:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->encoderStepValue);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->motorStepValue);
        break;
      }
      case COMMAND::DEFORMATION_CALIBRATION_RESET:
        _globalVariables->ConstDeformationModeParams.DeformationToHold += _globalVariables->deformationNullOffset;
        _globalVariables->deformationNullOffset = 0;
        break;
      case COMMAND::STOP_ACQ_DISPLACEMENT:
        //printf("\n\rSTOP ACQ DISP\n\r");
        _globalVariables->EnabledAcq &= ~ACQ_DISPLACEMENT;
        break;
      case COMMAND::START_ACQ_DISPLACEMENT:
        //printf("\n\rSTART ACQ DISP\n\r");
        _globalVariables->EnabledAcq |= ACQ_DISPLACEMENT;
        break;
      case COMMAND::STOP_ACQ_STRAIN:
        //printf("\n\rSTOP ACQ STRAIN\n\r");
        _globalVariables->EnabledAcq &= ~ACQ_STRAIN;
        break;
      case COMMAND::START_ACQ_STRAIN:
        //printf("\n\rSTART ACQ STRAIN\n\r");
        _globalVariables->EnabledAcq |= ACQ_STRAIN;
        break;
      case COMMAND::DISABLE_ACQ_DISPLACEMENT_AVERAGE:
        //printf("\n\rSTOP AVERAGE ACQ DISP\n\r");
        _globalVariables->AverageAcq &= ~ACQ_DISPLACEMENT;
        break;
      case COMMAND::ENABLE_ACQ_DISPLACEMENT_AVERAGE:
        //printf("\n\rSTART AVERAGE ACQ DISP\n\r");
        _globalVariables->AverageAcq |= ACQ_DISPLACEMENT;
        break;
      case COMMAND::DISABLE_ACQ_STRAIN_AVERAGE:
        //printf("\n\rSTOP AVERAGE ACQ STRAIN\n\r");
        _globalVariables->AverageAcq &= ~ACQ_STRAIN;
        break;
      case COMMAND::ENABLE_ACQ_STRAIN_AVERAGE:
        //printf("\n\rSTART AVERAGE ACQ STRAIN\n\r");
        _globalVariables->AverageAcq |= ACQ_STRAIN;
        break;
      case COMMAND::STOP_ACQ_SENSORS_TM:
        //printf("\n\rSTOP ACQ SENSORS\n\r");
        _globalVariables->EnabledAcq &= ~ACQ_SENSORS_TM;
        break;
      case COMMAND::START_ACQ_SENSORS_TM:
        //printf("\n\rSTART ACQ SENSORS\n\r");
        _globalVariables->EnabledAcq |= ACQ_SENSORS_TM;
        break;
      case COMMAND::DISABLE_WAIT_DISPLACEMENT_SENSOR_RESULT:
        //printf("\n\rSTOP ACQ SENSORS\n\r");
        _globalVariables->WaitAcqComplete &= ~WAIT_ACQ_COMPLETE_DISPLACEMENT;
        break;
      case COMMAND::ENABLE_WAIT_DISPLACEMENT_SENSOR_RESULT:
        //printf("\n\rSTART ACQ SENSORS\n\r");
        _globalVariables->WaitAcqComplete |= WAIT_ACQ_COMPLETE_DISPLACEMENT;
        break;
      case COMMAND::DISABLE_WAIT_STRAIN_SENSOR_RESULT:
        //printf("\n\rSTOP ACQ SENSORS\n\r");
        _globalVariables->WaitAcqComplete &= ~WAIT_ACQ_COMPLETE_STRAIN;
        break;
      case COMMAND::ENABLE_WAIT_STRAIN_SENSOR_RESULT:
        //printf("\n\rSTART ACQ SENSORS\n\r");
        _globalVariables->WaitAcqComplete |= WAIT_ACQ_COMPLETE_STRAIN;
        break;
      

      //TEST DISPLACEMENT SIGNAL
      case COMMAND::SET_TEST_SIN_SIGNAL:
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.type);
        //_globalVariables->TestSinSignal = int32Value2;
        break;
      case COMMAND::SET_TEST_SIN_SIGNAL_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.sinSignalAmplitude);
        break;
      case COMMAND::SET_TEST_SIN_SIGNAL_INCREMENT:
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.sinSignalIncrement);
        break;
      case COMMAND::SET_TEST_SIGNAL_STRAIN_VALUE:{
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.constSignalStrain);
        break;
      }
      case COMMAND::SET_TEST_SIGNAL_POSITION_VALUE:{
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.constSignalPosition);
        break;
      }
      case COMMAND::SET_TEST_SIGNAL_DEFORMATION_VALUE:{
        writeValue(data, dataLength, _globalVariables->TestSignalInfo.constSignalDeformation);
        break;
      }

      //CONST DISPLACEMENT MODE
      case COMMAND::SET_CONST_DISP_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.MaxDeviation);
        break;
      case COMMAND::SET_CONST_DISP_MODE_FREQUENCY:{
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.ModeFrequency);
        break;
      }
      case COMMAND::SET_CONST_DISP_PID_KP:
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_CONST_DISP_PID_KI:
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_CONST_DISP_PID_KD:
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Kd);
        break;
      case COMMAND::SET_CONST_DISP_POSITION_TO_HOLD:{
        _globalVariables->displSharedLowerLimit = NAN;
        _globalVariables->displSharedUpperLimit = NAN;
        _globalVariables->strainSharedLowerLimit = NAN;
        _globalVariables->strainSharedUpperLimit = NAN;
        _globalVariables->deformSharedLowerLimit = NAN;
        _globalVariables->deformSharedUpperLimit = NAN;
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        break;
      }
      case COMMAND::SET_CONST_DISP_POSITION_TO_HOLD_WITH_ADD_RANGE:{
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        writeValue(data +  8, _dataLength, _globalVariables->strainSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->strainSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->deformSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->deformSharedUpperLimit);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvStrain > _globalVariables->strainSharedUpperLimit)
          _globalVariables->isBeginStrainHiger = true;
        else if (_globalVariables->roCurrentAvStrain < _globalVariables->strainSharedLowerLimit)
          _globalVariables->isBeginStrainHiger = false;
        if (_globalVariables->roCurrentAvDeformation > _globalVariables->deformSharedUpperLimit)
          _globalVariables->isBeginDeformationHiger = true;
        else if (_globalVariables->roCurrentAvDeformation < _globalVariables->deformSharedLowerLimit)
          _globalVariables->isBeginDeformationHiger = false;
        _globalVariables->Mode = DAC_STATE_DISP_CONST;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_CONST_DISP_POSITION_TO_HOLD_WITH__6__RANGE:{
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        writeValue(data +  8, _dataLength, _globalVariables->displSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->displSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->strainSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->strainSharedUpperLimit);
        writeValue(data +  40, _dataLength, _globalVariables->deformSharedLowerLimit);
        writeValue(data +  48, _dataLength, _globalVariables->deformSharedUpperLimit);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvPosition > _globalVariables->displSharedUpperLimit)
          _globalVariables->isBeginDisplacementHiger = true;
        else if (_globalVariables->roCurrentAvPosition < _globalVariables->displSharedLowerLimit)
          _globalVariables->isBeginDisplacementHiger = false;
        if (_globalVariables->roCurrentAvStrain > _globalVariables->strainSharedUpperLimit)
          _globalVariables->isBeginStrainHiger = true;
        else if (_globalVariables->roCurrentAvStrain < _globalVariables->strainSharedLowerLimit)
          _globalVariables->isBeginStrainHiger = false;
        if (_globalVariables->roCurrentAvDeformation > _globalVariables->deformSharedUpperLimit)
          _globalVariables->isBeginDeformationHiger = true;
        else if (_globalVariables->roCurrentAvDeformation < _globalVariables->deformSharedLowerLimit)
          _globalVariables->isBeginDeformationHiger = false;
        _globalVariables->Mode = DAC_STATE_DISP_CONST;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }

      case COMMAND::SET_CONST_DISP_SET_SPEED:
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.Speed);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        break;

      //SINUS DISPLACEMENT MODE
      case COMMAND::SET_SIN_DISP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_DISP_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SIN_DISP_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_DISP_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDisplacementModeParams.SINFrequency;
        break;
      case COMMAND::SET_SIN_DISP_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SIN_DISP_PID_KP:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SIN_DISP_PID_KI:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SIN_DISP_PID_KD:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SIN_DISP_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SIN_DISP_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SINDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDisplacementModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_DATA_DECIMATION_COEFF:{
        writeValue(data, dataLength, _globalVariables->DataDecimationCoeff);
        EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
        if(EthernetAnswerMail != nullptr){
          EthernetAnswerMail->command = COMMAND::TM_ONCE_DATA_DECIMATION_COEF_SET_COMPLETE;
          EthernetAnswerMail->dataLength = 4;
          //error status 0
          basic.writeValueToBytesBuffer(EthernetAnswerMail->data, 0x0);
          EthernetAnswerMailBox.put(EthernetAnswerMail);
        }
        break;
      }
      case COMMAND::SET_SIN_DISP_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.MaxDeviation);
        break;
      case COMMAND::SET_SIN_DEFORM_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.MaxDeviation);
        break;    
      case COMMAND::SET_AVERAGE_POSITION_BUFFER_SIZE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        _globalVariables->AveragePosition.setNumberOfValues(value);
        break;
      }
      case COMMAND::SET_AVERAGE_STRAIN_BUFFER_SIZE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        _globalVariables->AverageStrain.setNumberOfValues(value);
        break;
      }
      //PROTECTION CMDs
      case COMMAND::SET_PROTECTION_DISPLACEMENT_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtect.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DISPLACEMENT_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtect.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DISPLACEMENT_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtect.setValuesCount(8);
        break;
      }
      case COMMAND::SET_PROTECTION_DISPLACEMENT_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtect.setMode(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DISPLACEMENT_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtectStage2.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DISPLACEMENT_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtectStage2.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DISPLACEMENT_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtectStage2.setValuesCount(8);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DISPLACEMENT_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        displacementProtectStage2.setMode(value);
        break;
      }
      case COMMAND::SET_PROTECTION_STRAIN_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtect.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_STRAIN_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtect.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_STRAIN_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtect.setValuesCount(8);
        break;
      }
      case COMMAND::SET_PROTECTION_STRAIN_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtect.setMode(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_STRAIN_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtectStage2.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_STRAIN_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtectStage2.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_STRAIN_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtectStage2.setValuesCount(8);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_STRAIN_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        strainProtectStage2.setMode(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DEFORMATION_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtect.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DEFORMATION_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtect.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DEFORMATION_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtect.setValuesCount(8);
        break;
      }
      case COMMAND::SET_PROTECTION_DEFORMATION_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtect.setMode(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DEFORMATION_UPPER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtectStage2.setUpperLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DEFORMATION_LOWER_LIMIT:{
        double value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtectStage2.setLowerLimit(value);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DEFORMATION_VALUES_COUNT:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtectStage2.setValuesCount(8);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DEFORMATION_MODE:{
        uint32_t value;
        basic.writeBytesBufferToValue(data, &value);
        deformationProtectStage2.setMode(value);
        break;
      }
      case COMMAND::SET_PROTECTION_DISPLACEMENT_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        displacementProtect.setLimits(upperLimit, lowerLimit);
        displacementProtect.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_PROTECTION_STRAIN_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        strainProtect.setLimits(upperLimit, lowerLimit);
        strainProtect.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_CYCLIC_STRAIN_PROTECTION_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, GV.blindePartOfCyclicStrainProtection);
        GV.blindePartOfCyclicStrainProtectionFirst = GV.blindePartOfCyclicStrainProtection;
        writeValue(data +  8, _dataLength, GV.deltaCyclicProtection);
        _dataLength = 4;
        writeValue(data +  16, _dataLength, GV.cyclicProtectMode);
        GV.isSimpleCyclicProtection = false;
        break;
      }
      case COMMAND::SET_CYCLIC_STRAIN_PROTECTION_PARAMS_ADVANCED:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, GV.blindePartOfCyclicStrainProtection);
        writeValue(data +  8, _dataLength, GV.deltaCyclicProtection);
        writeValue(data + 16, _dataLength, GV.blindePartOfCyclicStrainProtectionFirst);
        writeValue(data + 24, _dataLength, GV.multiplier);
        _dataLength = 4;
        writeValue(data +  32, _dataLength, GV.cyclicProtectMode);
        GV.isSimpleCyclicProtection = false;
        break;
      } 
      case COMMAND::SET_CYCLIC_PROTECTION_MODE:{
        basic.writeBytesBufferToValue(data, &GV.cyclicProtectMode);
        GV.isSimpleCyclicProtection = false;
        break;
      }
      case COMMAND::SET_CYCLIC_PROTECTION_MODE_MEMORY_PARAMS:{
        basic.writeBytesBufferToValue(data, &GV.cyclicProtectMode);
        GV.isSimpleCyclicProtection = true;
        break;
      }
      case COMMAND::SET_PROTECTION_DEFORMATION_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        deformationProtect.setLimits(upperLimit, lowerLimit);
        deformationProtect.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_PROTECTION_MODES:{
        uint32_t _dataLength = 4;
        uint32_t displacementMode;
        uint32_t strainMode;
        uint32_t deformationMode;
        writeValue(data    , _dataLength, displacementMode);
        writeValue(data + 4, _dataLength, strainMode);
        writeValue(data + 8, _dataLength, deformationMode);
        displacementProtect.setMode(displacementMode);
        strainProtect.setMode(strainMode);
        deformationProtect.setMode(deformationMode);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DISPLACEMENT_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        displacementProtectStage2.setLimits(upperLimit, lowerLimit);
        displacementProtectStage2.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_STRAIN_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        strainProtectStage2.setLimits(upperLimit, lowerLimit);
        strainProtectStage2.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_DEFORMATION_PARAMS:{
        uint32_t _dataLength = 8;
        double upperLimit;
        double lowerLimit;
        uint32_t valuesCount;
        writeValue(data     , _dataLength, upperLimit);
        writeValue(data +  8, _dataLength, lowerLimit);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, valuesCount);
        deformationProtectStage2.setLimits(upperLimit, lowerLimit);
        deformationProtectStage2.setValuesCount(valuesCount);
        break;
      }
      case COMMAND::SET_2_STAGE_PROTECTION_MODES:{
        uint32_t _dataLength = 4;
        uint32_t displacementMode;
        uint32_t strainMode;
        uint32_t deformationMode;
        writeValue(data    , _dataLength, displacementMode);
        writeValue(data + 4, _dataLength, strainMode);
        writeValue(data + 8, _dataLength, deformationMode);
        displacementProtectStage2.setMode(displacementMode);
        strainProtectStage2.setMode(strainMode);
        deformationProtectStage2.setMode(deformationMode);
        break;
      }
	  case COMMAND::GET_PROTECTION_DISPLACEMENT_UPPER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, displacementProtect.getUpperLimit());
		break;
	  case COMMAND::GET_PROTECTION_DISPLACEMENT_LOWER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, displacementProtect.getLowerLimit());
		break;
      case COMMAND::GET_PROTECTION_DISPLACEMENT_MODE:
        dataLength = basic.writeValueToBytesBuffer(data, displacementProtect.getMode());
		break;
//STRAIN PROTECTION
      case COMMAND::GET_PROTECTION_STRAIN_UPPER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, strainProtect.getUpperLimit());
		break;
	  case COMMAND::GET_PROTECTION_STRAIN_LOWER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, strainProtect.getLowerLimit());
		break;
      case COMMAND::GET_PROTECTION_STRAIN_MODE:
        dataLength = basic.writeValueToBytesBuffer(data, strainProtect.getMode());
		break;
		//DEFORMATION PROTECTION
      case COMMAND::GET_PROTECTION_DEFORMATION_UPPER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, deformationProtect.getUpperLimit());
		break;
      case COMMAND::GET_PROTECTION_DEFORMATION_LOWER_LIMIT:
        dataLength = basic.writeValueToBytesBuffer(data, deformationProtect.getLowerLimit());
		break;
      case COMMAND::GET_PROTECTION_DEFORMATION_MODE:
        dataLength = basic.writeValueToBytesBuffer(data, deformationProtect.getMode());
		break;
      //CONST STRAIN MODE
      case COMMAND::SET_CONST_STRAIN_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.MaxDeviation);
        break;
      case COMMAND::SET_CONST_STRAIN_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.ModeFrequency);
        break;
      case COMMAND::SET_CONST_STRAIN_PID_KP:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_CONST_STRAIN_PID_KI:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_CONST_STRAIN_PID_KD:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Kd);
        break;
      case COMMAND::SET_CONST_STRAIN_LOAD_TO_HOLD:{
        _globalVariables->displSharedLowerLimit = NAN;
        _globalVariables->displSharedUpperLimit = NAN;
        _globalVariables->strainSharedLowerLimit = NAN;
        _globalVariables->strainSharedUpperLimit = NAN;
        _globalVariables->deformSharedLowerLimit = NAN;
        _globalVariables->deformSharedUpperLimit = NAN;
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.StrainToHold);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        break;}

      case COMMAND::SET_CONST_STRAIN_LOAD_TO_HOLD_WITH_ADD_RANGE:{
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstStrainModeParams.StrainToHold);
        writeValue(data +  8, _dataLength, _globalVariables->displSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->displSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->deformSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->deformSharedUpperLimit);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvPosition > _globalVariables->displSharedUpperLimit)
          _globalVariables->isBeginDisplacementHiger = true;
        else if (_globalVariables->roCurrentAvPosition < _globalVariables->displSharedLowerLimit)
          _globalVariables->isBeginDisplacementHiger = false;
        if (_globalVariables->roCurrentAvDeformation > _globalVariables->deformSharedUpperLimit)
          _globalVariables->isBeginDeformationHiger = true;
        else if (_globalVariables->roCurrentAvDeformation < _globalVariables->deformSharedLowerLimit)
          _globalVariables->isBeginDeformationHiger = false;
        break;}

      case COMMAND::SET_CONST_STRAIN_LOAD_TO_HOLD_WITH__6__RANGE:{
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstStrainModeParams.StrainToHold);
        writeValue(data +  8, _dataLength, _globalVariables->displSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->displSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->strainSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->strainSharedUpperLimit);
        writeValue(data +  40, _dataLength, _globalVariables->deformSharedLowerLimit);
        writeValue(data +  48, _dataLength, _globalVariables->deformSharedUpperLimit);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvPosition > _globalVariables->displSharedUpperLimit)
          _globalVariables->isBeginDisplacementHiger = true;
        else if (_globalVariables->roCurrentAvPosition < _globalVariables->displSharedLowerLimit)
          _globalVariables->isBeginDisplacementHiger = false;
        if (_globalVariables->roCurrentAvStrain > _globalVariables->strainSharedUpperLimit)
          _globalVariables->isBeginStrainHiger = true;
        else if (_globalVariables->roCurrentAvStrain < _globalVariables->strainSharedLowerLimit)
          _globalVariables->isBeginStrainHiger = false;
        if (_globalVariables->roCurrentAvDeformation > _globalVariables->deformSharedUpperLimit)
          _globalVariables->isBeginDeformationHiger = true;
        else if (_globalVariables->roCurrentAvDeformation < _globalVariables->deformSharedLowerLimit)
          _globalVariables->isBeginDeformationHiger = false;
        break;}

      case COMMAND::SET_CONST_STRAIN_SAMPLE_CUT:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.SampleCut);
        break;
      case COMMAND::SET_CONST_STRAIN_SAMPLE_LENGTH:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.SampleLength);
        break;
      case COMMAND::SET_CONST_STRAIN_YOUNGS_MODULUS:
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.YoungModulus);
        break;
      case COMMAND::SET_CONST_STRAIN_SET_SPEED:
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstStrainModeParams.Speed);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        break;
      //sinus strain mode
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_STRAIN_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SIN_STRAIN_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_STRAIN_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINStrainModeParams.SINFrequency;
        break;
      case COMMAND::SET_SIN_STRAIN_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SIN_STRAIN_PID_KP:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SIN_STRAIN_PID_KI:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SIN_STRAIN_PID_KD:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SIN_STRAIN_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SINStrainModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SIN_STRAIN_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SINStrainModeParams.NumberOfCycles)){
          if ( _globalVariables->SINStrainModeParams.NumberOfCycles > 0){
            //_globalVariables->SINStrainModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_SIN_STRAIN_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.MaxDeviation);
        break;
      case COMMAND::SET_SIN_STRAIN_YOUNGS_MODULUS:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.YoungModulus);
        break;
      case COMMAND::SET_SIN_STRAIN_SAMPLE_CUT:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.SampleCut);
        break;
      case COMMAND::SET_SIN_STRAIN_SAMPLE_LENGTH:
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.SampleLength);
        break;
     
      //CONST DEFORMATION MODE

      case COMMAND::SET_CONST_DEFORMATION_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.MaxDeviation);
        break;
      case COMMAND::SET_CONST_DEFORMATION_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::SET_CONST_DEFORMATION_PID_KP:
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_CONST_DEFORMATION_PID_KI:
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_CONST_DEFORMATION_PID_KD:
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Kd);
        break;
      case COMMAND::SET_CONST_DEFORMATION_POSITION_TO_HOLD:{
        _globalVariables->displSharedLowerLimit = NAN;
        _globalVariables->displSharedUpperLimit = NAN;
        _globalVariables->strainSharedLowerLimit = NAN;
        _globalVariables->strainSharedUpperLimit = NAN;
        _globalVariables->deformSharedLowerLimit = NAN;
        _globalVariables->deformSharedUpperLimit = NAN;
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        break;}

      case COMMAND::SET_CONST_DEFORM_POSITION_TO_HOLD_WITH_ADD_RANGE:{
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        writeValue(data +  8, _dataLength, _globalVariables->displSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->displSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->strainSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->strainSharedUpperLimit);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvPosition > _globalVariables->displSharedUpperLimit)
          _globalVariables->isBeginDisplacementHiger = true;
        else if (_globalVariables->roCurrentAvPosition < _globalVariables->displSharedLowerLimit)
          _globalVariables->isBeginDisplacementHiger = false;
        if (_globalVariables->roCurrentAvStrain > _globalVariables->strainSharedUpperLimit)
          _globalVariables->isBeginStrainHiger = true;
        else if (_globalVariables->roCurrentAvStrain < _globalVariables->strainSharedLowerLimit)
          _globalVariables->isBeginStrainHiger = false;
        break;}

      case COMMAND::SET_CONST_DEFORM_POSITION_TO_HOLD_WITH__6__RANGE:{
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        writeValue(data +  8, _dataLength, _globalVariables->displSharedLowerLimit);
        writeValue(data +  16, _dataLength, _globalVariables->displSharedUpperLimit);
        writeValue(data +  24, _dataLength, _globalVariables->strainSharedLowerLimit);
        writeValue(data +  32, _dataLength, _globalVariables->strainSharedUpperLimit);
        writeValue(data +  40, _dataLength, _globalVariables->deformSharedLowerLimit);
        writeValue(data +  48, _dataLength, _globalVariables->deformSharedUpperLimit);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        if (_globalVariables->roCurrentAvPosition > _globalVariables->displSharedUpperLimit)
          _globalVariables->isBeginDisplacementHiger = true;
        else if (_globalVariables->roCurrentAvPosition < _globalVariables->displSharedLowerLimit)
          _globalVariables->isBeginDisplacementHiger = false;
        if (_globalVariables->roCurrentAvStrain > _globalVariables->strainSharedUpperLimit)
          _globalVariables->isBeginStrainHiger = true;
        else if (_globalVariables->roCurrentAvStrain < _globalVariables->strainSharedLowerLimit)
          _globalVariables->isBeginStrainHiger = false;
        if (_globalVariables->roCurrentAvDeformation > _globalVariables->deformSharedUpperLimit)
          _globalVariables->isBeginDeformationHiger = true;
        else if (_globalVariables->roCurrentAvDeformation < _globalVariables->deformSharedLowerLimit)
          _globalVariables->isBeginDeformationHiger = false;
        break;}

      case COMMAND::SET_CONST_DEFORMATION_SET_SPEED:
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        writeValue(data, dataLength, _globalVariables->ConstDeformationModeParams.Speed);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        break;

      //SINUS DEFORMATION MODE

      case COMMAND::SET_SIN_DEFORM_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_DEFORM_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SIN_DEFORM_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SIN_DEFORM_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDeformationModeParams.SINFrequency;
        break;
      case COMMAND::SET_SIN_DEFORM_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SIN_DEFORM_PID_KP:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SIN_DEFORM_PID_KI:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SIN_DEFORM_PID_KD:
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SIN_DEFORM_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SIN_DEFORM_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SINDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDeformationModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        //check for edge conditions
        if (_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SIN_DEFORM_AMPLITUDE_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }

      //SINUS BASED DEFORMATION MODE

      case COMMAND::SET_SINUS_BASED_DEFORM_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDeformationModeParams.SINFrequency;
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_PID_KP:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_PID_KI:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_PID_KD:
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SINUS_BASED_DEFORM_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SINUS_BASED_DEFORM_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_SINUS_BASED_DEFORM_BASE_RATIO:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.baseRatio);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        //check for edge conditions
        if (_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DEFORM_AMPL_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }

      case COMMAND::SET_WORK_MODE:{
        if (dataLength == sizeof (uint32_t)){
          writeValue(data, dataLength, _globalVariables->WorkMode);
        }else{
          uint8_t dummy;
          writeValue(data, dataLength, dummy);
          _globalVariables->WorkMode = (uint32_t)dummy;
        }
        break;
      }
      case COMMAND::SET_TEST_STATUS:{
        uint32_t _dataLength = 1;
        writeValue(data, _dataLength, _globalVariables->testStatus);
        _globalVariables->strokeCounter = 0;
        _globalVariables->testProcessPause.resetState();
        break;  
      }
      case COMMAND::SET_TIME_MEASURE_ENABLE:{
        writeValue(data, dataLength, _globalVariables->TimeMeasure.enable);
        break;
      }
      case COMMAND::SET_STATIC_TEST_STEP:{
        //DEPRECATED
        //uint32_t _dataLength = 1;
        //writeValue(data, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].id_tag);
        //writeValue(data + 1, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].rel_arr[0]);
        //writeValue(data + 2, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].rel_arr[1]);
        //writeValue(data + 3, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].rel_arr[2]);
        //writeValue(data + 4, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].rel_arr[3]);
        //writeValue(data + 5, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].rel_arr[4]);
        //writeValue(data + 6, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].panel_type);
        //writeValue(data + 7, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].isp_type);
        //writeValue(data + 8, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].id_boolparam);
        //_dataLength = 8;
        //writeValue(data + 9, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].value);
        //_dataLength = 4;
        //writeValue(data + 17, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].cycle);
        //_dataLength = 1;
        //writeValue(data + 21, _dataLength, _globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].vozvrat);
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].currentCycleCount = 0;
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].initPosition = _globalVariables->roCurrentPosition;
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].initStrain = _globalVariables->roCurrentStrain;
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].initDeformation = _globalVariables->roCurrentDeformation;
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].initTime = SystemTimer.elapsed_time();
        //_globalVariables->staticTestSteps[_globalVariables->staticTestStepsCount].firstTime = false;
        //_globalVariables->staticTestStepsCount++;
        break;
      }
      case COMMAND::SET_STATIC_TEST_DELETE_ALL_STEPS:{
        //DEPRECATED
        // _globalVariables->staticTestStepsCount = 0;
        break;
      }
      case COMMAND::SET_STATIC_TEST_DELETE_STEP:{
        //DEPRECATED
        // if(_globalVariables->staticTestStepsCount > 0){
        //   _globalVariables->staticTestStepsCount--;
        // }
        break;
      }
	    case COMMAND::SET_STATIC_TEST_PAUSE:{
        //DEPRECATED
        // _globalVariables->InternalTaskState = INTERNAL_TASK_STATE_PAUSE_TASK;
        // _globalVariables->_nextIndex = true;
        break;
      }
      case COMMAND::SET_STATIC_TEST_RESUME:{
        //DEPRECATED
        // _globalVariables->InternalTask = INTERNAL_TASK_STATIC_TEST;
        // _globalVariables->InternalTaskState = INTERNAL_TASK_STATE_STEP_1;
        break;
      }
      case COMMAND::SET_SAMPLE_BREAK_DETECTION_PARAMS:{
        // uint32_t _dataLength = 8;
        // writeValue(data,      _dataLength, _globalVariables->SBDProcentOfMaxStrain1);
        // writeValue(data + 8 , _dataLength, _globalVariables->SBDStartStrain1);
        break;
      }
      case COMMAND::SET_SAMPLE_BREAK_DETECTION_PARAMS_DF:{
        // uint32_t _dataLength = 8;
        // writeValue(data     , _dataLength, _globalVariables->SBDProcentOfMaxStrain2);
        // writeValue(data +  8, _dataLength, _globalVariables->SBDStartStrain2);
        // writeValue(data + 16, _dataLength, _globalVariables->SBDTime);
        break;
      }
      case COMMAND::GET_SAMPLE_BREAK_DETECTION_PARAMS:{
        // dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SBDProcentOfMaxStrain1);
        // dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SBDStartStrain1);
        // dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SBDProcentOfMaxStrain2);
        // dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SBDStartStrain2);
        // dataLength += basic.writeValueToBytesBuffer(data + 32, (uint64_t)(_globalVariables->SBDTime.count()));
        break;
      }
      case COMMAND::SET_SAMPLE_BREAK_DETECTION_ENABLE_MAX_STRAIN:{
        // uint32_t _dataLength = 4;
        // uint32_t val;
        // writeValue(data, _dataLength, val);
        // _globalVariables->SBDStateMaxStrain = val;
        break;
      }
      case COMMAND::SET_SAMPLE_BREAK_DETECTION_ENABLE_DF:{
        // uint32_t _dataLength = 4;
        // uint32_t val;
        // writeValue(data, _dataLength, val);
        // _globalVariables->SBDStateDF = val;
        break;
      }
      case COMMAND::SET_EXT_SBD_MAX_STRAIN:{
        uint32_t _dataLength = 4;
        uint32_t val;
        writeValue(data, _dataLength, val);
        _globalVariables->ExT_SBDStateMaxStrain = val;
        break;
      }
      case COMMAND::SET_EXT_SBD_PARAMS_MAX_STRAIN:{
        uint32_t _dataLength = 8;
        writeValue(data,      _dataLength, _globalVariables->ExT_SBDProcentOfMaxStrain1);
        writeValue(data + 8 , _dataLength, _globalVariables->ExT_SBDStartStrain1);
        break;
      }
      case COMMAND::SET_EXT_SBD_ENABLE_DF:{
        uint32_t _dataLength = 4;
        uint32_t val;
        writeValue(data, _dataLength, val);
        _globalVariables->ExT_SBDStateDF = val;
        break;
      }
      case COMMAND::SET_EXT_SBD_PARAMS_DF:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->ExT_SBDProcentOfMaxStrain2);
        writeValue(data +  8, _dataLength, _globalVariables->ExT_SBDStartStrain2);
        writeValue(data + 16, _dataLength, _globalVariables->ExT_SBDTime);
        break;
      }
      case COMMAND::EXT_SBD_START:{
        _globalVariables->InternalTask = INTERNAL_TASK_SBD;
        _globalVariables->InternalTaskSBD = INTERNAL_TASK_SBD_INIT;
        break;
      }
      case COMMAND::EXT_SBD_STOP:{
        _globalVariables->InternalTask = INTERNAL_TASK_NONE;
        _globalVariables->InternalTaskSBD = INTERNAL_TASK_SBD_NONE;
        break;
      }
      case COMMAND::SET_SSI_NULL_OFFSET:{
        _globalVariables->Mode = DAC_STATE_NONE;
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        writeValue(data, dataLength, _globalVariables->SSINullOffset);
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_START_STOP_AMPL_TUNE_PARAMS:{
        uint32_t _dataLength = 8;

        double tmpDoub;
        writeValue(data, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->startStopAmplitudeRatio = tmpDoub;}

        writeValue(data + 8, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->stopAmplitudeRatio = tmpDoub;}

        writeValue(data + 16, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->anchorSinFrequency = tmpDoub;}

        writeValue(data + 24, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->anchorSinFrequencyStop = tmpDoub;}

        _dataLength = 4;
        int tmp;
        writeValue(data + 32, _dataLength, tmp);
        if (tmp != -1){
          _globalVariables->minMaxCalculatingCounts = tmp;
        }

        writeValue(data + 36, _dataLength, tmp);
        if (tmp != -1){_globalVariables->minMaxCalculatingCountsMainProcess = tmp;}

        _dataLength = 8;
        writeValue(data + 40, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->minDeltaRatioForNullPointAttenuating = tmpDoub;}

        writeValue(data + 48, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->amplitudePrecision = tmpDoub;}

        writeValue(data + 56, _dataLength, tmpDoub);
        if (tmpDoub != -1){_globalVariables->tresholdForNullPointDeltaAccept = (float)tmpDoub;}

        _dataLength = 4;
        writeValue(data + 64, _dataLength, tmp);
        if (tmp != -1){_globalVariables->stepForNullPointGetCorrection = tmp;}

        break;
      }

      case COMMAND::GET_START_STOP_AMPL_TUNE_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->startStopAmplitudeRatio);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->stopAmplitudeRatio);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->anchorSinFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->anchorSinFrequencyStop);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->minMaxCalculatingCounts);
        dataLength += basic.writeValueToBytesBuffer(data + 36, _globalVariables->minMaxCalculatingCountsMainProcess);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->minDeltaRatioForNullPointAttenuating);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->amplitudePrecision);
        dataLength += basic.writeValueToBytesBuffer(data + 56, (double)_globalVariables->tresholdForNullPointDeltaAccept);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->stepForNullPointGetCorrection);
        break;
      }
      case COMMAND::SET_MIN_MAX_CALCULATING_COUNS_MAIN:{
        uint32_t _dataLength = 4;
        writeValue(data, _dataLength, _globalVariables->minMaxCalculatingCountsMainProcess);
        break;
      }
      case COMMAND::WRITE_STRAIN_CALIBR_COEFS:{
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
          ADCext.setCalibrCoefs(k, b);
          #else
          ADS869xStrain.setCalibrCoefs(k, b);
          #endif
          //ADCext.writeCalibrCoefsInFlash(k, b);
        }
        break;
      }
      case COMMAND::WRITE_DEFORMATION_CALIBR_COEFS:{
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          ADCextExtens.setCalibrCoefs(k, b);
          //ADCext.writeCalibrCoefsInFlash(k, b);
        }
        break;
      }
      case COMMAND::WRITE_POSITION_CALIBR_COEFS:
      {
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          RSSIReader.setCalibrCoefs(k, b);
        }
        break;
      }
      case COMMAND::WRITE_TO_FLASH_STRAIN_CALIBR_COEFS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          //ADCext.setCalibrCoefs(k, b);
          #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
          ADCext.writeCalibrCoefsInFlash(k, b);
          #else
          ADS869xStrain.writeCalibrCoefsInFlash(k, b);
          #endif
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::WRITE_TO_FLASH_DEFORMATION_CALIBR_COEFS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          //ADCext.setCalibrCoefs(k, b);
          ADCextExtens.writeCalibrCoefsInFlash(k, b);
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::WRITE_TO_FLASH_POSITION_CALIBR_COEFS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t _dataLength = 8;
        double k, b;
        if (writeValue(data, _dataLength, k) &&
            writeValue(data + 8, _dataLength, b)){
          RSSIReader.writeCalibrCoefsInFlash(k, b);
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::READ_STRAIN_CALIBR_COEFS:{
        double k, b;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        ADCext.getCalibrCoefs(&k, &b);
        #else
        ADS869xStrain.getCalibrCoefs(&k, &b);
        #endif
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::READ_DEFORMATION_CALIBR_COEFS:{
        double k, b;
        ADCextExtens.getCalibrCoefs(&k, &b);
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::READ_POSITION_CALIBR_COEFS:{
        double k, b;
        RSSIReader.getCalibrCoefs(&k, &b);
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::READ_FROM_FLASH_STRAIN_CALIBR_COEFS:{
        double k, b;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        ADCext.readCalibrCoefsFromFlash(&k, &b);
        #else
        ADS869xStrain.readCalibrCoefsFromFlash(&k, &b);
        #endif
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::READ_FROM_FLASH_DEFORMATION_CALIBR_COEFS:{
        double k, b;
        ADCextExtens.readCalibrCoefsFromFlash(&k, &b);
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::READ_FROM_FLASH_POSITION_CALIBR_COEFS:{
        double k, b;
        RSSIReader.readCalibrCoefsFromFlash(&k, &b);
        dataLength =  basic.writeValueToBytesBuffer(data     , k);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , b);
        break;
      }
      case COMMAND::SET_INTERNAL_TASK:{
        writeValue(data, dataLength, _globalVariables->InternalTask);
        break;
      }
      case COMMAND::START_INTERNAL_TASK:{
        _globalVariables->InternalTaskState = INTERNAL_TASK_STATE_INIT;
        break;
      }
      case COMMAND::STOP_INTERNAL_TASK:{
        if ((_globalVariables->InternalTaskState != INTERNAL_TASK_STATE_NONE) || (_globalVariables->InternalTaskState == INTERNAL_TASK_STATE_PAUSE_TASK)){
          _globalVariables->InternalTask = INTERNAL_TASK_STATIC_TEST;
          _globalVariables->InternalTaskState = INTERNAL_TASK_STATE_STOP_TASK;
        }
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SINStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SINStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        //check for edge conditions
        if (_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SIN_DISPL_AMPLITUDE_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        if (_globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SINStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SIN_STRAIN_AMPLITUDE_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SINStrainModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }

        //SINUS BASED DISPLACEMENT MODE

      case COMMAND::SET_SINUS_BASED_DISP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDisplacementModeParams.SINFrequency;
        break;
      case COMMAND::SET_SINUS_BASED_DISP_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_PID_KP:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_PID_KI:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SINUS_BASED_DISP_PID_KD:
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SINUS_BASED_DISP_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SINUS_BASED_DISP_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_SINUS_BASED_DISP_BASE_RATIO:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.baseRatio);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        //check for edge conditions
        if (_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_DISP_AMPL_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }

        //SINUS BASED STRAIN MODE

      case COMMAND::SET_SINUS_BASED_STRAIN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.UpAmplitude);
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_UP_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.UpAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_DOWN_AMPLITUDE:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.DownAmplitude);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedStrainModeParams.SINFrequency;
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_MODE_FREQUENCY:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.ModeFrequency);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_PID_KP:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kp);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_PID_KI:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Ki);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_PID_KD:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kd);
        break;
      // case COMMAND_SET_SINUS_BASED_STRAIN_TCYCLE:
      //   writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.Tcycle);
      //   break;
      case COMMAND::SET_SINUS_BASED_STRAIN_NUMBER_OF_CYCLES:
        if (writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.NumberOfCycles)){
          if ( _globalVariables->SinusBasedStrainModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedStrainModeParams.NumberOfCycles++;
          }
        }
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_MAX_DEVIATION:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.MaxDeviation);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_YOUNGS_MODULUS:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.YoungModulus);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_SAMPLE_CUT:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.SampleCut);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_SAMPLE_LENGTH:
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.SampleLength);
        break;
      case COMMAND::SET_SINUS_BASED_STRAIN_BASE_RATIO:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.baseRatio);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_ENABLE:{
        uint32_t state;
        writeValue(data, dataLength, state);
        if (state)
        {
          _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_ENABLE;
        }
        else{
          _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.state = AMPLITUDE_TUNE_STATE_EXIT;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_CORRECTION_TYPE:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.correctionType);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_THREAD_FREQ:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.freq);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_PID_COEFS:{
        uint32_t _dataLength = 8;
        writeValue(data, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKP);
        writeValue(data, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKP);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKI);
        writeValue(data + 8, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKI);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKD);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_FALL_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        if (_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles < 1){
            _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeFallCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_RISE_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        //check for edge conditions
        if (_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles < 1){
            _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.amplitudeRiseCycles = 1;
        }
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_WAIT_CYCLES:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.waitCycles);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_SMOOTH_START:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.startProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_SMOOTH_STOP:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.stopProcess);
        break;
      }
      case COMMAND::SET_SINUS_BASED_STRAIN_AMPL_TUNE_MAIN_CORRECTION:{
        writeValue(data, dataLength, _globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.mainProcess);
        break;
      }
      case COMMAND::SET_HW_CMD:{
        uint32_t _dataLength = 4;
        uint32_t hwCmd = HW_CMD_UNDEFINED;
        int32_t state = 0;
        writeValue(data, _dataLength, hwCmd);
        writeValue(data + 4, _dataLength, state);
        switch (hwCmd)
        {
        case HW_CMD_0:
          HwCmd0.write(state);
          break;
        case HW_CMD_1:
          HwCmd1.write(state);
          break;
        case HW_CMD_2:
          HwCmd2.write(state);
          break;
        case HW_CMD_3:
          HwCmd3.write(state);
          break;
        case HW_CMD_4:
          HwCmd4.write(state);
          break;
        case HW_CMD_5:
          HwCmd5.write(state);
          break;
        case HW_CMD_6:
          HwCmd6.write(state);
          break;
        
        default:
          break;
        }
        //printf("SET_HWCMD:%d; state:%d\n\r", hwCmd, state);
        break;
      }
      //set group params
      case COMMAND::SET_CONST_VOLTAGE_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->ConstModeParams.Voltage);
        writeValue(data + 8 , _dataLength, _globalVariables->ConstModeParams.ConstFrequency);
        _dataLength = 4;
        writeValue(data + 16, _dataLength, _globalVariables->ConstModeParams.Direction);
        break;
      }
      case COMMAND::SET_CONST_STRAIN_PARAMS:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        writeValue(data     , _dataLength, _globalVariables->ConstStrainModeParams.MaxDeviation);
        writeValue(data + 8 , _dataLength, _globalVariables->ConstStrainModeParams.ModeFrequency);
        writeValue(data + 16, _dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Kp);
        writeValue(data + 24, _dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Ki);
        writeValue(data + 32, _dataLength, _globalVariables->ConstStrainModeParams.PIDParams.Kd);
        writeValue(data + 40, _dataLength, _globalVariables->ConstStrainModeParams.StrainToHold);
        writeValue(data + 48, _dataLength, _globalVariables->ConstStrainModeParams.SampleCut);
        writeValue(data + 56, _dataLength, _globalVariables->ConstStrainModeParams.SampleLength);
        writeValue(data + 64, _dataLength, _globalVariables->ConstStrainModeParams.YoungModulus);
        writeValue(data + 72, _dataLength, _globalVariables->ConstStrainModeParams.Speed);
        writeValue(data + 80, _dataLength, _globalVariables->ConstStrainModeParams.MaxSpeed);
        writeValue(data + 88, _dataLength, _globalVariables->ConstStrainModeParams.delta);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        break;
      }
      case COMMAND::SET_CONST_DISPLACEMENT_PARAMS:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        writeValue(data     , _dataLength, _globalVariables->ConstDisplacementModeParams.MaxDeviation);
        writeValue(data + 8 , _dataLength, _globalVariables->ConstDisplacementModeParams.ModeFrequency);
        writeValue(data + 16, _dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Kp);
        writeValue(data + 24, _dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Ki);
        writeValue(data + 32, _dataLength, _globalVariables->ConstDisplacementModeParams.PIDParams.Kd);
        writeValue(data + 40, _dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        writeValue(data + 48, _dataLength, _globalVariables->ConstDisplacementModeParams.Speed);
        writeValue(data + 56, _dataLength, _globalVariables->ConstDisplacementModeParams.MaxSpeed);
        writeValue(data + 64, _dataLength, _globalVariables->ConstDisplacementModeParams.delta);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        break;
      }
      case COMMAND::SET_CONST_DEFORMATION_PARAMS:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        writeValue(data     , _dataLength, _globalVariables->ConstDeformationModeParams.MaxDeviation);
        writeValue(data + 8 , _dataLength, _globalVariables->ConstDeformationModeParams.ModeFrequency);
        writeValue(data + 16, _dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Kp);
        writeValue(data + 24, _dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Ki);
        writeValue(data + 32, _dataLength, _globalVariables->ConstDeformationModeParams.PIDParams.Kd);
        writeValue(data + 40, _dataLength, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        writeValue(data + 48, _dataLength, _globalVariables->ConstDeformationModeParams.Speed);
        writeValue(data + 56, _dataLength, _globalVariables->ConstDeformationModeParams.MaxSpeed);
        writeValue(data + 64, _dataLength, _globalVariables->ConstDeformationModeParams.delta);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        break;        
      }
      case COMMAND::SET_SIN_DISPLACEMENT_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINDisplacementModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINDisplacementModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDisplacementModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SINDisplacementModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SINDisplacementModeParams.PIDParams.Kd);
        if (writeValue(data + 56, _dataLength, _globalVariables->SINDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SINDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDisplacementModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SINDisplacementModeParams.MaxDeviation);
        // writeValue(data + 72, _dataLength, _globalVariables->SINDisplacementModeParams.Tcycle);
        break;
      }
      case COMMAND::SET_SIN_DEFORMATION_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINDeformationModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINDeformationModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDeformationModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SINDeformationModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SINDeformationModeParams.PIDParams.Kd);
        if (writeValue(data + 56, _dataLength, _globalVariables->SINDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SINDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDeformationModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SINDeformationModeParams.MaxDeviation);
        // writeValue(data + 72, _dataLength, _globalVariables->SINDeformationModeParams.Tcycle);
        break;
      }      
      case COMMAND::SET_SIN_BASED_DISP_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedDisplacementModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedDisplacementModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDisplacementModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd);
        if (writeValue(data + 56, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.MaxDeviation);
        // writeValue(data + 72, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.Tcycle);
        writeValue(data + 80, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 88, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.ModeType);
        break;
      }
      case COMMAND::SET_SIN_BASED_DEFORMATION_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDeformationModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SinusBasedDeformationModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd);
        if (writeValue(data + 56, _dataLength, _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SinusBasedDeformationModeParams.MaxDeviation);
        // writeValue(data + 72, _dataLength, _globalVariables->SinusBasedDeformationModeParams.Tcycle);
        writeValue(data + 80, _dataLength, _globalVariables->SinusBasedDeformationModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 88, _dataLength, _globalVariables->SinusBasedDeformationModeParams.ModeType);
        break;
      }     
      case COMMAND::SET_SIN_STRAIN_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINStrainModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINStrainModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINStrainModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SINStrainModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SINStrainModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SINStrainModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SINStrainModeParams.PIDParams.Kd);
        if(writeValue(data + 56, _dataLength, _globalVariables->SINStrainModeParams.NumberOfCycles)){
          if (_globalVariables->SINStrainModeParams.NumberOfCycles > 0){
          //_globalVariables->SINStrainModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SINStrainModeParams.MaxDeviation);
        writeValue(data + 72, _dataLength, _globalVariables->SINStrainModeParams.SampleCut);
        writeValue(data + 80, _dataLength, _globalVariables->SINStrainModeParams.SampleLength);
        writeValue(data + 88, _dataLength, _globalVariables->SINStrainModeParams.YoungModulus);
        // writeValue(data + 96, _dataLength, _globalVariables->SINStrainModeParams.Tcycle);
        break;
      }
      case COMMAND::SET_SIN_BASED_STRAIN_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedStrainModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedStrainModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedStrainModeParams.SINFrequency;
        writeValue(data + 24, _dataLength, _globalVariables->SinusBasedStrainModeParams.ModeFrequency);
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kp);
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Ki);
        writeValue(data + 48, _dataLength, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kd);
        if(writeValue(data + 56, _dataLength, _globalVariables->SinusBasedStrainModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedStrainModeParams.NumberOfCycles > 0){
          //_globalVariables->SinusBasedStrainModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 64, _dataLength, _globalVariables->SinusBasedStrainModeParams.MaxDeviation);
        writeValue(data + 72, _dataLength, _globalVariables->SinusBasedStrainModeParams.SampleCut);
        writeValue(data + 80, _dataLength, _globalVariables->SinusBasedStrainModeParams.SampleLength);
        writeValue(data + 88, _dataLength, _globalVariables->SinusBasedStrainModeParams.YoungModulus);
        // writeValue(data + 96, _dataLength, _globalVariables->SinusBasedStrainModeParams.Tcycle);
        writeValue(data + 104, _dataLength, _globalVariables->SinusBasedStrainModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 112, _dataLength, _globalVariables->SinusBasedStrainModeParams.ModeType);
        break;
      }
      case COMMAND::SET_TIME_MEASURE_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->TimeMeasure.startMeasurePosition);
        writeValue(data + 8 , _dataLength, _globalVariables->TimeMeasure.endMeasurePosition);
        break;
      }
      case COMMAND::SET_HARDNESS_CALC_PARAMS:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SampleHardnessInfo.Fmax);
        writeValue(data + 8 , _dataLength, _globalVariables->SampleHardnessInfo.maxElongation);
        writeValue(data + 16, _dataLength, _globalVariables->SampleHardnessInfo.speed);
        _dataLength = 4;
        writeValue(data + 24, _dataLength, _globalVariables->SampleHardnessInfo.direction);
        break;
      }
      case COMMAND::SET_MACHINE_PARAMS:{
        uint32_t _dataLength = 4;
        writeValue(data     , _dataLength, _globalVariables->valveDirectionMode);
        writeValue(data + 4 , _dataLength, _globalVariables->pistonMode);
        writeValue(data + 8 , _dataLength, _globalVariables->positionInvertAxis);
        writeValue(data + 12, _dataLength, _globalVariables->positionAxisMode);
        writeValue(data + 16, _dataLength, _globalVariables->strainInvertAxis);
        writeValue(data + 20, _dataLength, _globalVariables->strainAxisMode);
        writeValue(data + 24, _dataLength, _globalVariables->deformationInvertAxis);
        writeValue(data + 28, _dataLength, _globalVariables->deformationAxisMode);
        break;
      }

      case COMMAND::SET_CONST_DISPLACEMENT_MODE:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstDisplacementModeParams.speedEnable = false;
        writeValue(data    , _dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        writeValue(data + 8, _dataLength, _globalVariables->ConstDisplacementModeParams.Speed);
        _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DISP_CONST;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_DISPLACEMENT_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINDisplacementModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINDisplacementModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDisplacementModeParams.SINFrequency;
        if (writeValue(data + 24, _dataLength, _globalVariables->SINDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SINDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDisplacementModeParams.NumberOfCycles++;
          }
        }
        _globalVariables->SINDisplacementModeParams.InternalCounter = 0;
        _globalVariables->SINDisplacementModeParams.InternalCounterBuffered = 0;
        _globalVariables->SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DISP_SIN;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_BASED_DISP_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedDisplacementModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedDisplacementModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDisplacementModeParams.SINFrequency;
        if (writeValue(data + 24, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedDisplacementModeParams.ModeType);
        _globalVariables->SinusBasedDisplacementModeParams.InternalCounter = 0;
        _globalVariables->SinusBasedDisplacementModeParams.InternalCounterBuffered = 0;
        _globalVariables->SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DISP_SINUS_BASED;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_CONST_STRAIN_MODE:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstStrainModeParams.speedEnable = false;
        writeValue(data     , _dataLength, _globalVariables->ConstStrainModeParams.StrainToHold);
        writeValue(data +  8, _dataLength, _globalVariables->ConstStrainModeParams.YoungModulus);
        writeValue(data + 16, _dataLength, _globalVariables->ConstStrainModeParams.Speed);
        _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_STRAIN_CONST;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_STRAIN_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINStrainModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINStrainModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINStrainModeParams.SINFrequency;
        if(writeValue(data + 24, _dataLength, _globalVariables->SINStrainModeParams.NumberOfCycles)){
          if (_globalVariables->SINStrainModeParams.NumberOfCycles > 0){
            //_globalVariables->SINStrainModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 32, _dataLength, _globalVariables->SINStrainModeParams.YoungModulus);
        uint8_t _toHold = 1;
        if (dataLength > 40) {
          _dataLength = 1;
          writeValue(data + 40, _dataLength, _toHold);
        }
        _globalVariables->SINStrainModeParams.holdConstDisplAtEnd = _toHold != 0;
        _globalVariables->SINStrainModeParams.InternalCounter = 0;
        _globalVariables->SINStrainModeParams.InternalCounterBuffered = 0;
        _globalVariables->SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_STRAIN_SIN;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_BASED_STRAIN_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedStrainModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedStrainModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedStrainModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedStrainModeParams.SINFrequency;
        if(writeValue(data + 24, _dataLength, _globalVariables->SinusBasedStrainModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedStrainModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedStrainModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedStrainModeParams.YoungModulus);
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedStrainModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 48, _dataLength, _globalVariables->SinusBasedStrainModeParams.ModeType);
        uint8_t _toHold = 1;
        if (dataLength > 52) {
          _dataLength = 1;
          writeValue(data + 52, _dataLength, _toHold);
        }
        _globalVariables->SinusBasedStrainModeParams.holdConstDisplAtEnd = _toHold != 0;
        _globalVariables->SinusBasedStrainModeParams.InternalCounter = 0;
        _globalVariables->SinusBasedStrainModeParams.InternalCounterBuffered = 0;
        _globalVariables->SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_STRAIN_SINUS_BASED;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_CONST_DEFORMATION_MODE:{
        uint32_t _dataLength = 8;
        _globalVariables->ConstDeformationModeParams.speedEnable = false;
        writeValue(data    , _dataLength, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        writeValue(data + 8, _dataLength, _globalVariables->ConstDeformationModeParams.Speed);
        _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DEFORMATION_CONST;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_DEFORMATION_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SINDeformationModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SINDeformationModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SINDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SINDeformationModeParams.SINFrequency;
        if (writeValue(data + 24, _dataLength, _globalVariables->SINDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SINDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SINDeformationModeParams.NumberOfCycles++;
          }
        }
        uint8_t _toHold = 1;
        if (dataLength > 32) {
          _dataLength = 1;
          writeValue(data + 32, _dataLength, _toHold);
        }
        _globalVariables->SINDeformationModeParams.holdConstDisplAtEnd = _toHold != 0;
        _globalVariables->SINDeformationModeParams.InternalCounter = 0;
        _globalVariables->SINDeformationModeParams.InternalCounterBuffered = 0;
        _globalVariables->SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DEFORMATION_SIN;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }
      case COMMAND::SET_SIN_BASED_DEFORMATION_MODE:{
        uint32_t _dataLength = 8;
        writeValue(data     , _dataLength, _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        writeValue(data + 8 , _dataLength, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        writeValue(data + 16, _dataLength, _globalVariables->SinusBasedDeformationModeParams.SINFrequency);
        _globalVariables->reserveSinMainFrequency = _globalVariables->SinusBasedDeformationModeParams.SINFrequency;
        if (writeValue(data + 24, _dataLength, _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles)){
          if (_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles > 0){
            //_globalVariables->SinusBasedDeformationModeParams.NumberOfCycles++;
          }
        }
        writeValue(data + 32, _dataLength, _globalVariables->SinusBasedDeformationModeParams.baseRatio);
        _dataLength = 4;
        writeValue(data + 40, _dataLength, _globalVariables->SinusBasedDeformationModeParams.ModeType);
        uint8_t _toHold = 1;
        if (dataLength > 44) {
          _dataLength = 1;
          writeValue(data + 44, _dataLength, _toHold);
        }
        _globalVariables->SinusBasedDeformationModeParams.holdConstDisplAtEnd = _toHold != 0;
        _globalVariables->SinusBasedDeformationModeParams.InternalCounter = 0;
        _globalVariables->SinusBasedDeformationModeParams.InternalCounterBuffered = 0;
        _globalVariables->SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
        _globalVariables->Mode = DAC_STATE_DEFORMATION_SINUS_BASED;
        _globalVariables->testProcessPause.resetState();
        _globalVariables->stepID++;
        break;
      }

      case COMMAND::SET_STRAIN_CALIBRATION_POINTS:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADCext.calibration->setPoints(points, pointsLength);
          ADCext.calibration->calculateSections();
          delete[] points;
        }
        #else
        if(ADS869xStrain.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xStrain.calibration->setPoints(points, pointsLength);
          ADS869xStrain.calibration->calculateSections();
          delete[] points;
        }
        #endif
        break;
      }
      case COMMAND::SET_STRAIN_CALIBRATION_POINTS_2:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADCext.calibration2->setPoints(points, pointsLength);
          ADCext.calibration2->calculateSections();
          delete[] points;
        }
        #else
        if(ADS869xStrain.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xStrain.calibration2->setPoints(points, pointsLength);
          ADS869xStrain.calibration2->calculateSections();
          delete[] points;
        }
        #endif
        break;
      }
      case COMMAND::SET_DEFORMATION_CALIBRATION_POINTS:{
        switch (_globalVariables->machineInfo.deformation.sensorType)
        {
        case SENSOR_TYPE_ANALOG:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADCextExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADCextExtens.calibration->setPoints(points, pointsLength);
            ADCextExtens.calibration->calculateSections();
            delete[] points;
          }
          break;
        }
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        case SENSOR_TYPE_ANALOG_0_10V:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.calibration->setPoints(points, pointsLength);
            ADS869xExtens.calibration->calculateSections();
            delete[] points;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.calibration2->setPoints(points, pointsLength);
            ADS869xExtens.calibration2->calculateSections();
            delete[] points;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT2:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration3->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.calibration3->setPoints(points, pointsLength);
            ADS869xExtens.calibration3->calculateSections();
            delete[] points;
          }
          break;
        }
        #endif
        default:
          break;
        }
        break;
      }
      case COMMAND::SET_POSITION_CALIBRATION_POINTS:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(RSSIReader.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          RSSIReader.calibration->setPoints(points, pointsLength);
          RSSIReader.calibration->calculateSections();
          delete[] points;
        }
        break;
      }
      case COMMAND::SET_TO_FLASH_STRAIN_CALIBRATION_POINTS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADCext.writeCalibrPointsInFlash(points, pointsLength);
          delete[] points;
        }
        #else
        if(ADS869xStrain.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xStrain.writeCalibrPointsInFlash(points, pointsLength);
          delete[] points;
        }
        #endif
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::SET_TO_FLASH_STRAIN_CALIBRATION_POINTS_2:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADCext.writeCalibrPointsInFlash2(points, pointsLength);
          delete[] points;
        }
        #else
        if(ADS869xStrain.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xStrain.writeCalibrPointsInFlash2(points, pointsLength);
          delete[] points;
        }
        #endif
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORMATION_CALIBRATION_POINTS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        switch (_globalVariables->machineInfo.deformation.sensorType)
        {
        case SENSOR_TYPE_ANALOG:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADCextExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADCextExtens.writeCalibrPointsInFlash(points, pointsLength);
            delete[] points;
          }
          break;
        }
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        case SENSOR_TYPE_ANALOG_0_10V:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.writeCalibrPointsInFlash(points, pointsLength);
            delete[] points;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.writeCalibrPointsInFlash2(points, pointsLength);
            delete[] points;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT2:{
          uint32_t pointsLength;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          writeValue(data, uint32Length, pointsLength);
          if(ADS869xExtens.calibration3->getMaxPoints() >= pointsLength && pointsLength != 1){
            point_t *points = new point_t[pointsLength];
            for(uint32_t i = 0; i < pointsLength; i++){
              writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
              writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
            }
            ADS869xExtens.writeCalibrPointsInFlash3(points, pointsLength);
            delete[] points;
          }
          break;
        }
        #endif
        default:
          break;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::SET_TO_FLASH_POSITION_CALIBRATION_POINTS:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(RSSIReader.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          RSSIReader.writeCalibrPointsInFlash(points, pointsLength);
          delete[] points;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_STRAIN_CALIBRATION_POINTS:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADCext.calibration->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        #else
        if(ADS869xStrain.calibration->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADS869xStrain.calibration->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        #endif
        break;
      }
      case COMMAND::GET_STRAIN_CALIBRATION_POINTS_2:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        if(ADCext.calibration2->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADCext.calibration2->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        #else
        if(ADS869xStrain.calibration2->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADS869xStrain.calibration2->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        #endif
        break;
      }
      case COMMAND::GET_DEFORMATION_CALIBRATION_POINTS:{
        switch (_globalVariables->machineInfo.deformation.sensorType)
        {
        case SENSOR_TYPE_ANALOG:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          if(ADCextExtens.calibration->getNumberOfPoints(dummy)){
            pointsLength = dummy;
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            if(ADCextExtens.calibration->getPoints(points, dummy)){
              for (int i = 0; i < (int)pointsLength; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
              }
              dataLength = _datalength; 
            }else{
              dataLength = 0;
            }
            delete[] points;
          }else{
            pointsLength = dummy;
            dataLength = 0;
          }
          break;
        }
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        case SENSOR_TYPE_ANALOG_0_10V:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          if(ADS869xExtens.calibration->getNumberOfPoints(dummy)){
            pointsLength = dummy;
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            if(ADS869xExtens.calibration->getPoints(points, dummy)){
              for (int i = 0; i < (int)pointsLength; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
              }
              dataLength = _datalength; 
            }else{
              dataLength = 0;
            }
            delete[] points;
          }else{
            pointsLength = dummy;
            dataLength = 0;
          }
          break; 
        }
        case SENSOR_TYPE_ANALOG_LVDT:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          if(ADS869xExtens.calibration2->getNumberOfPoints(dummy)){
            pointsLength = dummy;
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            if(ADS869xExtens.calibration2->getPoints(points, dummy)){
              for (int i = 0; i < (int)pointsLength; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
              }
              dataLength = _datalength; 
            }else{
              dataLength = 0;
            }
            delete[] points;
          }else{
            pointsLength = dummy;
            dataLength = 0;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT2:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          if(ADS869xExtens.calibration3->getNumberOfPoints(dummy)){
            pointsLength = dummy;
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            if(ADS869xExtens.calibration3->getPoints(points, dummy)){
              for (int i = 0; i < (int)pointsLength; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
              }
              dataLength = _datalength; 
            }else{
              dataLength = 0;
            }
            delete[] points;
          }else{
            pointsLength = dummy;
            dataLength = 0;
          }
          break;
        }
        #endif
        default:
          break;
        }
        break;
      }
      case COMMAND::GET_POSITION_CALIBRATION_POINTS:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        if(RSSIReader.calibration->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(RSSIReader.calibration->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        break;
      }
      case COMMAND::GET_FROM_FLASH_STRAIN_CALIBRATION_POINTS:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        ADCext.readCalibrPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADCext.readCalibrPointsFromFlash(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        #else
        ADS869xStrain.readCalibrPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADS869xStrain.readCalibrPointsFromFlash(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        #endif
        break;
      }
      case COMMAND::GET_FROM_FLASH_STRAIN_CALIBRATION_POINTS_2:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        ADCext.readCalibrPointsSizeFromFlash2(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADCext.readCalibrPointsFromFlash2(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        #else
        ADS869xStrain.readCalibrPointsSizeFromFlash2(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADS869xStrain.readCalibrPointsFromFlash2(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        #endif
        break;
      }
      case COMMAND::SWITCH_STRAIN_CALIBRATION:{
        uint32_t _dataLength = 1;
        writeValue(data, _dataLength, _globalVariables->strainChannel);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORMATION_CALIBRATION_POINTS:{
        switch (_globalVariables->machineInfo.deformation.sensorType)
        {
        case SENSOR_TYPE_ANALOG:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          ADCextExtens.readCalibrPointsSizeFromFlash(&dummy);
          pointsLength = dummy;
          if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            ADCextExtens.readCalibrPointsFromFlash(points, dummy);
            for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
            delete[] points;
          }else{
            
            dataLength = 0;
          }
          break;
        }
        #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN)
        case SENSOR_TYPE_ANALOG_0_10V:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          ADS869xExtens.readCalibrPointsSizeFromFlash(&dummy);
          pointsLength = dummy;
          if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            ADS869xExtens.readCalibrPointsFromFlash(points, dummy);
            for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
            delete[] points;
          }else{
            
            dataLength = 0;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          ADS869xExtens.readCalibrPointsSizeFromFlash2(&dummy);
          pointsLength = dummy;
          if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            ADS869xExtens.readCalibrPointsFromFlash2(points, dummy);
            for (int i = 0; i < dummy; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
            delete[] points;
          }else{
            
            dataLength = 0;
          }
          break;
        }
        case SENSOR_TYPE_ANALOG_LVDT2:{
          uint32_t pointsLength = 0;
          uint32_t uint32Length = sizeof pointsLength;
          uint32_t doubleLength = sizeof(double);
          int dummy = 0;
          ADS869xExtens.readCalibrPointsSizeFromFlash3(&dummy);
          pointsLength = dummy;
          if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
            uint32_t _datalength = 0;
            _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
            point_t *points = new point_t[pointsLength];
            ADS869xExtens.readCalibrPointsFromFlash3(points, dummy);
            for (int i = 0; i < dummy; i++){
                _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
                _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
            delete[] points;
          }else{
            
            dataLength = 0;
          }
          break;
        }
        #endif
        default:
          break;
        }
        break;
      }
      case COMMAND::GET_FROM_FLASH_POSITION_CALIBRATION_POINTS:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        RSSIReader.readCalibrPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          RSSIReader.readCalibrPointsFromFlash(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        break;
      }
      // Deformation 2nd channel
      case COMMAND::SET_DEFORMATION_CALIBRATION_POINTS_2ND_CH:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(ADS869xExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xExtens.calibration->setPoints(points, pointsLength);
          ADS869xExtens.calibration->calculateSections();
          delete[] points;
        }
        break;
      }
      case COMMAND::GET_DEFORMATION_CALIBRATION_POINTS_2ND_CH:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        if(ADS869xExtens.calibration->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADS869xExtens.calibration->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORM_CALIBRATION_POINTS_2ND_CH:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(ADS869xExtens.calibration->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xExtens.writeCalibrPointsInFlash(points, pointsLength);
          delete[] points;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORM_CALIBRATION_POINTS_2ND_CH:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        ADS869xExtens.readCalibrPointsSizeFromFlash(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADS869xExtens.readCalibrPointsFromFlash(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        break;
      }
      // Deformation 3rd channel
      case COMMAND::SET_DEFORMATION_CALIBRATION_POINTS_3RD_CH:{
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(ADS869xExtens.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xExtens.calibration2->setPoints(points, pointsLength);
          ADS869xExtens.calibration2->calculateSections();
          delete[] points;
        }
        break;
      }
      case COMMAND::GET_DEFORMATION_CALIBRATION_POINTS_3RD_CH:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        if(ADS869xExtens.calibration2->getNumberOfPoints(dummy)){
          pointsLength = dummy;
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          if(ADS869xExtens.calibration2->getPoints(points, dummy)){
            for (int i = 0; i < (int)pointsLength; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
            }
            dataLength = _datalength; 
          }else{
            dataLength = 0;
          }
          delete[] points;
        }else{
          pointsLength = dummy;
          dataLength = 0;
        }
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORM_CALIBRATION_POINTS_3RD_CH:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t pointsLength;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        writeValue(data, uint32Length, pointsLength);
        if(ADS869xExtens.calibration2->getMaxPoints() >= pointsLength && pointsLength != 1){
          point_t *points = new point_t[pointsLength];
          for(uint32_t i = 0; i < pointsLength; i++){
            writeValue(data + uint32Length + 2 * i * doubleLength,                doubleLength, points[i].xRAW);
            writeValue(data + uint32Length + 2 * i * doubleLength + doubleLength, doubleLength, points[i].yPhy);
          }
          ADS869xExtens.writeCalibrPointsInFlash2(points, pointsLength);
          delete[] points;
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORM_CALIBRATION_POINTS_3RD_CH:{
        uint32_t pointsLength = 0;
        uint32_t uint32Length = sizeof pointsLength;
        uint32_t doubleLength = sizeof(double);
        int dummy = 0;
        ADS869xExtens.readCalibrPointsSizeFromFlash2(&dummy);
        pointsLength = dummy;
        if(pointsLength > 0 && pointsLength != 0xFFFFFFFF){
          uint32_t _datalength = 0;
          _datalength += basic.writeValueToBytesBuffer(data, pointsLength);
          point_t *points = new point_t[pointsLength];
          ADS869xExtens.readCalibrPointsFromFlash2(points, dummy);
          for (int i = 0; i < dummy; i++){
              _datalength += basic.writeValueToBytesBuffer(data, points[i].xRAW, uint32Length + 2 * i * doubleLength);
              _datalength += basic.writeValueToBytesBuffer(data, points[i].yPhy, uint32Length + 2 * i * doubleLength + doubleLength);
          }
          dataLength = _datalength; 
          delete[] points;
        }else{
          
          dataLength = 0;
        }
        break;
      }
      case COMMAND::SET_DEFORMATION_CHANNEL:{
        if(_globalVariables->Mode != DAC_STATE_DEFORMATION_CONST){
          writeValue(data, dataLength, _globalVariables->DeformationChannel);
        }
        break;
      }
      case COMMAND::GET_DEFORMATION_CHANNEL:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->DeformationChannel);
        break;
      }

      //calibration points notes write and read flash memory
      
      case COMMAND::SET_TO_FLASH_STRAIN_CALIBRATION_POINTS_NOTES:{
        writeValueLikeCharBuffer(STRAIN_CALIBRATION_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::GET_FROM_FLASH_STRAIN_CALIBRATION_POINTS_NOTES:{
        writeValueLikeCharBuffer(POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::SET_TO_FLASH_DISPL_CALIBRATION_POINTS_NOTES:{        
        writeValueLikeCharBuffer(POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DISPL_CALIBRATION_POINTS_NOTES:{
        readValueLikeCharBuffer(dataLength, data);
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORM_CALIBRATION_POINTS_NOTES:{
        writeValueLikeCharBuffer(DEFORMATION_CALIBRATION_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORM_CALIBRATION_POINTS_NOTES:{
        readValueLikeCharBuffer(dataLength, data);
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORM_CH2_CALIBRATION_POINTS_NOTES:{
        writeValueLikeCharBuffer(DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORM_CH2_CALIBRATION_POINTS_NOTES:{
        readValueLikeCharBuffer(dataLength, data);
        break;
      }
      case COMMAND::SET_TO_FLASH_DEFORM_CH3_CALIBRATION_POINTS_NOTES:{
        writeValueLikeCharBuffer(DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_MAX_SIZE, dataLength, data);
        break;
      }
      case COMMAND::GET_FROM_FLASH_DEFORM_CH3_CALIBRATION_POINTS_NOTES:{
        readValueLikeCharBuffer(dataLength, data);
        break;
      }


      case COMMAND::SET_TO_FLASH_STRAIN_REFERENCE_VOLTAGE:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        if(dataLength >= sizeof(float)){
          internalFlash.setWritingParams(data, sizeof(float), STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET, true);
          internalFlash.Writing_To_Flash_Through_Buf_Sector();
        }
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_STRAIN_REFERENCE_VOLTAGE:{
        internalFlash.readInOneSector(data, STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET, sizeof(float));
        break;
      }
      case COMMAND::SET_FLASH_OPERATION_TYPE:{
        uint32_t _dataLength = 4;
        writeValue(data, _dataLength, _globalVariables->flashOperationType);
        #if (ADC_STRAIN_TYPE == ADC_STRAIN_TYPE_ADS8320)
        ADCext.setFlashOperationType(_globalVariables->flashOperationType);
        #else
        ADS869xStrain.setFlashOperationType(_globalVariables->flashOperationType);
        #endif
        ADCextExtens.setFlashOperationType(_globalVariables->flashOperationType);
        break;
      }
      case COMMAND::GET_FLASH_OPERATION_TYPE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->flashOperationType);
        break;
      }
      case COMMAND::SET_GLOBAL_VARIABLE:{
        uint32_t index = 0;
        basic.writeBytesBufferToValue<uint32_t>(data, &index);
        this->_globalVariablesInterface->writeValue(index, data + sizeof index, RAM_MEMORY_TYPE);
        break;
      }
      case COMMAND::GET_GLOBAL_VARIABLE:{
        uint32_t index = 0;
        basic.writeBytesBufferToValue<uint32_t>(data, &index);
        dataLength = this->_globalVariablesInterface->readValue(index, data + sizeof index, RAM_MEMORY_TYPE) + sizeof index;
        break;
      }
      case COMMAND::SET_TO_FLASH_GLOBAL_VARIABLE:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t index = 0;
        basic.writeBytesBufferToValue<uint32_t>(data, &index);
        this->_globalVariablesInterface->writeValue(index, data + sizeof index, FLASH_MEMORY_TYPE);
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::GET_FROM_FLASH_GLOBAL_VARIABLE:{
        uint32_t index = 0;
        basic.writeBytesBufferToValue<uint32_t>(data, &index);
        dataLength = this->_globalVariablesInterface->readValue(index, data + sizeof index, FLASH_MEMORY_TYPE) + sizeof index;
        break;
      }
      case COMMAND::ADD_GLOBAL_VARIABLE_TO_FLASH_SET_QUEUE:{
        _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
        uint32_t index = 0;
        basic.writeBytesBufferToValue<uint32_t>(data, &index);
        this->_globalVariablesInterface->writeValue(index, data + sizeof index, FLASH_MEMORY_QUEUE);
        _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
        break;
      }
      case COMMAND::START_SET_GLOBAL_VARIABLES:{
        uint32_t index = 7;
        data = 0;
        this->_globalVariablesInterface->writeValue(index, data + sizeof index, FLASH_MEMORY_SET);
        break;
      }

      case COMMAND::RESET_WARNING_ALARM_LIGHTS:{
        greenLED.write(1);
        yellowLED.write(0);
        redLED.write(0);
        #if (PROJECT_NAME == PROJECT_NAME_MPD)
        alarmLight.write(0);
        #endif
        break;
      }
//GET CMDs
      case COMMAND::GET_MODE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->Mode);
        break;
      }
      case COMMAND::GET_CURRENT_MODE_FREQ:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->currentModeFreq);
        break;
      }
      case COMMAND::GET_DATA_DECIMATION_COEFF:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->DataDecimationCoeff);
        break;
      }
      case COMMAND::GET_SIN_DISP_TCYCLE:{
        dataLength = basic.writeValueToBytesBuffer(data, NAN);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_TCYCLE:{
        dataLength = basic.writeValueToBytesBuffer(data, NAN);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_NUMBER_OF_CYCLES:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.NumberOfCycles);
        break;
      }
      case COMMAND::GET_SIN_DISP_NUMBER_OF_CYCLES:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.NumberOfCycles);
        break;
      }
      case COMMAND::GET_SINUS_BASED_STRAIN_NUMBER_OF_CYCLES:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.NumberOfCycles);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DISP_NUMBER_OF_CYCLES:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles);
        break;
      }
      case COMMAND::GET_SIN_DISP_MAX_DEVIATION:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.MaxDeviation);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_MAX_DEVIATION:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.MaxDeviation);
        break;
      }
      case COMMAND::GET_AVERAGE_POSITION_BUFFER_SIZE:{
        uint32_t value = _globalVariables->AveragePosition.getNumberOfValues();
        dataLength = basic.writeValueToBytesBuffer(data, value);
        break;
      }
      case COMMAND::GET_AVERAGE_STRAIN_BUFFER_SIZE:{
        uint32_t value = _globalVariables->AverageStrain.getNumberOfValues();
        dataLength = basic.writeValueToBytesBuffer(data, value);
        break;
      }
      case COMMAND::GET_AVERAGE_DEFORMATION_BUFFER_SIZE:{
        uint32_t value = _globalVariables->AverageDeformation.getNumberOfValues();
        dataLength = basic.writeValueToBytesBuffer(data, value);
        break;
      }
      case COMMAND::GET_WORK_MODE:{
        switch(_globalVariables->machineInfo.ethernetProtocolVersion){
          case DATA_EXCHANGE_PROTOCOL_VERSION_ZERO ... DATA_EXCHANGE_PROTOCOL_VERSION_FIRST:
            dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->WorkMode);
            break;
          default:{
            uint8_t dummy = (uint8_t)_globalVariables->WorkMode;
            dataLength = basic.writeValueToBytesBuffer(data, dummy);
            break;
          }
        }
        
        break;
      }
      case COMMAND::GET_SINUS_BASED_DISPL_TYPE_MODE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.ModeType);
        break;
      }
      case COMMAND::GET_SINUS_BASED_STRAIN_TYPE_MODE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.ModeType);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DEFORM_TYPE_MODE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.ModeType);
        break;
      } 
      case COMMAND::GET_TEST_SIN_SIGNAL:{
        int32_t value = _globalVariables->TestSignalInfo.type;
        dataLength = basic.writeValueToBytesBuffer(data, value);
        break; 
      }
      case COMMAND::GET_TEST_SIN_SIGNAL_AMPLITUDE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TestSignalInfo.sinSignalAmplitude);
        break;
      }
      case COMMAND::GET_TEST_SIN_SIGNAL_INCREMENT:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TestSignalInfo.sinSignalIncrement);
        break;
      }
      case COMMAND::GET_TEST_SIGNAL_STRAIN_VALUE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TestSignalInfo.constSignalStrain);
        break;
      }
      case COMMAND::GET_TEST_SIGNAL_POSITION_VALUE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TestSignalInfo.constSignalPosition);
        break;
      }
      case COMMAND::GET_TEST_SIGNAL_DEFORMATION_VALUE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TestSignalInfo.constSignalDeformation);
        break;
      }
      case COMMAND::GET_REFERENCE_VOLTAGE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ReferenceVoltage);
        break;
      }
      case COMMAND::GET_EXTENS_REFERENCE_VOLTAGE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ExtensRefVoltage);
        break;
      }
      case COMMAND::GET_DISPL_REFERENCE_VOLTAGE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->DisplRefVoltage);
        break;
      }
      case COMMAND::GET_DISPL_ENCODER_STEP_VALUE:{
        double value = displEncoder.getStepValue();
        basic.writeValueToBytesBuffer(data, value);
        dataLength = sizeof(value);
        break;
      }
      case COMMAND::GET_DEFORM_ENCODER_STEP_VALUE:{
        double value = deformEncoder.getStepValue();
        basic.writeValueToBytesBuffer(data, value);
        dataLength = sizeof(value);
        break;
      }
      case COMMAND::GET_TIME_MEASURE_ENABLE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TimeMeasure.enable);
        break;
      }
      case COMMAND::GET_HW_CMD:{
        //uint32_t _dataLength = 4;
        uint32_t hwCmd = HW_CMD_UNDEFINED;
        int32_t state = 0;
        writeValue(data, dataLength, hwCmd);
        //writeValue(data, _dataLength, state);
        switch (hwCmd)
        {
        case HW_CMD_0:
          //state = HwCmdFb0.read();
          break;
        case HW_CMD_1:
          state = HwCmdFb1.read();
          break;
        // case HW_CMD_2:
        //   state = HwCmdFb2.read();
        //   break;
        // case HW_CMD_3:
        //   state = HwCmdFb3.read();
        //   break;
        // case HW_CMD_4:
        //   state = HwCmdFb4.read();
        //   break;
#if (!(REMOTE_CONTROL_TYPE == REMOTE_CONTROL_TYPE_ENCODER))
        case HW_CMD_5:
          state = HwCmdFb5.read();
          break;
#endif
        case HW_CMD_6:
          state = HwCmdFb6.read();
          break;
        
        default:
          break;
        }
        //printf("GET_HWCMD:%d; state:%d\n\r", hwCmd, state);
        dataLength =  basic.writeValueToBytesBuffer(data    , hwCmd);
        dataLength += basic.writeValueToBytesBuffer(data + 4, state);
        //printf("datasize:%d;\n\r", dataLength);
        break;
      }
      case COMMAND::GET_SIN_DISPLACEMENT_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SINDisplacementModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SINDisplacementModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SINDisplacementModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SINDisplacementModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SINDisplacementModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SINDisplacementModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SINDisplacementModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SINDisplacementModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SINDisplacementModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, NAN);
        break;
      }
      case COMMAND::GET_SIN_BASED_DISP_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SinusBasedDisplacementModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SinusBasedDisplacementModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SinusBasedDisplacementModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SinusBasedDisplacementModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SinusBasedDisplacementModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, NAN);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->SinusBasedDisplacementModeParams.baseRatio);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->SinusBasedDisplacementModeParams.ModeType);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SINStrainModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SINStrainModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SINStrainModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SINStrainModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SINStrainModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SINStrainModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SINStrainModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SINStrainModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SINStrainModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, _globalVariables->SINStrainModeParams.SampleCut);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->SINStrainModeParams.SampleLength);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->SINStrainModeParams.YoungModulus);
        dataLength += basic.writeValueToBytesBuffer(data + 96, NAN);
        break;
      }
       case COMMAND::GET_SIN_BASED_STRAIN_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SinusBasedStrainModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SinusBasedStrainModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SinusBasedStrainModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SinusBasedStrainModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SinusBasedStrainModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SinusBasedStrainModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SinusBasedStrainModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, _globalVariables->SinusBasedStrainModeParams.SampleCut);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->SinusBasedStrainModeParams.SampleLength);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->SinusBasedStrainModeParams.YoungModulus);
        dataLength += basic.writeValueToBytesBuffer(data + 96, NAN);
        dataLength += basic.writeValueToBytesBuffer(data + 104, _globalVariables->SinusBasedStrainModeParams.baseRatio);
        dataLength += basic.writeValueToBytesBuffer(data + 112, _globalVariables->SinusBasedStrainModeParams.ModeType);
        break;
      }
      case COMMAND::GET_CONST_STRAIN_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->ConstStrainModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->ConstStrainModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->ConstStrainModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->ConstStrainModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->ConstStrainModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->ConstStrainModeParams.StrainToHold);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->ConstStrainModeParams.SampleCut);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->ConstStrainModeParams.SampleLength);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->ConstStrainModeParams.YoungModulus);
        dataLength += basic.writeValueToBytesBuffer(data + 72, _globalVariables->ConstStrainModeParams.Speed);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->ConstStrainModeParams.MaxSpeed);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->ConstStrainModeParams.delta);
        break;
      }
      case COMMAND::GET_CONST_DISPLACEMENT_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->ConstDisplacementModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->ConstDisplacementModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->ConstDisplacementModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->ConstDisplacementModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->ConstDisplacementModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->ConstDisplacementModeParams.Speed);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->ConstDisplacementModeParams.MaxSpeed);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->ConstDisplacementModeParams.delta);
        break;
      }
      case COMMAND::GET_CONST_DEFORMATION_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->ConstDeformationModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->ConstDeformationModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->ConstDeformationModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->ConstDeformationModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->ConstDeformationModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->ConstDeformationModeParams.Speed);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->ConstDeformationModeParams.MaxSpeed);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->ConstDeformationModeParams.delta);
        break;
      }
        case COMMAND::GET_SIN_DEFORMATION_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SINDeformationModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SINDeformationModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SINDeformationModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SINDeformationModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SINDeformationModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SINDeformationModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SINDeformationModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SINDeformationModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SINDeformationModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, NAN);
        break;
      }
      case COMMAND::GET_SIN_BASED_DEFORM_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SinusBasedDeformationModeParams.SINFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SinusBasedDeformationModeParams.ModeFrequency);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SinusBasedDeformationModeParams.MaxDeviation);
        dataLength += basic.writeValueToBytesBuffer(data + 72, NAN);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->SinusBasedDeformationModeParams.baseRatio);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->SinusBasedDeformationModeParams.ModeType);
        break;
      }      
      case COMMAND::GET_TIME_MEASURE_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->TimeMeasure.startMeasurePosition);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->TimeMeasure.endMeasurePosition);
        break;
      }
      case COMMAND::GET_SIN_DISP_PID_KP:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.PIDParams.Kp);
        break;
      }
      case COMMAND::GET_SIN_DISP_PID_KI:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.PIDParams.Ki);
        break;
      }
      case COMMAND::GET_SIN_DISP_PID_KD:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.PIDParams.Kd);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DISP_PID_KP:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DISP_PID_KI:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DISP_PID_KD:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd);
        break;
      }

      case COMMAND::GET_SIN_STRAIN_PID_KP:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.PIDParams.Kp);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_PID_KI:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.PIDParams.Ki);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_PID_KD:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.PIDParams.Kd);
        break;
      }
      case COMMAND::GET_SINUS_BASED_STRAIN_PID_KP:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kp);
        break;
      }
      case COMMAND::GET_SINUS_BASED_STRAIN_PID_KI:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.PIDParams.Ki);
        break;
      }
      case COMMAND::GET_SINUS_BASED_STRAIN_PID_KD:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.PIDParams.Kd);
        break;
      }
      case COMMAND::GET_CONST_DISP_PID_KP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDisplacementModeParams.PIDParams.Kp);
        break;
      case COMMAND::GET_CONST_DISP_PID_KI:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDisplacementModeParams.PIDParams.Ki);
        break;
      case COMMAND::GET_CONST_DISP_PID_KD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDisplacementModeParams.PIDParams.Kd);
        break;
      case COMMAND::GET_CONST_STRAIN_PID_KP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstStrainModeParams.PIDParams.Kp);
        break;
      case COMMAND::GET_CONST_STRAIN_PID_KI:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstStrainModeParams.PIDParams.Ki);
        break;
      case COMMAND::GET_CONST_STRAIN_PID_KD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstStrainModeParams.PIDParams.Kd);
        break;
      //SINUS DEFORMATION MODE
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE:
        dataLength =  basic.writeValueToBytesBuffer(data    , _globalVariables->SINDeformationModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8, _globalVariables->SINDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::GET_SIN_DEFORM_FREQUENCY:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.SINFrequency);
        break;
      case COMMAND::GET_SIN_DEFORM_MODE_FREQUENCY:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::GET_SIN_DEFORM_PID_KP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::GET_SIN_DEFORM_PID_KI:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::GET_SIN_DEFORM_PID_KD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.PIDParams.Kd);
        break;
      case COMMAND::GET_SIN_DEFORM_TCYCLE:
        dataLength = basic.writeValueToBytesBuffer(data, NAN);
        break;
      case COMMAND::GET_SIN_DEFORM_NUMBER_OF_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.NumberOfCycles);
        break;
      case COMMAND::GET_SIN_DEFORM_MAX_DEVIATION:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.MaxDeviation);
        break;
      case COMMAND::GET_SIN_DEFORM_UP_AMPLITUDE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.UpAmplitude);
        break;
      case COMMAND::GET_SIN_DEFORM_DOWN_AMPLITUDE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_ENABLE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.state);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_THREAD_FREQ:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.freq);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_PID_COEFS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKP);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKI);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKD);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKP);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKI);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_CORRECTION_TYPE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.correctionType);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_WAIT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.waitCycles);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_RISE_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_FALL_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_SMOOTH_START:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.startProcess);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_SMOOTH_STOP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.stopProcess);
        break;
      case COMMAND::GET_SIN_DEFORM_AMPLITUDE_TUNE_MAIN_CORRECTION:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.amplitudeTuneInfo.mainProcess);
        break;
      //CONST DEFORMATION MODE
      case COMMAND::GET_CONST_DEFORM_MODE_FREQUENCY:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::GET_CONST_DEFORM_PID_KP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::GET_CONST_DEFORM_PID_KI:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::GET_CONST_DEFORM_PID_KD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.PIDParams.Kd);
        break;
      case COMMAND::GET_CONST_DEFORM_MAX_DEVIATION:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.MaxDeviation);
        break;
      case COMMAND::GET_CONST_DEFORM_DEFORMATION_TO_HOLD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDeformationModeParams.DeformationToHold);
        break;
      //SINUS BASED DEFORMATION MODE
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPLITUDE:
        dataLength =  basic.writeValueToBytesBuffer(data    , _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        dataLength += basic.writeValueToBytesBuffer(data + 8, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_FREQUENCY:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.SINFrequency);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_MODE_FREQUENCY:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.ModeFrequency);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_PID_KP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_PID_KI:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_PID_KD:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_TCYCLE:
        dataLength = basic.writeValueToBytesBuffer(data, NAN);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_NUMBER_OF_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_MAX_DEVIATION:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.MaxDeviation);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_UP_AMPLITUDE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.UpAmplitude);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_DOWN_AMPLITUDE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.DownAmplitude);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_ENABLE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.state);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_THREAD_FREQ:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.freq);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_PID_COEFS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD);
        break;
      }
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_CORRECTION_TYPE:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.correctionType);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_WAIT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.waitCycles);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_RISE_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeRiseCycles);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_FALL_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.amplitudeFallCycles);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_SMOOTH_START:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.startProcess);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_SMOOTH_STOP:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.stopProcess);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_AMPL_TUNE_MAIN_CORRECTION:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.mainProcess);
        break;      

      //GET without set pair
      case COMMAND::GET_NULL_POINT:{
        double _nullPointPosition, _nullPointStrain, _nullPointDeformation;
        switch (_globalVariables->Mode)
        {
        case DAC_STATE_DISP_SIN:
          _nullPointPosition =    _globalVariables->SINDisplacementModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SINDisplacementModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SINDisplacementModeParams.NullPointDeformation;
          break;
        case DAC_STATE_DISP_SINUS_BASED:
          _nullPointPosition =    _globalVariables->SinusBasedDisplacementModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SinusBasedDisplacementModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SinusBasedDisplacementModeParams.NullPointDeformation;
          break;
        case DAC_STATE_STRAIN_SIN:
          _nullPointPosition =    _globalVariables->SINStrainModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SINStrainModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SINStrainModeParams.NullPointDeformation;
          break;
        case DAC_STATE_STRAIN_SINUS_BASED:
          _nullPointPosition =    _globalVariables->SinusBasedStrainModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SinusBasedStrainModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SinusBasedStrainModeParams.NullPointDeformation;
          break;
        case DAC_STATE_DEFORMATION_SIN:
          _nullPointPosition =    _globalVariables->SinusBasedDeformationModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SinusBasedDeformationModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SinusBasedDeformationModeParams.NullPointDeformation;
          break;
        case DAC_STATE_DEFORMATION_SINUS_BASED:
          _nullPointPosition =    _globalVariables->SINDeformationModeParams.NullPointDisplacement;
          _nullPointStrain =      _globalVariables->SINDeformationModeParams.NullPointStrain;
          _nullPointDeformation = _globalVariables->SINDeformationModeParams.NullPointDeformation;
          break;
        default:
          _nullPointPosition    = _globalVariables->AveragePosition.get();
          _nullPointStrain      = _globalVariables->AverageStrain.get();
          _nullPointDeformation = _globalVariables->AverageDeformation.get();
          break;
        }
        dataLength =  basic.writeValueToBytesBuffer(data    ,   _nullPointPosition);
        dataLength += basic.writeValueToBytesBuffer(data + 8,   _nullPointStrain);
        dataLength += basic.writeValueToBytesBuffer(data + 16,  _nullPointDeformation);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.NullPoint, data);
        break;
      }
      case COMMAND::GET_CURRENT_TEST_STEP:{
        //DEPRECATED
        //dataLength = basic.writeValueToBytesBuffer(data, (int32_t)_globalVariables->currentStaticTestStep);
        break;
      }
      case COMMAND::SET_TCYCLE:{
        if(dataLength == sizeof (us_timestamp_t)){
          task = Task::SET_TCYCLE;
          this->addTask(task, data, dataLength);
        }else{
          EthernetAnswerMail_t *EthernetAnswerMail = EthernetAnswerMailBox.try_alloc_for(0ms);
          EthernetAnswerMail->command = COMMAND::TM_ONCE_SET_TCYCLE_COMPLETE;
          EthernetAnswerMail->dataLength = 4;
          //error status -1
          basic.writeValueToBytesBuffer(EthernetAnswerMail->data, (uint32_t)(ERROR_DURING_SET_TCYCLE));
          EthernetAnswerMailBox.put(EthernetAnswerMail);
        }
        break;
      }
      case COMMAND::ADD_FILTER_TYPE_AND_RANGE_AT_END:{
        task = Task::ADD_FILTER_TYPE_AND_RANGE_AT_END;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::ADD_FILTER_TYPE_AND_RANGE_AT_INDEX:{
        task = Task::ADD_FILTER_TYPE_AND_RANGE_AT_INDEX;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::REMOOVE_FILTER_BY_PARAMETER:{
        task = Task::REMOOVE_FILTER_BY_PARAMETER;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::ORDERING_ONE_AFTER_ANOTHER_BY_PARAMETER:{
        task = Task::ORDERING_ONE_AFTER_ANOTHER_BY_PARAMETER;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::ADD_SIN_DISPL_NULL_POINT:{
        task = Task::ADD_SIN_DISPL_NULL_POINT;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_FILTERING_ACTIVITY_UNIT:{
        task = Task::SET_FILTERING_ACTIVITY_UNIT;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_FILTERING_ACTIVITY_DATA_LINE:{
        task = Task::SET_FILTERING_ACTIVITY_DATA_LINE;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::SET_FILTERING_ACTIVITY_ALL:{
        task = Task::SET_FILTERING_ACTIVITY_ALL;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::GET_TCYCLE:{
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->TcycleTime);
        break;
      }
      case COMMAND::GET_FILTER_SET_STATUS_BY_DATATYPE:{
        uint32_t _dataLength = 4;
        uint32_t typeOfFilteredData;
        writeValue(data, _dataLength, typeOfFilteredData);
        // ExeThr->makingDataCharBufferFromParameters((uint32_t)0, dataLength, data, 
        //   ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 0),
        //   ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 0),
        //   ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 1),
        //   ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 1),
        //   ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 2),
        //   ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 2),
        //   ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 3),
        //   ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 3),
        //   ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 4),
        //   ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 4));
        dataLength =  basic.writeValueToBytesBuffer(data     , ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 0));
        dataLength += basic.writeValueToBytesBuffer(data + 4 , ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 0));
        dataLength += basic.writeValueToBytesBuffer(data + 8, ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 1));
        dataLength += basic.writeValueToBytesBuffer(data + 12, ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 1));
        dataLength += basic.writeValueToBytesBuffer(data + 16, ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 2));
        dataLength += basic.writeValueToBytesBuffer(data + 20, ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 2));
        dataLength += basic.writeValueToBytesBuffer(data + 24, ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 3));
        dataLength += basic.writeValueToBytesBuffer(data + 28, ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 3));
        dataLength += basic.writeValueToBytesBuffer(data + 32, ExeThr->dataFiltersSet->getTypeOfFilterInSet(typeOfFilteredData, 4));
        dataLength += basic.writeValueToBytesBuffer(data + 36, ExeThr->dataFiltersSet->getRangeOfFilterFromSet(typeOfFilteredData, 4));
        break;
      }
      case COMMAND::GET_ACTIVITYES_SET_STATUS_BY_DATATYPE:{
        uint32_t _dataLength = 4;
        uint32_t typeOfFilteredData;
        writeValue(data, _dataLength, typeOfFilteredData);
        // ExeThr->makingDataCharBufferFromParameters((uint32_t)0, dataLength, data, 
        //   ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][DIRECTING],
        //   ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][MONITORING],
        //   ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][ANSWERING],
        //   ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][DISPLAYING]);
        dataLength =  basic.writeValueToBytesBuffer(data     , ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][DIRECTING]);
        dataLength += basic.writeValueToBytesBuffer(data + 1 , ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][MONITORING]);
        dataLength += basic.writeValueToBytesBuffer(data + 2, ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][ANSWERING]);
        dataLength += basic.writeValueToBytesBuffer(data + 3, ExeThr->switcherFilterSet->activityTypes[typeOfFilteredData-1][DISPLAYING]);
        break;
      }
      case COMMAND::GET_SIN_STRAIN_NULL_POINT:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.NullPointStrain);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINStrainModeParams.NullPoint, data);
        break;
      case COMMAND::GET_SIN_DISP_NULL_POINT:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.NullPointDisplacement);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINStrainModeParams.NullPoint, data);
        break;
      case COMMAND::GET_SIN_DEFORM_NULL_POINT:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.NullPointDeformation);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINStrainModeParams.NullPoint, data);
        break;
      // case COMMAND_GET_DELTA_POINT:
      //   dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->DeltaPoints);
      //   //dataLength = basic.writeValueToBytesBuffer(_globalVariables->DeltaPoints, data);
      //   break;
      case COMMAND::GET_CURRENT_CYCLES:{
        long long _currentCycles;
        switch (_globalVariables->Mode)
        {
        case DAC_STATE_DISP_SIN:
          _currentCycles = _globalVariables->SINDisplacementModeParams.InternalCounter;
          break;
        case DAC_STATE_STRAIN_SIN:
          _currentCycles = _globalVariables->SINStrainModeParams.InternalCounter;
          break;
        case DAC_STATE_DISP_SINUS_BASED:
          _currentCycles = _globalVariables->SinusBasedDisplacementModeParams.InternalCounter;
          break;
        case DAC_STATE_STRAIN_SINUS_BASED:
          _currentCycles = _globalVariables->SinusBasedStrainModeParams.InternalCounter;
          break;  
        case DAC_STATE_DEFORMATION_SIN:
          _currentCycles = _globalVariables->SINDeformationModeParams.InternalCounter;
          break;
        case DAC_STATE_DEFORMATION_SINUS_BASED:
          _currentCycles = _globalVariables->SinusBasedDeformationModeParams.InternalCounter;
          break;
        default:
          _currentCycles = 0;
          break;
        }
        dataLength = basic.writeValueToBytesBuffer(data, _currentCycles);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      }
      case COMMAND::GET_NUMBER_OF_CYCLES:{
        long long _numberOfCycles;
        switch (_globalVariables->Mode)
        {
        case DAC_STATE_DISP_SIN:
          _numberOfCycles = _globalVariables->SINDisplacementModeParams.NumberOfCycles;
          break;
        case DAC_STATE_STRAIN_SIN:
          _numberOfCycles = _globalVariables->SINStrainModeParams.NumberOfCycles;
          break;
        case DAC_STATE_DISP_SINUS_BASED:
          _numberOfCycles = _globalVariables->SinusBasedDisplacementModeParams.NumberOfCycles;
          break;
        case DAC_STATE_STRAIN_SINUS_BASED:
          _numberOfCycles = _globalVariables->SinusBasedStrainModeParams.NumberOfCycles;
          break;  
        case DAC_STATE_DEFORMATION_SIN:
          _numberOfCycles = _globalVariables->SINDeformationModeParams.NumberOfCycles;
          break;
        case DAC_STATE_DEFORMATION_SINUS_BASED:
          _numberOfCycles = _globalVariables->SinusBasedDeformationModeParams.NumberOfCycles;
          break;
        default:
          _numberOfCycles = 0;
          break;
        }
        dataLength = basic.writeValueToBytesBuffer(data, _numberOfCycles);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      }
      case COMMAND::GET_SIN_DISP_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDisplacementModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SIN_STRAIN_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINStrainModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINStrainModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SIN_DEFORM_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SINDeformationModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SINUS_BASED_DISP_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDisplacementModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SINUS_BASED_STRAIN_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedStrainModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SINUS_BASED_DEFORM_CURRENT_CYCLES:
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->SinusBasedDeformationModeParams.InternalCounter);
        //dataLength = basic.writeValueToBytesBuffer(_globalVariables->SINDisplacementModeParams.InternalCounter - 1, data);
        break;
      case COMMAND::GET_SAMPLE_HARDNESS_INFO:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->SampleHardnessInfo.edgeValue1);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->SampleHardnessInfo.edgeValue2);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->SampleHardnessInfo.edgeValue3);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->SampleHardnessInfo.edgeValue4);
        dataLength += basic.writeValueToBytesBuffer(data + 32, _globalVariables->SampleHardnessInfo.edgeValue5);
        dataLength += basic.writeValueToBytesBuffer(data + 40, _globalVariables->SampleHardnessInfo.initialPosition);
        dataLength += basic.writeValueToBytesBuffer(data + 48, _globalVariables->SampleHardnessInfo.speed);
        dataLength += basic.writeValueToBytesBuffer(data + 56, _globalVariables->SampleHardnessInfo.p1.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 64, _globalVariables->SampleHardnessInfo.p1.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 72, _globalVariables->SampleHardnessInfo.p1.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 80, _globalVariables->SampleHardnessInfo.p1.time);
        dataLength += basic.writeValueToBytesBuffer(data + 88, _globalVariables->SampleHardnessInfo.p2.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 96, _globalVariables->SampleHardnessInfo.p2.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 104, _globalVariables->SampleHardnessInfo.p2.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 112, _globalVariables->SampleHardnessInfo.p2.time);
        dataLength += basic.writeValueToBytesBuffer(data + 120, _globalVariables->SampleHardnessInfo.p3.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 128, _globalVariables->SampleHardnessInfo.p3.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 136, _globalVariables->SampleHardnessInfo.p3.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 144, _globalVariables->SampleHardnessInfo.p3.time);
        dataLength += basic.writeValueToBytesBuffer(data + 152, _globalVariables->SampleHardnessInfo.p4.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 160, _globalVariables->SampleHardnessInfo.p4.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 168, _globalVariables->SampleHardnessInfo.p4.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 176, _globalVariables->SampleHardnessInfo.p4.time);
        dataLength += basic.writeValueToBytesBuffer(data + 184, _globalVariables->SampleHardnessInfo.p5.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 192, _globalVariables->SampleHardnessInfo.p5.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 200, _globalVariables->SampleHardnessInfo.p5.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 208, _globalVariables->SampleHardnessInfo.p5.time);
        dataLength += basic.writeValueToBytesBuffer(data + 216, _globalVariables->SampleHardnessInfo.p6.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 224, _globalVariables->SampleHardnessInfo.p6.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 232, _globalVariables->SampleHardnessInfo.p6.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 240, _globalVariables->SampleHardnessInfo.p6.time);
        dataLength += basic.writeValueToBytesBuffer(data + 248, _globalVariables->SampleHardnessInfo.p7.alpha);
        dataLength += basic.writeValueToBytesBuffer(data + 256, _globalVariables->SampleHardnessInfo.p7.displ);
        dataLength += basic.writeValueToBytesBuffer(data + 264, _globalVariables->SampleHardnessInfo.p7.strain);
        dataLength += basic.writeValueToBytesBuffer(data + 272, _globalVariables->SampleHardnessInfo.p7.time);
        break;
      }
      case COMMAND::GET_MACHINE_PARAMS:{
        dataLength =  basic.writeValueToBytesBuffer(data     , _globalVariables->valveDirectionMode);
        dataLength += basic.writeValueToBytesBuffer(data + 4 , _globalVariables->pistonMode);
        dataLength += basic.writeValueToBytesBuffer(data + 8 , _globalVariables->positionInvertAxis);
        dataLength += basic.writeValueToBytesBuffer(data + 12, _globalVariables->positionAxisMode);
        dataLength += basic.writeValueToBytesBuffer(data + 16, _globalVariables->strainInvertAxis);
        dataLength += basic.writeValueToBytesBuffer(data + 20, _globalVariables->strainAxisMode);
        dataLength += basic.writeValueToBytesBuffer(data + 24, _globalVariables->deformationInvertAxis);
        dataLength += basic.writeValueToBytesBuffer(data + 28, _globalVariables->deformationAxisMode);
        break;
      }
      case COMMAND::GET_SIN_DISP_LAST_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , displMaxMinCalc.getLastMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, displMaxMinCalc.getLastMinValue());
        break;
      }
      case COMMAND::GET_SIN_DISP_AVERAGE_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , displMaxMinCalc.getAverageMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, displMaxMinCalc.getAverageMinValue());
        break;
      }
      case COMMAND::GET_SIN_STRAIN_LAST_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , strainMaxMinCalc.getLastMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, strainMaxMinCalc.getLastMinValue());
        break;
      }
      case COMMAND::GET_SIN_STRAIN_AVERAGE_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , strainMaxMinCalc.getAverageMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, strainMaxMinCalc.getAverageMinValue());
        break;
      }
      case COMMAND::GET_SIN_DEFORM_LAST_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , deformationMaxMinCalc.getLastMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, deformationMaxMinCalc.getLastMinValue());
        break;
      }
      case COMMAND::GET_SIN_DEFORM_AVERAGE_MAX_MIN:{
         dataLength =  basic.writeValueToBytesBuffer(data     , deformationMaxMinCalc.getAverageMaxValue());
         dataLength += basic.writeValueToBytesBuffer(data +  4, deformationMaxMinCalc.getAverageMinValue());
        break;
      }
      //SYSTEM FEATURES
      case COMMAND::SYSTEM_PERFORM_SOFTWARE_RESET:{
        __NVIC_SystemReset();
        break;
      }
      case COMMAND::SYSTEM_CHANGE_ETHERNET_PROTOCOL:{
        task = Task::CHANGE_ETHERNET_PROTOCOL_VERSION;
        this->addTask(task, data, dataLength);
        break;
      }
      case COMMAND::GET_CONST_DISP_SET_SPEED: {
        dataLength = basic.writeValueToBytesBuffer(data, _globalVariables->ConstDisplacementModeParams.Speed);
        break;
      }
	  case COMMAND::REMOTE_CONTROLLER_START_TEST: {
		task = Task::START_TEST_BY_REMOTE_CONTROLLER;
        this->addTask(task, data, dataLength);
		break;
	  }
	  case COMMAND::REMOTE_CONTROLLER_STOP_TEST: {
		task = Task::STOP_TEST_BY_REMOTE_CONTROLLER;
        this->addTask(task, data, dataLength);
		break;
	  }
	  case COMMAND::SET_CONST_DISP_POSITION_TO_HOLD_WITH_ACCEPT:{
        //_globalVariables->ConstDisplacementModeParams.speedEnable = false;
        //writeValue(data, dataLength, _globalVariables->ConstDisplacementModeParams.PositionToHold);
        //_globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
		this->positionToHoldTimeout->detach();
        this->positionToHoldTimeout->attach(callback(this, &EthernetParser::stopPiston), 500ms);
        break;
      }
      //DEFAULT CASE
      default:
        dataLength = 0;
        break;
      }
    return error;
}

//check next mode to reset
void EthernetParser::checkResetMode(uint32_t nextMode){
  //reset sinus displacement mode
  if (nextMode == DAC_STATE_STRAIN_SIN){
    _globalVariables->SINStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DISP_SIN){
    _globalVariables->SINDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_STRAIN_SINUS_BASED){
    _globalVariables->SinusBasedStrainModeParams.State = SIN_STRAIN_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DISP_SINUS_BASED){
    _globalVariables->SinusBasedDisplacementModeParams.State = SIN_DISPLACEMENT_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DISP_CONST){
    _globalVariables->ConstDisplacementModeParams.speedEnable = false;
    _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_STRAIN_CONST){
    _globalVariables->ConstStrainModeParams.speedEnable = false;
    _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DEFORMATION_CONST){
    _globalVariables->ConstDeformationModeParams.speedEnable = false;
    _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DEFORMATION_SIN){
    _globalVariables->SINDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
  }
  if (nextMode == DAC_STATE_DEFORMATION_SINUS_BASED){
    _globalVariables->SinusBasedDeformationModeParams.State = SIN_DEFORMATION_MODE_STATE_RESET;
  }
}

void EthernetParser::resetEmergencyButton(void){
  HwCmd5.write(1);
}

void EthernetParser::writeValueLikeCharBuffer(uint32_t limit, uint32_t dataLength, char *data){
    //printf(" Time-%10.10d \n", (int)SystemTimer.elapsed_time().count());
    _globalVariables -> flashWriteModeTcycleSet(ExeThr, &ExecutionThread::calculateNextPoint);
    uint32_t index = 0;
    basic.writeBytesBufferToValue<uint32_t>(data, &index);
    uint8_t numberOfChars = dataLength - sizeof(index);
    //printf(" numberW_raw-%10.10d \n", numberOfChars);
    if (numberOfChars >= (uint8_t)limit){
      numberOfChars = (uint8_t)limit - 1;
    }
    //printf(" numberW-%10.10d \n", numberOfChars);
    char *tmpBuff = new char[numberOfChars + 1];
    if (tmpBuff){
      tmpBuff[0] = numberOfChars;
      for (int i = 0; i < numberOfChars; i++){
        tmpBuff[i+1] = *(data + sizeof index + i);
      }
      uint8_t tmp = 0;
      this->_globalVariablesInterface->sizeOfCharBuffer = numberOfChars + 1;
      this->_globalVariablesInterface->ptrOnCharBuffer = tmpBuff;
      this->_globalVariablesInterface->writeValue<uint8_t>(index, tmp, FLASH_MEMORY_CHAR_ARRAY);
    }
    delete[] tmpBuff;
    _globalVariables -> flashWriteModeTcycleReset(ExeThr, &ExecutionThread::calculateNextPoint);
    //printf(" Time-%10.10d \n", (int)SystemTimer.elapsed_time().count());
}

void EthernetParser::readValueLikeCharBuffer(uint32_t& dataLength, char *data){
    uint32_t index = 0;
    basic.writeBytesBufferToValue<uint32_t>(data, &index);
    int tmp = 0;
    uint8_t charFromFlash = 0;
    uint8_t valuesSize = this->_globalVariablesInterface->readValue<uint8_t>(index, FLASH_MEMORY_TYPE, tmp, 0);
    for (uint8_t i = 0; i < valuesSize; i ++){
      charFromFlash = this->_globalVariablesInterface->readValue<uint8_t>(index, FLASH_MEMORY_TYPE, tmp, i + 1);
      *(data + sizeof index + i) = charFromFlash;  
    }
    dataLength = sizeof index + valuesSize;
}

void EthernetParser::stopPiston(void){
  _globalVariables->displSharedLowerLimit = NAN;
  _globalVariables->displSharedUpperLimit = NAN;
  _globalVariables->strainSharedLowerLimit = NAN;
  _globalVariables->strainSharedUpperLimit = NAN;
  _globalVariables->deformSharedLowerLimit = NAN;
  _globalVariables->deformSharedUpperLimit = NAN;
  _globalVariables->ConstDisplacementModeParams.speedEnable = false;
  _globalVariables->ConstDisplacementModeParams.PositionToHold = _globalVariables->roCurrentAvPosition;
  //_globalVariables->ConstDisplacementModeParams.nextDesirePoint = _globalVariables->roCurrentAvPosition;
  _globalVariables->ConstDisplacementModeParams.State = CONST_DISPLACEMENT_MODE_STATE_RESET;
  _globalVariables->ConstDisplacementModeParams.waitForPIDReset = true;
  if(_globalVariables->machineInfo.machineType == MACHINE_TYPE_ELECTRO_STATIC_MACHINE){
    _globalVariables->Mode = DAC_STATE_NONE;
  }
  if(_globalVariables->machineInfo.machineType == MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE){
    _globalVariables->Mode = DAC_STATE_CLOSE_VALVE;
    _globalVariables->closeValveState = CLOSE_VALVE_STATE_RESET;
  }
  if(_globalVariables->machineInfo.machineType == MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE){
    _globalVariables->Mode = DAC_STATE_DISP_CONST;
  }
}

void EthernetParser::stopPistonAtStrain(void){
  _globalVariables->displSharedLowerLimit = NAN;
  _globalVariables->displSharedUpperLimit = NAN;
  _globalVariables->strainSharedLowerLimit = NAN;
  _globalVariables->strainSharedUpperLimit = NAN;
  _globalVariables->deformSharedLowerLimit = NAN;
  _globalVariables->deformSharedUpperLimit = NAN;
  _globalVariables->ConstStrainModeParams.speedEnable = false;
  _globalVariables->ConstStrainModeParams.StrainToHold = _globalVariables->roCurrentAvStrain;
  //_globalVariables->ConstStrainModeParams.nextDesirePoint = _globalVariables->roCurrentAvPosition;
  _globalVariables->ConstStrainModeParams.State = CONST_STRAIN_MODE_STATE_RESET;
  //_globalVariables->ConstStrainModeParams.waitForPIDReset = true;
  _globalVariables->Mode = DAC_STATE_STRAIN_CONST;
}

void EthernetParser::stopPistonAtDeformation(void){
  _globalVariables->displSharedLowerLimit = NAN;
  _globalVariables->displSharedUpperLimit = NAN;
  _globalVariables->strainSharedLowerLimit = NAN;
  _globalVariables->strainSharedUpperLimit = NAN;
  _globalVariables->deformSharedLowerLimit = NAN;
  _globalVariables->deformSharedUpperLimit = NAN;
  _globalVariables->ConstDeformationModeParams.speedEnable = false;
  _globalVariables->ConstDeformationModeParams.DeformationToHold = _globalVariables->roCurrentAvDeformation;
  //_globalVariables->ConstStrainModeParams.nextDesirePoint = _globalVariables->roCurrentAvPosition;
  _globalVariables->ConstDeformationModeParams.State = CONST_DEFORMATION_MODE_STATE_RESET;
  //_globalVariables->ConstDeformationModeParams.waitForPIDReset = true;
  _globalVariables->Mode = DAC_STATE_DEFORMATION_CONST;
}