/*

2022.04.16.
- 10942 팰린드롬?: https://www.acmicpc.net/problem/10942
- 다이나믹 프로그래밍
- GoldⅢ

- 이차원 배열에 시작점(S)과 끝점(E)에 따라 팰린드롬 여부를 저장한다.
- 선택한 숫자의 길이에 따라 다음과 같이 판단한다.
    - 1개의 숫자만 선택했을 때: 항상 팰린드롬이다.
    - 2개의 숫자만 선택했을 때: 선택한 두 숫자가 같으면 팰린드롬이다.
    - 3개 이상의 숫자를 선택했을 때: 양쪽 가장 끝 부분의 두 숫자가 같고, 양쪽 끝 두 숫자를 제외한 
    나머지가 팰린드롬일 때 팰린드롬이다.
- 선택하는 숫자의 개수가 1개에서 점점 커지도록 하여 3개 이상의 숫자를 선택하였을 때 사이의 수들이 
  팰린드롬인지 확인 할 수 있도록 한다.

*/

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
