/*

2022.07.01.
- 18405 경쟁적 전염: https://www.acmicpc.net/problem/18405
- 골드Ⅴ
- 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 시뮬레이션

- visited에 방문한 시간을 저장하고 map에 바이러스의 번호를 저장하면서 bfs를 진행한다.
- 방문 시간은 동일하게 진행되지만 바이러스의 번호가 작은 것부터 시작한다는 보장이 없다.
  -> 이미 방문한 칸의 방문 시간이 현재 방문 시간이 같고, map에 저장된 번호가 현재 번호보다 크면 map에 저장된 번호를 현재 번호로 바꾼다.
  -> bfs 큐에는 이미 들어있고, 방문 시간도 저장되어 있으므로 map의 번호만 바꿔준다.

*/

#include <iostream>
#include <queue>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
typedef pair<int, int> pii;

int N, K;
int S, X, Y;
int map[201][201];
int visited[201][201];
queue<pii> q;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			visited[i][j] = -1;
			if (map[i][j] != 0) {
				q.push({ i, j });
				visited[i][j] = 0;
			}
		}
	}
	cin >> S >> X >> Y;

	for (int t = 1; t <= S; t++) {
		int qsize = q.size();
		for (int i = 0; i < qsize; i++) {
			pii curr = q.front();
			int num = map[curr.first][curr.second];
			q.pop();

			for (int j = 0; j < 4; j++) {
				int nextx = curr.first + dx[j];
				int nexty = curr.second + dy[j];

				if (nextx < 0 || nexty < 0 || nextx >= N || nexty >= N) continue;
				if (visited[nextx][nexty] == -1) {
					q.push({ nextx, nexty });
					map[nextx][nexty] = num;
					visited[nextx][nexty] = t;
				}
				else {
					if (visited[nextx][nexty] == t && map[nextx][nexty] > num) {
						map[nextx][nexty] = num;
					}
				}
			}
			
		}
	}
	cout << map[X-1][Y-1];
	return 0;
}
