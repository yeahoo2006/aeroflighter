/**
 * Copyright 2012 ABB. All rights reserved.
 *
 * @file    lib_rprintf.c
 * @brief   UART print.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    Jul 12, 2013
 *******************************************************************************
 * History_Begin
 *
 * Revision 1.00  from  Jul 12, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 *
 * History_End
 */

#include <stdarg.h>
#include "stddef.h"
#include "api.h"
#include "drv_compiler.h"
#include "drv_usart.h"
#include "lib_rprintf.h"


#define BUFFER_SIZE 12U
#define BASE_DEC	10U
#define BASE_HEX	16U

/**
 * @brief   convert integer numbers to output string according to:
 *           sign, number base\n
 *           Migrated from project MIO 2013-05-30 by Fox-Lilei.Zhai.
 *
 * @date    Jan 29, 2013
 * @author  Kimi-Jijun.MA <Kimi-Jijun.MA@cn.abb.com>
 *
 * @param   is_signed [in] [whether it is signed or unsigned.]
 * @param   signed_value [in] [value that need to output]
 * @param   num_base [in] [number base to output, 10 - decimal, 16 - hexdecimal]
 */
static void _convert_value(boolean is_signed, uint32_t unsigned_val, uint8_t num_base)
{
    uint8_t outputbuf[BUFFER_SIZE];
    uint8_t *strptr = NULL;

    if(is_signed)
    {
        DRV_usart_putchar('-');
    }

    strptr = outputbuf;
    *strptr = 0U;
    do
    {
        uint8_t ch = unsigned_val % num_base + '0';
        if (ch > '9')
        {
                ch = ch - '9' - 1 + 'A';
        }
        strptr++;
        *strptr = ch;
        unsigned_val /= num_base;
    }
    while (unsigned_val);

    while(*strptr)
    {
        DRV_usart_putchar(*strptr);
        strptr--;
    }
}

/**
 * @brief   print output with format\n
 *
 *           WARNING: be careful while using thie function.
 *                    Do necessary type casting to get correct output.
 *           Placeholders | Parameter type
 *           -----------------------------
 *               %c %C    |    uint8_t
 *               %s %S    |    uint8_t *
 *               %d %D    |    int16_t
 *               %u %U    |    uint16_t
 *               %i %I    |    int32_t
 *               %l %L    |    uint32_t
 *               %x %X    |    uint32_t
 *
 *           Migrated from project MIO 2013-05-30 by Fox-Lilei.Zhai.
 *           Rewrote code and comments 2013-07-24 by Fox-Lilei.Zhai
 *
 * @date    Jan 29, 2013
 * @author  Kimi-Jijun.MA <Kimi-Jijun.MA@cn.abb.com>
 *
 * @param   format_str [in] [variable format string]
 */
void rprintf(const uint8_t *format_str, ...) {
    uint8_t next_char = 0U;
    uint8_t *strptr = NULL;
    boolean is_signed = FALSE;
    int32_t int32_val = 0;
    uint32_t uint32_val = 0;
    uint8_t  uint8_val = 0;
    int16_t int16_val = 0;
    uint16_t uint16_val = 0;
    uint32_t convert_val = 0;
    va_list args;
    va_start(args, format_str);

    for (;;)
    {
        next_char = *format_str;
        format_str++;
        /* Output until next '%' */
        while (next_char != '%')
        {
            if (!next_char)
            {
                va_end(args);
                return;
            } else {
                DRV_usart_putchar(next_char);
                next_char = *format_str;
                format_str++;
            }
        }

        is_signed = FALSE;
        next_char = *format_str;
        format_str++;

        switch (next_char) {
            case '%':
                DRV_usart_putchar('%');
                break;
                
            case 'c':
            case 'C':
                next_char = (uint8_t) va_arg(args, uint8_t);
                DRV_usart_putchar(next_char);
                break;
            case 's':
            case 'S':
                strptr = (uint8_t*) va_arg(args, uint8_t *);
                while (*strptr)
                {
                    DRV_usart_putchar(*strptr);
                    strptr++;
                }
                break;

            case 'd':
            case 'D':
                int16_val = va_arg(args, int16_t);
                if (int16_val < 0)
                {
                    is_signed = TRUE;
                    convert_val = (uint32_t)0 - int16_val;
                }
                else
                {
                    is_signed = FALSE;
                    convert_val = (uint32_t)int16_val;
                }
                _convert_value(is_signed, convert_val, BASE_DEC);
                break;
            case 'u':
            case 'U':
                is_signed = FALSE;
                uint16_val = va_arg(args, uint16_t);
                _convert_value(is_signed, (uint32_t)(uint16_val), BASE_DEC);
                break;

            case 'i':
            case 'I':
                int32_val = va_arg(args, int32_t);
                if (int32_val < 0)
                {
                    is_signed = TRUE;
                    convert_val = (uint32_t)0 - int32_val;
                }
                else
                {
                    is_signed = FALSE;
                    convert_val = (uint32_t)int32_val;
                }
                _convert_value(is_signed, convert_val, BASE_DEC);
                break;
            case 'l':
            case 'L':
                is_signed = FALSE;
                uint32_val = va_arg(args, uint32_t);
                _convert_value(is_signed, uint32_val, BASE_DEC);
                break;
                
            case 'x':
            case 'X':
                is_signed = FALSE;
                uint32_val = va_arg(args, uint32_t);
                _convert_value(is_signed, uint32_val, BASE_HEX);
                break;

            case 'h':
            case 'H':
                is_signed = FALSE;
                uint8_val = va_arg(args, uint8_t);
                if (uint8_val <= 0x0F)
                {
                    DRV_usart_putchar('0');
                }
                _convert_value(is_signed, uint8_val, BASE_HEX);
                break;

            default:
                DRV_usart_putchar(next_char);
                break;
        }
    }
}

/* Call the following function to see if rprintf works fine for your chip */
#ifdef CHIP_RPRINTF
void rprintf_test(void)
{
    rprintf("============ rprintf testing ============\n");
    rprintf("%%c[%c] %%C[%C]\n", 'a', 'A');
    rprintf("%%s[%s] %%S[%S]\n", "Hello", "world");
    rprintf("-----------------------------------------\n");
    {
        int16_t value = -32768;
        rprintf("-32768: %%d[%d] %%D[%D]\n", value, value);
        value = 0;
        rprintf("0: %%d[%d] %%D[%D]\n", value, value);
        value = 32767;
        rprintf("32767: %%d[%d] %%D[%D]\n", value, value);
    }
    rprintf("-----------------------------------------\n");
    {
        uint16_t value = 0;
        rprintf("0: %%u[%u] %%U[%U]\n", value, value);
        value = 65535;
        rprintf("65535: %%u[%u] %%U[%U]\n", value, value);
    }
    rprintf("-----------------------------------------\n");
    {
        int32_t value = -2147483648;
        rprintf("-2147483648: %%i[%i] %%I[%I]\n", value, value);
        value = 0;
        rprintf("0: %%i[%i] %%I[%I]\n", value, value);
        value = 2147483647;
        rprintf("2147483647: %%i[%i] %%I[%I]\n", value, value);
    }
    rprintf("-----------------------------------------\n");
    {
        uint32_t value = 0;
        rprintf("0: %%l[%l] %%L[%L]\n", value, value);
        value = 4294967295;
        rprintf("4294967295: %%l[%l] %%L[%L]\n", value, value);
    }
    rprintf("-----------------------------------------\n");
    {
        uint32_t value = 0;
        rprintf("0: %%x[%x] %%X[%X]\n", value, value);
        value = 0xFFFF;
        rprintf("0xFFFF: %%x[%x] %%X[%X]\n", value, value);
    }
}
#endif

