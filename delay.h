
 /*-----------------------------------------------------------------------
  Function: Delay us/ms/S
???? : PIC18F46K22
??: 64Mhz
-----------------------------------------------------------------------*/
#ifndef __delay_h
#define __delay_h
void delay_nus(unsigned int n);
void delay_nms(unsigned int n);
void delay_1us(void);
void delay_1ms(void) ;

void delay_1us(void)                 //1us????
  {
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
  }

void delay_nus(unsigned int n)       //N us????
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1us();
  }

void delay_1ms(void)                 //1ms????
  {
   unsigned int i;
   for (i=0;i<500;i++);
  }

void delay_nms(unsigned int n)       //N ms????
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }


