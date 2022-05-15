/*

2022.05.15.
- 3745 오름세: https://www.acmicpc.net/problem/3745
- 골드Ⅱ
- 이분 탐색, 가장 긴 증가하는 부분 수열: o(nlogn)

- LIS 알고리즘을 사용한다.(LIS = lower bound의 위치를 찾아 삽입하여 만든 배열)
- 정해진 입력 개수가 없으므로 while문의 조건에 cin >> n을 넣어 사용한다.
    -> EOF가 입력되면(잘못된 값이 입력되면) false를 리턴한다.

*/
#include <iostream>

using namespace std;

int lis[100001];
int ptr;

int in, lis_idx;
int n;

int lower_bound(int idx, int num) {
	int s = 0;
	int e = idx;
	while (s < e) {
		int mid = (s + e) / 2;
		if (lis[mid] >= num) e = mid;
		else s = mid+1;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (cin >> n) {
		ptr = 0;
		for (int i = 0; i < n; i++) {
			cin >> in;
			lis_idx = lower_bound(ptr, in);
			lis[lis_idx] = in;
			if (ptr == lis_idx) ptr++;
		}
		cout << ptr << '\n';
	}
	return 0;
}
