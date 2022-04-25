#include <iostream>
#include <vector>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int R, C, T;
int map[51][51];
int tmp_map[51][51];
vector<pair<int, int>> air_cleaner;

void initialize() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			tmp_map[i][j] = 0;
		}
	}
	tmp_map[air_cleaner[0].first][air_cleaner[0].second] = -1;
	tmp_map[air_cleaner[1].first][air_cleaner[1].second] = -1;
}
void spread_dust() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == 0 || map[i][j] == -1) continue;

			int cnt = 0;
			int divided = map[i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int nextr = i + dx[k];
				int nextc = j + dy[k];
				
				if (nextr >= 0 && nextr < R && nextc >= 0 && nextc < C && map[nextr][nextc] != -1) {
					tmp_map[nextr][nextc] += divided;
					cnt++;
				}
			}
			tmp_map[i][j] += (map[i][j] - divided* cnt);
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = tmp_map[i][j];
		}
	}
}
void upper_cleaning(int r, int c) {

	for (int i = 1; i <= C-1; i++) { //right
		map[r][i] = tmp_map[r][i-1];
	}
	for (int i = r-1; i >= 0; i--) {
		map[i][C - 1] = tmp_map[i+1][C - 1];
	}
	for (int i = C - 2; i >= 0; i--) {
		map[0][i] = tmp_map[0][i + 1];
	}
	for (int i = 1; i <= r-1 ; i++) {
		map[i][0] = tmp_map[i - 1][0];
	}
	map[r][c] = -1;
	map[r][c + 1] = 0;
}

void lower_cleaning(int r, int c) {
	for (int i = 1; i <= C - 1; i++) {
		map[r][i] = tmp_map[r][i - 1];
	}
	for (int i = r+1; i <= R - 1; i++) {
		map[i][C - 1] = tmp_map[i - 1][C - 1];
	}
	for (int i = C - 2; i >= 0; i--) {
		map[R - 1][i] = tmp_map[R - 1][i + 1];
	}
	for (int i = R - 2; i >= r + 1; i--) {
		map[i][0] = tmp_map[i + 1][0];
	}
	map[r][c] = -1;
	map[r][c + 1] = 0;
}

int dust_count() {
	int cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cnt += map[i][j];
		}
	}
	cnt += 2; // 공기청정기인 -2 상쇄
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C >> T;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				air_cleaner.push_back({ i,j });
			}

		}
	}

	while (T--) {
		initialize();
		spread_dust();
		upper_cleaning(air_cleaner[0].first, air_cleaner[0].second);
		lower_cleaning(air_cleaner[1].first, air_cleaner[1].second);
	}

	int cnt = dust_count();
	cout << cnt;
	return 0;
}
