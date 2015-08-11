/**
 * Copyright 2012 ABB. All rights reserved.
 *
 * @file    test.c
 * @brief   Test for the program.\n
 *         
 * @author  Will-liang.he@cn.abb.com
 * @date    Apr 25, 2015
 *******************************************************************************
 * History_Begin 
 * 
 * Revision 1.00  from Apr 25, 2015\n
 * Developer    Will-liang.he <Will-liang.he@cn.abb.com>\n
 * Description  Initial version\n
 * When modification start, add this information
 * 
 * History_End 
 */
#include "data.h"
#include "test.h"
#include "drv_pin_map.h"
#include "lib_rprintf.h"
#include <stdlib.h>
#include<string.h>
#include "api.h"
uint8_t received_buf[SERIAL_BUF_LEN];

