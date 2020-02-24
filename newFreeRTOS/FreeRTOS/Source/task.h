//
// Created by Wu Alex on 2020/2/19.
//

#ifndef NEWFREERTOS_TASK_H
#define NEWFREERTOS_TASK_H

#include "portmacro.h"
#include "list.h"
#include "projdef.h"

typedef struct tskTaskControlBlock
{
    volatile StackType_t  *pxTopOfStack;  /*栈顶*/
    ListItem_t  xStateListItem;         /*任务节点， 通过这个节点，可以将任务控制块挂接到各种链表中。这个节点就类似于晾衣架的钩子*/
    StackType_t *pxStack;                /*任务栈起始地址*/
    /* 任务名称，字符串形式*/
    char pcTaskName[configMax_TASK_NAME_LEN];
}tskTCB;
typedef tskTCB TCB_t;

/* 任务句柄 */
typedef void* TaskHandle_t;

//多任务系统中，有多少个任务就需要定义多少个任务栈
#define TASK1_STACK_SIZE    128
extern StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE 128
extern StackType_t Task2Stack[TASK2_STACK_SIZE];

/* 实现任务创建函数 */
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
TaskHandle_t xTaskCreateStatic(
        TaskFunction_t pxTaskCode,          //任务入口
        const char* const pcName,           //任务名称，字符串形式方便调试
        const uint32_t ulStackDepth,        //任务栈大小，单位是字
        void *const pvParameters,           //任务形参
        StackType_t *const pxStackBuffer,  //任务栈起始地址
        TCB_t * const pxTaskBuffer);        //任务控制块指针
#endif

/*任务就绪列表*/
extern List_t pxReadyTasksLists[configMAX_PRIORITIES];

/*就绪列表初始化*/
void prvInitialiseTaskLists(void);

/*启动调度器*/
void vTaskStartScheduler(void);

/*全局指针，用于指向当前正在运行或者即将要运行的任务的任务控制块*/
extern TCB_t *pxCurrent;


#endif //NEWFREERTOS_TASK_H
