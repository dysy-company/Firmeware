
/*
    This file content all pins settings
*/
#include <mbed.h>

#ifndef Pin_Config_h743zi_h
#define Pin_Config_h743zi_h
/*
    PORT A
*/
    // PinName DO_ADC_ADS8320_StrainSensor_CS          = PA_4;     //SPI1
    // PinName DO_ADC_ADS8320_StrainSensor_SCK         = PA_5;     //SPI1
    // PinName DI_ADC_ADS8320_StrainSensor_MISO        = PA_6;     //SPI1
    // PinName DO_1W_To_UART1_TX_TEDs                  = PA_9;     //UART1TX
    // PinName DI_1W_To_UART1_RX_TEDs                  = PA_10;
    // PinName DI_RC_0_ENCODER_A                       = PA_15;    //TIM2 to main board J1 socket
/*
    PORT B
*/           
    // PinName DI_RC_1_ENCODER_B                       = PB_3;     //TIM2 to main board J1 socket
    // PinName DO_ADC_ADS8320_DeformationSensor_CS     = PB_9;     //SPI2
    // PinName DO_UART3_TX_CONTROL_PANEL               = PB_10;
    // PinName DI_UART3_RX_CONTROL_PANEL               = PB_11;
/*      
    PORT C      
*/      
    // PinName DI_ADC_ADS8320_DeformationSensor_MISO   = PC_2;//SPI2
    //PinName DO_DAC_AD5621_VoltAdjuster_MOSI         = PC_3;//SPI2


    // PinName DO_RSSI_DisplSensor_SCK                 = PC_10;//SPI3
    // PinName DI_RSSI_DisplSensor_DATA                = PC_11;//SPI3
/*      
    PORT D      
*/      
    // PinName DO_UART2_TX_MOTOR_CONTROL               = PD_5;
    // PinName DI_UART2_RX_MOTOR_CONTROL               = PD_6;
/*
    PORT E
*/
    //DAC MCP4921 Servo valve
    // PinName DO_DAC_MCP4921_SerValve_SCK             = PE_2;//SPI4
    // PinName DO_DAC_MCP4921_SerValve_CS              = PE_11;//SPI4
    // PinName DO_DAC_MCP4921_SerValve_MOSI            = PE_6;//SPI4
    //pulse displacement sensor     
    //PinName DO_StartPulse                           = PE_3;
    //PinName DI_StopPulse                            = PE_5; //NOT_USED
    
    //hardware output analog cmds      
    PinName DO_RC_0                                 = PE_7;     //to additional board J3 socket
    PinName DO_RC_1                                 = PE_8;     //to additional board J3 socket
    PinName DO_RC_2_MOTOR_STEP_CW                   = PE_9;     //to main board J1 socket
    PinName DO_RC_3_MOTOR_DIR_CCW                   = PG_10;    //to main board J1 socket
    PinName DO_RC_4_WARNING_LIGHT                   = PE_4;     //to main board J1 socket
    PinName DO_RC_5_MOTOR_ENABLE                    = PG_12;    //to main board J1 socket
    PinName DO_RC_6_ALARM_LIGHT                     = PG_12;    //to main board J1 socket
    PinName DO_RC_7                                 = PE_0;     //to additional board J3 socket 
    PinName DO_RC_8                                 = PE_1;     //to additional board J3 socket
    PinName DO_RC_9                                 = PG_14;    //to additional board J3 socket
    PinName DO_RC_10                                = PG_15;    //to additional board J3 socket
    PinName DO_RC_11                                = PE_3;     //to additional board J3 socket
/*
    PORT F
*/
    //Direction pins
    PinName DO_Direct_H                             = PF_0;
    //PinName DO_Direct_L = PC_7;
    PinName DO_Reverse_H                            = PF_1;
    //PinName DO_Reverse_L = PA_13
    //enable power to circuit segments
    // PinName DO_CoilPower                            = PF_2;
    // PinName DO_SSIPower                             = PF_3;
    //debug for timing pin
    PinName DO_Debug                                = PF_4;
    
    //Relays
    PinName DO_SwitchStrainAmp                      = PF_5;
    // PinName DO_SwitchStrainNumbPins                 = PF_10;

    // PinName DO_DAC_AD5621_StrainSensorPwr_CS        = PF_6;

    // PinName DO_DACDeformStrainSensPwr_ADCTM_CLK     = PF_7;     //SPI5
    // PinName DI_ADCTM_MISO                           = PF_8;     //SPI5
    // PinName DO_DAC_DeformAndStrainSensPwr_MOSI      = PF_9;     //SPI5
    //ADC MCP3201 SPI devices
    //PinName DO_ADC_MCP3201_SCK                      = PF_7;   //SPI5
    //PinName DI_ADC_MCP3201_MISO                     = PF_8;   //SPI5
    // PinName DO_ADC_MCP3201_SSICurrent_CS            = PF_12;    //SPI5
    // PinName DO_ADC_MCP3201_StrainSenseCurrent_CS    = PF_13;    //SPI5
    // PinName DO_ADC_MCP3201_CoilCurrent_CS           = PF_14;    //SPI5
    // PinName DO_ADC_MCP3201_StrainSenseVoltage_CS    = PF_15;    //SPI5
/*
    PORT G
*/
    //hardware input analog cmds 
    //PinName DI_RC_0_ENCODER_A                     = PA_15;    describe in portA
    //PinName DI_RC_1_ENCODER_B                     = PB_3;     describe in portB
    PinName DI_RC_2_UP_END_SWITCH                   = PG_2;     //to additional board J3 socket     
    PinName DI_RC_3_DOWN_END_SWITCH                 = PG_3;     //to additional board J3 socket
    PinName DI_RC_4_EMERGENCY_STOP                  = PG_4;     //to additional board J3 socket
    PinName DI_RC_5                                 = PG_5;     //to additional board J3 socket
    PinName DI_RC_6                                 = PG_6;     //to additional board J3 socket    
    PinName DI_RC_7                                 = PG_9;     //to additional board J3 socket  moveUp
    PinName DI_RC_8                                 = PG_10;    //to additional board J3 socket  moveDown
    PinName DI_RC_9                                 = PG_12;    //to additional board J3 socket
    PinName DI_RC_10                                = PG_14;    //to additional board J3 socket
    PinName DI_RC_11                                = PG_15;    //to additional board J3 socket
    
/*
    Input port
*/
    PinName IP_MK1  = PC_8;
    PinName IP_MK2  = PC_9;
    PinName IP_MK3  = PD_14;
    PinName IP_MK4  = PD_15;
    PinName IP_MK5  = PE_10;
    PinName IP_MK6  = PE_11;
    PinName IP_MK7  = PE_12;
    PinName IP_MK8  = PE_13;
    PinName IP_MK9  = PE_14;
    PinName IP_MK10 = PE_15;

/*
    LEDs
*/
    PinName DO_LED_GREEN = PB_0;
    PinName DO_LED_YELLOW = PE_1;
    PinName DO_LED_RED = PB_14;

//     PinName COM1 = PC_12;
//     PinName COM2 = PD_2;
//     PinName COM3 = PD_3;

//     PinName Res = PG_2;
//     PinName TEDS_OUT = PA_9;
//     PinName TEDS_IN = PA_10;
//     PinName SDA = PF_15;
//     PinName SCL = PF_14;

#endif