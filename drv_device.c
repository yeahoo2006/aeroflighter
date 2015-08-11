/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_device.c
 * @brief   Device configuration.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    Apr 19, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  Apr 19, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */


/*
 * Configuration words settings and values are located in the pic_chipinfo.html
 * from the DOCS of compiler installation folder.
 */

/*
 * Notes for XINST:
 *
 * http://www.experts123.com/q/does-the-hi-tech-c-compiler-for-pic18-mcus-support-the-extended-instruction-set.html
 * "
 * The extended instruction set allows the device to access additional instructions,
 * but at the expense of loosing access bank memory.
 * The main reason for the use of this instruction set is to allow reentracny,
 * which is currently not supported by the compiler.
 * Reentrancy may be introduced in future versions and this may well require
 * utilization of the extended instruction set.
 * "
 *
 * We shall disable it if we won't call the same function in both main and ISRs.
 *                                                              Fox-Lilei.Zhai
 *                                                                  2013-09-04
 */

// CONFIG1L

//#pragma config RETEN = OFF      // VREG Sleep Enable bit (Disabled - Controlled by SRETEN bit)
//#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
//#pragma config SOSCSEL = DIG    // SOSC Power Selection and mode Configuration bits (Digital (SCLKI) mode)
//#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config FOSC = HSHP          // Oscillator (HS oscillator (High power, 16 MHz - 25 MHz))
#pragma config PLLCFG = 0      // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = 1      // Fail-Safe Clock Monitor (Disabled)
#pragma config PRICLKEN = ON
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)  
// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = OFF  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 190         // Brown-out Reset Voltage bits (2.7V)
//#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = SWON       // Watchdog Timer (WDT controlled by SWDTEN bit setting)
#pragma config WDTPS = 64       // Watchdog Postscaler (1:16)

// CONFIG3L
//#pragma config RTCOSC = SOSCREF // RTCC Clock Select (RTCC uses SOSC)

// CONFIG3H
#pragma config CCP2MX = PORTB3  // CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = ON   // ANSELB<5:0> resets to 0, PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config CCP3MX = PORTB5     //  CCP3 input/output is multiplexed with RB5
#pragma config HFOFST = ON    //The system clock is held off until the HFINTOSC is stable
#pragma config T3CMX  = PORTC0    //1 = T3CKI is on RC0
#pragma config P2BMX  = PORTD2    //1 = P2B is on RB5
#pragma config MCLRE  = EXTMCLR    //1 = MCLR pin enabled;
// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config LVP = OFF        //1 = Single-Supply ICSP enabled
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)
// #pragma config DEBUG = 0      //0 = Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
// CONFIG5L
#pragma config CP0 = 1        // Code Protect 00800-03FFF (Disabled)
#pragma config CP1 = 1        // Code Protect 04000-07FFF (Disabled)
#pragma config CP2 = 1        // Code Protect 08000-0BFFF (Disabled)
#pragma config CP3 = 1        // Code Protect 0C000-0FFFF (Disabled)
//#pragma config CP4 = OFF        // Code Protect 10000-13FFF (Disabled)
//#pragma config CP5 = OFF        // Code Protect 14000-17FFF (Disabled)
//#pragma config CP6 = OFF        // Code Protect 18000-1BFFF (Disabled)
//#pragma config CP7 = OFF        // Code Protect 1C000-1FFFF (Disabled)

// CONFIG5H
#pragma config CPB = 1        // Code Protect Boot (Disabled)
#pragma config CPD = 1        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = 1       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = 1       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = 1       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = 1       // Table Write Protect 0C000-0FFFF (Disabled)
//#pragma config WRT4 = OFF       // Table Write Protect 10000-13FFF (Disabled)
//#pragma config WRT5 = OFF       // Table Write Protect 14000-17FFF (Disabled)
//#pragma config WRT6 = OFF       // Table Write Protect 18000-1BFFF (Disabled)
//#pragma config WRT7 = OFF       // Table Write Protect 1C000-1FFFF (Disabled)

// CONFIG6H
#pragma config WRTC = 1       // Config. Write Protect (Disabled)
#pragma config WRTB = 1       // Table Write Protect Boot (Disabled)
#pragma config WRTD = 1       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = 1      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBTR1 = 1      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBTR2 = 1      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBTR3 = 1      // Table Read Protect 0C000-0FFFF (Disabled)
//#pragma config EBRT4 = OFF      // Table Read Protect 10000-13FFF (Disabled)
//#pragma config EBRT5 = OFF      // Table Read Protect 14000-17FFF (Disabled)
//#pragma config EBRT6 = OFF      // Table Read Protect 18000-1BFFF (Disabled)
//#pragma config EBRT7 = OFF      // Table Read Protect 1C000-1FFFF (Disabled)

// CONFIG7H
#pragma config EBTRB = 1      // Table Read Protect Boot (Disabled)


/* User ID */
#pragma config IDLOC0 = 0x00
#pragma config IDLOC1 = 0x0A
#pragma config IDLOC2 = 0x0B
#pragma config IDLOC3 = 0x0B

/*
 * Inline special functions that the code generator will expand internally.
 * Use #pragma inline() or inline specifier for user-defined functions.
 */
/* #pragma intrinsic(_delay) */

