/*

2022.05.04.
- 2638 치즈: https://www.acmicpc.net/problem/2638
- 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 시뮬레이션, 깊이 우선 탐색
- 골드Ⅳ

- 외부 공기는 모두 이어져 있고, 내부 공기는 이들과 이어져 있지 않은 공기들이다.
   -> 외부 공기가 확실한 (0,0)에서 bfs를 통해 외부 공기를 모두 확인한다.
- bfs로 외부 공기를 확인하며 치즈가 외부 공기 몇 칸과 접촉하고 있는지 기록한다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { -1, 1, 0, 0 };

int N, M;
int map[101][101];
int cheese_cnt;

int air_touch[101][101];
bool visited[101][101];
queue<pair<int, int>> q;

void initialize() {
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			visited[i][j] = false;
			air_touch[i][j] = 0;
		}
	}
	while (!q.empty()) q.pop();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) cheese_cnt++;
		}
	}

	int t = 0;
	while (cheese_cnt > 0) {
		initialize();

		//bfs로 외부 공기탐색. 외부공기는 모두 이어져있다. 가장자리인 (0,0)은 항상 외부공기이다.
		q.push({ 0,0 });
		visited[0][0] = true;

		while (!q.empty()) {
			pair<int, int> curr = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int nextx = curr.first + dx[i];
				int nexty = curr.second + dy[i];
				if (nextx >= 0 && nextx < N && nexty >= 0 && nexty < M) {
					if (map[nextx][nexty] == 0 && visited[nextx][nexty] == false) {
						visited[nextx][nexty] = true;
						q.push({ nextx, nexty });
					}
					else if (map[nextx][nexty] == 1) { //치즈가 외부공기와 접촉하는 경우 기록
						air_touch[nextx][nexty]++;
					}
				}
			}
		}

		//치즈가 외부공기와 2면이상 접촉하는 경우
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (air_touch[i][j] >= 2) {
					map[i][j] = 0;
					cheese_cnt--;
				}
			}
		}
		t++;
	}
	cout << t;
	return 0;
}
