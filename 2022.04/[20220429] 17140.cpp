/*

2022.04.29
- 17140 이차원 배열과 연산: https://www.acmicpc.net/problem/17140
- 구현, 정렬, 시뮬레이션
- 골드Ⅳ

- 배열을 사용해서 각 숫자의 등장 횟수를 센다.
- 우선순위큐를 활용하여 정해진 조건대로 숫자를 정렬한다.
- 배열이 최대 100*100이기 때문에 R연산과 C연산을 할 때 값이 있는 부분을 채우고
  나머지는 전부 0으로 채워 길이를 맞춘다.
- R연산과 C연산을 하는 중에 가장 길었던 값을 저장하여 새로운 행/열 개수로 사용한다.

*/
#include <iostream>
#include <queue>
using namespace std;

int A[101][101];
int num_arr[101];
int r, c, k;
int t;
int row, column;

// <count, num>
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void initialize() {
	for (int i = 0; i < 101; i++) {
		num_arr[i] = 0;
	}
	while (!pq.empty()) pq.pop();
	return;
}

void R_operation() {
	int maximum = 0;
	for (int i = 1; i <= row; i++) {
		initialize();
		for (int j = 1; j <= column; j++) {
			num_arr[A[i][j]]++;
		}
		for (int j = 1; j <= 100; j++) {
			if (num_arr[j] == 0) continue;
			pq.push({ num_arr[j], j });
		}
		int j = 1;
		while (!pq.empty()) {
			pair<int, int> curr = pq.top();
			pq.pop();
			if (j > 100) continue;
			A[i][j++] = curr.second;
			A[i][j++] = curr.first;
			maximum = max(maximum, j-1);
		}
		for (; j < 101; j++) {
			A[i][j] = 0;
		}
	}
	column = maximum;
	return;
}
void C_operation() {
	int maximum = 0;
	for (int j = 1; j <= column; j++) {
		initialize();
		for (int i = 1; i <= row; i++) {
			num_arr[A[i][j]]++;
		}
		for (int i = 1; i <= 100; i++) {
			if (num_arr[i] == 0) continue;
			pq.push({ num_arr[i], i });
		}
		int i = 1;
		while (!pq.empty()) {
			pair<int, int> curr = pq.top();
			pq.pop();
			if (i > 100) continue;
			A[i++][j] = curr.second;
			A[i++][j] = curr.first; 
			maximum = max(maximum, i - 1);
		}
		for (; i < 101; i++) {
			A[i][j] = 0;
		}
	}
	row = maximum;
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> A[i][j];
		}
	}
	row = 3;
	column = 3;

	while (true) {
		if (A[r][c] == k) break;
		if (t > 100) {
			t = -1;
			break;
		}

		if (row >= column) R_operation();
		else C_operation();

		t++;
	}
	cout << t;
	return 0;
}
