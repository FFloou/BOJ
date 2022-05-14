/*

2022.05.14.
- 1261 알고스팟: https://www.acmicpc.net/problem/1261
- 골드Ⅴ
- 그래프 이론, 다익스트라, 0-1 너비 우선 탐색

- bfs로 탐색하면서 해당 위치까지 이동했을 때 부순 벽의 수를 기록한다.
- 이전에 기록된 값 보다 더 많은 벽을 부쉈으면 큐에 삽입하지 않는다.(prune)
- 큐가 빌 때 까지 연산을 반복한다. (도착점에 도착하는 모든 경우를 고려하기 위함)
   -> 벽을 피해 이동한 경우 최단 거리가 아니지만 정답인 경로일 수 있다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int N, M;

char map[101][101];
int visited[101][101];
int MAX;
queue<pair<int, int>> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N;
	MAX = M * N; // 벽의 최대 개수
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			visited[i][j] = MAX; // 최대 값으로 초기화
		}
	}
  
	q.push({ 0,0 });
	visited[0][0] = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		if (x == N - 1 && y == M - 1) continue;

		for (int i = 0; i < 4; i++) {
			int nextx = x + dx[i];
			int nexty = y + dy[i];
			if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= M) continue;

			// (nextx, nexty)로 이동할 때까지 부순 벽의 수 계산
			int crushed = (map[nextx][nexty] == '1') ? (visited[x][y] + 1) : (visited[x][y]);
			// (nextx, nexty)로 이동했을 때 부순 벽이 기록한 것 보다 많으면 건너뛰기
			if (visited[nextx][nexty] <= crushed) continue;

			visited[nextx][nexty] = crushed;
			q.push({ nextx, nexty});
		}
	}
	cout << visited[N - 1][M - 1];
	return 0;
}
