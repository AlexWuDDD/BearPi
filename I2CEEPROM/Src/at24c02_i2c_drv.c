//
// Created by Wu Alex on 2020/1/2.
//

#include "at24c02_i2c_drv.h"


uint8_t At24c02_Write_Byte(uint16_t addr, uint8_t* dat){
    return HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
            I2C_MEMADD_SIZE_8BIT, dat, 1, 0xFFFF);
}

uint8_t At24c02_Read_Byte(uint16_t addr, uint8_t* read_buf){
    return HAL_I2C_Mem_Read(&hi2c1, AT24C02_ADDR_READ, addr,
            I2C_MEMADD_SIZE_8BIT, read_buf, 1, 0xFFFF);
}

uint8_t At24c02_Write_Amount_Byte(uint16_t addr, uint8_t* dat, uint16_t size){
    uint8_t i = 0;
    uint16_t  cnt = 0; //写入字节计数

    /*对于起始地址，有两种情况，分别判断*/
    if(0 == addr % 8){
        /*起始地址刚好是页开始地址*/
        /*对于写入的字节数，有两种情况，分别判断*/
        if(size <= 8){
            //写入的字节数不大于一页，直接写入
            return HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                    I2C_MEMADD_SIZE_8BIT, dat, size, 0xFFFF);
        }
        else{
            //写入的字节数大于一页，先将整页循环写入
            for(i=0;i<size/8;++i){
                HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                        I2C_MEMADD_SIZE_8BIT, &dat[cnt], 8, 0xFFFF);
                addr += 8;
                cnt += 8;
                HAL_Delay(50); //这个要加 不然会写失败
            }
            //将剩余的字节写入
            return HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                    I2C_MEMADD_SIZE_8BIT,&dat[cnt], size-cnt, 0xFFFF);
        }
    }
    else{
        /*起始地址偏离页开始地址*/
        /*对于写入的字节数，有两种情况吗分别判断*/
        if(size <= (8-addr%8)){
            /*该页可以写完*/
            return HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                    I2C_MEMADD_SIZE_8BIT, dat, size, 0xFFFF);
        }
        else{
            /*该页写不完*/
            //先将该页写完
            cnt += (8 - addr%8);
            HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                    I2C_MEMADD_SIZE_8BIT, dat, cnt, 0xFFFF);
            addr += cnt;
            HAL_Delay(50);

            //循环写整页数据
            for(i=0;i< (size-cnt)/8 ;++i){
                HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                                  I2C_MEMADD_SIZE_8BIT, &dat[cnt], 8, 0xFFFF);
                addr += 8;
                cnt += 8;
                HAL_Delay(50);
            }
            //将剩余的字节写入
            return HAL_I2C_Mem_Write(&hi2c1, AT24C02_ADDR_WRITE, addr,
                                     I2C_MEMADD_SIZE_8BIT,&dat[cnt], size-cnt, 0xFFFF);
        }
    }

}

uint8_t At24c02_Read_Amount_Byte(uint16_t addr, uint8_t* recv_buf, uint16_t size){

    return HAL_I2C_Mem_Read(&hi2c1, AT24C02_ADDR_READ, addr,
            I2C_MEMADD_SIZE_8BIT, recv_buf, size, 0xFFFF);
}