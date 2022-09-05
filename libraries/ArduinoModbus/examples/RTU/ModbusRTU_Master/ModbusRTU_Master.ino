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
  Modbus RTU Master example

  This example shows how to set up a Modbus RTU Master device
  to communicate with a Modbus RTU Slave to request data from
  input registers.
*/


#include <ArduinoRS485.h>
#include <ModbusRTUClient.h>

#define NUM_REGISTERS   10      //Number of consecutive registers to read.
#define FIRST_REGISTER  1000    //First register's address.
#define SLAVE_ADDRESS   1       //Modbus Slave address to request data from.
#define BAUDRATE        19200   //Baudrate

void setup() {
  Serial.begin(115200);
  while(!Serial){}
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);
  if(!ModbusRTUClient.begin(BAUDRATE, SERIAL_8E1)){  //Modbus client configured as 8 data bits, Even parity and 1 stop bit (SERIAL_8E1).
    Serial.println("Client not initialized!");    
  }
  else Serial.println("Client successfully initialized");
}

void loop() {
  delay(5000);
  ModbusRTUClient.requestFrom(SLAVE_ADDRESS, INPUT_REGISTERS, FIRST_REGISTER, NUM_REGISTERS);
  for(int i = 0; i<NUM_REGISTERS; i++){
    long data = ModbusRTUClient.read();
    Serial.println(data);
  }
}
