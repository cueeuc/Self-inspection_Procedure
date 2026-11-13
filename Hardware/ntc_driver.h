#ifndef _NTC_H
#define _NTC_H

#include "Config.h"
#include "ADC.h"


#define len   sizeof(temp_table) / sizeof(temp_table[0]) 
#define Absolute_value(value)  ((value>0) ? (value) : (-(value)))

int search_temp(float ntc_Rx100);
int measure_temp(void);

#endif