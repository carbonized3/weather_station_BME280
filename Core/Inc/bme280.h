#ifndef INC_BME280_H_
#define INC_BME280_H_

#include "main.h"

#define be16toword(a)	((((a)>>8) & 0xff ) | (((a)<<8) & 0xff00))

	// Перевернули 2 байта: 0xFC88 --> 0x88FC
#define be24toword(a)	((((a)>>16)&0x000000FF)|((a)&0x0000FF00)|(((a)<<16)&0x00FF0000))
/*
 	 Меняем порядок байтов. Нужно здесь, потому что старший байт температуры является младшим - т.е это формат BIG ENDIAN(be).
 	 Первой операцией сдвигаем старший байт на 2 байта влево, и одновременно чистим все остальное кроме места, на которое
 	 он встанет. Второй операцией сохраняем середину - она не меняется. Третьей операцией сдвигаем младший байт на место
 	 старшего чистим все остальное кроме места, на которое он встанет операцией & 0x00FF0000 и все полученные 3 байта
 	 лог. ИЛИ синтезируя число в правлиьном порядке.
 	 Используем два нуля впереди, т.к числа могут быть либо 16 бит либо 32, 24 формата нет
 */
//---------------------------------------Коэфициенты для вычисления высота над уровнем моря---------------------------------
#define SEALEVELPRESSURE_HPA 		(1013.25)
#define SEALEVELPRESSURE_PA 		(1013250)
//------------------------------------------------
//--------------------------------------------------Адреса регистров-------------------------------------------------------
#define BME280_HUM_LSB_REG			0xFE
#define BME280_HUM_MSB_REG			0xFD
#define BME280_TEMP_XLSB_REG		0xFC
#define BME280_TEMP_LSB_REG			0xFB
#define BME280_TEMP_MSB_REG			0xFA
#define BME280_PRESS_XLSB_REG		0xF9
#define BME280_PRESS_LSB_REG		0xF8
#define BME280_PRESS_MSB_REG		0xF7
#define BME280_CONFIG_REG			0xF5
#define BME280_CTRL_MEAS_REG		0xF4
#define BME280_STATUS_REG			0xF3
#define BME280_CTRL_HUM_REG			0xF2
#define BME280_RESET_REG			0xE0
#define BME280_ID_REG				0xD0

#define BME280_REGISTER_PRESSUREDATA 	0xF7	// В дш рекомендуют считывать регистры температуры, влажности и давления
#define BME280_REGISTER_TEMPDATA 		0xFA	// пачкой, то есть за одну транзакцию i2c всю температуру или что-то ещё
#define BME280_REGISTER_HUMIDDATA 		0xFD	// Поэтму используем первый регистр msb и смещение

//----------------------------------------------Время нахождения в STANDBY режиме------------------------------------------
#define BME280_STBY_MSK 			0xE0
#define BME280_STBY_0_5 			0x00
#define BME280_STBY_62_5 			0x20
#define BME280_STBY_125 			0x40
#define BME280_STBY_250 			0x60
#define BME280_STBY_500 			0x80
#define BME280_STBY_1000 			0xA0
#define BME280_STBY_10 				0xC0
#define BME280_STBY_20 				0xE0
//--------------------------------------------Фильтры, коэф. фильтрации----------------------------------------------------
#define BME280_FILTER_MSK 			0x1C
#define BME280_FILTER_OFF 			0x00
#define BME280_FILTER_2 			0x04
#define BME280_FILTER_4 			0x08
#define BME280_FILTER_8 			0x0C
#define BME280_FILTER_16 			0x10
//--------------------------------------------Оверсэмлинг для Т, Р, H-----------------------------------------------------
#define BME280_OSRS_T_MSK 			0xE0
#define BME280_OSRS_T_SKIP 			0x00
#define BME280_OSRS_T_x1 			0x20
#define BME280_OSRS_T_x2 			0x40
#define BME280_OSRS_T_x4 			0x60
#define BME280_OSRS_T_x8 			0x80
#define BME280_OSRS_T_x16 			0xA0

#define BME280_OSRS_P_MSK 			0x1C
#define BME280_OSRS_P_SKIP 			0x00
#define BME280_OSRS_P_x1 			0x04
#define BME280_OSRS_P_x2 			0x08
#define BME280_OSRS_P_x4 			0x0C
#define BME280_OSRS_P_x8 			0x10
#define BME280_OSRS_P_x16 			0x14

#define BME280_OSRS_H_MSK 			0x07		// Для оверсэмплинга Влажности свой регистр CTRL_HUM_REG
#define BME280_OSRS_H_SKIP 			0x00
#define BME280_OSRS_H_x1 			0x01
#define BME280_OSRS_H_x2 			0x02
#define BME280_OSRS_H_x4 			0x03
#define BME280_OSRS_H_x8 			0x04
#define BME280_OSRS_H_x16 			0x05
//------------------------------------------------
#define BME280_MODE_MSK 			0x03
#define BME280_MODE_SLEEP			0x00
#define BME280_MODE_FORCED			0x01
#define BME280_MODE_NORMAL			0x03
//------------------------------------------------
#define BME280_REGISTER_DIG_T1 		0x88
#define BME280_REGISTER_DIG_T2 		0x8A
#define BME280_REGISTER_DIG_T3 		0x8C
#define BME280_REGISTER_DIG_P1 		0x8E
#define BME280_REGISTER_DIG_P2 		0x90
#define BME280_REGISTER_DIG_P3 		0x92
#define BME280_REGISTER_DIG_P4 		0x94
#define BME280_REGISTER_DIG_P5 		0x96
#define BME280_REGISTER_DIG_P6 		0x98
#define BME280_REGISTER_DIG_P7 		0x9A
#define BME280_REGISTER_DIG_P8 		0x9C
#define BME280_REGISTER_DIG_P9 		0x9E
#define BME280_REGISTER_DIG_H1 		0xA1
#define BME280_REGISTER_DIG_H2 		0xE1
#define BME280_REGISTER_DIG_H3 		0xE3
#define BME280_REGISTER_DIG_H4 		0xE4
#define BME280_REGISTER_DIG_H5 		0xE5
#define BME280_REGISTER_DIG_H6 		0xE7
//--------------------------------------------------Адрес устройтсва и айди--------------------------------------------------------------
#define BME280_ADDRESS				0x76
#define BME280_ID					0x60

//-----------------------------------------------------------Статусы-------------------------------------------------------
#define BME280_STATUS_MEASURING 	0x08 //Running conversion
#define BME280_STATUS_IM_UPDATE 	0x01 //NVM data copying

//-----------------------------------------------------------Значения------------------------------------------------------
#define SOFT_RESET_VALUE			0xB6
#define _1_BYTE				1		// для записи в регистры
#define _2_BYTE				2

#define LED_OFF()			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define LED_ON()			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0)

uint8_t BME280_init();
float BME280_readTemp();
float BME280_readPress();
float BME280_ReadAltitude(float seaLevel);
float BME280_readHum();

#endif /* INC_BME280_H_ */
