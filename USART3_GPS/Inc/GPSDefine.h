//
// Created by Wu Alex on 2020/2/12.
//

#ifndef USART3_GPS_GPSDEFINE_H
#define USART3_GPS_GPSDEFINE_H

#include <stdio.h>
#include <string.h>

/***************************************************\
*GPS NMEA-0183协议重要参数结构体定义
*卫星信息
\***************************************************/
__packed typedef struct
{
    uint32_t latitude_bd;                   //纬度   分扩大100000倍，实际要除以100000
    uint8_t nshemi_bd;                      //北纬/南纬,N:北纬;S:南纬
    uint32_t longitude_bd;            //经度 分扩大100000倍,实际要除以100000
    uint8_t ewhemi_bd;                      //东经/西经,E:东经;W:西经
}gps_msg;

/* E53_ST1传感器数据类型定义 ------------------------------------------------------------*/
typedef struct
{
    float    Longitude;             //经度
    float    Latitude;        //纬度
} E53_ST1_Data_TypeDef;


extern gps_msg  gpsMsg;
extern E53_ST1_Data_TypeDef E53_ST1_Data;
extern unsigned char gps_uart[1000];

uint8_t NMEA_Comma_Pos(uint8_t *buf,uint8_t cx);
uint32_t NMEA_Pow(uint8_t m,uint8_t n);
int NMEA_Str2num(uint8_t *buf,uint8_t*dx);
void NMEA_BDS_GPRMC_Analysis(gps_msg *gpsmsg,uint8_t *buf);
void E53_ST1_Read_Data(void);

#endif //USART3_GPS_GPSDEFINE_H
