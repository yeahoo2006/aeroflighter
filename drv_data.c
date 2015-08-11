
#include "I2C.h"
#include "data.h"
#include "api.h"
uint16_t Calib_acc_z(){
for (int i=0;i<100;i++)
{
    I2C_Read_Reg(ACC_ADDR,ACC_Z0,&var1);
    I2C_Read_Reg(ACC_ADDR,ACC_Z1,&var2);
    var3=(var1)+(var2<<8);
    temp_var3 += var3;
    var3 = 0;
}
calib_acc_z = temp_var3 / 100;
off_acc_z =round((calib_acc_z -255) / 4);
}

uint16_t Calib_acc_x(){
for (int i=0;i<100;i++)
{
    I2C_Read_Reg(ACC_ADDR,ACC_X0,&var4);
    I2C_Read_Reg(ACC_ADDR,ACC_X1,&var5);
    var6=(var4)+(var5<<8);
    temp_var6 += var6;
    var6 = 0;
}
calib_acc_x = temp_var6 / 100;
off_acc_x = round((calib_acc_x) / 4);
}

uint16_t Calib_acc_y(){
for (int i=0;i<100;i++)
{
    I2C_Read_Reg(ACC_ADDR,ACC_Y0,&var7);
    I2C_Read_Reg(ACC_ADDR,ACC_Y1,&var8);
    var9=(var7)+(var8<<8);
    temp_var9 += var9;
    var9 = 0;
}
calib_acc_y = temp_var9 / 100;
off_acc_y = round((calib_acc_y) / 4);
}


boolean _init_acc(){
       I2C_Read_Reg(ACC_ADDR,DEVID,&device);
       I2C_Write_Reg(ACC_ADDR,ACC_DATA_FORMAT,0x0B);
       I2C_Write_Reg(ACC_ADDR,POWER_CTL,0x08);
       I2C_Write_Reg(ACC_ADDR,INT_ENABLE,0x80);
       I2C_Write_Reg(ACC_ADDR,BW_RATE,0x0A);
       I2C_Write_Reg(ACC_ADDR,0x1E,off_acc_x);
       I2C_Write_Reg(ACC_ADDR,0x1F,off_acc_y);
       I2C_Write_Reg(ACC_ADDR,0x20,off_acc_z);
       //__delay_ms(2);
       return TRUE;
}

boolean _init_geoscope()
{
   I2C_Read_Reg(GYO_ADDR,0x0F,&var13);
   I2C_Write_Reg(GYO_ADDR,0x20,0x0f);   //
   I2C_Write_Reg(GYO_ADDR,0x21,0x00);   //
   I2C_Write_Reg(GYO_ADDR,0x22,0x08);   //
   I2C_Write_Reg(GYO_ADDR,0x23,0x00);  //
   I2C_Write_Reg(GYO_ADDR,0x24,0x00);
   return 1;
}

void obtain_gescope_x()
{
I2C_Read_Reg(GYO_ADDR,0x28,&var10);
I2C_Read_Reg(GYO_ADDR,0x29,&var11);
var12=(var10)+(var11<<8);
}
void obtain_gescope_y()
{
I2C_Read_Reg(GYO_ADDR,0x2A,&var15);
I2C_Read_Reg(GYO_ADDR,0x2B,&var16);
var17=(var15)+(var16<<8);
}
void obtain_gescope_z()
{
I2C_Read_Reg(GYO_ADDR,0x2C,&var18);
I2C_Read_Reg(GYO_ADDR,0x2D,&var19);
var20=(var18)+(var19<<8);
}

