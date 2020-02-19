//
// Created by Wu Alex on 2020/2/18.
//

#ifndef NEWFREERTOS_TEST_H
#define NEWFREERTOS_TEST_H

#include "list.h"
#include "task.h"

void ListInsertTest();

/************** task 实验 ******************/
//裸机系统中两个变量轮流翻转
uint32_t flag1;
uint32_t flag2;

/* 软件延时，不必纠结具体的时间 */
void delay( uint32_t count );
void BareBoardVarChange();

/* 任务1 */
void Task1_Entry(void *p_arg);
/* 任务2 */
void Task2_Entry(void *p_arg);

//任务控制块定义
/* 定义任务控制块 */
TCB_t Task1TCB;
TCB_t Task2TCB;




#endif //NEWFREERTOS_TEST_H
