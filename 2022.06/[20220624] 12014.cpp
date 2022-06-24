/*

2022.06.24.
- 12014 주식: https://www.acmicpc.net/problem/12014
- 골드Ⅱ
- 가장 긴 증가하는 부분 수열: o(n log n)

- 주어진 N개의 숫자로 만들 수 있는 LIS의 길이를 구한다.
- 그 길이가 K이상일 때 조건을 만족할 수 있고 그 미만일 때 만족할 수 없다.

*/

#include <iostream>

using namespace std;


int T;
int N, K;
int value;
int lis[10001];
int idx;

int lower_bound(int num) {
	int s = 0;
	int mid = 0;
	int e = idx;
	while (s < e) {
		mid = (s + e) / 2;
		if (num <= lis[mid]) e = mid;
		else s = mid + 1;
	}
	return e;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	int cnt = 1;
	while (cnt <= T) {
		cin >> N >> K;
		idx = 0;
		for (int i = 0; i < N; i++) {
			cin >> value;
			int loc = lower_bound(value);
			lis[loc] = value;
			if (loc == idx) idx++;
		}
		cout << "Case #" << cnt << '\n';
		if (idx >= K) cout << "1\n";
		else cout << "0\n";
		cnt++;
	}
	return 0;
}
