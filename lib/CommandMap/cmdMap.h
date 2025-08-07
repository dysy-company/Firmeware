#ifndef CMDMAP_H
#define CMDMAP_H

#include "mbed.h"
// #include <map>
#include <iostream>
#include <list>
#include "../../include/Shared_Params.h"

#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
    #include "Map_SH.h"
#endif
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN
    #include "Map_SM.h"
#endif



#define CMD_MAP_OK 0
#define CMD_MAP_ERROR -1
#define CMD_MAP_ERROR_PINTYPE -2

typedef enum
{
    FALLING = 0,
    RISING = 1,
} interruptMode_t;

typedef enum HwCmd : uint16_t
{
    NOT_USED = 0xFFFF,
    COM_1_MK = 1,
    COM_2_MK = 2,
    COM_3_MK = 3,
    COM_4_MK = 4,
    COMMAND_1 = 11,
    COMMAND_2 = 12,
    COMMAND_3 = 13,
    COMMAND_4 = 14,
    COMMAND_5 = 15,
    COMMAND_6 = 16,
    COMMAND_7 = 17,
    COMMAND_8 = 18,
    IP_MK_1 = 31,
    IP_MK_2 = 32,
    IP_MK_3 = 33,
    IP_MK_4 = 34,
    IP_MK_5 = 35,
    IP_MK_6 = 36,
    IP_MK_7 = 37,
    IP_MK_8 = 38,
    IP_MK_9 = 39,
    IP_MK_10 = 40,

} HwCmd_t;

enum HwPinType : uint8_t
{
    Out = 0,
    In = 1,
    Interrupt = 2
};

typedef struct HwBinding
{
    PinName pin = NC;
    HwCmd_t cmd = NOT_USED;
    HwPinType pinType = Out;
    mbed::Callback<void()> callbac = nullptr;
    interruptMode_t interruptMode = FALLING;
    union
    {
        DigitalOut *digitalOut;
        DigitalIn *digitalIn;
        InterruptIn *interruptIn;
    };
} HwBinding;

class CommandMap
{
public:
    CommandMap() {}
    /**
     * @brief Registers a function in the command map
     * @param cmd The command to register
     * @param pinType In/Out/Interrupt
     * @param pin PinName
     * @param callbac The function to execute
     */
    int8_t registerCommand(HwCmd_t cmd, DigitalOut *pin);
    int8_t registerCommand(HwCmd_t cmd, DigitalIn *pin);

    /**
     * @brief Registers a function in the command map
     * @param cmd The command to register
     * @param pin PinName
     * @param callbac The function to execute
     * @param mode Interrupt mode: FALLING/RISING
     */
    int8_t registerCommand(HwCmd_t cmd, InterruptIn *pin, mbed::Callback<void()> callbac, uint8_t mode); // bind callback

    /**
     * @brief Read value from any pin
     */
    int8_t read(PinName pin);

    /**
     * @brief Write value to "Out" pin. else return error
     * @param value_for_write The value to write
     */
    int8_t write(PinName pin, int value_for_write);

    /**
     * @brief Test function to write value to all "Out" pins
     * @param value_for_write The value to write
     */
    int8_t writeAllOuts(int value_for_write);

    int8_t getAllPins(char *data);    
    uint16_t getAllInType(HwPinType type, char *data);

    uint32_t get_size();
    int8_t replaceCommand(HwCmd_t cmd, HwCmd_t cmd_new);
    int8_t deleteCommand(HwCmd_t cmd);

    ~CommandMap()
    {
        // ������� ����������� ���������� �������
        for (auto &binding : hwBindings)
        {
            switch (binding.pinType)
            {
            case Out:
                delete binding.digitalOut;
                break;
            case In:
                delete binding.digitalIn;
                break;
            case Interrupt:
                delete binding.interruptIn;
                break;
            }
        }
    }

private:
    int8_t addPinNameToStr(PinName pin, string *str);
    std::list<HwBinding> hwBindings;
    void registerPin(HwBinding *binding);
};

#endif