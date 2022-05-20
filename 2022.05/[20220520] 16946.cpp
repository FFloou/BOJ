/*

2022.05.20.
- 16946 벽 부수고 이동하기 4: https://www.acmicpc.net/problem/16946 
- 골드Ⅱ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 깊이 우선 탐색

- bfs를 통해 빈칸이 이어진 그룹을 만들고, 그 그룹에 빈칸이 몇개 있는지 세어준다.
   -> bfs로 탐색하는 중, 빈칸과 바로 이어진 벽을 만나는 경우 그 좌표를 따로 큐에 저장해둔다.
- 빈칸 그룹을 만들어 개수를 센 후, 그 개수를 빈칸 그룹과 이어진 벽에 더해준다.
- bfs로 탐색중 벽을 확인했을 때는 visited를 표시하여 중복해서 포함되지 않게 하고,
   빈칸 개수를 벽에 더해준 후에는 visited를 다시 없는 상태로 되돌려 다음 bfs에서 접근할 수 있도록 한다.
- 최종 출력 할 때 10으로 나눈 나머지를 출력하게 해준다.

*/
#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N, M;
char input;
int map[1001][1001];
bool visited[1001][1001];

queue<pair<int, int>> q;
queue<pair<int, int>> map_update;


void bfs(int x, int y) {
	int cnt = 0; // 이어진 빈칸 수
	
	visited[x][y] = true;
	q.push({ x, y });

	// 이어진 빈칸 개수 세기
	while (!q.empty()) {
		pair<int, int> curr = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < 4; i++) {
			int nextx = curr.first + dx[i];
			int nexty = curr.second + dy[i];

			if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= M) continue;
			if (visited[nextx][nexty] == true) continue;

			visited[nextx][nexty] = true;

			// 빈칸으로 이어진 경우
			if (map[nextx][nexty] == 0) q.push({ nextx,nexty });
			// 빈칸이 아니라 빈칸과 바로 이어진 벽인 경우. 중복으로 들어가는 경우를 막기 위해 visited 설정
			else map_update.push({ nextx,nexty });
		}
	}

	// 이어진 빈칸 그룹과 붙은 벽에 이동할 수 있는 칸의 개수 더하기
	while (!map_update.empty()) {
		pair<int, int> curr = map_update.front(); map_update.pop();
		// 벽 위치에서 이동할 수 있는 칸의 개수를 더함
		map[curr.first][curr.second] += cnt;
		// 벽이 중복하여 체크될 수 있도록 visited를 false로 돌려놓음.
		visited[curr.first][curr.second] = false;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> input;
			map[i][j] = input - '0'; //int 형식으로 저장
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 빈칸이고 방문한적 없는 칸에 대해서 bfs 실행
			if (map[i][j] == 0 && visited[i][j] == false) bfs(i, j);
		}
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << (map[i][j] % 10);
		}
		cout << '\n';
	}
	return 0;
}
