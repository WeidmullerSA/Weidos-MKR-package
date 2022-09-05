/**
Copyright (C) 2021 Weidmüller SA. All rights reserved.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


/*
  Modbus RTU Slave example

  Example that shows how to set up a Modbus RTU Slave with Coils,
  Discrete Inputs, Holding and Input Registers.

  Slave is configured with the following:
   - Coils: 5 consecutive coils starting at address 700.
   - Discrete Inputs: 5 consecutive discrete inputs starting at address 800.
   - Holding Registers: 2 consecutive holding registers starting at address 900.
   - Input Registers: 10 consecutive input registers starting at address 1000.


  Values stored in the Modbus RTU Slave are known and can be checked
  by requesting its data with a Modbus RTU Master properlly configured.
  
 */
 
#include <ModbusRTUServer.h>


uint16_t inputRegisterValues[] = {1000, 1020, 4020, 325, 0, 0, 0, 0, 0, 0}; 
uint8_t discreteInputValues[] = {1,7,111,243,0}; 
const unsigned long baudrate = 19200; 
const int slaveAddress = 1;


void setup() {
  ModbusRTUServer.begin(RS485, slaveAddress, baudrate, SERIAL_8E1);
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);
  RS485.setDelays(70, 70);
  RS485.setTimeout(100);

  ModbusRTUServer.configureCoils(700, 5);                             //Create 5 coils with address starting at 700.
  ModbusRTUServer.coilWrite(700, 0b00000101);                         //Set value for coil with address 700.                      
  ModbusRTUServer.coilWrite(701, 0b00000010);                         //Set value for coil with address 701. 
  ModbusRTUServer.coilWrite(702, 0b00000000);                         //Set value for coil with address 702.
  ModbusRTUServer.coilWrite(703, 0b00000001);                         //Set value for coil with address 703.
  ModbusRTUServer.coilWrite(704, 0b00111100);                         //Set value for coil with address 704.
 
  ModbusRTUServer.configureDiscreteInputs(800, 5);                    //Create 5 discrete inputs with address starting at 800.
  ModbusRTUServer.writeDiscreteInputs(800, discreteInputValues, 5);   //Alternatively one can use discreteInputWrite() to set discrete inputs one by one.

  ModbusRTUServer.configureHoldingRegisters(900, 2);                  //Create 2 holding registers with address starting at 900.
  ModbusRTUServer.holdingRegisterWrite(900, 121);
  ModbusRTUServer.holdingRegisterWrite(901, 134);

  ModbusRTUServer.configureInputRegisters(1000, 10);                    //Create 10 input registers with address starting at 1000.
  ModbusRTUServer.writeInputRegisters(1000, inputRegisterValues, 10);   //Alternatively one can use inputRegisterWrite() to set input registers one by one. 
}


void loop() {
  ModbusRTUServer.poll();
}
