#ifndef GLOBAL_VARIABLES_INTERFACE_T_HPP
#define GLOBAL_VARIABLES_INTERFACE_T_HPP
#include "GlobalVariablesInterface.h"

template <typename T> void GlobalVariablesInterface::writeValue(uint32_t index, T value, memoryType_t memoryType){
    switch (index)
    {
    case GLOBAL_VARIABLES_POSITION_AXIS_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->positionAxisMode, POSITION_AXIS_MODE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STRAIN_AXIS_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->strainAxisMode, STRAIN_AXIS_MODE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_AXIS_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->deformationAxisMode, DEFORMATION_AXIS_MODE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_POSITION_INVERT_AXIS:
        this->writeValueImplementation<int>(this->_globalVariables->positionInvertAxis, POSITION_INVERT_AXIS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STRAIN_INVERT_AXIS:
        this->writeValueImplementation<int>(this->_globalVariables->strainInvertAxis, STRAIN_INVERT_AXIS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_INVERT_AXIS:
        this->writeValueImplementation<int>(this->_globalVariables->deformationInvertAxis, DEFORMATION_INVERT_AXIS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_PISTON_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->pistonMode, PISTON_MODE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_VALVE_DIRECTION_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->valveDirectionMode, VALVE_DIRECTION_MODE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA:
        this->writeValueImplementation<double>(this->_globalVariables->PistonParams.topArea, PISTON_PARAMS_TOP_AREA_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_PISTON_PARAMS_BOTTOM_AREA:
        this->writeValueImplementation<double>(this->_globalVariables->PistonParams.bottomArea, PISTON_PARAMS_BOTTOM_AREA_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_VALVE_PARAMS_IMAX:
        this->writeValueImplementation<double>(this->_globalVariables->ValveParams.Imax, VALVE_PARAMS_IMAX_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_VALVE_PARAMS_QVALVE:
        this->writeValueImplementation<double>(this->_globalVariables->ValveParams.Qvalve, VALVE_PARAMS_QVALVE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_POSITION_UPPER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->positionUpperThreshold, STATIC_TEST_POSITION_UPPER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_POSITION_LOWER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->positionLowerThreshold, STATIC_TEST_POSITION_LOWER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_STRAIN_UPPER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->strainUpperThreshold, STATIC_TEST_STRAIN_UPPER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_STRAIN_LOWER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->strainLowerThreshold, STATIC_TEST_STRAIN_LOWER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_UPPER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->deformationUpperThreshold, STATIC_TEST_DEFORMATION_UPPER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_LOWER_THRESHOLD:
        this->writeValueImplementation<double>(this->_globalVariables->deformationLowerThreshold, STATIC_TEST_DEFORMATION_LOWER_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_ENCODER_STEP_VALUE:
        this->writeValueImplementation<double>(this->_globalVariables->encoderStepValue, ENCODER_STEP_VALUE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->motorDriverType, MOTOR_DRIVER_TYPE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE:
        this->writeValueImplementation<int>(this->_globalVariables->controllerOnlineMode, CONTROLLER_ONLINE_MODE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MOTOR_STEP_VALUE:
        this->writeValueImplementation<double>(this->_globalVariables->motorStepValue, MOTOR_STEP_VALUE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1:
        this->writeValueImplementation<int>(this->_globalVariables->LimitSwitchPolarity1, LIMITSWITCH_POLARITY_1_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_2:
        this->writeValueImplementation<int>(this->_globalVariables->LimitSwitchPolarity2, LIMITSWITCH_POLARITY_2_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY:
        this->writeValueImplementation<int>(this->_globalVariables->EmergencyStopPolarity, EMERGENCY_STOP_POLARITY_OFFSET, value, memoryType);
        break;
	case GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE:
        this->writeValueImplementation<double>(this->_globalVariables->encoderExtensiaStepValue, DEFORMATION_ENCODER_STEP_VALUE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->displOverrunStepBack, DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_UNDERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->displUnderrunStepBack, DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STRAIN_OVERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->strainOverrunStepBack, STRAIN_OVERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STRAIN_UNDERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->strainUnderrunStepBack, STRAIN_UNDERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_OVERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->deformOverrunStepBack, DEFORMATION_OVERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_UNDERRUN_STEP_BACK:
        this->writeValueImplementation<double>(this->_globalVariables->deformUnderrunStepBack, DEFORMATION_UNDERRUN_STEP_BACK_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SSI_NULL_OFFSET:
        this->writeValueImplementation<double>(this->_globalVariables->SSINullOffset, SSI_NULL_OFFSET_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_PWM_FREQ:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->PWMFreq, PWM_FREQ_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SERIAL_NUMBER:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->machineInfo.serialNumber, SERIAL_NUMBER_FLASH_OFFSET, value, memoryType);
        break; 
    case GLOBAL_VARIABLES_ID:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->machineInfo.id, ID_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION:
        this->writeValueImplementation<uint16_t>(this->_globalVariables->machineInfo.ethernetProtocolVersion, ETHERNET_PROTOCOL_VERSION_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MACHINE_TYPE:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->machineInfo.machineType, MACHINE_TYPE_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.displacement.sensorType, DISPLACEMENT_CHANNEL_INFO_SENSOR_TYPE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_DISPLACEMENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.displacement.maxValue, DISPLACEMENT_CHANNEL_INFO_MAX_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_DISPLACEMENT_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.displacement.maxValueOverloadPercent, DISPLACEMENT_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_DISPLACEMENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.displacement.minValue, DISPLACEMENT_CHANNEL_INFO_MIN_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.displacement.minValueOverloadPercent, DISPLACEMENT_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    case GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.strain.sensorType, STRAIN_CHANNEL_INFO_SENSOR_TYPE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_STRAIN:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.strain.maxValue, STRAIN_CHANNEL_INFO_MAX_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_STRAIN_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.strain.maxValueOverloadPercent, STRAIN_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_STRAIN:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.strain.minValue, STRAIN_CHANNEL_INFO_MIN_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.strain.minValueOverloadPercent, STRAIN_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorType, DEFORMATION_CHANNEL_INFO_SENSOR_TYPE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_DEFORMATION:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.deformation.maxValue, DEFORMATION_CHANNEL_INFO_MAX_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_DEFORMATION_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.deformation.maxValueOverloadPercent, DEFORMATION_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_DEFORMATION:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.deformation.minValue, DEFORMATION_CHANNEL_INFO_MIN_VALUE, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT:
        this->writeValueImplementation<double>(this->_globalVariables->machineInfo.deformation.minValueOverloadPercent, DEFORMATION_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, value, memoryType);
        break;
    //PID
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Kp, SIN_DISPLASEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Ki, SIN_DISPLASEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Kd, SIN_DISPLASEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Kp, SIN_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Ki, SIN_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Kd, SIN_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Kp, SIN_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Ki, SIN_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Kd, SIN_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp, SINUS_BASED_DISPL_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki, SINUS_BASED_DISPL_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd, SINUS_BASED_DISPL_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp, SINUS_BASED_DEFORM_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki, SINUS_BASED_DEFORM_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd, SINUS_BASED_DEFORM_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Kp, SINUS_BASED_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Ki, SINUS_BASED_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Kd, SINUS_BASED_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break; 

    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Kp, CONST_DISPLACEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Ki, CONST_DISPLACEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;    
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Kd, CONST_DISPLACEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Kp, CONST_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break; 
    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Ki, CONST_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break; 
    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Kd, CONST_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;         

    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Kp, CONST_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Ki, CONST_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;     
    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Kd, CONST_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
                //MaxVoltages

    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.MaxVoltage, SIN_DISPLASEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.MaxVoltage, SIN_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.MaxVoltage, SIN_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxVoltage, SINUS_BASED_DISPL_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.MaxVoltage, SINUS_BASED_DEFORM_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.MaxVoltage, SINUS_BASED_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxVoltage, CONST_DISPLACEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxVoltage, CONST_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxVoltage, CONST_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT:
        this->writeValueImplementation<double>(this->_globalVariables->SINVoltageModeParams.MaxVoltage, SIN_VOLTAGE_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

       //Const displacement mode params
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxDeviation, CONST_DISPLACEMENT_MODE_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.ModeFrequency, CONST_DISPLACEMENT_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_SPEED:
       this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.Speed, CONST_DISPLACEMENT_MODE_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_SPEED:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxSpeed, CONST_DISPLACEMENT_MODE_MAX_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.delta, CONST_DISPLACEMENT_MODE_DELTA_PARAMS_FLASH_OFFSET, value, memoryType);
        break; 

        //Max Steps and delta
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.delta, CONST_STRAIN_MODE_DELTA_PARAMS_FLASH_OFFSET, value, memoryType);
        break;  
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.delta, CONST_DEFORMATION_MODE_DELTA_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SINDisplacementModeParams.MaxSteps, SIN_DISPLASEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SINDeformationModeParams.MaxSteps, SIN_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SINStrainModeParams.MaxSteps, SIN_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxSteps, SINUS_BASED_DISPL_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SinusBasedDeformationModeParams.MaxSteps, SINUS_BASED_DEFORM_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->SinusBasedStrainModeParams.MaxSteps, SINUS_BASED_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->ConstDisplacementModeParams.MaxSteps, CONST_DISPLACEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->ConstDeformationModeParams.MaxSteps, CONST_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP:
        this->writeValueImplementation<uint64_t>(this->_globalVariables->ConstStrainModeParams.MaxSteps, CONST_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;

        //TCycle time
    case GLOBAL_VARIABLES_T_CYCLE_TIME:
        this->writeValueImplementation<us_timestamp_t>(this->_globalVariables->TcycleTime, T_CYCLE_TIME_PARAMS_FLASH_OFFSET, value, memoryType);
        break;     
    case GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->ConstModeParams.ConstFrequency, CONST_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxDeviation, CONST_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.ModeFrequency, CONST_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_SPEED:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.Speed, CONST_STRAIN_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MAX_SPEED:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxSpeed, CONST_STRAIN_MAX_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_DELTA:
        this->writeValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.delta, CONST_STRAIN_DELTA_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxDeviation, CONST_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.ModeFrequency, CONST_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_SPEED:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.Speed, CONST_DEFORMATION_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_SPEED:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxSpeed, CONST_DEFORMATION_MAX_SPEED_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_DELTA:
        this->writeValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.delta, CONST_DEFORMATION_DELTA_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.MaxDeviation, SIN_DISPLASEMENT_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.ModeFrequency, SIN_DISPLASEMENT_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKP, SIN_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKP, SIN_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKI, SIN_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKI, SIN_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKD, SIN_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKD, SIN_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.MaxDeviation, SIN_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.ModeFrequency, SIN_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKP, SIN_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKP, SIN_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKI, SIN_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKI, SIN_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKD, SIN_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKD, SIN_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.MaxDeviation, SIN_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.ModeFrequency, SIN_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKP, SIN_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKP, SIN_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKI, SIN_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKI, SIN_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKD, SIN_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKD, SIN_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxDeviation, SIN_BASED_DISP_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.ModeFrequency, SIN_BASED_DISP_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.MaxDeviation, SIN_BASED_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.ModeFrequency, SIN_BASED_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_MAX_DEV:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.MaxDeviation, SIN_BASED_DEFORM_MAX_DEV_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_MODE_FREQ:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.ModeFrequency, SIN_BASED_DEFORM_MODE_FREQ_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[0], DEFORMATION_SENSOR_TYPE_CH1_FLASH_OFFSET, value, memoryType); 
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH2:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[1], DEFORMATION_SENSOR_TYPE_CH2_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH3:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[2], DEFORMATION_SENSOR_TYPE_CH3_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH4:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[3], DEFORMATION_SENSOR_TYPE_CH4_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.activeChannels, ACTIVE_DEFORMATION_CHANNELS_FLASH_OFFSET, value, memoryType);
        break;   
 	case GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE:
        this->writeValueImplementation<float>(this->_globalVariables->ReferenceVoltage, STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE:
        this->writeValueImplementation<float>(this->_globalVariables->ExtensRefVoltage, DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_REFERENCE_VOLTAGE:
        this->writeValueImplementation<float>(this->_globalVariables->DisplRefVoltage, POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET, value, memoryType);
        break;
        //SSI sensor resolution
    case GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION:
        this->writeValueImplementation<double>(this->_globalVariables->SSISensorResolution, SSI_SENSOR_RESOLUTION_FLASH_OFFSET, value, memoryType);     
        break;
        //strain button protection
    case GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT:
        this->writeValueImplementation<float>(this->_globalVariables->strainButtonUpperLimit, STRAIN_BUTTON_PROTECTION_UPPER_LIMIT, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT:
        this->writeValueImplementation<float>(this->_globalVariables->strainButtonLowerLimit, STRAIN_BUTTON_PROTECTION_LOWER_LIMIT, value, memoryType);     
        break;
	case GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->enableActiveLevel, ENABLE_ACTIVE_LEVEL_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CLR_ACTIVE_LEVEL:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->CLRActiveLevel, CLR_ACTIVE_LEVEL_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CWL_ACTIVE_LEVEL:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->CWLActiveLevel, CWL_ACTIVE_LEVEL_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->CCWLActiveLevel, CCWL_ACTIVE_LEVEL_FLASH_OFFSET, value, memoryType);
        break;
        //speed by button
    case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR:
        this->writeValueImplementation<float>(this->_globalVariables->displButtonRegularSpeed, REGULAR_SPEED_BY_BUTTON_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST:
        this->writeValueImplementation<float>(this->_globalVariables->displButtonFastSpeed, FAST_SPEED_BY_BUTTON_FLASH_OFFSET, value, memoryType);     
        break;
        //tcycle for flash writing
    case GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING:
        this->writeValueImplementation<us_timestamp_t>(this->_globalVariables->TcycleTimeFlashWriting, TCYCLE_FOR_FLASH_WRITING_FLASH_OFFSET, value, memoryType);     
        break;
        //cyclic delta for protection
    case GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA:
        this->writeValueImplementation<float>(this->_globalVariables->strainCyclicDelta, STRAIN_CYCLIC_DELTA_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_CYCLIC_DELTA:
        this->writeValueImplementation<float>(this->_globalVariables->displacementCyclicDelta, DISPLACEMENT_CYCLIC_DELTA_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA:
        this->writeValueImplementation<float>(this->_globalVariables->deformationCyclicDelta, DEFORMATION_CYCLIC_DELTA_FLASH_OFFSET, value, memoryType);     
        break;
        //calibration notes
    case GLOBAL_VARIABLES_STRAIN_CALIBRATION_NOTES:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, STRAIN_CALIBRATION_NOTES_FLASH_OFFSET, value, memoryType);  
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_CALIBRATION_NOTES:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, POSITION_CALIBRATION_NOTES_FLASH_OFFSET, value, memoryType);   
        break;
    case GLOBAL_VARIABLES_DEFORMATION_CALIBRATION_NOTES:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET, value, memoryType);    
        break;
    case GLOBAL_VARIABLES_DEFORMATION_2CH_CALIBRATION_NOTES:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_3CH_CALIBRATION_NOTES:
        this->writeValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MAX_POSITION:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->maxPosition, MAX_POSITION_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIDDLE_POSITION:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->middlePosition, MIDDLE_POSITION_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIDDLE_UP_THRESHOLD:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->middleUpThreshold, MIDDLE_UP_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MIDDLE_DOWN_THRESHOLD:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->middleDownThreshold, MIDDLE_DOWN_THRESHOLD_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_POSITION_DIVIDER:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->positionDivider, POSITION_DIVIDER_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_VALVE_INVERT_AXIS:
        this->writeValueImplementation<int>(this->_globalVariables->valveInvertAxis, VALVE_INVERT_AXIS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_PORT:
        this->writeValueImplementation<uint16_t>(this->_globalVariables->port, PORT_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->machineInfo.ethernetConnectionTimeoutStopTest, ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST_OFFSET, value, memoryType);
        break;
        //Amplitude attenuation coefs
    case GLOBAL_VARIABLES_MIN_DELTA_RATIO_FOR_NULLPOINT:
        this->writeValueImplementation<double>(this->_globalVariables->minDeltaRatioForNullPointAttenuating, MIN_DELTA_RATIO_FOR_NULLPOINT_ATTEN_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_DISPL_NULLPOINT:
        this->writeValueImplementation<double>(this->_globalVariables->minAmplForDisplNullPointAttenuating, MIN_AMPL_FOR_DISPL_NULLPOINT_ATTEN_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_DEFORM_NULLPOINT:
        this->writeValueImplementation<double>(this->_globalVariables->minAmplForDeformNullPointAttenuating, MIN_AMPL_FOR_DEFORM_NULLPOINT_ATTEN_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_STRAIN_NULLPOINT:
        this->writeValueImplementation<double>(this->_globalVariables->minAmplForStrainNullPointAttenuating, MIN_AMPL_FOR_STRAIN_NULLPOINT_ATTEN_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO:
        this->writeValueImplementation<double>(this->_globalVariables->startStopAmplitudeRatio, START_STOP_AMPLITUDE_RATIO_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP:
        this->writeValueImplementation<double>(this->_globalVariables->stopAmplitudeRatio, START_STOP_AMPLITUDE_RATIO_STOP_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_AMPLITUDE_PRECISION:
        this->writeValueImplementation<double>(this->_globalVariables->amplitudePrecision, AMPLITUDE_PRECISION_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT:
        this->writeValueImplementation<float>(this->_globalVariables->tresholdForNullPointDeltaAccept, TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->stepForNullPointGetCorrection, STEP_FOR_NULLPOINT_GET_CORRECTION_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->minMaxCalculatingCounts, MIN_MAX_CALCULATING_COUNTS_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC:
        this->writeValueImplementation<int>(this->_globalVariables->minMaxCalculatingCountsMainProcess, MIN_MAX_CALCULATING_COUNTS_MAIN_PROC_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START:
        this->writeValueImplementation<double>(this->_globalVariables->anchorSinFrequency, ANCHOR_SIN_FREQUENCY_START_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_STOP:
        this->writeValueImplementation<double>(this->_globalVariables->anchorSinFrequencyStop, ANCHOR_SIN_FREQUENCY_STOP_FLASH_OFFSET, value, memoryType);     
        break;
    case GLOBAL_VARIABLES_MIDDLE_PISTON_POSITION:
        this->writeValueImplementation<double>(this->_globalVariables->middlePistonPosition, MIDDLE_PISTON_POSITION_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_UNITS:
        this->writeValueImplementation<uint32_t>(this->_globalVariables->DeformationUnits, DEFORMATION_UNITS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKP, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKI, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKD, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKP, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKI, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKD, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKP, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKI, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKD, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD:
        this->writeValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, value, memoryType);
        break;
    
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT:
        this->writeValueImplementation<double>(this->_globalVariables->blindePartOfCyclicStrainProtection, BLINDE_PART_CYCL_STRAIN_PRPOT_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT:
        this->writeValueImplementation<double>(this->_globalVariables->defaultBlindePartOfCyclicStrainProtection, BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST:
        this->writeValueImplementation<double>(this->_globalVariables->blindePartOfCyclicStrainProtectionFirst, BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST:
        this->writeValueImplementation<double>(this->_globalVariables->defaultBlindePartOfCyclicStrainProtectionFirst, BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION:
        this->writeValueImplementation<double>(this->_globalVariables->deltaCyclicProtection, DELTA_CYCLIC_PROTECTION_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION_DEFAULT:
        this->writeValueImplementation<double>(this->_globalVariables->deltaCyclicProtectionDefault, DELTA_CYCLIC_PROTECTION_DEFAULT_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MULTIPLIER:
        this->writeValueImplementation<double>(this->_globalVariables->multiplier, MULTIPLIER_FLASH_OFFS, value, memoryType);
        break;
    case GLOBAL_VARIABLES_MULTIPLIER_DEFAULT:
        this->writeValueImplementation<double>(this->_globalVariables->multiplierDefault, MULTIPLIER_DEFAULT_FLASH_OFFS, value, memoryType);
        break;
    default:
        break;
    }
}

// template <typename T> void GlobalVariablesInterface::writeValue(uint32_t index, T value, memoryType_t memoryType, uint8_t exstraFlashOffset){
//     switch (index){
    
//     default:
//         break;
//     }
// }

template <typename T> T GlobalVariablesInterface::readValue(uint32_t index, memoryType_t memoryType){
    int size = 0;
    return this->readValue<T>(index, memoryType, size);
}

template <typename T> T GlobalVariablesInterface::readValue(uint32_t index, memoryType_t memoryType, int &size){
    switch (index)
    {
    case GLOBAL_VARIABLES_POSITION_AXIS_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->positionAxisMode, POSITION_AXIS_MODE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_AXIS_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->strainAxisMode, STRAIN_AXIS_MODE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_AXIS_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->deformationAxisMode, DEFORMATION_AXIS_MODE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_POSITION_INVERT_AXIS:
        return this->readValueImplementation<int>(this->_globalVariables->positionInvertAxis, POSITION_INVERT_AXIS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_INVERT_AXIS:
        return this->readValueImplementation<int>(this->_globalVariables->strainInvertAxis, STRAIN_INVERT_AXIS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_INVERT_AXIS:
        return this->readValueImplementation<int>(this->_globalVariables->deformationInvertAxis, DEFORMATION_INVERT_AXIS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_PISTON_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->pistonMode, PISTON_MODE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_VALVE_DIRECTION_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->valveDirectionMode, VALVE_DIRECTION_MODE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA:
        return this->readValueImplementation<double>(this->_globalVariables->PistonParams.topArea, PISTON_PARAMS_TOP_AREA_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_PISTON_PARAMS_BOTTOM_AREA:
        return this->readValueImplementation<double>(this->_globalVariables->PistonParams.bottomArea, PISTON_PARAMS_BOTTOM_AREA_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_VALVE_PARAMS_IMAX:
        return this->readValueImplementation<double>(this->_globalVariables->ValveParams.Imax, VALVE_PARAMS_IMAX_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_VALVE_PARAMS_QVALVE:
        return this->readValueImplementation<double>(this->_globalVariables->ValveParams.Qvalve, VALVE_PARAMS_QVALVE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_POSITION_UPPER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->positionUpperThreshold, STATIC_TEST_POSITION_UPPER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_POSITION_LOWER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->positionLowerThreshold, STATIC_TEST_POSITION_LOWER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_STRAIN_UPPER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->strainUpperThreshold, STATIC_TEST_STRAIN_UPPER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_STRAIN_LOWER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->strainLowerThreshold, STATIC_TEST_STRAIN_LOWER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_UPPER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->deformationUpperThreshold, STATIC_TEST_DEFORMATION_UPPER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_LOWER_THRESHOLD:
        return this->readValueImplementation<double>(this->_globalVariables->deformationLowerThreshold, STATIC_TEST_DEFORMATION_LOWER_THRESHOLD_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_ENCODER_STEP_VALUE:
        return this->readValueImplementation<double>(this->_globalVariables->encoderStepValue, ENCODER_STEP_VALUE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->motorDriverType, MOTOR_DRIVER_TYPE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE:
        return this->readValueImplementation<int>(this->_globalVariables->controllerOnlineMode, CONTROLLER_ONLINE_MODE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MOTOR_STEP_VALUE:
        return this->readValueImplementation<double>(this->_globalVariables->motorStepValue, MOTOR_STEP_VALUE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1:
        return this->readValueImplementation<int>(this->_globalVariables->LimitSwitchPolarity1, LIMITSWITCH_POLARITY_1_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_2:
        return this->readValueImplementation<int>(this->_globalVariables->LimitSwitchPolarity2, LIMITSWITCH_POLARITY_2_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY:
        return this->readValueImplementation<int>(this->_globalVariables->EmergencyStopPolarity, EMERGENCY_STOP_POLARITY_OFFSET, memoryType, size);
        break;
	case GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE:
        return this->readValueImplementation<double>(this->_globalVariables->encoderExtensiaStepValue, DEFORMATION_ENCODER_STEP_VALUE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->displOverrunStepBack, DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_UNDERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->displUnderrunStepBack, DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_OVERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->strainOverrunStepBack, STRAIN_OVERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_UNDERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->strainUnderrunStepBack, STRAIN_UNDERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_OVERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->deformOverrunStepBack, DEFORMATION_OVERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_UNDERRUN_STEP_BACK:
        return this->readValueImplementation<double>(this->_globalVariables->deformUnderrunStepBack, DEFORMATION_UNDERRUN_STEP_BACK_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SSI_NULL_OFFSET:
        return this->readValueImplementation<double>(this->_globalVariables->SSINullOffset, SSI_NULL_OFFSET_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_PWM_FREQ:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->PWMFreq, PWM_FREQ_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SERIAL_NUMBER:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->machineInfo.serialNumber, SERIAL_NUMBER_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_ID:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->machineInfo.id, ID_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION:
        return this->readValueImplementation<uint16_t>(this->_globalVariables->machineInfo.ethernetProtocolVersion, ETHERNET_PROTOCOL_VERSION_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MACHINE_TYPE:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->machineInfo.machineType, MACHINE_TYPE_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.displacement.sensorType, DISPLACEMENT_CHANNEL_INFO_SENSOR_TYPE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_DISPLACEMENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.displacement.maxValue, DISPLACEMENT_CHANNEL_INFO_MAX_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_DISPLACEMENT_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.displacement.maxValueOverloadPercent, DISPLACEMENT_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_DISPLACEMENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.displacement.minValue, DISPLACEMENT_CHANNEL_INFO_MIN_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.displacement.minValueOverloadPercent, DISPLACEMENT_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.strain.sensorType, STRAIN_CHANNEL_INFO_SENSOR_TYPE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_STRAIN:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.strain.maxValue, STRAIN_CHANNEL_INFO_MAX_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_STRAIN_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.strain.maxValueOverloadPercent, STRAIN_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_STRAIN:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.strain.minValue, STRAIN_CHANNEL_INFO_MIN_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.strain.minValueOverloadPercent, STRAIN_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorType, DEFORMATION_CHANNEL_INFO_SENSOR_TYPE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_DEFORMATION:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.deformation.maxValue, DEFORMATION_CHANNEL_INFO_MAX_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MAX_DEFORMATION_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.deformation.maxValueOverloadPercent, DEFORMATION_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_DEFORMATION:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.deformation.minValue, DEFORMATION_CHANNEL_INFO_MIN_VALUE, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT:
        return this->readValueImplementation<double>(this->_globalVariables->machineInfo.deformation.minValueOverloadPercent, DEFORMATION_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT, memoryType, size);
        break;
    //PID    
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Kp, SIN_DISPLASEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Ki, SIN_DISPLASEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.PIDParams.Kd, SIN_DISPLASEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Kp, SIN_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Ki, SIN_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.PIDParams.Kd, SIN_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Kp, SIN_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Ki, SIN_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.PIDParams.Kd, SIN_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kp, SINUS_BASED_DISPL_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Ki, SINUS_BASED_DISPL_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.PIDParams.Kd, SINUS_BASED_DISPL_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Kp, SINUS_BASED_DEFORM_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Ki, SINUS_BASED_DEFORM_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.PIDParams.Kd, SINUS_BASED_DEFORM_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Kp, SINUS_BASED_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Ki, SINUS_BASED_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.PIDParams.Kd, SINUS_BASED_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break; 

    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Kp, CONST_DISPLACEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Ki, CONST_DISPLACEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;    
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.PIDParams.Kd, CONST_DISPLACEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Kp, CONST_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break; 
    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Ki, CONST_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break; 
    case GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.PIDParams.Kd, CONST_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;         

    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Kp, CONST_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Ki, CONST_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;     
    case GLOBAL_VARIABLES_CONST_STRAIN_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.PIDParams.Kd, CONST_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
        //MaxVoltages

    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.MaxVoltage, SIN_DISPLASEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.MaxVoltage, SIN_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.MaxVoltage, SIN_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxVoltage, SINUS_BASED_DISPL_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.MaxVoltage, SINUS_BASED_DEFORM_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.MaxVoltage, SINUS_BASED_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxVoltage, CONST_DISPLACEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxVoltage, CONST_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxVoltage, CONST_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT:
        return this->readValueImplementation<double>(this->_globalVariables->SINVoltageModeParams.MaxVoltage, SIN_VOLTAGE_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

    //Const displacement mode params
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxDeviation, CONST_DISPLACEMENT_MODE_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.ModeFrequency, CONST_DISPLACEMENT_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.Speed, CONST_DISPLACEMENT_MODE_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.MaxSpeed, CONST_DISPLACEMENT_MODE_MAX_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDisplacementModeParams.delta, CONST_DISPLACEMENT_MODE_DELTA_PARAMS_FLASH_OFFSET, memoryType, size);
        break;    
    
        //Max Steps and delta
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.delta, CONST_STRAIN_MODE_DELTA_PARAMS_FLASH_OFFSET, memoryType, size);
        break;  
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.delta, CONST_DEFORMATION_MODE_DELTA_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SINDisplacementModeParams.MaxSteps, SIN_DISPLASEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SINDeformationModeParams.MaxSteps, SIN_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SINStrainModeParams.MaxSteps, SIN_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxSteps, SINUS_BASED_DISPL_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SinusBasedDeformationModeParams.MaxSteps, SINUS_BASED_DEFORM_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->SinusBasedStrainModeParams.MaxSteps, SINUS_BASED_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->ConstDisplacementModeParams.MaxSteps, CONST_DISPLACEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->ConstDeformationModeParams.MaxSteps, CONST_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->ConstStrainModeParams.MaxSteps, CONST_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;

        //TCycle time
    case GLOBAL_VARIABLES_T_CYCLE_TIME:
        return this->readValueImplementation<us_timestamp_t>(this->_globalVariables->TcycleTime, T_CYCLE_TIME_PARAMS_FLASH_OFFSET, memoryType, size);
        break;     
    case GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->ConstModeParams.ConstFrequency, CONST_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxDeviation, CONST_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.ModeFrequency, CONST_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.Speed, CONST_STRAIN_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_MAX_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.MaxSpeed, CONST_STRAIN_MAX_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_STRAIN_DELTA:
        return this->readValueImplementation<double>(this->_globalVariables->ConstStrainModeParams.delta, CONST_STRAIN_DELTA_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxDeviation, CONST_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.ModeFrequency, CONST_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.Speed, CONST_DEFORMATION_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_SPEED:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.MaxSpeed, CONST_DEFORMATION_MAX_SPEED_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CONST_DEFORMATION_DELTA:
        return this->readValueImplementation<double>(this->_globalVariables->ConstDeformationModeParams.delta, CONST_DEFORMATION_DELTA_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.MaxDeviation, SIN_DISPLASEMENT_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.ModeFrequency, SIN_DISPLASEMENT_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKP, SIN_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKP, SIN_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKI, SIN_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKI, SIN_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.UpKD, SIN_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.DownKD, SIN_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.MaxDeviation, SIN_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.ModeFrequency, SIN_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKP, SIN_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKP, SIN_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKI, SIN_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKI, SIN_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.UpKD, SIN_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.DownKD, SIN_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.MaxDeviation, SIN_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.ModeFrequency, SIN_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKP, SIN_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKP, SIN_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKI, SIN_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKI, SIN_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.UpKD, SIN_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.DownKD, SIN_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.MaxDeviation, SIN_BASED_DISP_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.ModeFrequency, SIN_BASED_DISP_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.MaxDeviation, SIN_BASED_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.ModeFrequency, SIN_BASED_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_MAX_DEV:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.MaxDeviation, SIN_BASED_DEFORM_MAX_DEV_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_MODE_FREQ:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.ModeFrequency, SIN_BASED_DEFORM_MODE_FREQ_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP, SIN_BASED_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI, SIN_BASED_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD, SIN_BASED_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD, SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[0], DEFORMATION_SENSOR_TYPE_CH1_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH2:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[1], DEFORMATION_SENSOR_TYPE_CH2_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH3:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[2], DEFORMATION_SENSOR_TYPE_CH3_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH4:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.sensorTypes[3], DEFORMATION_SENSOR_TYPE_CH4_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->machineInfo.deformation.activeChannels, ACTIVE_DEFORMATION_CHANNELS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE:
        return this->readValueImplementation<float>(this->_globalVariables->ReferenceVoltage, STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE:
        return this->readValueImplementation<float>(this->_globalVariables->ExtensRefVoltage, DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_REFERENCE_VOLTAGE:
        return this->readValueImplementation<float>(this->_globalVariables->DisplRefVoltage, POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET, memoryType, size);
        break;  

        //SSI sensor resolution
    case GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION:
        return this->readValueImplementation<double>(this->_globalVariables->SSISensorResolution, SSI_SENSOR_RESOLUTION_FLASH_OFFSET, memoryType, size);     
        break;
        //strain button protection
    case GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT:
        return this->readValueImplementation<float>(this->_globalVariables->strainButtonUpperLimit, STRAIN_BUTTON_PROTECTION_UPPER_LIMIT, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT:
        return this->readValueImplementation<float>(this->_globalVariables->strainButtonLowerLimit, STRAIN_BUTTON_PROTECTION_LOWER_LIMIT, memoryType, size);     
        break;         
	case GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->enableActiveLevel, ENABLE_ACTIVE_LEVEL_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CLR_ACTIVE_LEVEL:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->CLRActiveLevel, CLR_ACTIVE_LEVEL_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CWL_ACTIVE_LEVEL:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->CWLActiveLevel, CWL_ACTIVE_LEVEL_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL:
        return this->readValueImplementation<uint8_t>(this->_globalVariables->CCWLActiveLevel, CCWL_ACTIVE_LEVEL_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR:
        return this->readValueImplementation<float>(this->_globalVariables->displButtonRegularSpeed, REGULAR_SPEED_BY_BUTTON_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST:
        return this->readValueImplementation<float>(this->_globalVariables->displButtonFastSpeed, FAST_SPEED_BY_BUTTON_FLASH_OFFSET, memoryType, size);     
        break;
        //tcycle for flash writing
    case GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING:
        return this->readValueImplementation<us_timestamp_t>(this->_globalVariables->TcycleTimeFlashWriting, TCYCLE_FOR_FLASH_WRITING_FLASH_OFFSET, memoryType, size);     
        break;
        //cyclic delta for protection
    case GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA:
        return this->readValueImplementation<float>(this->_globalVariables->strainCyclicDelta, STRAIN_CYCLIC_DELTA_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_CYCLIC_DELTA:
        return this->readValueImplementation<float>(this->_globalVariables->displacementCyclicDelta, DISPLACEMENT_CYCLIC_DELTA_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA:
        return this->readValueImplementation<float>(this->_globalVariables->deformationCyclicDelta, DEFORMATION_CYCLIC_DELTA_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MAX_POSITION:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->maxPosition, MAX_POSITION_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIDDLE_POSITION:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->middlePosition, MIDDLE_POSITION_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIDDLE_UP_THRESHOLD:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->middleUpThreshold, MIDDLE_UP_THRESHOLD_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIDDLE_DOWN_THRESHOLD:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->middleDownThreshold, MIDDLE_DOWN_THRESHOLD_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_POSITION_DIVIDER:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->positionDivider, POSITION_DIVIDER_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_VALVE_INVERT_AXIS:
        return this->readValueImplementation<int>(this->_globalVariables->valveInvertAxis, VALVE_INVERT_AXIS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_PORT:
        return this->readValueImplementation<uint16_t>(this->_globalVariables->port, PORT_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->machineInfo.ethernetConnectionTimeoutStopTest, ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST_OFFSET, memoryType, size);
        break;
    //Amplitude attenuation coefs
    case GLOBAL_VARIABLES_MIN_DELTA_RATIO_FOR_NULLPOINT:
        return this->readValueImplementation<double>(this->_globalVariables->minDeltaRatioForNullPointAttenuating, MIN_DELTA_RATIO_FOR_NULLPOINT_ATTEN_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_DISPL_NULLPOINT:
        return this->readValueImplementation<double>(this->_globalVariables->minAmplForDisplNullPointAttenuating, MIN_AMPL_FOR_DISPL_NULLPOINT_ATTEN_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_DEFORM_NULLPOINT:
        return this->readValueImplementation<double>(this->_globalVariables->minAmplForDeformNullPointAttenuating, MIN_AMPL_FOR_DEFORM_NULLPOINT_ATTEN_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIN_AMPL_FOR_STRAIN_NULLPOINT:
        return this->readValueImplementation<double>(this->_globalVariables->minAmplForStrainNullPointAttenuating, MIN_AMPL_FOR_STRAIN_NULLPOINT_ATTEN_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO:
        return this->readValueImplementation<double>(this->_globalVariables->startStopAmplitudeRatio, START_STOP_AMPLITUDE_RATIO_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP:
        return this->readValueImplementation<double>(this->_globalVariables->stopAmplitudeRatio, START_STOP_AMPLITUDE_RATIO_STOP_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_AMPLITUDE_PRECISION:
        return this->readValueImplementation<double>(this->_globalVariables->amplitudePrecision, AMPLITUDE_PRECISION_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT:
        return this->readValueImplementation<float>(this->_globalVariables->tresholdForNullPointDeltaAccept, TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->stepForNullPointGetCorrection, STEP_FOR_NULLPOINT_GET_CORRECTION_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->minMaxCalculatingCounts, MIN_MAX_CALCULATING_COUNTS_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC:
        return this->readValueImplementation<int>(this->_globalVariables->minMaxCalculatingCountsMainProcess, MIN_MAX_CALCULATING_COUNTS_MAIN_PROC_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START:
        return this->readValueImplementation<double>(this->_globalVariables->anchorSinFrequency, ANCHOR_SIN_FREQUENCY_START_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_STOP:
        return this->readValueImplementation<double>(this->_globalVariables->anchorSinFrequencyStop, ANCHOR_SIN_FREQUENCY_STOP_FLASH_OFFSET, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_MIDDLE_PISTON_POSITION:
        return this->readValueImplementation<double>(this->_globalVariables->middlePistonPosition, MIDDLE_PISTON_POSITION_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DEFORMATION_UNITS:
        return this->readValueImplementation<uint32_t>(this->_globalVariables->DeformationUnits, DEFORMATION_UNITS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKP, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKI, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKD, SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKP, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKI, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINStrainModeParams.amplitudeTuneInfo.NullPointKD, SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKP, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKI, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SINDeformationModeParams.amplitudeTuneInfo.NullPointKD, SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKP, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKI, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD:
        return this->readValueImplementation<double>(this->_globalVariables->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKD, SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS, memoryType, size);
        break;
        
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT:
        return this->readValueImplementation<double>(this->_globalVariables->blindePartOfCyclicStrainProtection, BLINDE_PART_CYCL_STRAIN_PRPOT_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT:
        return this->readValueImplementation<double>(this->_globalVariables->defaultBlindePartOfCyclicStrainProtection, BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST:
        return this->readValueImplementation<double>(this->_globalVariables->blindePartOfCyclicStrainProtectionFirst, BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST:
        return this->readValueImplementation<double>(this->_globalVariables->defaultBlindePartOfCyclicStrainProtectionFirst, BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION:
        return this->readValueImplementation<double>(this->_globalVariables->deltaCyclicProtection, DELTA_CYCLIC_PROTECTION_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION_DEFAULT:
        return this->readValueImplementation<double>(this->_globalVariables->deltaCyclicProtectionDefault, DELTA_CYCLIC_PROTECTION_DEFAULT_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MULTIPLIER:
        return this->readValueImplementation<double>(this->_globalVariables->multiplier, MULTIPLIER_FLASH_OFFS, memoryType, size);
        break;
    case GLOBAL_VARIABLES_MULTIPLIER_DEFAULT:
        return this->readValueImplementation<double>(this->_globalVariables->multiplierDefault, MULTIPLIER_DEFAULT_FLASH_OFFS, memoryType, size);
        break;
    default:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->machineInfo.serialNumber, SERIAL_NUMBER_FLASH_OFFSET, memoryType, size);
        break;
    }
}

template <typename T> T GlobalVariablesInterface::readValue(uint32_t index, memoryType_t memoryType, int &size, uint8_t exstraFlashOffset){
    switch (index){
    case GLOBAL_VARIABLES_STRAIN_CALIBRATION_NOTES:
        if (exstraFlashOffset >= 0 && exstraFlashOffset < STRAIN_CALIBRATION_NOTES_FLASH_MAX_SIZE){
            return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, STRAIN_CALIBRATION_NOTES_FLASH_OFFSET + exstraFlashOffset, memoryType, size);
        }
        else return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, STRAIN_CALIBRATION_NOTES_FLASH_MAX_SIZE - 1, memoryType, size);     
        break;
    case GLOBAL_VARIABLES_DISPLACEMENT_CALIBRATION_NOTES:
        if (exstraFlashOffset >= 0 && exstraFlashOffset < POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE){
            return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, POSITION_CALIBRATION_NOTES_FLASH_OFFSET + exstraFlashOffset, memoryType, size);
        }
        else return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE - 1, memoryType, size);    
        break;
    case GLOBAL_VARIABLES_DEFORMATION_CALIBRATION_NOTES:
        if (exstraFlashOffset >= 0 && exstraFlashOffset < DEFORMATION_CALIBRATION_NOTES_FLASH_MAX_SIZE){
            return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET + exstraFlashOffset, memoryType, size);
        }
        else return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_NOTES_FLASH_MAX_SIZE - 1, memoryType, size);      
        break;
    case GLOBAL_VARIABLES_DEFORMATION_2CH_CALIBRATION_NOTES:
        if (exstraFlashOffset >= 0 && exstraFlashOffset < DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_MAX_SIZE){
            return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET + exstraFlashOffset, memoryType, size);
        }
        else return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_MAX_SIZE - 1, memoryType, size);      
        break;
    case GLOBAL_VARIABLES_DEFORMATION_3CH_CALIBRATION_NOTES:
        if (exstraFlashOffset >= 0 && exstraFlashOffset < DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_MAX_SIZE){
            return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET + exstraFlashOffset, memoryType, size);
        }
        else return this->readValueImplementation<uint8_t>(this->_globalVariables->readingAndWritingFlashTrash, DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_MAX_SIZE - 1, memoryType, size);      
        break;
    default:
        return this->readValueImplementation<uint64_t>(this->_globalVariables->machineInfo.serialNumber, SERIAL_NUMBER_FLASH_OFFSET, memoryType, size);
        break;
    }
}

template <typename T> T GlobalVariablesInterface::readValueImplementation(T &gvValue, uint32_t flashOffset, memoryType_t memoryType, int &size){
    T value;
    size = sizeof value;
    switch (memoryType)
    {
        case RAM_MEMORY_TYPE:
            value =  gvValue;
            break;
        case FLASH_MEMORY_TYPE:{
            switch (this->_globalVariables->flashOperationType)
            {
            case FLASH_OPERATION_CPU:
                this->_internalFlash->readInOneSector<T>(value, flashOffset);
                break;
            case FLASH_OPERATION_DMA:
                this->_internalFlashDMA->readFromFlash<T>(value, flashOffset);
                break;
            default:
                break;
            }
            break;
        }
        default:
            value =  gvValue;
            break;
    }
    return value;
}
template <typename T> void GlobalVariablesInterface::writeValueImplementation(T &gvValue, uint32_t flashOffset, T value, memoryType_t memoryType){
    switch (memoryType)
    {
        case RAM_MEMORY_TYPE:
            gvValue = value;
            break;
        case FLASH_MEMORY_TYPE:{
            switch (this->_globalVariables->flashOperationType)
            {
            case FLASH_OPERATION_CPU:
                this->_internalFlash->Writing_To_Flash_Through_Buf_Sector<T>(value, flashOffset);
                break;
            case FLASH_OPERATION_DMA:
                this->_internalFlashDMA->setParams(value, flashOffset);
                break;
            default:
                break;
            }
            break;
        }
        case FLASH_MEMORY_QUEUE:{
            this->_internalFlashDMA->setParamsForQueue(value, flashOffset);
            break;
        }
        case FLASH_MEMORY_SET:{
            this->_internalFlashDMA->writeToFlashViaQueue();
            break;
        }
        case FLASH_MEMORY_CHAR_ARRAY:{
            this->_internalFlashDMA->setParamsBuffer<uint8_t>(this->ptrOnCharBuffer, flashOffset, this->sizeOfCharBuffer);
            break;
        }
        default:
            break;
    }
}
template <typename T> int GlobalVariablesInterface::readValueAnyType(uint32_t index, char *buffer, memoryType_t memoryType){
    int size = 0;
    T value;
    value = this->readValue<T>(index, memoryType, size);
    basic.writeValueToBytesBuffer(buffer, value, 0);
    return size;
}
template <typename T, typename R = T> int GlobalVariablesInterface::readValueAnyTypeCast(uint32_t index, char *buffer, memoryType_t memoryType){
    int size = 0;
    T value;
    value = this->readValue<T>(index, memoryType, size);
    R val = (R)value;
    basic.writeValueToBytesBuffer(buffer, val, 0);
    size = sizeof(R);
    return size;
}
template <typename T> void GlobalVariablesInterface::writeValueAnyType(uint32_t index, char *buffer, memoryType_t memoryType, T value){
    basic.writeBytesBufferToValue(buffer, &value);
    this->writeValue<T>(index, value, memoryType);
}
template <typename T, typename R = T> void GlobalVariablesInterface::writeValueAnyTypeCast(uint32_t index, char *buffer, memoryType_t memoryType, T value){
    basic.writeBytesBufferToValue(buffer, &value);
    R val = (R)value;
    this->writeValue<R>(index, val, memoryType);
} 
#endif