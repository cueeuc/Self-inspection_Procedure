#ifndef _SEG_H
#define _SEG_H

#include "Config.h"

#define NIX_DI      P44     //串行数据
#define NIX_SCK     P42     //移位时钟
#define NIX_RCK     P43     //锁存时钟

#define GET_BIT_VAL(byte, pos)  (byte & (1L << pos))

void seg_write(u8 Get_byte,u8 Get_seg);

void seg_display(u8 s_num,u8 s_bit);

#endif