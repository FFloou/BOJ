/*

2022.06.20.
- 2550 전구: https://www.acmicpc.net/problem/2550
- 골드Ⅲ
- 다이나믹 프로그래밍, 가장 긴 증가하는 부분 수열: o(nlogn)

- 전구 순서를 기준으로 했을 때, 왼쪽의 연결된 스위치의 순서가 증가하는 순서대로 전구를 선택한다.
- LIS 알고리즘으로 가장 긴 부분 수열을 만들고, 그 때 자신의 위치를 저장한다.
   -> 선택된 전구를 알아낼 때, 저장된 위치를 뒤에서 부터 훑어보면서 찾아간다.

*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int l[10001];
int r[10001];
int LIS[10001];
int trace[10001];
vector<int> answer;
int idx, t;


int lower_bound(int num, int idx) {
	int s = 0;
	int e = idx;
	int mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (LIS[mid] < num) {
			s = mid + 1;
		}
		else { // mid>=num
			e = mid;
		}
	}
	return e;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> l[i];
	}
	for (int i = 1; i <= N; i++) {
		cin >> t;
		r[t] = i;
	}
	for (int i = 1; i <= N; i++) {
		int num = r[l[i]];
		int loc = lower_bound(num, idx);
		trace[i] = loc;
		LIS[loc] = num;
		if (loc == idx) idx++;
	}
	cout << idx << '\n';
	int temp = idx - 1;
	for (int i = N; i > 0; i--) {
		if (trace[i] == temp) {
			answer.push_back(l[i]);
			temp--;
		}
	}
	for (int i = 0; i < idx; i++) {
		cout << answer[i] << ' ';
	}
	return 0;
}
