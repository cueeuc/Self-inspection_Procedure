#include "init.h"

/****************  GPIO初始化函数 *****************/
void	GPIO_config(void)
{
    //UART串口引脚初始化
    P3_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1);
    
//	//数码管引脚初始化
	P4_MODE_IO_PU(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
    
	//独立按键引脚初始化
	P5_MODE_IO_PU(GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	
    //LED引脚初始化
    P4_MODE_OUT_PP(GPIO_Pin_5);
    P2_MODE_OUT_PP(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7);
    P1_MODE_OUT_PP(GPIO_Pin_4|GPIO_Pin_5);
    
//	//蜂鸣器引脚初始化
    P0_MODE_OUT_PP(GPIO_Pin_0);
//	
//	//振动马达引脚初始化
//	P0_MODE_OUT_PP(GPIO_Pin_1);
//	
//	//RTC时钟引脚初始化
	P3_MODE_IO_PU(GPIO_Pin_7);
	
    //I2C_OLED显示屏引脚初始化
    P3_MODE_OUT_OD(GPIO_Pin_2 | GPIO_Pin_3);
    
//	//电位器引脚初始化
	P0_MODE_IN_HIZ(GPIO_Pin_5);
//    
//    //NTC热敏电阻引脚初始化
    P0_MODE_IN_HIZ(GPIO_Pin_4);
//    
//    //温湿度传感器引脚初始化
    P4_MODE_IO_PU(GPIO_Pin_6);    
    
    //按键矩阵引脚初始化
    P0_MODE_IO_PU(GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7);
	P1_MODE_IO_PU(GPIO_Pin_7);
	P3_MODE_IO_PU(GPIO_Pin_4|GPIO_Pin_5);
	P4_MODE_IO_PU(GPIO_Pin_0|GPIO_Pin_1);
}

/***************  串口初始化函数 *****************/
void	UART_config(void)
{
    COMx_InitDefine		COMx_InitStructure;					//结构定义

    COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;	//模式, UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
    COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1, BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
    COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率, 一般 110 ~ 115200
    COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
    COMx_InitStructure.BaudRateDouble = DISABLE;			//波特率加倍, ENABLE或DISABLE
    UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口1 UART1,UART2,UART3,UART4
    NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

    UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}


/****************  I2C初始化函数 *****************/
void	I2C_config(void)
{
	I2C_InitTypeDef		I2C_InitStructure;

	I2C_InitStructure.I2C_Mode      = I2C_Mode_Master;	// 主从选择   I2C_Mode_Master, I2C_Mode_Slave
	I2C_InitStructure.I2C_Enable    = ENABLE;			// I2C功能使能,   ENABLE, DISABLE
	I2C_InitStructure.I2C_MS_WDTA   = DISABLE;			// 主机使能自动发送,  ENABLE, DISABLE
	I2C_InitStructure.I2C_Speed     = 13;				// 总线速度=Fosc/2/(Speed*2+4),      0~63

	I2C_Init(&I2C_InitStructure);
   
	NVIC_I2C_Init(I2C_Mode_Master,DISABLE,Priority_0);	//主从模式, I2C_Mode_Master, I2C_Mode_Slave; 中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

   // 引脚选择
	I2C_SW(I2C_P33_P32);					//I2C_P14_P15,I2C_P24_P25,I2C_P33_P32
}

/******************* AD配置函数 *******************/
void	ADC_config(void)
{
	ADC_InitTypeDef		ADC_InitStructure;		//结构定义

	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X16T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);				//ADC电源开关, ENABLE或DISABLE
	NVIC_ADC_Init(DISABLE,Priority_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
}

/******************** INT配置 ********************/
void	Exti_config(void)
{
    EXTI_InitTypeDef	Exti_InitStructure;					//结构定义
    Exti_InitStructure.EXTI_Mode      = EXT_MODE_Fall;  //中断模式,   EXT_MODE_RiseFall,EXT_MODE_Fall
    Ext_Inilize(EXT_INT3,&Exti_InitStructure);				//初始化

    NVIC_INT3_Init(ENABLE,Priority_0);		                //中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

}


void sys_init(void)
{
    EAXSFR();// 扩展寄存器访问使能 
	GPIO_config();
    UART_config();
	I2C_config();
    ADC_config();
    Exti_config();
    EA=1;
}
void motor_init(){
    
}