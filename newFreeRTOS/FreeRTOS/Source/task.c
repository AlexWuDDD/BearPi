//
// Created by Wu Alex on 2020/2/19.
//

#include "task.h"


static void prvInitialiseNewTask(TaskHandle_t pxTaskCode,
        const char* const pcName,
        const uint32_t ulStackDepth,
        void * const pvParameters,
        TaskHandle_t * const pxCreatedTask,
        TCB_t *pxNewTCB )
{
    StackType_t *pxTopOfStack;
    UBaseType_t X;

    /* 获取栈顶地址 */
    pxTopOfStack = pxNewTCB->pxStack + (ulStackDepth - (uint32_t)1);
    /* 向下做8字节对齐 */
    pxTopOfStack = (StackType_t*)(((uint32_t)pxTopOfStack)&(~((uint32_t)0x0007)));
    /* 将任务的名字存储在TCB中 */
    for(x=(UBaseType_t)0; x < (UBaseType_t)configMax_TASK_NAME_LEN; ++x){
        pxNewTCB->pcTaskName[x] = pcName[x];

        if(pcName[x] == 0x00){
            break;
        }
    }

    pxNewTCB->pcTaskName[configMax_TASK_NAME_LEN-1]='\0';

    /*初始化TCB中的xStateListItem节点*/
    vListInitialiseItem(&(pxNewTCB->xStateListItem));
    /*设置xStateListItem节点的拥有者*/
    listSET_ITEM_OWNER(&(pxNewTCB->xStateListItem), pxNewTCB);

    /* 初始化任务栈 */
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxTopOfStack, pxTaskCode, pvParameters);

    /* 让任务句柄指向任务控制块 */
    if ((void*)pxCreatedTask != NULL){
        *pxCreatedTask = (TaskHandle_t)pxNewTCB;
    }

}

TaskHandle_t xTaskCreateStatic(
        TaskFunction_t pxTaskCode,          //任务入口
        const char* const pcName,           //任务名称，字符串形式方便调试
        const uint32_t ulStackDepth,        //任务栈大小，单位是字
        void *const pvParameters,           //任务形参
        StackType_t *const pxStackBuffer,  //任务栈起始地址
        TCB_t * const pxTaskBuffer)        //任务控制块指针
{
    TCB_t *pxNewTCB;
    TaskHandle_t xReturn;

    if( ( pxTaskBuffer != NULL ) && ( pxStackBuffer != NULL )){
        pxNewTCB = (TCB_t*) pxTaskBuffer;
        pxNewTCB->pxStack = (StackType_t*) pxStackBuffer;

        /* 创建新的任务 */
        prvInitialiseNewTask(pxTaskCode, pcName, ulStackDepth, pvParameters, &xReturn, pxNewTCB);
    }
    else{
        xReturn = NULL;
    }
    /* 返回任务句柄， 如果任务创建成功， 此时xReturn应该指向任务控制块 */
    return xReturn;
}
