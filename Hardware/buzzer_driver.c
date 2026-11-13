#include "buzzer_driver.h"


#define BUZZER P00

//			 C	 D     E 	F	 G	  A	   B	 C`
static u16  hz2[] = {523, 587, 659, 698, 784, 880, 988, 1047};

//			             C`	   D`     E`   F`	  G`	A`	  B`    C``
static u16  hz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};

// 1 -  7
// 8 - 15
//16 - 23
u16  FREQS[] = {
	262, 294, 330, 349, 392, 440, 494,       // L1~L7 (低音)
	523, 587, 659, 698, 784, 880, 988,       // N1~N7 (中音)
	1047, 1175, 1319, 1397, 1568, 1760, 1976, // H1~H7 (高音)
};



/***************  PWM配置函数 *****************/
void PWM_Buzzer_config(u16 hz_output)
{
    PWMx_InitDefine		PWMx_InitStructure;

    u16 period = (MAIN_Fosc / hz_output);
    
    PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWMx_InitStructure.PWM_Duty    =  0;								//PWM占空比时间, 0~Period
    PWMx_InitStructure.PWM_EnoSelect  = ENO5P;	//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_Configuration(PWM5, &PWMx_InitStructure);

    PWMx_InitStructure.PWM_Period   = period-1;					//周期时间,   0~65535
    PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
    PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
    PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
    PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
    
    
    PWM5_SW(PWM5_SW_P00);			//PWM4_SW_P16_P17,PWM4_SW_P26_P27,PWM4_SW_P66_P67,PWM4_SW_P34_P33

    // 初始化PWMA/B的中断
    NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}

void Buzzer_init(void){
    EAXSFR(); /* 扩展寄存器使能 */
    PWM_Buzzer_config(1000);
}

// 按照指定频率播放声音
void Buzzer_play(u16 hz_value){
//    PWM_config(hz_value);
    u16 period = (MAIN_Fosc / hz_value);
    u16 duty = period * 0.02f; // 这里的0.02可以决定音量大小
    
    // 设置PWMB输出Period (1/频率)
    PWMB_AutoReload(period - 1);	//周期设置
    // 设置PWM5的占空比
    PWMB_Duty5(duty);
    // 启用PWMB通道5的输出使能
    PWMB_CC5E_Enable();
}

void Buzzer_beep(u16 tone){ // 1,2,3,4,5,6,7,8
    if (tone == 0) {        // 如果是休止符
        Buzzer_stop();      // 直接静音
        return;
    }
    Buzzer_play(FREQS[tone - 1]);
}

void Buzzer_stop(void){
    PWMB_CC5E_Disable(); // 单独关闭PWMB的通道5输出
}