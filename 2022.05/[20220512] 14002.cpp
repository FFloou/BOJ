/*

2022.05.12.
- 14002 가장 긴 증가하는 부분 수열 4: https://www.acmicpc.net/problem/14002
- 골드Ⅳ
- 다이나믹 프로그래밍

- LIS 알고리즘으로 가장 긴 증가하는 부분수열의 길이를 찾는다.
- 각 숫자별로 부분수열에서 몇 번째 인덱스로 들어갈 수 있는지 저장한다.
- 배열의 뒤에서 부터 시작하여 인덱스에 맞게 부분 수열을 구성한다.

*/
#include <iostream>
using namespace std;

int lis[1001];
int lis_idx[1001];
int A[1001];
int N;
int idx;

int lower_bound(int idx, int num) {
	int s = 0;
	int e = idx;
	int mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (lis[mid] >= num) e = mid;
		else s = mid + 1;
	}
	return e;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	for (int i = 0; i < N; i++) {
		int loc = lower_bound(idx, A[i]);
		lis[loc] = A[i];
		lis_idx[i] = loc;
		if (loc == idx) idx++;
	}

	cout << idx << '\n';
	int tmp = idx-1;
	for (int i = N - 1; i >= 0; i--) {
		if (lis_idx[i] == tmp) {
			lis[tmp] = A[i];
			tmp--;
		}
	}
	for (int i = 0; i < idx; i++) {
		cout << lis[i] << ' ';
	}
	
	return 0;
}
