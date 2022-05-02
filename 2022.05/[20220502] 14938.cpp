/*

2022.05.02.
- 14938 서강 그라운드: https://www.acmicpc.net/problem/14938
- 그래프 이론, 다익스트라, 플로이드-와샬
- 골드Ⅳ

- 정점의 개수가 100개로 플로이드-와샬 적용이 가능할 만큼 작다.
- 자기자신의 경우는 0으로 초기화하여 자기자신도 m보다 작으면 방문한다.

*/
#include <iostream>

using namespace std;

const int INF = 987654321;
int n, m, r;
int a, b, l;
int map[101][101];
int item[101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m >> r;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) map[i][j] = 0;
			else map[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		cin >> item[i];
	}

	for (int i = 0; i < r; i++) {
		cin >> a >> b >> l;
		map[a][b] = l;
		map[b][a] = l;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
			}
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		int sum = 0;
		for (int j = 1; j <= n; j++) {
			if (map[i][j] <= m) sum += item[j];
		}
		answer = max(answer, sum);
	}
	cout << answer;
	return 0;
}
