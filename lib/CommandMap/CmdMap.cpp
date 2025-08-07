#include "CmdMap.h"

int8_t CommandMap::registerCommand(HwCmd_t cmd, DigitalOut *pin)
{
    HwBinding binding;
    binding.pinType = Out;
    binding.cmd = cmd;
    binding.digitalOut = pin;

    binding.pin = NC;
    binding.callbac = nullptr;
    registerPin(&binding);

    hwBindings.push_back(binding);
    return CMD_MAP_OK;
}
int8_t CommandMap::registerCommand(HwCmd_t cmd, DigitalIn *pin)
{
    HwBinding binding;
    binding.pinType = In;
    binding.cmd = cmd;
    binding.digitalIn = pin;

    binding.pin = NC;
    binding.callbac = nullptr;
    registerPin(&binding);

    hwBindings.push_back(binding);
    return CMD_MAP_OK;
}

void CommandMap::registerPin(HwBinding *binding)
{
#if (CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN)
    switch (binding->cmd)
    {
    case COM_1_MK:
        binding->pin = COM_1_MK_PIN;
        break;
    case COM_2_MK:
        binding->pin = COM_2_MK_PIN;
        break;
    case COM_3_MK:
        binding->pin = COM_3_MK_PIN;
        break;
    case COM_4_MK:
        binding->pin = COM_4_MK_PIN;
        break;
    case COMMAND_1:
        binding->pin = COMMAND_1_PIN;
        break;
    case COMMAND_2:
        binding->pin = COMMAND_2_PIN;
        break;
    case COMMAND_3:
        binding->pin = COMMAND_3_PIN;
        break;
    case COMMAND_4:
        binding->pin = COMMAND_4_PIN;
        break;
    case COMMAND_5:
        binding->pin = COMMAND_5_PIN;
        break;
    case COMMAND_6:
        binding->pin = COMMAND_6_PIN;
        break;
    case COMMAND_7:
        binding->pin = COMMAND_7_PIN;
        break;
    case COMMAND_8:
        binding->pin = COMMAND_8_PIN;
        break;
    case IP_MK_1:
        binding->pin = IP_MK_1_PIN;
        break;
    case IP_MK_2:
        binding->pin = IP_MK_2_PIN;
        break;
    case IP_MK_3:
        binding->pin = IP_MK_3_PIN;
        break;
    case IP_MK_4:
        binding->pin = IP_MK_4_PIN;
        break;
    case IP_MK_5:
        binding->pin = IP_MK_5_PIN;
        break;
    case IP_MK_6:
        binding->pin = IP_MK_6_PIN;
        break;
    case IP_MK_7:
        binding->pin = IP_MK_7_PIN;
        break;
    case IP_MK_8:
        binding->pin = IP_MK_8_PIN;
        break;
    case IP_MK_9:
        binding->pin = IP_MK_9_PIN;
        break;
    case IP_MK_10:
        binding->pin = IP_MK_10_PIN;
        break;
    default:
        binding->pin = NC;
        break;
    }
#endif
#if CONTROLLER_BOARD_TYPE == CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN
    switch (binding->cmd)
    {
    case COM_1_MK:
        binding->pin = COM_1_MK_PIN;
        break;
    case COM_2_MK:
        binding->pin = COM_2_MK_PIN;
        break;
    case COM_3_MK:
        binding->pin = COM_3_MK_PIN;
        break;
    case IP_MK_1:
        binding->pin = IP_MK_1_PIN;
        break;
    case IP_MK_2:
        binding->pin = IP_MK_2_PIN;
        break;
    case IP_MK_3:
        binding->pin = IP_MK_3_PIN;
        break;
    case IP_MK_4:
        binding->pin = IP_MK_4_PIN;
        break;
    case IP_MK_5:
        binding->pin = IP_MK_5_PIN;
        break;
    case IP_MK_6:
        binding->pin = IP_MK_6_PIN;
        break;
    case IP_MK_7:
        binding->pin = IP_MK_7_PIN;
        break;
    case IP_MK_8:
        binding->pin = IP_MK_8_PIN;
        break;
    case IP_MK_9:
        binding->pin = IP_MK_9_PIN;
        break;
    case IP_MK_10:
        binding->pin = IP_MK_10_PIN;
        break;
    default:
        binding->pin = NC;
        break;
    }
#endif
}

int8_t CommandMap::registerCommand(HwCmd_t cmd, InterruptIn *pin, mbed::Callback<void()> callbac, uint8_t mode)
{
    HwBinding binding;
    binding.cmd = cmd;
    binding.interruptIn = pin;

    binding.pinType = Interrupt;
    binding.callbac = callbac;
    registerPin(&binding);
    if (mode == FALLING)
        pin->fall(callbac); 
    else
        pin->rise(callbac); 
    
    // save bind in list
    hwBindings.push_back(binding);
    return CMD_MAP_OK;
}

int8_t CommandMap::read(PinName pin)
{
    for (auto &binding : hwBindings)
    {
        if (binding.pin != pin || binding.pin == NC)
            continue;

        switch (binding.pinType)
        {
        case In:
            return binding.digitalIn->read();
        case Interrupt:
            return binding.interruptIn->read();
        case Out:
            return binding.digitalOut->read();
        default:
            return CMD_MAP_ERROR;
        }
    }
    return CMD_MAP_ERROR;
}

int8_t CommandMap::write(PinName pin, int value_for_write)
{
    for (auto &binding : hwBindings)
    {
        if (binding.pin != pin || binding.pin == NC)
            continue;

        switch (binding.pinType)
        {
        case In:
            return CMD_MAP_ERROR;
        case Interrupt:
            return CMD_MAP_ERROR;
        case Out:
            binding.digitalOut->write(value_for_write);
            break;
        default:
            return CMD_MAP_ERROR;
        }
    }
    return CMD_MAP_OK;
}
int8_t CommandMap::writeAllOuts(int value_for_write)
{
    for (auto &binding : hwBindings)
    {
        if (binding.pinType == Out && binding.pin != NC)
        {
            binding.digitalOut->write(value_for_write);
        }
    }
    return CMD_MAP_OK;
}

int8_t CommandMap::replaceCommand(HwCmd_t cmd, HwCmd_t cmd_new)
{
    HwBinding *binding_for_cmd = nullptr;
    HwBinding *binding_for_cmd_new = nullptr;
    
    for (auto &binding : hwBindings)
    {
        if (binding.cmd == cmd)
            binding_for_cmd = &binding;
        else if (binding.cmd == cmd_new)
            binding_for_cmd_new = &binding;
    }

    if (!binding_for_cmd || !binding_for_cmd_new)
        return CMD_MAP_ERROR;

    if (binding_for_cmd->pinType != binding_for_cmd_new->pinType)
        return CMD_MAP_ERROR_PINTYPE;

    binding_for_cmd->cmd = cmd_new;
    binding_for_cmd_new->cmd = NOT_USED;
    return CMD_MAP_OK;
}
int8_t CommandMap::deleteCommand(HwCmd_t cmd)
{
    for (auto it = hwBindings.begin(); it != hwBindings.end(); it++)
    {
        if (it->cmd == cmd)
            it->cmd = NOT_USED;
    }
    return CMD_MAP_OK;
}
uint32_t CommandMap::get_size()
{
    return hwBindings.size();
}

int8_t CommandMap::getAllPins(char *data) // write all pins to data
{
    unsigned int offset = 0;

    offset += getAllInType(In, data + offset);
    // cout<<"i="<<i<<endl;
    offset += getAllInType(Out, data + offset);
    // cout<<"i="<<i<<endl;
    offset += getAllInType(Interrupt, data + offset);
    data[offset] = '\0';
    // cout<<"i="<<i<<endl;
    return CMD_MAP_OK;
}

uint16_t CommandMap::getAllInType(HwPinType type, char *data)
{
    std::string resultStr = "";
    switch (type)
    {
    case In:
        resultStr += "Ins: ";
        break;
    case Out:
        resultStr += "Outs: ";
        break;
    case Interrupt:
        resultStr += "Interrupts: ";
        break;
    default:
        resultStr += "|INVALID_TYPE|";
        break;
    }

    for (auto &binding : hwBindings)
    {
        if (binding.pinType != type)
        {
            continue;
        }
        switch (binding.cmd)
        {
        case NOT_USED:
            resultStr += "NOT_USED=";
            break;
        case COM_1_MK:
            resultStr += "COM_1_MK=";
            break;
        case COM_2_MK:
            resultStr += "COM_2_MK=";
            break;
        case COM_3_MK:
            resultStr += "COM_3_MK=";
            break;
        case COM_4_MK:
            resultStr += "COM_4_MK=";
            break;
        case COMMAND_1:
            resultStr += "COMMAND_1=";
            break;
        case COMMAND_2:
            resultStr += "COMMAND_2=";
            break;
        case COMMAND_3:
            resultStr += "COMMAND_3=";
            break;
        case COMMAND_4:
            resultStr += "COMMAND_4=";
            break;
        case COMMAND_5:
            resultStr += "COMMAND_5=";
            break;
        case COMMAND_6:
            resultStr += "COMMAND_6=";
            break;
        case COMMAND_7:
            resultStr += "COMMAND_7=";
            break;
        case COMMAND_8:
            resultStr += "COMMAND_8=";
            break;
        case IP_MK_1:
            resultStr += "IP_MK_1=";
            break;
        case IP_MK_2:
            resultStr += "IP_MK_2=";
            break;
        case IP_MK_3:
            resultStr += "IP_MK_3=";
            break;
        case IP_MK_4:
            resultStr += "IP_MK_4=";
            break;
        case IP_MK_5:
            resultStr += "IP_MK_5=";
            break;
        case IP_MK_6:
            resultStr += "IP_MK_6=";
            break;
        case IP_MK_7:
            resultStr += "IP_MK_7=";
            break;
        case IP_MK_8:
            resultStr += "IP_MK_8=";
            break;
        case IP_MK_9:
            resultStr += "IP_MK_9=";
            break;
        case IP_MK_10:
            resultStr += "IP_MK_10=";
            break;
        default:
            resultStr += "|INVALID_CMD|";
            break;
        }
        addPinNameToStr(binding.pin, &resultStr);
    }
    resultStr += '\n';
    resultStr.copy(data, resultStr.size());

    return resultStr.size();
}

int8_t CommandMap::addPinNameToStr(PinName pin, string *str)
{
    switch (pin)
    {
        // For SH:
    case PD_12:
        *str += "PD_12";
        break;
    case PD_13:
        *str += "PD_13";
        break;
    case PC_13:
        *str += "PC_13";
        break;
    case PG_0:
        *str += "PG_0";
        break;
    case PD_14:
        *str += "PD_14";
        break;
    case PD_15:
        *str += "PD_15";
        break;
    case PD_10:
        *str += "PD_10";
        break;
    case PG_8:
        *str += "PG_8";
        break;
    case PG_5:
        *str += "PG_5";
        break;
    case PG_6:
        *str += "PG_6";
        break;
    case PG_9:
        *str += "PG_9";
        break;
    case PG_12:
        *str += "PG_12";
        break;
    case PE_10:
        *str += "PE_10";
        break;
    case PE_11:
        *str += "PE_11";
        break;
    case PE_12:
        *str += "PE_12";
        break;
    case PE_13:
        *str += "PE_13";
        break;
    case PF_0:
        *str += "PF_0";
        break;
    case PF_1:
        *str += "PF_1";
        break;
    case PG_2:
        *str += "PG_2";
        break;
    case PG_3:
        *str += "PG_3";
        break;
    case PG_14:
        *str += "PG_14";
        break;
    case PG_15:
        *str += "PG_15";
        break;
        // for SM:
    case PC_12:
        *str += "PC_12";
        break;
    case PD_2:
        *str += "PD_2";
        break;
    case PD_3:
        *str += "PD_3";
        break;
    case PC_8:
        *str += "PC_8";
        break;
    case PC_9:
        *str += "PC_9";
        break;
    case PG_7:
        *str += "PG_7";
        break;
    case PE_14:
        *str += "PE_14";
        break;
    case PE_15:
        *str += "PE_15";
        break;
    default:
        *str += "NOT FOUND";
        break;
    }
    *str += " |"; // terminator
    return CMD_MAP_OK;
}
