#include"play.h"

int arrayForInnerBoardLayout[SIZE][SIZE];
extern struct node h[300];

//��ʼ��һ�������̸�� 
void initRecordBoard() {
    memset(arrayForInnerBoardLayout, 0, sizeof(arrayForInnerBoardLayout));
}

//����UI
void drawui() {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "����");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (gamemode == 1)
        outtextxy(0, 0, "Author: AmorphophallusKonjac�������ϣ����������˶�ս");
    else if (gamemode == 2)
        outtextxy(0, 0, "Author: AmorphophallusKonjac�������ϣ��������˻���ս");
    else if (gamemode == 3)
        outtextxy(0, 0, "Author: AmorphophallusKonjac�������ϣ������������ս");
    else
        outtextxy(0, 0, "Author: AmorphophallusKonjac�������ϣ�������Ծָ���");
}

//��������
void drawchess(int x, int y, int k) {
    setfont(14, 0, "����");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    if (k % 2) {
        setcolor(EGERGB(0x0, 0x0, 0x0));
        setfillcolor(EGERGB(0x0, 0x0, 0x0));
        fillellipse(BASEY + y * GAP, BASEX + x * GAP, RATIO, RATIO);
        setcolor(EGERGB(0xff, 0xff, 0xff));
    }
    else {
        setcolor(EGERGB(0xff, 0xff, 0xff));
        setfillcolor(EGERGB(0xff, 0xff, 0xff));
        fillellipse(BASEY + y * GAP, BASEX + x * GAP, RATIO, RATIO);
        setcolor(EGERGB(0x0, 0x0, 0x0));
    }
    xyprintf(BASEY + y * GAP, BASEX + x * GAP, "%d", k);
}

//����������
void drawboard() {
    cleardevice();
    setcolor(EGERGB(0x0, 0x0, 0x0));
    for (int i = 0; i < SIZE; ++i) {
        line(BASEY, BASEX + i * GAP, BASEY + (SIZE - 1) * GAP, BASEX + i * GAP);
        line(BASEY + i * GAP, BASEX, BASEY + i * GAP, BASEX + (SIZE - 1) * GAP);
    }
    setfont(14, 0, "����");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(EGERGB(0x0, 0x0, 0x0));
    for (int i = 0; i < SIZE; ++i) {
        xyprintf(BASEY - GAP + 10, BASEX + i * GAP, "%d", i);
        xyprintf(BASEY + i * GAP, BASEX - GAP + 10, "%d", i);
    }
}

//��ӡ����
void display() {
    drawboard();
    drawui();
    for (int i = 0; i < cnt; ++i)
        drawchess(h[i].x, h[i].y, i + 1);
}

//�����Ӧ�����ϵ�������Ŀ
int cntconnect(int x, int y, int dx, int dy) {
    int cplayer = arrayForInnerBoardLayout[x][y];
    int num;
    if (!arrayForInnerBoardLayout[x][y]) return 0;
    num = 1;
    for (int i = x + dx, j = y + dy; inrange(i, j) && arrayForInnerBoardLayout[i][j] == cplayer; i += dx, j += dy, ++num);
    for (int i = x - dx, j = y - dy; inrange(i, j) && arrayForInnerBoardLayout[i][j] == cplayer; i -= dx, j -= dy, ++num);
    return num;
}

//��ȡ��������
void getinput() {
    mouse_msg msg = { 0 };
    for (; is_run(); delay_fps(60)) {
        while (mousemsg()) {
            msg = getmouse();
        }
        if (msg.is_down() && msg.y >= BASEX - GAP / 2 && msg.x >= BASEY - GAP / 2) {
            g_x = (msg.y - (BASEX - GAP / 2)) / GAP;
            g_y = (msg.x - (BASEY - GAP / 2)) / GAP;
            if (inrange(g_x, g_y) && !arrayForInnerBoardLayout[g_x][g_y])
                return;
        }
    }
}

//���벢��������
void setinput() {
    getinput();
    arrayForInnerBoardLayout[g_x][g_y] = player;
    h[cnt].x = g_x; h[cnt].y = g_y; ++cnt;
}

//���������Ϣ
void printpos() {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "����");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (player == BLACK) {
        xyprintf(0, 520, "��������(%d,%d)", g_x, g_y);
    }
    else {
        xyprintf(0, 520, "��������(%d,%d)", g_x, g_y);
    }
}

//��������
void pass() {
    player ^= 3;
}

//�ж���Ӯ
int win(int x, int y) {
    if (cntconnect(x, y, 0, 1) >= 5 || cntconnect(x, y, 1, 0) >= 5 || cntconnect(x, y, 1, 1) >= 5 || cntconnect(x, y, 1, -1) >= 5) {
        if (player == BLACK)
            return WHITE;
        else
            return BLACK;
    }
    return 0;
}

//������
void judge(int result) {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "����");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (result == WHITE)
        xyprintf(0, 540, "����Ӯ���Ƿ񱣴�Ծ����ף�y/n��");
    else if (result == BLACK)
        xyprintf(0, 540, "����Ӯ���Ƿ񱣴�Ծ����ף�y/n��");
    else
        xyprintf(0, 540, "ƽ�֡��Ƿ񱣴�Ծ����ף�y/n��");
}

//ѯ���Ƿ�����洢·��
void askrew() {
    int k = 0;
    for (; k != 'n' && k != 'N'; ) {
        k = getch();
        if (k == 'y' || k == 'Y') {
            saverew();
            break;
        }
    }
}

//�����׵�����ָ���ļ�
void saverew() {
    char str[100], st[] = ".chman";
    FILE* fp;
    inputbox_getline("�����������ļ�", "�����������ļ���", str, 100);
    strcat(str, st);
    fp = fopen(str, "w");
    for (int i = 0; i < cnt; ++i) {
        fprintf(fp, "%d, %d\n", h[i].x, h[i].y);
    }
    fclose(fp);
}

//��ָ���ļ���������
void loadrew() {
    char str[100], st[] = ".chman";
    FILE* fp;
    inputbox_getline("���������������ļ�����������׺��", "�����������ļ���", str, 100);
    strcat(str, st);
    fp = fopen(str, "r");
    while (fscanf(fp, "%d, %d\n", &h[cnt].x, &h[cnt].y)) ++cnt;
}
