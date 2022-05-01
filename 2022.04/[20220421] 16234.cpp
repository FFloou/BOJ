/*

2022.04.21.
- 16234 인구 이동: https://www.acmicpc.net/problem/16234
- 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 시뮬레이션
- GoldⅤ

- bfs로 만들어지는 연합의 수 세기
- bfs로 각 나라를 방문할 때마다 필요한 요소(인구수, 나라 위치 등)를 저장한다.
- 만들어진 연합의 개수가 나라의 개수와 같으면 연합이 없다

*/
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int N, L, R, t;
int country[51][51];
bool visited[51][51];

void bfs(int x, int y) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> uni; // 연합에 속하는 나라의 위치 저장

	int sum = 0;

	q.push({ x, y });
	visited[x][y] = true;
	uni.push_back({ x, y });

	while (!q.empty()) {
		pair<int, int> curr = q.front(); q.pop();
		sum += country[curr.first][curr.second]; //연합에 속한 나라의 인구의 합
		for (int i = 0; i < 4; i++) {
			int nextx = curr.first + dx[i];
			int nexty = curr.second + dy[i];
			if (nextx >= 0 && nextx < N && nexty >= 0 && nexty < N && visited[nextx][nexty] == false) {
				int diff = abs(country[curr.first][curr.second] - country[nextx][nexty]);
				if (diff >= L && diff <= R) {
					uni.push_back({ nextx, nexty });
					visited[nextx][nexty] = true;
					q.push({ nextx, nexty });
				}
			}
		}
	}
	int moved = sum / uni.size();
	for (int i = 0; i < uni.size(); i++){
		country[uni[i].first][uni[i].second] = moved;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> country[i][j];
		}
	}

	while (true) {
		// visited 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = false;
			}
		}

		int union_cnt = 0; //만들어지는 연합의 개수
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == true) continue;
				bfs(i, j); // 연합 만들기
				union_cnt++; 
			}
		}
		// 연합의 개수 == 나라의 개수 (이동이 불가능한 상태)
		if (union_cnt == N * N) break;
		t++;
	}
	cout << t;
	return 0;
}
