#include "rtc_driver.h"



//RTC时钟时间写入函数
void rtc_write(rtc_t rtc_write) {
    u8  Slave_data[NUMBER]= {0};
    u8	C = 0;
    Slave_data[0]=((rtc_write.second  / 10)<<4) |(rtc_write.second % 10);
    Slave_data[1]=((rtc_write.minute / 10)<<4) | (rtc_write.minute % 10);
    Slave_data[2]=((rtc_write.hour / 10)<<4) | (rtc_write.hour % 10);
    Slave_data[3]=((rtc_write.day / 10)<<4) | (rtc_write.day % 10);
    Slave_data[4]=rtc_write.week;
    C =(rtc_write.year>=2100) ? 1 : 0;
    Slave_data[5]=(C<<7) | ((rtc_write.month / 10)<<4) | (rtc_write.month % 10);
    //year:((year % 100) / 10<<4) | (year%10);
    Slave_data[6]=((rtc_write.year % 100) / 10<<4) | (rtc_write.year % 10);
    I2C_WriteNbyte(RTC_dev_addr, 0x02, Slave_data, NUMBER);
}

//RTC时钟时间读取函数
void rtc_read(rtc_t *rtc_read) {
    u8  Slave_data[NUMBER]= {0};
    u8 C =0;
    I2C_ReadNbyte(RTC_dev_addr, 0x02, Slave_data, NUMBER);

    rtc_read->second = ((Slave_data[0] >> 4) & 0x07) * 10 + (Slave_data[0] & 0x0F);

    rtc_read->minute = ((Slave_data[1] >> 4) & 0x07) * 10 + (Slave_data[1] & 0x0F);

    rtc_read->hour = ((Slave_data[2] >> 4) & 0x03) * 10 + (Slave_data[2] & 0x0F);

    rtc_read->day = ((Slave_data[3] >> 4) & 0x03) * 10 + (Slave_data[3] & 0x0F);

    rtc_read->week = Slave_data[4] & 0x07;
    
    rtc_read->month = ((Slave_data[5] >> 4) & 0x01) * 10 + (Slave_data[5] & 0x0F);

    C = Slave_data[5] >> 7;

    rtc_read->year = ((Slave_data[6] >> 4) & 0x0F) * 10 + (Slave_data[6] & 0x0F);

    if (C == 0) {
        rtc_read->year += 2000;
    } else {
        rtc_read->year += 2100;
    }
}

//RTC闹钟配置函数
void Alarm_setting(rtc_a set) {
    u8  alarm_regs[REG];
    alarm_regs[0] = 0x80,alarm_regs[1] = 0x80;
    alarm_regs[2] = 0x80,alarm_regs[3] = 0x80;
    if(set.minute>=0) {
        alarm_regs[0] = 0x00 | ((set.minute / 10)<<4) | (set.minute % 10);
    }
    if(set.hour>=0) {
        alarm_regs[1] = 0x00 | ((set.hour / 10)<<4) | (set.hour % 10);
    }
    if(set.day>=0) {
        alarm_regs[2] = 0x00 | ((set.day / 10)<<4) | (set.day % 10);
    }
    if(set.week>=0) {
        alarm_regs[3] = 0x00 | set.week;
    }
    I2C_WriteNbyte(RTC_dev_addr, 0x09, alarm_regs, REG);
}


/*
控制/状态寄存器2（首地址 0x01）
   bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0
┌───┬───┬───┬───┬───┬───┬───┬───┬
│  -   │  -   │ -    │  -   │  AF  │  -   │ AIE  │  -   │
└───┴───┴───┴───┴───┴───┴───┴───┴
   0x80    0x40    0x20    0x10    0x08    0x04    0x02    0x01
AF:闹钟标志（硬件置1，软件清0）
AIE:闹钟中断使能（软件控制）
-：保留
*/

//RTC闹钟启动函数
void Alarm_detection(u8 Flag) {
    u8 cf = 0;
    I2C_ReadNbyte(RTC_dev_addr, 0x01, &cf, 1);
    cf &= ~(1 << 3);
    if(Flag) {
        cf |= (1 << 1);
    } else {
        cf &=~(1 << 1);
    }
    I2C_WriteNbyte(RTC_dev_addr, 0x01, &cf, 1);
}

//RTC闹钟标志清除函数
void Reminder_elimination() {
    u8 cf = 0;
    I2C_ReadNbyte(RTC_dev_addr, 0x01, &cf, 1);
    cf &= ~(1 << 3);
    I2C_WriteNbyte(RTC_dev_addr, 0x01, &cf, 1);
}

//RTC定时器配置函数
void timer_setting(timer_type types,u8 count) {
    u8 te;
    te = (1 << 7) | (types);
    I2C_WriteNbyte(RTC_dev_addr,0x0E,&te, 1);//定时器控制寄存器,控制定时器的启动/停止和时钟源选择
    te = count;
    I2C_WriteNbyte(RTC_dev_addr,0x0F,&te, 1);//定时器计数器寄存器,存放8位倒计时初值 (0~255)
}

//RTC定时器使能函数
void timer_enable(u8 flag) {
    u8 ts = 0;
    //控制/状态寄存器2，Bit 0 (TIE)：定时器中断使能，Bit 2 (TF)：定时器中断标志位
    I2C_ReadNbyte(RTC_dev_addr,0x01,&ts, 1);

    //先清除标志，再使能中断
    ts &= ~( 1 << 2 );

    if(flag) {
        ts |= (1 >> 0);
    } else {
        ts &= ~ (1 << 2);
    }
    I2C_WriteNbyte(RTC_dev_addr,0x01,&ts, 1);
}

//RTC定时器标志清除函数
void timer_clear() {
    u8 cs = 0;
    I2C_ReadNbyte(RTC_dev_addr,0x01,&cs, 1);
    cs &= ~ (1 << 2);
    I2C_WriteNbyte(RTC_dev_addr,0x01,&cs, 1);
}

//RTC时间对齐函数
void time_alignment() {
    rtc_t ta;
    u8 i;
    // 将接收缓冲区中的所有数据依次发送出去（回显功能）
    for(i=0; i<COM1.RX_Cnt; i++)
    {
        TX1_write2buff(RX1_Buffer[i]);// 将第i个字节写入发送缓冲区
    }

    //数据发送格式:命令头(2byte)+世纪+年+月+日+星期+时+分+秒+次秒+毫秒
    //              0      1      2    3  4  5  6   7
    ta.year = RX1_Buffer[2] *100 +  RX1_Buffer[3];
    ta.month = RX1_Buffer[4];
    ta.day = RX1_Buffer[5];
    ta.week = RX1_Buffer[6];
    ta.hour = RX1_Buffer[7];
    ta.minute = RX1_Buffer[8];
    ta.second = RX1_Buffer[9];
    rtc_write(ta);
}





