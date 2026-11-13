#ifndef	_BUTTONS_H_
#define	_BUTTONS_H_

#include "Config.h"

#define COL1	P03
#define COL2	P06
#define COL3	P07
#define COL4	P17

#define ROW1	P34
#define ROW2	P35
#define ROW3	P40
#define ROW4	P41

#define DOWN		0
#define UP			1
#define ROW_KEY		4
#define	COL_KEY		4

#define statues(index)  button_status[index]
#define statues_assign(index,col)     button_status[index]= Col_sel(col)

void Keyboard_scan();

void Level_selection(u8 row);

int Col_sel(u8 col);

u8 is_ghost_key(u8 row, u8 col);

extern u8 key_index;

#endif