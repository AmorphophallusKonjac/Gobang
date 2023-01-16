#ifndef _COMMON_H_
#define _COMMON_H_

/*�����趨*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define SHOW_CONSOLE
#include <graphics.h>

//���������궨��
#define SIZE 15		//���̴�С
#define CHARSIZE 2	//�����ַ�ռ�����ֽ�
#define ENPTY 0
#define BLACK 1
#define WHITE 2

//ȫ�ֱ���
struct node {
	int x, y;
};
extern int hcnt;
extern int cnt;
extern int g_x;
extern int g_y; //����λ��
extern int player; //������
extern int arrayForInnerBoardLayout[SIZE][SIZE];
extern int v[2][SIZE + 1][14348907]; //Ԥ�����еļ�ֵ
extern int bitboard[4][31];
extern int bitlen[4][31];
extern int airole;

//��������
int inrange(int x, int y);
int win(int x, int y);
int isfull();
int leftx(int, int);
int lefty(int, int);
int rightx(int, int);
int righty(int, int);

#endif // !_COMMON_H_
