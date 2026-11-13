#include "APP.h"
#include "INIT.h"


#define PREQ			1000
#define PERIOD (MAIN_Fosc / PREQ)
PWMx_Duty duty;

void PWM_Motor_config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;

	PWMx_InitStructure.PWM_Mode    		=  CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    		=  0;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect  = ENO6P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM6, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period   = PERIOD - 1;					//周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;			//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB

	PWM6_SW(PWM6_SW_P01);					//PWM6_SW_P21,PWM6_SW_P54,PWM6_SW_P01,PWM6_SW_P75

	NVIC_PWM_Init(PWMB,DISABLE,Priority_0);
}


float rst_v = 0;//ADC电压值
float pwm_duty = 0;//PWM占空比

void task_6() _task_ TASK_MOTOR{
    
    u16 adc_value = 0;//ADC值
    
    EAXSFR();
    PWM_Motor_config();
    EA=1;
    
    while(1){
        adc_value = Get_ADCResult(ADC_CH13);
        
        rst_v = adc_value * 2.5 / 4096;
        
        pwm_duty = rst_v * 100 / 1.65;
        
        printf("ADC:%d, rst_v:%.2fV, pwm_duty:%.2f%%\n",(int)adc_value,rst_v,pwm_duty);
        
        duty.PWM6_Duty = PERIOD * pwm_duty / 100;
        UpdatePwm(PWM6, &duty);
        
        Is_Screen_OLED_Clear(0);

        os_wait2(K_TMO, 40);
    }
}

void Motor_Close() {
    // 禁用PWM6的通道输出
    // 这会立即停止PWM输出，电机停止    
    PWMB_CC6E_Disable();
}

void Motor_Display() {
    char motor_buf[32];
    sprintf(motor_buf,"rst_v:%.2fV",rst_v);
    OLED_ShowString(0,2,motor_buf,16);
    sprintf(motor_buf,"pwm_duty:%.2f%%",pwm_duty);
    OLED_ShowString(0,4,motor_buf,16);    
}