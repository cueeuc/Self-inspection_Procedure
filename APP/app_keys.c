#include "APP.h"
#include "key_driver.h"

void task_button_down(u8 key_index) {

    if(key_index == 0 || key_index == 1) {
        g_cur_pos = (g_cur_pos + menu_len-1) % menu_len;
    } else if(key_index == 2 || key_index == 3) {
        g_cur_pos = (g_cur_pos + 1) % menu_len;
    }
    printf("g_cur_pos: %d\n",g_cur_pos);
    switch(g_pre_pos) {
    case 0 :
        os_delete_task(TASK_LED);
        LED_Close();
        break;
    case 1 :
        os_delete_task(TASK_NTC);
        break;
    case 2 :
        os_delete_task(TASK_MOTOR);
        Motor_Close();
        break;
    case 3 :
        os_delete_task(TASK_RTC);
        break;
    case 4 :
        os_delete_task(TASK_SEG);
        Seg_Close();
        break;
    case 5 :
        os_delete_task(TASK_DHT);
        break;
    case 6 :
        os_delete_task(TASK_BUZZER);
        BUZZER_Close();
        break;
    default:
        break;
    }

    switch(g_cur_pos) {
    case 0 :
        os_create_task(TASK_LED);
        break;
    case 1 :
        os_create_task(TASK_NTC);
        break;
    case 2 :
        os_create_task(TASK_MOTOR);
        break;
    case 3 :
        os_create_task(TASK_RTC);
        break;
    case 4 :
        os_create_task(TASK_SEG);
        break;
    case 5 :
        os_create_task(TASK_DHT);
        break;
    case 6 :
        os_create_task(TASK_BUZZER);
        break;       
    default:
        break;
    }

    os_send_signal(TASK_SPI_OLED);
    Is_Screen_OLED_Clear(1);

    g_pre_pos = g_cur_pos;
}

void task_button_up(u8 key_index) {
    key_index = key_index;
}


void task_3() _task_ TASK_KEYS{

    while(1) {
    Judgment_button();
    os_wait2(K_TMO,2);
    }
}
