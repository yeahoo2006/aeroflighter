/* 
 * File:   data.h
 * Author: CNWIHE1
 *
 * Created on March 4, 2015, 3:38 PM
 */
#include "drv_compiler.h"
#ifndef DATA_H
#define	DATA_H
#define  round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) 
uint8_t var1;
uint8_t var2;
uint8_t var4;
uint8_t var5;
uint8_t var7;
uint8_t var8;
int16_t var3;
int16_t var6;
int16_t var9;
uint8_t var10;
uint8_t var11;
int16_t var12;
uint8_t var13;
uint8_t var15;
uint8_t var16;
int16_t var17;
uint8_t var18;
uint8_t var19;
int16_t var20;
int16_t off_acc_z;
int16_t off_acc_x;
int16_t off_acc_y;
int16_t temp_var3=0;
int16_t temp_var6=0;
int16_t temp_var9=0;
int16_t calib_acc_z;
int16_t calib_acc_y;
int16_t calib_acc_x;
extern boolean _init_acc();
uint8_t  device;
extern uint16_t Calib_acc_z();
extern uint16_t Calib_acc_y();
extern uint16_t Calib_acc_x();
extern void obtain_gescope_x();
extern void obtain_gescope_y();
extern void obtain_gescope_z();
#endif	/* DATA_H */

