/*

2022.06.13.
- 1956 운동: https://www.acmicpc.net/problem/1956
- 골드Ⅳ
- 그래프 이론, 플로이드-워셜

- 각 도시에서 다른 도시로 갈 수 있는 최소 경로를 플로이드-워셜 알고리즘으로 구한다.
- a->b, b->a 로 이동 가능한지 확인하고, 가능하다면 그 최소값을 구한다.
- 모든 도시를 방문하고 돌아오는 경우가 아니라 그저 시작점으로 다시 돌아오는 경우임에 주의한다.

*/
#include <iostream>

using namespace std;

const int INF = 2000000000;
int V, E;
int a, b, c;
int graph[401][401];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for (int i = 0; i < 401; i++) {
		for (int j = 0; j < 401; j++) {
			graph[i][j] = INF;
		}
	}
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		graph[a][b] = c;
	}

	for (int k = 1; k <= V; k++) {
		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {
				if (graph[i][k] == INF || graph[k][j] == INF) continue;
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
	int answer = -1;
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			if (graph[i][j] == INF || graph[j][i] == INF) continue;
			if (answer == -1) answer = graph[i][j] + graph[j][i];
			else answer = min(answer, graph[i][j] + graph[j][i]);
		}
	}

	cout << answer;
	return 0;
}
