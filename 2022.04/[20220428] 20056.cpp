/*

2022.04.28.
- 20056 마법사 상어와 파이어볼: https://www.acmicpc.net/problem/20056
- 구현, 시뮬레이션
- 골드Ⅳ

- 파이어볼이 이동하고, 합쳐질 때 필요한 정보를 저장한다.
- 특히 방향이 모두 홀수이거나 양수를 확인하는 것은 %2의 결과를 더해
  모두 양수이면 파이어볼의 개수, 모두 홀수이면 0이 되는 것을 활용한다.
- 1칸에 1개가 있는 경우 나누어지지 않기 때문에 
  1칸에 있는 파이어볼의 개수에 따라서 저장하는 내용을 다르게 한다.

*/
#include <iostream>
#include <vector>
using namespace std;

struct fball {
	int r_pos;
	int c_pos;
	int mass;
	int speed;
	int direction;
};

struct cell {
	int tmass;
	int tnum;
	int tdirection;
	int tspeed;
};

int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int N, M, K;
int r, c, m, s, d;

vector <fball> flist;
cell map[51][51];


void move_fireball() {
	for (int i = 0; i < flist.size(); i++) {

		int step = flist[i].speed % N;
		int dir = flist[i].direction;

		int newr = (N + flist[i].r_pos + (dr[dir] * step)) % N;
		int newc = (N + flist[i].c_pos + (dc[dir] * step)) % N;

		if (newr == 0) newr = N;
		if (newc == 0) newc = N;

		map[newr][newc].tmass += flist[i].mass;
		map[newr][newc].tspeed += flist[i].speed;
		map[newr][newc].tnum += 1;

		if (map[newr][newc].tnum == 1) { 
			map[newr][newc].tdirection = dir;
		}
		else { // 2개부터 홀수 양수 체크
			if (map[newr][newc].tnum == 2) {
				map[newr][newc].tdirection %= 2;
			}
			map[newr][newc].tdirection += dir % 2;
		}
	

	}
	return;
}

void divide_fireball() {
	flist.clear();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j].tnum == 1) { //파이어볼이 1개일 때는 분열하지 않음
				flist.push_back({ i,j,map[i][j].tmass, map[i][j].tspeed, map[i][j].tdirection });
			}
			else if (map[i][j].tmass / 5 == 0) {
				continue;
			}
			else{

				int newm = map[i][j].tmass / 5;
				int news = map[i][j].tspeed / map[i][j].tnum;
				int newdir = 0;
				if (map[i][j].tdirection != 0 && map[i][j].tdirection != map[i][j].tnum) newdir = 1;

				for (int k = 0; k < 4; k++) {
					flist.push_back({ i, j, newm, news, newdir });
					newdir += 2;
				}
			}

		}
	}
	return;
}

void initialize() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = { 0,0,0,0 };
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;
		flist.push_back({ r,c,m,s,d });
	}
	while (K--) {
		initialize();
		move_fireball();
		divide_fireball();

	}

	int cnt = 0;
	for (int i = 0; i < flist.size(); i++) {
		cnt += flist[i].mass;
	}
	cout << cnt;

	return 0;
}
