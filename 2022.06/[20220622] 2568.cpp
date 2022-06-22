/*

2022.06.22.
- 2568 전깃줄 - 2: https://www.acmicpc.net/problem/2568
- 플래티넘Ⅴ
- 가장 긴 증가하는 부분 수열: o(n log n)

- B의 위치를 기준으로 앞에서 부터 A의 위치로 LIS를 만든다.
- LIS를 이루는 번호를 역추적하면서 LIS에 속하지 않는다면 정답에 포함한다.
- 아예 전깃줄이 이어지지 않은 위치는 미리 확인하여 LIS나 역추적에서 제외한다.

*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int A, B;
int max_num;
int arr[500001];
int lis[500001];
int trace[500001];
int idx;
vector<int> answer;

int lower_bound(int idx, int num) {
	int s = 0;
	int e = idx;
	int mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (lis[mid] < num) s = mid + 1;
		else e = mid;
	}
	return e;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A >> B;
		arr[B] = A;
		max_num = max({ A, B, max_num });
	}
	for (int i = 1; i <= max_num; i++) {
		if (arr[i] == 0) {
			trace[i] = -1000;
			continue;
		}
		if (idx == 0 || lis[idx - 1] < arr[i]) {
			lis[idx] = arr[i];
			trace[i] = idx;
			idx++;
		}
		else {
			int loc = lower_bound(idx, arr[i]);
			lis[loc] = arr[i];
			trace[i] = loc;
		}
	}
	idx--;
	for (int i = max_num; i > 0; i--) {
		if (trace[i] < 0) continue;
		if (trace[i] == idx) idx--;
		else {
			answer.push_back(arr[i]);
		}
	}
	sort(answer.begin(), answer.end());

	cout << answer.size() << '\n';
	for (auto value : answer) {
		cout << value << '\n';
	}
	return 0;
}
