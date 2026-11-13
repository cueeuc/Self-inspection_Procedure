#include "key_driver.h"


// 状态保存变量，初始值 0x0F (二进制 0000 1111)，表示初始时 4 个按键全为释放(1)
u8 State_save=0x0F;

u8  Button_sel (u8 k) {
    switch(k) {
    case 0:return KEY1;
    case 1:return KEY2;
    case 2:return KEY3;
    case 3:return KEY4;
    default:return 0;
    }
}

void Judgment_button(void) {
    u8 i=0;
    // 思路：利用 State_save 记录上一次的状态，结合当前引脚电平，判断“边沿”（从按下到释放，或从释放到按下）
    for(i=0; i<4; i++) {
        if(IS_KEY_DOWN(i) && Button_sel(i)==UP) { // 检测 KEY-i 的释放动作
           
            task_button_up(i);
            SET_KEY_UP(i);
            
        } else if(IS_KEY_UP(i) && Button_sel(i)==DOWN) { // 检测 KEY-i 的按下动作
             
            task_button_down(i);
            SET_KEY_DOWN(i);
        }
    }
}