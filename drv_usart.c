/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_usart.c
 * @brief   USART driver.\n
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

#include <string.h>
#include <stdlib.h>
#include "drv_pin_map.h"
#include "drv_compiler.h"
uint8_t sci_rx_flag = 0;
uint8_t serial_in_buf[SERIAL_BUF_LEN] = {0};
volatile uint8_t uart_rx_cnt = 0;
void DRV_usart_init(void)
{
    PIE3bits.TX2IE = 0;
    PIE3bits.RC2IE = 1;
    IPR3bits.RC2IP = 0;
    PIN_DIR_USART_TX = PIN_INPUT;
    PIN_ANS_USART_TX = PIN_ANS_DIGIT;
    PIN_DIR_USART_RX = PIN_INPUT;
    PIN_ANS_USART_RX = PIN_ANS_DIGIT;
    TXSTA2 = 0b00100000;
    /*         |||||||+---- TX9D: Ninth bit of Transmit Data [NOT IN USE]
     *         ||||||+----- TRMT: Transmit Shift Register Status [NOT IN USE]
     *         |||||+------ BRGH: High Baud Rate Select
     *         |||||             0: Low speed
     *         ||||+------- SENDB: Send Break Character [NOT IN USE]
     *         |||+-------- SYNC: EUSART Mode Select
     *         |||                0: Asynchronous mode
     *         ||+--------- TXEN: Transmit Enable
     *         ||                 1: Transmit enabled
     *         |+---------- TX9: 9-bit Transmit Enable
     *         |                 0: Selects 8-bit transmission
     *         +----------- CSRC: Clock Source Select [NOT IN USE]
     */

    RCSTA2 = 0b10010000;
    /*         |||||||+---- RX9D: Ninth bit of Received Data [NOT IN USE]
     *         ||||||+----- OERR: Overrun Error [NOT IN USE]
     *         |||||+------ FERR: Framing Error [NOT IN USE]
     *         ||||+------- ADDEN: Address Detect Enable [NOT IN USE]
     *         |||+-------- CREN: Continuous Receive Enable
     *         |||                0: disable receiver
     *         ||+--------- SREN: Single Receive Enable [NOT IN USE]
     *         |+---------- RX9: 9-bit Receive Enable
     *         |                 0: Select 8-bit reception
     *         +----------- SPEN: Serial Port Enable
     *                            1: Serial port enabled
     */

    BAUDCON2 = 0b00000000;
    /*           |||||||+---- ABDEN: Auto-Baud Detect Enable [NOT IN USE]
     *           ||||||+----- WUE: Wake-up Enable [NOT IN USE]
     *           |||||+------ Unimiplemented [NOT IN USE]
     *           ||||+------- BRG16: 16-bit Bayd Rate Generator
     *           ||||                0: 16-bit Baud Rate Generator is not used (SPBRG1)
     *           |||+-------- CKTXP: Clock/Transmit Polarity Select
     *           |||                 0: Idle state for transmit (TXx) is high
     *           ||+--------- DTRXP:Data/Receive Polarity Select bit
     *           ||                  0: Receive data (RXx) is inverted (active-high)
     *           |+---------- RCIDL: Receive Idle Flag [NOT IN USE]
     *           +----------- ABDOVF: Auto-Baud Detect Overflow [NOT IN USE]
     */

    /* Generate default baudrate: 9600 */
    SPBRG2  = 25;

}

static uint8_t _cnt_one_in_byte(uint8_t target)
{
    uint8_t index = 0;
    uint8_t cnt = 0;
    //Caculate the number of '1' in msg
    for (index = 0; index < 8; index++)
    {
        if ((target << index) & 0x80)
        {
            cnt ++;
        }
    }

    return cnt;
}

/**
 * @brief   Caculate the parity used in TX9D
 * @date    May 30, 2014
 * @author  Yoda-yude.zhang<yoda-yude.zhang@cn.abb.com>
 * @param   msg   [IN]  [data]
 */
/*
uint8_t DRV_tx_parity(uint8_t msg)
{
    boolean result;
    uint8_t cnt = 0;

    //Caculate the number of '1' in msg
    cnt = _cnt_one_in_byte(msg);

    //Acroding to the cnt and the parity type to get the result
    switch (paritymode)
    {
        case PARITY_ODD:
        {
            result = (cnt%2 == 0) ? 1 : 0;
        }
        break;
        case PARITY_EVEN:
        {
            result = (cnt%2 == 0) ? 0 :1;
        }
        break;
        case PARITY_NONE:
        default:
        break;
    }

    return result;
}
*/
/**
 * @brief   Check the parity and return the result,used in the receiver
 * @date    May 30, 2014
 * @author  Yoda-yude.zhang<yoda-yude.zhang@cn.abb.com>
 * @param   msg   [IN]  [data]
 *           result[OUT] [boolean]
 */
/*
boolean DRV_check_parity(uint8_t msg, uint8_t parity)
{
    boolean result = FALSE;
    uint8_t cnt = 0;

    //Caculate the number of '1' in msg
    cnt = _cnt_one_in_byte(msg);

    //Acroding to the cnt and the parity type to get the result
    switch (paritymode)
    {
        case PARITY_ODD:
        {
            if (((cnt%2 == 0) && (parity == 1)) ||
                ((cnt%2 == 1) && (parity == 0)))
                result = TRUE;
        }
        break;
        case PARITY_EVEN:
        {
            if (((cnt%2 == 0) && (parity == 0)) ||
                ((cnt%2 == 1) && (parity == 1)))
                result = TRUE;
        }
        break;
        case PARITY_NONE:
        {
            result = TRUE;
        }
        break;
        default:
        break;
    }

    return result;
}
*/
/**
 * @brief   Sends a byte via usart bus.\n
 *
 * @date    Apr 12, 2013
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 *
 * @param   msg [in] [The byte to be sent.]
 */

//void DRV_usart_485_tx(uint8_t msg)
//{
//    if(paritymode != PARITY_NONE)
//    {
//        TXSTA1bits.TX9D = DRV_tx_parity(msg);
//    }
//    TXREG1 = msg;
//}

/**
 * @brief   Sends a byte via usart bus.\n
 *
 * @date    Apr 12, 2013
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 *
 * @param   msg [in] [The byte to be sent.]
 */
//void DRV_usart_usb_tx(uint8_t msg)
//{
//    if(paritymode != PARITY_NONE)
//    {
//        TXSTA2bits.TX9D = DRV_tx_parity(msg);
//    }
//    TXREG2 = msg;
//}

/**
 * @brief   Config the baud and the parity.\n
 *
 * @date    Jun 05, 2014
 * @author  yoda-yude.zhang <yoda-yude.zhang@cn.abb.com>
 *
 * @param   baud   [in] [The baud to be set.]
 *           parity [in] [The parity to be set.]
 */

//void DRV_usart_cfg(DRV_usart_baud_t baud,DRV_usart_parity_t parity)
//{
//    paritymode = parity;
//
//    /* Initialize modbus stack again with new communication parameters */
//    EXT_modbus_init();
//
//    switch(baud)
//    {
//        case BAUD_1200:
//        {
//            SPBRGH1 = 0x0D;
//            SPBRG1  = 0x04;
//            SPBRGH2 = 0x0D;
//            SPBRG2  = 0x04;
//        }
//        break;
//        case BAUD_2400:
//        {
//            SPBRGH1 = 0x06;
//            SPBRG1  = 0x82;
//            SPBRGH2 = 0x06;
//            SPBRG2  = 0x82;
//        }
//        break;
//        case BAUD_4800:
//        {
//            SPBRGH1 = 0x03;
//            SPBRG1  = 0x41;
//            SPBRGH2 = 0x03;
//            SPBRG2  = 0x41;
//        }
//        break;
//        case BAUD_9600:
//        {
//            SPBRGH1 = 0x01;
//            SPBRG1  = 0xA0;
//            SPBRGH2 = 0x01;
//            SPBRG2  = 0xA0;
//        }
//        break;
//        case BAUD_19200:
//        {
//            SPBRGH1 = 0x00;
//            SPBRG1  = 0xCF;
//            SPBRGH2 = 0x00;
//            SPBRG2  = 0xCF;
//        }
//        break;
//        case BAUD_38400 :
//        {
//            SPBRGH1 = 0x00;
//            SPBRG1  = 0x68;
//            SPBRGH2 = 0x00;
//            SPBRG2  = 0x68;
//        }
//        break;
//        default:
//            break;
//    }
//    if(parity == PARITY_NONE)
//    {
//        TXSTA1bits.TX9 = 0;// set the 8-bit
//        RCSTA1bits.RX9 = 0;// set the 8-bit
//        TXSTA2bits.TX9 = 0;// set the 8-bit
//        RCSTA2bits.RX9 = 0;// set the 8-bit
//    }
//    else
//    {
//        TXSTA1bits.TX9 = 1;// set the 9-bit
//        RCSTA1bits.RX9 = 1;// set the 9-bit
//        TXSTA2bits.TX9 = 1;// set the 9-bit
//        RCSTA2bits.RX9 = 1;// set the 9-bit
//    }
//}
 

/**
 * @brief   Sends a byte via usart bus for factory test.\n
 *
 * @date    Feb 12, 2014
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 *
 * @param   msg [in] [The byte to be sent.]
 */
void DRV_usart_tx(uint8_t msg)
{
    RCSTA2bits.CREN=0b0;
    TXSTA2bits.TXEN=0b1;
    /* Wait until tx buffer is empty */
    while (!TX2IF);
    TXREG2 = msg;
    /* Wait last char is transmitted*/
    while(!TXSTA2bits.TRMT);
    TXSTA2bits.TXEN=0b0;
    RCSTA2bits.CREN=0b1;
}


/**
 * @brief   Send one char data by serial port.
 * @date    Apr 17, 2013
 * @author  Bill-bihao.dai<bihao.dai@cn.abb.com>
 *
 * @param   c  [IN]  [char data]
 * @return  void
 */
void DRV_usart_putchar(uint8_t c)
{
    if ('\n' == c)
    {
        DRV_usart_tx('\r');
    }
    else DRV_usart_tx(c);
}

/**
 * @brief   Judge if the data is a digit. no-digit return FALSE
 * @date    Jul 16, 2013
 * @author  Bill-Bihao.dai<bihao.dai.liu@cn.abb.com>
 *
 * @param   data  [in]  [The data will be judged whether a digit]
 * @return  byte  [return TRUE if is a digit, otherwise return FALSE]
 */
static uint8_t _is_digit(uint8_t data)
{
    if (data >= '0' && data <= '9')
    {
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief   Judge if the data is a valid letter. if not return
 * @date    Jul 16, 2013
 * @author  Bill-Bihao.dai<bihao.dai.liu@cn.abb.com>
 *
 * @param   data  [in]  [The data will be judged whether a valid letter]
 * @return  byte  [return TRUE if is a valid letter, otherwise return FALSE]
 */
static uint8_t _is_valid_letter(uint8_t data)
{
    if (data >= 'A' && data <= 'Z')
    {
        return TRUE;
    }
    else if (data >= 'a' && data <= 'z')
    {
        return TRUE;
    }
    else if ('-' == data || '_' == data)//support charactor "-" and "_"
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief   Dispose the received data when serial mode is command mode
 * @date    Apr 17, 2013
 * @author  Bill-bihao.dai<bihao.dai@cn.abb.com>
 *
 * @param   data  [IN]  [received char data]
 * @return  void
 */
void DRV_usart_rx(uint8_t data)
{
    if (0x0D == data) /* Enter */
    {
        DRV_usart_putchar('\n');
        sci_rx_flag = 1;
        uart_rx_cnt = 0;
    }
    else if ((0x08 == data) /* Backspace */ ||
             (0x7F == data) /* Delete */ )
    {
        if (0 != uart_rx_cnt)
        {
            DRV_usart_putchar('\b');
            DRV_usart_putchar(' ');
            DRV_usart_putchar('\b');
            uart_rx_cnt--;
            serial_in_buf[uart_rx_cnt] = 0;
        }
    }
    else if (_is_valid_letter(data) || _is_digit(data))
    {
        if (uart_rx_cnt < SERIAL_BUF_LEN)
        {
            serial_in_buf[uart_rx_cnt++]=data;
            DRV_usart_putchar(data);
        }
    }
    else
    { }
}

/**
 * @brief   Check if specific serial port has received a string. If has been received, copy the string to data.
 * @date    Apr 17, 2013
 * @author  Bill-bihao.dai<bihao.dai@cn.abb.com>
 *
 * @param   daten    [IN]  [The buffer used to store the data]
 *          buf_len  [IN]  [data's length]
 * @return  boolean  [SUCCESS-TRUE, FAILED-FALSE]
 */
boolean DRV_usart_read_cmd(uint8_t *data, uint8_t buf_len)
{
    uint8_t *pc_tmp;
    if (buf_len >= SERIAL_BUF_LEN)
    {
        buf_len = SERIAL_BUF_LEN - 1;
    }

    if (sci_rx_flag) // New string received
    {
        pc_tmp = strcpy(data, serial_in_buf);
        sci_rx_flag = 0; // Clear new string flag
        pc_tmp = memset(serial_in_buf, 0, sizeof(serial_in_buf));
        return TRUE;
    }
    else
    {
        *data = 0;
        return FALSE;
    }

}


#if defined(SLC_DEBUG)
/**
 * @brief   Sends a byte via usart bus for factory test.\n
 *
 * @date    Feb 12, 2014
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 *
 * @param   msg [in] [The byte to be sent.]
 */
void putch(uint8_t msg)
{
    /* Wait until tx buffer is empty */
    while (!TX2IF);
    TX2REG = msg;
    /* Wait last char is transmitted*/
    while(!TXSTA2bits.TRMT);
}
#endif

