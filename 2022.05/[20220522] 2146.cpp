/*

2022.05.22.
- 2146 다리 만들기: https://www.acmicpc.net/problem/2146
- 골드Ⅲ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- bfs를 통해 각 섬들에 번호를 붙인다. 이 때, 섬과 바로 붙어있는 바다에도 그 섬의 번호를 붙인다.
- 섬에 속한 육지인 경우 dist = 0, 섬에 바로 붙은 바다인 경우 dist = 1으로 설정한다.
- 섬과 바로 붙어있는 바다는 따로 큐에 저장하고, 그 큐를 이용하여 bfs로 섬과 섬이 연결되는 부분을 찾는다.
- 다음 탐색할 칸이 이미 방문한 적이 있고, 다른 섬에서 출발한 것이면(map의 번호가 다르면) 다리가 연결된 것이다.
- 찾은 값이 가장 작은 값이 아닐 수 있으므로 바로 종료하지 않고 모든 경우를 탐색해본다.

*/
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N;
int map[101][101];
int dist[101][101];

queue < pair<int, int>> bridge_q;
queue<pair<int, int>> land_q;

void land_bfs(int x, int y, int num) {
	dist[x][y] = 0;
	map[x][y] = num;
	land_q.push({ x, y });

	while (!land_q.empty()) {
		pair<int, int> curr = land_q.front();
		land_q.pop();

		for (int i = 0; i < 4; i++) {
			int nextx = curr.first + dx[i];
			int nexty = curr.second + dy[i];
			if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= N) continue;
			if (dist[nextx][nexty] != -1) continue;

			// 다음 칸이 섬에 포함된 육지인 경우
			if (map[nextx][nexty] == 1) {
				land_q.push({ nextx, nexty });
				dist[nextx][nexty] = 0;
			}
			// 다음 칸이 섬과 바로 연결된 바다인 경우
			else if(map[nextx][nexty] == 0) {
				bridge_q.push({ nextx, nexty });
				dist[nextx][nexty] = 1;
			}
			map[nextx][nexty] = num;
		}
	}
	return;
}

int bridge_bfs() {
	int min_dist = N * N;
	while (!bridge_q.empty()) {
		pair<int, int> curr = bridge_q.front();
		bridge_q.pop();

		for (int i = 0; i < 4; i++) {
			int nextx = curr.first + dx[i];
			int nexty = curr.second + dy[i];
			if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= N) continue;
			//다음 칸에 방문한적 없는 경우
			if (dist[nextx][nexty] == -1) {
				bridge_q.push({ nextx, nexty });
				dist[nextx][nexty] = dist[curr.first][curr.second] + 1;
				map[nextx][nexty] = map[curr.first][curr.second];
				continue;
			}
			//다음 칸에 방문한 적이 있고, 다른 섬에서 출발한 경우
			if (map[nextx][nexty] != map[curr.first][curr.second]) {
				min_dist = min(min_dist, dist[nextx][nexty] + dist[curr.first][curr.second]);
				break;
			}

		}
	}
	return min_dist;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			dist[i][j] = -1;
		}
	}

	int group = 2;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 1) land_bfs(i, j, group++);
		}
	}

	cout << bridge_bfs()<<'\n';

	return 0;
}
