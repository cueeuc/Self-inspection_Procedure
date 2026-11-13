#include "APP.h"
#include "spi_oled.h"
#include "i2c_oled.h"


int g_cur_pos = 0;
int g_pre_pos = 0;
u8 is_clear_screen = 0;

char* spi_dis[] = {
    {"LED跑马灯"},
    {"热敏电阻"},
    {"振动马达"},
    {"RTC时钟"},
    {"Digital-tube"},
    {"温湿度传感器"},
    {"键盘蜂鸣器"},
    //{"舵机","SERVO"},
};

char* i2c_dis[]={
    {"LED"},
    {"NTC-TMP"},
    {"MOTOR"},
    {"RTC"},
    {"SEGMENT"},
    {"DHT11"},
    {"BUZZER"},
};

int menu_len = sizeof(spi_dis)/sizeof(spi_dis[0]);

void task_1() _task_ TASK_SPI_OLED{
    int i = 0;
    char menu_str[32]="";
    
    SPI_OLED_Init();
    SPI_OLED_ColorTurn(0);// 设置颜色反转模式，0正常显示，1反转显示
    SPI_OLED_DisplayTurn(0); // 设置屏幕旋转方向，0正常显示，1旋转180°
    SPI_OLED_Clear();
    while(1){
        SPI_OLED_Clear();
        //i<4,ISP显示屏高为64个字符，每个字符高为16个像素，最多只能显示4行数据
        for(i=0;i<4;i++){
            int index = (i + g_cur_pos) % menu_len; //循环显示菜单项
            sprintf(menu_str,"%c %d.%s",(i ? ' ' :'>'),(int)index,spi_dis[index]);
            SPI_OLED_Display_GB2312_string(0,i*2,menu_str);
        }
         os_wait1(K_SIG);
    }   
}

void Is_Screen_OLED_Clear(u8 screen_clear){
    if(screen_clear != 0){
        is_clear_screen = 1;
    }
    os_send_signal(TASK_I2C_OLED);
}


void task_2() _task_ TASK_I2C_OLED{
    OLED_Init();//初始化OLED
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    while(1){
        if(is_clear_screen){
            is_clear_screen = 0;
            OLED_Clear();
            printf("Clear the I2C Display screen \n");
        }
        OLED_ShowString(0,0,i2c_dis[g_cur_pos],16);
        switch(g_cur_pos){
            case 0 : LED_Display();break;
            case 1 : NTC_Display();break;
            case 2 : Motor_Display();break;
            case 3 : RTC_Display();break;
            case 4 : Seg_Display();break;
            case 5 : DHT_Display();break;
            case 6 : BUZZER_Display();break;
            default:break;
        }
        os_wait1(K_SIG);
    }
}