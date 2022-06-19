/*

2022.06.19.
- 1240 노드사이의 거리: https://www.acmicpc.net/problem/1240
- 골드Ⅴ
- 그래프 이론, 그래프 탐색, 트리, 너비 우선 탐색, 깊이 우선 탐색

- bfs로 지나온 거리를 더하면서 입력받은 시작점에서 도착점까지 탐색을 진행한다.

  */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<pair<int, int>> graph[1001];
bool visited[1001];
int a, b, c;
queue<pair<int, int>> q;

void initialize() {
	while (!q.empty())q.pop();
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}
}

int bfs(int from, int to) {
	initialize();
	int answer = 0;

	q.push({ 0, from });
	visited[from] = true;
	while (!q.empty()) {
		int dist = q.front().first;
		int node = q.front().second;
		q.pop();

		if (node == to) {
			answer = dist;
			break;
		}
		for (int i = 0; i < graph[node].size(); i++) {
			pair<int, int> next = graph[node][i];
			if (visited[next.first]) continue;
			visited[next.first] = true;
			q.push({ next.second + dist, next.first });
		}
	}
	return answer;
}
	int main() {
		ios::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);

		cin >> N >> M;
		for (int i = 0; i < N - 1; i++) {
			cin >> a >> b >> c;
			graph[a].push_back({ b, c });
			graph[b].push_back({ a, c });
		}
		for (int i = 0; i < M; i++) {
			cin >> a >> b;
			cout << bfs(a, b)<<'\n';
		}
		
		return 0;
	}
