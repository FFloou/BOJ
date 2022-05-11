/*

2022.05.11.
- 1600 말이 되고픈 원숭이: https://www.acmicpc.net/problem/1600
- 골드Ⅳ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 말처럼 이동할 수 있는 횟수를 포함하여 bfs로 탐색한다.
- 방문 여부를 저장할 때 말처럼 이동할 수 있는 남은 횟수도 고려할 요소기 때문에 
   [x좌표] [y좌표] [남은 횟수] 3차원 배열로 저장한다.

*/
#include <iostream>
#include <queue>
using namespace std;

struct pos {
	int x;
	int y;
	int k;
	int dist;
};

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int hx[9] = { -2,-1,1,2,2,1,-1,-2 };
int hy[9] = { 1,2,2,1,-1,-2,-2,-1 };

int K, W, H;
int map[201][201];
bool visited[201][201][31];
int min_dist = -1;

queue<pos> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> K >> W >> H;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
		}
	}
	q.push({ 0,0,K,0 });
	visited[0][0][K] = true;

	while (!q.empty()) {
		pos curr = q.front(); q.pop();
		if (curr.x == H - 1 && curr.y == W - 1) {
			min_dist = curr.dist;
			break;
		}
		//평범하게 이동하는 경우
		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx < 0 || nextx >= H || nexty < 0 || nexty >= W || visited[nextx][nexty][curr.k]) continue;
			if (map[nextx][nexty] == 1) continue;
			visited[nextx][nexty][curr.k] = true;
			q.push({ nextx, nexty, curr.k, curr.dist + 1 });

		}
		if (curr.k == 0) continue;
		////말처럼 이동하는 경우
		for (int i = 0; i < 9; i++) {
			int nextx = curr.x + hx[i];
			int nexty = curr.y + hy[i];
			if (nextx < 0 || nextx >= H || nexty < 0 || nexty >= W || visited[nextx][nexty][curr.k-1]) continue;
			if (map[nextx][nexty] == 1) continue;
			visited[nextx][nexty][curr.k - 1]= true;
			q.push({ nextx, nexty, curr.k - 1, curr.dist + 1 });

		}

	}
	cout << min_dist;
	return 0;
}
