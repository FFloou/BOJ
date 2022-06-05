/*

2022.06.05.
- 2294 동전 2: https://www.acmicpc.net/problem/2294
- 골드Ⅴ
- 다이나믹 프로그래밍

- 한 종류의 동전부터 모든 종류의 동전을 사용하여 1원에서 k원까지 만들 때, 사용되는 최소 동전 개수를 저장한다

*/
#include <iostream>

using namespace std;

const int MAX = 100000;
int n, k;
int dp[10001];
int coins[101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coins[i];
	}
	for (int i = 1; i <= k; i++) {
		dp[i] = MAX;
	}

	for (int i = 0; i < n; i++) {
		int cost = coins[i];
		for (int j = cost; j <= k; j++) {
			dp[j] = min(dp[j], dp[j - cost] + 1);
		}
	}
	if (dp[k] == MAX) cout << -1;
	else cout << dp[k];
	return 0;
}
