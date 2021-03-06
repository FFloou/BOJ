/*

2022.04.08.
- 17142 연구소 3: https://www.acmicpc.net/problem/17142
- 그래프 이론, 브루트포스 알고리즘, 그래프 탐색, 너비 우선 탐색
- GoldIV

- 바이러스의 위치를 저장하고, M개의 활성화할 바이러스를 선택한다.
- 바이러스의 위치 인덱스로 증가하는 수열을 만들어 활성 바이러스로 선택한다.
- 선택한 바이러스들로 bfs를 시행한다.
- bfs에서 빈 칸(0)의 개수를 기준으로 확산의 완료 여부를 판단한다.
- 이전에 찾은 최소 시간을 넘어간다면 bfs를 종료하여 탐색 시간을 줄인다.
- 큐가 비어서 종료된 경우는 확산이 불가능 하여 종료된 경우이다.
    - 큐에 좌표를 넣으며 남은 빈 칸의 개수와 시간을 업데이트하기 때문이다.
- 방문 여부를 저장하는 배열을 따로 쓰지 않고 복사한 map에 표시된 숫자로 방문여부를 판단한다.

*/

#include <iostream>
#include <queue>
#include <vector>
#define MAX 987654321

using namespace std;

int N, M;
int zero;
int map[51][51];
int tmap[51][51];

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

queue<pair<int, int>> q;
vector<pair<int, int>> v;
vector<int> selected;
int answer = MAX;

void initialize() {
	while (!q.empty()) q.pop(); //큐 비우기

	for (int i = 0; i < N; i++) { //map 복사
		for (int j = 0; j < N; j++) {
			tmap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < M; i++) { //선택한 바이러스만 활성화
		int x = v[selected[i]].first;
		int y = v[selected[i]].second;

		tmap[x][y] = 3; //활성 바이러스 == 3
		q.push({ x, y });
	}
	return;
}

int bfs() {
	int t = 0; //시간
	int s = zero; //남은 빈칸 수

	while (!q.empty() && s > 0 && t<answer) { //빈칸이 없거나 최소 시간을 넘으면 종료
		int qsize = q.size();
		for (int i = 0; i < qsize; i++) {
			pair<int, int> curr = q.front(); q.pop();
			for (int j = 0; j < 4; j++) {
				int nextx = curr.first + dx[j];
				int nexty = curr.second + dy[j];

				if (nextx >= 0 && nexty >= 0 && nextx < N && nexty < N && tmap[nextx][nexty] != 1) { //벽이 아닌 경우
					if (tmap[nextx][nexty] == 3) continue; //이미 활성된 부분 건너뛰기

					if(tmap[nextx][nexty] == 0) s--; //빈 칸인 경우 남은 빈칸 수 줄이기
					tmap[nextx][nexty] = 3; // 바이러스 활성화
					q.push({ nextx, nexty });
				}
			}
		}
		t++; //시간 증가
	}
	if (q.empty()) return -1; // 더 이상 이동이 불가능해 종료된 경우
	else return t;  //최소 시간 리턴
}

void select(int num) {
	if (selected.size() == M) { // 활성화 할 바이러스 선택 완료
		initialize(); // 초기화
		int result = bfs(); //바이러스가 퍼짐
		if (result > -1 ) answer = result; // 빈칸이 남은 경우가 아니라면 업데이트
		return;
	}
	for (int i = num; i < v.size(); i++) {
		if (M - selected.size() > v.size() - num) break; //바이러스 선택을 완성하지 못하는 경우 prune
		selected.push_back(i);
		select(i + 1);
		selected.pop_back();
	}
  return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) zero++; // 빈 칸 개수 세기
			else if (map[i][j] == 2) v.push_back({ i,j }); // 바이러스가 위치한 장소 저장
		}
	}
	select(0);
	if (answer == MAX) cout << -1; //answer의 업데이트가 없는 경우
	else cout << answer;
	return 0;
}
