///**
// * Copyright 2013 ABB. All rights reserved.
// *
// * @file    drv_ccp.c
// * @brief   CCP driver.\n
// *
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// * @date    May 23, 2013
// *******************************************************************************
// * History_Begin
// *
// * Revision 1.00  from  May 23, 2013\n
// * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
// * Description  Initial version\n
// * When modification start, add this information
// *
// * History_End
// */
//
//#include "api.h"
//#include "drv_compiler.h"
//#include "drv_pin_map.h"
///**
// * @brief   Disable AO output.\n
// * @date    Jan 23, 2014
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//void DRV_ccp5_disable_ao(void)
//{
//    /* CCP5 PWM configuration */
//    CCP5CON = 0b00110000;
//    /*          ||||++++---- CCP5M: CCP5 Mode Select
//     *          ||||                0000: Capture/Compare/PWM off
//     *          ||++-------- DC5B: Two LSBs of the PWM duty cycle.
//     *          ||                 11
//     *          ++---------- P5M: PWM Output Configuration [NOT IN USE]
//     */
//
//    PIN_DIR_AO_TYPE = PIN_INPUT;
//}
//
///**
// * @brief   Driver for set value of AO PWM.\n
// * @date    June 19, 2013
// * @author  Bill-bihao.dai <bihao.dai@cn.abb.com>
// */
//void DRV_ccp5_set_pwm(uint16_t value)
//{
//    CCPR5L = (uint8_t)(value >> 2);
//    DC5B0 = (value & 0x0001) ? 0b1 : 0b0;
//    DC5B1 = (value & 0x0002) ? 0b1 : 0b0;
//}
//
///**
// * @brief   Driver for CPP5. Used for AO PWM.\n
// *          Timer2 is used for CPP5.
// *          Generate 3.90625KHz PWM.
// * @date    May 23, 2013
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//void DRV_ccp5_init_ao(void)
//{
//    /* Disable PIN output  */
//    PIN_DIR_CTRL_OP = PIN_INPUT;
//    /* Set TIMER4 period for PWM period */
//    PR4 = 0xFF;
//
//    /* CCP5 PWM configuration */
//    CCP5CON = 0b00111100;
//    /*          ||||++++---- CCP5M: CCP5 Mode Select
//     *          ||||                1100: PWM mode
//     *          ||++-------- DC5B: Two LSBs of the PWM duty cycle.
//     *          ||                 11
//     *          ++---------- P5M: PWM Output Configuration [NOT IN USE]
//     */
//
//    /* Eight MSBs of the PWM duty cycle */
//    CCPR5L = 0b11111111;
//
//    /* Choose and start TIMER4 */
//    {
//        CCPTMRS1bits.C5TSEL0 = 0b1;
//
//        /* Disable TMR4 interrupt*/
//        TMR4IE = 0b0;
//
//        /* Clear TMR4 interrupt flag */
//        TMR4IF = 0b0;
//
//        /* Timer4 configuration */
//        T4CON = 0b00000110;
//        /*        ||||||++---- T4CKPS: Timer2-type Clock Prescale Select
//         *        ||||||               1x: Prescaler is 16
//         *        |||||+------ TMR4ON: Timer 1 On
//         *        |||||                1: Enable Timer4
//         *        |++++------- T4OUTPS:  [NOT IN USE]
//         *        +----------- Unimiplemented [NOT IN USE]
//         */
//    }
//
//    /* Enable pin output */
//    PIN_DIR_CTRL_OP = PIN_OUTPUT;
//}
//
///**
// * @brief   Driver for CPP9. Used for AI -9V PWM.\n
// *          Timer4 is used for CPP9.
// *          Generate 10KHz 50% PWM for AI.
// *          We have three CCP parameter candidates:
// *             Timer prescale = 16
// *             PR = 0x63
// *             CCPRxL:CCPxCON = 0b0011001000
// * @date    May 23, 2013
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//static void _ccp9_init_aivolt(void)
//{
//    /* Disable PIN output  */
//    PIN_DIR_AI_PWM = PIN_INPUT;
//
//    /* Set TIMER2 period for PWM period */
//    PR2 = 0x63;
//
//    /* CCP9 PWM configuration */
//    CCP9CON = 0b00001100;
//    /*          ||||++++---- CCP9M: CCP9 Mode Select
//     *          ||||                1100: PWM mode
//     *          ||++-------- DC9B: Two LSBs of the PWM duty cycle.
//     *          ||                 00
//     *          ++---------- P9M: PWM Output Configuration [NOT IN USE]
//     */
//
//    /* Eight MSBs of PWM duty cycle */
//    CCPR9L = 0b00110010;
//
//    /* Choose and start TIMER2 */
//    {
//        CCPTMRS2bits.C9TSEL0 = 0b0;
//
//        /* Disable TMR2 interrupt*/
//        TMR2IE = 0b0;
//
//        /* Clear TMR2 interrupt flag */
//        TMR2IF = 0b0;
//
//        /* Timer2 configuration */
//        T2CON = 0b00000110;
//        /*        ||||||++---- T2CKPS: Timer2-type Clock Prescale Select
//         *        ||||||               1X: Prescaler is 16
//         *        |||||+------ TMR2ON: Timer 2 On
//         *        |||||                1: Enable Timer2
//         *        |++++------- T2OUTPS:  [NOT IN USE]
//         *        +----------- Unimiplemented [NOT IN USE]
//         */
//    }
//
//    /* Enable pin output */
//    PIN_DIR_AI_PWM = PIN_OUTPUT;
//}
//
///**
// * @brief   Driver for ECCP1. Used for AI capture mode.\n
// *
// * @date    May 30, 2013
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//static void _ccp1_init_aicap(void)
//{
//    /* Turn CCP1 off */
//    CCP1CON = 0b00000000;
//    /*          ||||++++---- CCP1M: ECCP1 Mode Select
//     *          ||||                0000: Capture/Compare/PWM off
//     *          ||++-------- DC1B: Two LSBs of the PWM duty cycle. [NOT IN USE]
//     *          ++---------- P1M: PWM Output Configuration [NOT IN USE]
//     */
//
//    /* Choose and start TIMER1 */
//    CCPTMRS0bits.C1TSEL = 0b000;
//
//    /* Disable interrupt */
//    CCP1IE = 0b0;
//
//    /* Clear interrupt flat */
//    CCP1IF = 0b0;
//}
//
///**
// * @brief   Driver for CCP6. Used for AI compare mode.\n
// *
// * @date    May 30, 2013
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//static void _ccp6_init_aicomp(void)
//{
//    /* Configure CCP6 as compare mode */
//    CCP6CON = 0b00001010;
//    /*          ||||++++---- CCP6M: CCP6 Mode Select
//     *          ||||                1010: Compare mode: generate software interrupt on compare match
//     *          ||++-------- DC6B: Two LSBs of the PWM duty cycle. [NOT IN USE]
//     *          ++---------- Unimiplemented [NOT IN USE]
//     */
//
//    /* Choose TIMER1 */
//    CCPTMRS1bits.C6TSEL0 = 0b0;
//
//    /* Disable interrupt */
//    CCP6IE = 0b0;
//
//    /* Clear interrupt flat */
//    CCP6IF = 0b0;
//
//    /* CCPR6H:L 0x0000 */
//    CCPR6L = 0x00;
//    CCPR6H = 0x00;
//}
//
///**
// * @brief   Driver for CCP4. Used for timer 3 compare mode to achieve MODBUS timer.\n
// *
// * @date    Dec 23, 2013
// * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
// */
//static void _ccp4_init_modbus(void)
//{
//    /* Configure CCP4 as compare mode */
//    CCP4CON = 0b00001010;
//    /*          ||||++++---- CCP4M: CCP4 Mode Select
//     *          ||||                1010: Compare mode: Generate software interrupt on compare match
//     *          ||++-------- DC4B: Two LSBs of the PWM duty cycle. [NOT IN USE]
//     *          ++---------- P4M: PWM Output Configuration [NOT IN USE]
//     */
//
//    /* Disable interrupt */
//    CCP4IE = 0b0;
//
//    /* Clear interrupt flat */
//    CCP4IF = 0b0;
//
//    /* Choose TIMER3 */
//    CCPTMRS1bits.C4TSEL = 0b01;
//
//    /* CCPR4H:L 0x0000 */
//    CCPR4L = 0x00;
//    CCPR4H = 0x00;
//}
//
//void DRV_ccp_init(void)
//{
//    _ccp4_init_modbus(); /* For MODBUS timer compare */
//    _ccp1_init_aicap(); /* For AI capture */
//    _ccp6_init_aicomp(); /* For AI compare */
//    _ccp9_init_aivolt(); /* For AI -9V */
//}
//
