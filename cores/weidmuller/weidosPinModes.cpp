#include "Arduino.h"
#include "weidosPinModes.h"


void weidos_initDefaultIOPins(){

    //Digital inputs
    pinMode(pin25, INPUT);	//DI_4
	pinMode(pin26, INPUT);	//DI_5
	pinMode(pin27, INPUT);	//DI_6
	pinMode(pin28, INPUT);	//DI_7
	
	//Digital outputs
	digitalWrite(pin55, LOW);
    digitalWrite(pin56, LOW);
    digitalWrite(pin57, LOW);
    digitalWrite(pin58, LOW);
	pinMode(pin55, OUTPUT); //DO0
	pinMode(pin56, OUTPUT); //DO1
	pinMode(pin57, OUTPUT); //DO2
	pinMode(pin58, OUTPUT); //DO3

	//Analog  inputs (Can also be used as digital inputs)
	pinMode(pin15, INPUT);	//ADI_0
	pinMode(pin16, INPUT);	//ADI_1
	pinMode(pin17, INPUT);	//ADI_2
	pinMode(pin18, INPUT);	//ADI_3
}
