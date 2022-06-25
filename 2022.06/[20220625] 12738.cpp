/*

2022.06.25.
- 12738 가장 긴 증가하는 부분 수열 3: https://www.acmicpc.net/problem/12738
- 골드Ⅱ
- 이분 탐색, 가장 긴 증가하는 부분 수열: o(n log n)

*/

#include <iostream>
#include <vector>

using namespace std;

int N;
int input;

vector<int> A;
vector<int> lis;

int lower_bound(int num) {
	int s = 0;
	int mid = 0;
	int e = lis.size();
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
		cin >> input;
		A.push_back(input);
	}
	for (int i = 0; i < N; i++) {
		int num = A[i];
		int loc = lower_bound(num);
		if (loc == lis.size()) lis.push_back(num);
		else lis[loc] = num;
	}
	cout << lis.size();
	return 0;
}
