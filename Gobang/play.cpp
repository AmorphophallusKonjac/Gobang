#include"play.h"

int arrayForInnerBoardLayout[SIZE][SIZE];
extern struct node h[300];
int bitboard[4][31];
int bitlen[4][31];

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
        outtextxy(0, 0, "五子棋人人对战");
    else if (gamemode == 2)
        outtextxy(0, 0, "五子棋人机对战");
    else if (gamemode == 3)
        outtextxy(0, 0, "五子棋机机对战");
    else
        outtextxy(0, 0, "五子棋对局复盘 按左右方向键控制棋谱，esc键退出。");
    setfillcolor(EGERGB(0xF9, 0xF7, 0xF0));
    bar(515 - 20, 530 - 10, 515 + 20, 530 + 10);
    setfont(14, 0, "黑体");
    setcolor(EGERGB(0x07, 0x2A, 0x40));
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    xyprintf(515, 530, "悔棋");
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
int getinput() {
    mouse_msg msg = { 0 };
    for (; is_run(); delay_fps(60)) {
        while (mousemsg()) {
            msg = getmouse();
        }
        if (msg.is_down() && 495 <= msg.x && msg.x <= 535 && 520 <= msg.y && msg.y <= 540 && cnt >= 2) {
            return 1;
        }
        if (msg.is_down() && msg.y >= BASEX - GAP / 2 && msg.x >= BASEY - GAP / 2) {
            g_x = (msg.y - (BASEX - GAP / 2)) / GAP;
            g_y = (msg.x - (BASEY - GAP / 2)) / GAP;
            if (inrange(g_x, g_y) && !arrayForInnerBoardLayout[g_x][g_y])
                return 0;
        }
    }
}

//读入并处理坐标
void setinput() {
    arrayForInnerBoardLayout[g_x][g_y] = player;
    bitboard[0][g_x] += player * pow(3, g_y);
    bitboard[1][g_y] += player * pow(3, g_x);
    bitboard[2][leftx(g_x, g_y)] += player * pow(3, lefty(g_x, g_y));
    bitboard[3][rightx(g_x, g_y)] += player * pow(3, righty(g_x, g_y));
    h[cnt].x = g_x; h[cnt].y = g_y; ++cnt;
}

//悔棋时更新信息
void delinput() {
    --cnt; g_x = h[cnt].x; g_y = h[cnt].y;
    arrayForInnerBoardLayout[g_x][g_y] = 0;
    bitboard[0][g_x] -= player * pow(3, g_y);
    bitboard[1][g_y] -= player * pow(3, g_x);
    bitboard[2][leftx(g_x, g_y)] -= player * pow(3, lefty(g_x, g_y));
    bitboard[3][rightx(g_x, g_y)] -= player * pow(3, righty(g_x, g_y));
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
    if (gamemode != 4) {
        if (result == WHITE)
            xyprintf(0, 540, "白棋赢。是否保存对局棋谱（y/n）");
        else if (result == BLACK)
            xyprintf(0, 540, "黑棋赢。是否保存对局棋谱（y/n）");
        else
            xyprintf(0, 540, "平局。是否保存对局棋谱（y/n）");
    }
    else {
        if (result == WHITE)
            xyprintf(0, 540, "白棋赢。");
        else if (result == BLACK)
            xyprintf(0, 540, "黑棋赢。");
        else
            xyprintf(0, 540, "平局。");
    }

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
    while (fscanf(fp, "%d, %d\n", &h[cnt].x, &h[cnt].y) != EOF) ++cnt;
    hcnt = cnt;
    cnt = 0;
    fclose(fp);
}

//读取复盘模式的指令
int getcmd() {
    int k = 0;
    for (; (k != key_esc && k != key_left && k != key_right) || (k == key_left && !cnt) || (k == key_right && cnt >= hcnt); ) {
        k = getch();
    }
    return k;
}

//处理复盘模式的指令
int setcmd() {
    int k = 0;
    if ((k = getcmd()) == key_esc) return 0;
    if (k == key_left && cnt) {
        --cnt; g_x = h[cnt - 1].x; g_y = h[cnt - 1].y;
        arrayForInnerBoardLayout[h[cnt].x][h[cnt].y] = ENPTY;
        return 1;
    }
    if (k == key_right && cnt < hcnt) {
        g_x = h[cnt].x; g_y = h[cnt].y; ++cnt;
        arrayForInnerBoardLayout[g_x][g_y] = player;
        return 1;
    }
}

void initbitboard() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 31; ++j)
            bitboard[i][j] = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 31; ++j)
            bitlen[i][j] = 15;
    for (int i = 0; i < 29; ++i) {
        bitlen[2][i] = (i < 15) ? i + 1 : 29 - i;
        bitlen[3][i] = (i < 15) ? i + 1 : 29 - i;
    }
}

int askblack() {
    char str[100];
    inputbox_getline("你想选黑棋吗？（y/n）", "", str, 100);
    if (str[0] == 'y')
        return 1;
    return 2;
}