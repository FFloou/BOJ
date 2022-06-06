/*

2022.06.06.
- 2293 동전 1: https://www.acmicpc.net/problem/2293
- 골드Ⅴ
- 다이나믹 프로그래밍

- n번째까지의 동전을 활용하여 k원을 만드는 방법인 아래 두 가지 경우의 수를 더한 값
   -> (n-1번째까지의 동전을 사용하여 k원 만들기)
   -> ((k-(n번째 동전의 값))원을 n번째까지의 동전을 사용하여 만들고 n번째 동전의 값을 각 방법에 더하는 경우)
- 위의 경우를 고려했을 때 k = 0 인 경우에도 0원을 만드는 경우는 한가지이기 때문에 dp[0] = 1으로 초기화

*/
#include <iostream>\

using namespace std;

int n, k;
int coins[101];
int dp[10001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coins[i];
	}
	
	dp[0] = 1;
	for (int i = 0; i < n; i++) {
		int cost = coins[i];
		for (int j = cost; j <= k; j++) {
			dp[j] += dp[j - cost];
		}
	}
	cout << dp[k];
	return 0;
}
