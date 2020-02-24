//
// Created by Wu Alex on 2020/2/19.
//
#include "port.h"

static void prvTaskExitError(void)
{
    /*函数停止在这里*/
    for(;;);
}

StackType_t *pxPortInitialiseStack(StackType_t *pxTopOfStack, TaskFunction_t pxCode, void* pvParameters)
{
    /* 异常发生时，自动加载到CPU寄存器的内容 */
    pxTopOfStack--;
    *pxTopOfStack = portINITIAL_XPSR;
    pxTopOfStack--;
    *pxTopOfStack == ((StackType_t)pxCode)&portSTART_ADDRESS_MASK;
    pxTopOfStack--;
    *pxTopOfStack = (StackType_t)prvTaskExitError;
    pxTopOfStack -= 5;
    *pxTopOfStack = (StackType_t)pvParameters;

    /*异常发生时，手动加载到CPU寄存器的内容*/
    pxTopOfStack -= 8;
    return pxTopOfStack;
}

bool xPortStartScheduler(){
    return true;
}

