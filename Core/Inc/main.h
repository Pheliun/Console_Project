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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define GPIO_A_Pin GPIO_PIN_0
#define GPIO_A_GPIO_Port GPIOA
#define GPIO_B_Pin GPIO_PIN_1
#define GPIO_B_GPIO_Port GPIOA
#define SCR_DC_Pin GPIO_PIN_2
#define SCR_DC_GPIO_Port GPIOA
#define SCR_NCS_Pin GPIO_PIN_3
#define SCR_NCS_GPIO_Port GPIOA
#define SD_NCS_Pin GPIO_PIN_4
#define SD_NCS_GPIO_Port GPIOA
#define GPIO_X_Pin GPIO_PIN_0
#define GPIO_X_GPIO_Port GPIOB
#define GPIO_Y_Pin GPIO_PIN_1
#define GPIO_Y_GPIO_Port GPIOB
#define GPIO_UP_Pin GPIO_PIN_8
#define GPIO_UP_GPIO_Port GPIOA
#define GPIO_LEFT_Pin GPIO_PIN_9
#define GPIO_LEFT_GPIO_Port GPIOA
#define GPIO_DOWN_Pin GPIO_PIN_10
#define GPIO_DOWN_GPIO_Port GPIOA
#define GPIO_RIGHT_Pin GPIO_PIN_11
#define GPIO_RIGHT_GPIO_Port GPIOA
#define SCR_BLK_Pin GPIO_PIN_4
#define SCR_BLK_GPIO_Port GPIOB
#define SCR_RST_Pin GPIO_PIN_5
#define SCR_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
