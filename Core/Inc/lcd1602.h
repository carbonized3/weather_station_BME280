
#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#include "main.h"

//---------------------------------------------------------------------------------------------------

#define d4_set() HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_SET)
#define d5_set() HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_SET)
#define d6_set() HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_SET)
#define d7_set() HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET)
#define d4_reset() HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, GPIO_PIN_RESET)
#define d5_reset() HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, GPIO_PIN_RESET)
#define d6_reset() HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, GPIO_PIN_RESET)
#define d7_reset() HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET)

#define e1          HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET) // установка линии E в 1
#define e0    		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET) // установка линии E в 0
#define rs1   		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET) // установка линии RS в 1 (данные)
#define rs0   		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET) // установка линии RS в 0 (команда)

//-----------------------------------Digit to char---------------------------------------------

#define _MINUS	  45
#define char_0	  48
#define char_1	  49
#define char_2	  50
#define char_3	  51
#define char_4	  52
#define char_5	  53
#define char_6	  54
#define char_7	  55
#define char_8	  56
#define char_9	  57




//---------------------------------------------------------------------------------------------------

void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_SendString(const char *str);
void LCD_SetPos(uint8_t x, uint8_t y);
void LCD_SendIntDigit(int digit);

#endif /* INC_LCD1602_H_ */
