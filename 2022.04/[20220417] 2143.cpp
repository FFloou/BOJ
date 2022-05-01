/*

2022.04.17.
- 2143 두 배열의 합: https://www.acmicpc.net/problem/2143
- 이분 탐색, 누적 합
- GoldⅢ

- A의 모든 부 배열의 합, B의 모든 부 배열의 합을 계산한다.
- A에서 나올 수 있는 합과 B에서 나올 수 있는 합을 더하여 주어진 값 T가 되는 경우를 탐색한다.
- 합이 같은 값일 수 있으므로 lower bound와 upper bound를 찾아 해당 값이 몇 개인지 확인한다.
- 부 배열의 경우의 수는 int 범위를 넘어갈 수 있음에 유의한다.
- 찾는 value가 배열의 마지막에 있을 수 있기 때문에 upper bound를 찾는 함수에는 index의 최대값은 배열의 크기가된다.

*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T, n, m;
long long answer;
int A[1001];
int B[1001];
vector<int> a;
vector<int> b;

int lowerBound(int value, vector<int>& arr) {
	long long s = 0;
	long long e = arr.size();
	long long mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (arr[mid] >= value) e = mid;
		else s = mid + 1;
	}
	return s;
}

int upperBound(int value, vector<int>& arr) {
	long long s = 0;
	long long e = arr.size();
	long long mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (arr[mid] > value) e = mid;
		else s = mid + 1;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> B[i];
	}

	//A, B 배열의 모든 부배열의 합을 구하여 저장
	int num = 0;
	for (int i = 0; i < n; i++) {
		num = 0;
		for (int j = i; j < n; j++) {
			num += A[j];
			a.push_back(num);
		}
	}
	for (int i = 0; i < m; i++) {
		num = 0;
		for (int j = i; j < m; j++) {
			num += B[j];
			b.push_back(num);
		}
	}
	//b만 정렬 -> b에서만 binary search 사용
	sort(b.begin(), b.end());
	for (long long i = 0; i < a.size(); i++) {
		int find_num = T - a[i];
		// 중복된 숫자가 있을 수 있으므로 lowerbound와 upperbound로 개수 세기
		long long upper = upperBound(find_num, b);
		long long lower = lowerBound(find_num ,b);
		answer += (upper - lower);
	}
	cout << answer;
	return 0;
}
