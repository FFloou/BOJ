/*

2022.06.21.
- 1833 고속철도 설계하기: https://www.acmicpc.net/problem/1833
- 골드Ⅲ
- 그래프 이론, 최소 스패닝 트리

- 크루스칼 알고리즘을 사용하여 최소 스패닝 트리를 만든다.
  -> 이미 연결된 노드는 입력 값을 순회하면서 같은 집합으로 묶어둔다.
- 이미 연결된 노드들의 형태가 항상 트리가 아니기 때문에 선택한 간선의 수를 종료 조건으로 할 수 없다.
  -> 모든 간선을 살펴보면서 간선에 연결된 두 노드가 같은 집합으로 묶여 있는지 확인하여 선택

*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, pair<int, int>> piii;
int N;
int graph[201][210];
int root[201];
vector<pair<int, int>> answer;
priority_queue<piii, vector<piii>, greater<piii>> pq;


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
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> graph[i][j];
		}
	}

	for (int i = 0; i < 201; i++) {
		root[i] = i;
	}

	int cost = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = i+1; j <= N; j++) {
			if (graph[i][j] < 0) {
				make(i, j);
				cost -= graph[i][j];
			}
			else {
				pq.push({ graph[i][j], {i, j} });
			}
		}
	}

	int M = 0;
	while (!pq.empty()) {
		piii curr = pq.top();
		pq.pop();
		if (make(curr.second.first, curr.second.second)) {
			cost += curr.first;
			answer.push_back(curr.second);
			M++;
		}
	}

	cout << cost << ' ' << M << '\n';
	for (int i = 0; i < M; i++) {
		cout << answer[i].first << ' ' << answer[i].second << '\n';
	}
	return 0;
}
