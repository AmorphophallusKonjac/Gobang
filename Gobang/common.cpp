#include"common.h"

node h[300];

//�ж��Ƿ����
int inrange(int x, int y) {
	if (0 <= x && x < SIZE && 0 <= y && y < SIZE)
		return 1;
	return 0;
}

//�ж������Ƿ�����
int isfull() {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (arrayForInnerBoardLayout[i][j] == ENPTY)
				return 0;
	return 1;
}
