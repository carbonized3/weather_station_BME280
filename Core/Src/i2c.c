#include "i2c.h"

static char str[13];

bool I2C_Write(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buffer, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Transmit(&hi, (uint16_t)(DEV_ADDR<<1), buffer, (uint16_t)sizebuf, (uint32_t)1000)!= HAL_OK)
	{
		/*	Не забываем свдинуть адрес на 1 влево, т.к HAL сам по себе добавляет бит в конец или нет в зависимости от
			 	 	 	 * чтения или наоборот записи в слэйв устройство	*/
		if (HAL_I2C_GetError(&hi) != HAL_I2C_ERROR_AF)
		{
			return false;
        }
	}
}

bool I2C_Read(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buffer, uint8_t sizebuf)
{
	while(HAL_I2C_Master_Receive(&hi, (uint16_t)(DEV_ADDR<<1), buffer, (uint16_t)sizebuf, (uint32_t)1000)!= HAL_OK)
	{
		if (HAL_I2C_GetError(&hi) != HAL_I2C_ERROR_AF)
		{
			return false;
        }
	}
}
