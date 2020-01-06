//
// Created by Wu Alex on 2020/1/6.
//

#ifndef I2CLIGHTSENSOR_BH1750_H
#define I2CLIGHTSENSOR_BH1750_H

#include "stdio.h"
#define BH1750_ADDR_WRITE 0X46
#define BH1750_ADDR_READ 0x47


typedef enum
{
    POWER_OFF_CMD   =   0x00,   //断电：无激活状态
    POWER_ON_CMD    =   0x01,   //通电：等待测量指令
    RESET_REGISTER  =   0x07,   //重置数字寄存器（在断电状态下不起作用）
    CONT_H_MODE     =   0x10,   //连续H分辨率模式：在11x分辨率下开始测量，测量时间120ms
    CONT_H_MODE2    =   0x11,   //连续H分辨率模式2：在0.51x分辨率下开始测量，测量时间120ms
    CONT_L_MODE     =   0x13,   //连续L分辨率模式：在411分辨率下开始测量，测量时间16ms
    ONCE_H_MODE     =   0x20,   //一次高分辨率模式：在11x分辨率下开始测量，测量时间120ms，测量后自动设置为断电模式
    ONCE_H_MODE2    =   0x21,   //一次高分辨率模式2：在0.51x分辨率下开始测量，测量时间120ms，测量后自动设置为断电模式
    ONCE_L_MODE     =   0x23    //一次低分辨率模式：在411x分辨率下开始测量，测量时间16ms，测量后自动设置为断电模式
} BH1750_MODE;


/**
 * @brief    向BH1750发送一条指令
 * @param    cmd —— BH1750工作模式指令（在BH1750_MODE中枚举定义）
 * @retval    成功返回HAL_OK
*/
uint8_t    BH1750_Send_Cmd(BH1750_MODE cmd);

/**
 * @brief    从BH1750接收一次光强数据
 * @param    dat —— 存储光照强度的地址（两个字节数组）
 * @retval    成功 —— 返回HAL_OK
*/
uint8_t BH1750_Read_Dat(uint8_t* dat);

/**
 * @brief    将BH1750的两个字节数据转换为光照强度值（0-65535）
 * @param    dat  —— 存储光照强度的地址（两个字节数组）
 * @retval    成功 —— 返回光照强度值
*/
uint16_t BH1750_Dat_To_Lux(uint8_t* dat);

#endif //I2CLIGHTSENSOR_BH1750_H
