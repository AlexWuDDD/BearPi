//
// Created by Wu Alex on 2020/1/7.
//

#ifndef TEMPERATUREHUMILITY_PRINTFREDIRECTION_H
#define TEMPERATUREHUMILITY_PRINTFREDIRECTION_H

#if 1
#include <stdio.h>

int _write(int fd, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xFFFF);
    return len;
}
#endif

#endif //TEMPERATUREHUMILITY_PRINTFREDIRECTION_H
