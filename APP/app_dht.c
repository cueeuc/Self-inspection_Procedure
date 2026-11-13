#include "APP.h"
#include "dht_driver.h"

float humidity = 0;
float temperature = 0;

void task_9() _task_ TASK_DHT{
    int8 rst= 0;
    while(1) {
        rst = DHT_data_detect();
        if(rst == SUCCESS) {
            printf("Êª¶È: %.2f%%,ÎÂ¶È: %.2f¡æ\n",humidity,temperature);
            Is_Screen_OLED_Clear(0);
        }
        os_wait2(K_TMO,400);
    }
}

void DHT_Display() {
    char buf_NTC[32]="";
    sprintf(buf_NTC,"humidity: %.2f",humidity);
    OLED_ShowString(0,2,buf_NTC,16);
    sprintf(buf_NTC,"temp: %.2f",temperature);
    OLED_ShowString(0,4,buf_NTC,16);
}