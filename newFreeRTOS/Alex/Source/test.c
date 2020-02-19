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
