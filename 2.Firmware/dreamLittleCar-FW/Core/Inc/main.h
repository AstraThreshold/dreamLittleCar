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
#include "stm32f4xx_hal.h"

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
static uint16_t tickCount = 0;
extern uint8_t tickFlag;  //per 100ms turn 1
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR2_CTRL1_Pin GPIO_PIN_6
#define MOTOR2_CTRL1_GPIO_Port GPIOA
#define MOTOR2_CTRL2_Pin GPIO_PIN_7
#define MOTOR2_CTRL2_GPIO_Port GPIOA
#define MOTOR1_PWM_Pin GPIO_PIN_0
#define MOTOR1_PWM_GPIO_Port GPIOB
#define MOTOR2_PWM_Pin GPIO_PIN_1
#define MOTOR2_PWM_GPIO_Port GPIOB
#define TRACK_OUT1_Pin GPIO_PIN_10
#define TRACK_OUT1_GPIO_Port GPIOB
#define TRACK_OUT2_Pin GPIO_PIN_12
#define TRACK_OUT2_GPIO_Port GPIOB
#define TRACK_OUT3_Pin GPIO_PIN_13
#define TRACK_OUT3_GPIO_Port GPIOB
#define TRACK_OUT4_Pin GPIO_PIN_14
#define TRACK_OUT4_GPIO_Port GPIOB
#define TRACK_OUT5_Pin GPIO_PIN_15
#define TRACK_OUT5_GPIO_Port GPIOB
#define MOTOR1_CTRL1_Pin GPIO_PIN_8
#define MOTOR1_CTRL1_GPIO_Port GPIOA
#define MOTOR1_CTRL2_Pin GPIO_PIN_9
#define MOTOR1_CTRL2_GPIO_Port GPIOA
#define IR_RXD_Pin GPIO_PIN_11
#define IR_RXD_GPIO_Port GPIOA
#define IR_TXD_Pin GPIO_PIN_12
#define IR_TXD_GPIO_Port GPIOA
#define HC05_RXD_Pin GPIO_PIN_15
#define HC05_RXD_GPIO_Port GPIOA
#define HC05_TXD_Pin GPIO_PIN_3
#define HC05_TXD_GPIO_Port GPIOB
#define HC05_STATE_Pin GPIO_PIN_4
#define HC05_STATE_GPIO_Port GPIOB
#define HC05_EN_Pin GPIO_PIN_5
#define HC05_EN_GPIO_Port GPIOB
#define SR04_ECHO_Pin GPIO_PIN_6
#define SR04_ECHO_GPIO_Port GPIOB
#define SR04_TRIG_Pin GPIO_PIN_7
#define SR04_TRIG_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
