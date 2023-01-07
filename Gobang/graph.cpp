#include"graph.h"


//打印图形界面窗口
void menu() {
	initgraph(640, 480);
	setbkcolor(EGERGB(0x17, 0x8C, 0xA4));
	setfillcolor(EGERGB(0xF9, 0xF7, 0xF0)); 
	bar(220, POS, 220 + WIDTH, POS + HEIGHT); //人人对战
	bar(220, POS + GAP, 220 + WIDTH, POS + GAP + HEIGHT); //人机对战
	bar(220, POS + 2 * GAP, 220 + WIDTH, POS + 2 * GAP + HEIGHT); //机机对战
	
	setcolor(EGERGB(0x07, 0x2A, 0x40));
	setfont(20, 0, "黑体");
	setbkmode(TRANSPARENT);
	outtextxy(280, POS + 15, "人人对战");
	outtextxy(280, POS + GAP + 15, "人机对战");
	outtextxy(280, POS + 2 * GAP + 15, "机机对战");
	setfont(40, 0, "黑体");
	outtextxy(222, POS - 110, "五子棋游戏");
	setfont(15, 0, "黑体");
	outtextxy(0, 0, "Author: AmorphophallusKonjac（汪铭煜）");
}

//判断鼠标位置决定模式
int mserange(int x, int y) {
	if (220 <= x && x <= 220 + WIDTH)
		if (POS <= y && y <= POS + HEIGHT)
			return 1;
		else if (POS + GAP <= y && y <= POS + GAP + HEIGHT)
			return 2;
		else if (POS + 2 * GAP <= y && y <= POS + 2 * GAP + HEIGHT)
			return 3;
	return 0;
}

//从鼠标读取信息选取模式
int select_mode() {
	mouse_msg msg = { 0 };
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			msg = getmouse();
		}
		if (msg.is_down() && mserange(msg.x, msg.y)) {
			return mserange(msg.x, msg.y);
		}
	}
}