/*

2022.05.30.
- 2212 센서: https://www.acmicpc.net/problem/2212
- 골드Ⅴ
- 그리디 알고리즘, 정렬

- K개의 묶음으로 끊었을 때 묶음의 최소값과 최대값의 차이의 합의 최소를 구하는 문제
- 정렬을 사용하여 센서 간 거리를 긴 순서대로 정렬하기
   -> K-1개의 연결을 끊어 K개의 덩어리로 만들어 K개의 집중국 세우기
- N >= K가 보장되지 않았기 때문에 K가 더 큰 경우의 Segfault 방지 필요

*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int pos;
vector<int> v;
vector<int> dist;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> pos;
		v.push_back(pos);
	}
	sort(v.begin(), v.end());

	// 센서 간 거리를 저장하여 거리가 긴 순서대로 정렬
	int sum = 0;
	for (int i = 0; i < N - 1; i++) {
		dist.push_back(v[i+1] - v[i]);
		sum += v[i+1] - v[i];
	}
	sort(dist.rbegin(), dist.rend());

	// 거리가 긴 순서대로 끊기. K개의 집중국 => K개의 묶음이므로 K-1개의 연결 제거
	for (int i = 0; i < K-1; i++) {
		// N보다 K가 큰 경우(Out Of Bound 예방)
		if (i >= dist.size()) break;
		sum -= dist[i];
	}
	cout << sum;
	return 0;
}
