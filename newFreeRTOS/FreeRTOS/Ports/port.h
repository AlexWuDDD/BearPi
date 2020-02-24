//
// Created by Wu Alex on 2020/2/24.
//
#ifndef NEWFREERTOS_PORT_H
#define NEWFREERTOS_PORT_H

#include <stdbool.h>
#include "portmacro.h"
#include "task.h"
#define portINITIAL_XPSR (0x01000000)
#define portSTART_ADDRESS_MASK ((StackType_t)0xfffffffeUL)


#define portNVIC_SYSPRI2_REG

StackType_t *pxPortInitialiseStack(StackType_t *pxTopOfStack, TaskFunction_t pxCode, void* pvParameters);
bool xPortStartScheduler();

#endif //NEWFREERTOS_PORT_H
