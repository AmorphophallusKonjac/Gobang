/*
Auther:AmorphophallusKonjac(������)

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
	/*printf("��������Ϸģʽ����0�����˶�ս����1���˻���ս; ��2��������ս\n");
	gamemode = getchar();
	while (!isdigit(gamemode) || (gamemode - '0') > 2) {
		printf("�Ƿ����룬������ѡ��\n");
		while (getchar() != '\n');
		gamemode = getchar();
	}
	if (gamemode == '0')
		pvp();
	else
		//pve();
	*/
}