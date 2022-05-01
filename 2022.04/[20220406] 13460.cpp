/*

2022.04.06.
- 13460 구슬 탈출 2: https://www.acmicpc.net/problem/13460
- 구현, 그래프 이론, 그래프 탐색, 너비 우선 탐색, 시뮬레이션
- GoldI

- 보드를 왼쪽, 오른쪽, 위쪽, 아래쪽으로 기울이는 네 가지 동작을 bfs로 탐색
- 한 칸씩 이동하는 것이 아니므로 반복문을 통해 더 이상 이동할 수 없을 때 까지 이동
- 두 색상의 구슬이 함께 움직이므로 구슬의 위치에 따라 먼저 움직일 구슬을 결정
- 두 구슬의 위치가 모두 같아야만 같은 경우기 때문에 방문 여부는 사차원 배열로 확인
- 제약 조건에 유의
  - 이동은 10회까지만 가능
  - 파란 구슬만 구멍에 빠져도 실패
  - 파란 구슬과 빨간 구슬에 동시에 빠져도 실패

*/
#include <iostream>
#include <queue>

using namespace std;

struct pos {
	int x;
	int y;
};
int N, M;
bool visited[11][11][11][11];
char board[11][11];
pair<int, int> hole;
pos blue, red;
//pair<blue, red>
queue<pair<pos, pos>> q;


pair<pos, pos> move(pos f, pos s, int dir_x, int dir_y, bool rev) {
	while (true) {
		if (board[f.x + dir_x][f.y + dir_y] == 'O') {
			f.x += dir_x;
			f.y += dir_y;
			break;
		}
		else if (board[f.x + dir_x][f.y + dir_y] == '.') {
			f.x += dir_x;
			f.y += dir_y;
		}
		else break;
	}

	while (true) {
		if (board[s.x + dir_x][s.y + dir_y] == 'O') {
			s.x += dir_x;
			s.y += dir_y;
			break;
		}
		else if (board[s.x + dir_x][s.y + dir_y] == '.') {
			if (s.x + dir_x == f.x && s.y + dir_y == f.y) break;

			s.x += dir_x;
			s.y += dir_y;
		}
		else break;
	}
	if (rev == true) return { s, f };
	else return { f,s };
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];

			if (board[i][j] == 'B') {
				blue = { i,j };
				board[i][j] = '.';
			}
			else if (board[i][j] == 'R') {
				red = { i,j };
				board[i][j] = '.';
			}
			else if (board[i][j] == 'O') {
				hole = { i, j };
			}
		}
	}

	q.push({ blue, red });
	visited[blue.x][blue.y][red.x][red.y] = true;

	for (int i = 0; i <= 10; i++) {
		int qsize = q.size();
		for (int j = 0; j < qsize; j++) {
			pair<pos, pos> curr = q.front(); q.pop();
			pos blue = curr.first;
			pos red = curr.second;

			if (blue.x == hole.first && blue.y == hole.second) continue; // 파란색만 구멍에 빠진 경우 종료
			else if (red.x == hole.first && red.y == hole.second) { //구멍에 빠진 경우
				cout << i;
				return 0; //종료
			}

			//위, 아래
			if (red.y == blue.y && red.x < blue.x) {
				pair<pos, pos> r1 = move(red, blue, -1, 0, true);
				if (visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] == false) {
					q.push(r1);
					visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] = true;
				}
				pair<pos, pos> r2 = move(blue, red, 1, 0, false);
				if (visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] == false) {
					q.push(r2); 
					visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] = true;
				}

			}
			else {
				pair<pos, pos> r1 = move(blue, red, -1, 0, false);
				if (visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] == false) {
					q.push(r1);
					visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] = true;
				}
				pair<pos, pos> r2 = move(red, blue, 1, 0, true);
				if (visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] == false) {
					q.push(r2);
					visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] = true;
				}

			}
			//왼쪽, 오른쪽
			if (red.x == blue.x && red.y < blue.y) {
				pair<pos, pos> r1 = move(red, blue, 0, -1, true);
				if (visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] == false) {
					q.push(r1);
					visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] = true;
				}
				pair<pos, pos> r2 = move(blue, red, 0, 1, false);
				if (visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] == false) {
					q.push(r2);
					visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] = true;
				}
			}
			else {
				pair<pos, pos> r1 = move(blue, red, 0, -1, false);
				if (visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] == false) {
					q.push(r1);
					visited[r1.first.x][r1.first.y][r1.second.x][r1.second.y] = true;
				}
				pair<pos, pos> r2 = move(red, blue, 0, 1, true);
				if (visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] == false) {
					q.push(r2);
					visited[r2.first.x][r2.first.y][r2.second.x][r2.second.y] = true;
				}
			}
		}
	}

	cout << -1;
	return 0;

}
