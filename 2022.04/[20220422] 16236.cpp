/*

2022.04.22.
- 16236 아기 상어: https://www.acmicpc.net/problem/16236
- 구현, 그래프 이런, 그래프 탐색, 너비 우선 탐색, 시뮬레이션
- 골드Ⅲ

- bfs로 다음에 먹을 고기를 탐색하고, 조건에 따라 상어를 움직인다.
- 단순히 큐에 넣는 순서만으로는 거리가 같은 때 선택 조건을 만족시킬 수 없다.
    -> 우선순위 큐로 거리가 같을 때 가장 위, 가장 왼쪽의 물고리를 먼저 꺼낼 수 있도록 해준다.
	
*/
#include <iostream>
#include <queue>
using namespace std;

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

struct node {
	int x;
	int y;
	int dist;
};

struct cmp {
	bool operator ()(node a, node b) {
		if (a.dist == b.dist) {
			if (a.x == b.x) {
				return a.y > b.y;
			}
			else return a.x > b.x;
		}
		else return a.dist > b.dist;
	}
};
int map[21][21];
int N;

int answer = 0;
int shark_size = 2;
int eaten_fish = 0;
int fish_cnt = 0;

pair<int, int> shark_pos;

int bfs(int x, int y) {
	priority_queue<node, vector<node>, cmp>q;

	bool visited[21][21] = { false };
	int dist = 0;

	q.push({ x, y, 0 });
	visited[x][y] = true;

	while (!q.empty()) {
		node curr = q.top(); q.pop();

		if (map[curr.x][curr.y] != 0 && map[curr.x][curr.y] < shark_size) { //먹기 성공한 경우
			shark_pos = { curr.x, curr.y };
			map[curr.x][curr.y] = 0;
			eaten_fish++;
			dist = curr.dist;
			if (eaten_fish == shark_size) { //아기상어 성장
				shark_size++;
				eaten_fish = 0;
			}
			break;
		}

		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx >= 0 && nextx < N && nexty >= 0 && nexty < N && visited[nextx][nexty] == false) {
				if (map[nextx][nexty] > shark_size) continue;
				visited[nextx][nexty] = true;
				q.push({ nextx, nexty, curr.dist + 1 });
			}
		}

	}
	return dist;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark_pos = { i,j };
				map[i][j] = 0;
			}
		}
	}
	while (true) {
		int t = bfs(shark_pos.first, shark_pos.second);

		// 더 이상 먹을 고기가 없는 경우
		if (t == 0) break;
		else answer += t;

	}

	cout << answer;
	return 0;
}
