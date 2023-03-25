#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

bool I2C_Write(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buffer, uint8_t sizebuf);
bool I2C_Read(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buffer, uint8_t sizebuf);


#endif /* INC_I2C_H_ */
