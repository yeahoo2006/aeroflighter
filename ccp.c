/* 
 * File:   ccp.c
 * Author: Administrator
 *
 * Created on 2015?7?21?, ??8:30
 */

#include <stdio.h>
#include <stdlib.h>
#include "pic18f46k22.h"
static void _ccp1_init(void)
{
    /* Configure CCP1 as compare mode */
    CCP1CON = 0b00001010;
    /*          ||||++++---- CCP1M: CCP1 Mode Select
     *          ||||                1010: Compare mode: generate software interrupt on compare match
     *          ||++-------- DC6B: Two LSBs of the PWM duty cycle. [NOT IN USE]
     *          ++---------- Unimiplemented [NOT IN USE]
     */

    /* Choose TIMER1 */
    CCPTMRS0bits.C1TSEL = 0b00;

    /* Disable interrupt */
    CCP1IE = 0b0;

    /* Clear interrupt flat */
    CCP1IF = 0b0;

    /* CCPR6H:L 0x0000 */
    CCPR1L = 0x00;
    CCPR1H = 0x00;
}
void DRV_ccp_init(void)
{
    _ccp1_init(); /* For MODBUS timer compare */
}
