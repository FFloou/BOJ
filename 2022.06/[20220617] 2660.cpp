/*

2022.06.17.
- 2660 회장뽑기: https://www.acmicpc.net/problem/2660
- 골드Ⅴ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 플로이드-워셜

- 각 회원의 점수는 각 간선의 길이를 1로하였을 때 다른 노드까지의 길이 중 가장 긴 것
   -> 플로이드-워셜로 한 회원과 모든 회원까지의 길이를 계산하여 가장 큰 값을 찾는다

*/
#include <iostream>

using namespace std;

int n;
int a, b;
int graph[51][51];
int score[51];
int answer[51];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 51; i++) {
		for (int j = 0; j < 51; j++) {
			if (i == j) graph[i][j] = 0;
			else graph[i][j] = 10000;
		}
	}
	cin >> n;
	while (true) {
		cin >> a >> b;
		if (a == -1 && b == -1) break;
		graph[a][b] = 1;
		graph[b][a] = 1;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
	int minimum = 10000;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int s = 0;
		for (int j = 1; j <= n; j++) {
			s = max(s, graph[i][j]);
		}
		score[i] = s;
		if (s < minimum) {
			minimum = s;
			cnt = 1;
		}
		else if (s == minimum) {
			cnt++;
		}
	}
	cout << minimum << ' ' << cnt<<'\n';
	for (int i = 1; i <= n; i++) {
		if (score[i] == minimum) cout << i << ' ';
	}
	return 0;
}
