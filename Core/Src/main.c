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
#include "main.h"
#include "i2c.h"
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
//  int iTempTim4Encoder; //临时存放从TIM4编码器接口捕获到的脉冲数�?
  short accx, accy, accz;
  short gyrox, gyroy, gyroz;	

	
	int iTemTimencoder1, iTemTimencoder2;
	
	uint8_t buf[3];
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
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
  
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		HAL_UART_Receive(&huart3, buf, 1, 0XFFFF);
		HAL_UART_Transmit(&huart3, buf, 1, 100);
		if(buf[0] == '1')
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
		}
		else if(buf[0] == '3')
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 300);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 300);
		}
		else if(buf[0] == '8')
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 800);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 800);
		}
		
		
		iTemTimencoder1 = GetTim4encoder();
		iTemTimencoder2 = GetTim2encoder();
		printf("the pluse of tim4 is = %d\r\n", iTemTimencoder1);
		printf("the pluse of tim2 is = %d\r\n", iTemTimencoder2);

		if(g_iButtonState == 1)
		{
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100);
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);

//			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//			HAL_GPIO_TogglePin(BIN1_GPIO_Port, BIN1_Pin);
//			HAL_GPIO_TogglePin(BIN2_GPIO_Port, BIN2_Pin);			
//			HAL_GPIO_TogglePin(AIN1_GPIO_Port, AIN1_Pin);			
//			HAL_GPIO_TogglePin(AIN2_GPIO_Port, AIN2_Pin);
		
		
		}
//    
//		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
//		MPU_Get_Accelerometer(&accx, &accy, &accz);		
//		printf("gyrox=%d, gyroy=%d, gytoz=%d \n ", gyrox, gyroy, gyroz);
//		printf("accx=%d, accy=%d, accz=%d \n ", accx, accy, accz);

//		printf("the pluse of tim4 is = %d\r\n", iTSSemTimencoder1);
//		printf("the pluse of tim2 is = %d\r\n", iTemTimencoder2);
//		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//		HAL_Delay(1000);
		
//		MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);
//		MPU_Get_Accelerometer(&accx, &accy, &accz);

//		HAL_Delay(1000);
//		if(g_iButtonState == 1)
//		{
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//		printf("LED GPIO TPGGLE!\n");
//		HAL_GPIO_TogglePin(BIN1_GPIO_Port, BIN1_Pin);
//		HAL_GPIO_TogglePin(BIN2_GPIO_Port, BIN2_Pin);
//		}
//		HAL_Delay(5000);
//		iTempTim4Encoder = GetTim4Encoder();
// 		printf("the pulse of tim encoder mode = %d\n",  iTempTim4Encoder);
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//		if(g_iButtonState == 1)
//		{
//			HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//			printf("LED IS TURN ON\n");
//		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
