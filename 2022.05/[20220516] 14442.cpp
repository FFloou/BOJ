/*

2022.05.16.
- 14442 벽 부수고 이동하기 2: https://www.acmicpc.net/problem/14442
- 골드Ⅲ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- dfs로 탐색하면서 몇 개의 벽을 부수고 도착했는지 함께 저장한다.
- 방문 여부를 확인할 때는 위치+부순 벽의 개수를 묶어 확인한다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

struct pos {
	int x;
	int y;
	int wall;
	int dist;
};
int N, M;
int K;

char map[1001][1001];
bool visited[1001][1001][11];
queue<pos> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
	q.push({ 1, 1, 0, 1 });
	visited[1][1][0] = true;

	int answer = -1;
	while (!q.empty()) {
		pos curr = q.front(); q.pop();
		if (curr.x == N && curr.y == M) {
			answer = curr.dist;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];

			if (nextx<1 || nexty <1 || nextx>N || nexty>M) continue;
			int crushed = (map[nextx][nexty] == '1') ? (curr.wall + 1) : curr.wall;
			if (crushed > K) continue;
			if (visited[nextx][nexty][crushed] == true) continue;

			q.push({ nextx, nexty, crushed, curr.dist + 1 });
			visited[nextx][nexty][crushed] = true;
		}
	}
	cout << answer;
	return 0;
}
