/*

2022.06.14.
- 2665 미로만들기: https://www.acmicpc.net/problem/2665
- 골드Ⅳ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 데이크스트라

- bfs로 모든 경로를 탐색하면서 해당 칸에 최소 몇개의 색을 바꾸고 도착할 수 있는지 저장한다.
- 느리지만 적은 수의 방을 바꾸고 도착한 경우가 있을 수 있으므로 끝방에 도착하는 즉시 종료하지 않고
  큐가 모두 빈 후에 bfs가 종료되도록 한다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
const int INF = 50000;
int n;
char map[51][51];
int visited[51][51];
queue<pair<int, int>> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			visited[i][j] = INF;
		}
	}
	q.push({ 1, 1 });
	visited[1][1] = 0;

	while (!q.empty()) {
		pair<int, int> curr = q.front();
		int change = visited[curr.first][curr.second];
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextx = curr.first + dx[i];
			int nexty = curr.second + dy[i];

			if (nextx < 1 || nexty < 1 || nexty > n || nextx > n) continue;
			if (map[nextx][nexty] == '1') {
				if (visited[nextx][nexty] <= change) continue;
				visited[nextx][nexty] = change;
				q.push({ nextx, nexty });
			}
			else {
				if (visited[nextx][nexty] <= change + 1) continue;
				visited[nextx][nexty] = change + 1;
				q.push({ nextx, nexty });
			}
		}
	}

	cout << visited[n][n];
	return 0;
}
