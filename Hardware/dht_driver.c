#include "dht_driver.h"


/********************************************************************
*                      表 10 单总线信号特性

* 符号      参数                           min    type    max    单位
* Tbe     主机起始信号拉低时间             18     20      30      ms
* Tgo     主机释放总线时间                 10     13      35      μS
* Trel    响应低电平时间                   78     83      88      μS
* Treh    响应高电平时间                   80     87      92      μS
* TLOW    信号 "0"、"1" 低电平时间         50     54      58      μS
* TH0     信号 "0" 高电平时间              23     24      27      μS
* TH1     信号 "1" 高电平时间              68     71      74      μS
* Ten     传感器释放总线时间               52     54      56      μS
*********************************************************************/

void delay(void) {
    NOP8();
}


char DHT_data_read(u8 *arr){
    int8 i,j;
    u16 count = 0;
    //主机发出起始拉低信号
    DH = 0;
    os_wait2(K_TMO, 4);
    DH = 1;

    NOP2();

    count = 0;

    Level_signal_change(1,6,42,"主机释放总线时间");

    Level_signal_change(0,75,89,"响应低电平时间");

    Level_signal_change(1,80,92,"响应高电平时间");

    //读取5个字节,每轮循环读取1Byte(1字节)
    for(i=0; i<5; i++) {
        //读取1字节,每轮循环读取1位(从高位到低位)
        for(j=7; j>=0; j--) {
            Level_signal_change(0,45,62,"信号 0、1 低电平时间");

            Level_signal_change(1,20,74,"信号0、1高电平时间");
            
            if(count>47) {
                arr[i] |= (1 << j);
            }
        }
    }
    printf("count->%d\n",(int)count);
    printf("data:");
    for(i = 0; i < 5; i++) {
        printf("%d ", (int)arr[i]);
    }
    printf("\n");
    
    if(((arr[0] + arr[1] + arr[2] + arr[3]) & 0xFF) != arr[4]) {
        printf("err: 校验失败\n");
        return -1;
    }

    printf("校验通过!\n");

    return 0;
}

int8 DHT_data_detect(void) {
    char rst;
    u8 dat[5] = {0x00};
    rst = DHT_data_read(dat);
    if(rst == SUCCESS) {
        humidity = dat[0];
        temperature = dat[2] + (dat[3] & 0x7F) * 0.1f;
        if(dat[3] & 0x80) {
            temperature *= -1;
        }
    } else {
        printf("无效校验位为:%d\n",(int)dat[4]);
    }
    return rst;
}