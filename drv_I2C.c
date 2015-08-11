/*
-----------------------------------------------------------------------------
 I2C driver for PIC18F46K22

 Author: Govind Mukundan
  ********************************* HISTORY ********************************
  Version : 1.0
  Date :
  Description: Initial Version
-----------------------------------------------------------------------------
*/
#include "I2C.h"
#include "drv_pin_map.h"
#include <i2c.h>
void DRV_I2C_init(void){
    PIN_DIR_SCL = PIN_INPUT;
    PIN_DIR_SDA = PIN_INPUT;
    PIN_ANS_SCL = PIN_ANS_DIGIT;
    PIN_ANS_SDA = PIN_ANS_DIGIT;
    SSP1CON1 = 0b00101000;
      /*         |||||||+----SSPxM<3:0>: Synchronous Serial Port Mode Select bits
       *         ||||||      1000 = I2C Master mode, clock = FOSC / (4 * (SSPxADD+1))(4)
       *         |||||
       *         |||+-------- CKP: Clock Polarity Select bit [NOT IN USE]
       *         |||          
       *         ||+--------- SSPxEN: Synchronous Serial Port Enable bit
       *         ||           1: Enables the serial port and configures the SDAx and SCLx pins as the source of the serial port pins
       *         ||           
       *         |+---------- SSPxOV: SSPxOV: [NOT IN USE]
       *         |            
       *         +-----------  WCOL: Write Collision Detect bit 
       */
    SSP1CON2 = 0b00000000;
    SSP1STATbits.CKE =0;
    SSP1STATbits.SMP =1;
    SSP1ADD =0x27;
}
void _I2C_Reset(void) {
    uint16_t temp = 1000;
    // Configure i2c interface
    SSP1ADD = 0x09; //400k for 16M Fcy
    temp = SSP1BUF; // clear RBF flag
}
//Resets the I2C bus to Idle

static void _reset_I2C_bus(void) {
    int x = 0;

    //initiate stop bit
    SSP1CON2bits.PEN = 1; //stop enble when set. 0 stop idle.

    //wait for hardware clear of stop bit
    while (SSP1CON2bits.PEN) {
        //__delay_us(10);
        x++;
        if (x > 1) break;
    }
    SSP1CON2bits.RCEN = 0; //Receive enable
    // IFS1bits.MI2C1IF = 0; // Clear Interrupt
    SSP1CON1bits.WCOL = 0; //When I2C can not send message, store the message in the buf
    //CPSTATbits.BCL = 0;
}

static boolean _I2C_Idle(void) {
    /* Wait until I2C Bus is Inactive */
    while (SSP1CON2bits.SEN || SSP1CON2bits.PEN || SSP1CON2bits.RCEN ||
            SSP1CON2bits.RSEN || SSP1CON2bits.ACKEN || SSP1STATbits.BF||SSP1STATbits.RW);
    return (TRUE);
}

static boolean _I2C_Start(void) {
    PIR1bits.SSP1IF = 0;
    // wait for module idle
    _I2C_Idle();
    // Enable the Start condition
    SSP1CON2bits.SEN = 1; //Start condition, Clear by hardware
    // Check for collisions
    if (SSP1CON1bits.WCOL) {//When I2C can not send message, store the message in the buf
        return (FALSE);
    } else {
        // wait for module idle
       _I2C_Idle();
        return (TRUE);
    }
}

static void _I2C_Stop(void) {

    int x = 0;
    PIR1bits.SSP1IF = 0;
    PIR2bits.BCL1IF = 0;
    // wait for module idle
    _I2C_Idle();
    //initiate stop bit
    SSP1CON2bits.PEN = 1;

    //wait for hardware clear of stop bit
    while (SSP1CON2bits.PEN) {//1 = Initiate Stop condition on SDAx and SCLx pins. Automatically cleared by hardware.
        // Delay10us(1);
        x++;
        if (x > 1) break;
    }
    SSP1CON2bits.RCEN = 0;//1=Enables Receive mode for I2C,0 = Receive idle
                        // IFS1bits.MI2C1IF = 0;
                        // Clear Interrupt
    SSP1CON1bits.WCOL = 0;//1 = A write to the SSPxBUF register was attempted while the I2C conditions were not valid for a transmission to
                        //be started No collision
    //  CPSTATbits.BCL = 0;
    // wait for module idle
    _I2C_Idle();
}

static boolean _I2C_SendByte(uint8_t data) {
    //while(CPSTATbits.TBF); //Wait till data is transmitted.
    PIR1bits.SSP1IF = 0;    //SSP1IF: Master Synchronous Serial Port 1 Interrupt Flag bit
                           //1 = The transmission/reception is complete (must be cleared by software)
                          //0 = Waiting to transmit/receive
    // Send the byte
    SSP1BUF = data;

    // Check for collisions
    if ((SSP1CON1bits.WCOL == 1)) {

        return (FALSE);
    } else {
        while (SSP1STATbits.BF); // wait until write cycle is complete
        if ((SSP1CON1bits.WCOL == 1)) {
            return (FALSE);
        } else {
            // wait for module idle
            _I2C_Idle();
            return (TRUE);
        }
    }
}

extern boolean I2C_Read_Reg(uint8_t add,uint8_t reg, uint8_t *rxPtr) {
    //check the BUS is idle?
    while(!_I2C_Idle());
    //1. i2c start
    _I2C_Start();

    //2. Set CP in W Mode 
    _I2C_SendByte(add<<1);

    //3. Check ACK
    _I2C_Idle();
    while (SSP1CON2bits.ACKSTAT == 1);
    if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ? 0 means getting the acknowledge.
    {
        // Means the write was fine
        //4.Now send the register number you want to read
        _I2C_SendByte(reg);

        //5.Issue a repeated start = a start cond without a prior stop
        _I2C_Start();

        //6. Set CP in R mode
        _I2C_SendByte((add<<1)+0b1);
        while (SSP1CON2bits.ACKSTAT == 1);
        _I2C_Idle();

        //7. check for ACK
       // _I2C_Idle();
       //while (SSP1CON2bits.ACKSTAT == 1);
        if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            _I2C_Idle();
            SSP1CON2bits.RCEN = 1; // enable master read
            while (SSP1CON2bits.RCEN); // wait for byte to be received !(CPSTATbits.RBF)
            PIR1bits.SSP1IF =0;           
            *rxPtr = SSP1BUF;
            // create a stop cond
            _I2C_Idle();
            // CPSTATbits.I2COV = 0;

            //set ACK to high
            SSP1CON2bits.ACKEN = 1;
            SSP1CON2bits.ACKDT = 1; // send nack            
            _I2C_Stop();
            return TRUE;
        }
    }
    return FALSE;
}
boolean I2C_Write_Reg(uint8_t add, uint8_t reg, uint8_t data) {
     //check the BUS is idle?
    while(!_I2C_Idle());
    //1. i2c start
    _I2C_Start();

    //2. Set CP in W Mode 
    _I2C_SendByte(add<<1);

    //3. Check ACK
    _I2C_Idle();
    while (SSP1CON2bits.ACKSTAT == 1);
    if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ? 0 means getting the acknowledge.
    {
        // Means the write was fine
        //4.Now send the register number you want to read
        _I2C_SendByte(reg);

        //5.Issue a repeated start = a start cond without a prior stop

        //6. Set CP in R mode
        while (SSP1CON2bits.ACKSTAT == 1);
        _I2C_Idle();

        //7. check for ACK
       // _I2C_Idle();
       //while (SSP1CON2bits.ACKSTAT == 1);
        if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ?
        {
            _I2C_SendByte(data);
            while (SSP1CON2bits.ACKSTAT == 1);
            PIR1bits.SSP1IF =0;           
            // create a stop cond
            _I2C_Idle();
            // CPSTATbits.I2COV = 0;         
            _I2C_Stop();
            PIR1bits.SSP1IF =0;  
            return TRUE;
        }
    }
    return FALSE;   
    
    
    
    
    
//    uint8_t i, flag;
//    flag = 0;
//    for (i = 0; i < 100; i++) {
//        //1. i2c start
//        _I2C_Start();
//        //2. Set CP in W Mode
//        _I2C_SendByte(add);
//        //3. Check ACK
//        _I2C_Idle();
//        if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ?
//        {
//            flag = 1;
//            break;
//        }
//
//    }
//    // 4.if write cmd was successful, put the data on the bus
//    if (flag == 1) {
//        _I2C_SendByte(reg);
//        _I2C_Idle();
//        if (SSP1CON2bits.ACKSTAT == 0) // Did we receive an ACK ?
//        {
//            _I2C_SendByte(data);
//        } else {
//            return FALSE;
//        }
//        _I2C_Stop();
//        return TRUE;
//    } else {
//        return FALSE;
//    }
}

