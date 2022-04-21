#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string wheel[5];
int K;
int move_dir[5];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 1; i <= 4; i++) {
		cin >> wheel[i];
	}
	cin >> K;
	int wnum = 0;
	int dir = 0;
	while (K--) {
		cin >> wnum >> dir;

		for (int i = 0; i < 5; i++) move_dir[i] = 0;

		if (wnum == 1) { // 1 2 3 4
			move_dir[1] = dir;
			if (wheel[1][2] != wheel[2][6] && move_dir[1] != 0) move_dir[2] = move_dir[1] * -1;
			if (wheel[2][2] != wheel[3][6] && move_dir[2] != 0) move_dir[3] = move_dir[2] * -1;
			if (wheel[3][2] != wheel[4][6] && move_dir[3] != 0) move_dir[4] = move_dir[3] * -1;
		}
		else if (wnum == 2) { // 2 (1 3) 4
			move_dir[2] = dir;
			if (wheel[1][2] != wheel[2][6] && move_dir[2] != 0) move_dir[1] = move_dir[2] * -1;
			if (wheel[2][2] != wheel[3][6] && move_dir[2] != 0) move_dir[3] = move_dir[2] * -1;
			if (wheel[3][2] != wheel[4][6] && move_dir[3] != 0) move_dir[4] = move_dir[3] * -1;
		}
		else if (wnum == 3) { // 3 (4 2) 1
			move_dir[3] = dir;
			if (wheel[3][2] != wheel[4][6] && move_dir[3] != 0) move_dir[4] = move_dir[3] * -1;
			if (wheel[2][2] != wheel[3][6] && move_dir[3] != 0) move_dir[2] = move_dir[3] * -1;
			if (wheel[1][2] != wheel[2][6] && move_dir[2] != 0) move_dir[1] = move_dir[2] * -1;
		}
		else { // wnum == 4   4 3 2 1
			move_dir[4] = dir;
			if (wheel[3][2] != wheel[4][6] && move_dir[4] != 0) move_dir[3] = move_dir[4] * -1;
			if (wheel[2][2] != wheel[3][6] && move_dir[3] != 0) move_dir[2] = move_dir[3] * -1;
			if (wheel[1][2] != wheel[2][6] && move_dir[2] != 0) move_dir[1] = move_dir[2] * -1;
		}

		for (int i = 1; i <= 4; i++) { // 톱니바퀴 회전
			if (move_dir[i] == 0) continue; // 회전하지 않는 경우
			if (move_dir[i] == 1) { // 시계 방향 회전
				char temp = wheel[i][7];
				wheel[i] = temp + wheel[i].substr(0, 7);
			}
			else { // 반시계 방향 회전
				char temp = wheel[i][0];
				wheel[i] = wheel[i].substr(1, 7) + temp;
			}
			
		}

	}

	int answer = 0;
	int num = 1;
	for (int i = 1; i <= 4; i++) {
		if (wheel[i][0] == '1') answer += num;
		num *= 2;
	}

	cout << answer;
	return 0;
}
