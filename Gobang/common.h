#ifndef _COMMON_H_
#define _COMMON_H_

/*基本设定*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

//基本参数宏定义
#define SIZE 15		//棋盘大小
#define CHARSIZE 2	//中文字符占两个字节
#define ENPTY 0
#define BLACK 1
#define WHITE 2

//全局变量
extern int g_x;
extern int g_y; //下棋位置
extern int player; //下棋人
extern char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1]; //初始化空棋盘
extern char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1]; //此数组存储用于显示的棋盘 
extern char play1Pic[];//黑棋子;
extern char play1CurrentPic[];
extern char play2Pic[];//白棋子;
extern char play2CurrentPic[];
extern int arrayForInnerBoardLayout[SIZE][SIZE];

//函数申明
int inrange(int x, int y);
int win(int x, int y);
int isfull();

#endif // !_COMMON_H_
