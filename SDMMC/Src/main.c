/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "sdmmc.h"
#include "usart.h"
#include "gpio.h"
#if 1
#include <stdio.h>

int _write(int fd, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}
#endif
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
uint8_t read_buf[512] = {0};
uint8_t write_buf[512] = {0};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int sdcard_status = 0;
  HAL_SD_CardCIDTypeDef sdcard_cid;
  int i = 0;

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
  MX_SDMMC1_SD_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("Micro SD Card Test....\n");

  /*检测SD是否处于正常（处于数据传输模式的传输状态）*/
  sdcard_status = HAL_SD_GetCardState(&hsd1);
  if(sdcard_status == HAL_SD_CARD_TRANSFER){
      printf("SD card init ok!\n");
      //打印SD基本信息
      printf("SD card information!\n");
      printf("CardCapacity: %llu\n",
              ((unsigned long long)hsd1.SdCard.BlockSize*hsd1.SdCard.BlockNbr));
      printf("CardBlockSize: %d\n", hsd1.SdCard.BlockSize);
      printf("CardBlockNum: %d\n", hsd1.SdCard.BlockNbr);
      printf("RCA: %d\n", hsd1.SdCard.RelCardAdd);
      printf("CardType: %d\n", &hsd1.SdCard.CardType);

      //读取并打印SD卡的CID信息
      HAL_SD_GetCardCID(&hsd1, &sdcard_cid);
      printf("ManufacturerID: %d \n", sdcard_cid.ManufacturerID);
  }
  else{
      printf("SD card init fail!\n");
      return 0;
  }

  /*擦除SD卡块*/
  printf("-------------- Block Erase ---------------\n");
  sdcard_status = HAL_SD_Erase(&hsd1,0, 512);
  if(sdcard_status == 0){
      printf("Erase block ok\n");
  }
  else{
      printf("Erase block fail\n");
  }

  //坑 要等得
  while(HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER){
      printf("sd card statues: %d\n", HAL_SD_GetCardState(&hsd1));
  }

  /*读取未操作之前的数据*/
  printf("--------------- Read SD card block data Test ---------------\n");
  sdcard_status = HAL_SD_ReadBlocks(&hsd1, read_buf, 0, 1, 0xffff);
  if(sdcard_status == 0){
      printf("Read block data ok\n");
      for(i=0; i<512;++i){
          printf("0x%02x ", read_buf[i]);
          if((i+1)%16==0){
              printf("\n");
          }
      }
  }
  else{
      printf("Read block data fail!\n");
  }

  /*填充缓冲区数据*/
  for(i=0;i<512;++i){
      write_buf[i] = i%256;
  }
  /*向SD卡块写入数据*/
  printf("----------- Write SD card block data Test -----------\n");
  sdcard_status = HAL_SD_WriteBlocks(&hsd1, write_buf,0, 1, 0xffff);
  if(sdcard_status == 0){
      printf("Write block data ok\n");
  }
  else{
      printf("Write block data fail!\n");
  }

  //坑 要等得
  while(HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER){
      printf("sd card statues: %d\n", HAL_SD_GetCardState(&hsd1));
  }

  /*读取操作之后的数据*/
  printf("--------------- Read SD card block data after Write ---------------\n");
  sdcard_status = HAL_SD_ReadBlocks(&hsd1, read_buf, 0, 1, 0xffff);
  if(sdcard_status == 0){
      printf("Read block data ok\n");
      for(i=0; i<512;++i){
          printf("0x%02x ", read_buf[i]);
          if((i+1)%16==0){
              printf("\n");
          }
      }
  }
  else{
      printf("Read block data fail!\n");
  }
  printf("----- Test Over -----\n");

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_SDMMC1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_48M2CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
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
