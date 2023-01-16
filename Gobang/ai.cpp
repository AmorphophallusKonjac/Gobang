#include"ai.h"

int board[SIZE][SIZE];
int cpbitboard[4][31];
int boardscore;

void ai_op() {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			board[i][j] = arrayForInnerBoardLayout[i][j];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 31; ++j)
			cpbitboard[i][j] = bitboard[i][j];
	boardscore = calc();
	Tree val, alp, bet;
	alp.score = -inf; bet.score = inf;
	val = dfs(0, alp, bet, airole);
	g_x = val.x; g_y = val.y;
}

void bitset(int x, int y, int role) {
	int bitrole = airole - 1;
	board[x][y] = role;
	boardscore -= v[bitrole][bitlen[0][x]][cpbitboard[0][x]] - v[bitrole ^ 1][bitlen[0][x]][cpbitboard[0][x]];
	boardscore -= v[bitrole][bitlen[1][y]][cpbitboard[1][y]] - v[bitrole ^ 1][bitlen[1][y]][cpbitboard[1][y]];
	boardscore -= v[bitrole][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] - v[bitrole ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]];
	boardscore -= v[bitrole][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]] - v[bitrole ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	cpbitboard[0][x] += role * pow(3, y);
	cpbitboard[1][y] += role * pow(3, x);
	cpbitboard[2][leftx(x, y)] += role * pow(3, lefty(x, y));
	cpbitboard[3][rightx(x, y)] += role * pow(3, righty(x, y));
	boardscore += v[bitrole][bitlen[0][x]][cpbitboard[0][x]] - v[bitrole ^ 1][bitlen[0][x]][cpbitboard[0][x]];
	boardscore += v[bitrole][bitlen[1][y]][cpbitboard[1][y]] - v[bitrole ^ 1][bitlen[1][y]][cpbitboard[1][y]];
	boardscore += v[bitrole][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] - v[bitrole ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]];
	boardscore += v[bitrole][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]] - v[bitrole ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
}

void bitdel(int x, int y, int role) {
	int bitrole = airole - 1;
	board[x][y] = 0;
	boardscore -= v[bitrole][bitlen[0][x]][cpbitboard[0][x]] - v[bitrole ^ 1][bitlen[0][x]][cpbitboard[0][x]];
	boardscore -= v[bitrole][bitlen[1][y]][cpbitboard[1][y]] - v[bitrole ^ 1][bitlen[1][y]][cpbitboard[1][y]];
	boardscore -= v[bitrole][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] - v[bitrole ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]];
	boardscore -= v[bitrole][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]] - v[bitrole ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	cpbitboard[0][x] -= role * pow(3, y);
	cpbitboard[1][y] -= role * pow(3, x);
	cpbitboard[2][leftx(x, y)] -= role * pow(3, lefty(x, y));
	cpbitboard[3][rightx(x, y)] -= role * pow(3, righty(x, y));
	boardscore += v[bitrole][bitlen[0][x]][cpbitboard[0][x]] - v[bitrole ^ 1][bitlen[0][x]][cpbitboard[0][x]];
	boardscore += v[bitrole][bitlen[1][y]][cpbitboard[1][y]] - v[bitrole ^ 1][bitlen[1][y]][cpbitboard[1][y]];
	boardscore += v[bitrole][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] - v[bitrole ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]];
	boardscore += v[bitrole][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]] - v[bitrole ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
}

int calc() {
	int bitrole = airole - 1;
	int val = 0;
	for (int i = 0; i < SIZE; ++i) {
		val += v[bitrole][bitlen[0][i]][cpbitboard[0][i]] - v[bitrole ^ 1][bitlen[0][i]][cpbitboard[0][i]];
		val += v[bitrole][bitlen[1][i]][cpbitboard[1][i]] - v[bitrole ^ 1][bitlen[1][i]][cpbitboard[1][i]];
	}
	for (int i = 0; i <= 28; ++i) {
		val += v[bitrole][bitlen[2][i]][cpbitboard[2][i]] - v[bitrole ^ 1][bitlen[2][i]][cpbitboard[2][i]];
		val += v[bitrole][bitlen[3][i]][cpbitboard[3][i]] - v[bitrole ^ 1][bitlen[3][i]][cpbitboard[3][i]];
	}
	return val;
}

int calc_now() {
	int bitrole = airole - 1;
	int val = 0;
	for (int i = 0; i < SIZE; ++i) {
		val += v[bitrole][bitlen[0][i]][bitboard[0][i]] - v[bitrole ^ 1][bitlen[0][i]][bitboard[0][i]];
		val += v[bitrole][bitlen[1][i]][bitboard[1][i]] - v[bitrole ^ 1][bitlen[1][i]][bitboard[1][i]];
	}
	for (int i = 0; i <= 28; ++i) {
		val += v[bitrole][bitlen[2][i]][bitboard[2][i]] - v[bitrole ^ 1][bitlen[2][i]][bitboard[2][i]];
		val += v[bitrole][bitlen[3][i]][bitboard[3][i]] - v[bitrole ^ 1][bitlen[3][i]][bitboard[3][i]];
	}
	return val;
}

bool check_dis(int x, int y) {
	int dx[] = { 0, 0, 1, -1, -1, -1, 1, 1 };
	int dy[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
	for (int i = 0; i < 8; ++i) {
		if (inrange(x + dx[i], y + dy[i]) && board[x + dx[i]][y + dy[i]])
			return 1;
		if (inrange(x + 2 * dx[i], y + 2 * dy[i]) && board[x + 2 * dx[i]][y + 2 * dy[i]])
			return 1;
	}
	return 0;
}

bool cmp(Tree a, Tree b) {
	return a.score > b.score;
}

int gen(Tree f[], int role) {
	int bitrole = role - 1;
	int cnt = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j) {
			if (!board[i][j] && check_dis(i, j)) {
				f[cnt].x = i; f[cnt].y = j; f[cnt++].score = calc_point(i, j, bitrole);
				//std::cout << i << " " << j << " " << calc_point(i, j, bitrole) << "\n";
			}
		}
	std::sort(f, f + cnt, cmp);
	return cnt;
}

struct Tree dfs(int dep, Tree alp, Tree bet, int role) {
	Tree val, f[225];
	int cnt;
	if (dep >= mdep) {
		val.score = boardscore;
		return val;
	}
	cnt = min(gen(f, role), 20);
	if (role == airole) {
		for (int i = 0; i < cnt; ++i) {
			if (alp.score != -inf) {
				bitset(f[i].x, f[i].y, role);
				Tree alp1 = alp; alp1.score++;
				val = dfs(dep + 1, alp, alp1, role ^ 3);
				val.x = f[i].x; val.y = f[i].y;
				bitdel(f[i].x, f[i].y, role);
				if (val.score <= alp.score) continue;
			}
			bitset(f[i].x, f[i].y, role);
			val = dfs(dep + 1, alp, bet, role ^ 3);
			val.x = f[i].x; val.y = f[i].y;
			bitdel(f[i].x, f[i].y, role);
			if (val.score > alp.score)
				alp = val;
			if (alp.score >= bet.score)
				return alp;
		}
		return alp;
	}
	else {
		for (int i = 0; i < cnt; ++i) {
			if (bet.score != inf) {
				bitset(f[i].x, f[i].y, role);
				Tree bet1 = bet; bet1.score--;
				val = dfs(dep + 1, bet1, bet, role ^ 3);
				val.x = f[i].x; val.y = f[i].y;
				bitdel(f[i].x, f[i].y, role);
				if (val.score >= bet.score) continue;
			}
			bitset(f[i].x, f[i].y, role);
			val = dfs(dep + 1, alp, bet, role ^ 3);
			val.x = f[i].x; val.y = f[i].y;
			bitdel(f[i].x, f[i].y, role);
			if (val.score < bet.score)
				bet = val;
			if (alp.score >= bet.score)
				return bet;
		}
		return bet;
	}
}