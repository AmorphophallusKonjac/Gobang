#ifndef _COMMON_H_
#define _COMMON_H_

/*基本设定*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
//#define SHOW_CONSOLE
#include <graphics.h>

//基本参数宏定义
#define SIZE 15		//棋盘大小
#define CHARSIZE 2	//中文字符占两个字节
#define ENPTY 0
#define BLACK 1
#define WHITE 2

//全局变量
struct node {
	int x, y;
};
extern int hcnt;
extern int cnt;
extern int g_x;
extern int g_y; //下棋位置
extern int player; //下棋人
extern int arrayForInnerBoardLayout[SIZE][SIZE];

//函数申明
int inrange(int x, int y);
int win(int x, int y);
int isfull();

#endif // !_COMMON_H_
