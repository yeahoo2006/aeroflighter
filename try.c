/* 
 * File:   try.c
 * Author: Administrator
 *
 * Created on 2015?7?26?, ??4:23
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

#include "lib_rprintf.h"
uint8_t ab_received_buf[8];
#define CMD_PROMPT {rprintf("\nFlighter> ");}

void Try(){
//rprintf("I'm Rock");
//for(;;)
//{
  //  CMD_PROMPT;
//while(!DRV_usart_read_cmd(ab_received_buf, 1));
//rprintf("%d",ab_received_buf[0]);
//    switch(ab_received_buf[0])
//	{
//            case 'E':
//                rprintf("It is empty");
//		break;
//            case 'F':
//                 rprintf("It is Full");
//        break;
//            default:
//        break;    
//        }
//}
}