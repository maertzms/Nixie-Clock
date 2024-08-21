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
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_LEN 8
#define BUFF_LEN 50
#define TRANSMIT_TIMEOUT 10
#define msgSize 9

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void Clear_Putty(void);
void Clear_Cube(void);
void Clear_Terminal(void);
void UpdateTime(void);
void UpdateClock(void);
void PrintClock(void);
void PrintTimer(void);
void Echo(void);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
unsigned char rxBUFF[BUFF_LEN] = {' '};
int Transmit = 0;
int Time_Update = 0;
int CLKUpdate = 0;
//STLink on UART2, FTDI on UART3
// UART_HandleTypeDef *ftdiUART = &huart2;
// UART_HandleTypeDef *stmUART = &huart3;
UART_HandleTypeDef *ftdiUART = &huart3;
UART_HandleTypeDef *stmUART = &huart2;
UART_HandleTypeDef *txUART = &huart2;
UART_HandleTypeDef *rxUART = &huart2;
uint8_t hours = 0;
uint8_t minutes = 0;
uint8_t seconds = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
    SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    Clear_Putty();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
  /* USER CODE END 2 */

  /* Initialize leds */
    BSP_LED_Init(LED_GREEN);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    // HAL_UART_Transmit(stmUART, (uint8_t *)"STLink\n\r", 8, TRANSMIT_TIMEOUT);
    // HAL_UART_Transmit(ftdiUART, (uint8_t *)"\nFTDI\n\r", 7, TRANSMIT_TIMEOUT);
    // HAL_UART_Receive_IT(ftdiUART, rxBUFF, RX_LEN);
    HAL_UART_Receive_IT(rxUART, rxBUFF, RX_LEN);
    HAL_TIM_Base_Start_IT(&htim2);
    
    while (1){
        if(CLKUpdate == 1){
            UpdateClock();
            PrintClock();
        }
        if(Time_Update == 1){
            Time_Update = 0;
            UpdateTime();
        }
        if(Transmit == 1){
            Transmit = 0;
        }
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
  htim2.Init.Prescaler = 2719;
//   htim2.Init.Period = 62499;
//   htim2.Init.Prescaler = 219;
  htim2.Init.Period = 63050;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(strcmp((char *)rxBUFF, "Set Time") == 0){
        Time_Update = 1;
    }
    else{
        HAL_UART_Receive_IT(rxUART, rxBUFF, RX_LEN);
        Transmit = 1;
    }
    
}
void Clear_Putty(void)
{
//    HAL_UART_Transmit(txUART, (uint8_t *)"\033c", 5, 10);
    uint8_t msg[4] = {27, '[', '2', 'J'};
   HAL_UART_Transmit(txUART, (uint8_t *)msg, 4, TRANSMIT_TIMEOUT);
}
void Clear_Cube(void)
{
   HAL_UART_Transmit(txUART, (uint8_t *)"\x1B[2J", 7, TRANSMIT_TIMEOUT);
}
void Clear_Terminal(void)
{
   uint8_t message[4] = {0x1B, 0x5B, 0x32, 0x4A};
   HAL_UART_Transmit(txUART, message, 4, TRANSMIT_TIMEOUT);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    CLKUpdate = 1;
    seconds++;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
}
void UpdateTime(){
    uint8_t rxTimeBUFF[2] = {' '};
    HAL_UART_Receive(rxUART, rxTimeBUFF, 3, TRANSMIT_TIMEOUT*70);
    hours = atoi((char *)rxTimeBUFF);
    HAL_UART_Receive(rxUART, rxTimeBUFF, 3, TRANSMIT_TIMEOUT*70);
    minutes = atoi((char *)rxTimeBUFF);
    HAL_UART_Receive(rxUART, rxTimeBUFF, 3, TRANSMIT_TIMEOUT*70);
    seconds = atoi((char *)rxTimeBUFF);
    
    // HAL_UART_Transmit(txUART, (uint8_t *)"Time Updated\n\r", 16, TRANSMIT_TIMEOUT*2);
    // uint8_t timBUFF[3] = {' '};
    // itoa(hours, (char *)timBUFF, 10);
    // HAL_UART_Transmit(txUART, (uint8_t*)"Hours: ", 7, TRANSMIT_TIMEOUT);
    // HAL_UART_Transmit(txUART, timBUFF, 3, TRANSMIT_TIMEOUT);
    
    // itoa(minutes, (char *)timBUFF, 10);
    // HAL_UART_Transmit(txUART, (uint8_t*)"\n\rMinutes: ", 11, TRANSMIT_TIMEOUT);
    // HAL_UART_Transmit(txUART, timBUFF, 3, TRANSMIT_TIMEOUT);
    
    // itoa(seconds, (char *)timBUFF, 10);
    // HAL_UART_Transmit(txUART, (uint8_t*)"\n\rSeconds: ", 11, TRANSMIT_TIMEOUT);
    // HAL_UART_Transmit(txUART, timBUFF, 3, TRANSMIT_TIMEOUT);
    // HAL_UART_Transmit(txUART, (uint8_t*)"\n\r", 2, TRANSMIT_TIMEOUT);
    HAL_UART_Receive_IT(rxUART, rxBUFF, RX_LEN);

}
void UpdateClock(void){
    if(seconds > 59){
        seconds = 0;
        minutes++;
    }
    if(minutes > 59){
        minutes = 0;
        hours++;
    }
    if(hours > 23)
        hours = 0;
}
void PrintClock(void){
    char msg[msgSize] = "    ";
    char *cntrBUFF = msg;
    itoa(hours, cntrBUFF, 10);
    HAL_UART_Transmit(txUART, (uint8_t *)cntrBUFF, msgSize, TRANSMIT_TIMEOUT);
    itoa(minutes, cntrBUFF, 10);
    HAL_UART_Transmit(txUART, (uint8_t *)cntrBUFF, msgSize, TRANSMIT_TIMEOUT);
    itoa(seconds, cntrBUFF, 10);
    HAL_UART_Transmit(txUART, (uint8_t *)cntrBUFF, msgSize, TRANSMIT_TIMEOUT);
    HAL_UART_Transmit(txUART, (uint8_t *)"\r", 1, TRANSMIT_TIMEOUT);
}
void PrintTimer(void){
    const uint8_t *txBUFF = rxBUFF;
    char msg[msgSize] = "         ";
    char *cntrBUFF = msg;
    itoa(TIM2->CNT, cntrBUFF, 10);
    HAL_UART_Transmit(txUART, (uint8_t *)cntrBUFF, 5, TRANSMIT_TIMEOUT);
    HAL_UART_Transmit(txUART, txBUFF, 1, TRANSMIT_TIMEOUT);

}
void Echo(void){

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
