
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
