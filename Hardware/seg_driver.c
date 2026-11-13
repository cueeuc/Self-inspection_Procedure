#include "seg_driver.h"

/*
    数据位含义：
    串行输入的16位数据，高八位为段选（A~G, DP）,低八位为位选（COM1~COM8，即DIG1~DIG8）
    段选决定显示什么内容，位选决定一位数码管被点亮

    写入原理：
    移位寄存器（NIX_SCK）：上升沿（0->1）会把NIX_DI上的数据读进去，并将原有的数据向后挤一位
    锁存寄存器（NIX_RCK）：
    低电平0，此时即使移位寄存器里有数据，也不会输出到外面，数码管保持原状
    高电平1，数码管瞬间点亮，显示对应的数字
*/


// 共阳数码管段选数组（低电平有效）
// 段码格式：bit7-DP, bit6-G, bit5-F, bit4-E, bit3-D, bit2-C, bit1-B, bit0-A
// 对应引脚：DP G F E D C B A

// 共阳极七段数码管段码，段位顺序：DP G F E D C B A
u8  seg_num[] = {
    //0~9:
//    0xC0,  // 0: A B C D E F 亮，G DP 灭
    0xF9,  // 1: B C 亮
    0xA4,  // 2: A B D E G 亮
    0xB0,  // 3: A B C D G 亮
    0x99,  // 4: B C F G 亮
    0x92,  // 5: A C D F G 亮
    0x82,  // 6: A C D E F G 亮
    0xF8,  // 7: A B C 亮
    0x80,  // 8: 全部点亮
    0x90  // 9: A B C D F G 亮

//    //10~16
//    0x83,  // b: C D E F G 亮（小写b）
//    0xC6,  // C: A D E F 亮
//    0xA1,  // d: B C D E G 亮（小写d）
//    0x86,  // E: A D E F G 亮
//    0x8E,  // F: A E F G 亮
//    0x8C,  // H: B C E F G 亮
//    0x89,  // h: B C E F G 亮（小写h）

//    //17~26
//    0xC7,  // L: D E F 亮
//    0xBF,  // n: C E G 亮（小写n）
//    0xC1,  // U: B C D E F 亮（大写U）
//    0x92,  // S: A C D F G 亮（复用数字5）
//    0x87,  // t: D E F G 亮（小写t）
//    0xC0,  // O: 复用数字 0
//    0x8C,  // P: A B E F G 亮（大写P）
//    0x91,  // q: B C D E G 亮（小写q，修复！）
//    0xAF,  // r: E G 亮（小写r）
//    0x86   // 预留
};



void seg_write(u8 Get_byte,u8 Get_seg) {

    // 问题：int8 i 可以工作，但 u8 i 会死循环
    // 原因：u8是无符号数，i从0减1变成255，永远>=0，导致无限循环,
    // 而int8是有符号数，范围为-128~127，i从0减1变成-1，可以跳出循环
    // 解决：保持 int8 类型，或改用 for(i=8; i>0; i--) 并调整索引
    int8 i=0;
    //串行读入高八位段选（A~G, DP）
    for(i=8; i>0; i--) {
        NIX_DI=GET_BIT_VAL(Get_byte, i-1);
        NIX_SCK=0;
        NOP2();
        NIX_SCK=1;
        NOP2();
    }
    //串行读入低八位位选（COM1~COM8，即DIG1~DIG8）
    for(i=8; i>0; i--) {
        NIX_DI=GET_BIT_VAL(Get_seg, i-1);
        NIX_SCK=0;
        NOP2();
        NIX_SCK=1;
        NOP2();
    }
    NIX_RCK=0;
    NOP2();
    NIX_RCK=1;
    NOP2();
}

void seg_display(u8 s_num,u8 s_bit) {
    //选段码表，显示数字或者字母
    u8 tube_num = seg_num[s_num];
    //选数码管
    u8 tube_bit = 1<<s_bit;
    seg_write(tube_num,tube_bit);
}
