#include "APP.h"
#include "rtc_driver.h"

rtc_t w_r;

void task_7() _task_ TASK_RTC{
    // 时间读取和屏幕刷新不能同时进行， 容易卡死，所以延时一会再启动
    os_wait2(K_TMO, 100);
    w_r.second = 50,w_r.minute = 0,w_r.hour = 0;
    w_r.day = 10,w_r.week = 7,w_r.month = 10,w_r.year = 2026;
    rtc_write(w_r);
    while(1) {
        rtc_read(&w_r);
        Is_Screen_OLED_Clear(0);
        os_wait2(K_TMO,200);
    }
}

char RTC_buf[32] = "";
void RTC_Display() {
    OLED_ShowChinese(32,0, 0, 16);  // 中
    OLED_ShowChinese(48,0, 1, 16);  // 国
    OLED_ShowChinese(64,0, 2, 16);  // 标
    OLED_ShowChinese(80,0, 3, 16);  // 准
    OLED_ShowChinese(96,0, 4, 16);  // 时
    OLED_ShowChinese(112,0, 5, 16); // 间
    // sprintf函数：将格式化的数据写入字符串缓冲区，功能类似于printf但输出到数组而非控制台
    // 参数1：目标字符数组（缓冲区），参数2：格式化字符串，后续为可变参数
    sprintf(RTC_buf, "%04d", (int)w_r.year);
    OLED_ShowString(0, 2, RTC_buf, 16);
    OLED_ShowChinese(32, 2, 6, 16);

    sprintf(RTC_buf, "%02d", (int)w_r.month);
    OLED_ShowString(48, 2, RTC_buf, 16);
    OLED_ShowChinese(64, 2, 7, 16);

    sprintf(RTC_buf, "%02d", (int)w_r.day);
    OLED_ShowString(80, 2, RTC_buf, 16);
    OLED_ShowChinese(96, 2, 8, 16);

    OLED_ShowChinese(0, 4, 9, 16);
    week_convert();


    sprintf(RTC_buf, "%02d", (int)w_r.hour);
    OLED_ShowString(32, 4, RTC_buf, 16);
    OLED_ShowChinese(48, 4, 10, 16);

    sprintf(RTC_buf, "%02d", (int)w_r.minute);
    OLED_ShowString(64, 4, RTC_buf, 16);
    OLED_ShowChinese(80, 4, 11, 16);

    sprintf(RTC_buf, "%02d", (int)w_r.second);
    OLED_ShowString(96, 4, RTC_buf, 16);
    OLED_ShowChinese(112, 4, 12, 16);
    if(COM1.RX_TimeOut > 0)
    {
        if(--COM1.RX_TimeOut == 0)
        {
            if(COM1.RX_Cnt > 0)
            {
                time_alignment();
            }
            COM1.RX_Cnt = 0;
        }
    }
    os_wait2(K_TMO,1);
}

void week_convert(){
    switch(w_r.week){
        case 1:
        OLED_ShowChinese(16, 4, 13, 16);
        break;
        case 2:
        OLED_ShowChinese(16, 4, 14, 16);
        break;
        case 3:
        OLED_ShowChinese(16, 4, 15, 16);
        break;
        case 4:
        OLED_ShowChinese(16, 4, 16, 16);
        break;
        case 5:
        OLED_ShowChinese(16, 4, 17, 16);
        break;
        case 6:
        OLED_ShowChinese(16, 4, 18, 16);
        break;
        case 7:
        OLED_ShowChinese(16, 4, 19, 16);
        break;
        default:
        break;        
    }
    
}