/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TRACK1 HAL_GPIO_ReadPin(TRACK_OUT1_GPIO_Port, TRACK_OUT1_Pin)
#define TRACK2 HAL_GPIO_ReadPin(TRACK_OUT2_GPIO_Port, TRACK_OUT2_Pin)
#define TRACK3 HAL_GPIO_ReadPin(TRACK_OUT3_GPIO_Port, TRACK_OUT3_Pin)
#define TRACK4 HAL_GPIO_ReadPin(TRACK_OUT4_GPIO_Port, TRACK_OUT4_Pin)
#define TRACK5 HAL_GPIO_ReadPin(TRACK_OUT5_GPIO_Port, TRACK_OUT5_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t ifMsgGet = 0;
uint8_t msg = 0;
uint8_t speed = 0;
uint8_t tickFlag = 0;
uint16_t pwmVal = 1;   //PWM占空比

//float kp = 20;
//float ki = 0;
//float kd = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void littleCarMove();
void goForward();
void goBack();
void turnLeft();
void turnRight();
void stopAll();

float pidOutput();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  pwmVal = 250;

  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_UART_Transmit(&huart1,"Ready!\r\n",sizeof("Ready!\r\n"),20);
  HAL_UART_Transmit(&huart1,"Waiting...\r\n", sizeof("Waiting...\r\n"),20);
  HAL_UART_Transmit(&huart1,"Motor Power:", sizeof("Motor Power:"),20);
  char powerMsg[10] = "";
  sprintf(powerMsg, "%.2f", 1000000.0 / pwmVal / 10000.0);
  HAL_UART_Transmit(&huart1, powerMsg, sizeof(powerMsg), 20);

  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal);    //修改比较值，修改占空比
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal-30);    //修改比较值，修改占空比

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    while ((msg != '1') && HAL_UART_Receive(&huart1,&msg,1,0) == HAL_OK);

    if (msg == '1')
    {
      ifMsgGet = 1;
      msg = 0;
    }
    if (ifMsgGet)
    {
      HAL_UART_Transmit(&huart1,"Get! Speed?(1-9)\r\n", sizeof("Get! Speed?(1-9)\r\n"),20);
      while ((msg != '1') && HAL_UART_Receive(&huart1, &speed, 1, 0) == HAL_OK);
      ifMsgGet = 0;
      //goForward();
      littleCarMove();
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//float pidOutput()
//{
//  float err, errPre;
//  static float integral;
//  float output;
//
//  if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 0 && TRACK4 == 1 && TRACK5 == 1) err = 0;
//
//  else if (TRACK1 == 1 && TRACK2 == 0 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) err = -1;
//  else if (TRACK1 == 0 && TRACK2 == 0 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) err = -2;
//  else if (TRACK1 == 0 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) err = -3;
//
//  else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 0 && TRACK5 == 1) err = 1;
//  else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 0 && TRACK5 == 0) err = 2;
//  else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 0) err = 3;
//
//  else err = 0;
//
//  integral += err;
//  output = kp * err + ki * integral + kd * (err - errPre);
//  errPre = err;
//  return output;
//}

void goForward()
{
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal);    //修改比较值，修改占空比
  //__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal);    //修改比较值，修改占空比
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal+8);    //修改比较值，修改占空比
  HAL_GPIO_WritePin(MOTOR1_CTRL1_GPIO_Port, MOTOR1_CTRL1_Pin, 1);
  HAL_GPIO_WritePin(MOTOR1_CTRL2_GPIO_Port, MOTOR1_CTRL2_Pin, 0);
  HAL_GPIO_WritePin(MOTOR2_CTRL1_GPIO_Port, MOTOR2_CTRL1_Pin, 0);
  HAL_GPIO_WritePin(MOTOR2_CTRL2_GPIO_Port, MOTOR2_CTRL2_Pin, 1);
}

void stopAll()
{
  HAL_GPIO_WritePin(MOTOR1_CTRL1_GPIO_Port, MOTOR1_CTRL1_Pin, 1);
  HAL_GPIO_WritePin(MOTOR1_CTRL2_GPIO_Port, MOTOR1_CTRL2_Pin, 1);
  HAL_GPIO_WritePin(MOTOR2_CTRL1_GPIO_Port, MOTOR2_CTRL1_Pin, 1);
  HAL_GPIO_WritePin(MOTOR2_CTRL2_GPIO_Port, MOTOR2_CTRL2_Pin, 1);
}

void turnLeft()
{
  //电机2反转
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal-40);    //修改比较值，修改占空比
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal-5);    //修改比较值，修改占空比
  HAL_GPIO_WritePin(MOTOR1_CTRL1_GPIO_Port, MOTOR1_CTRL1_Pin, 1);
  HAL_GPIO_WritePin(MOTOR1_CTRL2_GPIO_Port, MOTOR1_CTRL2_Pin, 0);
  HAL_GPIO_WritePin(MOTOR2_CTRL1_GPIO_Port, MOTOR2_CTRL1_Pin, 1);
  HAL_GPIO_WritePin(MOTOR2_CTRL2_GPIO_Port, MOTOR2_CTRL2_Pin, 0);
}

void turnRight()
{
  //电机1反转
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal-55);    //修改比较值，修改占空比
  HAL_GPIO_WritePin(MOTOR1_CTRL1_GPIO_Port, MOTOR1_CTRL1_Pin, 0);
  HAL_GPIO_WritePin(MOTOR1_CTRL2_GPIO_Port, MOTOR1_CTRL2_Pin, 1);
  HAL_GPIO_WritePin(MOTOR2_CTRL1_GPIO_Port, MOTOR2_CTRL1_Pin, 0);
  HAL_GPIO_WritePin(MOTOR2_CTRL2_GPIO_Port, MOTOR2_CTRL2_Pin, 1);
}

void littleCarMove()
{
  while(1)
  {
    HAL_UART_Receive(&huart1,&msg,1,10);

    if (msg == '3') //emergency stop
    {
      msg = 0;
      HAL_UART_Transmit(&huart1,"Stop!!!\r\n", sizeof("Stop!!!\r\n"),8);
      stopAll();
      return;
    }

    if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 0 && TRACK4 == 1 && TRACK5 == 1) goForward();

    else if (TRACK1 == 1 && TRACK2 == 0 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) turnLeft();
    else if (TRACK1 == 0 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) turnLeft();
    else if (TRACK1 == 0 && TRACK2 == 0 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) turnLeft();

    else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 0 && TRACK5 == 1) turnRight();
    else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 0) turnRight();
    else if (TRACK1 == 1 && TRACK2 == 1 && TRACK3 == 1 && TRACK4 == 1 && TRACK5 == 1) turnRight();

//    float tempFlag = pidOutput();
//    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, pwmVal + tempFlag);
//    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, pwmVal + tempFlag);
//    if (tempFlag < 15 && tempFlag > -15) goForward();
//    else if (tempFlag >= 15) turnLeft();
//    else if (tempFlag <= -15) turnRight();

    if (tickFlag == 1)
    {
      HAL_UART_Transmit(&huart1,"Running...\r\n", sizeof("Running...\r\n"),8);
      tickFlag = 0;
    }
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

