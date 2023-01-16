#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SHOW_CONSOLE
#include <graphics.h>

int select_mode();
void menu(); //绘制目录
void pvp(); //人人对战
void pve(); //人机对战
void eve(); //机机对战
void rew(); //复盘

#endif // !_MAIN_H_