/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_pin_map.h
 * @brief   PIN mappings.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    Oct 11, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  Oct 11, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */

#ifndef DRV_PIN_MAP_H_
#define DRV_PIN_MAP_H_



/* PIN data direction */
#define PIN_OUTPUT      0
#define PIN_INPUT       1
/* PIN weak pull-up */
#define PIN_WPU_DISABLE 0
#define PIN_WPU_ENABLE  1
/* PIN analog select */
#define PIN_ANS_DIGIT   0
#define PIN_ANS_ANALOG  1

#define SERIAL_BUF_LEN  20 //Define the length of the serial buffer
#define PIN_DATA_LOW    0
#define PIN_DATA_HIGH   1
/***** Mapping PIN to functions *****/

///* PORTA0 */
//#define PIN_DIR_NC_A0           TRISA0  /* NC */
//#define PIN_ANS_NC_A0           ANSEL0
//#define PIN_WT_NC_A0            LATA0
///* PORTA1 */
//#define PIN_DIR_IN_PL           TRISA1  /* SPI input PL */
//#define PIN_ANS_IN_PL           ANSEL1
//#define PIN_WT_IN_PL            LATA1
///* PORTA2 */
//#define PIN_DIR_IN_CLK          TRISA2  /* SPI input CLK */
//#define PIN_ANS_IN_CLK          ANSEL2
//#define PIN_WT_IN_CLK           LATA2
///* PORTA3 */
//#define PIN_DIR_SPI_IN_DATA     TRISA3  /* SPI input data */
//#define PIN_RD_SPI_IN_DATA      RA3
/* PORTA4 */
#define PIN_DIR_MOTOR           TRISA4  /* Auxiliary output: relay */
//#define PIN_ANS_MOTOR           ANSEL4
#define PIN_RD_MOTOR            RA4
#define PIN_WT_MOTOR            LATA4
///* PORTA5 */
//#define PIN_DIR_NC_A5           TRISA5  /* NC */
//#define PIN_WT_NC_A5            LATA5
/* PORTA6 */                    /* OSC2 */
/* PORTA7 */                    /* OSC1 */

/* PORTB0 */
//#define PIN_DIR_KEY             TRISB0  /* Keyboard */
//#define PIN_RD_KEY              RB0
///* PORTB1 */
//#define PIN_DIR_24VOUT          TRISB1  /* 24V output short circuit detection */
//#define PIN_RD_24VOUT           RB1
///* PORTB2 */
//#define PIN_DIR_NC_B2           TRISB2  /* NC */
//#define PIN_WT_NC_B2            LATB2
///* PORTB3 */
//#define PIN_DIR_NC_B3           TRISB3  /* NC */
//#define PIN_WT_NC_B3            LATB3
///* PORTB4 */
//#define PIN_DIR_NC_B4           TRISB4  /* NC */
//#define PIN_WT_NC_B4            LATB4
///* PORTB5 */
//#define PIN_DIR_NC_B5           TRISB5  /* NC */
//#define PIN_WT_NC_B5            LATB5
/* PORTB6 */                    /* PGC */
/* PORTB7 */                    /* PGD */

/* PORTC0 */
//#define PIN_DIR_485_DIR         TRISC0  /* EUSART-TO-485 control */
//#define PIN_WT_485_DIR          LATC0
///* PORTC1 */
//#define PIN_DIR_UNIO_AUX        TRISC1  /* Auxiliary EEPROM UNIO */
//#define PIN_RD_UNIO_AUX         RC1
///* PORTC2 */
//#define PIN_DIR_AI_CAP          TRISC2  /* AI capture */
//#define PIN_RD_AI_CAP           RC2
/* PORTC3 */
#define PIN_DIR_SCL               TRISC3  /* AI multiplex C */
#define PIN_ANS_SCL               ANSC3
/* PORTC4 */
#define PIN_DIR_SDA               TRISC4  /* AI multiplex B */
#define PIN_ANS_SDA               ANSC4
///* PORTC5 */
//#define PIN_DIR_AI_MULA         TRISC5  /* AI multiplex A */
//#define PIN_WT_AI_MULA          LATC5
/* PORTC6 */
#define PIN_DIR_USART_TX          TRISD6  /* EUSART-TO-485 TX */
#define PIN_ANS_USART_TX          ANSD6
/* PORTC7 */
#define PIN_DIR_USART_RX          TRISD7  /* EUSART-TO-485 RX */
#define PIN_ANS_USART_RX          ANSD7
//#define RS485_TX                PIN_DATA_LOW /*Define the direction of the usart*/
//#define RS485_RX                PIN_DATA_HIGH
///* PORTD0 */
//#define PIN_DIR_DGT_CHL_4       TRISD0  /* DI/DO channel 4 */
//#define PIN_RD_DGT_CHL_4        RD0
//#define PIN_WT_DGT_CHL_4        LATD0
///* PORTD1 */
//#define PIN_DIR_NC_D1           TRISD1  /* NC */
//#define PIN_WT_NC_D1            LATD1
///* PORTD2 */
//#define PIN_DIR_LED_IND         TRISD2  /* LED indicators control */
//#define PIN_WT_LED_IND          LATD2
///* PORTD3 */
//#define PIN_DIR_LED_BCK         TRISD3  /* LED backlight control */
//#define PIN_WT_LED_BCK          LATD3
///* PORTD4 */
//#define PIN_DIR_SPI_OUT_DATA    TRISD4  /* SPI output data */
///* PORTD5 */
//#define PIN_DIR_NC_D5           TRISD5  /* NC */
//#define PIN_WT_NC_D5            LATD5
///* PORTD6 */
//#define PIN_DIR_SPI_OUT_CLK     TRISD6  /* SPI output clock */
///* PORTD7 */
//#define PIN_DIR_SPI_OUT_STROBE  TRISD7  /* SPI output strobe */
//#define PIN_WT_SPI_OUT_STROBE   LATD7
//
///* PORTE0 */
//#define PIN_DIR_NC_E0           TRISE0  /* NC */
//#define PIN_WT_NC_E0            LATE0
///* PORTE1 */
//#define PIN_DIR_NC_E1           TRISE1  /* NC */
//#define PIN_WT_NC_E1            LATE1
///* PORTE2 */
//#define PIN_DIR_NC_E2           TRISE2  /* NC */
//#define PIN_WT_NC_E2            LATE2
///* PORTE3 */
//#define PIN_DIR_AI_PWM          TRISE3  /* AI -9V PWM */
///* PORTE4 */
//#define PIN_DIR_NC_E4           TRISE4  /* NC */
//#define PIN_WT_NC_E4            LATE4
///* PORTE5 */
//#define PIN_DIR_DGT_CHL_1       TRISE5  /* DI/DO channel 1 */
//#define PIN_RD_DGT_CHL_1        RE5
//#define PIN_WT_DGT_CHL_1        LATE5
///* PORTE6 */
//#define PIN_DIR_DGT_CHL_2       TRISE6  /* DI/DO channel 2 */
//#define PIN_RD_DGT_CHL_2        RE6
//#define PIN_WT_DGT_CHL_2        LATE6
///* PORTE7 */
//#define PIN_DIR_DGT_CHL_3       TRISE7  /* DI/DO channel 3 */
//#define PIN_RD_DGT_CHL_3        RE7
//#define PIN_WT_DGT_CHL_3        LATE7
//
///* PORTF0 */                    /* Not Exist */
///* PORTF1 */
//#define PIN_DIR_UNIO_MAIN       TRISF1  /* Main EEPROM UNIO */
//#define PIN_ANS_UNIO_MAIN       ANSEL9
//#define PIN_RD_UNIO_MAIN        RF1
///* PORTF2 */
//#define PIN_DIR_NC_F2           TRISF2  /* NC */
//#define PIN_ANS_NC_F2           ANSEL10
//#define PIN_WT_NC_F2            LATF2
///* PORTF3 */
//#define PIN_DIR_NC_F3           TRISF3  /* NC */
//#define PIN_ANS_NC_F3           ANSEL11
//#define PIN_WT_NC_F3            LATF3
///* PORTF4 */
//#define PIN_DIR_NC_F4           TRISF4  /* NC */
//#define PIN_WT_NC_F4            LATF4
///* PORTF5 */
//#define PIN_DIR_NC_F5           TRISF5  /* NC */
//#define PIN_ANS_NC_F5           ANSEL5
//#define PIN_WT_NC_F5            LATF5
///* PORTF6 */
//#define PIN_DIR_NC_F6           TRISF6  /* NC */
//#define PIN_ANS_NC_F6           ANSEL6
//#define PIN_WT_NC_F6            LATF6
/* PORTF7 */
#define PIN_DIR_AO_TYPE         TRISF7  /* AO I/U type control */
#define PIN_ANS_AO_TYPE         ANSEL7
#define PIN_WT_AO_TYPE          LATF7
//
///* PORTG0 */
//#define PIN_DIR_NC_G0           TRISG0  /* NC */
//#define PIN_ANS_NC_G0           ANSEL16
//#define PIN_WT_NC_G0            LATG0
///* PORTG1 */
//#define PIN_DIR_USB_TX          TRISG1  /* EUSART-TO-USB TX */
//#define PIN_ANS_USB_TX          ANSEL17
///* PORTG2 */
//#define PIN_DIR_USB_RX          TRISG2  /* EUSART-TO-USB RX */
//#define PIN_ANS_USB_RX          ANSEL18
///* PORTG3 */
//#define PIN_DIR_NC_G3           TRISG3  /* NC */
//#define PIN_ANS_NC_G3           ANSEL19
//#define PIN_WT_NC_G3            LATG3
/* PORTG4 */
#define PIN_DIR_CTRL_OP         TRISG4  /* Main output: AO/Relay/SSR */
#define PIN_WT_CTRL_OP          LATG4

/* Watchdog */
#define DRV_WDT_RESET()   { CLRWDT(); }
#define DRV_WDT_ENABLE()    { WDTCON = 0b00000001; }
#define DRV_WDT_DISABLE()   { WDTCON = 0b00000000; }

/* Enable/Disable all interrupts */
#define DRV_disable_ints()  { di(); }
#define DRV_enable_ints()   { ei(); }

#endif /* DRV_PIN_MAP_H_ */
