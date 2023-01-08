#include"mode.h"

int player = BLACK;
int g_x = 7, g_y = 7;
int cnt = 0;
int hcnt = 0;

void pvp() {
	int result;
	initRecordBoard();
	display();
	while (!(result = win(g_x, g_y)) && !(isfull())) {
		setinput();
		display();
		printpos();
		pass();
	}
	judge(result);
	askrew();
}

void pve() {

}

void eve() {

}

void rew() {
	loadrew();
	int result;
	initRecordBoard();
	display();
	while (setcmd()) {
		display();
		pass();
		if ((result = win(g_x, g_y)) || isfull())
			judge(result);
	}
}