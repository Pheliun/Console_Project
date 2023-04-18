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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_interface.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CMD_SOFTRST 0x01
#define CMD_COLADDRSET 0x2A
#define CMD_PAGADDRSET 0x2B
#define CMD_MEMWRCON 0x3C
#define CMD_DSPINVON 0x21
#define CMD_DSPINVOFF 0x20



#define STRTPG 320/2-20
#define ENDPG 320/2+20
#define STRTCL 240/2-20
#define ENDCL 240/2+20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
// offsets
uint16_t start_pag = STRTPG;
uint16_t end_pag = ENDPG;
uint16_t start_col = STRTCL;
uint16_t end_col = ENDCL;

//colors
uint16_t red_clr = (uint16_t) ((255<<11) | (0<<5) | 0);
uint16_t white_clr = (uint16_t) ((255<<11) | (255<<5) | 255);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FATFS fs;
FIL fil;
FRESULT fresult;
char buffer[1024];

UINT br, bw;

/* capacity related variables */
FATFS *pfs;
DWORD fre_clust;
uint32_t total, freespace;


/* buffer functions */
// returns buffer's data size
uint8_t buffSize(char *buff){
	int i = 0;
	while (*buff++ != '\0'){
		i++;
	}
	return i;
}
// clears buffer of data
uint8_t clearBuff(char *buff){
	int i = 0;
	while (*buff++ != '\0'){
		buffer[i] = '\0';
	}
	return i;
}


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
  init_ILI9341(); //initialize screen
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SCR_DC_Pin|SCR_NCS_Pin|SD_NCS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCR_BLK_Pin|SCR_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GPIO_A_Pin GPIO_B_Pin GPIO_UP_Pin GPIO_LEFT_Pin
                           GPIO_DOWN_Pin GPIO_RIGHT_Pin */
  GPIO_InitStruct.Pin = GPIO_A_Pin|GPIO_B_Pin|GPIO_UP_Pin|GPIO_LEFT_Pin
                          |GPIO_DOWN_Pin|GPIO_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SCR_DC_Pin SCR_NCS_Pin SD_NCS_Pin */
  GPIO_InitStruct.Pin = SCR_DC_Pin|SCR_NCS_Pin|SD_NCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIO_X_Pin GPIO_Y_Pin */
  GPIO_InitStruct.Pin = GPIO_X_Pin|GPIO_Y_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SCR_BLK_Pin SCR_RST_Pin */
  GPIO_InitStruct.Pin = SCR_BLK_Pin|SCR_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	 if(GPIO_Pin == GPIO_A_Pin) // check if GPIO_A is pressed
	  {
	    // handle GPIO_A press
		 displayInversionON();
	  }
	  else if(GPIO_Pin == GPIO_B_Pin) // check if GPIO_B is pressed
	  {
	    // handle GPIO_B press
		  displayInversionOFF();
	  }
	  else if(GPIO_Pin >= GPIO_UP_Pin && GPIO_Pin <= GPIO_LEFT_Pin) // check if GPIO_UP or GPIO_LEFT is pressed
	  {
		  ClearScreen(start_col, end_col, start_pag, end_pag);
	    if(HAL_GPIO_ReadPin(GPIOA, GPIO_UP_Pin) == GPIO_PIN_SET) // check if GPIO_UP is pressed
	    {
	      // handle GPIO_UP press
	    	start_pag--;
	    	end_pag--;
	    	columnAddressSet(start_col, end_col);
	    	pageAddressSet(start_pag, end_pag);
	    	writeMemoryContinue(red_clr, start_col, end_col, start_pag, end_pag);

	    }
	    else if(HAL_GPIO_ReadPin(GPIOA,GPIO_LEFT_Pin) == GPIO_PIN_SET) // check if GPIO_LEFT is pressed
	    {
	      // handle GPIO_LEFT press
	    	start_col--;
	    	end_col--;
	    	columnAddressSet(start_col, end_col);
	    	pageAddressSet(start_pag, end_pag);
	    	writeMemoryContinue(red_clr, start_col, end_col, start_pag, end_pag);
	    }
	  }
	  else if(GPIO_Pin >= GPIO_DOWN_Pin && GPIO_Pin <= GPIO_RIGHT_Pin) // check if GPIO_DOWN or GPIO_RIGHT is pressed
	  {
		  ClearScreen(start_col, end_col, start_pag, end_pag);
	    if(HAL_GPIO_ReadPin(GPIOA, GPIO_DOWN_Pin) == GPIO_PIN_SET) // check if GPIO_DOWN is pressed
	    {
	      // handle GPIO_DOWN press
	    	start_pag++;
	    	end_pag++;
	    	columnAddressSet(start_col, end_col);
	    	pageAddressSet(start_pag, end_pag);
	    	writeMemoryContinue(red_clr, start_col, end_col, start_pag, end_pag);
	    }
	    else if(HAL_GPIO_ReadPin(GPIOA, GPIO_RIGHT_Pin) == GPIO_PIN_SET) // check if GPIO_RIGHT is pressed
	    {
	      // handle GPIO_RIGHT press
	    	start_col++;
	    	end_col++;
	    	columnAddressSet(start_col, end_col);
	    	pageAddressSet(start_pag, end_pag);
	    	writeMemoryContinue(red_clr, start_col, end_col, start_pag, end_pag);
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
