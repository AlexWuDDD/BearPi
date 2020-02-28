/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId LowPriorityTaskHandle;
osThreadId MidPriorityTaskHandle;
osThreadId HighPriorityTasHandle;
osMutexId myMutex01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void LowPriority(void const * argument);
void MidPriority(void const * argument);
void HighPriority(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of myMutex01 */
  osMutexDef(myMutex01);
  myMutex01Handle = osMutexCreate(osMutex(myMutex01));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of LowPriorityTask */
  osThreadDef(LowPriorityTask, LowPriority, osPriorityLow, 0, 128);
  LowPriorityTaskHandle = osThreadCreate(osThread(LowPriorityTask), NULL);

  /* definition and creation of MidPriorityTask */
  osThreadDef(MidPriorityTask, MidPriority, osPriorityNormal, 0, 128);
  MidPriorityTaskHandle = osThreadCreate(osThread(MidPriorityTask), NULL);

  /* definition and creation of HighPriorityTas */
  osThreadDef(HighPriorityTas, HighPriority, osPriorityHigh, 0, 128);
  HighPriorityTasHandle = osThreadCreate(osThread(HighPriorityTas), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_LowPriority */
/**
  * @brief  Function implementing the LowPriorityTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_LowPriority */
void LowPriority(void const * argument)
{
  /* USER CODE BEGIN LowPriority */
  BaseType_t xReturn = pdPASS;
  /* Infinite loop */
  for(;;)
  {
    printf("LowPriority_Task申请信号量\n");
    xReturn = xSemaphoreTake(myMutex01Handle, portMAX_DELAY); //拿不到一直等
    if(xReturn == pdTRUE){
        printf("LowPriority_Task Running\n");
        for(int i = 0; i < 2000000; ++i){
            HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        }
        printf("LowPriority_Task释放信号量\n");
        xReturn = xSemaphoreGive(myMutex01Handle);
    }
    osDelay(1000);
  }
  /* USER CODE END LowPriority */
}

/* USER CODE BEGIN Header_MidPriority */
/**
* @brief Function implementing the MidPriorityTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MidPriority */
void MidPriority(void const * argument)
{
  /* USER CODE BEGIN MidPriority */
  /* Infinite loop */
  for(;;)
  {
    printf("MidPriority_Task Running\n");
    osDelay(1000);
  }
  /* USER CODE END MidPriority */
}

/* USER CODE BEGIN Header_HighPriority */
/**
* @brief Function implementing the HighPriorityTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HighPriority */
void HighPriority(void const * argument)
{
  /* USER CODE BEGIN HighPriority */
    BaseType_t xReturn = pdPASS;
    /* Infinite loop */
    for(;;)
    {
        printf("HighPriority_Task申请信号量\n");
        xReturn = xSemaphoreTake(myMutex01Handle, portMAX_DELAY); //拿不到一直等
        if(xReturn == pdTRUE){
            printf("HighPriority_Task Running\n");
            HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
            printf("HighPriority_Task释放信号量\n");
            xReturn = xSemaphoreGive(myMutex01Handle);
        }
        osDelay(1000);
    }
  /* USER CODE END HighPriority */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
