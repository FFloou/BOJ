/*

2022.04.27.
- 21610 마법사 상어와 비바라기: https://www.acmicpc.net/problem/21610
- 골드Ⅴ
- 구현, 시뮬레이션

- 좌표의 끝과 끝이 연결되어 있기 때문에 이동했을 때 가지는 좌표를 모듈러로 계산한다.
- 구름의 위치를 배열로 저장하여 이동, 비내리기, 물복사 등이 일어날 좌표를 찾는다.
- 구름이 다시 만들어질 때는 위치를 저장한 배열이 변경되기 때문에 cloud_exist에 구름이 존재했던 사실을 저장한다.

*/
#include <iostream>
#include <queue>
using namespace std;

int dr[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[9] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

int N, M;
int d, s;
int A[51][51];

int cloud_num = 0;
pair<int, int> cloud[3000];
bool cloud_exist[51][51];
pair<int, int> move_info[101];

void initialize() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cloud_exist[i][j] = false;
		}
	}
}

void move_cloud(int m) {
	int direction = move_info[m].first;
	int speed = move_info[m].second % N;

	for (int i = 0; i < cloud_num; i++) {
		int r = cloud[i].first;
		int c = cloud[i].second;

		int newr = (N + r + (speed * dr[direction])) % N;
		int newc = (N + c + (speed * dc[direction])) % N;

		if (newr == 0) newr = N;
		if (newc == 0) newc = N;

		cloud[i] = { newr,newc };
		cloud_exist[newr][newc] = true;
	}
	return;
}

void pour_rain() {
	for (int i = 0; i < cloud_num; i++) {
		int r = cloud[i].first;
		int c = cloud[i].second;

		A[r][c]++;
	}
	return;
}

void water_copy_bug() {
	for (int i = 0; i < cloud_num; i++) {
		int r = cloud[i].first;
		int c = cloud[i].second;

		for (int j = 2; j <= 8; j += 2) {
			int nextr = r + dr[j];
			int nextc = c + dc[j];

			if (nextr > 0 && nextr <= N && nextc > 0 && nextc <= N && A[nextr][nextc] > 0) {
				A[r][c]++;
			}
		}
	}
	return;
}

void make_cloud() {
	cloud_num = 0; //구름이 사라짐 (더 이상 구름 사용x)
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (A[r][c] < 2 || cloud_exist[r][c] == true) continue;
			cloud[cloud_num++] = { r, c };
			A[r][c] -= 2;
		}
	}
	return;
}

int total_water() {
	int total = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			total += A[i][j];
		}
	}
	return total;
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> d >> s;
		move_info[i] = { d, s };
	}

	cloud[cloud_num++] = { N, 1 };
	cloud[cloud_num++] = { N, 2 };
	cloud[cloud_num++] = { N - 1, 1 };
	cloud[cloud_num++] = { N - 1, 2 };

	for (int i = 1; i <= M; i++) {
		initialize();
		move_cloud(i);
		pour_rain();
		water_copy_bug();
		make_cloud();
	}

	cout << total_water();
	return 0;
}
