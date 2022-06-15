/*

2022.06.15.
- 6497 전력난: https://www.acmicpc.net/problem/6497
- 골드Ⅳ
- 그래프 이론, 최소 스패닝 트리

- 크루스칼 알고리즘으로 최소 스패닝 트리를 만들고, 선택된 길의 길이를 더하여 저장한다.
   -> 길이가 작은 순으로 정렬하여 union-find를 통해 루프를 만들지 않는 새로운 길을 선택한다.
- 전체 비용(모든 길의 길이의 합)에서 선택된 길의 길이를 빼서 절약된 금액을 구한다.

*/
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, pair<int, int>> piii;

int m, n;
int x, y, z;
priority_queue<piii, vector<piii>, greater<piii>> pq;
int root[200001];

// union-find
int find(int node) {
	if (root[node] == node) return node;
	else return root[node] = find(root[node]);
}
bool make(int a, int b) {
	int aparent = find(a);
	int bparent = find(b);
	if (aparent == bparent) return false;
	else {
		root[aparent] = bparent;
		return true;
	}
}
void initialize(int e) {
	for (int i = 0; i < e; i++) {
		root[i] = i;
	}
	while (!pq.empty())pq.pop();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	while (true) {
		cin >> m >> n;
		if (m == 0 && n == 0) break;
		
		initialize(m);

		int sum = 0;
		for (int i = 0; i < n; i++) {
			cin >> x >> y >> z;
			pq.push({ z, {x, y} });
			sum += z;
		}
		
		int choose = 0;
		int cnt = 0;
		while (!pq.empty()) {
			if (cnt >= m - 1) break;
			int cost = pq.top().first;
			int from = pq.top().second.first;
			int to = pq.top().second.second;
			pq.pop();

			if (make(from, to)) {
				cnt++;
				choose += cost;
			}

		}
		cout << sum - choose<<'\n';
	}

	return 0;
}
