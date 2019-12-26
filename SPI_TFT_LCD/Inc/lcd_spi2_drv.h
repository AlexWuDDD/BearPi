//
// Created by Wu Alex on 2019/12/26.
//

#ifndef SPI_TFT_LCD_LCD_SPI2_DRV_H
#define SPI_TFT_LCD_LCD_SPI2_DRV_H

#include "main.h"

//使用ASCII字符显示请打开该宏(值设为1)
#define	USE_ASCII_FONT_LIB			1

//使用图片显示请打开该宏(值设为1)
#define USE_PICTURE_DISPLAY			1



#define    LCD_PWR(n)   (n?\
    HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_SET):\
    HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_RESET))
#define    LCD_WR_RS(n) (n?\
    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_SET):\
    HAL_GPIO_WritePin(LCD_WR_RS_GPIO_Port,LCD_WR_RS_Pin,GPIO_PIN_RESET))
#define    LCD_RST(n)   (n?\
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET):\
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET))


//LCD屏幕分辨率定义
#define LCD_Width   240
#define LCD_Height  240
//颜色定义
#define WHITE   0xFFFF    //白色
#define YELLOW  0xFFE0    //黄色
#define BRRED   0XFC07    //棕红色
#define PINK    0XF81F    //粉色
#define RED     0xF800    //红色
#define BROWN   0XBC40    //棕色
#define GRAY    0X8430    //灰色
#define GBLUE   0X07FF    //兰色
#define GREEN   0x07E0    //绿色
#define BLUE    0x001F    //蓝色
#define BLACK   0x0000    //黑色

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Clear(uint16_t color);
void LCD_Init(void);

void LCD_Draw_ColorPoint(uint16_t x, uint16_t y,uint16_t color);
void LCD_Draw_ColorLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_ColorRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_ColorCircle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
#if USE_ASCII_FONT_LIB
void LCD_ShowChar(uint16_t x, uint16_t y, char ch, uint16_t back_color, uint16_t font_color, uint8_t font_size);
void LCD_ShowCharStr(uint16_t x, uint16_t y, uint8_t max_width, char* str, uint16_t back_color, uint16_t font_color, uint8_t font_size);
#endif /* USE_ASCII_FONT_LIB */
void LCD_Draw_ColorSixPointStar(uint16_t x, uint16_t y, uint8_t r, uint16_t color);
#if USE_PICTURE_DISPLAY
void LCD_Show_Image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p);
#endif /*USE_PICTURE_DISPLAY */



#endif //SPI_TFT_LCD_LCD_SPI2_DRV_H
