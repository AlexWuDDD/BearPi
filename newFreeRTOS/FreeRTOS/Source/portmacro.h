//
// Created by Wu Alex on 2020/2/14.
//

#ifndef NEWFREERTOS_PORTMACRO_H
#define NEWFREERTOS_PORTMACRO_H

#include <stdio.h>
#include <stddef.h>
#include "FreeRTOSConfig.h"

/* 数据类型重定义 */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   long

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t TickType_t;
#define portMAX_DELAY (TickType_t) 0xffff
#else
typedef uint32_t TickType_t;
#define portMAX_DELAY (TickType_t) 0xffffffffUL
#endif


#endif //NEWFREERTOS_PORTMACRO_H
