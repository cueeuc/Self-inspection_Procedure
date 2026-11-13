#include "APP.h"

static u8 led_count = 0;

void LED_Init(void) {
    LED_SW = 0;
    LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=1;
}

void LED_Close(void){
    LED_SW = 1;
}

void LED_Display(void){
    char buff_LED[32]="";
    sprintf(buff_LED,"num: %d",(int)led_count);
    OLED_ShowString(0,2,buff_LED,16);

}


void task_4() _task_ TASK_LED{
    int i = 1;
    LED_Init();
    while(1) {
        for(i=1; i<=8; i++) {
            switch(i) {
            case 1:LED1=0;break;
            case 2:LED2=0;break;
            case 3:LED3=0;break;
            case 4:LED4=0;break;
            case 5:LED5=0;break;
            case 6:LED6=0;break;
            case 7:LED7=0;break;
            case 8:LED8=0;break;
            default: break;
            }
            led_count = i;
            Is_Screen_OLED_Clear(0);
            os_wait2(K_TMO,40);
        }
        LED1=LED2=LED3=LED4=LED5=LED6=LED7=LED8=1;
        led_count = 0;
        Is_Screen_OLED_Clear(0);
        os_wait2(K_TMO,40);
    }
}

