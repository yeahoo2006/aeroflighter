/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_tmr.c
 * @brief   Timer 0/1/2/4/6 driver.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    May 23, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  May 23, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */

#include "api.h"
#include "pic18f46k22.h"

/**
 * @brief   Timer1 initialization.\n
 *          Timer1 is used for AI sampling.
 * @date    Jun 8, 2013
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 */
void _tmr0_init(void)
{
    T1CON = 0b10000001;
    /*        |||||+++---- Timer0 Prescaler Select bits
     *        |||||                 001: 1/4 prescale
     *        ||||+------- PSA: Timer0 Prescaler Assignment bit
     *                              0=Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
     *        |||+-------- T0SE: Timer0 Source Edge Select bit
     *        ||+--------- T0CS: Timer0 Clock Source Select bit
     *        |+---------- T08BIT: Timer0 8-bit/16-bit Control bit
     *        ||                   0 = Timer0 is configured as a 16-bit timer/counter
     *        +----------- TMR0ON: Timer0 On/Off Control bit
     *                             1 = Enables Timer0
     */
}



void _tmr1_init(void)
{
    T1CON = 0b00001001;
    /*        |||||||+---- TMR1ON: Timer 1 On
     *        |||||||              1: Enable Timer 1
     *        ||||||+----- T1RD16: 16-bit Read/Write Mode Enable [NOT IN USE]
     *        |||||+------ T1SYNC: Timer 1 External Clock Input Synchronization Control [NOT IN USE]
     *        ||||+------- T1SOSCEN: Secondary Oscillator Enable Control [NOT IN USE]
     *        ||++-------- T1CKPS: Timer 1 Input Clock Prescale Select
     *        ||                   00: Prescale value 1:1
     *        ++---------- TMR1CS: Timer1 Clock Source Select
     *                             00: Instruction Clock (FOSC/4)
     */

    T1GCON = 0b00000000;
    /*         ||||||++---- T1SS: Timer 1 Gate Source Select [NOT IN USE]
     *         |||||+------ T1GVAL: Timer 1 Gate Current State [NOT IN USE]
     *         ||||+------- T1GGO/DONE: Timer 1 Gate Single-Pulse Acquisition Status [NOT IN USE]
     *         |||+-------- T1GSPM: Timer 1 Gate Single-Pulse Mode [NOT IN USE]
     *         ||+--------- T1GTM: Timer 1 Gate Toggle Mode [NOT IN USE]
     *         |+---------- T1GPOL: Timer 1 Gate Polarity [NOT IN USE]
     *         +----------- TMR1GE: Timer 1 Gate Enable
     *                              0: Timer 1 counts regardless of Timer 1 gate function
     */

    /* Disable Timer1 gate */
    TMR1GE = 0b0;
}

void _tmr3_init(void)
{
    T3CON = 0b00001001;
    /*        |||||||+---- TMR1ON: Timer 1 On
     *        |||||||              1: Enable Timer 1
     *        ||||||+----- T3RD16: 16-bit Read/Write Mode Enable [NOT IN USE]
     *        |||||+------ T3SYNC: Timer 1 External Clock Input Synchronization Control [NOT IN USE]
     *        ||||+------- T3SOSCEN: Secondary Oscillator Enable Control [NOT IN USE]
     *        ||++-------- T3CKPS: Timer 1 Input Clock Prescale Select
     *        ||                   00: Prescale value 1:1
     *        ++---------- TMR3CS: Timer1 Clock Source Select
     *                             00: Instruction Clock (FOSC/4)
     */

    T3GCON = 0b00000000;
    /*         ||||||++---- T3SS: Timer 1 Gate Source Select [NOT IN USE]
     *         |||||+------ T3GVAL: Timer 1 Gate Current State [NOT IN USE]
     *         ||||+------- T3GGO/DONE: Timer 1 Gate Single-Pulse Acquisition Status [NOT IN USE]
     *         |||+-------- T3GSPM: Timer 1 Gate Single-Pulse Mode [NOT IN USE]
     *         ||+--------- T3GTM: Timer 1 Gate Toggle Mode [NOT IN USE]
     *         |+---------- T3GPOL: Timer 1 Gate Polarity [NOT IN USE]
     *         +----------- TMR3GE: Timer 1 Gate Enable
     *                              0: Timer 1 counts regardless of Timer 1 gate function
     */

    /* Disable Timer1 gate */
    TMR3GE = 0b0;
}


void _tmr5_init(void)
{
    T5CON = 0b00001001;
    /*        |||||||+---- TMR1ON: Timer 1 On
     *        |||||||              1: Enable Timer 1
     *        ||||||+----- T5RD16: 16-bit Read/Write Mode Enable [NOT IN USE]
     *        |||||+------ T5SYNC: Timer 1 External Clock Input Synchronization Control [NOT IN USE]
     *        ||||+------- T5SOSCEN: Secondary Oscillator Enable Control [NOT IN USE]
     *        ||++-------- T5CKPS: Timer 1 Input Clock Prescale Select
     *        ||                   00: Prescale value 1:1
     *        ++---------- TMR5CS: Timer1 Clock Source Select
     *                             00: Instruction Clock (FOSC/4)
     */

    T5GCON = 0b00000000;
    /*         ||||||++---- T5SS: Timer 1 Gate Source Select [NOT IN USE]
     *         |||||+------ T5GVAL: Timer 1 Gate Current State [NOT IN USE]
     *         ||||+------- T5GGO/DONE: Timer 1 Gate Single-Pulse Acquisition Status [NOT IN USE]
     *         |||+-------- T5GSPM: Timer 1 Gate Single-Pulse Mode [NOT IN USE]
     *         ||+--------- T5GTM: Timer 1 Gate Toggle Mode [NOT IN USE]
     *         |+---------- T5GPOL: Timer 1 Gate Polarity [NOT IN USE]
     *         +----------- TMR5GE: Timer 1 Gate Enable
     *                              0: Timer 1 counts regardless of Timer 1 gate function
     */

    /* Disable Timer1 gate */
    TMR5GE = 0b0;
}



void DRV_tmr_init(void)
{
    _tmr0_init();
    /* Timer1 forfor general purpose timers. */
    _tmr1_init();
    /* Timer3 forfor general purpose timers.*/
    _tmr3_init();
    /* Timer5 for general purpose timers. */
    _tmr5_init();
}

