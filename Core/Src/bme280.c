#include <bme280.h>

char str1[100];
int32_t temper_int;

typedef struct
{
  uint16_t dig_T1;
  int16_t dig_T2;
  int16_t dig_T3;
  uint16_t dig_P1;
  int16_t dig_P2;
  int16_t dig_P3;
  int16_t dig_P4;
  int16_t dig_P5;
  int16_t dig_P6;
  int16_t dig_P7;
  int16_t dig_P8;
  int16_t dig_P9;
  uint8_t dig_H1;
  int16_t dig_H2;
  uint8_t dig_H3;
  int16_t dig_H4;
  int16_t dig_H5;
  int8_t dig_H6;
} BME280_CalibData;

BME280_CalibData CalibData;
//------------------------------------------------

static void Error()
{
	LED_OFF();
}
/*
 	 Также после функции ошибки добавим функции записи и чтения по определённому адресу байта для шины I2C
 */
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c2, (Addr<<1), (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);
	if(status != HAL_OK) Error();
}
//------------------------------------------------

static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	status = HAL_I2C_Mem_Read(&hi2c2, (Addr<<1), Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	/*
   	   Здесь спец. функция для раюоты с памятью контроллеров, либо еепром. Указываем адрес устройства, адрес, в нашем
   	   случае адрес регистра размер адреса (8 бит), указатель на буффер и сколько оттуда считать и записать, то есть 1
	 */
	if(status != HAL_OK) Error();
	return value;
}
static void I2Cx_ReadData16(uint16_t Addr, uint8_t Reg, uint16_t *Value)	// Для чтения 2 байт
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read(&hi2c2, (Addr<<1), Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)Value, 2, 0x10000);
	if(status != HAL_OK) Error();
}
//------------------------------------------------
static void I2Cx_ReadData24(uint16_t Addr, uint8_t Reg, uint32_t *Value)	// Для чтения 3 байт
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Read(&hi2c2, (Addr<<1), Reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)Value, 3, 0x10000);
  	if(status != HAL_OK) Error();
}
//------------------------------------------------

uint8_t BME280_readRegister(uint8_t reg)
{
	I2Cx_ReadData(BME280_ADDRESS, reg);
}

static bool BME280_writeRegister(uint8_t reg, uint8_t value)
{
	I2Cx_WriteData(BME280_ADDRESS, reg, value);
}

uint8_t BME280_readStatus(void)
{
	uint8_t res = BME280_readRegister(BME280_STATUS_REG) & 0x09;	// Почистили неустановленные биты.
	return res;
}

bool BME280_reset()
{
	if( !(BME280_writeRegister(BME280_RESET_REG, SOFT_RESET_VALUE)) ) return false;	// Проверка на успешность
	return true;
}

//------------------------------------------------
void BME280_ReadReg_BE_U24(uint8_t Reg, uint32_t *Value)	// Функция для чтения в правильном порядке байт
{
  I2Cx_ReadData24(BME280_ADDRESS,Reg,Value);
  *(uint32_t *) Value = be24toword(*(uint32_t *) Value) & 0x00FFFFFF;
}
void BME280_ReadReg_BE_S16(uint8_t Reg, int16_t *Value)
{
	I2Cx_ReadData16(BME280_ADDRESS,Reg,(uint16_t*)Value);
	*(uint16_t *) Value = be16toword(*(uint16_t *) Value);
}
//------------------------------------------------
//------------------------------------------------

void BME280_ReadReg_U16(uint8_t Reg, uint16_t *Value)
{
	I2Cx_ReadData16(BME280_ADDRESS, Reg, Value);
}
//------------------------------------------------
void BME280_ReadReg_S16(uint8_t Reg, int16_t *Value)
{
	I2Cx_ReadData16(BME280_ADDRESS,Reg, (uint16_t*) Value);
}

void BME280_ReadReg_U24(uint8_t Reg, uint32_t *Value)
{
	I2Cx_ReadData24(BME280_ADDRESS, Reg, Value);
	*(uint32_t *) Value &= 0x00FFFFFF;			// Последний байт уберем, т.к нам нужно всего 20
}
//------------------------------------------------

void BME280_ReadCoefficients(void)
{
  BME280_ReadReg_U16(BME280_REGISTER_DIG_T1,&CalibData.dig_T1);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_T2,&CalibData.dig_T2);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_T3,&CalibData.dig_T3);

  BME280_ReadReg_U16(BME280_REGISTER_DIG_P1,&CalibData.dig_P1);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P2,&CalibData.dig_P2);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P3,&CalibData.dig_P3);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P4,&CalibData.dig_P4);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P5,&CalibData.dig_P5);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P6,&CalibData.dig_P6);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P7,&CalibData.dig_P7);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P8,&CalibData.dig_P8);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_P9,&CalibData.dig_P9);

  CalibData.dig_H1 = BME280_readRegister(BME280_REGISTER_DIG_H1);

  BME280_ReadReg_S16(BME280_REGISTER_DIG_H2,&CalibData.dig_H2);

  CalibData.dig_H3 = BME280_readRegister(BME280_REGISTER_DIG_H3);

  CalibData.dig_H4 = (BME280_readRegister(BME280_REGISTER_DIG_H4) << 4) | (BME280_readRegister(BME280_REGISTER_DIG_H4+1) & 0xF);

  CalibData.dig_H5 = (BME280_readRegister(BME280_REGISTER_DIG_H5+1) << 4) | (BME280_readRegister(BME280_REGISTER_DIG_H5) >> 4);

  CalibData.dig_H6 = (int8_t)BME280_readRegister(BME280_REGISTER_DIG_H6);
}
//------------------------------------------------
void BME280_SetFilter(uint8_t filter)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CONFIG_REG) & ~BME280_FILTER_MSK;
	// очистили все биты на всякий, в которые будем писать
	reg |= filter & BME280_FILTER_MSK;		// Если вдруг во входном значении лишние значения, очистим их с помощью маски и лог. И
	BME280_writeRegister(BME280_CONFIG_REG, reg);
}
//------------------------------------------------
void BME280_SetStandby(uint8_t tsb)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CONFIG_REG) & ~BME280_STBY_MSK;	// Очистим значение от предыдущих битов если они есть там
	reg |= tsb & BME280_STBY_MSK;				// Если вдруг во входном значении лишние значения, очистим их с помощью маски и лог. И
	BME280_writeRegister(BME280_CONFIG_REG,reg);
}
//------------------------------------------------
void BME280_SetOversamplingTemper(uint8_t ovrsmp)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CTRL_MEAS_REG) & ~BME280_OSRS_T_MSK;	// Очистим значение от предыдущих битов если они есть там
	reg |= ovrsmp & BME280_OSRS_T_MSK;				// Если вдруг во входном значении лишние значения, очистим их с помощью маски и лог. И
	BME280_writeRegister(BME280_CTRL_MEAS_REG, reg);
}
//------------------------------------------------
void BME280_SetOversamplingPress(uint8_t ovrsmp)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CTRL_MEAS_REG) & ~BME280_OSRS_P_MSK;	// Очистим значение от предыдущих битов если они есть там
	reg |= ovrsmp & BME280_OSRS_P_MSK;				// Если вдруг во входном значении лишние значения, очистим их с помощью маски и лог. И
	BME280_writeRegister(BME280_CTRL_MEAS_REG, reg);
}
//------------------------------------------------
static void BME280_SetOversamplingHum(uint8_t ovrsmp)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CTRL_HUM_REG) & ~BME280_OSRS_H_MSK;
	/*  В этот рег можно писать только после того, как записали значения в регистр CTRL_MEAS и задали оверсэмлинги	*/
	reg |= ovrsmp & BME280_OSRS_H_MSK;				// Если вдруг во входном значении лишние значения, очистим их с помощью маски и лог. И
	BME280_writeRegister(BME280_CTRL_HUM_REG, reg);

	reg = BME280_readRegister(BME280_CTRL_MEAS_REG);
	BME280_writeRegister(BME280_CTRL_MEAS_REG, reg);
	/*
	 	После занесения значений оверсемплинга влажности в соответствующий регистр мы считали и заново записали данные
	 	регистра F4. Мы это сделали потому, что существует такое требование, гласящее о том, что изменения регистра
	 	оверсемплинга влажности станут актуальными только после записи регистра CTRL_MEAS
	 */
}

static void BME280_SetMode(uint8_t mode)
{
	uint8_t reg;
	reg = BME280_readRegister(BME280_CTRL_MEAS_REG) & ~BME280_MODE_MSK;
	reg |= mode & BME280_MODE_MSK;
	BME280_writeRegister(BME280_CTRL_MEAS_REG, reg);
}


float BME280_readHum()
{
	float hum_float = 0.0f;
	uint32_t hum_raw;
	int32_t hum_raw_sign, v_x1_u32r;
	BME280_readTemp(); // must be done first to get t_fine
	BME280_ReadReg_BE_S16(BME280_REGISTER_HUMIDDATA, &hum_raw);		// Прочитали сырое значение в правильном порядке байт

	hum_raw_sign = ((int32_t)hum_raw)&0x0000FFFF;
	v_x1_u32r = (temper_int - ((int32_t)76800));
	v_x1_u32r = (((((hum_raw_sign << 14) - (((int32_t)CalibData.dig_H4) << 20) -
		(((int32_t)CalibData.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
		(((((((v_x1_u32r * ((int32_t)CalibData.dig_H6)) >> 10) *
		(((v_x1_u32r * ((int32_t)CalibData.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
		((int32_t)2097152)) * ((int32_t)CalibData.dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
		((int32_t)CalibData.dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
	v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	hum_float = (v_x1_u32r>>12);
	hum_float /= 1024.0f;

	return hum_float;
}

float BME280_readTemp()
{
	float temp_float = 0.0f;
	//char str[20];
	uint32_t temper_raw;	// Для чтения регистров
	int32_t val1, val2;		// Для промежуточных измерений
	BME280_ReadReg_BE_U24(BME280_REGISTER_TEMPDATA, &temper_raw);	// Считаем 3 байта сразу
	/*
	 	 По изменениям данных мы видим, что они у нас перевёрнуты, то есть меняется старший байт, не может же температура
	 	 скакать на порядок. Ну, в принципе, мы так и ожидали, так как байты в регистре и расположены наоборот, судя по
	 	 даташиту, старшим байтом вперёд (формат big endian). Поэтому нам надо как-то перевернуть всё это дело.

	 	 Получается считывать сразу пачкой регистры не указывая каждый раз новый адрес регистра за счёт того, что
	 	 микросхема BME280 сама после того как ей указали адрес и начали при следующем старте считвыать байт, она сама
	 	 после первого считанного байта выдает байт из следующего регистра, т.е инкременитрует адрес.
	 	 Например:
	 	 	 1. Мы дали адрес ус-ва(W) + адрес регистра
	 	 	 2. Затем дали адрес ус-ва(R) и начали читать.
	 	 	 3. 1-ый байт будет из регистра, адрес которого мы указали
	 	 	 4. 2-ой байт будет уже из (адрес_регистра + 1)
	 	 	 5. 3-ий байт будет из (адрес_регистра + 2)
	 	 И т.д, сколько мы укажем в функции HAL.
	 	 Ещё момент есть, что функция HAL_I2C_Mem_Read()  как-то сама в переменную правильно присваивает считанные значения
	 	 в таком порядке:
	 	 	 1-ый считанный байт будет являться младшим.
	 	 	 2-ой считанный байт смещается на 8 влево.
	 	 	 3-ий считанный байт смещается на 16 влево относительно нуля.

	 	 Т. е идёт автоматическое смещение и нам не нужно ничего делать и заморачиваться массивами, чтобы каждый новый
	 	 элемент падал в +1 ячейку. Одно условие, чтобы данные не потерялись, в переменной, которую мы на вермя приводим к
	 	 типу (uint8_t *), было куда сдвигать, т.е тип должен быть 16,32 и тд бит
	 */

	temper_raw >>= 4;
						// Убрали часть, котоаря не учавствует
	/*	Теперь сдвинем всё это на 4 бита вправо, так как именно так у нас хранится сырое значение температуры и
	 * 		четыре самых младших бита не участвуют в показаниях	*/

	val1 = ((((temper_raw>>3) - ((int32_t)CalibData.dig_T1 <<1))) *
	((int32_t)CalibData.dig_T2)) >> 11;

	/*val2 = (((((temper_raw>>4) - ((int32_t)CalibData.dig_T1)) *
	((temper_raw>>4) - ((int32_t)CalibData.dig_T1))) >> 12) *
	((int32_t)CalibData.dig_T3)) >> 14;*/

	val2 = (int32_t)(((((temper_raw>>4) - ((int32_t)CalibData.dig_T1)) *
	((temper_raw>>4) - ((int32_t)CalibData.dig_T1))) >> 12) *
	((int32_t)CalibData.dig_T3)) >> 14;

	temper_int = val1 + val2;
	temp_float = ((temper_int * 5 + 128) >> 8);
	temp_float /= 100.0f;
	/*
		Взяли пример, как вычислить температуру из сырого значения регистров в int прямиком из даташита
	*/
	return temp_float;
}
//------------------------------------------------
float BME280_readPress()
{
	float press_float = 0.0f;
	uint32_t press_raw, pres_int;
	int64_t val1, val2, p;

	BME280_readTemp(); // must be done first to get t_fine. Участвует в расчётах давления
	BME280_ReadReg_BE_U24(BME280_REGISTER_PRESSUREDATA, &press_raw);
	press_raw >>= 4;		//последние 4 бита не участвуют

	val1 = ((int64_t) temper_int) - 128000;
	val2 = val1 * val1 * (int64_t)CalibData.dig_P6;
	val2 = val2 + ((val1 * (int64_t)CalibData.dig_P5) << 17);
	val2 = val2 + ((int64_t)CalibData.dig_P4 << 35);
	val1 = ((val1 * val1 * (int64_t)CalibData.dig_P3) >> 8) + ((val1 * (int64_t)CalibData.dig_P2) << 12);
	val1 = (((((int64_t)1) << 47) + val1)) * ((int64_t)CalibData.dig_P1) >> 33;
	if (val1 == 0) {
	  return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - press_raw;
	p = (((p << 31) - val2) * 3125) / val1;
	val1 = (((int64_t)CalibData.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	val2 = (((int64_t)CalibData.dig_P8) * p) >> 19;
	p = ((p + val1 + val2) >> 8) + ((int64_t)CalibData.dig_P7 << 4);
	pres_int = ((p >> 8) * 1000) + (((p & 0xff) * 390625) / 100000);
	press_float = pres_int / 100.0f;
	/*	Расчёты взяли и ДШ	*/
	return press_float;
}
//------------------------------------------------
float BME280_ReadAltitude(float seaLevel)		// Высота над уровнем моря, зависит от давления
{
	float att = 0.0f;
	float atm = BME280_readPress();
	att = 44330.0 * (1.0 - pow(atm / seaLevel, 0.1903));
	return att;
}

//------------------------------------------------

uint8_t BME280_init()
{
	uint32_t value32;

	LED_ON();
	if (BME280_readRegister(BME280_ID_REG) != BME280_ID) {}	// Проверка работаем ли мы с действительно bme280

	BME280_reset();			// Дальше нужно сделать ресет
	while (BME280_readStatus() & BME280_STATUS_IM_UPDATE){} 	// Ждём в цикле, если установлен бит занятости

	BME280_ReadCoefficients();		// Читаем коэфициенты
	/* Во время нахождения в данном состоянии STANBY мы при необходимости и считываем данные. Это время и настроим */
	BME280_SetStandby(BME280_STBY_1000);	// Режим стэндбай	1000 мс, время когда датчик ничего не делает. см диаграмму в дш
	BME280_SetFilter(BME280_FILTER_4);		// Коэф. фильтрации 4.
	BME280_SetOversamplingTemper(BME280_OSRS_T_x4);
	BME280_SetOversamplingPress(BME280_OSRS_P_x2);
	BME280_SetOversamplingHum(BME280_OSRS_H_x1);
	BME280_SetMode(BME280_MODE_NORMAL);

	/*value32 = BME280_readRegister(BME280_CTRL_MEAS_REG);
	value32 |= BME280_readRegister(BME280_CTRL_HUM_REG) << 8;
	sprintf(str1, "%04Xrn", value32);
	LCD_SetPos(0, 0);
	LCD_SendString(str1);

	sprintf(str1,
	  (value32 & BME280_OSRS_T_MSK) ? "ON " : "OFF ",
	  (value32 & BME280_OSRS_P_MSK) ? "ON " : "OFF ",
	  ((value32 >> 8) & BME280_OSRS_H_MSK) ? "ON " : "OFF ");
	LCD_SetPos(0, 1);
	LCD_SendString(str1);*/
}


