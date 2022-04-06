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
