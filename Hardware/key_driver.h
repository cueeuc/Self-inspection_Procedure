#ifndef _KEY_H
#define _KEY_H

#include "Config.h"

#define KEY1 P51
#define KEY2 P52
#define KEY3 P53
#define KEY4 P54

#define DOWN    0
#define UP      1

// 检查按键 k 当前是否为按下状态
#define IS_KEY_DOWN(k)      (((State_save>>k)&0x01) == DOWN)

// 检查按键 k 当前是否为释放状态
#define IS_KEY_UP(k)        (((State_save>>k)&0x01) == UP)

// 将按键 k 的状态标记为按下（清除位）：State_save 的第 k 位清零
#define SET_KEY_DOWN(k)      (State_save &= ~(1L<<k))

// 将按键 k 的状态标记为释放（置位）：State_save 的第 k 位置 1
#define SET_KEY_UP(k)        (State_save |= (1L<<k))

extern void task_button_down(u8 key_index);
extern void task_button_up(u8 key_index);

void Judgment_button(void);

#endif