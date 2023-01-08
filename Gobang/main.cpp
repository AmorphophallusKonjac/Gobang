/*
Auther:AmorphophallusKonjac(ֽפֳתלֿ)

*/

#include "main.h"

int gamemode;

int main() {
	menu();
	gamemode = select_mode();
	if (gamemode == 1)
		pvp();
	else if (gamemode == 2)
		pve();
	else if (gamemode == 3)
		eve();
	else
		rew();
	getch();
	closegraph();
	return 0;
}