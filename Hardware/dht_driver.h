#ifndef _DHT_H_
#define _DHT_H_

#define DH	P46

#include "Config.h"

#define Level_signal_change(flag,min,max,para)							                       \
do{                                                                                            \
	count = 0;                                                                                 \
	while(DH == flag){                                                                         \
		delay();                                                                               \
		count++;                                                                               \
	}                                                                                          \
	if(count < min || count > max){                                                            \
		printf("时间:[%dus],%s不在合理的[%dus %dus]范围\n",(int)count,para,(int)min,(int)max); \
		return -1;                                                                                \
	}                                                                                          \
}while(0)


void delay(void);

char DHT_data_read(u8 *arr);

int8 DHT_data_detect(void);

extern float humidity;
extern float temperature;

#endif