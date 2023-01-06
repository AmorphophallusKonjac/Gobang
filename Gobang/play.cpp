#include"play.h"

char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
{
        "┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
}; //初始化空棋盘
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1]; //此数组存储用于显示的棋盘 
char play1Pic[] = "●";//黑棋子;
char play1CurrentPic[] = "▲";
char play2Pic[] = "○";//白棋子;
char play2CurrentPic[] = "△";
int arrayForInnerBoardLayout[SIZE][SIZE];

//初始化一个空棋盘格局 
void initRecordBorard(void) {
    memset(arrayForInnerBoardLayout, 0, sizeof(arrayForInnerBoardLayout));
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE * CHARSIZE + 1; ++j)
            arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            switch (arrayForInnerBoardLayout[i][j]) {
            case BLACK:
                for (int k = 0; k < 2; ++k)
                    arrayForDisplayBoard[i][j * 2 + k] = play1Pic[k];
                break;
            case WHITE:
                for (int k = 0; k < 2; ++k)
                    arrayForDisplayBoard[i][j * 2 + k] = play2Pic[k];
                break;
            case LASTBLACK:
                for (int k = 0; k < 2; ++k)
                    arrayForDisplayBoard[i][j * 2 + k] = play1CurrentPic[k];
                arrayForInnerBoardLayout[i][j] = BLACK;
                break;
            case LASTWHITE:
                for (int k = 0; k < 2; ++k)
                    arrayForDisplayBoard[i][j * 2 + k] = play2CurrentPic[k];
                arrayForInnerBoardLayout[i][j] = WHITE;
                break;
            default: {}
                break;
            }
        }
}

//显示棋盘格局 
void displayBoard(void) {
    //第一步：标题
    printf("         ");
    if (gamemode == '0')
        printf("五子棋人人对战\n");
    else if (gamemode == '1')
        printf("五子棋人机对战\n");
    else
        printf("五子棋机机对战\n");
    //第二步：将arrayForDisplayBoard输出到屏幕上
    printf(" ");
    for (int i = 0; i < SIZE; ++i) {
        printf("%2c", i + 'A');
    }
    printf("\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("%2d", i + 1);
        for (int j = 0; j < SIZE * CHARSIZE; ++j) {
            printf("%c", arrayForDisplayBoard[i][j]);
            if (j % 2 && !arrayForInnerBoardLayout[i][j / 2]) printf(" ");
        }
        printf("\n");
    }
}

//打印棋盘
void display() {
    innerLayoutToDisplayArray();
    displayBoard();
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
    int correct_input = 0;
    char temp_y;
    do {
        while (getchar() != '\n')
            ;   //清空输入流
        scanf("\n%c%d", &temp_y, &g_x);  //\n吸收残留的回车符 下同

        while ((!inrange(g_x - 1, temp_y - 'a') && !inrange(g_x - 1, temp_y - 'A'))) {
            printf("输入坐标非法，请重新输入\n");
            while (getchar() != '\n')
                ;
            scanf("\n%c%d", &temp_y, &g_x);
        }
        g_y = (temp_y > 'Z') ? temp_y - 'a' : temp_y - 'A';
        --g_x;
        //判断输入位置是否已经有棋子
        if (arrayForInnerBoardLayout[g_x][g_y])
            printf("输入位置有棋子，请重新输入 \n");
        else 
            correct_input = 1;
    } while (correct_input != 1);
}

//读入并处理坐标
void setinput() {
    getinput();
    arrayForInnerBoardLayout[g_x][g_y] = player + 2;
}

//输出落子信息
void printpos() {
    if (player == BLACK)
        printf("黑子落在了%c%d\n", 'A' + g_y, g_x + 1);
    else 
        printf("白子落在了%c%d\n", 'A' + g_y, g_x + 1);
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
    if (result == WHITE)
        printf("白棋赢\n");
    else if (result == BLACK)
        printf("黑棋赢\n");
    else
        printf("平局\n");
}
