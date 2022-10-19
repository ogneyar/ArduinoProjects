/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789.h"
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(BLK_GPIO_Port, BLK_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    ST7789_Init(240, 240);
	  // Инициализация входа для кнопки
    // Тест вывода основных цветов
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		
//    uint16_t color = RGB565(255, 0, 0);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);
//  
//    color = RGB565(0, 255, 0);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(50, 55, 50);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(0, 0, 255);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(255, 255, 0);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(255, 0, 255);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(0, 255, 255);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);

//    color = RGB565(255, 255, 255);
//    ST7789_FillScreen(color);
//    HAL_Delay(500);
//		
//    ST7789_FillScreen(BLACK);
//    ST7789_SetBL(100);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		ST7789_DrawChar_5x8(100, 100, RGB565(0, 255, 255), RGB565(0, 0, 0), 0, 'A');
		ST7789_DrawChar_7x11(60, 60, RGB565(0, 255, 255), RGB565(0, 0, 0), 0, 0xBB);

    ST7789_print_5x8(10, 30, RGB565(0, 255, 255), RGB565(0, 0, 0), 0, "Привет"); 		
    ST7789_print_7x11(40, 40, RGB565(0, 255, 255), RGB565(0, 0, 0), 0, "Welcome"); 		

    HAL_Delay(10000);

//		for (uint8_t y = 0; y<240 ; y++) {
//			ST7789_DrawLine(120, 120, 239, y, RGB565(y+10, 0, 0));
//		}
//   		
//		for (uint8_t x = 0; x<240 ; x++) {
//			ST7789_DrawLine(120, 120, x, 239, RGB565(0, x+10, 0));
//		}
//   
//		for (uint8_t y = 0; y<240 ; y++) {
//			ST7789_DrawLine(120, 120, 0, y, RGB565(0, 0, y+10));
//		}
// 
//		for (uint8_t x = 0; x<240 ; x++) {
//			ST7789_DrawLine(120, 120, x, 0, RGB565(x+10, x+10, x+10));
//		}
//    HAL_Delay(1000);

//    ST7789_FillScreen(BLACK);
//    ST7789_SetBL(100);

//    for (uint8_t x = 0; x < 240 ; x = x + 20) {
//			for (uint8_t y = 0; y < 240; y = y + 20) {
//				ST7789_DrawRectangleFilled(x + 3, y + 3, x + 17, y + 17, RGB565(x, y, 0));
//				ST7789_DrawRectangle(x + 2, y + 2, x + 19, y + 19, RGB565(250, 250, 250));
//			}
//		}
//    HAL_Delay(1000);

//    ST7789_FillScreen(BLACK);
//    ST7789_SetBL(100);

//    for (uint8_t x = 0; x < 240 ; x = x + 20) {
//			for (uint8_t y = 0; y < 240; y = y + 20) {
//        ST7789_DrawCircleFilled(x + 10, y + 10, 8, RGB565(x, y, 0));
//        ST7789_DrawCircle(x + 10, y + 10, 9, RGB565(0, y, x));
//			}
//		}
//    HAL_Delay(1000);

//    ST7789_FillScreen(BLACK);
 //   ST7789_SetBL(100);
	
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
