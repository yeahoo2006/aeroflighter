/* 
 * File:   motor.c
 * Author: Will-liang.he@cn.abb.com     
 *
 * Created on 2015/07/21
 */

#include <stdio.h>
#include <stdlib.h>
#include "pic18f46k22.h"
#include "drv_pin_map.h"
#include "drv_isr.h"



/*Init the Motor_0*/
/*
 * (65536 * 9 + 50176) * 4 / 64000000 = 0.04(Second) => 9, 0xC400
 * (65536 * 8 + 8992) * 4 / 64000000 = 0.03333(Second) => 8, 0x2320
 */

void init_motor(){
PIN_DIR_MOTOR = PIN_OUTPUT;
PIN_WT_MOTOR = PIN_DATA_LOW;
}

