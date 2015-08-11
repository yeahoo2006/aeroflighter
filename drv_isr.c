/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_isr.c
 * @brief   ISR.\n
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
#include "drv_compiler.h"
#include "stddef.h"
#include "drv_usart.h"
#include "lib_rprintf.h"
#include "drv_isr.h"
#include "drv_pin_map.h"

uint8_t tmr_of_max = 0; /* Maximum timer 1 overflow counter value */
uint8_t tmr_of_cnt = 0; /* Timer 1 overflow counter */
boolean flag_1ms = FALSE;
boolean flag_motor_control = FALSE;
boolean flag_18ms = FALSE;
boolean flag_motor_control_rest_TMR=FALSE;
void DRV_isr_init(void)
{
    RCONbits.IPEN = 0b1; /* Enable interrupt priority */

     INTCON = 0b00000000;
    /*          |||||||+---- RBIF: Port B Interrupt-On-Change Interrupt Flag
     *          ||||||+----- INT0IF: INT0 External Interrupt Flag
     *          |||||+------ TMR0IF: TMR0 Overflow Interrupt Flag
     *          ||||+------- RBIE: Port B Interrupt-On-Change Interrupt Enable
     *          |||+-------- INT0IE: INT0 External Interrupt Enable
     *          ||+--------- TMR0IE: TMR0 Overflow Interrupt Enable
     *          |+---------- PEIE/GIEL: Peripheral Interrupt Enable
     *          |                       0: Disables all low priority interrupts
     *          +----------- GIE/GIEH: Global Interrupt Enable
     *                                 0: Disables all interrupts including low priority
     */

    INTCON2 = 0b10000000;
    /*          |||||||+---- RBIP: RB Port Change Interrupt Priority
     *          ||||||+----- INT3IP: INT3 External Interrupt Priority
     *          |||||+------ TMR0IP: TMR0 Overflow Interrupt Priority
     *          ||||+------- INTEDG3: External Interrupt 3 Edge Select
     *          |||+-------- INTEDG2: External Interrupt 2 Edge Select
     *          ||+--------- INTEDG1: External Interrupt 1 Edge Select
     *          |+---------- INTEDG0: External Interrupt 0 Edge Select
     *          +----------- RBPU: PORTB Pull-up Enable
     *                             1: PORTB pull-ups are disabled
     */

    INTCON3 = 0b00000000;
    /*          |||||||+---- INT1IF: INT1 External Interrupt Flag
     *          ||||||+----- INT2IF: INT2 External Interrupt Flag
     *          |||||+------ INT3IF: INT3 External Interrupt Flag
     *          ||||+------- INT1IE: INT1 External Interrupt Enable
     *          |||+-------- INT2IE: INT2 External Interrupt Enable
     *          ||+--------- INT3IE: INT3 External Interrupt Enable
     *          |+---------- INT1IP: INT1 External Interrupt Priority
     *          +----------- INT2IP: INT2 External Interrupt Priority
     */

    PIR1 = 0b00000000;
    /*       |||||||+---- TMR1IF: TMR1 Overflow Interrupt Flag
     *       ||||||+----- TMR2IF: TMR2 to PR2 Match Interrupt Flag
     *       |||||+------ TMR1GIF: Timer1 Gate Interrupt Flag
     *       ||||+------- SSP1IF: Master Synchronous Serial Port1 Interrupt Flag
     *       |||+-------- TX1IF: EUSART1 Transmit Interrupt Flag
     *       ||+--------- RC1IF: EUSART1 Receive Interrupt Flag
     *       |+---------- ADIF: A/D Converter Interrupt Flag
     *       +----------- PSPIF: Parallel Slave Port Read/Write Interrupt Flag
     */

    PIR2 = 0b00000000;
    /*       |||||||+---- TMR3GIF: TMR3 Gate Interrupt Flag
     *       ||||||+----- TMR3IF: TMR3 Overflow Interrupt Flag
     *       |||||+------ HLVDIF: Low-Voltage Detect Interrupt Flag
     *       ||||+------- BCL1IF: Bus Collision Interrupt Flag
     *       |||+-------- BCL2IF: Bus Collision Interrupt Flag
     *       ||+--------- SSP2IF: Master Synchronous Serial Port Interrupt Flag
     *       |+---------- Unimplemented
     *       +----------- OSCFIF: Oscillator Fail Interrupt Flag
     */

    PIR3 = 0b00000000;
    /*       |||||||+---- RTCCIF: RTCC Interrupt Flag
     *       ||||||+----- CCP1IF: ECCP1 Interrupt Flag
     *       |||||+------ CCP2IF: ECCP2 Interrupt Flag
     *       ||||+------- CTMUIF: CTMU Interrupt Flag
     *       |||+-------- TX2IF: EUSART2 Transmit Interrupt Flag
     *       ||+--------- RC2IF: EUSART2 Receive Interrupt Flag
     *       |+---------- Unimplemented
     *       +----------- TMR5GIF: Timer5 Gate Interrupt Flag
     */

    PIR4 = 0b00000000;
    /*       |||||||+---- CCP3IF: ECCP3 Interrupt Flag
     *       ||||||+----- CCP4IF: CCP4 Interrupt Flag
     *       |||||+------ CCP5IF: CCP5 Interrupt Flag
     *       ||||+------- CCP6IF: CCP6 Interrupt Flag
     *       |||+-------- CCP7IF: CCP7 Interrupt Flag
     *       ||+--------- CCP8IF: CCP8 Interrupt Flag
     *       |+---------- CCP9IF: CCP9 Interrupt Flag
     *       +----------- CCP10IF: CCP10 Interrupt Flag
     */

    PIR5 = 0b00000000;
    /*       |||||||+---- TMR4IF: TMR4 to PR4 Match Interrupt Flag
     *       ||||||+----- TMR5IF: TMR5 Overflowh Interrupt Flag
     *       |||||+------ TMR6IF: TMR6 to PR6 Match Interrupt Flag
     *       ||||+------- TMR7IF: TMR7 Overflow Interrupt Flag
     *       |||+-------- TMR8IF: TMR8 to PR8 Match Interrupt Flag
     *       ||+--------- TMR10IF: TMR6 to PR10 Match Interrupt Flag
     *       |+---------- TMR12IF: TMR12 to PR12 Match Interrupt Flag
     *       +----------- TMR7GIF: TMR7 Gate Interrupt Flag
     */

   // PIR6 = 0b00000000;
    /*       |||||||+---- CMP1IF: CMP1 Interrupt Flag
     *       ||||||+----- CMP2IF: CMP2 Interrupt Flag
     *       |||||+------ CMP3IF: CMP3 Interrupt Flag
     *       ||||+------- Unimplemented
     *       |||+-------- EEIF: Data EEDATA/FLASH Write Operation Interrupt Flag
     *       +++--------- Unimplemented
     */

    PIE1 = 0b00000000;
    /*       |||||||+---- TMR1IE: TMR1 Overflow Interrupt Enable
     *       ||||||+----- TMR2IE: TMR2 to PR2 Match Interrupt Enable
     *       |||||+------ TMR1GIE: TMR1 Gate Interrupt Enable
     *       ||||+------- SSP1IE: Master Synchronous Serial Port 1 Interrupt Enable
     *       |||+-------- TX1IE: EUSART1 Transmit Interrupt Enable
     *       ||+--------- RC1IE: EUSART1 Receive Interrupt Enable
     *       |+---------- ADIE: A/D Converter Interrupt Enable
     *       +----------- PSPIE: Parallel Slave Port Read/Write Interrupt Enable
     */

    PIE2 = 0b00000000;
    /*       |||||||+---- TMR3GIE: Timer3 Gate Interrupt
     *       ||||||+----- TMR3IE: TMR3 Overflow Match Interrupt Enable
     *       |||||+------ HLVDIE: Low-Voltage Detect Interrupt Enable
     *       ||||+------- BCL1IE: Bus Collision Interrupt Enable
     *       |||+-------- BCL2IE: Bus Collision Interrupt Enable
     *       ||+--------- SSP2IE: Master Synchronous Serial Port 2 Interrupt Enable
     *       |+---------- Unimplemented
     *       +----------- OSCFIE: Oscillator Fail Interrupt Enable
     */

    PIE3 = 0b00000000;
    /*       |||||||+---- RTCCIE: RTCC Interrupt Enable
     *       ||||||+----- CCP1IE: ECCP1 Interrupt Enable
     *       |||||+------ CCP2IE: ECCP2 Interrupt Enable
     *       ||||+------- CTMUIE: CTMU Interrupt Enable
     *       |||+-------- TX2IE: EUSART2 Transmit Interrupt Enable
     *       ||+--------- RC2IE: EUSART2 Receive Interrupt Enable
     *       |+---------- Unimplemented
     *       +----------- TMR5GIE: Timer5 Gate Interrupt Enable
     */

    PIE4 = 0b00000000;
    /*       |||||||+---- CCP3IE: CCP3 Interrupt Enable
     *       ||||||+----- CCP4IE: CCP4 Interrupt Enable
     *       |||||+------ CCP5IE: CCP5 Interrupt Enable
     *       ||||+------- CCP6IE: CCP6 Interrupt Enable
     *       |||+-------- CCP7IE: CCP7 Interrupt Enable
     *       ||+--------- CCP8IE: CCP8 Interrupt Enable
     *       |+---------- CCP9IE: CCP9 Interrupt Enable
     *       +----------- CCP10IE: CCP10 Interrupt Enable
     */

    PIE5 = 0b00000000;
    /*       |||||||+---- TMR4IE: TMR4 to PR4 Match Interrupt Enable
     *       ||||||+----- TMR5IE: TMR5 Overflow Interrupt Enable
     *       |||||+------ TMR6IE: TMR6 to PR6 Match Interrupt Enable
     *       ||||+------- TMR7IE: TMR7 Overflow Interrupt Enable
     *       |||+-------- TMR8IE: TMR8 to PR8 Match Interrupt Enable
     *       ||+--------- TMR10IE: TMR10 to PR10 Match Interrupt Enable
     *       |+---------- TMR12IE: TMR12 to PR12 Match Interrupt Enable
     *       +----------- TMR7GIE: TMR7 Gate Interrupt Enable
     */

    //PIE6 = 0b00000000;
    /*       |||||||+---- CMP1IE: CMP1 Enable
     *       ||||||+----- CMP2IE: CMP2 Enable
     *       |||||+------ CMP3IE: CMP3 Enable
     *       ||||+------- Unimplemented
     *       |||+-------- EEIE: Data EEDATA/FLASH Write Operation Enable
     *       +++--------- Unimplemented
     */

    IPR1 = 0b00000001;
    /*       |||||||+---- TMR1IP: TMR1 Overflow Interrupt Priority
    /*       |||||||              1: High priority
     *       ||||||+----- TMR2IP: TMR2 to PR2 Match Interrupt Priority
     *       |||||+------ TMR1GIP: Timer1 Gate Interrupt Priority
     *       ||||+------- SSP1IP: Master Synchronous Serial Port 1 Interrupt Priority
     *       |||+-------- TX1IP: EUSART1 Transmit Interrupt Priority
     *       ||+--------- RC1IP: EUSART1 Receive Interrupt Priority
     *       |+---------- ADIP: A/D Convert Interrupt Priority
     *       +----------- PSPIP: Parallel Slave Port Read/Write Interrupt Priority
     */

    IPR2 = 0b00000001;
    /*       |||||||+---- TMR3GIP: TMR2 Gate Interrupt Priority
     *       ||||||+----- TMR3IP: TMR3 Overflow Interrupt Priority
     *       |||||+------ HLVDIP: Low-Voltage Detect Interrupt Priority
     *       ||||+------- BCL1IP: Bus Collision Interrupt Priority
     *       |||+-------- BCL2IP: Bus Collision Interrupt Priority
     *       ||+--------- SSP2IP: Master Synchronous Serial Port 2 Interrupt Priority
     *       |+---------- Unimplemented
     *       +----------- OSCFIP: Oscillator Fail Interrupt Priority
     */

    IPR3 = 0b00000100;
    /*       |||||||+---- RTCCIP: RTCC Interrupt Priority
     *       ||||||+----- CCP1IP: ECCP1 Interrupt Priority
    /*       ||||||               1: High priority
     *       |||||+------ CCP2IP: ECCP2 Interrupt Priority
     *       ||||+------- CTMUIP: CTMU Interrupt Priority
     *       |||+-------- TX2IP: EUSART2 Transmit Interrupt Priority
     *       ||+--------- RC2IP: EUSART2 Receive Interrupt Priority
     *       |+---------- Unimplemented
     *       +----------- TMR5GIP: Timer5 Gate Interrupt Priority
     */

    IPR4 = 0b00000000;
    /*       |||||||+---- CCP3IP: CCP3 Interrupt Priority
     *       ||||||+----- CCP4IP: CCP4 Interrupt Priority
     *       |||||+------ CCP5IP: CCP5 Interrupt Priority
     *       ||||+------- CCP6IP: CCP6 Interrupt Priority
     *       ||||                 1: High priority
     *       |||+-------- CCP7IP: CCP7 Interrupt Priority
     *       ||+--------- CCP8IP: CCP8 Interrupt Priority
     *       |+---------- CCP9IP: CCP9 Interrupt Priority
     *       +----------- CCP10IP: CCP10 Interrupt Priority
     */

    IPR5 = 0b00000000;
    /*       |||||||+---- TMR4IP: TMR4 to PR4 Match Interrupt Priority
     *       ||||||+----- TMR5IP: TMR5 Overflow Interrupt Priority
     *       |||||+------ TMR6IP: TMR6 to PR6 Match Interrupt Priority
     *       ||||+------- TMR7IP: TMR7 Overflow Interrupt Priority
     *       |||+-------- TMR8IP: TMR8 to PR8 Match Interrupt Priority
     *       ||+--------- TMR10IP: TMR10 to PR10 Match Interrupt Priority
     *       |+---------- TMR12IP: TMR12 to PR12 Match Interrupt Priority
     *       +----------- TMR7GIP: TMR7 Gate Interrupt Priority
     */



}

#define DISABLE_CCP1() \
{ \
    CCP1IE = 0b0; /* Disable interrupt */ \
}
#define ENABLE_CCP1() \
{ \
    CCP1IE = 0b0; /* Disable interrupt */ \
    CCP1IF = 0b0; /* Clear interrupt flat */ \
    CCP1IE = 0b1; /* Enable interrupt */ \
}

#define ENABLE_TMR0_INT() \
{ \
    TMR0 = 0x0000; /* Reset TMR1 */ \
    TMR0IF = 0; /* Timer1 interrupt flag */ \
    TMR0IE = 0b1; /* Enable Timer1 interrupt */ \
}

#define DISABLE_TMR0_INT() \
{ \
    TMR0IE = 0b0; /* Disable Timer1 interrupt */ \
    TMR0 = 0x0000; /* Reset TMR1 */ \
    TMR0IF = 0b0; /* Timer1 interrupt flag */ \
}

#define CFG_CCP1(CCPR1L_VAL, CCPR1H_VAL) \
{ \
    CCPR1L = CCPR1L_VAL; \
    CCPR1H = CCPR1H_VAL; \
}

#define motor_1ms_TMR() \
{ \
    tmr_of_max = 0; \
    CFG_CCP6(0xA0, 0x0F); \
    tmr_of_cnt = 0; \
    ENABLE_TMR1_INT(); \
    flag_1ms = TRUE;\
}


void motor_control(uint8_t percent){
    tmr_of_max = 0; 
    uint16_t temp = 4 * percent * 10;
    CFG_CCP6((temp & 0011), ((temp & 1100)>>8));
    tmr_of_cnt = 0; 
    ENABLE_TMR1_INT(); 
    flag_motor_control=TRUE;
    
}

void motor_18ms_TMR(){
    tmr_of_max=1;
    CFG_CCP6(0x40,0x19);
    tmr_of_cnt = 0; 
    ENABLE_TMR1_INT(); 
    flag_18ms=TRUE;
    
}
void motor_control_rest_TMR(uint8_t percent){
    tmr_of_max=0;
    uint16_t rest = 4 * (100-percent) * 10;
    CFG_CCP6((rest & 0011), ((rest & 1100)>>8));
    tmr_of_cnt = 0; 
    ENABLE_TMR1_INT(); 
    flag_motor_control_rest_TMR=TRUE;
}
void motor_loop(uint8_t percent){
    motor_1ms_TMR();
    motor_control(percent);
    motor_control_rest_TMR(percent);
    motor_18ms_TMR();
}
void  interrupt low_priority low_isr(void)
{

//    /* EUSART-USB rx */
    if (PIR3bits.RC2IF && PIE3bits.RC2IE)
  {
/* Datasheet:
 * The receive FIFO buffer can hold two characters.
 * An overrun error will be generated if a third character,
 * in its entirety, is received before the FIFO is accessed.
 * When this happens, the OERR is set.
 * The characters already in the FIFO buffer can be read,
 * but no additional characters will be received
 * until the error is cleared.
 */
//#if defined(TARGET_FACTORY) || defined(TARGET_SIMULATION)
        uint8_t rec_char = RCREG2;
        DRV_usart_rx(rec_char);
        if (1 == RCSTA2bits.OERR)
        {
            RCSTA2bits.CREN = 0b0;
            RCSTA2bits.CREN = 0b1;
        }
    }
    

}

void  interrupt high_priority high_isr(void)
{
    if (CCP1IF && CCP1IE) /* CCP6IF will be set even if CCP6IE is not set */
    {
        CCP1IF = 0;
        DISABLE_CCP1();
        if(flag_1ms==FALSE && flag_motor_control==FALSE && flag_18ms==FALSE &&flag_motor_control_rest_TMR==FALSE )
        {PIN_WT_MOTOR = PIN_DATA_HIGH;}
        if(flag_1ms==TRUE && flag_motor_control==FALSE && flag_18ms==FALSE &&flag_motor_control_rest_TMR==FALSE)
            {PIN_WT_MOTOR = PIN_DATA_HIGH;}
        if(flag_1ms==TRUE && flag_motor_control==TRUE && flag_18ms==FALSE &&flag_motor_control_rest_TMR==FALSE)
             {PIN_WT_MOTOR = PIN_DATA_LOW;}
        if(flag_1ms==TRUE && flag_motor_control==TRUE && flag_18ms==FALSE &&flag_motor_control_rest_TMR==TRUE)
             {PIN_WT_MOTOR = PIN_DATA_LOW;}
        if(flag_1ms==TRUE && flag_motor_control==TRUE && flag_18ms==TRUE &&flag_motor_control_rest_TMR==TRUE)
             {PIN_WT_MOTOR = PIN_DATA_LOW;
              flag_1ms = FALSE;
              flag_motor_control=FALSE;
              flag_18ms = FALSE;
              flag_motor_control_rest_TMR=FALSE;
              }
        }

    
    /* Timer1 overflow */
    if (TMR0IF && TMR0IE)
    {
        TMR0IF = 0b0;

        tmr_of_cnt++;

        /* For timers that specifies time period */
        if ((0xFF != tmr_of_max) && (tmr_of_cnt == tmr_of_max))
        {
            DISABLE_TMR0_INT();
            ENABLE_CCP1();
        }
    }
}

