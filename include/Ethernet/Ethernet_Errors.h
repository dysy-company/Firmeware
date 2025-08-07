#ifndef ETHERNET_ERRORS_H
#define ETHERNET_ERRORS_H

//TEST EXECUTION 
enum class TestExecutionCompleteStatus : uint32_t{
    OK                                                                           = 0x00000000,
    SAMPLE_BREAKED_MAX_STRAIN                                                    = 0x00000001,
    SAMPLE_BREAKED_DF                                                            = 0x00000002,
    EMERGENCY_STOP                                                               = 0x00000003,
    LIMIT_SWITCH                                                                 = 0x00000004,
    STOP_BY_REMOTE_CONTROL                                                       = 0x00000005,
    LIMIT_SWITCH_LEFT_DOOR                                                       = 0x00000006,
    LIMIT_SWITCH_RIGHT_DOOR                                                      = 0x00000007
};


//ERRORS DEFINES
#define NO_ERROR                                                                                                    0x00000000
#define ETHERNET_ERROR_UNEXPECTED_DATA_LENGTH                                                                       0x00000001

#define ERROR_DURING_SET_TCYCLE                                                                                     0x00001000

#define ERROR_WRONG_INPUT_DATA                                                                                      0x00001001
#define ERROR_ALL_PLACES_TAKED                                                                                      0x00001002
#define ERROR_OBJECT_IS_EMPTY                                                                                       0x00001003
#define ERROR_NOTHING_TO_DO                                                                                         0x00001004

#define SYSTEM_ERROR_UNDEFINED                                                                                      0x50000000
#define SYSTEM_ERROR_DURING_ALLOC_MEMORY                                                                            0x50000001

#define SYSTEM_ERROR_WRITE_TO_FLASH_FAILED                                                                          0x50100000

#define ETHERNET_ERROR_SAMPLE_HARDNESS_UNEXPECTED_INITIAL_MODE                                                      0x80000100
//default error value for initialazing
#define DEFAULT_VALUE                                                                                               0x8000FFFF

#endif