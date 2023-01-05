#ifndef _COMMON_H_
#define _COMMON_H_

/*�����趨*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

//���������궨��
#define SIZE 15		//���̴�С
#define CHARSIZE 2	//�����ַ�ռ�����ֽ�
#define ENPTY 0
#define BLACK 1
#define WHITE 2

//ȫ�ֱ���
extern int g_x;
extern int g_y; //����λ��
extern int player; //������
extern char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1]; //��ʼ��������
extern char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1]; //������洢������ʾ������ 
extern char play1Pic[];//������;
extern char play1CurrentPic[];
extern char play2Pic[];//������;
extern char play2CurrentPic[];
extern int arrayForInnerBoardLayout[SIZE][SIZE];

//��������
int inrange(int x, int y);
int win(int x, int y);
int isfull();

#endif // !_COMMON_H_
