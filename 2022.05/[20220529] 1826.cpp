/*

2022.05.29.
- 1826 연료 채우기: https://www.acmicpc.net/problem/1826
- 골드Ⅲ
- 자료 구조, 그리디 알고리즘, 정렬, 우선순위 큐

- 현재 연료로 갈 수 있는 거리의 주유소를 우선순위 큐에 모두 추가하여 얻을 수 있는 연료가 큰 순서로 정렬한다.
- 우선순위 큐에서 가장 연료를 많이 충전할 수 있는 주유소를 하나 빼내고 현재 연료에 충전 할 수 있는 연료를 더한다.
- 위 과정을 목적지까지 도착 할 수 있는 연료를 얻거나 모든 주유소를 방문할 때까지 반복한다.

*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, L, P;
int a, b;
// <거리, 연료>
vector<pair<int, int>> v;
// <연료, 거리>
priority_queue<pair<int, int>> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		v.push_back({ a, b });
	}
	cin >> L >> P;

	sort(v.begin(), v.end());
	int midx = 0;
	int answer = 0;

	while (true) {
		while (midx < v.size() && v[midx].first <= P) {
			pq.push({v[midx].second, v[midx].first});
			midx++;
		}
		if (P >= L) {
			break;
		}
		if (pq.empty()) {
			answer = -1;
			break;
		}
		pair<int, int> curr = pq.top(); pq.pop();
		P += curr.first;
		answer++;
	}
	cout << answer;
	
	return 0;
}
