#include"graph.h"


//��ӡͼ�ν��洰��
void menu() {
	initgraph(640, 480);
	setbkcolor(EGERGB(0x17, 0x8C, 0xA4));
	setfillcolor(EGERGB(0xF9, 0xF7, 0xF0)); 
	bar(220, POS, 220 + WIDTH, POS + HEIGHT); //���˶�ս
	bar(220, POS + GAP, 220 + WIDTH, POS + GAP + HEIGHT); //�˻���ս
	bar(220, POS + 2 * GAP, 220 + WIDTH, POS + 2 * GAP + HEIGHT); //������ս
	
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
}

//�ж����λ�þ���ģʽ
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

//������ȡ��Ϣѡȡģʽ
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