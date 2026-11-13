#ifndef _RTC_DRV_H_
#define _RTC_DRV_H_

#include "Config.h"
#include "I2C.h"
#include "UART.h"

#define NUMBER  7
#define	REG		4
#define	RTC_dev_addr	(0x51 << 1)  

typedef struct time {
    u16 year;
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 week;
    u8 month;
    u8 century;
} rtc_t;


typedef struct alarm {
    u16 year;
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 week;
    u8 month;
} rtc_a;

typedef enum{
	
	HZ_4096  = 0x00,
    HZ_64    = 0x01,
    HZ_1     = 0x02,
    HZ_60    = 0x03	

}timer_type;

void rtc_write(rtc_t rtc_write);

void rtc_read(rtc_t *rtc_read);

void Alarm_setting(rtc_a set);

void Alarm_detection(u8 Flag);

void Reminder_elimination();

void timer_setting(timer_type types,u8 count);

void timer_enable(u8 flag);

void timer_clear();

void time_alignment();

#endif