#ifndef _PLAY_H_
#define _PLAY_H_

#include "common.h"

#define LASTBLACK 3
#define LASTWHITE 4
#define RATIO 13
#define BASEY 96
#define BASEX 50
#define GAP 32
#define key_left 293
#define key_right 295

extern int gamemode;

int getcmd();
int setcmd();
void loadrew(void);
void saverew(void);
void askrew(void);
void drawui(void);
void drawchess(int x, int y, int k);
void drawboard();
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
