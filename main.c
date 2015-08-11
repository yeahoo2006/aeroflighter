/* 
 * File:   main.c
 * Author: Administrator
 *
 * Created on 2015?3?10?, ??1:23
 */

#include <stdio.h>
#include <stdlib.h>
#include "api.h"
#include "data.h"
#include "drv_usart.h"
#include "pic18f46k22.h"
#include "test.h"
#include "I2C.h"
#include "motor.h"
#include "isr.h"
#include "lib_rprintf.h"

void main(void) {
DRV_init();
//if(_init_acc());
//if(_init_geoscope());
for(;;){
Try();
}
}