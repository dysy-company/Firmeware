#ifndef GLOBAL_VARIABLES_DEFINES_H
#define GLOBAL_VARIABLES_DEFINES_H

#include <mbed.h>
//TODO: CHECK FOR DUPLICATE VALUES
#define GLOBAL_VARIABLES                                                                0x00000000

#define GLOBAL_VARIABLES_POSITION_AXIS_MODE                                             0x00000001
#define GLOBAL_VARIABLES_STRAIN_AXIS_MODE                                               0x00000002
#define GLOBAL_VARIABLES_DEFORMATION_AXIS_MODE                                          0x00000003

#define GLOBAL_VARIABLES_POSITION_INVERT_AXIS                                           0x00000004
#define GLOBAL_VARIABLES_STRAIN_INVERT_AXIS                                             0x00000005
#define GLOBAL_VARIABLES_DEFORMATION_INVERT_AXIS                                        0x00000006

#define GLOBAL_VARIABLES_PISTON_MODE                                                    0x00000007

#define GLOBAL_VARIABLES_VALVE_DIRECTION_MODE                                           0x00000008
//PISTON PARAMS STRUCT
#define GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA                                         0x00000009
#define GLOBAL_VARIABLES_PISTON_PARAMS_BOTTOM_AREA                                      0x0000000A
//VALVE PARAMS STRUCT
#define GLOBAL_VARIABLES_VALVE_PARAMS_IMAX                                              0x0000000B
#define GLOBAL_VARIABLES_VALVE_PARAMS_QVALVE                                            0x0000000C

#define GLOBAL_VARIABLES_STATIC_TEST_POSITION_UPPER_THRESHOLD                           0x0000000D
#define GLOBAL_VARIABLES_STATIC_TEST_POSITION_LOWER_THRESHOLD                           0x0000000E
#define GLOBAL_VARIABLES_STATIC_TEST_STRAIN_UPPER_THRESHOLD                             0x0000000F
#define GLOBAL_VARIABLES_STATIC_TEST_STRAIN_LOWER_THRESHOLD                             0x00000010
#define GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_UPPER_THRESHOLD                        0x00000011
#define GLOBAL_VARIABLES_STATIC_TEST_DEFORMATION_LOWER_THRESHOLD                        0x00000012

#define GLOBAL_VARIABLES_ENCODER_STEP_VALUE                                             0x00000013
#define GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE                                               0x00000014
#define GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE                                          0x00000015
#define GLOBAL_VARIABLES_MOTOR_STEP_VALUE                                               0x00000016
#define GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1                                         0x00000017
#define GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_2                                         0x00000018
#define GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY                                         0x00000019

#define GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE                                 0x0000001E

#define GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK                                 0x0000001F
#define GLOBAL_VARIABLES_DISPLACEMENT_UNDERRUN_STEP_BACK                                0x00000020
#define GLOBAL_VARIABLES_STRAIN_OVERRUN_STEP_BACK                                       0x00000021
#define GLOBAL_VARIABLES_STRAIN_UNDERRUN_STEP_BACK                                      0x00000022
#define GLOBAL_VARIABLES_DEFORMATION_OVERRUN_STEP_BACK                                  0x00000023
#define GLOBAL_VARIABLES_DEFORMATION_UNDERRUN_STEP_BACK                                 0x00000024

#define GLOBAL_VARIABLES_SSI_NULL_OFFSET                                                0x00000025

#define GLOBAL_VARIABLES_PWM_FREQ                                                       0x00000026

#define GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL                                            0x00000027
#define GLOBAL_VARIABLES_CLR_ACTIVE_LEVEL                                               0x00000028
#define GLOBAL_VARIABLES_CWL_ACTIVE_LEVEL                                               0x00000029
#define GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL                                              0x0000002A

//SERIAL NUMBER & ID
#define GLOBAL_VARIABLES_SERIAL_NUMBER                                                  0x00001000
#define GLOBAL_VARIABLES_ID                                                             0x00001001
#define GLOBAL_VARIABLES_MACHINE_TYPE                                                   0x00001002
#define GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION                                      0x00001003

#define GLOBAL_VARIABLES_IP_ADDRESS                                                     0x00001004
#define GLOBAL_VARIABLES_NET_MASK                                                       0x00001005
#define GLOBAL_VARIABLES_GATEWAY                                                        0x00001006
#define GLOBAL_VARIABLES_PORT                                                           0x00001007

#define GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST                 0x00001008

#define GLOBAL_VARIABLES_MAX_STRAIN                                                     0x00001100
#define GLOBAL_VARIABLES_MIN_STRAIN                                                     0x00001101
#define GLOBAL_VARIABLES_MAX_STRAIN_OVERLOAD_PERCENT                                    0x00001102
#define GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT                                    0x00001103
#define GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE                                             0x00001104

#define GLOBAL_VARIABLES_MAX_DISPLACEMENT                                               0x00001110
#define GLOBAL_VARIABLES_MIN_DISPLACEMENT                                               0x00001111
#define GLOBAL_VARIABLES_MAX_DISPLACEMENT_OVERLOAD_PERCENT                              0x00001112
#define GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT                              0x00001113
#define GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE                                       0x00001114

#define GLOBAL_VARIABLES_MAX_DEFORMATION                                                0x00001120
#define GLOBAL_VARIABLES_MIN_DEFORMATION                                                0x00001121
#define GLOBAL_VARIABLES_MAX_DEFORMATION_OVERLOAD_PERCENT                               0x00001122
#define GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT                               0x00001123
#define GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE                                        0x00001124

#define GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE                                       0x00001125
#define GLOBAL_VARIABLES_DISPLACEMENT_REFERENCE_VOLTAGE                                 0x00001126
#define GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE                                  0x00001127

#define GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1                                    0x00001128
#define GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH2                                    0x00001129
#define GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH3                                    0x0000112A
#define GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH4                                    0x0000112B
#define GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS                                    0x0000112C

//PID COEFS ID
#define GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP                                        0x00003000
#define GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KI                                        0x00003001
#define GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KD                                        0x00003002
#define GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KP                                         0x00003003
#define GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KI                                         0x00003004
#define GLOBAL_VARIABLES_SIN_DEFORMATION_PID_KD                                         0x00003005
#define GLOBAL_VARIABLES_SIN_STRAIN_PID_KP                                              0x00003006
#define GLOBAL_VARIABLES_SIN_STRAIN_PID_KI                                              0x00003007
#define GLOBAL_VARIABLES_SIN_STRAIN_PID_KD                                              0x00003008
#define GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KP                                0x00003009
#define GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KI                                0x0000300A
#define GLOBAL_VARIABLES_SINUS_BASED_DISPLACEMENT_PID_KD                                0x0000300B
#define GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KP                                 0x0000300C
#define GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KI                                 0x0000300D
#define GLOBAL_VARIABLES_SINUS_BASED_DEFORMATION_PID_KD                                 0x0000300E
#define GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KP                                      0x0000300F
#define GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KI                                      0x00003010
#define GLOBAL_VARIABLES_SINUS_BASED_STRAIN_PID_KD                                      0x00003011
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KP                                      0x00003012
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KI                                      0x00003013
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_PID_KD                                      0x00003014
#define GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KP                                       0x00003015
#define GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KI                                       0x00003016
#define GLOBAL_VARIABLES_CONST_DEFORMATION_PID_KD                                       0x00003017
#define GLOBAL_VARIABLES_CONST_STRAIN_PID_KP                                            0x00003018
#define GLOBAL_VARIABLES_CONST_STRAIN_PID_KI                                            0x00003019
#define GLOBAL_VARIABLES_CONST_STRAIN_PID_KD                                            0x0000301A

//Max Voltages

#define GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT                                 0x00004000
#define GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_VOLT                                  0x00004001
#define GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_VOLT                                       0x00004002
#define GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_VOLT                                0x00004003
#define GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_VOLT                               0x00004004
#define GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_VOLT                               0x00004005
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_VOLT                               0x00004006
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_VOLT                                0x00004007
#define GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_VOLT                                     0x00004008
#define GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT                                      0x00004009

//Const displacement mode params saving to flash
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV                                0x0000400A
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MODE_FREQ                              0x0000400B
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_SPEED                                  0x0000400C
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_SPEED                              0x0000400D
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA                                  0x0000400E

//Max Steps and delta
#define GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA                                        0x0000400F
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA                                   0x00004010
#define GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP                                 0x00004011
#define GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_MAX_STEP                                  0x00004012
#define GLOBAL_VARIABLES_SIN_STRAIN_MODE_MAX_STEP                                       0x00004013
#define GLOBAL_VARIABLES_SINUS_BASED_DISPL_MODE_MAX_STEP                                0x00004014
#define GLOBAL_VARIABLES_SINUS_BASED_DEFORM_MODE_MAX_STEP                               0x00004015
#define GLOBAL_VARIABLES_SINUS_BASED_STRAIN_MODE_MAX_STEP                               0x00004016
#define GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_STEP                               0x00004017
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_MAX_STEP                                0x00004018
#define GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP                                     0x00004019

//Const mode params
#define GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ                                           0x0000401A

//Const strain mode params
#define GLOBAL_VARIABLES_CONST_STRAIN_MAX_DEV                                           0x0000401B
#define GLOBAL_VARIABLES_CONST_STRAIN_MODE_FREQ                                         0x0000401C
#define GLOBAL_VARIABLES_CONST_STRAIN_SPEED                                             0x0000401D
#define GLOBAL_VARIABLES_CONST_STRAIN_MAX_SPEED                                         0x0000401E
#define GLOBAL_VARIABLES_CONST_STRAIN_DELTA                                             0x0000401F

//Const deformation mode params     
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_DEV                                      0x00004020
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_FREQ                                    0x00004021
#define GLOBAL_VARIABLES_CONST_DEFORMATION_SPEED                                        0x00004022
#define GLOBAL_VARIABLES_CONST_DEFORMATION_MAX_SPEED                                    0x00004023
#define GLOBAL_VARIABLES_CONST_DEFORMATION_DELTA                                        0x00004024

//Sinus displacement mode params        
#define GLOBAL_VARIABLES_SIN_DISPLASEMENT_MAX_DEV                                       0x00004025
#define GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_FREQ                                     0x00004026
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KP                                       0x00004027
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KP                                     0x00004028
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KI                                       0x00004029
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KI                                     0x0000402A
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_UP_KD                                       0x0000402B
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_DOWN_KD                                     0x0000402C

//Sinus strain mode params
#define GLOBAL_VARIABLES_SIN_STRAIN_MAX_DEV                                             0x0000402D
#define GLOBAL_VARIABLES_SIN_STRAIN_MODE_FREQ                                           0x0000402E
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KP                                     0x0000402F
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KP                                   0x00004030
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KI                                     0x00004031
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KI                                   0x00004032
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_UP_KD                                     0x00004033
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_DOWN_KD                                   0x00004034

//Sinus deformation mode params
#define GLOBAL_VARIABLES_SIN_DEFORMATION_MAX_DEV                                        0x00004035
#define GLOBAL_VARIABLES_SIN_DEFORMATION_MODE_FREQ                                      0x00004036
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KP                                     0x00004037
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KP                                   0x00004038
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KI                                     0x00004039
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KI                                   0x0000403A
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_UP_KD                                     0x0000403B
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_DOWN_KD                                   0x0000403C

//Sinus based displacement mode params
#define GLOBAL_VARIABLES_SIN_BASED_DISP_MAX_DEV                                         0x0000403D
#define GLOBAL_VARIABLES_SIN_BASED_DISP_MODE_FREQ                                       0x0000403E
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KP                                 0x0000403F
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KP                               0x00004040
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KI                                 0x00004041
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KI                               0x00004042
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_UP_KD                                 0x00004043
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_DOWN_KD                               0x00004044

//Sinus based strain mode params
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_MAX_DEV                                       0x00004045
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_MODE_FREQ                                     0x00004046
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KP                               0x00004047
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KP                             0x00004048
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KI                               0x00004049
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KI                             0x0000404A
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_UP_KD                               0x0000404B
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_DOWN_KD                             0x0000404C

//Sinus based deformation mode params
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_MAX_DEV                                       0x0000404D
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_MODE_FREQ                                     0x0000404E
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KP                               0x0000404F
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KP                             0x00004050
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KI                               0x00004051
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KI                             0x00004052
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_UP_KD                               0x00004053
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD                             0x00004054

//Amplitude tune coefs
#define GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC                           0x0000407E
#define GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP                                0x0000407F
#define GLOBAL_VARIABLES_MIN_DELTA_RATIO_FOR_NULLPOINT                                  0x00004080
#define GLOBAL_VARIABLES_MIN_AMPL_FOR_DISPL_NULLPOINT                                   0x00004081
#define GLOBAL_VARIABLES_MIN_AMPL_FOR_DEFORM_NULLPOINT                                  0x00004082
#define GLOBAL_VARIABLES_MIN_AMPL_FOR_STRAIN_NULLPOINT                                  0x00004083
#define GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO                                     0x00004084   
#define GLOBAL_VARIABLES_AMPLITUDE_PRECISION                                            0x00004085
#define GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT                            0x00004086
#define GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION                              0x00004087
#define GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS                                     0x00004088
#define GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START                                     0x00004089
#define GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_STOP                                      0x0000408A

//Middle piston position
#define GLOBAL_VARIABLES_MIDDLE_PISTON_POSITION                                         0x0000408B

//Null point PIDs

#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KP                           0x0000408C
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KI                           0x0000408D
#define GLOBAL_VARIABLES_SIN_DISP_AMPL_TUNE_NULL_POINT_PID_KD                           0x0000408E
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP                         0x0000408F
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI                         0x00004090
#define GLOBAL_VARIABLES_SIN_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD                         0x00004091
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP                         0x00004092
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI                         0x00004093
#define GLOBAL_VARIABLES_SIN_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD                         0x00004094
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KP                     0x00004095
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KI                     0x00004096
#define GLOBAL_VARIABLES_SIN_BASED_DISP_AMPL_TUNE_NULL_POINT_PID_KD                     0x00004097
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KP                   0x00004098
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KI                   0x00004099
#define GLOBAL_VARIABLES_SIN_BASED_STRAIN_AMPL_TUNE_NULL_POINT_PID_KD                   0x0000409A
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KP                   0x0000409B
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KI                   0x0000409C
#define GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_NULL_POINT_PID_KD                   0x0000409D

//Cyclic strain protection
#define GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT                                  0x0000409E
#define GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT                          0x0000409F
#define GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_FIRST                            0x000040A0
#define GLOBAL_VARIABLES_BLINDE_PART_CYCL_STRAIN_PRPOT_DEFAULT_FIRST                    0x000040A1
#define GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION                                        0x000040A2
#define GLOBAL_VARIABLES_DELTA_CYCLIC_PROTECTION_DEFAULT                                0x000040A3
#define GLOBAL_VARIABLES_MULTIPLIER                                                     0x000040A4
#define GLOBAL_VARIABLES_MULTIPLIER_DEFAULT                                             0x000040A5

//TCycle time
#define GLOBAL_VARIABLES_T_CYCLE_TIME                                                   0x00004100
//SSI sensor resolution                                                   
#define GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION                                          0x00004101
//strain button limits
#define GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT                                      0x00004102
#define GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT                                      0x00004103
//speed by button
#define GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR                                  0x00004104
#define GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST                                     0x00004105
//Tcycle for flash writing
#define GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING                                       0x00004106
//cyclic delta for protection
#define GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA                                            0x00004107
#define GLOBAL_VARIABLES_DISPLACEMENT_CYCLIC_DELTA                                      0x00004108
#define GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA                                       0x00004109
//calibration points notes
#define GLOBAL_VARIABLES_STRAIN_CALIBRATION_NOTES                                       0x0000410A
#define GLOBAL_VARIABLES_DISPLACEMENT_CALIBRATION_NOTES                                 0x0000410B
#define GLOBAL_VARIABLES_DEFORMATION_CALIBRATION_NOTES                                  0x0000410C
#define GLOBAL_VARIABLES_DEFORMATION_2CH_CALIBRATION_NOTES                              0x0000410D
#define GLOBAL_VARIABLES_DEFORMATION_3CH_CALIBRATION_NOTES                              0x0000410E

//Deformation units
#define GLOBAL_VARIABLES_DEFORMATION_UNITS                                              0x0000410F

//Digital valve params
#define GLOBAL_VARIABLES_MAX_POSITION                                                   0x00005000
#define GLOBAL_VARIABLES_MIDDLE_POSITION                                                0x00005001
#define GLOBAL_VARIABLES_MIDDLE_UP_THRESHOLD                                            0x00005002
#define GLOBAL_VARIABLES_MIDDLE_DOWN_THRESHOLD                                          0x00005003
#define GLOBAL_VARIABLES_POSITION_DIVIDER                                               0x00005004
#define GLOBAL_VARIABLES_VALVE_INVERT_AXIS                                              0x00005005

#endif