
/*******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  May 23, 2013\n
 * Developer    Will-liang.he <Will-liang.hecn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */

#include "drv_pin_map.h"
void DRV_ccp5_disable_ao(void)
{
    /* CCP5 PWM configuration */
    CCP5CON = 0b00110000;
    /*          ||||++++---- CCP5M: CCP5 Mode Select
     *          ||||                0000: Capture/Compare/PWM off
     *          ||++-------- DC5B: Two LSBs of the PWM duty cycle.
     *          ||                 11
     *          ++---------- P5M: PWM Output Configuration [NOT IN USE]
     */

    PIN_DIR_AO_TYPE = PIN_INPUT;
}
void DRV_ccp5_set_pwm(uint16_t value)
{
    CCPR5L = (uint8_t)(value >> 2);
    DC5B0 = (value & 0x0001) ? 0b1 : 0b0;
    DC5B1 = (value & 0x0002) ? 0b1 : 0b0;
}

void DRV_ccp5_init_ao(void)
{
    /* Disable PIN output  */
    PIN_DIR_CTRL_OP = PIN_INPUT;
    /* Set TIMER4 period for PWM period */
    PR4 = 0xFF;

    /* CCP5 PWM configuration */
    CCP5CON = 0b00111100;
    /*          ||||++++---- CCP5M: CCP5 Mode Select
     *          ||||                1100: PWM mode
     *          ||++-------- DC5B: Two LSBs of the PWM duty cycle.
     *          ||                 11
     *          ++---------- P5M: PWM Output Configuration [NOT IN USE]
     */

    /* Eight MSBs of the PWM duty cycle */
    CCPR5L = 0b11111111;

    /* Choose and start TIMER4 */
    {
        CCPTMRS1bits.C5TSEL0 = 0b1;

        /* Disable TMR4 interrupt*/
        TMR4IE = 0b0;

        /* Clear TMR4 interrupt flag */
        TMR4IF = 0b0;

        /* Timer4 configuration */
        T4CON = 0b00000110;
        /*        ||||||++---- T4CKPS: Timer2-type Clock Prescale Select
         *        ||||||               1x: Prescaler is 16
         *        |||||+------ TMR4ON: Timer 1 On
         *        |||||                1: Enable Timer4
         *        |++++------- T4OUTPS:  [NOT IN USE]
         *        +----------- Unimiplemented [NOT IN USE]
         */
    }

    /* Enable pin output */
    PIN_DIR_CTRL_OP = PIN_OUTPUT;
}