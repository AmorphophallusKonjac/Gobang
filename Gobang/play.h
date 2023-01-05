#ifndef _PLAY_H_
#define _PLAY_H_

#include "common.h"

#define LASTBLACK 3
#define LASTWHITE 4

extern char gamemode;

void innerLayoutToDisplayArray(void);
void displayBoard(void);
void initRecordBoard(void);
void display(void);
int win(int x, int y);
void getinput(void);
void setinput(void);
void printpos(void);
void pass(void);
int cntconnect(int x, int y, int dx, int dy);
void judge(int result);

#endif // !_PLAY_H_
