/*

2022.06.10.
- 1726 로봇: https://www.acmicpc.net/problem/1726
- 골드Ⅲ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 각 명령을 실행했을 때의 상태를 모두 bfs로 탐색하여 정답 상태까지 가장 짧은 거리를 찾는다
- 방향을 고려해야하기 때문에 visited를 3차원 배열로 하여 위치와 방향을 고려하여 방문 여부를 확인한다
- Go명령을 수행할 때, 이동하는 경로에 갈 수 없는 지점(1)이 존재하는지 확인한다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[5] = {0, 0, 0, 1, -1};
int dy[5] = {0, 1, -1, 0, 0};

struct robot {
	int x;
	int y;
	int d;
};
int M, N;
int map[101][101];
int a, b, c;

robot start;
robot goal;

queue<pair<int, robot>> q;
bool visited[101][101][5];

// dir에서 회전할 수 있는 두 방향을 리턴
pair<int, int> turn(int dir) {
	if (dir == 1) return{ 4, 3 };
	else if (dir == 2) return { 3,4 };
	else if (dir == 3) return{ 1,2 };
	else return { 2,1 };
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	cin >> a >> b >> c;
	start = { a, b, c };
	cin >> a >> b >> c;
	goal = { a, b, c };

	q.push({ 0, start });
	visited[start.x][start.y][start.d] = true;

	while (!q.empty()) {
		int cnt = q.front().first;
		robot curr = q.front().second;
		q.pop();

		if (curr.x == goal.x && curr.y == goal.y && curr.d == goal.d) {
			cout << cnt;
			break;
		}
		// Turn 명령을 사용한 경우
		pair<int, int> nextd = turn(curr.d);
		if (!visited[curr.x][curr.y][nextd.first]) {
			q.push({ cnt + 1, {curr.x, curr.y, nextd.first} });
			visited[curr.x][curr.y][nextd.first] = true;
		}
		if (!visited[curr.x][curr.y][nextd.second]) {
			q.push({ cnt + 1, {curr.x, curr.y, nextd.second} });
			visited[curr.x][curr.y][nextd.second] = true;
		}
		// Go 명령을 사용한 경우. 1칸, 2칸, 3칸 이동
		for (int i = 1; i <= 3; i++) {
			int nextx = curr.x + i * dx[curr.d];
			int nexty = curr.y + i * dy[curr.d];

			if (nextx <= 0 || nexty <= 0 || nextx > M || nexty > N) continue;
			// 이동 불가능한 칸이 있으면 같은 방향으로 더 큰 Go 명령은 사용불가
			if (map[nextx][nexty] == 1) break; 
			if (visited[nextx][nexty][curr.d]) continue;

			q.push({ cnt + 1, {nextx, nexty, curr.d} });
			visited[nextx][nexty][curr.d] = true;
		}
	}

	return 0;
}
