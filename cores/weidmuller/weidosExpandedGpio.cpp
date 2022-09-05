#include "Arduino.h"
#include "weidosExpandedGpio.h"
#include "weidos_mcp23008.h"

#define expandedPinToDeviceIndex(p) (p & 0xff)
#define expandedPinToDeviceAddress(x) (x>>8)
#define isExpandedPin(p) (p > 0xff)


void initExpandedGpio(){
    #ifdef HAVE_MCP23008
    mcp23008.begin();
    #endif
    return;
}


extern "C"{
    void _digitalWrite( pin_size_t ulPin, PinStatus ulVal);
    void _pinMode( pin_size_t ulPin, PinMode ulMode);
}


void pinMode( pin_size_t ulPin, PinMode ulMode)
{
  // Handle the case the pin isn't usable as PIO
    if(!isExpandedPin(ulPin)){
        _pinMode(ulPin, ulMode);
        return;
    }

    #ifdef HAVE_MCP23008
    mcp23008.setAddress(expandedPinToDeviceAddress(ulPin));
    mcp23008.pinMode(expandedPinToDeviceIndex(ulPin), ulMode);
    #endif
    return;
}
    

void digitalWrite( pin_size_t ulPin, PinStatus ulVal)
{
    if(!isExpandedPin(ulPin)){
        _digitalWrite(ulPin, ulVal);
        return;
    }
    #ifdef HAVE_MCP23008
    mcp23008.setAddress(expandedPinToDeviceAddress(ulPin));
    mcp23008.digitalWrite(expandedPinToDeviceIndex(ulPin), ulVal);
    #endif
    return;
}
