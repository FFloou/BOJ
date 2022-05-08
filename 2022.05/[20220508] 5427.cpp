/*
2022.05.08.
- 5427 불: https://www.acmicpc.net/problem/5427
- 그래프 이론, 그래프 탐색, 너비 우선 탐색
- 골드Ⅳ

- 불이 퍼져나가도록 한 후, 상근이가 움직일 수 있는 위치를 bfs로 탐색한다.
- 불이 새로 붙는 칸은 갈 수 없지만, 현재 상근이가 존재한 칸에 불이 붙어도 다른 칸으로 이동할 수는 있다.
    -> 불이 퍼져나간 후에 상근이가 이동한다.
- 빠져나갈 수 있는 위치(배열의 가장자리)에 도착하면 bfs를 종료한다.

*/
#include <iostream>
#include <queue>

using namespace std;


int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int T;
int w, h;
char map[1001][1001];
bool visited[1001][1001];
queue<pair<int, int>> fire;
queue<pair<int, int>> sg;

//불이 사방으로 퍼져나간다.
void spread_fire() {
	int qsize = fire.size();
	for (int i = 0; i < qsize; i++) {
		pair<int, int> curr = fire.front(); fire.pop();
		for (int j = 0; j < 4; j++) {
			int nextx = curr.first + dx[j];
			int nexty = curr.second + dy[j];

			if (nextx < 0 || nexty < 0 || nextx >= w || nexty >= h) continue;
			if (map[nextx][nexty] == '.') {
				map[nextx][nexty] = '*';
				fire.push({ nextx, nexty });
			}
		}
	}

}

void initialize() {
	while (!fire.empty()) fire.pop();

	for (int i = 0; i < 1001; i++) {
		for (int j = 0; j < 1001; j++) {
			visited[i][j] = false;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> T;
	while (T--) {
		initialize();
		cin >> h >> w;
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				cin >> map[i][j];
				if (map[i][j] == '@') { //위치를 큐에 저장하고 map은 빈자리로 표시
					sg.push({ i, j});
					visited[i][j] = true;
					map[i][j] = '.';
				}
				if (map[i][j] == '*') fire.push({ i, j });
			}
		}

		int t = 0;
		int answer = 0;

		while (!sg.empty()) {
			t++; //시간 증가
			spread_fire(); //불이 퍼짐
			int qsize = sg.size(); // t-1 시간에 가능했던 상근이 위치들만 확인
			for (int i = 0; i < qsize; i++) {
				pair<int, int> curr = sg.front(); sg.pop();
				// 탈출할 수 있는 위치에 도착했다면
				if (curr.first == w - 1 || curr.second == h - 1 || curr.first == 0 || curr.second == 0) {
					answer = t;  // 답 저장
					while (!sg.empty()) sg.pop();   // 바깥 while문 탈출 조건
					break; //현재 for문 탈출
				}

				for (int j = 0; j < 4; j++) {
					int nextx = curr.first + dx[j];
					int nexty = curr.second + dy[j];

					if (nextx < 0 || nexty < 0 || nextx >= w || nexty >= h) continue;
					if (map[nextx][nexty] == '.' && visited[nextx][nexty] == false) {
						visited[nextx][nexty] = true;
						sg.push({ nextx, nexty });
					}

				}
			}
		}

		if (answer == 0) cout << "IMPOSSIBLE\n";  //갈 곳이 없어서 bfs 종료
		else cout << answer << '\n';   //답을 찾고 bfs 종료

	}

	return 0;
}
