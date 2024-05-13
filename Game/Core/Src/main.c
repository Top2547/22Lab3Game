/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
UART_HandleTypeDef hlpuart1;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
uint8_t SPIRx[10];
uint8_t SPITx[10];

uint8_t Mode;
uint8_t Switch = 1;
uint8_t LMode1 = 1;
//int Time;
//uint32_t Random_Number[50] = {3,4,2,3,2,3,1,4,2,3,1,2,3,4,2,3,2,1,4,2,3,1,4,2,3,4,1,2,3,2,1,2,3,4,3,2,3,4,3,2,1,4,3,4,2,4,1,4,3,2} ;
//int i = 0;
//int Pattern_Count = 0;
//uint32_t Pattern_Sol[50]; //correct pattern
//uint32_t Pattern_Check[50]; //pattern you play
//int State ; //0 for display 1 for play
//int Numcheck_Count; // to check if you trick all the button
//int test;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
void SPITxRx_Setup();
void SPITxRx_readIO();
void IODIRB_Setup();
void ReadSwitch();
void LED_From();
void Game();
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
  MX_LPUART1_UART_Init();
  MX_TIM2_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  //SPITxRx_Setup();
  IODIRB_Setup();
  HAL_TIM_Base_Start_IT(&htim3); //Control LED 1Hz

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //SPITxRx_readIO();
	  ReadSwitch();
	  Game();
	  Time = HAL_GetTick();
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 16999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 499;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1699;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//void SPITxRx_Setup()
//{
////CS pulse
//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0); // CS Select
//HAL_Delay(1);
//HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1); // CS deSelect
//HAL_Delay(1);
//}

void IODIRB_Setup()//at BEGIN 2
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
	SPITx[0] = 0b01000000;//write
	SPITx[1] = 0x01;//IODIRB
	SPITx[2] = 0b00000000;
	HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
}

void SPITxRx_readIO()
{
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0); // CS Select
		if (Mode == 0)
		{
			SPITx[0] = 0b01000001;//read
			SPITx[1] = 0x12;
			SPITx[2] = 0;
		}
		else if(Mode == 1)
		{
			Game();
		}
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
	}
}


void ReadSwitch()
{
	if (SPIRx[2]==239)
			{
				Switch = 1;
			}
		else if (SPIRx[2]==223)
			{
				Switch = 2;
			}
		else if (SPIRx[2]==176)
			{
				Switch = 3;
			}
		else if (SPIRx[2]==127)
			{
				Switch = 4;
			}
//	if (State == 1)
//		{
//			if (SPIRx[2]==239)
//				{
//				Pattern_Check[Pattern_Count] = 1;
//				Numcheck_Count = Numcheck_Count + 1;
//				State = 0;
//				Switch = 1;
//				}
//			else if (SPIRx[2]==223)
//				{
//				Pattern_Check[Pattern_Count] = 2;
//				Numcheck_Count = Numcheck_Count + 1;
//				State = 0;
//				Switch = 2;
//				}
//			else if (SPIRx[2]==176)
//				{
//				Pattern_Check[Pattern_Count] = 3;
//				Numcheck_Count = Numcheck_Count + 1;
//				State = 0;
//				Switch = 3;
//				}
//			else if (SPIRx[2]==127)
//				{
//				Pattern_Check[Pattern_Count] = 4;
//				Numcheck_Count = Numcheck_Count + 1;
//				State = 0;
//				Switch = 4;
//				}
//		}
}

void Game()
{
	if (Switch == 1)
			{
				SPITx[0] = 0b01000000;//write
				SPITx[1] = 0x15;//OLATB
				if (LMode1 == 1)
					{
					SPITx[2] = 0b11111110;
					test = 7;
					}
				else if (LMode1 == 2)
					{
					SPITx[2] = 0b11111101;
					}
				else if (LMode1 == 3)
					{
					SPITx[2] = 0b11111011;
					}
				else if (LMode1 == 4)
					{
					SPITx[2] = 0b11110111;
					}
				else if (LMode1 == 5)
					{
					SPITx[2] = 0b11101111;
					test = 10;
					}
				else if (LMode1 == 6)
					{
					SPITx[2] = 0b11011111;
					}
				else if (LMode1 == 7)
					{
					SPITx[2] = 0b10111111;
					}
				else if (LMode1 == 8)
					{
					SPITx[2] = 0b01111111;
					}
			}

//	SPITx[0] = 0b01000000;//write
//	SPITx[1] = 0x15;//OLATB
//	Pattern_Sol[Pattern_Count] = Random_Number[Pattern_Count];
//	if (State == 0)
//	{
//		for (i=0;i<=Pattern_Count+1;1)
//		{
//			if (Random_Number[i] == 1)
//			{
//				SPITx[2] = 0b11111011;
//				HAL_Delay(1000);
//				State = 1;
//			}
//			else if (Random_Number[i] == 2)
//			{
//				SPITx[2] = 0b11110111;
//				HAL_Delay(1000);
//				State = 1;
//			}
//			else if (Random_Number[i] == 3)
//			{
//				SPITx[2] = 0b11101111;
//				HAL_Delay(1000);
//				State = 1;
//			}
//			else if (Random_Number[i] == 4)
//			{
//				SPITx[2] = 0b11011111;
//				HAL_Delay(1000);
//				State = 1;
//			}
//		}
//		SPITx[2] = 0b00111100;
//
//	}
//    if (State == 1)
//	{
//		if (SPIRx[2]==239)
//			{
//			Pattern_Check[Pattern_Count] = 1;
//			Numcheck_Count = Numcheck_Count + 1;
//			State = 0;
//			}
//		else if (SPIRx[2]==223)
//			{
//			Pattern_Check[Pattern_Count] = 2;
//			Numcheck_Count = Numcheck_Count + 1;
//			State = 0;
//			}
//		else if (SPIRx[2]==176)
//			{
//			Pattern_Check[Pattern_Count] = 3;
//			Numcheck_Count = Numcheck_Count + 1;
//			State = 0;
//			}
//		else if (SPIRx[2]==127)
//			{
//			Pattern_Check[Pattern_Count] = 4;
//			Numcheck_Count = Numcheck_Count + 1;
//			State = 0;
//			}
//		Pattern_Count = Pattern_Count + 1;
//	}
	//HAL_Delay(1000);
}

//void LED_From()
//{
//	if (Switch == 1)
//		{
//			SPITx[0] = 0b01000000;//write
//			SPITx[1] = 0x15;//OLATB
//			if (LMode1 == 1)
//				{
//				SPITx[2] = 0b11111110;
//				}
//			else if (LMode1 == 2)
//				{
//				SPITx[2] = 0b11111101;
//				}
//			else if (LMode1 == 3)
//				{
//				SPITx[2] = 0b11111011;
//				}
//			else if (LMode1 == 4)
//				{
//				SPITx[2] = 0b11110111;
//				}
//			else if (LMode1 == 5)
//				{
//				SPITx[2] = 0b11101111;
//				}
//			else if (LMode1 == 6)
//				{
//				SPITx[2] = 0b11011111;
//				}
//			else if (LMode1 == 7)
//				{
//				SPITx[2] = 0b10111111;
//				}
//			else if (LMode1 == 8)
//				{
//				SPITx[2] = 0b01111111;
//				}
//		}
//		else if (Switch == 2)
//		{
//			SPITx[0] = 0b01000000;//write
//			SPITx[1] = 0x15;//OLATB
//			if (LMode1 == 1)
//				{
//				SPITx[2] = 0b00000001;
//				}
//			else if (LMode1 == 2)
//				{
//				SPITx[2] = 0b00000010;
//				}
//			else if (LMode1 == 3)
//				{
//				SPITx[2] = 0b00000100;
//				}
//			else if (LMode1 == 4)
//				{
//				SPITx[2] = 0b00001000;
//				}
//			else if (LMode1 == 5)
//				{
//				SPITx[2] = 0b00010000;
//				}
//			else if (LMode1 == 6)
//				{
//				SPITx[2] = 0b00100000;
//				}
//			else if (LMode1 == 7)
//				{
//				SPITx[2] = 0b01000000;
//				}
//			else if (LMode1 == 8)
//				{
//				SPITx[2] = 0b10000000;
//				}
//		}
//
//}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim3)
	{
		LMode1+=1;
		if (LMode1>8)
		{
			LMode1 = 1;
		}
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	Mode+=1;
	if (Mode>1)
	{
		Mode = 0;
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1); //CS dnSelect
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
