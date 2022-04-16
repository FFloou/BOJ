#include <iostream>
using namespace std;

int N, M;
int S, E;
int numbers[2001];
bool dp[2001][2001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
	}

	for (int cnt = 0; cnt < N; cnt++) { // i+1 == 숫자의 개수
		for (int sidx = 0; sidx + cnt < N; sidx++) { // j == 시작하는 index
			if (cnt == 0) { //1개의 숫자만 포함
				dp[sidx][sidx] = true;
			}
			else if (cnt == 1) {  // 2개의 숫자만 포함
				if (numbers[sidx] == numbers[sidx + 1]) {
					dp[sidx][sidx + 1] = true;
				}
			}
			else { // 3개 이상의 숫자가 포함될 때
				if (numbers[sidx] == numbers[sidx + cnt] && dp[sidx + 1][sidx + cnt - 1] == true) {
					dp[sidx][sidx + cnt] = true;
				}

			}
		}
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> S >> E;
		cout << dp[S - 1][E - 1] << '\n';
	}
	return 0;
}
