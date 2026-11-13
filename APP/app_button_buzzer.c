#include "APP.h"
#include "button_driver.h"
#include "buzzer_driver.h"

void BUZZER_Close(){
    Buzzer_stop();
}

void task_10() _task_ TASK_BUZZER{
    Buzzer_init();
    while(1) {
        
        Keyboard_scan();
        
        Is_Screen_OLED_Clear(0);
        os_wait2(K_TMO,20);
    }
}

void BUZZER_Display() {
    char buf_BUZZER[32]="";
    sprintf(buf_BUZZER,"key_index: %02d",(int)key_index);
    OLED_ShowString(0,2,buf_BUZZER,16);    
}