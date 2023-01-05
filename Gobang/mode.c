#include"mode.h"

int player = BLACK;
int g_x = 7, g_y = 7;

void pvp() {
	int result;
	system("cls");
	display();
	while (!(result = win(g_x, g_y)) && !(isfull())) {
		printf("输入格式为A1或a1\n");
		setinput();
		system("cls");
		display();
		printpos();
		pass();
	}
	judge(result);
}