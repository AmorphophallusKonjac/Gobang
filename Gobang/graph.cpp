#include"graph.h"

void menu() {
	initgraph(640, 480);
	setbkcolor(EGERGB(0x17, 0x8C, 0xA4));
	setfillcolor(EGERGB(0xF9, 0xF7, 0xF0)); 
	bar(220, POS, 220 + WIDTH, POS + HEIGHT);
	bar(220, POS + GAP, 220 + WIDTH, POS + GAP + HEIGHT);
	bar(220, POS + 2 * GAP, 220 + WIDTH, POS + 2 * GAP + HEIGHT);
	
	setcolor(EGERGB(0x07, 0x2A, 0x40));
	setfont(20, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(280, POS + 15, "���˶�ս");
	outtextxy(280, POS + GAP + 15, "�˻���ս");
	outtextxy(280, POS + 2 * GAP + 15, "������ս");
	setfont(40, 0, "����");
	outtextxy(222, POS - 110, "��������Ϸ");
	setfont(15, 0, "����");
	outtextxy(0, 0, "Author: AmorphophallusKonjac�������ϣ�");
	getch();
	closegraph();
}