#ifndef _APP_H
#define _APP_H


#include "Config.h"
#include "i2c_oled.h"
#include "PWM.h"
#include "Switch.h"
#include "NVIC.h"
#include "ADC.h"
#include <string.h>

//LEDÒý½Å
#define LED_SW  P45
#define LED1    P27
#define LED2    P26
#define LED3    P15
#define LED4    P14
#define LED5    P23
#define LED6    P22
#define LED7    P21
#define LED8    P20


//ÈÎÎñ
#define TASK_SPI_OLED       1
#define TASK_I2C_OLED       2
#define TASK_KEYS           3
#define TASK_LED            4  
#define TASK_NTC            5
#define TASK_MOTOR          6
#define TASK_RTC            7
#define TASK_SEG            8
#define TASK_DHT            9
#define TASK_BUZZER         10

extern int g_cur_pos;
extern int g_pre_pos;
extern int menu_len;

void LED_Display(void);
void LED_Close(void);

void NTC_Display(void);

void Motor_Display(void);
void Motor_Close(void);

void RTC_Display(void);
void week_convert(void);

void Seg_Display(void);
void Seg_Close(void);

void DHT_Display(void);

void BUZZER_Display(void);
void BUZZER_Close(void);

void Is_Screen_OLED_Clear(u8 screen_clear);
    
#endif