#include "Arduino.h"
#include "weidosPinModes.h"


void weidos_initDefaultIOPins(){
	
	//Digital outputs
	digitalWrite(pin55, LOW);
    digitalWrite(pin56, LOW);
    digitalWrite(pin57, LOW);
    digitalWrite(pin58, LOW);
	pinMode(pin55, OUTPUT); //DO0
	pinMode(pin56, OUTPUT); //DO1
	pinMode(pin57, OUTPUT); //DO2
	pinMode(pin58, OUTPUT); //DO3
}