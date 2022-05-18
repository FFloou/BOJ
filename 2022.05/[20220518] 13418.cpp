/*

2022.05.18.
- 13418 학교 탐방하기: https://www.acmicpc.net/problem/13418
- 골드Ⅲ
- 그래프 이론, 최소 스패닝 트리

- 오르막길을 우선 선택하는 MST, 내리막길을 우선 선택하는 MST 두 개를 만들어 
    MST에 포함된 오르막길의 길이를 세어 피로도를 계산한다.
- 우선순위 큐를 사용하여 정렬하고, 어떤 길을 우선 선택할지에 따라 최소 힙, 최대 힙을 각각 사용한다.
- 선택한 edge의 수가 node - 1일 때 MST가 완성되었으므로 종료한다.
     ( 0 ~ N 까지 연결하므로 N개의 edge가 선택되면 종료한다.)
- 오르막 길인 경우에 0, 내리막 길인 경우에 1이 입력으로 주어지는 것에 주의한다.

*/
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, pair<int, int>> piii;

int N, M;
int A, B, C;
int uni[1010];

priority_queue<piii> min_pq;
priority_queue<piii, vector<piii>, greater<piii>> max_pq;


void initialize() {
	for (int i = 0; i <= N; i++) {
		uni[i] = i;
	}
}

int find_parent(int node) {
	if (uni[node] == node) return node;
	else return uni[node] = find_parent(uni[node]);
}

bool make_union(int a, int b) {
	int aparent = find_parent(a);
	int bparent = find_parent(b);

	if (aparent != bparent) {
		uni[bparent] = aparent;
		return true;
	}
	else return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M+1; i++) {
		cin >> A >> B >> C;
		max_pq.push({ C, {A, B} });
		min_pq.push({ C, {A, B} });
	}

	int max_road = 0;
	initialize();
	int cnt = 0;
	while (!max_pq.empty()) {
		int cost = max_pq.top().first;
		int from = max_pq.top().second.first;
		int to = max_pq.top().second.second;

		max_pq.pop();

		if (make_union(from, to)) {
			cnt++;
			if(cost == 0) max_road++;
		}
		if (cnt == N) break;
	}

	int min_road = 0;
	cnt = 0;
	initialize();
	while (!min_pq.empty()) {
		int cost = min_pq.top().first;
		int from = min_pq.top().second.first;
		int to = min_pq.top().second.second;

		min_pq.pop();

		if (make_union(from, to)) {
			cnt++;
			if(cost == 0) min_road++;
		}
		if (cnt == N) break;
	}

	cout << (max_road * max_road) - (min_road * min_road);
	return 0;
}
