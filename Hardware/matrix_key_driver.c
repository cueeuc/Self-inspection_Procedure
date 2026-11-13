#include "button_driver.h"
#include "buzzer_driver.h"
//记录上次按键状态数组
u8	button_status[]= {
    1,1,1,1, //0, 1, 2, 3
    1,1,1,1, //4, 5, 6, 7
    1,1,1,1, //8, 9, 10,11
    1,1,1,1  //12,13,14,15
};

//控制行输出信号的电平
void Level_selection(u8 row) {
    ROW1 = (row == 0) ? 0 : 1;
    ROW2 = (row == 1) ? 0 : 1;
    ROW3 = (row == 2) ? 0 : 1;
    ROW4 = (row == 3) ? 0 : 1;
}

//选择列输入信号
int Col_sel(u8 col) {
    if(col == 0)	return COL1;
    if(col == 1)	return COL2;
    if(col == 2)	return COL3;
    if(col == 3)	return COL4;
    return 0;
}

u8 key_index = 0;
//矩阵按鍵扫描函数
void Keyboard_scan() {
    u8 row=0, col=0,index = 0;
    for(row=0; row<ROW_KEY; row++) {
        Level_selection(row);
        NOP2();
        for(col=0; col<COL_KEY; col++) {
            index = (row*4)+col;
            if(statues(index) != Col_sel(col)) {
                statues_assign(index,col);
                if(Col_sel(col) == DOWN) {
                    key_index = index + 1;
                    Buzzer_beep(index + 1);
                    printf("KEY[%d] DOWN\n",(int)(index+1));
                } else {
                    Buzzer_stop();
                    printf("KEY[%d] UP\n",(int)(index+1));
                }
            }
        }
    }
}