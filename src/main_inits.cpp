// #include "Shared_Definitions.h"
#include "..//lib/GlobalVariablesInterface/GlobalVariablesInterface.h"
#include "..//Protect/Protect.h"
#include "..//lib/DataExchangeProtocol/DataExchangeProtocol.h"
#include "..//include/BackupVariables.h"

extern GlobalVariablesInterface GVI;
extern backupVariables_t BV;

extern Protect strainProtect;
extern Protect strainProtectStage2;
extern Protect strainEdgeProtect;
// extern Protect strainButtonProtect;
extern Protect displacementProtect;
extern Protect displacementProtectStage2;
extern Protect displacementEdgeProtect;
extern Protect deformationProtect;
extern Protect deformationProtectStage2;
extern Protect deformationEdgeProtect;


int readGV(globalVariables_t &GV) {

  //read BV
  BV.valvePosition = (int32_t*) BACKUP_RAM_START_ADDRESS;
  BV.encoderPulses = (int32_t*) (BACKUP_RAM_START_ADDRESS + sizeof(int32_t));
  BV.strainNullOffset = (double*) (BACKUP_RAM_START_ADDRESS + sizeof(int32_t) * 2);

  if(*BV.valvePosition == 0xFFFFFFFF){
    *BV.valvePosition = 0;
  }
  if(*BV.encoderPulses == 0xFFFFFFFF){
    *BV.encoderPulses = 0;
  }
  if(std::isnan(*BV.strainNullOffset)){
    *BV.strainNullOffset = 0;
  }

  //read serial number & ID
  GV.machineInfo.serialNumber                         =        GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SERIAL_NUMBER, FLASH_MEMORY_TYPE);
  GV.machineInfo.id                                   =        GVI.readValue<uint64_t>(GLOBAL_VARIABLES_ID,            FLASH_MEMORY_TYPE);
  GV.machineInfo.machineType                          =        GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MACHINE_TYPE, FLASH_MEMORY_TYPE);

  uint16_t tmpU16;
  tmpU16                                              =        GVI.readValue<uint16_t>(GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION, FLASH_MEMORY_TYPE);
  if(tmpU16 == 0xFFFF){
    GV.machineInfo.ethernetProtocolVersion = DATA_EXCHANGE_PROTOCOL_VERSION_ZERO;
  }else{
    GV.machineInfo.ethernetProtocolVersion = tmpU16;
  }
  
  std::string tmpString;
  tmpString                                           =        GVI.readValue<std::string>(GLOBAL_VARIABLES_IP_ADDRESS, FLASH_MEMORY_TYPE); 
  if((tmpString.size() != (uint32_t)FLASH_IP_PARAMS_AREA_SIZE)) GV.ipAddress = tmpString;

  tmpString                                           =        GVI.readValue<std::string>(GLOBAL_VARIABLES_NET_MASK, FLASH_MEMORY_TYPE);
  if((tmpString.size() != (uint32_t)FLASH_IP_PARAMS_AREA_SIZE)) GV.netMask = tmpString;

  tmpString                                           =        GVI.readValue<std::string>(GLOBAL_VARIABLES_GATEWAY, FLASH_MEMORY_TYPE);
  if((tmpString.size() != (uint32_t)FLASH_IP_PARAMS_AREA_SIZE)) GV.gateway = tmpString;
  
  tmpU16                                              =        GVI.readValue<uint16_t>(GLOBAL_VARIABLES_PORT, FLASH_MEMORY_TYPE);
  if(tmpU16 != 0xFFFF) GV.machineInfo.EthernetPort = tmpU16;

  GV.machineInfo.EthernetBoardIPAddress = GV.ipAddress.c_str();
  GV.machineInfo.EthernetNetMask = GV.netMask.c_str();
  GV.machineInfo.EthernetGateway = GV.gateway.c_str();
  GV.machineInfo.EthernetPort = GV.port;

  uint32_t tmpU32;
  tmpU32                                              =        GVI.readValue<uint32_t>(GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST, FLASH_MEMORY_TYPE);
  if(tmpU32 != 0xFFFFFFFF)  GV.machineInfo.ethernetConnectionTimeoutStopTest = tmpU32;
  else                      GV.machineInfo.ethernetConnectionTimeoutStopTest = 10000;

  GV.machineInfo.strain.sensorType                    =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE, FLASH_MEMORY_TYPE);
  GV.machineInfo.displacement.sensorType              =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.sensorType               =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.sensorTypes[0]           =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.sensorTypes[1]           =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH2, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.sensorTypes[2]           =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH3, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.sensorTypes[3]           =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH4, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.activeChannels           =        GVI.readValue<uint8_t>(GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS, FLASH_MEMORY_TYPE);
  uint64_t dummy                                      =        GVI.readValue<us_timestamp_t>(GLOBAL_VARIABLES_T_CYCLE_TIME, FLASH_MEMORY_TYPE);
  if(dummy != 0xFFFFFFFFFFFFFFFF) GV.TcycleTime       =       dummy;

  GV.machineInfo.strain.maxValue                      = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_STRAIN, FLASH_MEMORY_TYPE);
  GV.machineInfo.strain.maxValueOverloadPercent       = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_STRAIN_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.strain.minValue                      = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_STRAIN, FLASH_MEMORY_TYPE);
  GV.machineInfo.strain.minValueOverloadPercent       = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.displacement.maxValue                = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_DISPLACEMENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.displacement.maxValueOverloadPercent = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_DISPLACEMENT_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.displacement.minValue                = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_DISPLACEMENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.displacement.minValueOverloadPercent = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.maxValue                 = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_DEFORMATION, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.maxValueOverloadPercent  = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MAX_DEFORMATION_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.minValue                 = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_DEFORMATION, FLASH_MEMORY_TYPE);
  GV.machineInfo.deformation.minValueOverloadPercent  = (float)GVI.readValue<double>(GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT, FLASH_MEMORY_TYPE);

  GV.positionUpperThreshold                           =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_POSITION_UPPER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.positionLowerThreshold                           =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_POSITION_LOWER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.strainUpperThreshold                             =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_STRAIN_UPPER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.strainLowerThreshold                             =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_STRAIN_LOWER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.deformationUpperThreshold                        =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_UPPER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.deformationLowerThreshold                        =        GVI.readValue<double>(GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_LOWER_THRESHOLD, FLASH_MEMORY_TYPE);
  GV.controllerOnlineMode                             =        GVI.readValue<uint32_t>(GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE, FLASH_MEMORY_TYPE);

  GV.encoderStepValue                                 =        GVI.readValue<double>(GLOBAL_VARIABLES_ENCODER_STEP_VALUE, FLASH_MEMORY_TYPE);
  GV.motorDriverType                                  =        GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE, FLASH_MEMORY_TYPE);
  GV.motorStepValue                                   =        GVI.readValue<double>(GLOBAL_VARIABLES_MOTOR_STEP_VALUE, FLASH_MEMORY_TYPE);

  GV.LimitSwitchPolarity1                             =        GVI.readValue<int>(GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1, FLASH_MEMORY_TYPE);
  GV.LimitSwitchPolarity2                             =        GVI.readValue<int>(GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_2, FLASH_MEMORY_TYPE);
  GV.EmergencyStopPolarity                            =        GVI.readValue<int>(GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY, FLASH_MEMORY_TYPE);

  GV.displOverrunStepBack                             =        GVI.readValue<double>(GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK, FLASH_MEMORY_TYPE);
  GV.displUnderrunStepBack                            =        GVI.readValue<double>(GLOBAL_VARIABLES_DISPLACEMENT_UNDERRUN_STEP_BACK, FLASH_MEMORY_TYPE);
  GV.strainOverrunStepBack                            =        GVI.readValue<double>(GLOBAL_VARIABLES_STRAIN_OVERRUN_STEP_BACK, FLASH_MEMORY_TYPE);
  GV.strainUnderrunStepBack                           =        GVI.readValue<double>(GLOBAL_VARIABLES_STRAIN_UNDERRUN_STEP_BACK, FLASH_MEMORY_TYPE);
  GV.deformOverrunStepBack                            =        GVI.readValue<double>(GLOBAL_VARIABLES_DEFORMATION_OVERRUN_STEP_BACK, FLASH_MEMORY_TYPE);
  GV.deformUnderrunStepBack                           =        GVI.readValue<double>(GLOBAL_VARIABLES_DEFORMATION_UNDERRUN_STEP_BACK, FLASH_MEMORY_TYPE);

  GV.SSINullOffset                                    =        GVI.readValue<double>(GLOBAL_VARIABLES_SSI_NULL_OFFSET, FLASH_MEMORY_TYPE);
  GV.encoderExtensiaStepValue                         =        GVI.readValue<double>(GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE, FLASH_MEMORY_TYPE);
  //PIDs reading

  GV.PWMFreq                                          =        GVI.readValue<uint32_t>(GLOBAL_VARIABLES_PWM_FREQ, FLASH_MEMORY_TYPE);
  double tmp;

  //Ref Voltages
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ReferenceVoltage                               =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ExtensRefVoltage                               =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DISPLACEMENT_REFERENCE_VOLTAGE, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.DisplRefVoltage                               =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.PIDParams.Kp         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.PIDParams.Ki         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.PIDParams.Kd         =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.PIDParams.Kp          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.PIDParams.Ki          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.PIDParams.Kd          =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.PIDParams.Kp               =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.PIDParams.Ki               =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.PIDParams.Kd               =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.PIDParams.Kp  =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.PIDParams.Ki  =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.PIDParams.Kd  =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.PIDParams.Kp   =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.PIDParams.Ki   =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.PIDParams.Kd   =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.PIDParams.Kp        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.PIDParams.Ki        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.PIDParams.Kd        =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.PIDParams.Kp       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.PIDParams.Ki       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.PIDParams.Kd       =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.PIDParams.Kp        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.PIDParams.Ki        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.PIDParams.Kd        =     tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.PIDParams.Kp             =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.PIDParams.Ki             =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.PIDParams.Kd             =     tmp : tmp=0;

    //MaxVoltages reading

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.MaxVoltage           =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.MaxVoltage            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.MaxVoltage                 =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.MaxVoltage    =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.MaxVoltage     =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.MaxVoltage          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.MaxVoltage         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.MaxVoltage          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.MaxVoltage               =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINVoltageModeParams.MaxVoltage                =     tmp : tmp=0;

  //Const displacement mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.MaxDeviation       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.ModeFrequency      =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.Speed              =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.MaxSpeed           =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDisplacementModeParams.delta              =     tmp : tmp=0;

  //Max Steps and delta

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.delta                    =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.delta               =     tmp : tmp=0;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SINDisplacementModeParams.MaxSteps             =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SINDeformationModeParams.MaxSteps              =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SINStrainModeParams.MaxSteps                   =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SinusBasedDisplacementModeParams.MaxSteps      =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SinusBasedDeformationModeParams.MaxSteps       =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.SinusBasedStrainModeParams.MaxSteps            =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.ConstDisplacementModeParams.MaxSteps           =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.ConstDeformationModeParams.MaxSteps            =     tmp : tmp=400;
  tmp = GVI.readValue<uint64_t>(GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP, FLASH_MEMORY_TYPE);
  (tmp != 0xFFFFFFFFFFFFFFFF) ? GV.ConstStrainModeParams.MaxSteps                 =     tmp : tmp=400;

  //Const mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstModeParams.ConstFrequency                 =     tmp : tmp=0;

  //Const strain mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.MaxDeviation             =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.ModeFrequency            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.Speed                    =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_MAX_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.MaxSpeed                 =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_STRAIN_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstStrainModeParams.delta                    =     tmp : tmp=0;

  //Const deformation mode params 

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.MaxDeviation        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.ModeFrequency       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.Speed               =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_SPEED, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.MaxSpeed            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_CONST_DEFORMATION_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.ConstDeformationModeParams.delta               =     tmp : tmp=0;

  //Sinus displacement mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLASEMENT_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.MaxDeviation         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.ModeFrequency        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.UpKP        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.DownKP      =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.UpKI        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.DownKI      =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.UpKD        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.DownKD      =     tmp : tmp=0;

  //Sinus strain mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.MaxDeviation               =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.ModeFrequency              =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.UpKP              =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.DownKP            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.UpKI              =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.DownKI            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.UpKD              =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.DownKD            =     tmp : tmp=0;

  //Sinus deformation mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.MaxDeviation          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.ModeFrequency         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.UpKP         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.DownKP       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.UpKI         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.DownKI       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.UpKD         =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.DownKD       =     tmp : tmp=0;

  //Sinus based displacement mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.MaxDeviation           =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.ModeFrequency          =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKP       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKP     =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKI       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKI     =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKD       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKD     =     tmp : tmp=0;

  //Sinus based strain mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.MaxDeviation                 =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.ModeFrequency                =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.UpKP       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.DownKP     =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.UpKI       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.DownKI     =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.UpKD       =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.DownKD     =     tmp : tmp=0;

  //Sinus based deformation mode params

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_MAX_DEV, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.MaxDeviation            =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_MODE_FREQ, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.ModeFrequency           =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP      =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI      =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD        =     tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD      =     tmp : tmp=0;

//SSI sensor resolution reading
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SSISensorResolution                                           =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.strainButtonLowerLimit                                        =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.strainButtonUpperLimit                                        =     tmp : tmp=0;

//MotorDriver commands active levels
  tmp = GVI.readValue<uint8_t>(GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL, FLASH_MEMORY_TYPE);
  if(tmp != 0xFF) GV.enableActiveLevel = tmp;
  tmp = GVI.readValue<uint8_t>(GLOBAL_VARIABLES_CLR_ACTIVE_LEVEL, FLASH_MEMORY_TYPE);
  if(tmp != 0xFF) GV.CLRActiveLevel = tmp;
  tmp = GVI.readValue<uint8_t>(GLOBAL_VARIABLES_CWL_ACTIVE_LEVEL, FLASH_MEMORY_TYPE);
  if(tmp != 0xFF) GV.CWLActiveLevel = tmp;
  tmp = GVI.readValue<uint8_t>(GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL, FLASH_MEMORY_TYPE);
  if(tmp != 0xFF) GV.CCWLActiveLevel = tmp;

//Speed by button
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.displButtonRegularSpeed                                       =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.displButtonFastSpeed                                          =     tmp : tmp=0;

//Tcycle time for flash writing
  tmp = GVI.readValue<us_timestamp_t>(GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFFFFFFFFFF) GV.TcycleTimeFlashWriting = tmp;
  
//Cyclic delta for protection
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.strainCyclicDelta                                             =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DISPLACEMENT_CYCLIC_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.displacementCyclicDelta                                             =     tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.deformationCyclicDelta                                             =     tmp : tmp=0;

  //Digital valve params
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MAX_POSITION, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.maxPosition = tmp;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MIDDLE_POSITION, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.middlePosition = tmp;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MIDDLE_UP_THRESHOLD, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.middleUpThreshold = tmp;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MIDDLE_DOWN_THRESHOLD, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.middleDownThreshold = tmp;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_POSITION_DIVIDER, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.positionDivider = tmp;
  tmp = GVI.readValue<int>(GLOBAL_VARIABLES_VALVE_INVERT_AXIS, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.valveInvertAxis = tmp;

  //Amplitude tune coefs
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MIN_DELTA_RATIO_FOR_NULLPOINT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.minDeltaRatioForNullPointAttenuating = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MIN_AMPL_FOR_DISPL_NULLPOINT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.minAmplForDisplNullPointAttenuating = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MIN_AMPL_FOR_DEFORM_NULLPOINT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.minAmplForDeformNullPointAttenuating = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MIN_AMPL_FOR_STRAIN_NULLPOINT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.minAmplForStrainNullPointAttenuating = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.startStopAmplitudeRatio = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.stopAmplitudeRatio = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_AMPLITUDE_PRECISION, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.amplitudePrecision = tmp : tmp=0;
  tmp = GVI.readValue<float>(GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.tresholdForNullPointDeltaAccept = tmp : tmp=0;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.stepForNullPointGetCorrection = tmp;
  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.minMaxCalculatingCounts = tmp;
  tmp = GVI.readValue<int>(GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.minMaxCalculatingCountsMainProcess = tmp;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.anchorSinFrequency = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_STOP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.anchorSinFrequencyStop = tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MIDDLE_PISTON_POSITION, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.middlePistonPosition = tmp : tmp=0;

  tmp = GVI.readValue<uint32_t>(GLOBAL_VARIABLES_DEFORMATION_UNITS, FLASH_MEMORY_TYPE);
  if(tmp != 0xFFFFFFFF) GV.DeformationUnits = tmp;
  //Null point PIDs
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDisplacementModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINStrainModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SINDeformationModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;

  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKP = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKI = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKD = tmp : tmp=0;
  //cyclic strain protection
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.blindePartOfCyclicStrainProtection = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.defaultBlindePartOfCyclicStrainProtection = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.blindePartOfCyclicStrainProtectionFirst = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.defaultBlindePartOfCyclicStrainProtectionFirst = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.deltaCyclicProtection = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION_DEFAULT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.deltaCyclicProtectionDefault = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MULTIPLIER, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.multiplier = tmp : tmp=0;
  tmp = GVI.readValue<double>(GLOBAL_VARIABLES_MULTIPLIER_DEFAULT, FLASH_MEMORY_TYPE);
  !std::isnan(tmp) ? GV.multiplierDefault = tmp : tmp=0;

  return 0;
}

int initProtects(const globalVariables_t &GV) {
  strainProtect.setLimits(                  GV.machineInfo.strain.maxValue + GV.machineInfo.strain.maxValue * GV.machineInfo.strain.maxValueOverloadPercent,
                                            GV.machineInfo.strain.minValue + GV.machineInfo.strain.minValue * GV.machineInfo.strain.minValueOverloadPercent);
  strainProtect.setValuesCount(             DEFAULT_STRAIN_PROTECT_COUNT);
  strainProtect.setMode(                    PROTECT_MODE_DISABLE);
  strainProtectStage2.setLimits(            GV.machineInfo.strain.maxValue + GV.machineInfo.strain.maxValue * GV.machineInfo.strain.maxValueOverloadPercent,
                                            GV.machineInfo.strain.minValue + GV.machineInfo.strain.minValue * GV.machineInfo.strain.minValueOverloadPercent);
  strainProtectStage2.setValuesCount(       DEFAULT_STRAIN_PROTECT_COUNT);
  strainProtectStage2.setMode(              PROTECT_MODE_DISABLE);
  strainEdgeProtect.setLimits(              GV.machineInfo.strain.maxValue + GV.machineInfo.strain.maxValue * GV.machineInfo.strain.maxValueOverloadPercent,
                                            GV.machineInfo.strain.minValue + GV.machineInfo.strain.minValue * GV.machineInfo.strain.minValueOverloadPercent);
  strainEdgeProtect.setValuesCount(         DEFAULT_STRAIN_EDGE_PROTECT_COUNT);
  strainEdgeProtect.setMode(                PROTECT_MODE_CONTINIUS);
  displacementProtect.setLimits(            GV.machineInfo.displacement.maxValue + GV.machineInfo.displacement.maxValue * GV.machineInfo.displacement.maxValueOverloadPercent,
                                            GV.machineInfo.displacement.minValue + GV.machineInfo.displacement.minValue * GV.machineInfo.displacement.minValueOverloadPercent);
  displacementProtect.setValuesCount(       DEFAULT_DISPLACEMENT_PROTECT_COUNT);
  displacementProtect.setMode(              PROTECT_MODE_DISABLE);
  displacementProtectStage2.setLimits(      GV.machineInfo.displacement.maxValue + GV.machineInfo.displacement.maxValue * GV.machineInfo.displacement.maxValueOverloadPercent,
                                            GV.machineInfo.displacement.minValue + GV.machineInfo.displacement.minValue * GV.machineInfo.displacement.minValueOverloadPercent);
  displacementProtectStage2.setValuesCount( DEFAULT_DISPLACEMENT_PROTECT_COUNT);
  displacementProtectStage2.setMode(        PROTECT_MODE_DISABLE);
  displacementEdgeProtect.setLimits(        GV.machineInfo.displacement.maxValue + GV.machineInfo.displacement.maxValue * GV.machineInfo.displacement.maxValueOverloadPercent,
                                            GV.machineInfo.displacement.minValue + GV.machineInfo.displacement.minValue * GV.machineInfo.displacement.minValueOverloadPercent);
  displacementEdgeProtect.setValuesCount(   DEFAULT_DISPLACEMENT_EDGE_PROTECT_COUNT);
  displacementEdgeProtect.setMode(          PROTECT_MODE_CONTINIUS);
  deformationProtect.setLimits(             GV.machineInfo.deformation.maxValue + GV.machineInfo.deformation.maxValue * GV.machineInfo.deformation.maxValueOverloadPercent,
                                            GV.machineInfo.deformation.minValue + GV.machineInfo.deformation.minValue * GV.machineInfo.deformation.minValueOverloadPercent);
  deformationProtect.setValuesCount(        DEFAULT_DEFORMATION_PROTECT_COUNT);
  deformationProtect.setMode(               PROTECT_MODE_DISABLE);
  deformationProtectStage2.setLimits(       GV.machineInfo.deformation.maxValue + GV.machineInfo.deformation.maxValue * GV.machineInfo.deformation.maxValueOverloadPercent,
                                            GV.machineInfo.deformation.minValue + GV.machineInfo.deformation.minValue * GV.machineInfo.deformation.minValueOverloadPercent);
  deformationProtectStage2.setValuesCount(  DEFAULT_DEFORMATION_PROTECT_COUNT);
  deformationProtectStage2.setMode(         PROTECT_MODE_DISABLE);
  deformationEdgeProtect.setLimits(         GV.machineInfo.deformation.maxValue + GV.machineInfo.deformation.maxValue * GV.machineInfo.deformation.maxValueOverloadPercent,
                                            GV.machineInfo.deformation.minValue + GV.machineInfo.deformation.minValue * GV.machineInfo.deformation.minValueOverloadPercent);
  deformationEdgeProtect.setValuesCount(    DEFAULT_DEFORMATION_EDGE_PROTECT_COUNT);
  deformationEdgeProtect.setMode(           PROTECT_MODE_CONTINIUS);
  return 0;
}
