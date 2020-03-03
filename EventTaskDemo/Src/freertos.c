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
#include "event_groups.h"
#include "stdio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
static EventGroupHandle_t  Event_Handle = NULL;
#define KEY1_EVENT (0x01 << 0) //设置事件掩码位0
#define KEY2_EVENT (0x01 << 1) //设置事件掩码位1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId LED_TASKHandle;
osThreadId KEY_TASKHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void LEDTASKEntry(void const * argument);
void KEYTASKEntry(void const * argument);

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
  /*创建Event_Handle*/
  Event_Handle = xEventGroupCreate();
  if(NULL != Event_Handle){
      printf("Event_Handle事件创建成功\n");
  }

  /* Create the thread(s) */
  /* definition and creation of LED_TASK */
  osThreadDef(LED_TASK, LEDTASKEntry, osPriorityNormal, 0, 128);
  LED_TASKHandle = osThreadCreate(osThread(LED_TASK), NULL);

  /* definition and creation of KEY_TASK */
  osThreadDef(KEY_TASK, KEYTASKEntry, osPriorityIdle, 0, 128);
  KEY_TASKHandle = osThreadCreate(osThread(KEY_TASK), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_LEDTASKEntry */
/**
  * @brief  Function implementing the LED_TASK thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_LEDTASKEntry */
void LEDTASKEntry(void const * argument)
{
  /* USER CODE BEGIN LEDTASKEntry */
  EventBits_t r_event;
  /* Infinite loop */
  for(;;)
  {
      r_event = xEventGroupWaitBits(Event_Handle, KEY1_EVENT | KEY2_EVENT,
              pdTRUE, /*退出时清楚事件位*/
              pdTRUE, /*满足感兴趣的所有事件*/
              portMAX_DELAY /*一直等*/);

      if((r_event & (KEY1_EVENT | KEY2_EVENT)) == (KEY1_EVENT | KEY2_EVENT)){
          //如果接受完整并且正确
          printf("KEY1与KEY2都摁下\n");
          HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
      }
      else{
          printf("事件错误\n");
      }
    osDelay(1);
  }
  /* USER CODE END LEDTASKEntry */
}

/* USER CODE BEGIN Header_KEYTASKEntry */
/**
* @brief Function implementing the KEY_TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KEYTASKEntry */
void KEYTASKEntry(void const * argument)
{
  /* USER CODE BEGIN KEYTASKEntry */
  /* Infinite loop */
  for(;;)
  {
      if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_RESET){
          printf("KEY1 被摁下\n");
          xEventGroupSetBits(Event_Handle, KEY1_EVENT);
      }
      if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_RESET){
          printf("KEY2 被摁下\n");
          xEventGroupSetBits(Event_Handle, KEY2_EVENT);
      }
    osDelay(20);
  }
  /* USER CODE END KEYTASKEntry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
