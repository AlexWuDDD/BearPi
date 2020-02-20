//
// Created by Wu Alex on 2020/2/18.
//

#include "test.h"


void ListInsertTest()
{
    struct xLIST List_Test;
    struct xLIST_ITEM List_Item1;
    struct xLIST_ITEM List_Item2;
    struct xLIST_ITEM List_Item3;

    vListInitialise(&List_Test);
    vListInitialiseItem(&List_Item1);
    List_Item1.xItemValue = 1;

    vListInitialiseItem(&List_Item2);
    List_Item2.xItemValue = 2;

    vListInitialiseItem(&List_Item3);
    List_Item3.xItemValue = 3;

    vListInsert(&List_Test, &List_Item3);
    vListInsert(&List_Test, &List_Item1);
    vListInsert(&List_Test, &List_Item2);

    struct xLIST_ITEM const * head = listGET_HEAD_ENTRY(&List_Test);
    printf("index: %ld\n", head->xItemValue);

    struct xLIST_ITEM const * marker = listGET_END_MARKER(&List_Test);
    printf("head: %ld, end: %ld\n", marker->pxNext->xItemValue, marker->pxPrevious->xItemValue);
}

void delay( uint32_t count )
{
    for(;count!=0;count--);
}

void BareBoardVarChange()
{
    for(;;){
        flag1=1;
        delay(100);
        flag1=0;
        delay(100);

        flag2=1;
        delay(100);
        flag2=0;
        delay(100);
    }
}

void Task1_Entry(void *p_arg)
{
    for(;;) {
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);
    }
}

void Task2_Entry(void *p_arg)
{
    for(;;) {
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);
    }
}

void taskTest1()
{
    /* 初始化与任务相关的列表*/
    prvInitialiseTaskLists();

    TaskHandle_t Task1_Handle = xTaskCreateStatic((TaskFunction_t)Task1_Entry, (char*)"Task1",
            (uint32_t)TASK1_STACK_SIZE,
            (void*)NULL, (StackType_t*)Task1Stack, (TCB_t*)&Task1TCB);

    /*将任务添加到就绪列表*/
    vListInsertEnd(&(pxReadyTasksLists[1]), &(((TCB_t*)&Task1TCB)->xStateListItem));

    TaskHandle_t Task2_Handle = xTaskCreateStatic((TaskFunction_t)Task2_Entry, (char*)"Task2",
            (uint32_t)TASK2_STACK_SIZE,
            (void*)NULL, (StackType_t*)Task2Stack, (TCB_t*)&Task2TCB);

    /*将任务添加到就绪列表*/
    vListInsertEnd(&(pxReadyTasksLists[2]), &(((TCB_t*)&Task2TCB)->xStateListItem))
}