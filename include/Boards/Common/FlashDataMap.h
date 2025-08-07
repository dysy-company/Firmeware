#ifndef FLASH_DATA_MAP
#define FLASH_DATA_MAP

#include <mbed.h>
#include "..\\..\\Global_Variables.h"

#if BOARD_INDEX == 2
#define BACKUP_RAM_START_ADDRESS                                0x38800000
#define BACKUP_RAM_END_ADDRESS                                  0x38800FFF
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

#define FLASH_CALIBRATION_NOTE_AREA_SIZE                        0x00000020UL
#define FLASH_IP_PARAMS_AREA_SIZE                               0x00000020UL
#define FLASH_STRING_AREA_SIZE                                  0x00000080UL    

#if BOARD_INDEX == 3
#define BACKUP_RAM_START_ADDRESS                                0x40024000
#define BACKUP_RAM_END_ADDRESS                                  0x40024FFF
//Masks for calculating FLASH-blocks from address
#define FLASH_SECTOR_ADDRESS_MASK                               0xFFFE0000 //0xFFFE0000
#define FLASH_PAGE_ADDRESS_MASK                                 0xFFFFFFFF
#define FLASH_OFFSET_OF_PAGE_MASK                               0x0001FFFF //0x0001FFFF
#define FLASH_OFFSET_IN_PAGE_MASK                               0x00000000

#define FLASH_START_ADDRESS                                     FLASH_BASE

#define FLASH_OFFSET                                            0x00020000UL //0x00040000UL //0x00020000UL

#define FLASH_AREA_DIVIDER                                      64UL
//                                                              0x0002 0000         64

#define FLASH_SECTOR_SIZE                                       0x00020000UL

#define FLASH_AREA_SIZE                                         (FLASH_SECTOR_SIZE/FLASH_AREA_DIVIDER) //128kb/64 = 2kb == 256 doubles


//GLOBAL PARAMS OFFSET                                          0x0800 0000           0x0010 0000           0x0000 0800     =  0x0810 2800
#define GLOBAL_VARIABLES_FLASH_OFFSET                           (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 5 * FLASH_AREA_SIZE + FLASH_OFFSET)
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
#define CONTROLLER_ONLINE_MODE_OFFSET                           (MOTOR_DRIVER_TYPE_OFFSET                                    + sizeof ((globalVariables_t*)(0))->motorDriverType             )//0x0810 287C
#define MOTOR_STEP_VALUE_OFFSET                                 (CONTROLLER_ONLINE_MODE_OFFSET                               + sizeof ((globalVariables_t*)(0))->controllerOnlineMode        )//0x0810 2884
#define LIMITSWITCH_POLARITY_1_OFFSET                           (MOTOR_STEP_VALUE_OFFSET                                     + sizeof ((globalVariables_t*)(0))->motorStepValue              )//0x0810 2888
#define LIMITSWITCH_POLARITY_2_OFFSET                           (LIMITSWITCH_POLARITY_1_OFFSET                               + sizeof ((globalVariables_t*)(0))->LimitSwitchPolarity1        )//0x0810 288C
#define EMERGENCY_STOP_POLARITY_OFFSET                          (LIMITSWITCH_POLARITY_2_OFFSET                               + sizeof ((globalVariables_t*)(0))->LimitSwitchPolarity2        )//0x0810 2890

#define DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET                   (EMERGENCY_STOP_POLARITY_OFFSET                              + sizeof ((globalVariables_t*)(0))->EmergencyStopPolarity       )//0x0810 2894
#define DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET                  (DISPLACEMENT_OVERRUN_STEP_BACK_OFFSET                       + sizeof ((globalVariables_t*)(0))->displOverrunStepBack        )//0x0810 2898
#define STRAIN_OVERRUN_STEP_BACK_OFFSET                         (DISPLACEMENT_UNDERRUN_STEP_BACK_OFFSET                      + sizeof ((globalVariables_t*)(0))->displUnderrunStepBack       )//0x0810 289C
#define STRAIN_UNDERRUN_STEP_BACK_OFFSET                        (STRAIN_OVERRUN_STEP_BACK_OFFSET                             + sizeof ((globalVariables_t*)(0))->strainOverrunStepBack       )//0x0810 28A0
#define DEFORMATION_OVERRUN_STEP_BACK_OFFSET                    (STRAIN_UNDERRUN_STEP_BACK_OFFSET                            + sizeof ((globalVariables_t*)(0))->strainUnderrunStepBack      )//0x0810 28A4
#define DEFORMATION_UNDERRUN_STEP_BACK_OFFSET                   (DEFORMATION_OVERRUN_STEP_BACK_OFFSET                        + sizeof ((globalVariables_t*)(0))->deformOverrunStepBack       )//0x0810 28A8

#define SSI_NULL_OFFSET_FLASH_OFFSET                            (DEFORMATION_UNDERRUN_STEP_BACK_OFFSET                       + sizeof ((globalVariables_t*)(0))->deformUnderrunStepBack      )//0x0810 28AC

//PID PARAMS
#define SIN_DISPLASEMENT_MODE_KP_PID_PARAMS_FLASH_OFFSET        (SSI_NULL_OFFSET_FLASH_OFFSET         						 + sizeof ((globalVariables_t*)(0))->SSINullOffset    			                    )
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

#define PWM_FREQ_FLASH_OFFSET                                   (CONST_STRAIN_MODE_KD_PID_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.PIDParams.Kd             )

#define DEFORMATION_ENCODER_STEP_VALUE_OFFSET                   (PWM_FREQ_FLASH_OFFSET                              		 + sizeof ((globalVariables_t*)(0))->PWMFreq                                        )

//Max Voltage Mods Params
#define SIN_DISPLASEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET      (DEFORMATION_ENCODER_STEP_VALUE_OFFSET                       + sizeof ((globalVariables_t*)(0))->encoderStepValue                               )
#define SIN_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET       (SIN_DISPLASEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.MaxVoltage           )
#define SIN_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET            (SIN_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.MaxVoltage            )
#define SINUS_BASED_DISPL_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET     (SIN_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.MaxVoltage                 )
#define SINUS_BASED_DEFORM_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET    (SINUS_BASED_DISPL_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET         + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.MaxVoltage    )
#define SINUS_BASED_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET    (SINUS_BASED_DEFORM_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.MaxVoltage     )
#define CONST_DISPLACEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET    (SINUS_BASED_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.MaxVoltage          )
#define CONST_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET     (CONST_DISPLACEMENT_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.MaxVoltage         )
#define CONST_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET          (CONST_DEFORMATION_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET         + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.MaxVoltage          )
#define SIN_VOLTAGE_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET           (CONST_STRAIN_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.MaxVoltage               )

//Const Displacement Params
#define CONST_DISPLACEMENT_MODE_MAX_DEV_PARAMS_FLASH_OFFSET     (SIN_VOLTAGE_MODE_MAX_VOLT_PARAMS_FLASH_OFFSET               + sizeof ((globalVariables_t*)(0))->SINVoltageModeParams.MaxVoltage                )
#define CONST_DISPLACEMENT_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET   (CONST_DISPLACEMENT_MODE_MAX_DEV_PARAMS_FLASH_OFFSET         + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.MaxDeviation       )
#define CONST_DISPLACEMENT_MODE_SPEED_PARAMS_FLASH_OFFSET       (CONST_DISPLACEMENT_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET       + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.ModeFrequency      )
#define CONST_DISPLACEMENT_MODE_MAX_SPEED_PARAMS_FLASH_OFFSET   (CONST_DISPLACEMENT_MODE_SPEED_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.Speed              )
#define CONST_DISPLACEMENT_MODE_DELTA_PARAMS_FLASH_OFFSET       (CONST_DISPLACEMENT_MODE_MAX_SPEED_PARAMS_FLASH_OFFSET       + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.MaxSpeed           )

//Max Steps and delta
#define CONST_STRAIN_MODE_DELTA_PARAMS_FLASH_OFFSET             (CONST_DISPLACEMENT_MODE_DELTA_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.delta              )
#define CONST_DEFORMATION_MODE_DELTA_PARAMS_FLASH_OFFSET        (CONST_STRAIN_MODE_DELTA_PARAMS_FLASH_OFFSET                 + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.delta                    )
#define SIN_DISPLASEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET      (CONST_DEFORMATION_MODE_DELTA_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.delta               )
#define SIN_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET       (SIN_DISPLASEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.MaxSteps             )
#define SIN_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET            (SIN_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.MaxSteps              )
#define SINUS_BASED_DISPL_MODE_MAX_STEP_PARAMS_FLASH_OFFSET     (SIN_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.MaxSteps                   )
#define SINUS_BASED_DEFORM_MODE_MAX_STEP_PARAMS_FLASH_OFFSET    (SINUS_BASED_DISPL_MODE_MAX_STEP_PARAMS_FLASH_OFFSET         + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.MaxSteps      )
#define SINUS_BASED_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET    (SINUS_BASED_DEFORM_MODE_MAX_STEP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.MaxSteps       )
#define CONST_DISPLACEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET    (SINUS_BASED_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.MaxSteps            )
#define CONST_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET     (CONST_DISPLACEMENT_MODE_MAX_STEP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->ConstDisplacementModeParams.MaxSteps           )
#define CONST_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET          (CONST_DEFORMATION_MODE_MAX_STEP_PARAMS_FLASH_OFFSET         + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.MaxSteps            )

//TCycle time
#define T_CYCLE_TIME_PARAMS_FLASH_OFFSET                        (CONST_STRAIN_MODE_MAX_STEP_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.MaxSteps                 )

//Const mode params
#define CONST_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET                (T_CYCLE_TIME_PARAMS_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->TcycleTime                                     )

//Const strain mode params
#define CONST_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET                (CONST_MODE_MODE_FREQ_PARAMS_FLASH_OFFSET                    + sizeof ((globalVariables_t*)(0))->ConstModeParams.ConstFrequency                 )
#define CONST_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET              (CONST_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET                    + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.MaxDeviation             )   
#define CONST_STRAIN_SPEED_PARAMS_FLASH_OFFSET                  (CONST_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.ModeFrequency            )              
#define CONST_STRAIN_MAX_SPEED_PARAMS_FLASH_OFFSET              (CONST_STRAIN_SPEED_PARAMS_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.Speed                    )
#define CONST_STRAIN_DELTA_PARAMS_FLASH_OFFSET                  (CONST_STRAIN_MAX_SPEED_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.MaxSpeed                 )

//Const deformation mode params
#define CONST_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET           (CONST_STRAIN_DELTA_PARAMS_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->ConstStrainModeParams.delta                    )
#define CONST_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET         (CONST_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET               + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.MaxDeviation        ) 
#define CONST_DEFORMATION_SPEED_PARAMS_FLASH_OFFSET             (CONST_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.ModeFrequency       )      
#define CONST_DEFORMATION_MAX_SPEED_PARAMS_FLASH_OFFSET         (CONST_DEFORMATION_SPEED_PARAMS_FLASH_OFFSET                 + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.Speed               )  
#define CONST_DEFORMATION_DELTA_PARAMS_FLASH_OFFSET             (CONST_DEFORMATION_MAX_SPEED_PARAMS_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.MaxSpeed            )      

//Sinus displacement mode params 
#define SIN_DISPLASEMENT_MAX_DEV_PARAMS_FLASH_OFFSET            (CONST_DEFORMATION_DELTA_PARAMS_FLASH_OFFSET                 + sizeof ((globalVariables_t*)(0))->ConstDeformationModeParams.delta                       )
#define SIN_DISPLASEMENT_MODE_FREQ_PARAMS_FLASH_OFFSET          (SIN_DISPLASEMENT_MAX_DEV_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.MaxDeviation                 )
#define SIN_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET            (SIN_DISPLASEMENT_MODE_FREQ_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.ModeFrequency                )
#define SIN_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET          (SIN_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.UpKP       )     
#define SIN_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET            (SIN_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.DownKP     )
#define SIN_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET          (SIN_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.UpKI       )
#define SIN_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET            (SIN_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.DownKI     )
#define SIN_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET          (SIN_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.UpKD       )

//Sinus strain mode params
#define SIN_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET                  (SIN_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.DownKD     )
#define SIN_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET                (SIN_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.MaxDeviation                       )
#define SIN_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET          (SIN_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET                    + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.ModeFrequency                      )
#define SIN_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET        (SIN_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.UpKP             )
#define SIN_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET          (SIN_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.DownKP           )
#define SIN_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET        (SIN_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.UpKI             )
#define SIN_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET          (SIN_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.DownKI           )
#define SIN_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET        (SIN_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.UpKD             )

//Sinus deformation mode params
#define SIN_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET             (SIN_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.DownKD           )
#define SIN_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET           (SIN_DEFORMATION_MAX_DEV_PARAMS_FLASH_OFFSET                 + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.MaxDeviation                  )
#define SIN_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET          (SIN_DEFORMATION_MODE_FREQ_PARAMS_FLASH_OFFSET               + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.ModeFrequency                 )
#define SIN_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET        (SIN_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.UpKP        )
#define SIN_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET          (SIN_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.DownKP      )
#define SIN_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET        (SIN_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.UpKI        )
#define SIN_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET          (SIN_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.DownKI      )
#define SIN_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET        (SIN_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.UpKD        )

//Sinus based displacement mode params
#define SIN_BASED_DISP_MAX_DEV_PARAMS_FLASH_OFFSET              (SIN_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.DownKD              )
#define SIN_BASED_DISP_MODE_FREQ_PARAMS_FLASH_OFFSET            (SIN_BASED_DISP_MAX_DEV_PARAMS_FLASH_OFFSET                  + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.MaxDeviation                  )
#define SIN_BASED_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET      (SIN_BASED_DISP_MODE_FREQ_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.ModeFrequency                 )
#define SIN_BASED_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET    (SIN_BASED_DISP_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKP        )
#define SIN_BASED_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET      (SIN_BASED_DISP_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKP      )
#define SIN_BASED_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET    (SIN_BASED_DISP_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKI        )
#define SIN_BASED_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET      (SIN_BASED_DISP_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKI      )
#define SIN_BASED_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET    (SIN_BASED_DISP_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET          + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.UpKD        )

//Sinus based strain mode params
#define SIN_BASED_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET            (SIN_BASED_DISP_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.DownKD      )
#define SIN_BASED_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET          (SIN_BASED_STRAIN_MAX_DEV_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.MaxDeviation                        )
#define SIN_BASED_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET    (SIN_BASED_STRAIN_MODE_FREQ_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.ModeFrequency                       )
#define SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET  (SIN_BASED_STRAIN_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKP              )
#define SIN_BASED_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET    (SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKP            )
#define SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET  (SIN_BASED_STRAIN_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKI              )
#define SIN_BASED_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET    (SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKI            )
#define SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET  (SIN_BASED_STRAIN_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.UpKD              )

//Sinus based deformation mode params
#define SIN_BASED_DEFORM_MAX_DEV_PARAMS_FLASH_OFFSET            (SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.DownKD            )
#define SIN_BASED_DEFORM_MODE_FREQ_PARAMS_FLASH_OFFSET          (SIN_BASED_DEFORM_MAX_DEV_PARAMS_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.MaxDeviation                   )
#define SIN_BASED_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET    (SIN_BASED_DEFORM_MODE_FREQ_PARAMS_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.ModeFrequency                  )
#define SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET  (SIN_BASED_DEFORM_AMPL_TUNE_UP_KP_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKP         )
#define SIN_BASED_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET    (SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKP       )
#define SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET  (SIN_BASED_DEFORM_AMPL_TUNE_UP_KI_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKI         )
#define SIN_BASED_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET    (SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKI       )
#define SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET  (SIN_BASED_DEFORM_AMPL_TUNE_UP_KD_PARAMS_FLASH_OFFSET        + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.UpKD         )   //0x0810 2C58

//SSI sensor resolution
#define SSI_SENSOR_RESOLUTION_FLASH_OFFSET                      (SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD_PARAMS_FLASH_OFFSET      + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.DownKD       )   //0x0810 2C60
//strain button protection
#define STRAIN_BUTTON_PROTECTION_UPPER_LIMIT                    (SSI_SENSOR_RESOLUTION_FLASH_OFFSET                          + sizeof ((globalVariables_t*)(0))->SSISensorResolution                                            )   //0x0810 2C68
#define STRAIN_BUTTON_PROTECTION_LOWER_LIMIT                    (STRAIN_BUTTON_PROTECTION_UPPER_LIMIT                        + sizeof ((globalVariables_t*)(0))->strainButtonUpperLimit                                         )   //0x0810 2C6C

//MotorDriver commands active levels
#define ENABLE_ACTIVE_LEVEL_FLASH_OFFSET                        (STRAIN_BUTTON_PROTECTION_LOWER_LIMIT                        + sizeof ((globalVariables_t*)(0))->strainButtonLowerLimit                                         )   //0x0810 2C70
#define CLR_ACTIVE_LEVEL_FLASH_OFFSET                           (ENABLE_ACTIVE_LEVEL_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->enableActiveLevel                                              )   //0x0810 2C71
#define CWL_ACTIVE_LEVEL_FLASH_OFFSET                           (CLR_ACTIVE_LEVEL_FLASH_OFFSET                               + sizeof ((globalVariables_t*)(0))->CLRActiveLevel                                                 )   //0x0810 2C72
#define CCWL_ACTIVE_LEVEL_FLASH_OFFSET                          (CWL_ACTIVE_LEVEL_FLASH_OFFSET                               + sizeof ((globalVariables_t*)(0))->CWLActiveLevel                                                 )   //0x0810 2C73

//Speed by button
#define REGULAR_SPEED_BY_BUTTON_FLASH_OFFSET                    (CCWL_ACTIVE_LEVEL_FLASH_OFFSET                              + sizeof ((globalVariables_t*)(0))->CCWLActiveLevel                                                )   //0x0810 2C74
#define FAST_SPEED_BY_BUTTON_FLASH_OFFSET                       (REGULAR_SPEED_BY_BUTTON_FLASH_OFFSET                        + sizeof ((globalVariables_t*)(0))->displButtonRegularSpeed                                        )   //0x0810 2C78
//tcycle for flash writing
#define TCYCLE_FOR_FLASH_WRITING_FLASH_OFFSET                   (FAST_SPEED_BY_BUTTON_FLASH_OFFSET                           + sizeof ((globalVariables_t*)(0))->displButtonFastSpeed                                           )   //0x0810 2C7C
//cyclic delta for protection
#define STRAIN_CYCLIC_DELTA_FLASH_OFFSET                        (TCYCLE_FOR_FLASH_WRITING_FLASH_OFFSET                       + sizeof ((globalVariables_t*)(0))->TcycleTimeFlashWriting                                         )   //0x0810 2C84
#define DISPLACEMENT_CYCLIC_DELTA_FLASH_OFFSET                  (STRAIN_CYCLIC_DELTA_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->strainCyclicDelta                                              )   //0x0810 2C88
#define DEFORMATION_CYCLIC_DELTA_FLASH_OFFSET                   (DISPLACEMENT_CYCLIC_DELTA_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->displacementCyclicDelta                                        )   //0x0810 2C8C

//Digital valve params
#define MAX_POSITION_FLASH_OFFSET                               (DEFORMATION_CYCLIC_DELTA_FLASH_OFFSET                       + sizeof ((globalVariables_t*)(0))->deformationCyclicDelta                                         )   //0x0810 2C90
#define MIDDLE_POSITION_FLASH_OFFSET                            (MAX_POSITION_FLASH_OFFSET                                   + sizeof ((globalVariables_t*)(0))->maxPosition                                                    )   //0x0810 2C94                            
#define MIDDLE_DOWN_THRESHOLD_FLASH_OFFSET                      (MIDDLE_UP_THRESHOLD_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->middleUpThreshold                                              )   //0x0810 2C9C                          
#define MIDDLE_UP_THRESHOLD_FLASH_OFFSET                        (MIDDLE_POSITION_FLASH_OFFSET                                + sizeof ((globalVariables_t*)(0))->middlePosition                                                 )   //0x0810 2C98                         
#define POSITION_DIVIDER_FLASH_OFFSET                           (MIDDLE_DOWN_THRESHOLD_FLASH_OFFSET                          + sizeof ((globalVariables_t*)(0))->middleDownThreshold                                            )   //0x0810 2CA0
#define VALVE_INVERT_AXIS_FLASH_OFFSET                          (POSITION_DIVIDER_FLASH_OFFSET                               + sizeof ((globalVariables_t*)(0))->positionDivider                                                )   //0x0810 2CA4

//Amplitude tune coefs
#define MIN_DELTA_RATIO_FOR_NULLPOINT_ATTEN_FLASH_OFFSET        (VALVE_INVERT_AXIS_FLASH_OFFSET                              + sizeof ((globalVariables_t*)(0))->valveInvertAxis                                                )   //0x0810 2CA8
#define MIN_AMPL_FOR_DISPL_NULLPOINT_ATTEN_FLASH_OFFSET         (MIN_DELTA_RATIO_FOR_NULLPOINT_ATTEN_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->minDeltaRatioForNullPointAttenuating                           )   //0x0810 2CB0
#define MIN_AMPL_FOR_DEFORM_NULLPOINT_ATTEN_FLASH_OFFSET        (MIN_AMPL_FOR_DISPL_NULLPOINT_ATTEN_FLASH_OFFSET             + sizeof ((globalVariables_t*)(0))->minAmplForDisplNullPointAttenuating                            )   //0x0810 2CB8
#define MIN_AMPL_FOR_STRAIN_NULLPOINT_ATTEN_FLASH_OFFSET        (MIN_AMPL_FOR_DEFORM_NULLPOINT_ATTEN_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->minAmplForDeformNullPointAttenuating                           )   //0x0810 2CC0
#define START_STOP_AMPLITUDE_RATIO_FLASH_OFFSET                 (MIN_AMPL_FOR_STRAIN_NULLPOINT_ATTEN_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->minAmplForStrainNullPointAttenuating                           )   //0x0810 2CC8
#define AMPLITUDE_PRECISION_FLASH_OFFSET                        (START_STOP_AMPLITUDE_RATIO_FLASH_OFFSET                     + sizeof ((globalVariables_t*)(0))->startStopAmplitudeRatio                                        )   //0x0810 2CD0
#define TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT_FLASH_OFFSET        (AMPLITUDE_PRECISION_FLASH_OFFSET                            + sizeof ((globalVariables_t*)(0))->amplitudePrecision                                             )   //0x0810 2CD8
#define STEP_FOR_NULLPOINT_GET_CORRECTION_FLASH_OFFSET          (TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT_FLASH_OFFSET            + sizeof ((globalVariables_t*)(0))->tresholdForNullPointDeltaAccept                                )   //0x0810 2CDC
#define MIN_MAX_CALCULATING_COUNTS_FLASH_OFFSET                 (STEP_FOR_NULLPOINT_GET_CORRECTION_FLASH_OFFSET              + sizeof ((globalVariables_t*)(0))->stepForNullPointGetCorrection                                  )   //0x0810 2CE0
#define ANCHOR_SIN_FREQUENCY_START_FLASH_OFFSET                 (MIN_MAX_CALCULATING_COUNTS_FLASH_OFFSET                     + sizeof ((globalVariables_t*)(0))->minMaxCalculatingCounts                                        )   //0x0810 2CE4
#define ANCHOR_SIN_FREQUENCY_STOP_FLASH_OFFSET                  (ANCHOR_SIN_FREQUENCY_START_FLASH_OFFSET                     + sizeof ((globalVariables_t*)(0))->anchorSinFrequency                                             )   //0x0810 2CEC

//Middle piston position
#define MIDDLE_PISTON_POSITION_FLASH_OFFSET                     (ANCHOR_SIN_FREQUENCY_STOP_FLASH_OFFSET                      + sizeof ((globalVariables_t*)(0))->anchorSinFrequencyStop                                         )   //0x0810 2CF4

//Deformation units
#define DEFORMATION_UNITS_FLASH_OFFSET                          (MIDDLE_PISTON_POSITION_FLASH_OFFSET                         + sizeof ((globalVariables_t*)(0))->middlePistonPosition                                           )   //0x0810 2CFC
//Ampl tune coefs continue
#define START_STOP_AMPLITUDE_RATIO_STOP_FLASH_OFFSET            (DEFORMATION_UNITS_FLASH_OFFSET                              + sizeof ((globalVariables_t*)(0))->DeformationUnits                                               )   //0x0810 2D00
#define MIN_MAX_CALCULATING_COUNTS_MAIN_PROC_FLASH_OFFSET       (START_STOP_AMPLITUDE_RATIO_STOP_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->stopAmplitudeRatio                                             )   //0x0810 2D08

//Null point PIDs
#define SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS         (MIN_MAX_CALCULATING_COUNTS_MAIN_PROC_FLASH_OFFSET           + sizeof ((globalVariables_t*)(0))->minMaxCalculatingCountsMainProcess                             )   //0x0810 2D1C
#define SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS         (SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS             + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKP        )   //0x0810 2D24
#define SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS         (SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS             + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKI        )   //0x0810 2D2C
#define SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS       (SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS             + sizeof ((globalVariables_t*)(0))->SINDisplacementModeParams.amplitudeTuneInfo.NullPointKD        )   //0x0810 2D34
#define SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS       (SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.NullPointKP              )   //0x0810 2D3C
#define SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS       (SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.NullPointKI              )   //0x0810 2D44
#define SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS       (SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINStrainModeParams.amplitudeTuneInfo.NullPointKD              )   //0x0810 2D4C
#define SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS       (SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.NullPointKP         )   //0x0810 2D54
#define SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS       (SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.NullPointKI         )   //0x0810 2D5C
#define SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS   (SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS           + sizeof ((globalVariables_t*)(0))->SINDeformationModeParams.amplitudeTuneInfo.NullPointKD         )   //0x0810 2D64
#define SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS   (SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS       + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKP )   //0x0810 2D6C
#define SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS   (SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS       + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKI )   //0x0810 2D74
#define SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS (SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS       + sizeof ((globalVariables_t*)(0))->SinusBasedDisplacementModeParams.amplitudeTuneInfo.NullPointKD )   //0x0810 2D7C
#define SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS (SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKP       )   //0x0810 2D84
#define SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS (SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKI       )   //0x0810 2D8C
#define SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS (SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedStrainModeParams.amplitudeTuneInfo.NullPointKD       )   //0x0810 2D94
#define SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS (SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKP  )   //0x0810 2D9C
#define SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS (SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKI  )   //0x0810 2DA4

#define BLINDE_PART_CYCL_STRAIN_PRPOT_FLASH_OFFS                (SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD_FLASH_OFFS     + sizeof ((globalVariables_t*)(0))->SinusBasedDeformationModeParams.amplitudeTuneInfo.NullPointKD  )   //0x0810 2DAC
#define BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FLASH_OFFS        (BLINDE_PART_CYCL_STRAIN_PRPOT_FLASH_OFFS                    + sizeof ((globalVariables_t*)(0))->blindePartOfCyclicStrainProtection                             )   //0x0810 2DB4
#define BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST_FLASH_OFFS          (BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FLASH_OFFS            + sizeof ((globalVariables_t*)(0))->defaultBlindePartOfCyclicStrainProtection                      )   //0x0810 2DBC
#define BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST_FLASH_OFFS  (BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST_FLASH_OFFS              + sizeof ((globalVariables_t*)(0))->blindePartOfCyclicStrainProtectionFirst                        )   //0x0810 2DC4
#define DELTA_CYCLIC_PROTECTION_FLASH_OFFS                      (BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST_FLASH_OFFS      + sizeof ((globalVariables_t*)(0))->defaultBlindePartOfCyclicStrainProtectionFirst                 )   //0x0810 2DCC
#define DELTA_CYCLIC_PROTECTION_DEFAULT_FLASH_OFFS              (DELTA_CYCLIC_PROTECTION_FLASH_OFFS                          + sizeof ((globalVariables_t*)(0))->deltaCyclicProtection                                          )   //0x0810 2DD4
#define MULTIPLIER_FLASH_OFFS                                   (DELTA_CYCLIC_PROTECTION_DEFAULT_FLASH_OFFS                  + sizeof ((globalVariables_t*)(0))->deltaCyclicProtectionDefault                                   )   //0x0810 2DDC
#define MULTIPLIER_DEFAULT_FLASH_OFFS                           (MULTIPLIER_FLASH_OFFS                                       + sizeof ((globalVariables_t*)(0))->multiplier                                                     )   //0x0810 2DE4


//End of Global Variables

//MACHINE INFO
#define MACHINE_INFO_SECTION_SIZE                               0x00000100

#if BOARD_INDEX == 2
//                                                              0x0800 0000           0x0010 0000            0x0000 0800
#define MACHINE_INFO_OFFSET                                     (FLASH_START_ADDRESS + FLASH_BANK_SIZE  + 8 * FLASH_AREA_SIZE)                                    //0x0810 4000
#endif

#if BOARD_INDEX == 3
//                                                              0x0800 0000           0x0010 0000            0x0000 0800
#define MACHINE_INFO_OFFSET                                     (FLASH_START_ADDRESS + FLASH_BANK_SIZE  + 8 * FLASH_AREA_SIZE + FLASH_OFFSET)                                    //0x0810 4000
#endif

//MACHINE TYPE
#define MACHINE_TYPE_OFFSET                                     MACHINE_INFO_OFFSET                                                                             //0x0810 4000
//SERIAL NUMBER                                                                       
#define SERIAL_NUMBER_FLASH_OFFSET                              (MACHINE_TYPE_OFFSET                                         + sizeof ((globalVariables_t*)(0))->machineInfo.machineType     )//0x0810 4004                                                                 
//ID
#define ID_FLASH_OFFSET                                         (SERIAL_NUMBER_FLASH_OFFSET                                  + sizeof ((globalVariables_t*)(0))->machineInfo.serialNumber    )//0x0810 400C
//Ethernet protocol version
#define ETHERNET_PROTOCOL_VERSION_OFFSET                        (ID_FLASH_OFFSET                                             + sizeof ((globalVariables_t*)(0))->machineInfo.id              )//0x0810 400E
//IP address
#define IP_ADDRESS_FLASH_OFFSET                                 (ETHERNET_PROTOCOL_VERSION_OFFSET                            + sizeof ((globalVariables_t*)(0))->machineInfo.ethernetProtocolVersion     )//0x0810 4010
#define NET_MASK_FLASH_OFFSET                                   (IP_ADDRESS_FLASH_OFFSET                                     + FLASH_IP_PARAMS_AREA_SIZE                                     )//0x0810 4030
#define GATEWAY_FLASH_OFFSET                                    (NET_MASK_FLASH_OFFSET                                       + FLASH_IP_PARAMS_AREA_SIZE                                     )//0x0810 4050
#define PORT_FLASH_OFFSET                                       (GATEWAY_FLASH_OFFSET                                        + FLASH_IP_PARAMS_AREA_SIZE                                     )//0x0810 4070
//Ethernet connection timeout to stop test process
#define ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST_OFFSET   (PORT_FLASH_OFFSET                                           + FLASH_IP_PARAMS_AREA_SIZE                                     )//0x0810 4090

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
//deformation channels
#define DEFORMATION_SENSOR_TYPE_CH1_FLASH_OFFSET                (DEFORMATION_CHANNEL_INFO_MIN_VALUE_OVERLOAD_PERCENT     + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.minValueOverloadPercent )
#define DEFORMATION_SENSOR_TYPE_CH2_FLASH_OFFSET                (DEFORMATION_SENSOR_TYPE_CH1_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.sensorTypes[0]          )
#define DEFORMATION_SENSOR_TYPE_CH3_FLASH_OFFSET                (DEFORMATION_SENSOR_TYPE_CH2_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.sensorTypes[1]          )            
#define DEFORMATION_SENSOR_TYPE_CH4_FLASH_OFFSET                (DEFORMATION_SENSOR_TYPE_CH3_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.sensorTypes[2]          )
#define ACTIVE_DEFORMATION_CHANNELS_FLASH_OFFSET                (DEFORMATION_SENSOR_TYPE_CH4_FLASH_OFFSET                + sizeof ((globalVariables_t*)(0))->machineInfo.deformation.sensorTypes[3]          ) 

#if BOARD_INDEX == 2
//CALIBRATION COEFFS OFFSET                                     0x0800 0000           0x0010 0000           0x0000 0800
#define CALIBRATION_COEFS_FLASH_OFFSET                          (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 9 * FLASH_AREA_SIZE      )                               //0x0810 4800
#endif

#if BOARD_INDEX == 3
#define FLASH_SIZE_DATA_REGISTER             0x1FF1E880U
//#define FLASH_SECTOR_TOTAL                   8U                    /* 8 sectors */
#define FLASH_SIZE                           ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0xFFFFU)) ? 0x200000U : \
                                             ((((*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) == 0x0000U)) ? 0x200000U : \
                                             (((uint32_t)(*((uint16_t *)FLASH_SIZE_DATA_REGISTER)) & (0x0FFFU)) << 10U)))  /* 2 MB   */
#define FLASH_BANK_SIZE                      0x00100000U //(FLASH_SIZE >> 1)     /* 1 MB   */

//CALIBRATION COEFFS OFFSET                                     0x0800 0000           0x0010 0000           0x0000 0800
#define CALIBRATION_COEFS_FLASH_OFFSET                          (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 9 * FLASH_AREA_SIZE + FLASH_OFFSET)                                     //0x0810 4800
#endif

//CALIBRATION COEFFS    
#define POSITION_CALIBRATION_COEFS_FLASH_OFFSET                 CALIBRATION_COEFS_FLASH_OFFSET
#define STRAIN_CALIBRATION_COEFS_FLASH_OFFSET                   (POSITION_CALIBRATION_COEFS_FLASH_OFFSET             + 2UL * sizeof(double) )
#define DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET              (STRAIN_CALIBRATION_COEFS_FLASH_OFFSET               + 2UL * sizeof(double) )
//CALIBRATION POINTS SIZES  
#define POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET           (DEFORMATION_CALIBRATION_COEFS_FLASH_OFFSET          + 2UL * sizeof(double) )
#define STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET             (POSITION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET       + sizeof(uint32_t)     )
#define DEFORMATION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET        (STRAIN_CALIBRATION_POINTS_SIZE_FLASH_OFFSET         + sizeof(uint32_t)     )
//reference voltages
#define POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET                 (DEFORMATION_CALIBRATION_POINTS_SIZE_FLASH_OFFSET    + sizeof(uint32_t)     )
#define STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET                   (POSITION_REFERENCE_VOLTAGE_FLASH_OFFSET             + sizeof(float)        )
#define DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET              (STRAIN_REFERENCE_VOLTAGE_FLASH_OFFSET               + sizeof(float)        )

#define DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET    (DEFORMATION_REFERENCE_VOLTAGE_FLASH_OFFSET           + sizeof(float)       )
#define DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET    (DEFORMATION_CALIBRATION_POINTS_SIZE_2CH_FLASH_OFFSET + sizeof(uint32_t)    )
#define DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET    (DEFORMATION_CALIBRATION_POINTS_SIZE_3RD_FLASH_OFFSET + sizeof(uint32_t)    )

#define POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET     (DEFORMATION_CALIBRATION_POINTS_SIZE_4TH_FLASH_OFFSET + sizeof(uint32_t)    )
#define STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET       (POSITION_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET  + sizeof(uint32_t)    )
#define STRAIN_CALIBRATION_POINTS_SIZE_2_FLASH_OFFSET           (STRAIN_SPEED_CALIBRATION_POINTS_SIZE_FLASH_OFFSET    + sizeof(uint32_t)    )

#if BOARD_INDEX == 2
//CALIBRATION POINTS OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_POINTS_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 10 * FLASH_AREA_SIZE)                                    //0x0810 5000
#endif

#if BOARD_INDEX == 3
//CALIBRATION POINTS OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_POINTS_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 10 * FLASH_AREA_SIZE + FLASH_OFFSET)                                  //0x0810 5000
#endif

//CALIBRATION POINTS        
#define STRAIN_CALIBRATION_POINTS_FLASH_OFFSET                  CALIBRATION_POINTS_FLASH_OFFSET //start of BANK2
#define STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE                FLASH_AREA_SIZE
#define END_OF_STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE         (CALIBRATION_POINTS_FLASH_OFFSET + STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE)

#define POSITION_CALIBRATION_POINTS_FLASH_OFFSET                END_OF_STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE
#define POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE              FLASH_AREA_SIZE
#define END_OF_POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE       (END_OF_STRAIN_CALIBRATION_POINTS_FLASH_MAX_SIZE + POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_POINTS_FLASH_OFFSET             END_OF_POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE
#define DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE           FLASH_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE    (END_OF_POSITION_CALIBRATION_POINTS_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_OFFSET      END_OF_DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE
#define DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_MAX_SIZE    FLASH_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_POINTS_2_FLASH_MAX_SIZE  (END_OF_DEFORMATION_CALIBRATION_POINTS_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_2ND_CH_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_OFFSET      END_OF_DEFORMATION_CALIBRATION_POINTS_2_FLASH_MAX_SIZE
#define DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_MAX_SIZE    FLASH_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_POINTS_3_FLASH_MAX_SIZE  (END_OF_DEFORMATION_CALIBRATION_POINTS_2_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_3RD_CH_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_OFFSET      END_OF_DEFORMATION_CALIBRATION_POINTS_3_FLASH_MAX_SIZE
#define DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_MAX_SIZE    FLASH_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_POINTS_4_FLASH_MAX_SIZE  (END_OF_DEFORMATION_CALIBRATION_POINTS_3_FLASH_MAX_SIZE + DEFORMATION_CALIBRATION_POINTS_4TH_CH_FLASH_MAX_SIZE)

#define POSITION_SPEED_CALIBRATION_POINTS_FLASH_OFFSET                 END_OF_DEFORMATION_CALIBRATION_POINTS_4_FLASH_MAX_SIZE
#define POSITION_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE               FLASH_AREA_SIZE
#define END_OF_POSITION_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE        (END_OF_DEFORMATION_CALIBRATION_POINTS_4_FLASH_MAX_SIZE + POSITION_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE)

#define STRAIN_SPEED_CALIBRATION_POINTS_FLASH_OFFSET                 END_OF_POSITION_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE
#define STRAIN_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE               FLASH_AREA_SIZE
#define END_OF_STRAIN_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE        (END_OF_POSITION_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE + STRAIN_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE)

#define STRAIN_CALIBRATION_POINTS_2_FLASH_OFFSET                  END_OF_STRAIN_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE //start of BANK2
#define STRAIN_CALIBRATION_POINTS_2_FLASH_MAX_SIZE                FLASH_AREA_SIZE
#define END_OF_STRAIN_CALIBRATION_POINTS_2_FLASH_MAX_SIZE         (END_OF_STRAIN_SPEED_CALIBRATION_POINTS_FLASH_MAX_SIZE + STRAIN_CALIBRATION_POINTS_2_FLASH_MAX_SIZE)

#if BOARD_INDEX == 2
//CALIBRATION NOTES OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_NOTES_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 20 * FLASH_AREA_SIZE)                                    //0x0810 5000
#endif

#if BOARD_INDEX == 3
//CALIBRATION NOTES OFFSET                                     0x0800 0000           0x0010 0000            0x0000 0800
#define CALIBRATION_NOTES_FLASH_OFFSET                         (FLASH_START_ADDRESS + FLASH_BANK_SIZE + 20 * FLASH_AREA_SIZE + FLASH_OFFSET)                                  //0x0810 5000
#endif

#define STRAIN_CALIBRATION_NOTES_FLASH_OFFSET                   CALIBRATION_NOTES_FLASH_OFFSET
#define STRAIN_CALIBRATION_NOTES_FLASH_MAX_SIZE                 FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_STRAIN_CALIBRATION_NOTES_FLASH_OFFSET            (CALIBRATION_NOTES_FLASH_OFFSET + STRAIN_CALIBRATION_NOTES_FLASH_MAX_SIZE)

#define POSITION_CALIBRATION_NOTES_FLASH_OFFSET                 END_OF_STRAIN_CALIBRATION_NOTES_FLASH_OFFSET
#define POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE               FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_POSITION_CALIBRATION_NOTES_FLASH_OFFSET          (END_OF_STRAIN_CALIBRATION_NOTES_FLASH_OFFSET + POSITION_CALIBRATION_NOTES_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET              END_OF_POSITION_CALIBRATION_NOTES_FLASH_OFFSET
#define DEFORMATION_CALIBRATION_NOTES_FLASH_MAX_SIZE            FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET       (END_OF_POSITION_CALIBRATION_NOTES_FLASH_OFFSET + DEFORMATION_CALIBRATION_NOTES_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET          END_OF_DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET
#define DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_MAX_SIZE        FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET   (END_OF_DEFORMATION_CALIBRATION_NOTES_FLASH_OFFSET + DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET          END_OF_DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET
#define DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_MAX_SIZE        FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET   (END_OF_DEFORMATION_CALIBRATION_2CH_NOTES_FLASH_OFFSET + DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_MAX_SIZE)

#define DEFORMATION_CALIBRATION_4CH_NOTES_FLASH_OFFSET          END_OF_DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET
#define DEFORMATION_CALIBRATION_4CH_NOTES_FLASH_MAX_SIZE        FLASH_CALIBRATION_NOTE_AREA_SIZE
#define END_OF_DEFORMATION_CALIBRATION_4CH_NOTES_FLASH_OFFSET   (END_OF_DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET + DEFORMATION_CALIBRATION_4CH_NOTES_FLASH_MAX_SIZE)


// END OF FLASH 0x0810 78A0
#define END_OF_FLASH                                            END_OF_DEFORMATION_CALIBRATION_3CH_NOTES_FLASH_OFFSET                      

#endif