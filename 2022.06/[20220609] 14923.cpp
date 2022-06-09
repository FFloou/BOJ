/*

2022.06.09.
- 14923 미로 탈출: https://www.acmicpc.net/problem/14923
- 골드Ⅳ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- bfs로 시작점에서 탈출 위치까지 이동하는 최단 거리를 구한다.
- 지팡이 사용여부를 함께 visited에 저장하여 같은 장소라도 지팡이를 사용하였을 때와 
  사용하지 않았을 때를 모두 bfs로 확인할 수 있도록 한다.

*/
#include <iostream>
#include <queue>

using namespace std;

struct nodes {
	int x;
	int y;
	int c;
	int d;
};

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N, M;
int map[1001][1001];
bool visited[1001][1001][2];
queue<nodes> q;
pair<int, int> start;
pair<int, int> goal;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
		}
	}
	q.push({ start.first, start.second, 0, 0 });
	visited[start.first][start.second][0] = true;

	int answer = -1;
	while (!q.empty()) {
		nodes curr = q.front(); q.pop();
		if (curr.x == goal.first && curr.y == goal.second) {
			answer = curr.d;
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx<=0 || nexty<=0 || nextx>N || nexty>M) continue;
			if (map[nextx][nexty] == 0 && !visited[nextx][nexty][curr.c]) {
				q.push({ nextx, nexty, curr.c, curr.d + 1 });
				visited[nextx][nexty][curr.c] = true;
			}
			else if (map[nextx][nexty] == 1 && !visited[nextx][nexty][curr.c]) {
				if (curr.c == 1) continue; // 지팡이를 사용해서 더 사용할 수 없는 경우
				q.push({ nextx, nexty, 1, curr.d + 1 });
				visited[nextx][nexty][1] = true;
			}
		}
	}
	cout << answer;
	return 0;
}
