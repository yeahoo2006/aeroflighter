/* 
 * File:   api.h
 * Author: Will.he @ cn.abb.com
 * Application Interface for AeroFlight
 * Created on March 4, 2015, 1:48 PM
 */
#include "drv_pin_map.h"
#include "pic18f46k22.h"
#ifndef API_H
#define	API_H
#define ACC_ADDR    0x53
#define ACC_READ    0xA7
#define ACC_WRITE   0xA6
#define ACC_DATA_FORMAT 0x31
#define BW_RATE     0x2C
#define INT_ENABLE  0x2E
#define POWER_CTL   0x2D
#define GYO_ADDR    0x69  // gyroscope sensor address
#define GYO_READ    0xD1
#define GYO_WRITE   0xD0
#define GEO_ADDR    0x1E  // geomagnetism sensor address
#define GEO_READ    0x3D
#define GEO_WRITE   0x3C
#define ACC_X0      0x32  // accleration sensor address
#define ACC_X1      0x33
#define ACC_Y0      0x34
#define ACC_Y1      0x35
#define ACC_Z0      0x36
#define ACC_Z1      0x37
#define DEVID       0x00
extern void DRV_init(void);
extern void DRV_isr_init();
extern void DRV_osc_init();
extern void DRV_tmr_init();
extern void DRV_init(void);
extern void DRV_I2C_init(void);
extern void test(void);

#endif	/* API_H */

