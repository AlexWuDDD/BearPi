//
// Created by Wu Alex on 2020/1/2.
//

#ifndef I2CEEPROM_AT24C02_I2C_DRV_H
#define I2CEEPROM_AT24C02_I2C_DRV_H

#include "i2c.h"

#define AT24C02_ADDR_WRITE 0xA0
#define AT24C02_ADDR_READ 0xA1

/**
 * @brief        AT24C02任意地址写一个字节数据
 * @param        addr —— 写数据的地址（0-255）
 * @param        dat  —— 存放写入数据的地址
 * @retval        成功 —— HAL_OK
*/
uint8_t At24c02_Write_Byte(uint16_t addr, uint8_t* dat);

/**
 * @brief        AT24C02任意地址读一个字节数据
 * @param        addr —— 读数据的地址（0-255）
 * @param        read_buf —— 存放读取数据的地址
 * @retval        成功 —— HAL_OK
*/
uint8_t At24c02_Read_Byte(uint16_t addr, uint8_t* read_buf);

/**
 * @brief        AT24C02任意地址连续写多个字节数据
 * @param        addr —— 写数据的地址（0-255）
 * @param        dat  —— 存放写入数据的地址
 * @retval        成功 —— HAL_OK
*/
uint8_t At24c02_Write_Amount_Byte(uint16_t addr, uint8_t* dat, uint16_t size);

/**
 * @brief        AT24C02任意地址连续读多个字节数据
 * @param        addr —— 读数据的地址（0-255）
 * @param        dat  —— 存放读出数据的地址
 * @retval        成功 —— HAL_OK
*/
uint8_t At24c02_Read_Amount_Byte(uint16_t addr, uint8_t* recv_buf, uint16_t size);

#endif //I2CEEPROM_AT24C02_I2C_DRV_H
