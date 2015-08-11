/* 
 * File:   I2C.h
 * Author: Will
 *I2C drive head from the Github
 * Created on 2015-3-2, 10:15
 */
#include "drv_compiler.h"
#include "api.h"

#ifndef I2C_H
#define	I2C_H
extern boolean I2C_Read_Reg(uint8_t add,uint8_t reg, uint8_t* rxPtr);
extern boolean I2C_Write_Reg(uint8_t add,uint8_t reg, uint8_t data);
//extern BOOL I2cWriteRegLoop(uint8_t add,uint8_t reg, uint8_t* data, uint8_t len);
// extern bool I2cReadRegisterLoop(uint8_t add,uint8_t reg, uint8_t* rxPtr, uint8_t len);
//extern void I2cTest(void);
#endif

