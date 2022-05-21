/*

2022.05.21.
- 2589 보물섬: https://www.acmicpc.net/problem/2589
- 골드Ⅴ
- 그래프 이론, 브루트포스 알고리즘, 그래프 탐색, 너비 우선 탐색

- 지도의 모든 L 칸을 돌아다니며 bfs를 실행하여 이어진 L칸 중 가장 멀리있는 칸까지의 거리를 구한다.
- bfs를 실행할 때 visited와 큐를 초기화하여 영향을 주지 않도록 주의한다.

*/
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N, M;
int answer = 0;
char map[51][51];

bool visited[51][51];
queue<pair<int, pair<int, int>>> q;


void initialize() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visited[i][j] = false;
		}
	}
	while (!q.empty()) q.pop();
}

int bfs(int x, int y) {
	initialize();

	q.push({ 0, {x, y} });
	visited[x][y] = true;
	int max_dist = 0;

	while (!q.empty()) {
		pair<int, int> pos = q.front().second;
		int dist = q.front().first;
		q.pop();
		max_dist = max(max_dist, dist);

		for (int i = 0; i < 4; i++) {
			int nextx = pos.first + dx[i];
			int nexty = pos.second + dy[i];
			if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= M) continue;
			if (map[nextx][nexty] == 'W' || visited[nextx][nexty]) continue;

			q.push({ dist + 1, {nextx, nexty} });
			visited[nextx][nexty] = true;
		}
	}

	return max_dist;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'W') continue;
			answer = max(answer, bfs(i, j));
		}
	}
	cout << answer;
	return 0;
}
