/*
Auther:AmorphophallusKonjac(汪铭煜)

*/

#include "main.h"

char gamemode;

int main() {
	//system("color F0");
	/*选择游戏模式*/
	printf("请输入游戏模式：（0）人人对战；（1）人机对战; （2）机机对战\n");
	gamemode = getchar();
	while (!isdigit(gamemode) || (gamemode - '0') > 2) {
		printf("非法输入，请重新选择\n");
		while (getchar() != '\n');
		gamemode = getchar();
	}
	if (gamemode == '0')
		pvp();
	else
		//pve();
	system("pause");
	return 0;
}