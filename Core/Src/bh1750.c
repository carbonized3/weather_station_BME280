#include "bh1750.h"

static uint8_t buffer[2];

unsigned int BH1750_ReadLux()
{
	unsigned int BH_H,BH_L;
	buffer[0] = OneTime_HResolution_Mode;

	I2C_Write(hi2c2, BH1750_ADDRESS, buffer, 1);
	I2C_Read(hi2c2, BH1750_ADDRESS, buffer, sizeof(buffer));

	BH_H = buffer[0];
	BH_L = buffer[1];
	BH_H <<= 8;
	BH_H |= BH_L;
	return ((BH_H/1.2));				// Эту величину(в люксах) остается только вывести куда-либо
}
