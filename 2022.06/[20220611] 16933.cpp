/*

2022.06.11.
- 16933 벽 부수고 이동하기 3: https://www.acmicpc.net/problem/16933
- 골드Ⅰ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 위치, 부순 벽의 수, 시간이 상태의 각 요소가 되어 visited를 4차원 배열로 선언하여 사용한다.
- bfs를 위한 큐에는 시간을 저장하지 않고, 이동한 거리로 시간을 추측하여 사용한다.
  -> 낮밤이 번갈아 생기기 때문에 홀짝을 확인하여 이동한 후의 시간을 저장하여 사용한다.
- 하나씩 입력 받기 위해 맵을 char로 입력받았음에 주의한다.(벽이 있는지 맵을 확인할 때 주의)

*/
#include <iostream>
#include <queue>

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
struct pos {
	int x;
	int y;
	int crush;
};
using namespace std;

int N, M, K;
bool visited[1001][1001][11][2];
char map[1001][1001];
queue<pair<int, pos>> q;

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
	q.push({ 1, {1, 1, 0} });
	visited[1][1][0][0] = true;

	int answer = -1;
	while (!q.empty()) {
		int d = q.front().first;
		pos curr = q.front().second;
		int t = d % 2; // 이동한 후의 낮(0)밤(1) 표시

		q.pop();
		
		if (curr.x == N && curr.y == M) {
			answer = d;
			break;
		}
		// 이동하는 경우
		for (int i = 0; i < 4; i++) { 
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx <= 0 || nexty <= 0 || nextx > N || nexty > M) continue;

			if (map[nextx][nexty] == '0') { // 벽이 없는 경우
				if (visited[nextx][nexty][curr.crush][t]) continue;
				visited[nextx][nexty][curr.crush][t] = true;
				q.push({ d + 1, {nextx, nexty, curr.crush} });
			}
			else { // 벽이 있는 경우
				if (curr.crush >= K || t == 0 || visited[nextx][nexty][curr.crush + 1][t]) continue;
				visited[nextx][nexty][curr.crush + 1][t] = true;
				q.push({ d + 1, {nextx, nexty, curr.crush + 1} });
			}
		}
		// 이동하지 않는 경우
		if (visited[curr.x][curr.y][curr.crush][t] == false) {
			visited[curr.x][curr.y][curr.crush][t] = true;
			q.push({ d + 1, {curr.x, curr.y,curr.crush} });
		}
	}

	cout << answer;
	return 0;
}
