/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#include <lcd1602.h>
#include "BH1750.h"
#include "bme280.h"

extern uint8_t exti_counter;	// Счётчик нажатий
extern uint8_t trigger_flag;

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern I2C_HandleTypeDef hi2c2;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define BUTTON_Pin GPIO_PIN_1
#define BUTTON_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_3
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_4
#define D5_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_5
#define D6_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_6
#define D7_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_7
#define E_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_8
#define RS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define PAGE_0		0	// Страницы, которые будут отображаться на дисплее
#define PAGE_1		1
#define PAGE_2		2
#define PAGE_3		3

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
