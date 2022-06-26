/*

2022.06.26.
- 14284 간선 이어가기 2: https://www.acmicpc.net/problem/14284
- 골드Ⅴ
- 그래프 이론, 데이크스트라

- 's와 t가 연결되는 시점에서 간선 추가를 멈춘다'는 조건이 있으므로 다익스트라를 완성하지 않고
   s에서 시작하여 처음으로 t노드를 만나는 시점에서 종료한다.
- 이 때의 최솟값을 구하기 때문에 노드 별로 방문하는 방법보다는 선택 가능한 간선 중 짧은 것을 선택하는 방식으로 진행한다.

*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
const int MAX = 1 << 30;
int n, m;
int a, b, c;
int s, t;

vector<pii> graph[5001];
priority_queue<pii, vector<pii>, greater<pii>> pq;
int dijkstra[5001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ c, b });
		graph[b].push_back({ c, a });
	}
	cin >> s >> t;

	for (int i = 0; i < 5001; i++) {
		dijkstra[i] = MAX;
	}
	dijkstra[s] = 0;
	pq.push({ 0, s });
	while (!pq.empty()) {
		int cost = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (cost > dijkstra[node]) continue;
		if (node == t) {
			cout << cost << '\n';
		}

		for (int i = 0; i < graph[node].size(); i++) {
			int next_node = graph[node][i].second;
			int next_cost = graph[node][i].first + cost;
			if (next_cost < dijkstra[next_node]) {
				dijkstra[next_node] = next_cost;
				pq.push({ next_cost, next_node });
			}
		}
	}
	return 0;
}
