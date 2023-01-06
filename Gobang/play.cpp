#include"play.h"

char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
{
        "���өөөөөөөөөөөөө�",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
}; //��ʼ��������
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1]; //������洢������ʾ������ 
char play1Pic[] = "��";//������;
char play1CurrentPic[] = "��";
char play2Pic[] = "��";//������;
char play2CurrentPic[] = "��";
int arrayForInnerBoardLayout[SIZE][SIZE];

//��ʼ��һ�������̸�� 
void initRecordBorard(void) {
    memset(arrayForInnerBoardLayout, 0, sizeof(arrayForInnerBoardLayout));
}

//��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
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

//��ʾ���̸�� 
void displayBoard(void) {
    //��һ��������
    printf("         ");
    if (gamemode == '0')
        printf("���������˶�ս\n");
    else if (gamemode == '1')
        printf("�������˻���ս\n");
    else
        printf("�����������ս\n");
    //�ڶ�������arrayForDisplayBoard�������Ļ��
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

//��ӡ����
void display() {
    innerLayoutToDisplayArray();
    displayBoard();
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
    int correct_input = 0;
    char temp_y;
    do {
        while (getchar() != '\n')
            ;   //���������
        scanf("\n%c%d", &temp_y, &g_x);  //\n���ղ����Ļس��� ��ͬ

        while ((!inrange(g_x - 1, temp_y - 'a') && !inrange(g_x - 1, temp_y - 'A'))) {
            printf("��������Ƿ�������������\n");
            while (getchar() != '\n')
                ;
            scanf("\n%c%d", &temp_y, &g_x);
        }
        g_y = (temp_y > 'Z') ? temp_y - 'a' : temp_y - 'A';
        --g_x;
        //�ж�����λ���Ƿ��Ѿ�������
        if (arrayForInnerBoardLayout[g_x][g_y])
            printf("����λ�������ӣ����������� \n");
        else 
            correct_input = 1;
    } while (correct_input != 1);
}

//���벢��������
void setinput() {
    getinput();
    arrayForInnerBoardLayout[g_x][g_y] = player + 2;
}

//���������Ϣ
void printpos() {
    if (player == BLACK)
        printf("����������%c%d\n", 'A' + g_y, g_x + 1);
    else 
        printf("����������%c%d\n", 'A' + g_y, g_x + 1);
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
    if (result == WHITE)
        printf("����Ӯ\n");
    else if (result == BLACK)
        printf("����Ӯ\n");
    else
        printf("ƽ��\n");
}
