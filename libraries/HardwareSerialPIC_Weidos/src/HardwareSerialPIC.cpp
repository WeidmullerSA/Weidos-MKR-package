#include "HardwareSerialPIC.h"

#ifdef HAVE_PIC

#include <Wire.h>

#define FIFO_SIZE					400

#define FIFO_RX_REGISTER			0x00
#define FIFO_TX_REGISTER			0x00
#define FIFO_TX_AVAILABLE_REGISTER	0x01
#define FIFO_RX_PENDING_REGISTER	0x02
#define RESET_REGISTER				0x7b

////////////////////////////////////////////////////////////////////////////////////////////////////
HardwareSerialPIC::HardwareSerialPIC(uint8_t i2cAddr) : i2cAddr(i2cAddr) {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::begin(unsigned long baud) {
	begin(baud, SERIAL_8N1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::begin(unsigned long baud, uint16_t config) {
	Wire.begin();

	reset();

	delay(100);

	// Set baudrate
	setBaudrate(baud);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::end() {
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::reset(){
	Wire.beginTransmission(i2cAddr);
	Wire.write(RESET_REGISTER);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::setBaudrate(unsigned long baud) {
	Wire.beginTransmission(i2cAddr);
	Wire.write(baud);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::write(uint8_t value) {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_TX_REGISTER);
	Wire.write(value);
	if (Wire.endTransmission()) {
		return 0;
	}
	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::write(const uint8_t *buffer, size_t size) {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_TX_REGISTER);
	size_t pending = size;
	while (pending--) {
		Wire.write(*buffer++);
	}
	if (Wire.endTransmission()) {
		return 0;
	}
	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::available() {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_RX_PENDING_REGISTER);
	if (Wire.endTransmission()) {
		return 0;
	}

	Wire.requestFrom(i2cAddr, 2);
	if (Wire.available() != 2) {
		return 0;
	}

	uint16_t ret = Wire.read();
	ret |= Wire.read() << 8;

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::availableForWrite() {
	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_TX_AVAILABLE_REGISTER);
	if (Wire.endTransmission()) {
		return 0;
	}

	Wire.requestFrom(i2cAddr, 2);
	if (Wire.available() != 2) {
		return 0;
	}

	uint16_t ret = Wire.read();
	ret |= Wire.read() << 8;

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::read() {
	if(!available()) return -1;

	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_RX_REGISTER);
	if (Wire.endTransmission()) {
		return -1;
	}

	Wire.requestFrom(i2cAddr, 1);
	if (Wire.available() != 1) {
		return -1;
	}

	return Wire.read();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t HardwareSerialPIC::read(uint8_t* buff, size_t size) {
	if(!available()) return -1;

	Wire.beginTransmission(i2cAddr);
	Wire.write(FIFO_RX_REGISTER);
	if (Wire.endTransmission()) {
		return -1;
	}

	Wire.requestFrom(i2cAddr, size);
	if (Wire.available() != size) {
		return -1;
	}

	size_t pending = size;
	while (pending--) {
		*buff++ = Wire.read();
	}
	return size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int HardwareSerialPIC::peek() {
	// TODO
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HardwareSerialPIC::flush() {
	while (availableForWrite() < FIFO_SIZE) {
		delay(1);
	}
}


HardwareSerialPIC SerialPIC(PIC_I2C_ADDRESS);

#endif		// HAVE_PIC
