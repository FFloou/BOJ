/*

2022.05.23.
- 16197 두 동전: https://www.acmicpc.net/problem/16197
- 골드Ⅳ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 백트래킹

- bfs로 동전들의 위치에서 이동할 수 있는 방법을 모두 탐색해본다.
- 두 동전의 다음 위치를 결정할 때, 어떤 조건을 먼저 살펴야 할지 순서에 주의한다.
   -> out of range 등의 에러 발생 가능성 높음
- 최대 이동 횟수 체크 -> 이동 -> 조건 만족 확인 순으로 작동하므로 최대 이동 횟수 설정에 주의한다.

*/
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
struct coins {
	pii coin1;
	pii coin2;
};
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int N, M;
char map[21][21];

queue<pair<int, coins>> q;
pii coin_pos[2];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	int idx = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'o') {
				coin_pos[idx++] = { i, j };
				map[i][j] = '.';
			}
		}
	}

	q.push({ 0, {coin_pos[0], coin_pos[1]} });

	int answer = -1;
	while (!q.empty()) {
		int move_num = q.front().first;
		pii c1 = q.front().second.coin1;
		pii c2 = q.front().second.coin2;
		q.pop();
		if (move_num >= 10) break;

		for (int i = 0; i < 4; i++) {
			pii new_c1 = { c1.first + dx[i], c1.second + dy[i] };
			pii new_c2 = { c2.first + dx[i], c2.second + dy[i] };

			// 보드 밖으로 떨어졌는지 확인
			bool fall1 = false;
			bool fall2 = false;

			if (new_c1.first < 0 || new_c1.first >= N || new_c1.second < 0 || new_c1.second >= M) fall1 = true;
			if (new_c2.first < 0 || new_c2.first >= N || new_c2.second < 0 || new_c2.second >= M) fall2 = true;

			if (fall1 && fall2) continue;
			else if (fall1 || fall2) {
				answer = move_num + 1;
				while (!q.empty()) q.pop();
				break;
			}
			// 벽으로 이동하는 경우 원래 자리에 있도록 처리
			if (map[new_c1.first][new_c1.second] == '#') {
				new_c1 = c1;
			}
			if (map[new_c2.first][new_c2.second] == '#') {
				new_c2 = c2;
			}
			if (new_c1 == c1 && new_c2 == c2) continue;
			else q.push({ move_num + 1, {new_c1, new_c2} });
			
		}
	}
	cout << answer;
	return 0;
}
