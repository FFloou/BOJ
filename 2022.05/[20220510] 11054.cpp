/*

2022.05.10.
- 11054 가장 긴 바이토닉 부분 수열: https://www.acmicpc.net/problem/11054
- 다이나믹 프로그래밍
- 골드Ⅲ

- 배열의 앞쪽부터 증가하는 부분수열을 만든다.
- 배열의 뒤쪽부터 증가하는 부분수열을 만든다.
- 같은 위치 까지의 두 부분 수열을 연결하면 바이토닉 수열이 된다.
- 각 위치 별로 두 부분수열의 길이를 구해서 더한 값이 가장 큰 값이 가장 긴 바이토닉 수열이다.

*/
#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[1001];
int idx;
int lis[1001];
int dp[1001];

int lower_bound(int idx, int num) {
	int s = 0;
	int e = idx;
	while (s < e) {
		int mid = (s + e) / 2;
		if (lis[mid] >= num) {
			e = mid;
		}
		else s = mid + 1;
	}
	return e;
}

int make_lis(int idx, int num) { //LIS를 만드는 함수
	int pos = lower_bound(idx, num);
	lis[pos] = num;
	if (pos == idx) idx++;
	return idx;  // LIS의 길이 리턴
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	idx = 0;
	for (int i = 0; i < N; i++) { // 각 위치에서 만들 수 있는 LIS의 길이 dp에 저장
		idx = make_lis(idx, arr[i]);
		dp[i] = idx;
	}

	//초기화
	idx = 0;
	for (int i = 0; i < idx; i++) {
		lis[i] = 0;
	}

	//뒤에서 부터 LIS 구성 -> 앞에서 부터 보면 감소하는 부분 수열
	// 각 위치에서 증가수열과 감소수열이 만났을 때 부분수열과 감소수열의 합의 최대값 찾기 
	int answer = 0;
	for (int i = (N - 1); i >= 0; i--) { 
		idx = make_lis(idx, arr[i]);
		answer = max(answer, dp[i] + idx - 1);  // arr[i]가 두 번 더해지기 때문에 -1
	}
	cout << answer;

	return 0;
}
