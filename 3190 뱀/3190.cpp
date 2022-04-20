
#include <iostream>
#include <queue>
using namespace std;

int N, K, L;
int x, y, t;
char d;
// 0: 빈칸 1:뱀 2: 사과
int map[110][110];
queue<pair<int, char>>q;
deque<pair<int, int>> snake;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> x >> y;
		map[x][y] = 2;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> t >> d;
		q.push({ t, d });
	}

	int time = 0;
	char direction = 'R';
	bool crush = false;
	//꼬리가 front에 머리가 back에 위치
	snake.push_back({ 1, 1 });
	map[1][1] = 1;
	while (true) {
		//뱀 움직이기
		pair<int, int> head = snake.back();
		//머리 이동
		if (direction == 'R') snake.push_back({ head.first, head.second + 1 });
		else if (direction == 'L') snake.push_back({ head.first, head.second - 1 });
		else if (direction == 'U') snake.push_back({ head.first - 1, head.second });
		else snake.push_back({ head.first + 1, head.second });

		//이동한 위치로 머리 업데이트
		head = snake.back();
		// 자기자신과 충돌한 경우
		if (map[head.first][head.second] == 1) crush = true;
		//사과 확인 && 꼬리 이동
		if (map[head.first][head.second] != 2) {
			map[snake.front().first][snake.front().second] = 0;
			snake.pop_front();
		}
		map[head.first][head.second] = 1;
		//시간 증가
		time++;
		//방향 전환
		if (!q.empty() && q.front().first == time) {
			char change = q.front().second; q.pop();
			if (direction == 'R') {
				if (change == 'L') direction = 'U';
				else direction = 'D';
			}
			else if (direction == 'L') {
				if (change == 'L') direction = 'D';
				else direction = 'U';
			}
			else if (direction == 'U') {
				if (change == 'L') direction = 'L';
				else direction = 'R';
			}
			else {
				if (change == 'L') direction = 'R';
				else direction = 'L';
			}
		}

		//게임 종료 판단
		if (head.first <= 0 || head.first > N || head.second <= 0 || head.second > N || crush==true) break;

	}
	cout << time;
	return 0;
}
