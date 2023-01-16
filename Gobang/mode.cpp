#include"mode.h"

int player = BLACK;
int g_x = 7, g_y = 7;
int cnt = 0;
int hcnt = 0;
int airole;

void pvp() {
	int result;
	initRecordBoard();
	display();
	while (!(result = win(g_x, g_y)) && !(isfull())) {
		if (getinput()) {
			delinput(); delinput(); g_x = 7; g_y = 7; display(); continue;
		}
		setinput();
		display();
		printpos();
		//std::cout << calc_now() << "\n";
		pass();
	}
	judge(result);
	askrew();
}

void pve() {
	int result;
	set_score();
	initRecordBoard();
	display();
	initbitboard();
	airole = askblack() ^ 3;
	std::cout << airole << "\n";
	if (airole == BLACK) {
		g_x = 7; g_y = 7;
		setinput();
		display();
		printpos();
		pass();
	}
	while (!(result = win(g_x, g_y)) && !(isfull())) {
		if (player == airole) {
			ai_op();
		}
		else {
			if (getinput()) {
				delinput(); delinput(); g_x = 7; g_y = 7; display(); continue;
			}
		}
		setinput();
		display();
		printpos();
		pass();
	}
	judge(result);
	askrew();
}

void eve() {
	int result;
	set_score();
	initRecordBoard();
	display();
	initbitboard();
	g_x = 7; g_y = 7;
	setinput();
	display();
	printpos();
	pass();
	while (!(result = win(g_x, g_y)) && !(isfull())) {
		airole = player;
		ai_op();
		setinput();
		display();
		printpos();
		pass();
	}
	judge(result);
	askrew();
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