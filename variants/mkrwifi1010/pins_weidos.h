#ifndef PINS_WEIDOS_H
#define PINS_WEIDOS_H

//####Weidmuller####
//Digital inputs
#define DI_4 (25u)
#define DI_5 (1u)
#define DI_6 (2u)
#define DI_7 (3u)
static const uint32_t pin25 = DI_4;
static const uint32_t pin26 = DI_5;
static const uint32_t pin27 = DI_6;
static const uint32_t pin28 = DI_7;

//Digital outputs
#define DO_0 (0x2100)
#define DO_1 (0x2101)
#define DO_2 (0x2102)
#define DO_3 (0x2103)
static const uint32_t pin55 = DO_0;
static const uint32_t pin56 = DO_1;
static const uint32_t pin57 = DO_2;
static const uint32_t pin58 = DO_3;

//Analog/Digital inputs
#define ADI_0 (17u)
#define ADI_1 (16u)
#define ADI_2 (20u)
#define ADI_3 (21u)
static const uint32_t pin15 = ADI_0;
static const uint32_t pin16 = ADI_1;
static const uint32_t pin17 = ADI_2;
static const uint32_t pin18 = ADI_3;

//Analog output
#define AO_0 (15u)
static const uint32_t pin45 = AO_0;

#define HAVE_MCP23008

#define ETHERNET_CS (6u)            //Ethernet slave select/chip select

#define RS485_TX 14
#define RS485_DE 5
#define RS485_RE 5

//####Weidmuller####
#endif

