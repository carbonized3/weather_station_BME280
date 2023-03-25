#include "lcd1602.h"


static void delay(void)
{
     uint16_t i;
     for(i=0;i<1000;i++)
	 {
	 }
}
static void LCD_WriteData(uint8_t data)
{
	if(((data>>3) & 0x01) == 1) d7_set();	else d7_reset();
	if(((data>>2) & 0x01) == 1) d6_set();	else d6_reset();
	if(((data>>1) & 0x01) == 1) d5_set();	else d5_reset();
	if((data & 0x01) == 1) 		d4_set();	else d4_reset();
	/*
	 	 Здесь мы проверяем на биты, 0 или 1. Двигаем сначала самый старший на место самого младшего и делаем лг. И
	 	 с единицой. Если в том разряде 1 то пишем лог.1 в соответсвующий пин, если нет, то пишем ноль
	 */
}
static void LCD_Data(uint8_t dt)
{
    rs1;
    LCD_WriteData(dt>>4);	// Младшая тетрада
    e1;
    delay();
    e0;
    LCD_WriteData(dt);		// Затем старшая
    e1;
    delay();
    e0;
}

static void LCD_Command(uint8_t dt)
{
    rs0;
    LCD_WriteData(dt>>4);
    e1;
    delay();
    e0;
    LCD_WriteData(dt);
    e1;
    delay();
    e0;
}
static uint8_t LCD_convertDigitToChar(uint8_t i) {
	switch(i) {
		case 0: return char_0;
		break;
		case 1: return char_1;
		break;
		case 2: return char_2;
		break;
		case 3: return char_3;
		break;
		case 4: return char_4;
		break;
		case 5: return char_5;
		break;
		case 6: return char_6;
		break;
		case 7: return char_7;
		break;
		case 8: return char_8;
		break;
		case 9: return char_9;
		break;
		default: return char_0;
	}
}
void LCD_SendIntDigit(int digit)
{
	int buf = digit;	// буффер
	uint8_t str[16] = {};	// Строка, которая у нас получится с числом, проинициализирована нулями
	int k = 0;

	if(digit > 0)		// Если число положительное
	{
		for (int8_t i = 15; i >= 0; i--)
		{
				if(buf > 0)				// Как только разделим последнюю цифру сюда уже не войдём
				{
					str[i] = buf % 10;	// Записываем с конца по-тихоньку число
					buf /= 10;			// Делим на 10, дробная часть будет отбрасываться
					continue;			// Пропускаем break
				}
				break;					// Если записали все число
		}
		for (uint8_t i = 0; i < 16; i++)			// Все работает!!
		{
			if(str[i] == 0 && k == 0) continue;
			/*
				Как только появится первое число в массиве, подлежащее записи, то мы попадём в ветку else,
				и k уже больше не будет равен нулю, поэтому это можно считатать признаком начала числа
				и использовать в условии пропуска, т.к просто условия str[i] == 0 недостотчно, ибо в числе
				могут присутствовать нули и они просто не выведутся на экран
			*/
			else
			{
				LCD_SendChar(LCD_convertDigitToChar(str[i]));	// Передали один символ массива преобразованный к чару
				k++;
			}
		}

	}
	else if(digit == 0) LCD_SendChar('0');
	else
	{
		LCD_SendChar(_MINUS);					// Вначале будет минус
		buf = buf - (2*buf);			// Делаем из отрицательного положиетльное

		for (int8_t i = 15; i >= 0; i--)
		{
			if(buf > 0)				// Как только разделим последнюю цифру сюда уже не войдём
			{
				str[i] = buf % 10;	// Записываем с конца по-тихоньку число
				buf /= 10;			// Делим на 10, дробная часть будет отбрасываться
				continue;			// Пропускаем break
			}
			break;					// Если записали все число
		}
		for (uint8_t i = 0; i < 16; i++)			// Все работает!!
		{
			if(str[i] == 0 && k == 0) continue;
			/*
				Как только появится первое число в массиве, подлежащее записи, то мы попадём в ветку else,
				и k уже больше не будет равен нулю, поэтому это можно считатать признаком начала числа
				и использовать в условии пропуска, т.к просто условия str[i] == 0 недостотчно, ибо в числе
				могут присутствовать нули и они просто не выведутся на экран
			*/
			else
			{
				LCD_SendChar(LCD_convertDigitToChar( str[i]) );	// Передали один символ массива преобразованный к чару
				k++;
			}
		}
	}
}
void LCD_SendFloatDigit(float digit)
{

}
void LCD_SendString(const char *str)
{
	for (uint8_t i = 0; str[i] != '\0'; i++)
	{
		LCD_SendChar(str[i]);
	}
}

void LCD_SendChar(const char ch)
{
    LCD_Data((uint8_t )ch);
    delay();
}
void LCD_Clear(void)
{
    LCD_Command(0x01);
    HAL_Delay(2);
}
void LCD_SetPos(uint8_t x, uint8_t y)

{
    switch(y)
    {
    	case 0:
    		LCD_Command(x|0x80);	// 0x80 пишем, потому что это условие для команды Set DDRAM Address. 1 в бите DB7
            HAL_Delay(1);
            break;
        case 1:
        	LCD_Command((0x40+x)|0x80);
        	HAL_Delay(1);
        	break;
        }

}
//----------------------------------------
void LCD_ini(void)
{
	HAL_Delay(40);
	rs0;
	LCD_WriteData(3);
	e1;
	delay();
	e0;
	HAL_Delay(1);
	LCD_WriteData(3);
	e1;
	delay();
	e0;
	HAL_Delay(1);
	LCD_WriteData(3);
	e1;
	delay();
	e0;
	HAL_Delay(1);
	LCD_Command(0x08);//режим 4 бит, 2 линии (для нашего большого дисплея это 4 линии, шрифт 5х8
//	HAL_Delay(1);
//	LCD_Command(0x28);//еще раз для верности
	HAL_Delay(1);
	LCD_Command(0x0C);//дисплей включаем (D=1), курсоры никакие не нужны
	HAL_Delay(1);
	LCD_Command(0x01);//уберем мусор
	HAL_Delay(2);
	LCD_Command(0x06);//пишем влево
	HAL_Delay(1);
	LCD_Command(0x02);//возвращаем курсор в нулевое положение
	HAL_Delay(2);
}
/*void str_lcd (char str1[])
{
	wchar_t n;
	for(n=0;str1[n]!='\0';n++)
	sendchar(str1[n]);
}*/
//----------------------------------------

