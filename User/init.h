#ifndef _INIT_H
#define _INIT_H

#include "I2C.h"
#include "GPIO.h"
#include "NVIC.h"
#include "Switch.h"
#include "UART.h"
#include "ADC.h"
#include "Exti.h"

void	GPIO_config(void);
void	UART_config(void);
void	I2C_config(void);
void	ADC_config(void);
void sys_init(void);


#endif