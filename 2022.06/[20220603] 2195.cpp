/*

2022.06.03.
- 2195 문자열 복사: https://www.acmicpc.net/problem/2195
- 골드Ⅴ
- 문자열, 그리디 알고리즘

- LCS(최장 공통 문자열)를 통해 P의 각 위치에서 가장 긴 연속된 공통 문자열을 계산한다.
- P의 가장 끝에서 시작하여 공통 문자열만큼 제거하며 앞으로 진행한다.
  -> P의 가장 끝 열에 저장된 가장 큰 값 만큼 idx를 앞으로 당긴다. 이를 idx가 0에 도착할 때까지 반복한다.

*/
#include <iostream>
#include <string>

using namespace std;

string s;
string p;

int dp[1001][1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> s;
	cin >> p;

	for (int i = 1; i <= s.length(); i++) {
		for (int j = 1; j <= p.length(); j++) {
			if (s[i - 1] == p[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
		}
	}
	
	int idx = p.length();
	int answer = 0;

	while (idx > 0) {
		answer++;
		int maximum = 0;
		int maxidx = -1;
		
		for (int i = 1; i <= s.length(); i++) {
			if (dp[i][idx] > maximum) {
				maximum = dp[i][idx];
				maxidx = i;
			}
		}
		idx = idx - maximum;
	}
	cout << answer;
	return 0;
}
