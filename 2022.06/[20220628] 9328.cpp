/*

2022.06.28.
- 9328 열쇠: https://www.acmicpc.net/problem/9328
- 골드Ⅰ
- 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 열쇠를 획득하면 배열에 획득 사실을 저장하고, 방문했던 문 들중 해당 열쇠로 열 수 있는 문들의 위치를 큐에 넣는다.
  -> 이미 방문한 적 있는 위치라면 경로가 존재하므로 열쇠를 획득한 후 다시 그 문으로 되돌아 가는 것이 가능하다.
- 문을 마주치면, 해당되는 열쇠가 있는지 확인하고 열쇠가 있다면 그대로 진행, 없다면 vector배열에 문의 위치를 저장한다. 
- 빌딩 정보의 사방을 빈 공간으로 감싸고, (0,0)에서 bfs를 시작하여 입장 경로가 존재하면 빌딩 안으로 들어갈 수 있도록 한다.
  -> 입장 위치를 찾기 위한 별도의 연산 없이 같은 bfs로 입장 위치를 찾을 수 있다.

*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int T;
int h, w;
string temp;

char map[110][110];
bool visited[110][110];
queue<pair<int, int>> q;
vector<pair<int, int>> doors[26];
int keys[26];

int answer;

void initialize() {
	for (int i = 0; i < 26; i++) {
		keys[i] = 0;
		doors[i].clear();
	}
	for (int i = 0; i < 110; i++) {
		for (int j = 0; j < 110; j++) {
			visited[i][j] = false;
		}
	}
	while (!q.empty()) q.pop();

	answer = 0;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while (T--) {
		initialize();
		cin >> h >> w;
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				cin >> map[i][j];
			}
		}
		cin >> temp;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] == '0') break;
			keys[temp[i] - 'a'] += 1;
		}
		h += 2;
		w += 2;
		for (int i = 0; i < h; i++) {
			map[i][0] = '.';
			map[i][w - 1] = '.';
		}
		for (int i = 0; i < w; i++) {
			map[0][i] = '.';
			map[h - 1][i] = '.';
		}
		q.push({ 0,0 });
		visited[0][0] = true;

		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			
			for (int i = 0; i < 4; i++) {
				int nextx = x + dx[i];
				int nexty = y + dy[i];

				if (nextx < 0 || nexty < 0 || nextx >= h || nexty >= w) continue;
				char letter = map[nextx][nexty];
				if (letter == '*' || visited[nextx][nexty]) continue;

				visited[nextx][nexty] = true;
				if (letter == '.') {
					q.push({ nextx, nexty });
				}
				else if (letter == '$') {
					answer++;
					q.push({ nextx, nexty });
				}
				else if (letter >= 'a' && letter <= 'z') {
					int lidx = letter - 'a';
					keys[lidx] += 1;
					q.push({ nextx, nexty });
					for (int j = 0; j < doors[lidx].size(); j++) {
						int doorx = doors[lidx][j].first;
						int doory = doors[lidx][j].second;
						q.push({ doorx, doory });
					}
					doors[lidx].clear();
				}
				else if (letter >= 'A' && letter <= 'Z') {
					int lidx = letter - 'A';
					if (keys[lidx] == 0) { // 열쇠가 없는 방의 경우
						doors[lidx].push_back({ nextx, nexty });
					}
					else { // 열쇠가 있는 방의 경우
						q.push({ nextx, nexty });
					}
				}
			}
		}
		cout << answer << '\n';
	}
	
	return 0;
}
