#ifndef __SPI_OLED_H
#define __SPI_OLED_H

#include "Config.h"
#include "delay.h"

sbit SPI_OLED_SCL=P5^0;   // SCLK
sbit SPI_OLED_SDA=P1^3;   // MOSI
sbit SPI_OLED_DC=P1^6;      
sbit SPI_OLED_CS=P4^7;      
sbit SPI_OLED_READ_FS0=P1^1; // MISO
sbit SPI_OLED_ROM_CS=P1^0;

#define u8  unsigned char
#define u32 unsigned long
#define SPI_OLED_CMD  0   //写命令
#define SPI_OLED_DATA 1   //写数据

#define SPI_OLED_SCL_Set()       SPI_OLED_SCL=1;
#define SPI_OLED_SCL_Clr()       SPI_OLED_SCL=0;

#define SPI_OLED_SDA_Set()       SPI_OLED_SDA=1;
#define SPI_OLED_SDA_Clr()       SPI_OLED_SDA=0;

#define SPI_OLED_DC_Set()        SPI_OLED_DC=1;
#define SPI_OLED_DC_Clr()        SPI_OLED_DC=0;

#define SPI_OLED_CS_Set()        SPI_OLED_CS=1;
#define SPI_OLED_CS_Clr()        SPI_OLED_CS=0;

#define SPI_OLED_ROM_CS_Set()    SPI_OLED_ROM_CS=1;
#define SPI_OLED_ROM_CS_Clr()    SPI_OLED_ROM_CS=0;

//void delay_ms(unsigned int ms);
void SPI_OLED_ColorTurn(u8 i);                              // 设置颜色反转模式，i=0正常显示（黑底白字），i=1反转显示（白底黑字）
void SPI_OLED_DisplayTurn(u8 i);                            // 设置屏幕旋转方向，i=0正常显示（0°），i=1旋转180°显示
void SPI_OLED_WR_Byte(u8 dat, u8 cmd);                     // SPI发送1字节数据，cmd=0表示发送命令，cmd=1表示发送显示数据
void SPI_OLED_Clear(void);                                 // 清空整个OLED屏幕，全部像素熄灭（或点亮，取决于颜色反转设置）
void SPI_OLED_address(u8 x, u8 y);                         // 设置光标位置，x为列地址（0~127），y为页地址（0~7，每页8像素行）
void SPI_OLED_Display_128x64(u8 *dp);                      // 显示一整屏128x64像素的位图数据，dp指向位图数组的首地址
void SPI_OLED_Display_16x16(u8 x, u8 y, u8 *dp);           // 在(x,y)位置显示16x16像素的汉字或图标，dp指向字模数据首地址
void SPI_OLED_Display_8x16(u8 x, u8 y, u8 *dp);            // 在(x,y)位置显示8x16像素的字符（如ASCII码），dp指向字模数据首地址
void SPI_OLED_Display_5x7(u8 x, u8 y, u8 *dp);             // 在(x,y)位置显示5x7像素的小字符，dp指向字模数据首地址
void Send_Command_to_ROM(u8 dat);                          // 向外部SPI Flash存储器发送1字节命令（如读数据指令、地址设置等）
u8 Get_data_from_ROM(void);                                // 从外部SPI Flash存储器读取1字节数据并返回
void SPI_OLED_get_data_from_ROM(u8 addrHigh, u8 addrMid, u8 addrLow, u8 *pbuff, u8 DataLen);
                                                            // 从外部SPI Flash的24位地址(addrHigh<<16 | addrMid<<8 | addrLow)开始，读取DataLen字节数据到pbuff缓冲区
void SPI_OLED_Display_GB2312_string(u8 x, u8 y, u8 *text); // 显示GB2312编码的中文字符串（每个汉字16x16像素），text为字符串指针
void SPI_OLED_Display_string_5x7(u8 x, u8 y, u8 *text);    // 显示5x7像素的英文字符串（ASCII码），text为字符串指针
void SPI_OLED_ShowNum(u8 x, u8 y, float num, u8 len);      // 在(x,y)位置显示浮点数num，len为显示的总位数（包含小数点和符号位）
void SPI_OLED_Init(void);                                  // 初始化OLED屏幕，包括SPI接口配置、复位、设置显示参数（亮度/对比度/寻址模式等）
#endif