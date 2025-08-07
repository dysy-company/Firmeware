#include "GlobalVariablesInterface.h"

GlobalVariablesInterface::GlobalVariablesInterface(globalVariables_t *GV, InternalFlash *internalFlash, InternalFlashDMA *internalFlashDMA){
    this->_globalVariables = GV;
    this->_internalFlash = internalFlash;
    this->_internalFlashDMA = internalFlashDMA;
}
GlobalVariablesInterface::~GlobalVariablesInterface(){

}

template <> std::string GlobalVariablesInterface::readValue<std::string>(uint32_t index, memoryType_t memoryType){
    int size = (uint32_t)FLASH_STRING_AREA_SIZE; //default
    return this->readValue<std::string>(index, memoryType, size);
}

template <> std::string GlobalVariablesInterface::readValue<std::string>(uint32_t index, memoryType_t memoryType, int &size){
    switch (index)
    {
    case GLOBAL_VARIABLES_IP_ADDRESS:
        size = (uint32_t)FLASH_IP_PARAMS_AREA_SIZE;
        return this->readValueImplementation<std::string>(this->_globalVariables->ipAddress, IP_ADDRESS_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_NET_MASK:
        size = (uint32_t)FLASH_IP_PARAMS_AREA_SIZE;
        return this->readValueImplementation<std::string>(this->_globalVariables->netMask, NET_MASK_FLASH_OFFSET, memoryType, size);
        break;
    case GLOBAL_VARIABLES_GATEWAY:
        size = (uint32_t)FLASH_IP_PARAMS_AREA_SIZE;
        return this->readValueImplementation<std::string>(this->_globalVariables->gateway, GATEWAY_FLASH_OFFSET, memoryType, size);
        break;
    default:
        size = (uint32_t)FLASH_IP_PARAMS_AREA_SIZE;
        return this->readValueImplementation<std::string>(this->_globalVariables->ipAddress, IP_ADDRESS_FLASH_OFFSET, memoryType, size);
        break;
    }
}

template <> std::string GlobalVariablesInterface::readValueImplementation<std::string>(std::string &gvValue, uint32_t flashOffset, memoryType_t memoryType, int &size){
    std::string value = "Bim Bim Bam Bam";
    switch (memoryType){
        case RAM_MEMORY_TYPE:
            value = gvValue;
            break;
        case FLASH_MEMORY_TYPE:
            switch (this->_globalVariables->flashOperationType){
                case FLASH_OPERATION_CPU:
                    this->_internalFlash->readInOneSector<std::string>(value, flashOffset);
                    break;
                case FLASH_OPERATION_DMA:
                    this->_internalFlashDMA->readFromFlash(value, flashOffset, size);
                    break;
                default:
                    break;
            }
            break;
        default:
            value = gvValue;
            break;
    }
    size = value.size();
    if(size > (uint32_t)FLASH_IP_PARAMS_AREA_SIZE){
        value = value.substr(0, (uint32_t)FLASH_IP_PARAMS_AREA_SIZE);
        size = (uint32_t)FLASH_IP_PARAMS_AREA_SIZE;
    }
    return value;
}

template <> int GlobalVariablesInterface::readValueAnyType<std::string>(uint32_t index, char *buffer, memoryType_t memoryType){
    int size = 0;
    std::string value;
    value = this->readValue<std::string>(index, memoryType, size);
    basic.writeValueToBytesBuffer(buffer, value, 0);
    return size;
}

template std::string GlobalVariablesInterface::readValue<std::string>(uint32_t, memoryType_t);
template std::string GlobalVariablesInterface::readValue<std::string>(uint32_t, memoryType_t, int &);
template std::string GlobalVariablesInterface::readValueImplementation<std::string>(std::string &, uint32_t, memoryType_t, int &);
template int GlobalVariablesInterface::readValueAnyType<std::string>(uint32_t, char *, memoryType_t);

template <> void GlobalVariablesInterface::writeValue<std::string>(uint32_t index, std::string value, memoryType_t memoryType){
    switch (index)
    {
    case GLOBAL_VARIABLES_IP_ADDRESS:
        this->writeValueImplementation<std::string>(this->_globalVariables->ipAddress, IP_ADDRESS_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_NET_MASK:
        this->writeValueImplementation<std::string>(this->_globalVariables->netMask, NET_MASK_FLASH_OFFSET, value, memoryType);
        break;
    case GLOBAL_VARIABLES_GATEWAY:
        this->writeValueImplementation<std::string>(this->_globalVariables->gateway, GATEWAY_FLASH_OFFSET, value, memoryType);
        break;
    default:
        break;
    }
}

template <> void GlobalVariablesInterface::writeValueImplementation<std::string>(std::string &gvValue, uint32_t flashOffset, std::string value, memoryType_t memoryType){
    switch (memoryType)
    {
        case RAM_MEMORY_TYPE:
            gvValue = value;
            break;
        case FLASH_MEMORY_TYPE:{
            switch (this->_globalVariables->flashOperationType)
            {
            case FLASH_OPERATION_CPU:
                this->_internalFlash->Writing_To_Flash_Through_Buf_Sector<std::string>(value, flashOffset);
                break;
            case FLASH_OPERATION_DMA:
                this->_internalFlashDMA->setParams<std::string>(value, flashOffset);
                break;
            default:
                break;
            }
            break;
        }
        case FLASH_MEMORY_QUEUE:{
            this->_internalFlashDMA->setParamsForQueue<std::string>(value, flashOffset);
            break;
        }
        case FLASH_MEMORY_SET:{
            this->_internalFlashDMA->writeToFlashViaQueue();
            break;
        }
        default:
            break;
    }
}

template <> void GlobalVariablesInterface::writeValueAnyType<std::string>(uint32_t index, char *buffer, memoryType_t memoryType, std::string value){
    basic.writeBytesBufferToValue(buffer, &value);
    this->writeValue<std::string>(index, value, memoryType);
}

template void GlobalVariablesInterface::writeValue<std::string>(uint32_t, std::string, memoryType_t);
template void GlobalVariablesInterface::writeValueImplementation<std::string>(std::string &, uint32_t, std::string, memoryType_t);
template void GlobalVariablesInterface::writeValueAnyType<std::string>(uint32_t, char *, memoryType_t, std::string);

void GlobalVariablesInterface::writeValue(uint32_t index, char *buffer, memoryType_t memoryType){
    switch(index){
        case GLOBAL_VARIABLES_POSITION_AXIS_MODE ... GLOBAL_VARIABLES_VALVE_DIRECTION_MODE:{
            int value = 0x0;
            this->writeValueAnyType<int>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA ... GLOBAL_VARIABLES_ENCODER_STEP_VALUE:{
            double value = 0.0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE:{
            int value = 0x0;
            this->writeValueAnyType<int>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MOTOR_STEP_VALUE:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1 ... GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY:{
            int value = 0x0;
            this->writeValueAnyType<int>(index, buffer, memoryType, value);
            break;
        }
		case GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE:{
    		double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK ... GLOBAL_VARIABLES_SSI_NULL_OFFSET:{
            float value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_PWM_FREQ:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
		case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP ... GLOBAL_VARIABLES_CONST_STRAIN_PID_KD:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_SERIAL_NUMBER ... GLOBAL_VARIABLES_ID:{
            uint64_t value = 0x0;
            this->writeValueAnyType<uint64_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION:{
            uint16_t value = 0x0;
            this->writeValueAnyType<uint16_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MACHINE_TYPE:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MAX_DISPLACEMENT ... GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MAX_STRAIN ... GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MAX_DEFORMATION ... GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT ... GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV ... GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA ... GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP ... GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP:{
            uint64_t value = 0x0;
            this->writeValueAnyType<uint64_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_T_CYCLE_TIME:{
            us_timestamp_t value = 0x0;
            this->writeValueAnyType<us_timestamp_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ ... GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1 ... GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE ... GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE:{
            float value = 0.0;
            this->writeValueAnyType<float>(index, buffer, memoryType, value);
            break;
		}
        case GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT ... GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT:{
            double value = 0x0;
            this->writeValueAnyTypeCast<double, float>(index, buffer, memoryType, value);
            break;
        }
		case GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL ... GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR ... GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST:{
            double value = 0x0;
            this->writeValueAnyTypeCast<double, float>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING:{
            uint64_t value = 0x0;
            this->writeValueAnyTypeCast<uint64_t, us_timestamp_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA ... GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA:{
            double value = 0x0;
            this->writeValueAnyTypeCast<double, float>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_CALIBRATION_NOTES ... GLOBAL_VARIABLES_DEFORMATION_3CH_CALIBRATION_NOTES:{
            uint8_t value = 0x0;
            this->writeValueAnyType<uint8_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MAX_POSITION ... GLOBAL_VARIABLES_POSITION_DIVIDER:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_VALVE_INVERT_AXIS:{
            int value = 0x0;
            this->writeValueAnyType<int>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_IP_ADDRESS ... GLOBAL_VARIABLES_GATEWAY:{
            std::string value = "Bim Bim Bam Bam";
            this->writeValueAnyType<std::string>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_PORT:{
            uint16_t value = 0x0;
            this->writeValueAnyType<uint16_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC:{
            int value = 0x0;
            this->writeValueAnyType<int>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP ... GLOBAL_VARIABLES_AMPLITUDE_PRECISION:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT:{
            double value = 0x0;
            this->writeValueAnyTypeCast<double, float>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION ... GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START ... GLOBAL_VARIABLES_MULTIPLIER_DEFAULT:{
            double value = 0x0;
            this->writeValueAnyType<double>(index, buffer, memoryType, value);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_UNITS:{
            uint32_t value = 0x0;
            this->writeValueAnyType<uint32_t>(index, buffer, memoryType, value);
            break;
        }
        default:
            break;
    }
}
int GlobalVariablesInterface::readValue(uint32_t index, char *buffer, memoryType_t memoryType){
    int size = 0;
    switch(index){
        case GLOBAL_VARIABLES_POSITION_AXIS_MODE ... GLOBAL_VARIABLES_VALVE_DIRECTION_MODE:{
            //int value = 0x0;
            size = this->readValueAnyType<int>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_PISTON_PARAMS_TOP_AREA ... GLOBAL_VARIABLES_ENCODER_STEP_VALUE:{
            //double value = 0.0;
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MOTOR_DRIVE_TYPE:{
            //int value = 0x0;
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_CONTOLLER_ONLINE_MODE:{
            //int value = 0x0;
            size = this->readValueAnyType<int>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MOTOR_STEP_VALUE:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_LIMITSWITCH_POLARITY_1 ... GLOBAL_VARIABLES_EMERGENCYSTOP_POLARITY:{
            //int value = 0x0;
            size = this->readValueAnyType<int>(index, buffer, memoryType);
            break;
        }
		case GLOBAL_VARIABLES_DEFORMATION_ENCODER_STEP_VALUE:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DISPLACEMENT_OVERRUN_STEP_BACK ... GLOBAL_VARIABLES_SSI_NULL_OFFSET:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_PWM_FREQ:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
		case GLOBAL_VARIABLES_SIN_DISPLACEMENT_PID_KP ... GLOBAL_VARIABLES_CONST_STRAIN_PID_KD:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_SERIAL_NUMBER ... GLOBAL_VARIABLES_ID:{
            size = this->readValueAnyType<uint64_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MACHINE_TYPE:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_VERSION:{
            size = this->readValueAnyType<uint16_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DISPLACEMENT_SENSOR_TYPE:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MAX_DISPLACEMENT ... GLOBAL_VARIABLES_MIN_DISPLACEMENT_OVERLOAD_PERCENT:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_SENSOR_TYPE:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MAX_STRAIN ... GLOBAL_VARIABLES_MIN_STRAIN_OVERLOAD_PERCENT:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MAX_DEFORMATION ... GLOBAL_VARIABLES_MIN_DEFORMATION_OVERLOAD_PERCENT:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_VOLT ... GLOBAL_VARIABLES_SIN_VOLTAGE_MODE_MAX_VOLT:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_MAX_DEV ... GLOBAL_VARIABLES_CONST_DISPLACEMENT_MODE_DELTA:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_CONST_STRAIN_MODE_DELTA ... GLOBAL_VARIABLES_CONST_DEFORMATION_MODE_DELTA:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_SIN_DISPLASEMENT_MODE_MAX_STEP ... GLOBAL_VARIABLES_CONST_STRAIN_MODE_MAX_STEP:{
            size = this->readValueAnyType<uint64_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_T_CYCLE_TIME:{
            size = this->readValueAnyType<us_timestamp_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_CONST_MODE_MODE_FREQ ... GLOBAL_VARIABLES_SIN_BASED_DEFORM_AMPL_TUNE_DOWN_KD:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_SENSOR_TYPE_CH1 ... GLOBAL_VARIABLES_ACTIVE_DEFORMATION_CHANNELS:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_REFERENCE_VOLTAGE ... GLOBAL_VARIABLES_DEFORMATION_REFERENCE_VOLTAGE:{
            size = this->readValueAnyType<float>(index, buffer, memoryType);
			break;
		}
        case GLOBAL_VARIABLES_SSI_SENSOR_RESOLUTION:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_BUTTON_LOWER_LIMIT ... GLOBAL_VARIABLES_STRAIN_BUTTON_UPPER_LIMIT:{
            size = this->readValueAnyTypeCast<float, double>(index, buffer, memoryType);
            break;
        }
		case GLOBAL_VARIABLES_ENABLE_ACTIVE_LEVEL ... GLOBAL_VARIABLES_CCWL_ACTIVE_LEVEL:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_REGULAR ... GLOBAL_VARIABLES_DISPL_SPEED_BY_BUTTON_FAST:{
            size = this->readValueAnyTypeCast<float, double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_TCYCLE_FOR_FLASH_WRITING:{
            size = this->readValueAnyTypeCast<us_timestamp_t, uint64_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_CYCLIC_DELTA ... GLOBAL_VARIABLES_DEFORMATION_CYCLIC_DELTA:{
            size = this->readValueAnyTypeCast<float, double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STRAIN_CALIBRATION_NOTES ... GLOBAL_VARIABLES_DEFORMATION_3CH_CALIBRATION_NOTES:{
            size = this->readValueAnyType<uint8_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_MAX_POSITION ... GLOBAL_VARIABLES_POSITION_DIVIDER:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_VALVE_INVERT_AXIS:{
            size = this->readValueAnyType<int>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_IP_ADDRESS ... GLOBAL_VARIABLES_GATEWAY:{
            size = this->readValueAnyType<std::string>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_PORT:{
            size = this->readValueAnyType<uint16_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_ETHERNET_PROTOCOL_CONNECTION_TIMEOUT_STOP_TEST:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
			break;
        }
        case GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS_MAIN_PROC:{
            size = this->readValueAnyType<int>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_START_STOP_AMPLITUDE_RATIO_STOP ... GLOBAL_VARIABLES_AMPLITUDE_PRECISION:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_TRESHOLD_FOR_NULLPOINT_DELTA_ACCEPT:{
            size = this->readValueAnyTypeCast<float, double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_STEP_FOR_NULLPOINT_GET_CORRECTION ... GLOBAL_VARIABLES_MIN_MAX_CALCULATING_COUNTS:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_ANCHOR_SIN_FREQUENCY_START ... GLOBAL_VARIABLES_MULTIPLIER_DEFAULT:{
            size = this->readValueAnyType<double>(index, buffer, memoryType);
            break;
        }
        case GLOBAL_VARIABLES_DEFORMATION_UNITS:{
            size = this->readValueAnyType<uint32_t>(index, buffer, memoryType);
            break;
        }
        default:
            break;
    }
    return size; 
}
