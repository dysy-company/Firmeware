#ifndef Shared_Params_h
#define Shared_Params_h
#include <mbed.h>
#include "Ethernet/Ethernet_Config.h"
#include "Enums/Commands.h"
#include "Ethernet/Ethernet_Errors.h"

//#define M_PI                                                                3.14159265358979323846264338327950288

#define REMOTE_CONTROLLER_VALUES_DATA_CHANNELS_SIZE                         1
#define VALUES_BUFFERS_SIZE                                                 4096//16300//8192//1024//256
#define ADC_TM_BUFFERS_SIZE                                        32
#define DIAGNOSTICS_BUFFERS_SIZE                                   4096 
#define VALVE_BUFFERS_SIZE                                         4096 

//machine types
#define MACHINE_TYPE_UNDEFINED                                              0x00000000
#define MACHINE_TYPE_UNIVERSAL_HYDRAULIC_MACHINE                            0x00000001
#define MACHINE_TYPE_ELECTRO_STATIC_MACHINE                                 0x00000002
#define MACHINE_TYPE_ELECTRO_HYDRAULIC_MACHINE                              0x00000003

#define CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED                           0x00000000
#define CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN                         0x00000001
#define CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN                          0x00000002

#define PROJECT_NAME_UNDEFINED                                              0x00000000
#define PROJECT_NAME_OLD_SVM_BOARD                                          0x00000001
#define PROJECT_NAME_MPD                                                    0x00000002

#define REMOTE_CONTROL_TYPE_UNDEFINED                                       0x00000000
#define REMOTE_CONTROL_TYPE_ENCODER                                         0x00000001
#define REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION                      0x00000002
#define REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION                         0x00000003
#define REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP                    0x00000004

#define LIMIT_SWITCH_DOORS_TYPE_UNDEFINED                                   0x00000000
#define LIMIT_SWITCH_DOORS_TYPE_TWO                                         0x00000001

#define EMERGENCY_STOP_TYPE_UNDEFINED                                       0x00000000
#define EMERGENCY_STOP_TYPE_BUTTON                                          0x00000001

#define BATTERY_UNDEFINED                                                   0x00000000
#define BATTERY_AVAILABLE                                                   0x00000001
  
#define ADC_STRAIN_TYPE_ADS8320                                             0x00000001
#define ADC_STRAIN_TYPE_ADS869x                                             0x00000002

#define MACHINE_TYPE_RESERVED                                               0x000000FF

#define SENSOR_TYPE_UNDEFINED                                               0x00
#define SENSOR_TYPE_DIGITAL_RSSI                                            0x01
#define SENSOR_TYPE_RUN_STOP                                                0x02
#define SENSOR_TYPE_DIGITAL                                                 0x03
#define SENSOR_TYPE_ANALOG_LVDT                                             0x04
#define SENSOR_TYPE_ANALOG                                                  0x05
#define SENSOR_TYPE_ENCODER                                                 0x06
#define SENSOR_TYPE_ANALOG_0_10V                                            0x07
#define SENSOR_TYPE_ANALOG_LVDT2                                            0x08

//pin types
#define PIN_TYPE_UNDEFINED                                                  0x00000000

#define PIN_TYPE_HW_CMD_0                                                   0x00000001
#define PIN_TYPE_HW_CMD_1                                                   0x00000002
#define PIN_TYPE_HW_CMD_2                                                   0x00000003
#define PIN_TYPE_HW_CMD_3                                                   0x00000004
#define PIN_TYPE_HW_CMD_4                                                   0x00000005
#define PIN_TYPE_HW_CMD_5                                                   0x00000006
#define PIN_TYPE_HW_CMD_6                                                   0x00000007
#define PIN_TYPE_HW_CMD_7_UP                                                0x00000008
#define PIN_TYPE_HW_CMD_7_DOWN                                              0x00000009
#define PIN_TYPE_HW_CMD_8_UP                                                0x0000000A
#define PIN_TYPE_HW_CMD_8_DOWN                                              0x0000000B
#define PIN_TYPE_COIL_POWER                                                 0x0000000C
#define PIN_TYPE_DISP_SEN_POWER                                             0x0000000D
#define PIN_TYPE_STRAIN_AMP                                                 0x0000000E
#define PIN_TYPE_STRAIN_SEN_SWITCH                                          0x0000000F
#define PIN_TYPE_DISP_SEN_START_PULSE                                       0x00000010
#define PIN_TYPE_DISP_SEN_STOP_PULSE                                        0x00000011
#define PIN_TYPE_VALVE_DIRECT_HIGH                                          0x00000012
#define PIN_TYPE_VALVE_REVERSE_HIGH                                         0x00000013
#define PIN_TYPE_VALVE_DIRECT_LOW                                           0x00000012
#define PIN_TYPE_VALVE_REVERSE_LOW                                          0x00000013
#define PIN_TYPE_DEBUG_PIN                                                  0x00000014
#define PIN_TYPE_ENCODER_MOVE_ENABLE                                        0x00000015

#define PIN_TYPE_HW_CMD_FEEDBACK_0                                          0x01000001
#define PIN_TYPE_HW_CMD_FEEDBACK_1                                          0x01000002
#define PIN_TYPE_HW_CMD_FEEDBACK_2                                          0x01000003
#define PIN_TYPE_HW_CMD_FEEDBACK_3                                          0x01000004
#define PIN_TYPE_HW_CMD_FEEDBACK_4                                          0x01000005
#define PIN_TYPE_HW_CMD_FEEDBACK_5                                          0x01000006
#define PIN_TYPE_HW_CMD_FEEDBACK_6                                          0x01000007
#define PIN_TYPE_HW_CMD_FEEDBACK_7                                          0x01000008
#define PIN_TYPE_HW_CMD_FEEDBACK_8                                          0x0100000A
#define PIN_TYPE_ENCODER_MOVE_UP                                            0x01000015
#define PIN_TYPE_ENCODER_MOVE_DOWN                                          0x01000016



// Specify DAC states
#define DAC_STATE_NONE                                                      0
#define DAC_STATE_CONST_LEVEL                                               1
#define DAC_STATE_SIN                                                       2//not used
#define DAC_STATE_COS                                                       3//not used
#define DAC_STATE_DISP_PULSE                                                4
#define DAC_STATE_CALIBRATION                                               5//not used
#define DAC_STATE_DISP_SIN                                                  6
#define DAC_STATE_DISP_CONST                                                7
#define DAC_STATE_STRAIN_SIN                                                8
#define DAC_STATE_STRAIN_CONST                                              9
#define DAC_STATE_STRAIN_PULSE                                              10
#define DAC_STATE_DISP_USER_DEFINED                                         11
#define DAC_STATE_STRAIN_USER_DEFINED                                       12
#define DAC_STATE_DISP_SINUS_BASED                                          13
#define DAC_STATE_STRAIN_SINUS_BASED                                        14
#define DAC_STATE_DEFORMATION_SIN                                           15
#define DAC_STATE_DEFORMATION_CONST                                         16
#define DAC_STATE_DEFORMATION_PULSE                                         17
#define DAC_STATE_DEFORMATION_USER_DEFINED                                  18
#define DAC_STATE_DEFORMATION_SINUS_BASED                                   19
#define DAC_STATE_CLOSE_VALVE                                               20

#define DAC_STATE_EXPERIMENTAL                                              32
#define DAC_STATE_UNDEFINED                                                 255

#define SINUS_BASED_UNDEFINED                                               0
#define SINUS_BASED_SQUARE                                                  1
#define SINUS_BASED_TRIANGLE                                                2
#define SINUS_BASED_TRAPEZE                                                 3

// Specify different pins to printing on UART other than the console UART.
#define TARGET_TX_PIN                                                     USBTX
#define TARGET_RX_PIN                                                     USBRX

// Specify defaults values for any params
#define DEFAULT_DAC_THREAD_VOLTAGE                                          0
#define DEFAULT_DAC_THREAD_FREQUENCY                                        0.100
#define DEFAULT_DAC_THREAD_STATE                                            DAC_STATE_NONE
#define DEFAULT_DAC_THREAD_EXPERIMENTAL_TIME_LENGTH                         0
#define DEFAULT_DAC_THREAD_EXPERIMENTAL_TIME_DELAY                          0
#define DEFAULT_ETHERNET_THREAD_STATE                                       ETHERNET_STATE_WAIT_CONNECTION

#define INTERNAL_TASK_NONE                                                      0x00000000
#define INTERNAL_TASK_SAMPLE_HARDNESS_CALCULATION                               0x00000001
#define INTERNAL_TASK_STATIC_TEST                                               0x00000002
#define INTERNAL_TASK_SBD                                                       0x00000003

#define INTERNAL_TASK_SBD_NONE                                                  0x00000000
#define INTERNAL_TASK_SBD_INIT                                                  0x00000001
#define INTERNAL_TASK_SBD_PROCESS                                               0x00000002
#define INTERNAL_TASK_SBD_EXIT                                                  0x00000003

#define INTERNAL_TASK_STATE_NONE                                                0x00000000
#define INTERNAL_TASK_STATE_INIT                                                0x00000001
#define INTERNAL_TASK_STATE_STEP_1                                              0x00000002
#define INTERNAL_TASK_STATE_STEP_2                                              0x00000003
#define INTERNAL_TASK_STATE_STEP_3                                              0x00000004
#define INTERNAL_TASK_STATE_STEP_4                                              0x00000005
#define INTERNAL_TASK_STATE_STEP_5                                              0x00000006
#define INTERNAL_TASK_STATE_STEP_6                                              0x00000007
#define INTERNAL_TASK_STATE_STEP_7                                              0x00000008
#define INTERNAL_TASK_STATE_STEP_8                                              0x00000009
#define INTERNAL_TASK_STATE_STEP_9                                              0x0000000A
#define INTERNAL_TASK_STATE_STEP_10                                             0x0000000B
#define INTERNAL_TASK_STATE_STEP_11                                             0x0000000C
#define INTERNAL_TASK_STATE_STEP_12                                             0x0000000D
#define INTERNAL_TASK_STATE_STEP_13                                             0x0000000E
#define INTERNAL_TASK_STATE_STEP_14                                             0x0000000F
#define INTERNAL_TASK_STATE_STEP_15                                             0x00000010
#define INTERNAL_TASK_STATE_STEP_16                                             0x00000011
#define INTERNAL_TASK_STATE_STEP_17                                             0x00000012
#define INTERNAL_TASK_STATE_STEP_18                                             0x00000013
#define INTERNAL_TASK_STATE_STEP_19                                             0x00000014
#define INTERNAL_TASK_STATE_STEP_20                                             0x00000015
#define INTERNAL_TASK_STATE_STEP_21                                             0x00000016
#define INTERNAL_TASK_STATE_STEP_22                                             0x00000017
#define INTERNAL_TASK_STATE_STEP_23                                             0x00000018
#define INTERNAL_TASK_STATE_STEP_24                                             0x00000019
#define INTERNAL_TASK_STATE_STEP_25                                             0x0000001A
#define INTERNAL_TASK_STATE_STEP_26                                             0x0000001B
#define INTERNAL_TASK_STATE_STEP_27                                             0x0000001C
#define INTERNAL_TASK_STATE_STEP_28                                             0x0000001D
#define INTERNAL_TASK_STATE_STEP_29                                             0x0000001E
#define INTERNAL_TASK_STATE_STEP_30                                             0x0000001F
#define INTERNAL_TASK_STATE_STEP_31                                             0x00000020
#define INTERNAL_TASK_STATE_STEP_32                                             0x00000021

#define INTERNAL_TASK_STATE_STOP_TASK                                           0x1FFFFFFF
#define INTERNAL_TASK_STATE_PAUSE_TASK                                          0x2FFFFFFF

#define STATIC_TEST_PANEL_TYPE_ACTION                                           0x00
#define STATIC_TEST_PANEL_TYPE_CONDITION                                        0x01
//
#define STATIC_TEST_ISP_TYPE_TEST                                               0x00
#define STATIC_TEST_ISP_TYPE_EXPOSURE                                           0x01
#define STATIC_TEST_ISP_TYPE_STOP_UNTIL_CONFIRM                                 0x02
//
#define STATIC_TEST_BOOLPARAM_DISPL_VELOCITY                                    0x00
#define STATIC_TEST_BOOLPARAM_STRAIN_VELOCITY                                   0x01
#define STATIC_TEST_BOOLPARAM_DEFORMATION                                       0x02
#define STATIC_TEST_BOOLPARAM_CHANGE_DIRECTION                                  0x03
///
#define STATIC_TEST_BOOLPARAM_STRAIN_HOLD                                       0x00
#define STATIC_TEST_BOOLPARAM_DISPL_HOLD                                        0x01
//
#define STATIC_TEST_BOOLPARAM_MOVE_TO                                           0x00
#define STATIC_TEST_BOOLPARAM_LOAD_ON                                           0x01
#define STATIC_TEST_BOOLPARAM_DEFORM_TO                                         0x02
#define STATIC_TEST_BOOLPARAM_ANGLE_TO                                          0x03

#define TEST_SIGNAL_NONE                                                        0x00000000
#define TEST_SIGNAL_SIN_GENERATION                                              0x00000001
#define TEST_SIGNAL_CONST_VALUES                                                0x00000002
#define TEST_SIGNAL_CONST_VALUES_RANDOM                                         0x00000003

#define AMPLITUDE_TUNE_STATE_DISABLE                                            0x00000000
#define AMPLITUDE_TUNE_STATE_ENABLE                                             0x00000001
#define AMPLITUDE_TUNE_STATE_INIT                                               0x00000002
#define AMPLITUDE_TUNE_STATE_CORRECTION                                         0x00000003
#define AMPLITUDE_TUNE_STATE_EXIT                                               0x1FFFFFFF

#define CORRECTION_TYPE_DISPLACEMENT                                        0x00000000
#define CORRECTION_TYPE_STRAIN                                              0x00000001
#define CORRECTION_TYPE_DEFORMATION                                         0x00000002

#define ACQ_DISPLACEMENT                                                     0x00000001
#define ACQ_STRAIN                                                           0x00000002
#define ACQ_PID_ZERO                                                         0x00000004
#define ACQ_PID_SIN                                                          0x00000008
#define ACQ_SENSORS_TM                                                       0x00000010
#define ACQ_DEFORMATION                                                      0x00000020
#define ACQ_UNDEFINED                                                        0x80000000

#define WAIT_ACQ_COMPLETE_DISPLACEMENT                                       0x00000001
#define WAIT_ACQ_COMPLETE_STRAIN                                             0x00000002
#define WAIT_ACQ_COMPLETE_DEFORMATION                                        0x00000004
#define WAIT_ACQ_COMPLETE_UNDEFINED                                          0x80000000

#define HW_CMD_0                                                             0x00000000
#define HW_CMD_1                                                             0x00000001                                                         
#define HW_CMD_2                                                             0x00000002
#define HW_CMD_3                                                             0x00000003
#define HW_CMD_4                                                             0x00000004
#define HW_CMD_5                                                             0x00000005
#define HW_CMD_6                                                             0x00000006
#define HW_CMD_UNDEFINED                                                     0xFFFFFFFF

//not used
#define HW_CMD_PUMP_STATE                                                   HW_CMD_4
#define HW_CMD_HIGH_PRESSURE_STATE                                          HW_CMD_6

#define RSSI_INACCURACY                                                     0.001

#define POSITION_INCREASE_PISTON_PUSH                                               1
#define POSITION_INCREASE_PISTON_PULL                                               -1
#define STRAIN_INCREASE_PISTON_PUSH                                                 1
#define STRAIN_INCREASE_PISTON_PULL                                                 -1
#define DEFORMATION_INCREASE_PISTON_PUSH                                            1
#define DEFORMATION_INCREASE_PISTON_PULL                                            -1

#define PISTON_UP_PISTON_PULL                                                       1
#define PISTON_UP_PISTON_PUSH                                                       -1

#define POSITION_NOT_INVERTED_AXIS                                                  1
#define POSITION_INVERTED_AXIS                                                      -1
#define STRAIN_NOT_INVERTED_AXIS                                                    1
#define STRAIN_INVERTED_AXIS                                                        -1
#define DEFORMATION_NOT_INVERTED_AXIS                                               1
#define DEFORMATION_INVERTED_AXIS                                                   -1

#define VALVE_NOT_INVERTED_DIRECTION                                                1
#define VALVE_INVERTED_DIRECTION                                                    -1

#if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN ))
#define DEFAULT_DISPLACEMENT_SUM_SIZE                                               100
#define DEFAULT_STRAIN_SUM_SIZE                                                     100
#define DEFAULT_DEFORMATION_SUM_SIZE                                                100
#define DEFAULT_STRAIN_ADC_NULL_OFFSET_SUM_SIZE                                     100
#define DEFAULT_DEFORMATION_ADC_NULL_OFFSET_SUM_SIZE                                100
#define DEFAULT_DISPLACEMENT_NULL_OFFSET_SUM_SIZE                                   100
#else
#define DEFAULT_DISPLACEMENT_SUM_SIZE                                               10
#define DEFAULT_STRAIN_SUM_SIZE                                                     10
#define DEFAULT_DEFORMATION_SUM_SIZE                                                10
#define DEFAULT_STRAIN_ADC_NULL_OFFSET_SUM_SIZE                                     10
#define DEFAULT_DEFORMATION_ADC_NULL_OFFSET_SUM_SIZE                                10
#define DEFAULT_DISPLACEMENT_NULL_OFFSET_SUM_SIZE                                   10
#endif

#define DEFAULT_DISPLACEMENT_PROTECT_UPPER_LIMIT                                    174.0
#define DEFAULT_DISPLACEMENT_PROTECT_LOWER_LIMIT                                    63.0
#define DEFAULT_DISPLACEMENT_PROTECT_COUNT                                          24

#define DEFAULT_DISPLACEMENT_EDGE_PROTECT_UPPER_LIMIT                               175.0
#define DEFAULT_DISPLACEMENT_EDGE_PROTECT_LOWER_LIMIT                               62.0
#define DEFAULT_DISPLACEMENT_EDGE_PROTECT_COUNT                                     10

#define DEFAULT_STRAIN_PROTECT_UPPER_LIMIT                                          100.0
#define DEFAULT_STRAIN_PROTECT_LOWER_LIMIT                                          -100.0
#define DEFAULT_STRAIN_PROTECT_COUNT                                                24

#define DEFAULT_STRAIN_EDGE_PROTECT_UPPER_LIMIT                                     102.0
#define DEFAULT_STRAIN_EDGE_PROTECT_LOWER_LIMIT                                     -102.0
#define DEFAULT_STRAIN_EDGE_PROTECT_COUNT                                           10

#define DEFAULT_DEFORMATION_PROTECT_UPPER_LIMIT                                     100.0
#define DEFAULT_DEFORMATION_PROTECT_LOWER_LIMIT                                     -100.0
#define DEFAULT_DEFORMATION_PROTECT_COUNT                                           24

#define DEFAULT_DEFORMATION_EDGE_PROTECT_UPPER_LIMIT                                102.0
#define DEFAULT_DEFORMATION_EDGE_PROTECT_LOWER_LIMIT                                -102.0
#define DEFAULT_DEFORMATION_EDGE_PROTECT_COUNT                                      10


#define WORK_MODE_SETTING_SAMPLE                                            0
#define WORK_MODE_READY_FOR_TESTING                                         1
#define WORK_MODE_TEST_IN_PROCESS                                           2
#define DEFAULT_WORK_MODE                                                   WORK_MODE_READY_FOR_TESTING

#define DEFAULT_ENCODER_BUFFER_SIZE                                                 125

#define DEFAULT_MAIL_SIZE                                                           16

#define DEFAULT_WATCHDOG_TIMEOUT                                                    10000

#define SENSOR_TEDS_NOT_FOUND                                                       0x00
#define SENSOR_TEDS_WAS_READ                                                        0x01
#define SENSOR_TEDS_UNDEFINED                                                       0xFF

#define CONTROLLER_MODE_CONTINUE_IF_NOT_CONNECTED                                   0
#define CONTROLLER_MODE_STOP_IF_NOT_CONNECTED                                       1

#define LIMIT_SWITCH_TYPE_UNDEFINED                                                 0x00
#define LIMIT_SWITCH_TYPE_ONE                                                       0x01
#define LIMIT_SWITCH_TYPE_TWO                                                       0x02

#define LIMIT_SWITCH_STATE_UNDEFINED                                                0x00
#define LIMIT_SWITCH_STATE_ONE                                                      0x01
#define LIMIT_SWITCH_STATE_TWO                                                      0x02

#define LIMIT_SWITCH_POWER_UNDEFINED                                                0x00
#define LIMIT_SWITCH_POWER_5V                                                       0x01
#define LIMIT_SWITCH_POWER_24V                                                      0x02

#define DEFORMATION_UNDEFINED_CHANNEL                                               0x00
#define DEFORMATION_1ST_CHANNEL                                                     0x01
#define DEFORMATION_2ND_CHANNEL                                                     0x02
#define DEFORMATION_3RD_CHANNEL                                                     0x03
#define DEFORMATION_4TH_CHANNEL                                                     0x04

#define DEFORMATION_1ST_CHANNEL_MASK                                                (uint8_t)0b11110001
#define DEFORMATION_2ND_CHANNEL_MASK                                                (uint8_t)0b11110010
#define DEFORMATION_3RD_CHANNEL_MASK                                                (uint8_t)0b11110100
#define DEFORMATION_4TH_CHANNEL_MASK                                                (uint8_t)0b11111000

#define FLASH_OPERATION_CPU                                                         0x00
#define FLASH_OPERATION_DMA                                                         0x01

#define STRAIN_CHANNEL_1ST                                                          0x00
#define STRAIN_CHANNEL_2ND                                                          0x01

#define TEST_PROCESS_PAUSE                                                          0x00
#define TEST_PROCESS_CONTINUE                                                       0x01
#define TEST_PROCESS_UNDEFINED                                                      0xFF

#define MAX_SIZE_OF_BUFFER                                                          99

#endif