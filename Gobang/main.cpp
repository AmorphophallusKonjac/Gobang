/*
Auther:AmorphophallusKonjac(汪铭煜)

*/

#include "main.h"

int gamemode;

int main() {
	menu();
	gamemode = select_mode();
	closegraph();
	system("color F0");
	if (gamemode == 1)
		pvp();
	else {}
		//pve();
	system("pause");
	return 0;
	/*printf("请输入游戏模式：（0）人人对战；（1）人机对战; （2）机机对战\n");
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
	*/
}