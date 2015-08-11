/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_osc.c
 * @brief   Oscillator driver.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    May 9, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  May 9, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 *
 * Revision 2.00  from  May 28  , 2014\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Port to PIC18F67K22.\n
 * When modification start, add this information
 *
 * History_End
 */

/**
 * @brief   Oscillator initialization.\n
 *
 * @date    May 9, 2013
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 */
#include "drv_compiler.h"
#include "pic18f46k22.h"
void DRV_osc_init(void)
{
    /* HS 16MHz external OSC */
    OSCCON = 0b00000000;
    /*         ||||||++---- SCS: System Clock Select
     *         ||||||            00: Primary clock (determined by FOSC<3:0> in CONFIG1H)
     *         |||||+------ HFIOFS: HFINTOSC Frequency Stable [NOT IN USE]
     *         ||||+------- OSTS: Oscillator Start-up Time-out Status [NOT IN USE]
     *         |+++-------- IRCF: Internal RC Oscillator Frequency Select [NOT IN USE]
     *         +----------- IDLEN: Idle Enable [NOT IN USE]
     */

    OSCCON2 = 0b00000000;
    /*          |||||||+---- LFIOFS: LFINTOSC Frequency Stable [NOT IN USE]
     *          ||||||+----- PRISD:Primary Oscillator Drive Circuit Shutdown bit [NOT IN USE]
     *          |||||+------ SOSCGO Secondary Oscillator Start Control bit
     *          ||||+------- MFIOSEL:MFINTOSC Select bit [NOT IN USE]
     *          ||+--------- Unimplemented [NOT IN USE]
     *          |+---------- SOSCRUN: SOSC Run Status [NOT IN USE]
     *          +----------- PLL Run Status bit [NOT IN USE]
     */

    OSCTUNE = 0b00000000;
    /*          ||++++++---- TUN: Frequency Tuning [NOT IN USE]
     *          |+---------- PLLEN: Frequency Multiplier
     *          |                   0: Disabled
     *          +----------- INTSRC: Internal Oscillator Low-Frequency Source Select [NOT IN USE]
     */

    /* Wait until HS OSC is ready */
    while (0b01 != OSTS)
    {
        ;
    }
}
