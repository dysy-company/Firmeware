#ifndef PIN_CONFIGURATOR_H
#define PIN_CONFIGURATOR_H

#include <mbed.h>

typedef uint32_t pinType_t;

typedef struct{
    pinType_t   pinType;
    PinName     pinName;
} pinConfig_t;

class PinConfigurator{
    public:
        PinConfigurator();
        ~PinConfigurator();
        PinName getPinName(pinType_t pinType);
        pinType_t getPinType(PinName pinName);
        void addPinConfig(pinConfig_t pinConfig);
        void clearPinConfigList();
    private:

};

#endif