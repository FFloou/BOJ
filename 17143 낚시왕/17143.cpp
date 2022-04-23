#include <iostream>
#include <queue>

using namespace std;

struct shark {
	int speed;
	int direction;
	int size;
};
int R, C, M;
int r, c, s, d, z;
int size_sum = 0;
shark board[110][110];
shark tmp_board[110][110];

void shark_catch(int c) {
	for (int i = 1; i <= R; i++) {
		if (board[i][c].size != 0) {
			size_sum += board[i][c].size;
			board[i][c] = { 0,0,0 };
			break;
		}
	}
	return;
}

int change_dir(int x, int y, int d) {
	if (d == 1 && x == 1) return 2;
	if (d == 2 && x == R) return 1;
	if (d == 3 && y == C) return 4;
	if (d == 4 && y == 1)return 3;
	return d;
}

void move_shark() {
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			if (board[r][c].size == 0) continue;

			int curr_r = r;
			int curr_c = c;
			int s = board[r][c].speed;
			int d = board[r][c].direction;
			int z = board[r][c].size;
			
			if (d == 1 || d == 2) s %= (R - 1) * 2;
			else s %= (C - 1) * 2;
			for(int i = 0; i<s; i++){
				d = change_dir(curr_r, curr_c, d);
				if (d == 1) {
					curr_r--;
				}
				else if (d == 2) {
					curr_r++;
				}
				else if (d == 3) {
					curr_c++;
				}
				else {
					curr_c--;
				}
			}

			if (tmp_board[curr_r][curr_c].size < z) {
				tmp_board[curr_r][curr_c] = {s, d, z};
			}
		}
	}
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			board[r][c] = tmp_board[r][c];
			tmp_board[r][c] = { 0,0,0 };
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		board[r][c] = { s, d, z };
	}
	
	for (int i = 1; i <= C; i++) {
		shark_catch(i);
		move_shark();
	}

	cout << size_sum;
	return 0;
}
