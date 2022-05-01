/*

2022.04.23.
- 15685 드래곤 커브: https://www.acmicpc.net/problem/15685
- 구현, 시뮬레이션
- 골드Ⅳ

- 드래곤 커브의 방향의 규칙을 찾아 커브를 만들고 그 방향을 배열로 저장한다.
- 저장된 배열의 방향을 읽어 드래곤 커브가 지나는 점을 표시한다.

*/
#include <iostream>

using namespace std;

int curve[4] = { 1,2,3,0 };
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, -1, 0, 1 };

int N;
int x, y, d, g;
int dragon_arr[1030];
bool point[101][101];

int draw_curve(int d, int g) {
	dragon_arr[1] = d;
	int last_idx = 1;
	for (int cnt = 1; cnt <= g; cnt++) {
		for (int i = 1; i <= last_idx; i++) {
			dragon_arr[last_idx * 2 - i + 1] = curve[dragon_arr[i]];
		}
		last_idx *= 2;
	}
	return last_idx;
}
void point_check(int x, int y, int max_idx) {
	int s = x;
	int e = y;
	point[s][e] = true;
	for (int i = 1; i <= max_idx; i++) {

		s += dx[dragon_arr[i]];
		e += dy[dragon_arr[i]];
		point[s][e] = true;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		int max_idx = draw_curve(d, g);
		point_check(x, y, max_idx);
	}
	int answer = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (point[i][j] == true && point[i + 1][j] == true && point[i][j + 1] == true && point[i + 1][j + 1] == true) {
				answer++;
			}
		}
	}

	cout << answer;
	return 0;
}
