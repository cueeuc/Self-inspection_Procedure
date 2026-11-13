#include "INIT.h"
#include "APP.h"



void main_start() _task_ 0 {
    sys_init();
    os_create_task(TASK_SPI_OLED);
    os_create_task(TASK_I2C_OLED);
    os_create_task(TASK_KEYS);
    os_create_task(TASK_LED);
    os_delete_task(0);
}



