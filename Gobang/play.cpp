#include"play.h"

int arrayForInnerBoardLayout[SIZE][SIZE];
extern struct node h[300];

//初始化一个空棋盘格局 
void initRecordBoard() {
    memset(arrayForInnerBoardLayout, 0, sizeof(arrayForInnerBoardLayout));
}

//画出UI
void drawui() {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "黑体");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (gamemode == 1)
        outtextxy(0, 0, "Author: AmorphophallusKonjac（汪铭煜）五子棋人人对战");
    else if (gamemode == 2)
        outtextxy(0, 0, "Author: AmorphophallusKonjac（汪铭煜）五子棋人机对战");
    else if (gamemode == 3)
        outtextxy(0, 0, "Author: AmorphophallusKonjac（汪铭煜）五子棋机机对战");
    else
        outtextxy(0, 0, "Author: AmorphophallusKonjac（汪铭煜）五子棋对局复盘");
}

//画出棋子
void drawchess(int x, int y, int k) {
    setfont(14, 0, "黑体");
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

//画出空棋盘
void drawboard() {
    cleardevice();
    setcolor(EGERGB(0x0, 0x0, 0x0));
    for (int i = 0; i < SIZE; ++i) {
        line(BASEY, BASEX + i * GAP, BASEY + (SIZE - 1) * GAP, BASEX + i * GAP);
        line(BASEY + i * GAP, BASEX, BASEY + i * GAP, BASEX + (SIZE - 1) * GAP);
    }
    setfont(14, 0, "黑体");
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(EGERGB(0x0, 0x0, 0x0));
    for (int i = 0; i < SIZE; ++i) {
        xyprintf(BASEY - GAP + 10, BASEX + i * GAP, "%d", i);
        xyprintf(BASEY + i * GAP, BASEX - GAP + 10, "%d", i);
    }
}

//打印棋盘
void display() {
    drawboard();
    drawui();
    for (int i = 0; i < cnt; ++i)
        drawchess(h[i].x, h[i].y, i + 1);
}

//计算对应方向上的连字数目
int cntconnect(int x, int y, int dx, int dy) {
    int cplayer = arrayForInnerBoardLayout[x][y];
    int num;
    if (!arrayForInnerBoardLayout[x][y]) return 0;
    num = 1;
    for (int i = x + dx, j = y + dy; inrange(i, j) && arrayForInnerBoardLayout[i][j] == cplayer; i += dx, j += dy, ++num);
    for (int i = x - dx, j = y - dy; inrange(i, j) && arrayForInnerBoardLayout[i][j] == cplayer; i -= dx, j -= dy, ++num);
    return num;
}

//获取输入坐标
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

//读入并处理坐标
void setinput() {
    getinput();
    arrayForInnerBoardLayout[g_x][g_y] = player;
    h[cnt].x = g_x; h[cnt].y = g_y; ++cnt;
}

//输出落子信息
void printpos() {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "黑体");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (player == BLACK) {
        xyprintf(0, 520, "黑子落在(%d,%d)", g_x, g_y);
    }
    else {
        xyprintf(0, 520, "白子落在(%d,%d)", g_x, g_y);
    }
}

//结束落子
void pass() {
    player ^= 3;
}

//判断输赢
int win(int x, int y) {
    if (cntconnect(x, y, 0, 1) >= 5 || cntconnect(x, y, 1, 0) >= 5 || cntconnect(x, y, 1, 1) >= 5 || cntconnect(x, y, 1, -1) >= 5) {
        if (player == BLACK)
            return WHITE;
        else
            return BLACK;
    }
    return 0;
}

//输出结果
void judge(int result) {
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    setfont(15, 0, "黑体");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    if (result == WHITE)
        xyprintf(0, 540, "白棋赢。是否保存对局棋谱（y/n）");
    else if (result == BLACK)
        xyprintf(0, 540, "黑棋赢。是否保存对局棋谱（y/n）");
    else
        xyprintf(0, 540, "平局。是否保存对局棋谱（y/n）");
}

//询问是否复盘与存储路径
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

//将棋谱导出到指定文件
void saverew() {
    char str[100], st[] = ".chman";
    FILE* fp;
    inputbox_getline("请命名棋谱文件", "请输入棋谱文件名", str, 100);
    strcat(str, st);
    fp = fopen(str, "w");
    for (int i = 0; i < cnt; ++i) {
        fprintf(fp, "%d, %d\n", h[i].x, h[i].y);
    }
    fclose(fp);
}

//从指定文件载入棋谱
void loadrew() {
    char str[100], st[] = ".chman";
    FILE* fp;
    inputbox_getline("请输入载入棋谱文件名（不含后缀）", "请输入棋谱文件名", str, 100);
    strcat(str, st);
    fp = fopen(str, "r");
    while (fscanf(fp, "%d, %d\n", &h[cnt].x, &h[cnt].y)) ++cnt;
}
