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
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "printfRedirection.h"
#include "sht30_i2c_drv.h"
#include <stdlib.h>
#include <lcd_spi2_drv.h>


void PrintFloat(float value)
{
    int tmp,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6;
    tmp = (int)value;
    tmp1=(int)((value-tmp)*10)%10;
    tmp2=(int)((value-tmp)*100)%10;
    tmp3=(int)((value-tmp)*1000)%10;
    tmp4=(int)((value-tmp)*10000)%10;
    tmp5=(int)((value-tmp)*100000)%10;
    tmp6=(int)((value-tmp)*1000000)%10;
    printf("%d.%d%d%d%d%d%d",tmp,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6);
}

void recurParse(int n, char** str, unsigned int* restSize) {
    if (n < 10) {
        if (*restSize > 1) {
            **str = n + '0';
            (*str)++;
            *restSize -= 1;
        }

    }
    else {
        recurParse(n / 10, str, restSize);
        if (*restSize > 1) {
            **str = n % 10 + '0';
            (*str)++;
            *restSize -= 1;
        }
    }
}
/*
*outBuffer: 输出字符串的缓冲区
*bufferSize: 输出字符串缓冲区的大小
*in: 要转换的浮点数
*decCount: 输出字符串保留的小数位数
*返回值: 写入到缓冲区中的字符个数（不包含\0）
*/
int float2String(char* outBuffer, unsigned int bufferSize, float in, unsigned int decCount) {
    int n;
    float dec;
    unsigned int restSize = bufferSize;
    if (restSize == 0) return 0;
    n = (int)in;
    dec = in - n;
    if (in < 0) {
        if (restSize > 1 && !(n == 0 && decCount == 0)) {
            *outBuffer++ = '-';
            --restSize;
        }
        n = -n;
    }
    if (dec < 0) {
        dec = -dec;
    }
    recurParse(n, &outBuffer, &restSize);
    if (decCount != 0) {
        if (restSize > 1) {
            *outBuffer++ = '.';
            --restSize;
        }
    }
    while (decCount) {
        dec *= 10;
        n = (int)dec;
        dec -= n;
        if (restSize > 1) {
            *outBuffer++ = n + '0';
            --restSize;
        }
        else {
            break;
        }
        decCount -= 1;
    }
    *outBuffer++ = NULL;
    return bufferSize - restSize;
}

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
  uint8_t recv_dat[6] = {0};
  float temperature = 0.0;
  float humidity = 0.0;

    char strValue[8] = {0};

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
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  //LCD_Clear(GREEN);
  LCD_Clear(BLACK);


  SHT30_reset();
  if(SHT30_Init() == HAL_OK){
      printf("sht30 init ok.\n");
  }
  else{
      printf("sht30 init fail.\n");
  }



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_Delay(1000);
    if(SHT30_Read_Dat(recv_dat) == HAL_OK){
        if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity) == 0) {
            printf("Temperature = ");PrintFloat(temperature);
            printf(", ");
            printf("Humidity = ");PrintFloat(humidity);
            printf("\n");
            LCD_ShowCharStr(0,120-32,180,"Temperature\:",BLACK,RED,24);
            float2String(strValue, sizeof(strValue)/sizeof(char), temperature, 2);
            LCD_ShowCharStr(160,120-32,60,strValue,BLACK,RED,24);

            LCD_ShowCharStr(0,120,180,"Humidity\:",BLACK,RED,24);
            float2String(strValue, sizeof(strValue)/sizeof(char), humidity, 2);
            LCD_ShowCharStr(160,120,60,strValue,BLACK,RED,24);
        }
        else{
            printf("crc check fail.\n");
        }
    }
    else{
        printf("read data from sht30 fail.\n");
    }

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
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
