#ifndef _AI_H_
#define _AI_H_

#include"common.h"
#include"evaluate.h"

struct Tree {
	int x, y, score;
};
const int inf = 2e6;
const int mdep = 6;
void ai_op(void);
void bitset(int, int, int);
void bitdel(int, int, int);
int calc(void);
int calc_now(void);
bool check_dis(int, int);
bool cmp(Tree, Tree);
int gen(Tree[], int);
struct Tree dfs(int, Tree, Tree, int);
int calc_point(int, int, int);

#endif // !_AI_H_

