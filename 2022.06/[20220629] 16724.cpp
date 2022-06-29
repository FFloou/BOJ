/*

2022.06.29.
- 16724 피리 부는 사나이: https://www.acmicpc.net/problem/16724
- 골드Ⅲ
- 그래프 이론, 자료 구조, 그래프 탐색 깊이 우선 탐색, 분리 집합

- 방향을 따라 이동했을 때 만나는 칸을 같은 그룹으로 묶고 한 그룹당 하나의 SAFE ZONE을 만든다.
- 방문한 적 없는 칸에서 출발하여 방문한 적있는 칸을 만날 때 까지 주어진 방향대로 진행하면서 해당 위티를 큐에 넣는다.
  -> 이미 그룹을 이루고 있는 칸을 만나면(0 이상) 큐에 들어있는 위치의 값을 해당 그룹 번호로 바꾼다.
  -> 새로운 그룹을 이루게 되면(-1) 그룹 번호(safe_zone)를 하나 증가시키고 큐에 들어잇는 위치의 값을 해당 번호로 바꾼다.

*/

#include <iostream>
#include <queue>


using namespace std;

typedef pair<int, int> pii;
int N, M;
char map[1001][1001];
int visited[1001][1001];
int safe_zone = 0;
queue <pii> q;

pii next_pos(int x, int y, char dir) {
	if (dir == 'D') return { x + 1, y };
	else if (dir == 'U') return { x - 1, y };
	else if (dir == 'R') return { x, y + 1 };
	else return { x, y - 1 };
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visited[i][j] > 0) continue;

			pii curr = { i,j };
			visited[i][j] = -1;
			q.push(curr);
			while (true) {
				curr = next_pos(curr.first, curr.second, map[curr.first][curr.second]);
				if (visited[curr.first][curr.second] == 0) {
					visited[curr.first][curr.second] = -1;
					q.push({ curr.first, curr.second });
				}
				else if (visited[curr.first][curr.second] == -1) {
					safe_zone++;
					while (!q.empty()) {
						visited[q.front().first][q.front().second] = safe_zone;
						q.pop();
					}
					break;
				}
				else {
					int group = visited[curr.first][curr.second];
					while (!q.empty()) {
						visited[q.front().first][q.front().second] = group;
						q.pop();
					}
					break;
				}
			}
		}
	}
	cout << safe_zone;
	return 0;
}
