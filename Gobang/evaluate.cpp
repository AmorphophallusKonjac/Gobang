#include"evaluate.h"

int v[2][SIZE + 1][14348907] = { 0 };
const int pp[] = { 1, 10, 100, 2200, 10000, 100000 };
extern int cpbitboard[4][31];

//计算单个点的落子得分
int calc_point(int x, int y, int role) {
	bitset(x, y, role + 1);
	int val1 = v[role][15][cpbitboard[0][x]] + v[role][15][cpbitboard[1][y]] + v[role][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] + v[role][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	int val2 = v[role ^ 1][15][cpbitboard[0][x]] + v[role ^ 1][15][cpbitboard[1][y]] + v[role ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] + v[role ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	bitdel(x, y, role + 1);
	int val3 = v[role][15][cpbitboard[0][x]] + v[role][15][cpbitboard[1][y]] + v[role][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] + v[role][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	int val4 = v[role ^ 1][15][cpbitboard[0][x]] + v[role ^ 1][15][cpbitboard[1][y]] + v[role ^ 1][bitlen[2][leftx(x, y)]][cpbitboard[2][leftx(x, y)]] + v[role ^ 1][bitlen[3][rightx(x, y)]][cpbitboard[3][rightx(x, y)]];
	//val -= v[role ^ 1][15][bitboard[0][x]] + v[role ^ 1][15][bitboard[1][y]] + v[role ^ 1][bitlen[2][leftx(x, y)]][bitboard[2][leftx(x, y)]] + v[role ^ 1][bitlen[3][rightx(x, y)]][bitboard[3][rightx(x, y)]];
	return (val1 - val2) - (val3 - val4);
}

//初始化得分函数
void set_score() {
	init_score_5();
	init_score();
}

//初始化长度为6-15的行的得分
void init_score() {
	for (int len = 6; len <= SIZE; ++len) {
		for (int i = 0; i < pow(3, len); ++i) {
			v[0][len][i] = v[0][len - 1][i % (int)pow(3, len - 1)];
			v[1][len][i] = v[1][len - 1][i % (int)pow(3, len - 1)];
			int x = i / (int)(pow(3, len - 6));
			switch (x) {
			case one_1w:
			case one_bw:
			case one_cw:
			case one_dw:
			case one_ew:
				v[1][len][i] += pp[0];
				break;
			case one_2w:
			case one_3w:
			case one_4w:
			case one_5w:
			case two_1w:
			case two_2w:
			case two_3w:
			case two_4w:
				v[1][len][i] += pp[1] - pp[0];
				break;
			case two_jw:
			case two_kw:
			case two_lw:
			case two_mw:
			case two_nw:
			case two_ow:
			case two_pw:
			case two_qw:
			case two_rw:
			case two_sw:
				v[1][len][i] += pp[1];
				break;
			case huo_two_1w:
			case huo_two_2w:
			case huo_two_3w:
			case huo_two_4w:
			case huo_two_5w:
			case huo_two_6w:
			case three_1w:
			case three_2w:
			case three_3w:
			case three_4w:
			case three_5w:
			case three_6w:
			case three_nw:
			case three_ow:
			case three_pw:
			case three_qw:
			case three_rw:
			case three_sw:
				v[1][len][i] += pp[2] - pp[1];
				break;
			case three_uw:
			case three_vw:
			case three_ww:
				v[1][len][i] += pp[2];
				break;
			case huo_three_1w:
			case huo_three_2w:
			case huo_three_3w:
			case huo_three_4w:
			case four_1w:
			case four_2w:
			case four_3w:
			case four_4w:
			case four_dw:
			case four_fw:
			case four_gw:
				v[1][len][i] += pp[3] - pp[2];
				break;
			case four_ew:
				v[1][len][i] += pp[3];
				break;
			case huo_four_w:
				v[1][len][i] += pp[4] - pp[3];
				break;
			case five_w1:
			case five_w2:
			case five_w3:
			case five_w4:
			case five_w5:
				v[1][len][i] += pp[5];
				break;
			case one_1b:
			case one_bb:
			case one_cb:
			case one_db:
			case one_eb:
				v[0][len][i] += pp[0];
				break;
			case one_2b:
			case one_3b:
			case one_4b:
			case one_5b:
			case two_1b:
			case two_2b:
			case two_3b:
			case two_4b:
				v[0][len][i] += pp[1] - pp[0];
				break;
			case two_jb:
			case two_kb:
			case two_lb:
			case two_mb:
			case two_nb:
			case two_ob:
			case two_pb:
			case two_qb:
			case two_rb:
			case two_sb:
				v[0][len][i] += pp[1];
				break;
			case huo_two_1b:
			case huo_two_2b:
			case huo_two_3b:
			case huo_two_4b:
			case huo_two_5b:
			case huo_two_6b:
			case three_1b:
			case three_2b:
			case three_3b:
			case three_4b:
			case three_5b:
			case three_6b:
			case three_nb:
			case three_ob:
			case three_pb:
			case three_qb:
			case three_rb:
			case three_sb:
				v[0][len][i] += pp[2] - pp[1];
				break;
			case three_ub:
			case three_vb:
			case three_wb:
				v[0][len][i] += pp[2];
				break;
			case huo_three_1b:
			case huo_three_2b:
			case huo_three_3b:
			case huo_three_4b:
			case four_1b:
			case four_2b:
			case four_3b:
			case four_4b:
			case four_db:
			case four_fb:
			case four_gb:
				v[0][len][i] += pp[3] - pp[2];
				break;
			case four_eb:
				v[0][len][i] += pp[3];
				break;
			case huo_four_b:
				v[0][len][i] += pp[4] - pp[3];
				break;
			case five_b1:
			case five_b2:
			case five_b3:
			case five_b4:
			case five_b5:
				v[0][len][i] += pp[5];
				break;
			}

		}
	}
}

//初始化长度为5的行的得分
void init_score_5() {
	for (int i = 0; i < 243; i++) {
		switch (i) {
		case 0:
			break;
		case one_2w:
		case one_3w:
		case one_4w:
		case one_5w:
		case one_6w:
			v[1][5][i] = 1;
			break;
		case one_2b:
		case one_3b:
		case one_4b:
		case one_5b:
		case one_6b:
			v[0][5][i] = 1;
			break;
		case 216:
		case 180:
		case 168:
		case 164:
		case 72:
		case 60:
		case 56:
		case 24:
		case 20:
		case 8:
			v[1][5][i] = 10;
			break;
		case 108:
		case 90:
		case 84:
		case 82:
		case 36:
		case 30:
		case 28:
		case 12:
		case 10:
		case 4:
			v[0][5][i] = 10;
			break;
		case 234:
		case 222:
		case 218:
		case 186:
		case 182:
		case 170:
		case 78:
		case 74:
		case 62:
		case 26:
			v[1][5][i] = 100;
			break;
		case 117:
		case 111:
		case 109:
		case 93:
		case 91:
		case 85:
		case 39:
		case 37:
		case 31:
		case 13:
			v[0][5][i] = 100;
			break;
		case 240:
		case 236:
		case 224:
		case 188:
		case 80:
			v[1][5][i] = 2000;
			break;
		case 120:
		case 118:
		case 112:
		case 94:
		case 40:
			v[0][5][i] = 2000;
			break;
		case 242:
			v[1][5][i] = 100000;
			break;
		case 121:
			v[0][5][i] = 100000;
			break;
		}
	}
}