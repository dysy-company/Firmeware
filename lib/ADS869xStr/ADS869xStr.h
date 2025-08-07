/**
 * @file ADS869xStr.h
 * @author Grigorii Bragin (braginsum1@gmail.com)
 * @brief Library for TI ADS869xStr ADC chip.
 * @version 0.1
 * @date 2023-01-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ADS869xStr_h
#define ADS869xStr_h

#include <mbed.h>
#include "..//..//include//Shared_Params.h"

#define  USE_HAL_SPI_REGISTER_CALLBACKS 1U

//SPI define
#define ADS869xStr_SPIx                             SPI1
//Clocks defines
#define ADS869xStr_SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define ADS869xStr_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define ADS869xStr_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS869xStr_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS869xStr_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define ADS869xStr_SPIx_CS_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
// #define ADS869xStr_SPIx_CS2_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
// #define ADS869xStr_SPIx_CS3_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADS869xStr_SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define ADS869xStr_SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()
//DMA defines
// #if BOARD_INDEX == 2
#define ADS869xStr_SPIx_DMA_RX_IRQHandler           DMA1_Stream1_IRQHandler
#define ADS869xStr_SPIx_DMA_RX_IRQn                 DMA1_Stream1_IRQn
#define ADS869xStr_SPIx_DMA_RX_IRQn_PreemptPriority 1
#define ADS869xStr_SPIx_DMA_RX_IRQn_SubPriority     0
#define ADS869xStr_SPIx_RX_DMA_REQUEST              DMA_REQUEST_SPI1_RX
#define ADS869xStr_SPIx_RX_DMA_STREAM               DMA1_Stream1

#define ADS869xStr_SPIx_DMA_TX_IRQHandler           DMA1_Stream3_IRQHandler
#define ADS869xStr_SPIx_DMA_TX_IRQn                 DMA1_Stream3_IRQn
#define ADS869xStr_SPIx_DMA_TX_IRQn_PreemptPriority 1
#define ADS869xStr_SPIx_DMA_TX_IRQn_SubPriority     0
#define ADS869xStr_SPIx_TX_DMA_REQUEST              DMA_REQUEST_SPI1_TX
#define ADS869xStr_SPIx_TX_DMA_STREAM               DMA1_Stream3
// #endif
// #if BOARD_INDEX == 3
// #define ADS869xStr_SPIx_DMA_RX_IRQHandler           DMA1_Stream2_IRQHandler
// #define ADS869xStr_SPIx_DMA_RX_IRQn                 DMA1_Stream2_IRQn
// #define ADS869xStr_SPIx_DMA_RX_IRQn_PreemptPriority 1
// #define ADS869xStr_SPIx_DMA_RX_IRQn_SubPriority     0
// #define ADS869xStr_SPIx_RX_DMA_CHANNEL              DMA_CHANNEL_0
// #define ADS869xStr_SPIx_RX_DMA_STREAM               DMA1_Stream2

// #define ADS869xStr_SPIx_DMA_TX_IRQHandler           DMA1_Stream5_IRQHandler
// #define ADS869xStr_SPIx_DMA_TX_IRQn                 DMA1_Stream5_IRQn
// #define ADS869xStr_SPIx_DMA_TX_IRQn_PreemptPriority 1
// #define ADS869xStr_SPIx_DMA_TX_IRQn_SubPriority     0
// #define ADS869xStr_SPIx_TX_DMA_CHANNEL              DMA_CHANNEL_0
// #define ADS869xStr_SPIx_TX_DMA_STREAM               DMA1_Stream5
// #endif
//SPI IRQ defines
#define ADS869xStr_SPIx_IRQHandler                  SPI1_IRQHandler
#define ADS869xStr_SPIx_IRQn                        SPI1_IRQn
#define ADS869xStr_SPIx_IRQn_PreemptPriority        1
#define ADS869xStr_SPIx_IRQn_SubPriority            0
//PC10     ------> SPI3_SCK
#define ADS869xStr_SPIx_SCK_PIN                     GPIO_PIN_5
#define ADS869xStr_SPIx_SCK_GPIO_PORT               GPIOA
#define ADS869xStr_SPIx_SCK_AF                      GPIO_AF5_SPI1

// #if ((CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED) || (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN))
//PB4     ------> SPI3_MISO
#define ADS869xStr_SPIx_MISO_PIN                    GPIO_PIN_6
#define ADS869xStr_SPIx_MISO_GPIO_PORT              GPIOA
#define ADS869xStr_SPIx_MISO_AF                     GPIO_AF5_SPI1
// #endif

// #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
//  //PC11     ------> SPI3_MISO
// #define ADS869xStr_SPIx_MISO_PIN                    GPIO_PIN_11
// #define ADS869xStr_SPIx_MISO_GPIO_PORT              GPIOC
// #define ADS869xStr_SPIx_MISO_AF                     GPIO_AF6_SPI3
// #endif

// #if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
// //PB1     ------> SPI3_NSS
// #define ADS869xStr_SPIx_CS_PIN                      GPIO_PIN_8
// #define ADS869xStr_SPIx_CS_GPIO_PORT                GPIOB
// #define ADS869xStr_SPIx_CS_AF                       GPIO_AF6_SPI3
// //PB8     ------> SPI3_NSS2
// #define ADS869xStr_SPIx_CS2_PIN                     GPIO_PIN_1
// #define ADS869xStr_SPIx_CS2_GPIO_PORT               GPIOB
// #define ADS869xStr_SPIx_CS2_AF                      GPIO_AF6_SPI3
// #else
//PB1     ------> SPI3_NSS
#define ADS869xStr_SPIx_CS_PIN                      GPIO_PIN_3
#define ADS869xStr_SPIx_CS_GPIO_PORT                GPIOA
#define ADS869xStr_SPIx_CS_AF                       GPIO_AF5_SPI1
// //PB8     ------> SPI3_NSS2
// #define ADS869xStr_SPIx_CS2_PIN                     GPIO_PIN_8
// #define ADS869xStr_SPIx_CS2_GPIO_PORT               GPIOB
// #define ADS869xStr_SPIx_CS2_AF                      GPIO_AF6_SPI3

// #endif
// //PA11    ------> SPI3_NSS3
// #define ADS869xStr_SPIx_CS3_PIN                     GPIO_PIN_11
// #define ADS869xStr_SPIx_CS3_GPIO_PORT               GPIOA
// // #define ADS869xStr_SPIx_CS3_AF                      GPIO_AF6_SPI3
//PB2     ------> SPI3_MOSI
#define ADS869xStr_SPIx_MOSI_PIN                    GPIO_PIN_5
#define ADS869xStr_SPIx_MOSI_GPIO_PORT              GPIOB
#define ADS869xStr_SPIx_MOSI_AF                     GPIO_AF5_SPI1


// #include <mbed.h>
#include "..//Calibration/Calibration.h"
#include "..//BasicElements/BasicElements.h"
#include "..//InternalFlash/InternalFlash.h"
#include "..//InternalFlashDMA/InternalFlashDMA.h"
#include "..//..//include//TypeDefs/ParamsTypeDefs.h"
#include "..//..//include//Ethernet/Ethernet_Errors.h"

extern BasicElements basic;
extern InternalFlash internalFlash;
extern InternalFlashDMA internalFlashDMA;

/**
 * @enum ADS869xStrTransferState
 * @brief DMA Channel Transfer State
 * 
 */
enum ADS869xStrTransferState : uint32_t{
	ADS869xStr_DMA_SPI_TRANSFER_WAIT,
	ADS869xStr_DMA_SPI_TRANSFER_IN_PROGRESS,
	ADS869xStr_DMA_SPI_TRANSFER_COMPLETE,
	ADS869xStr_DMA_SPI_TRANSFER_ERROR
};

/**
 * @enum ADS869xStrActiveAlarm
 * @brief Alarm include enumeration
 * @details Define include alarm bits in output word data. Values ready to write into Data Out Control Register
 */
enum ADS869xStrActiveAlarm{
    ADS869xStr_ACTIVE_ALARM_NOT_INCLUDE                            = 0b00,
    ADS869xStr_ACTIVE_ALARM_INCLUDE_H_FLAG                         = 0b01,
    ADS869xStr_ACTIVE_ALARM_INCLUDE_L_FLAG                         = 0b10,
    ADS869xStr_ACTIVE_ALARM_INCLUDE_BOTH                           = 0b11
};

/**
 * @enum ADS869xStrDataVal
 * @brief Data Value enumeration
 * @details Define output word data. Values ready to write into Data Out Control Register
 */
enum ADS869xStrDataVal{
    ADS869xStr_OUTPUT_VALUE_CONVERSION_DATA                        = 0b000,
    ADS869xStr_OUTPUT_VALUE_ALL_ZEROS                              = 0b100,
    ADS869xStr_OUTPUT_VALUE_ALL_UNITS                              = 0b101,
    ADS869xStr_OUTPUT_VALUE_ALTERNATING_ZEROS_AND_UNITS            = 0b110,
    ADS869xStr_OUTPUT_VALUE_ALTERNATING_ZERO_ZEROS_AND_UNIT_UNITS  = 0b111
};

/**
 * @enum ADS869xStrSPIMode
 * @brief SPI Mode enumeration
 * @details SPI Mode Set or Read to/from ADC SDI_CTL_REG register
 */
enum ADS869xStrSPIMode{
    ADS869xStr_SPI_MODE_CPOL_0_CPHASE_0                            = 0b00,
    ADS869xStr_SPI_MODE_CPOL_0_CPHASE_1                            = 0b01,
    ADS869xStr_SPI_MODE_CPOL_1_CPHASE_0                            = 0b10,
    ADS869xStr_SPI_MODE_CPOL_1_CPHASE_1                            = 0b11
};

/**
 * @enum ADS869xStrSDO1Config
 * @brief SDO1 Config Enumeration
 * @details SDO1_CONFIG Bits in SDO_CTL_REG Register
 */
enum ADS869xStrSDO1Config{
    ADS869xStr_SDO1_CONFIG_TRI_STATE_1BIT_SDO_MODE                 = 0b0000000000,
    ADS869xStr_SDO1_CONFIG_ALARM_1BIT_SDO_MODE                     = 0b0100000000,
    ADS869xStr_SDO1_CONFIG_GPO_1BIT_SDO_MODE                       = 0b1000000000,
    ADS869xStr_SDO1_CONFIG_COMBINED_SDO0_2BIT_MODE                 = 0b1100000000
};

/**
 * @enum ADS869xStrSSyncClk
 * @brief SSYNC_CLK enumeration
 * @details This bit controls the source of the clock selected for source-synchronous transmission. This bit takes effect ONLY in the ADC master clock of source-synchronous mode of operation.
 */
enum ADS869xStrSSyncClk{
    ADS869xStr_SSYNC_CLK_EXTERNAL_SCLK                             = 0b00000000,
    ADS869xStr_SSYNC_CLK_INTERNAL_CLOCK                            = 0b01000000
};

/**
 * @enum ADS869xStrSDOMode
 * @brief SDO_MODE enumerator
 * @details These bits control the data output modes of the device.
 */
enum ADS869xStrSDOMode{
    ADS869xStr_SDO_MODE_SAME_AS_SDI                                = 0b00,
    ADS869xStr_SDO_MODE_INVALID_CONFIG                             = 0b10,
    ADS869xStr_SDO_MODE_FOLLOW_ADC_MASTER_CLOCK_OR_SS_PROTOCOL     = 0b11
};

/**
 * @enum ADS869xStrRange
 * @brief Input Range enumeration
 * @details Values ready to write into Input Range Register
 */
enum ADS869xStrRange{
    ADS869xStr_PM_3                                                = 0b0000,   //+-3*Vref
    ADS869xStr_PM_2_5                                              = 0b0001,   //+-2.5*Vref
    ADS869xStr_PM_1_5                                              = 0b0010,   //+-1.5*Vref
    ADS869xStr_PM_1_25                                             = 0b0011,   //+-1.25*Vref
    ADS869xStr_PM_0_625                                            = 0b0100,   //+-0.625*Vref
    ADS869xStr_P_3                                                 = 0b1000,   //+3*Vref
    ADS869xStr_P_2_5                                               = 0b1001,   //+2.5*Vref
    ADS869xStr_P_1_5                                               = 0b1010,   //+1.5*Vref
    ADS869xStr_P_1_25                                              = 0b1011    //+1.25*Vref
};

/**
 * @enum ADS869xStrExternalRef
 * @brief External Reference enumeration
 * @details Define external/intenal refence voltage selection.
 */
enum ADS869xStrExternalRef{
    ADS869xStr_EXTERNAL_REF_DISABLED                               = 0b0000000,
    ADS869xStr_EXTERNAL_REF_ENABLED                                = 0b1000000
};

/**
 * @enum ADS869xStrCmd
 * @brief Input commands enumeration
 * @details Define commands values. Values ready to write into ADC.
 */
enum ADS869xStrCmd : uint32_t{
	ADS869xStr_CMD_NOP                                             = 0b00000000000000000000000000000000,
	ADS869xStr_CMD_CLEAR_HWORD                                     = 0b11000000000000000000000000000000,
	ADS869xStr_CMD_READ_HWORD                                      = 0b11001000000000000000000000000000,
	ADS869xStr_CMD_READ_BYTE                                       = 0b01001000000000000000000000000000,
	ADS869xStr_CMD_WRITE                                           = 0b11010000000000000000000000000000,
	ADS869xStr_CMD_WRITE_MSB                                       = 0b11010010000000000000000000000000,
	ADS869xStr_CMD_WRITE_LSB                                       = 0b11010100000000000000000000000000,
	ADS869xStr_CMD_SET_HWORD                                       = 0b11011000000000000000000000000000
};

/**
 * @typedef @struct ADS869xStrSendDataPacket_t
 * @brief Send packet struct ready to send into ADC;
 * @details Define command, address and data value to write;
 */
typedef struct ADS869xStrSendDataPacket{
    ADS869xStrCmd              cmd;
    uint32_t                address;
    uint16_t                data;
} ADS869xStrSendDataPacket_t;

/**
 * @typedef @struct ADS869xStrOutputDataWord_t
 * @brief Output word data structure from ADC.
 * @details Ready to use (align) output data from ADC.
 */
typedef struct ADS869xStrOutputDataWord{
    uint32_t    conversionResult;
    uint8_t     deviceAddress;
    uint8_t     AVDDAlarmFlags;
    uint8_t     inputAlarmFlags;
    uint8_t     inputRange;
    uint8_t     parityBits;
} ADS869xStrOutputDataWord_t;

/**
 * @enum ADS869xStrRegisterAddress
 * @brief Register addresses enumeration
 * @details Define register addresses. Ready to write into ADC input data word.
 */
enum ADS869xStrRegisterAddress : uint32_t{
	ADS869xStr_DEVICE_ID_REG                               = 0x00000000,
	ADS869xStr_RST_PWRCTL_REG                              = 0x00040000,
	ADS869xStr_SDI_CTL_REG                                 = 0x00080000,
	ADS869xStr_SDO_CTL_REG                                 = 0x000C0000,
	ADS869xStr_DATAOUT_CTL_REG                             = 0x00100000,
	ADS869xStr_RANGE_SEL_REG                               = 0x00140000,
	ADS869xStr_ALARM_REG                                   = 0x00200000,
	ADS869xStr_ALARM_H_TH_REG                              = 0x00240000,
	ADS869xStr_ALARM_L_TH_REG                              = 0x00280000
};

/**
 * @enum ADS869xStrRegisterShift
 * @brief Register offsets enumeration
 * @details Define register addresses offsets. Ready to write into ADC input data word.
 */
enum ADS869xStrRegisterShift : uint32_t{
    ADS869xStr_REG_NULL_BYTE                               = 0x00000000,
    ADS869xStr_REG_FIRST_BYTE                              = 0x00010000,
    ADS869xStr_REG_SECOND_BYTE                             = 0x00020000,
    ADS869xStr_REG_THIRD_BYTE                              = 0x00030000
};

/**
 * @typedef @struct ADS869xStrRegisters_t
 * @brief All ADC registers data structure.
 * @details Define all ADC registers values;
 */
typedef struct ADS869xStrRegisters{
    uint32_t    DEVICE_ID_REG;
    uint32_t    RST_PWRCTL_REG;
    uint32_t    SDI_CTL_REG;
    uint32_t    SDO_CTL_REG;
    uint32_t    DATAOUT_CTL_REG;
    uint32_t    RANGESELREG;
    uint32_t    ALARM_REG;
    uint32_t    ALARM_H_TH_REG;
    uint32_t    ALARM_L_TH_REG;
} ADS869xStrRegisters_t;

/**
 * @brief Register offsets enumeration
 * @details Define register addresses offsets. Ready to write into ADC input data word.
 */
#define ADS869xStr_DATAOUT_CTL_REG_DEVICE_ADDR_INCL        0x00004000
#define ADS869xStr_DATAOUT_CTL_REG_VDD_ACTIVE_ALARM_INCL   0x00003000
#define ADS869xStr_DATAOUT_CTL_REG_IN_ACTIVE_ALARM_INCL    0x00000C00
#define ADS869xStr_DATAOUT_CTL_REG_RANGE_INCL              0x00000100
#define ADS869xStr_DATAOUT_CTL_REG_PAR_EN                  0x00000008
#define ADS869xStr_DATAOUT_CTL_REG_DATA_VAL                0x00000007

#define ADS869xStr_RST_PWRCTL_REG_WKEY                     0x0000FF00
#define ADS869xStr_RST_PWRCTL_REG_VDD_AL_DIS               0x00000020
#define ADS869xStr_RST_PWRCTL_REG_IN_AL_DIS                0x00000010
#define ADS869xStr_RST_PWRCTL_REG_RSTN_APP                 0x00000004
#define ADS869xStr_RST_PWRCTL_REG_NAP_EN                   0x00000002
#define ADS869xStr_RST_PWRCTL_REG_PWRDN                    0x00000001

#define ADS869xStr_RANGE_SEL_REG_INTREF_DIS                0x00000040
#define ADS869xStr_RANGE_SEL_REG_RANGE_SEL                 0x0000000F

#define ADS869xStr_ALARM_REG_ACTIVE_VDD_L_FLAG             0x00008000
#define ADS869xStr_ALARM_REG_ACTIVE_VDD_H_FLAG             0x00004000
#define ADS869xStr_ALARM_REG_ACTIVE_IN_L_FLAG              0x00000800
#define ADS869xStr_ALARM_REG_ACTIVE_IN_H_FLAG              0x00000400
#define ADS869xStr_ALARM_REG_TRP_VDD_L_FLAG                0x00000080
#define ADS869xStr_ALARM_REG_TRP_VDD_H_FLAG                0x00000040
#define ADS869xStr_ALARM_REG_TRP_IN_L_FLAG                 0x00000020
#define ADS869xStr_ALARM_REG_TRP_IN_H_FLAG                 0x00000010
#define ADS869xStr_ALARM_REG_OVW_ALARM                     0x00000001


constexpr static double ADS869xStrInternalReferenceVoltage = 4.096;

class ADS869xStr{
    public:
        /**
         * @brief Construct a new ADS869xStr object
         * @details Used static define SPI.
         * 
         * @param spiPrescaler divider SPI clock.
         * @param numberOfCalibrationPoints default 256 points.
         */
        ADS869xStr(unsigned long spiPrescaler, unsigned long numberOfCalibrationPoints);
        
        /**
         * @brief Destroy the ADS869xStr object
         * 
         */
        ~ADS869xStr();
        
        /**
         * @brief Initialize callbacks and init SPI.
         * 
         * @return int HAL_OK if init complete.
         */
        int init(void);

        /**
         * @brief Set the Vref voltage
         * @details Calculate LSBWeight for getting voltage from ADC code.
         * 
         * @param Vref 
         */
        void setVref(double Vref);
        
        double calcVoltage(uint32_t &DataBits);
        uint32_t calcCode(double voltage);
        double calcStrain(uint32_t code);
        double calcStrain2(uint32_t code);

        /**
         * @brief This method start SPI transfer.
         * @details This method using blocking mode. Send command if it was prepared in queue.
         * 
         * @return HAL_StatusTypeDef - status of transfer. HAL_OK if transfer complete successful.
         */
        HAL_StatusTypeDef transferBlocking(void);

        //  /**
        //  * @brief This method start SPI transfer.
        //  * @details This method using blocking mode. Send command if it was prepared in queue.
        //  * 
        //  * @return HAL_StatusTypeDef - status of transfer. HAL_OK if transfer complete successful.
        //  */
        // HAL_StatusTypeDef transferBlocking2(void);
        
        //  /**
        //  * @brief This method start SPI transfer.
        //  * @details This method using blocking mode. Send command if it was prepared in queue.
        //  * 
        //  * @return HAL_StatusTypeDef - status of transfer. HAL_OK if transfer complete successful.
        //  */
        // HAL_StatusTypeDef transferBlocking3(void);

        /**
         * @brief Launch DMA channel for receiving ADC value.
         * @details This method using non-blocking mode. Send command if it was prepared in queue.
         * 
         * @return HAL_StatusTypeDef - status of transfer. HAL_OK if start transfer complete successful. 
         */
        HAL_StatusTypeDef startTransfer(bool firstStart);
        
        // /**
        //  * @brief Launch DMA channel for receiving ADC value.
        //  * @details This method using non-blocking mode. Send command if it was prepared in queue.
        //  * 
        //  * @return HAL_StatusTypeDef - status of transfer. HAL_OK if start transfer complete successful. 
        //  */
        // HAL_StatusTypeDef startTransfer2(bool firstStart);

        // /**
        //  * @brief Launch DMA channel for receiving ADC value.
        //  * @details This method using non-blocking mode. Send command if it was prepared in queue.
        //  * 
        //  * @return HAL_StatusTypeDef - status of transfer. HAL_OK if start transfer complete successful. 
        //  */
        // HAL_StatusTypeDef startTransfer3(bool firstStart);

        /**
         * @brief Get the Transfer Status of DMA transaction
         * 
         * @return uint32_t Status
         */
        uint32_t getTransferStatus(void);

        /**
         * @brief Clear the Transfer Status of DMA transaction
         * 
         */
        void clearTransferStatus(void);
        
        
        ///TODO
        
        
        //return last saved ADC value
        uint32_t getLastCode();
        uint32_t getLastCode(bool parseResult);

        // uint32_t getLastCode2();
        // uint32_t getLastCode2(bool parseResult);

        // uint32_t getLastCode3();
        // uint32_t getLastCode3(bool parseResult);

        float getVoltage(void);
        //float getDeformation(void);

        /**
         * @brief Prepare set the Device Address of current ADC. Data will send while next SPI transfer.
         * 
         * @param[in] deviceAddress Use only 4 LSB bits. Addresses ranges from 0x0 to 0xF;
         */
        void setDeviceAddress(uint8_t deviceAddress);
        
        /**
         * @brief Prepare set Reset Power Control Register. Data will send while next SPI transfer.
         * 
         * @param[in] VDDAlDis Set VDD alarm. Disabled if false. Enabled if true. 
         * @param[in] InAlDis Set Input alarm. Disabled if false. Enabled if true. 
         * @param[in] RSTnApp nRST pin function. If false nRST pin functions as a POR class reset (causes full device initialization). If true nRST pin functions as an application reset (only user-programmed modes are cleared).
         * @param[in] NAPEN NAP mode. If false NAP mode of converter is disable. True enables  the converter to enter NAP mode if CONVST/nCS is held high after the current conversion completes.
         * @param[in] PWRDN Converter mode. False - converter into active mode. True - converter into power-down mode.
         */
        void setResetPwrCtl(bool VDDAlDis, bool InAlDis, bool RSTnApp, bool NAPEN, bool PWRDN);
        
        /**
         * @brief Prepare set Data Out Register. Data will send while next SPI transfer. 
         * @details This command sets ADC Output Word content.
         * 
         * @param[in] deviceAddr True - include Device Address in output word.
         * @param[in] vddActiveAlarm 0b00 - do not include. 0b01 - include ACTIVE_VDD_H_FLAG. 0b01 - include ACTIVE_VDD_H_FLAG. 0b11 - include both flags.
         * @param[in] inActiveAlarm 0b00 - do not include. 0b01 - include ACTIVE_IN_H_FLAG. 0b01 - include ACTIVE_IN_H_FLAG. 0b11 - include both flags.
         * @param[in] range True - include 4-bit input range setting in output word.
         * @param[in] parity True - include parity bits in output word. Two parity bits(ADC output and output data frame) are appended to the LSBs of the output data.
         * @param[in] dataVal These bits control the data value output by the converter. Bits corresponding ADS869xStrDataVal type values.
         */
        void setDataOut(bool deviceAddr, ADS869xStrActiveAlarm vddActiveAlarm, ADS869xStrActiveAlarm inActiveAlarm, bool range, bool parity, ADS869xStrDataVal dataVal);
        
        /**
         * @brief Prepare set the Input Range Register
         * @details This command control source of reference voltage and input voltage reference.
         * 
         * @param externalRef False - internal reference enable. True - internal reference disable, used external reference.
         * @param range These bits control input voltage range. Values corresponding ADS869xStrRange type;
         */
        void setRange(ADS869xStrExternalRef externalRef, ADS869xStrRange range);
        
        /**
         * @brief Prepare set ADC SPI Mode
         * @details This command set ADC SPI Mode into the SDI_CTL_REG Register
         * 
         * @param spiMode 2 bits to set CPOL (correspond MSB bit) and CPHASE (correspond LSB bit).
         */
        void setADCSPIMode(ADS869xStrSPIMode spiMode);

        /**
         * @brief Prepare set ADC SDO Mode
         * @details This command set SDO Mode Register. This register controls the data protocol used to transmit data out from the SDO-x pins.
         * 
         * @param SDO1Config Two bits are used to configure ALARM/SDO-1/GPO.
         * @param SSyncClk This bit controls the source of the clock selected for source-synchronous transmission. This bit takes effect ONLY in the ADC master clock of source-synchronous mode of operation.
         * @param SDOMode These bits control the data output modes of the device.
         */
        void setADCSDOMode(ADS869xStrSDO1Config SDO1Config, ADS869xStrSSyncClk SSyncClk, ADS869xStrSDOMode SDOMode);

        /**
         * @brief Prepare set the Alarm Register
         * @details This command control output alarm flags (active and tripped) for the input and AVDD alarm.
         * 
         * @param activeVDDLFlag Active Alarm output flag for low AVDD voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param activeVDDHFlag Active Alarm output flag for high AVDD voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param activeInLFlag Active Alarm output flag for low input voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param activeInHFlag Active Alarm output flag for high input voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param TrpVDDLFlag Tripped Alarm output flag for low VDD voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param TrpVDDHFlag Tripped Alarm output flag for high VDD voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param TrpInLFlag Tripped Alarm output flag for low input voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param TrpInHFlag Tripped Alarm output flag for high input voltage. 0 - no alarm. 1 - alarm condition exists.
         * @param OVW Logical OR outputs all tripped alarm flags. 0 - no alarm. 1 - alarm condition exists.
         */
        void setActiveAlarm(
            bool activeVDDLFlag, 
            bool activeVDDHFlag, 
            bool activeInLFlag, 
            bool activeInHFlag, 
            bool TrpVDDLFlag, 
            bool TrpVDDHFlag,
            bool TrpInLFlag,
            bool TrpInHFlag,
            bool OVW
        );

        /**
         * @brief Prepare set alarm hysteresis and high threshold for the input alarm
         * @details This command set ALARM_H_TH_REG Register. After this command need to complete 2 transfers.
         * 
         * @param hystVoltage 6-bit[7:2] hysteresis value for the input alarm. Bits [1:0] will set to 0b00.
         * @param highVoltage Threshold for comparison. Will appended with 0b00.
         */
        void setHystAndHighAlarm(uint8_t hystVoltage, uint16_t highVoltage);

        /**
         * @brief Prepare set alarm low threshold for the input alarm
         * @details This command set ALARM_L_TH_REG Register. 
         * 
         * @param lowVoltage Threshold for comparison. Will appended with 0b00.
         */
        void setLowAlarm(uint16_t lowVoltage);

        void setFlashOperationType(uint32_t flashOperationType);

        void setCalibrCoefs(double k, double b);
        void getCalibrCoefs(double *k, double *b);
        errorCode_t writeCalibrCoefsInFlash(double k, double b);
        errorCode_t readCalibrCoefsFromFlash(double *k, double *b);
        errorCode_t waitReadCompleteCalibrCoefsFromFlash(int timeout);
        errorCode_t writeCalibrPointsInFlash(point_t *points, int size);
        errorCode_t readCalibrPointsFromFlash(point_t *points, int size);
        errorCode_t readCalibrPointsSizeFromFlash(int *size);
        Calibration *calibration;
        errorCode_t writeCalibrPointsInFlash2(point_t *points, int size);
        errorCode_t readCalibrPointsFromFlash2(point_t *points, int size);
        errorCode_t readCalibrPointsSizeFromFlash2(int *size);
        Calibration *calibration2;

        // void setCalibrCoefs2(double k, double b);
        // void getCalibrCoefs2(double *k, double *b);
        // errorCode_t writeCalibrCoefsInFlash2(double k, double b);
        // errorCode_t readCalibrCoefsFromFlash2(double *k, double *b);
        // errorCode_t waitReadCompleteCalibrCoefsFromFlash2(int timeout);
        // errorCode_t writeCalibrPointsInFlash2(point_t *points, int size);
        // errorCode_t readCalibrPointsFromFlash2(point_t *points, int size);
        // errorCode_t readCalibrPointsSizeFromFlash2(int *size);
        // Calibration *calibration2;

        // void setCalibrCoefs3(double k, double b);
        // void getCalibrCoefs3(double *k, double *b);
        // errorCode_t writeCalibrCoefsInFlash3(double k, double b);
        // errorCode_t readCalibrCoefsFromFlash3(double *k, double *b);
        // errorCode_t waitReadCompleteCalibrCoefsFromFlash3(int timeout);
        // errorCode_t writeCalibrPointsInFlash3(point_t *points, int size);
        // errorCode_t readCalibrPointsFromFlash3(point_t *points, int size);
        // errorCode_t readCalibrPointsSizeFromFlash3(int *size);
        // Calibration *calibration3;
    private:
        
        CircularBuffer<ADS869xStrSendDataPacket_t, 10> sendQueue;
        
        Semaphore *readFromFlashSemaphore;
        Semaphore *readFromFlashSemaphore2;
        Semaphore *readFromFlashSemaphore3;
        double _k = 0.00341142;//0.0035078;//-0.00334599;//-0.00396559;
        double _b = -108.929;//-111.626;//111.752;//123.595;
        double _k2 = 0.00341142;//0.0035078;//-0.00334599;//-0.00396559;
        double _b2 = -108.929;//-111.626;//111.752;//123.595;
        // double _k3 = 0.00341142;//copy paste
        // double _b3 = -108.929;//copy paste
        
        /*  Vref voltage    */
        double Vref = ADS869xStrInternalReferenceVoltage;
        ADS869xStrRange range = ADS869xStr_PM_3;
        ADS869xStrExternalRef externalReference = ADS869xStr_EXTERNAL_REF_DISABLED;
        double LSBWeight = 0;
        double PFS, NFS;
        // #if BOARD_INDEX == 2
        uint32_t SendRawBits[1];
        uint32_t RecvRawBits[1];
        // #endif
        // #if BOARD_INDEX == 3
        // uint16_t SendRawBits[2];
        // uint32_t RecvRawBits[2];
        // #endif
        ADS869xStrSendDataPacket_t lastPacket;
        // ADS869xStrSendDataPacket_t lastPacket2;
        // ADS869xStrSendDataPacket_t lastPacket3;
        ADS869xStrOutputDataWord_t outputWord;
        ADS869xStrRegisters_t registers = {0};
        ADS869xStrCmd lastCmd = ADS869xStr_CMD_NOP;
        uint32_t lastAnswer = 0x0;

        uint32_t _flashOperationType = FLASH_OPERATION_CPU;

        /**
         * @brief Calculate PFS, NFS
         * @details This method calculate Positive Full-Scale, Negative Full-Scale. Units is Volts. Reference voltage must be set before calculate.
         * 
         * @param PFS Positive Full-Scale (V)
         * @param NFS Negative Full-Scale (V)
         */
        void getPFSNFS(double &PFS, double &NFS);

        /**
         * @brief Prepare and calculate bits for sending
         * 
         * @param packet data struct 
         */
        void prepareSendBits(ADS869xStrSendDataPacket_t *packet);

        /**
         * @brief Parse receiving bits
         * 
         * @param packet data struct
         */
        void parseReceiveBits(ADS869xStrSendDataPacket_t *packet);
};

#endif