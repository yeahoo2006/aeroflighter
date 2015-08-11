/**
 * Copyright 2013 ABB. All rights reserved.
 *
 * @file    drv_compiler.h
 * @brief   Contains compiler specific things.\n
 *
 * @author  fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>
 * @date    Apr 22, 2013
 *******************************************************************************
 * History_Begin 
 * 
 * Revision 1.00  from  Apr 22, 2013\n
 * Developer    fox-lilei.zhai <fox-lilei.zhai@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 * 
 * History_End 
 */

#ifndef DRV_COMPILER_H_
#define DRV_COMPILER_H_

/*
 * CCI implementation comments:
 *
 * 1. Use "" to include header files that are not provided by the compiler.
 *    Although all header file folders are added in "-I" command line parameter,
 *    which means we can use <> to include them,
 *    we still use "" to make a difference with <>.
 */
#include <xc.h>
#include <stddef.h>
#include <stdint.h>

/*
 * Do NOT define bit as boolean
 * as bit variables cannot be auto variables or function parameters
 */
typedef unsigned char boolean;
/*
 * Default "char" in 8-bit compilers are "unsigned char"
 * Default "char" in 16- and 32-bit compilers are "signed char"
 * DO use "unsigned"/"signed" for char declarations.
 */

#define TRUE            1
#define FALSE           0

#define SUCCESS         1
#define FAIL            0

#define _XTAL_FREQ  64000000 /* Set it to FOSC so that __delay_xx() library works */

#endif /* DRV_COMPILER_H_ */
