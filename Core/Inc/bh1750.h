#ifndef INC_BH1750_H_
#define INC_BH1750_H_

#include "main.h"
#include "i2c.h"

//---------------------------------------------BH1750-----------------------------------------------------------
#define BH1750_ADDRESS		0x23 	// (0b00100011)

#define SLAW_ADDRLOW 0b01000110		// Ёто отправл¤ем как SLAW в случае если ножка ADD подт¤нута к «емле
#define SLAR_ADDRLOW 0b01000111		// Ёто отправл¤ем как SLAR. ќтличаетс¤ от SLAW единичкой в мл. разр¤де
#define SLAW_ADDRHIGH 0b10111000	// Ёто отправл¤ем как SLAW в случае если ножка ADD подт¤нута к 3.3 ¬
#define SLAR_ADDRHIGH 0b10111001	// Ёто отправл¤ем как SLAR. ќтличаетс¤ от SLAW единичкой в мл. разр¤де
#define POWER_DOWN 0
#define POWER_ON 0x01
#define RESET 0x07
#define Continuously_HResolution_Mode 0x10	 // Start measurement at 1lx resolution.
#define Continuously_HResolution_Mode_2 0x11 // Start measurement at 0.5lx resolution.
#define Continuously_LResolution_Mode 0x13   // Start measurement at 4lx resolution
#define OneTime_HResolution_Mode 0x20		 // Start measurement at 1lx resolution.
#define OneTime_HResolution_Mode_2 0x21		 // Start measurement at 0.5lx resolution.
#define OneTime_LResolution_Mode 0x23		 // Start measurement at 4lx resolution.

#define ACK 1
#define NACK 0

#define I2C_TIMEOUT                                              1000

//--------------------------------------------ѕ–ќ“ќ“»ѕџ ‘”Ќ ÷»…------------------------------------
void BH1750_init();
unsigned int BH1750_ReadLux();

#endif /* INC_BH1750_H_ */
