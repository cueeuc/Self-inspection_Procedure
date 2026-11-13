#include "APP.h"
#include "seg_driver.h"
#include "timer.h"

u8 num[] = {0,1,2,3,4,5,6,7};
static int8 i = 0;

void Timer_Seg_config(void)
{
    TIM_InitTypeDef		TIM_InitStructure;						//结构定义
    //定时器2做16位自动重装, 中断频率为1000HZ
    TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;		//指定时钟源,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
    TIM_InitStructure.TIM_ClkOut    = DISABLE;				//是否输出高速脉冲, ENABLE或DISABLE
    TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);				//初值
    TIM_InitStructure.TIM_PS        = 0;					//8位预分频器(n+1), 0~255, (注意:并非所有系列都有此寄存器,详情请查看数据手册)
    TIM_InitStructure.TIM_Run       = ENABLE;				//是否初始化后启动定时器, ENABLE或DISABLE
    Timer_Inilize(Timer2,&TIM_InitStructure);				//初始化Timer2	  Timer0,Timer1,Timer2,Timer3,Timer4
    NVIC_Timer2_Init(ENABLE,NULL);		//中断使能, ENABLE/DISABLE; 无优先级
}

void Time_callback() {
    seg_display(num[i],i);
    i++;
    if(i>=8) {
        i = 0;
    }
}

void Seg_Display() {

}

void Seg_Close() {
    Timer2_Run(DISABLE);
    seg_write(0xFF,0x00);
}


void task_8() _task_ TASK_SEG{
    Timer_Seg_config();
    while(1) {
        Is_Screen_OLED_Clear(0);
        os_wait2(K_TMO,1);
    }
}