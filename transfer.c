/* 
 * File:   transfer.c
 * Author: Administrator
 *
 * Created on 2015?7?22?, ??10:23
 */

#include <stdio.h>
#include <stdlib.h>

char buffer[33]; 
char *inttohex(uint8_t aa)
{
    static uint8_t i = 0;
    if (aa < 16)           
    {
        if (aa < 10)      
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
        buffer[i+1] = '\0';  
    }
    else
    {
        inttohex(aa / 16); 
        i++;                
        aa %= 16;           
        if (aa < 10)       
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
    }
    return (buffer);
} 

