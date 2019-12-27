//
// Created by Wu Alex on 2019/12/27.
//

#ifndef QSPIFLASH_SPI_FLASH_H
#define QSPIFLASH_SPI_FLASH_H

#include "main.h"
#include "quadspi.h"

/*
MCU 通过向 SPI Flash 发送各种命令
 来读写 SPI Flash内部的寄存器，所以这种裸机驱动，
 首先要先宏定义出需要使用的命令，
 然后利用 HAL 库提供的库函数，封装出三个底层函数，便于移植：

向 SPI Flash 发送命令的函数
向 SPI Flash 发送数据的函数
从 SPI Flash 接收数据的函数
*/

#define ManufactDeviceID_CMD 0x90
#define READ_STATU_REGISTER_1   0x05
#define READ_STATU_REGISTER_2   0x35
#define READ_DATA_CMD            0x03
#define WRITE_ENABLE_CMD        0x06
#define WRITE_DISABLE_CMD        0x04
#define SECTOR_ERASE_CMD        0x20
#define CHIP_ERASE_CMD            0xc7
#define PAGE_PROGRAM_CMD        0x02


/**
 * @brief        向SPI Flash发送指令
 * @param        instruction —— 要发送的指令
 * @param        address     —— 要发送的地址
 * @param        dummyCycles —— 空指令周期数
 * @param        instructionMode —— 指令发送模式
 * @param        addressMode —— 地址发送模式
 * @param        addressSize —— 地址大小
 * @param        dataMode    —— 数据发送模式
 * @retval        成功返回HAL_OK
*/

HAL_StatusTypeDef QSPI_Send_Command(uint32_t instruction,
                                    uint32_t address,
                                    uint32_t dummyCycles,
                                    uint32_t instructionMode,
                                    uint32_t addressMode,
                                    uint32_t addressSize,
                                    uint32_t dataMode);

/**
* @brief    QSPI发送指定长度的数据
* @param    buf  —— 发送数据缓冲区首地址
* @param    size —— 要发送数据的字节数
 * @retval    成功返回HAL_OK
 */
HAL_StatusTypeDef QSPI_Transmit(uint8_t* send_buf, uint32_t size);

/**
 * @brief   QSPI接收指定长度的数据
 * @param   buf  —— 接收数据缓冲区首地址
 * @param   size —— 要接收数据的字节数
 * @retval    成功返回HAL_OK
 */
HAL_StatusTypeDef QSPI_Receive(uint8_t* recv_buf, uint32_t size);


/*
 * 读取Manufacture ID和Device ID
 * 读取 Flash 内部这两个ID有两个作用：
 * 检测SPI Flash是否存在
 * 可以根据ID判断Flash具体型号
 * */

/**
 * @brief   读取Flash内部的ID
 * @param   none
 * @retval    成功返回device_id
 */
uint16_t W25QXX_ReadID(void);
/**
 * @brief    读取SPI FLASH数据
 * @param   dat_buffer —— 数据存储区
 * @param   start_read_addr —— 开始读取的地址(最大32bit)
 * @param   byte_to_read —— 要读取的字节数(最大65535)
 * @retval  none
 */
void W25QXX_Read(uint8_t* dat_buffer,
        uint32_t start_read_addr,
        uint16_t byte_to_read);

/**
 * @brief    读取W25QXX的状态寄存器，W25Q64一共有2个状态寄存器
 * @param     reg  —— 状态寄存器编号(1~2)
 * @retval    状态寄存器的值
 */
uint8_t W25QXX_ReadSR(uint8_t reg);
/**
 * @brief    阻塞等待Flash处于空闲状态
 * @param   none
 * @retval  none
 */
void W25QXX_Wait_Busy(void);

/*
 * Flash 芯片默认禁止写数据，
 * 所以在向 Flash 写数据之前，
 * 必须发送命令开启写使能
 * */

/**
 * @brief    W25QXX写使能,将S1寄存器的WEL置位
 * @param    none
 * @retval
 */
void W25QXX_Write_Enable(void);

/**
 * @brief    W25QXX写禁止,将WEL清零
 * @param    none
 * @retval    none
 */
void W25QXX_Write_Disable(void);

/*SPI Flash有个特性：
 * 数据位可以由1变为0，
 * 但是不能由0变为1。
 */
/**
 * @brief    W25QXX擦除一个扇区
 * @param   sector_addr    —— 扇区地址 根据实际容量设置
 * @retval  none
 * @note    阻塞操作
 */
void W25QXX_Erase_Sector(uint32_t sector_addr);

/**
 * @brief    页写入操作
 * @param    dat —— 要写入的数据缓冲区首地址
 * @param    WriteAddr —— 要写入的地址
 * @param   byte_to_write —— 要写入的字节数（0-256）
 * @retval    none
 */
void W25QXX_Page_Program(uint8_t* dat, uint32_t WriteAddr, uint16_t byte_to_write);


#endif //QSPIFLASH_SPI_FLASH_H
