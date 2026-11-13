#include "APP.h"
#include "ntc_driver.h"

int temp = 0;

void NTC_Display() {
    char buf_NTC[32]="";
    sprintf(buf_NTC,"temp: %d",(int)temp);
    OLED_ShowString(0,2,buf_NTC,16);
}

void task_5() _task_ TASK_NTC{
    while(1) {
        temp = measure_temp();
        Is_Screen_OLED_Clear(0);
        os_wait2(K_TMO,20);
    }
}