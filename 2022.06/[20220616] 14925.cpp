/*

2022.06.16.
- 14925 목장 건설하기: https://www.acmicpc.net/problem/14925
- 골드Ⅳ
- 다이나믹 프로그래밍

- 들판인 위치에서 만들 수 있는 가장 큰 정사각형의 크기를 계산하여 저장한다.
  -> 왼쪽 대각선 위, 왼쪽, 왼쪽 위의 값을 확인하여 가장 작은 값에 1을 더한다.

*/
#include <iostream>
#include <algorithm>

using namespace std;

int M, N;
int map[1001][1001];
int dp[1001][1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}

	int answer = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] != 0) continue;
			dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) +1;
			answer = max(answer, dp[i][j]);
		}
	}
	cout << answer;
	return 0;
}
