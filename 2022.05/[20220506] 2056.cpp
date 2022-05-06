/*
2022.05.06.
- 2056 작업: https://www.acmicpc.net/problem/2056
- 다이나믹 프로그래밍, 그래프 이론, 위상 정렬
- 골드Ⅳ

- 위상정렬 알고리즘 사용
- 모든 작업이 선행작업이 없을 때에 주의

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N;
int a, b;
int invertex[10001];
int wtime[10001];
int donetime[10001];
vector<int> graph[10001];
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> wtime[i]>>invertex[i];
		if (invertex[i] == 0) {
			q.push(i);
			donetime[i] = wtime[i];
		}
		for (int j = 0; j < invertex[i]; j++) {
			cin >> b;
			graph[b].push_back(i);
		}
	}

	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (int i = 0; i < graph[curr].size(); i++) {
			int next = graph[curr][i];
			invertex[next]--;
			donetime[next] = max(donetime[next], donetime[curr] + wtime[next]);
			if (invertex[next] == 0) q.push(next);
		}
	}
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		answer = max(answer, donetime[i]);
	}
	cout << answer;
	return 0;
}
