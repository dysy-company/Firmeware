#ifndef FLASH_DATA_MAP
#define FLASH_DATA_MAP

#include <mbed.h>
#include "..\\..\\Global_Variables.h"

#if BOARD_INDEX == 2
//Masks for calculating FLASH-blocks from address
#define FLASH_SECTOR_ADDRESS_MASK                               0xFFFE0000
#define FLASH_PAGE_ADDRESS_MASK                                 0xFFFFFFE0
#define FLASH_OFFSET_OF_PAGE_MASK                               0x0001FFE0
#define FLASH_OFFSET_IN_PAGE_MASK                               0x0000001F

#define FLASH_START_ADDRESS                                     FLASH_BASE

#define FLASH_AREA_DIVIDER                                      64UL
//                                                              0x0002 0000         64
#define FLASH_AREA_SIZE                                         (FLASH_SECTOR_SIZE/FLASH_AREA_DIVIDER) //128kb/64 = 2kb == 256 doubles


//GLOBAL PARAMS OFFSET                                          0x0800 0000           0x0010 0000           0x0000 0800     =  0x0810 2800
#define GLOBAL_VARIABLES_FLASH_OFFSET                           (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 5 * FLASH_AREA_SIZE)
#endif

#if BOARD_INDEX == 3
//Masks for calculating FLASH-blocks from address
#define FLASH_SECTOR_ADDRESS_MASK                               0xFFFD0000 //0xFFFE0000
#define FLASH_PAGE_ADDRESS_MASK                                 0xFFFFFFFF
#define FLASH_OFFSET_OF_PAGE_MASK                               0x0002FFFF //0x0001FFFF
#define FLASH_OFFSET_IN_PAGE_MASK                               0x00000000

#define FLASH_START_ADDRESS                                     FLASH_BASE

#define FLASH_OFFSET                                            0x00000000UL //0x00040000UL //0x00020000UL

#define FLASH_AREA_DIVIDER                                      64UL
//                                                              0x0002 0000         64

#define FLASH_SECTOR_SIZE                                       0x00040000UL

#define FLASH_AREA_SIZE                                         (FLASH_SECTOR_SIZE/FLASH_AREA_DIVIDER) //128kb/64 = 2kb == 256 doubles


//GLOBAL PARAMS OFFSET                                          0x0800 0000           0x0010 0000           0x0000 0800     =  0x0810 2800
#define GLOBAL_VARIABLES_FLASH_OFFSET                           (FLASH_START_ADDRESS + FLASH_BANK_SIZE + FLASH_OFFSET)
#endif
//AXIS MODES OFFSET                                             
#define POSITION_AXIS_MODE_FLASH_OFFSET                         GLOBAL_VARIABLES_FLASH_OFFSET                                                                                               //0x0810 2800
#define STRAIN_AXIS_MODE_FLASH_OFFSET                           (POSITION_AXIS_MODE_FLASH_OFFSET                             + sizeof ((globalVariables_t*)(0))->positionAxisMode            )//0x0810 2804
#define DEFORMATION_AXIS_MODE_FLASH_OFFSET                      (STRAIN_AXIS_MODE_FLASH_OFFSET                               + sizeof ((globalVariables_t*)(0))->strainAxisMode              )//0x0810 2808
//INVERT OF AXIS MODE OFFSET
#define POSITION_INVERT_AXIS_FLASH_OFFSET                       (DEFORMATION_AXIS_MODE_FLASH_OFFSET                          + sizeof ((globalVariables_t*)(0))->deformationAxisMode         )//0x0810 280C
#define STRAIN_INVERT_AXIS_FLASH_OFFSET                         (POSITION_INVERT_AXIS_FLASH_OFFSET                           + sizeof ((globalVariables_t*)(0))->positionInvertAxis          )//0x0810 2810
#define DEFORMATION_INVERT_AXIS_FLASH_OFFSET                    (STRAIN_INVERT_AXIS_FLASH_OFFSET                             + sizeof ((globalVariables_t*)(0))->strainInvertAxis            )//0x0810 2814
//PISTON MODE OFFSET
#define PISTON_MODE_FLASH_OFFSET                                (DEFORMATION_INVERT_AXIS_FLASH_OFFSET                        + sizeof ((globalVariables_t*)(0))->deformationInvertAxis       )//0x0810 2818
//VALVE DIRECTION MODE
#define VALVE_DIRECTION_MODE_FLASH_OFFSET                       (PISTON_MODE_FLASH_OFFSET                                    + sizeof ((globalVariables_t*)(0))->pistonMode                  )//0x0810 281C
//PISTON PARAMS
#define PISTON_PARAMS_TOP_AREA_FLASH_OFFSET                     (VALVE_DIRECTION_MODE_FLASH_OFFSET                           + sizeof ((globalVariables_t*)(0))->valveDirectionMode          )//0x0810 2820
#define PISTON_PARAMS_BOTTOM_AREA_FLASH_OFFSET                  (PISTON_PARAMS_TOP_AREA_FLASH_OFFSET                         + sizeof ((globalVariables_t*)(0))->PistonParams.topArea        )//0x0810 2828
//VALVE PARAMS
#define VALVE_PARAMS_IMAX_FLASH_OFFSET                          (PISTON_PARAMS_BOTTOM_AREA_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->PistonParams.bottomArea     )//0x0810 2830
#define VALVE_PARAMS_QVALVE_FLASH_OFFSET                        (VALVE_PARAMS_IMAX_FLASH_OFFSET                              + sizeof ((globalVariables_t*)(0))->ValveParams.Imax            )//0x0810 2838
//STATIC TEST PARAMS
#define STATIC_TEST_POSITION_UPPER_THRESHOLD_FLASH_OFFSET       (VALVE_PARAMS_QVALVE_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->ValveParams.Qvalve          )//0x0810 2840
#define STATIC_TEST_POSITION_LOWER_THRESHOLD_FLASH_OFFSET       (STATIC_TEST_POSITION_UPPER_THRESHOLD_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->positionUpperThreshold      )//0x0810 2848
#define STATIC_TEST_STRAIN_UPPER_THRESHOLD_FLASH_OFFSET         (STATIC_TEST_POSITION_LOWER_THRESHOLD_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->positionLowerThreshold      )//0x0810 2850
#define STATIC_TEST_STRAIN_LOWER_THRESHOLD_FLASH_OFFSET         (STATIC_TEST_STRAIN_UPPER_THRESHOLD_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->strainUpperThreshold        )//0x0810 2858
#define STATIC_TEST_DEFORMATION_UPPER_THRESHOLD_FLASH_OFFSET    (STATIC_TEST_STRAIN_LOWER_THRESHOLD_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->strainLowerThreshold        )//0x0810 2860
#define STATIC_TEST_DEFORMATION_LOWER_THRESHOLD_FLASH_OFFSET    (STATIC_TEST_DEFORMATION_UPPER_THRESHOLD_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->deformationUpperThreshold   )//0x0810 2868 

#define ENCODER_STEP_VALUE_OFFSET                               (STATIC_TEST_DEFORMATION_LOWER_THRESHOLD_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->deformationLowerThreshold   )//0x0810 2870
#define MOTOR_DRIVER_TYPE_OFFSET                                (ENCODER_STEP_VALUE_OFFSET                                   + sizeof ((globalVariables_t*)(0))->encoderStepValue            )//0x0810 2878
#define CONTROLLER_ONLINE_MODE_OFFSET                           (MOTOR_DRIVER_TYPE_OFFSET                                    + sizeof ((globalVariables_t*)(0))->controllerOnlineMode        )//0x0810 287C
#define MOTOR_STEP_VALUE_OFFSET                                 (CONTROLLER_ONLINE_MODE_OFFSET                               + sizeof ((globalVariables_t*)(0))->motorStepValue              )//0x0810 2884
#define LIMITSWITCH_POLARITY_1_OFFSET                           (MOTOR_STEP_VALUE_OFFSET                                     + sizeof ((globalVariables_t*)(0))->LimitSwitchPolarity1        )//0x0810 2888
#define LIMITSWITCH_POLARITY_2_OFFSET                           (LIMITSWITCH_POLARITY_1_OFFSET                               + sizeof ((globalVariables_t*)(0))->LimitSwitchPolarity2        )//0x0810 288C
#define EMERGENCY_STOP_POLARITY_OFFSET                          (LIMITSWITCH_POLARITY_2_OFFSET                               + sizeof ((globalVariables_t*)(0))->EmergencyStopPolarity       )//0x0810 2890

#define DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET                   (EMERGENCY_STOP_POLARITY_OFFSET                              + sizeof ((globalVariables_t*)(0))->displOverrunStepBack        )//0x0810 2894
#define DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET                  (DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET                       + sizeof ((globalVariables_t*)(0))->displUnderrunStepBack       )//0x0810 2898
#define STRAIN_OVERRUN_STEP_BACK_OFFSET                         (DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET                      + sizeof ((globalVariables_t*)(0))->strainOverrunStepBack       )//0x0810 289C
#define STRAIN_UNDERRUN_STEP_BACK_OFFSET                        (STRAIN_OVERRUN_STEP_BACK_OFFSET                             + sizeof ((globalVariables_t*)(0))->strainUnderrunStepBack      )//0x0810 28A0
#define DEFORMATION_OVERRUN_STEP_BACK_OFFSET                    (STRAIN_UNDERRUN_STEP_BACK_OFFSET                            + sizeof ((globalVariables_t*)(0))->deformOverrunStepBack       )//0x0810 28A4
#define DEFORMATION_UNDERRUN_STEP_BACK_OFFSET                   (DEFORMATION_OVERRUN_STEP_BACK_OFFSET                        + sizeof ((globalVariables_t*)(0))->deformUnderrunStepBack      )//0x0810 28A8

//PID PARAMS
#define SIN_DISPLASEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET        (DEFORMATION_UNDERRUN_STEP_BACK_OFFSET        			    + sizeof ((globalVariables_t*)(0))->deformUnderrunStepBack  			            )
#define SIN_DISPLASEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET        (SIN_DISPLASEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.PIDParams.Kp         )
#define SIN_DISPLASEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET        (SIN_DISPLASEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.PIDParams.Ki         )
#define SIN_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET         (SIN_DISPLASEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.PIDParams.Kd         )
#define SIN_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET         (SIN_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.PIDParams.Kp          )
#define SIN_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET         (SIN_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.PIDParams.Ki          )
#define SIN_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET              (SIN_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.PIDParams.Kd          )
#define SIN_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET              (SIN_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.PIDParams.Kp               )
#define SIN_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET              (SIN_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.PIDParams.Ki               )
#define SINUS_BASED_DISPL_MODE_KP_PID_PARAMS_FLASH_OFFSET       (SIN_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.PIDParams.Kd               )
#define SINUS_BASED_DISPL_MODE_KI_PID_PARAMS_FLASH_OFFSET       (SINUS_BASED_DISPL_MODE_KP_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.PIDParams.Kp  )         
#define SINUS_BASED_DISPL_MODE_KD_PID_PARAMS_FLASH_OFFSET       (SINUS_BASED_DISPL_MODE_KI_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.PIDParams.Ki  )
#define SINUS_BASED_DEFORM_MODE_KP_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_DISPL_MODE_KD_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.PIDParams.Kd  )
#define SINUS_BASED_DEFORM_MODE_KI_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_DEFORM_MODE_KP_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.PIDParams.Kp   )
#define SINUS_BASED_DEFORM_MODE_KD_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_DEFORM_MODE_KI_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.PIDParams.Ki   )
#define SINUS_BASED_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_DEFORM_MODE_KD_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.PIDParams.Kd   )
#define SINUS_BASED_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.PIDParams.Kp        )
#define SINUS_BASED_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.PIDParams.Ki        )
#define CONST_DISPLACEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET      (SINUS_BASED_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.PIDParams.Kd        )
#define CONST_DISPLACEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET      (CONST_DISPLACEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.PIDParams.Kp       )
#define CONST_DISPLACEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET      (CONST_DISPLACEMENT_MODE_KI_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.PIDParams.Ki       )
#define CONST_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET       (CONST_DISPLACEMENT_MODE_KD_PID_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.PIDParams.Kd       )
#define CONST_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET       (CONST_DEFORMATION_MODE_KP_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.PIDParams.Kp        )
#define CONST_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET       (CONST_DEFORMATION_MODE_KI_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.PIDParams.Ki        )
#define CONST_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET            (CONST_DEFORMATION_MODE_KD_PID_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.PIDParams.Kd        )
#define CONST_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET            (CONST_STRAIN_MODE_KP_PID_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.PIDParams.Kp             )
#define CONST_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET            (CONST_STRAIN_MODE_KI_PID_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.PIDParams.Ki             )



//End of Global Variables

//MACHINE INFO
#define MACHINE_INFO_SECTION_SIZE                               0x00000100

#if BOARD_INDEX == 2
//                                                              0x0800 0000           0x0010 0000            0x0000 0800
#define MACHINE_INFO_OFFSET                                     (FLASH_START_ADDRESS + FLASH_BANK_SIZE  + 8 * FLASH_AREA_SIZE)                                    //0x0810 4000
#endif

#if BOARD_INDEX == 3
//                                                              0x0800 0000           0x0010 0000            0x0000 0800
#define MACHINE_INFO_OFFSET                                     (FLASH_START_ADDRESS + FLASH_BANK_SIZE  + 3 * FLASH_AREA_SIZE + FLASH_OFFSET)                                    //0x0810 4000
#endif

//MACHINE TYPE
#define MACHINE_TYPE_OFFSET                                     MACHINE_INFO_OFFSET                                                                             //0x0810 4000
//SERIAL NUMBER                                                                       
#define SERIAL_NUMBER_FLASH_OFFSET                              (MACHINE_TYPE_OFFSET                                         + sizeof ((globalVariables_t*)(0))->machineInfo.machineType     )//0x0810 4004                                                                 
//ID
#define ID_FLASH_OFFSET                                         (SERIAL_NUMBER_FLASH_OFFSET                                  + sizeof ((globalVariables_t*)(0))->machineInfo.serialNumber    )//0x0810 400C
//displacement channel info
#define DISPLACEMENT_CHANNEL_INFO_OFFSET                        (MACHINE_INFO_OFFSET + MACHINE_INFO_SECTION_SIZE                                                                                             )//0x0810 4100    
#define DISPLACEMENT_CHANNEL_INFO_SENSOR_TYPE                   (DISPLACEMENT_CHANNEL_INFO_OFFSET                                                                                                            )//0x0810 4100
#define DISPLACEMENT_CHANNEL_INFO_MAX_VALUE                     (DISPLACEMENT_CHANNEL_INFO_SENSOR_TYPE                   + sizeof ((globalVariables_t*)(0))->machineInfo.displacement.sensorType             )//0x0810 4108
#define DISPLACEMENT_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT    (DISPLACEMENT_CHANNEL_INFO_MAX_VALUE                     + sizeof ((globalVariables_t*)(0))->machineInfo.displacement.maxValue               )//0x0810 4110
#define DISPLACEMENT_CHANNEL_INFO_MIN_VALUE                     (DISPLACEMENT_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT    + sizeof ((globalVariables_t*)(0))->machineInfo.displacement.maxValueOverloadPercent)//0x0810 4118
#define DISPLACEMENT_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT    (DISPLACEMENT_CHANNEL_INFO_MIN_VALUE                     + sizeof ((globalVariables_t*)(0))->machineInfo.displacement.minValue               )//0x0810 4120
//strain channel info
#define STRAIN_CHANNEL_INFO_OFFSET                              (DISPLACEMENT_CHANNEL_INFO_OFFSET + MACHINE_INFO_SECTION_SIZE                                                                                )//0x0810 4200    
#define STRAIN_CHANNEL_INFO_SENSOR_TYPE                         (STRAIN_CHANNEL_INFO_OFFSET                                                                                                                  )//0x0810 4200
#define STRAIN_CHANNEL_INFO_MAX_VALUE                           (STRAIN_CHANNEL_INFO_SENSOR_TYPE                         + sizeof ((globalVariables_t*)(0))->machineInfo.strain.sensorType                   )//0x0810 4208
#define STRAIN_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT          (STRAIN_CHANNEL_INFO_MAX_VALUE                           + sizeof ((globalVariables_t*)(0))->machineInfo.strain.maxValue                     )//0x0810 4210
#define STRAIN_CHANNEL_INFO_MIN_VALUE                           (STRAIN_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT          + sizeof ((globalVariables_t*)(0))->machineInfo.strain.maxValueOverloadPercent      )//0x0810 4218
#define STRAIN_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT          (STRAIN_CHANNEL_INFO_MIN_VALUE                           + sizeof ((globalVariables_t*)(0))->machineInfo.strain.minValue                     )//0x0810 4220
//deformation channel info
#define DEFORMATION_CHANNEL_INFO_OFFSET                         (STRAIN_CHANNEL_INFO_OFFSET + MACHINE_INFO_SECTION_SIZE                                                                                      )//0x0810 4300    
#define DEFORMATION_CHANNEL_INFO_SENSOR_TYPE                    (DEFORMATION_CHANNEL_INFO_OFFSET                                                                                                             )//0x0810 4300
#define DEFORMATION_CHANNEL_INFO_MAX_VALUE                      (DEFORMATION_CHANNEL_INFO_SENSOR_TYPE                    + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.sensorType              )//0x0810 4308
#define DEFORMATION_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT     (DEFORMATION_CHANNEL_INFO_MAX_VALUE                      + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.maxValue                )//0x0810 4310
#define DEFORMATION_CHANNEL_INFO_MIN_VALUE                      (DEFORMATION_CHANNEL_INFO_MAX_VALUE_OVERLOAD_PERCENT     + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.maxValueOverloadPercent )//0x0810 4318
#define DEFORMATION_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT     (DEFORMATION_CHANNEL_INFO_MIN_VALUE                      + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.minValue                )//0x0810 4320

#if BOARD_INDEX == 2
//CALIBRATION COEFFS OFFSET                                     0x0800 0000           0x0010 0000           0x0000 0800
#define CALIBRATION_COEFS_FLASH_OFFSET                          (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 9 * FLASH_AREA_SIZE)                                     //0x0810 4800
#endif

#if BOARD_INDEX == 3
#define FLASH_SIZE_DATA_REGISTER             0x1FF1E880U
//#define FLASH_SECTOR_TOTAL                   8U                    /* 8 sectors */
#define FLASH_SIZE                           ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0xFFFFU)) ? 0x200000U : \
                                             ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x0000U)) ? 0x200000U : \
                                             (((uint32_t)(*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) & (0x0FFFU)) << 10U)))  /* 2 MB   */
#define FLASH_BANK_SIZE                      0x00100000U //(FLASH_SIZE >> 1)     /* 1 MB   */

//CALIBRATION COEFFS OFFSET                                     0x0800 0000           0x0010 0000           0x0000 0800
#define CALIBRATION_COEFS_FLASH_OFFSET                          (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 4 * FLASH_AREA_SIZE + FLASH_OFFSET)                                     //0x0810 4800
#endif

//CALIBRATION COEFFS    
#define POSITION_CALIBRATION_COEFS_FLASH_OFFSET                 CALIBRATION_COEFS_FLASH_OFFSET
#define STRAIN_CALIBRATION_COEFS_FLASH_OFFSET                   (POSITION_CALIBRATION_COEFS_FLASH_OFFSET             + 2UL * sizeof(double))
#define DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET              (STRAIN_CALIBRATION_COEFS_FLASH_OFFSET               + 2UL * sizeof(double))
//CALIBRATION POINTS SIZES  
#define POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET           (DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET          + 2UL * sizeof(double))
#define STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET             (POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET       + sizeof(uint32_t))
#define DEFORMATION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET        (STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET         + sizeof(uint32_t))
//reference voltages
#define POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET                 (DEFORMATION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET    + sizeof(uint32_t))
#define STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET                   (POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET             + sizeof(float))
#define DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET              (STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET               + sizeof(float))

#define DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET    (DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET          + sizeof(float))
#define DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET    (DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET + sizeof(uint32_t))

#if BOARD_INDEX == 2
//CALIBRATION POINTS OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_POINTS_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 10 * FLASH_AREA_SIZE)                                    //0x0810 5000
#endif

#if BOARD_INDEX == 3
//CALIBRATION POINTS OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_POINTS_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 5 * FLASH_AREA_SIZE + FLASH_OFFSET)                                  //0x0810 5000
#endif

//CALIBRATION POINTS        
#define STRAIN_CALIBRATION_POINTS_FLASH_OFFSET                  CALIBRATION_POINTS_FLASH_OFFSET //start of BANK2
#define STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE                FLASH_AREA_SIZE

#define POSITION_CALIBRATION_POINTS_FLASH_OFFSET                (CALIBRATION_POINTS_FLASH_OFFSET + STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE)
#define POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE              FLASH_AREA_SIZE

#define DEFORMATION_CALIBRATION_POINTS_FLASH_OFFSET             (CALIBRATION_POINTS_FLASH_OFFSET + STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE + POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE)
#define DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE           FLASH_AREA_SIZE

#define DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET      (CALIBRATION_POINTS_FLASH_OFFSET + STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE + POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE)
#define DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_MAX_SIZE    FLASH_AREA_SIZE

#define DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET      (CALIBRATION_POINTS_FLASH_OFFSET + STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE + POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_MAX_SIZE)
#define DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_MAX_SIZE    FLASH_AREA_SIZE

#endif