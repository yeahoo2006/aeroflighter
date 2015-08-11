/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_api.c
 * @brief   API of the DRIVER layer.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    Apr 12, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  Apr 12, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */

#include "api.h"
#include "drv_compiler.h"


/**
 * @brief   Initialize all drivers.\n
 *
 * @date    Apr 12, 2013
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 */
void DRV_init(void){
     /* Init watchdog timer */
    DRV_WDT_DISABLE();
    /* Initialize all drivers */
    //DRV_disable_ints();
    di();
    DRV_isr_init(); /* Keep interrupt initialization on top */
    DRV_osc_init();
    PEIE = 0b1; /* Peripheral Interrupt Enable */
   DRV_enable_ints();
   DRV_usart_init();
   DRV_I2C_init();
   DRV_WDT_ENABLE();
}

