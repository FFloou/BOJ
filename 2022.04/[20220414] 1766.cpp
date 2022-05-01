/*

2022.04.14.
- 1766 문제집: https://www.acmicpc.net/problem/1766
- 그래프 이론, 자료 구조, 우선순위 큐, 위상 정렬
- GoldⅡ

- 위상 정렬과 우선순위 큐를 사용한다.
- 위상 정렬로 먼저 풀어야하는 문제를 먼저 처리하여 우선순위 큐에 넣는다.
- 우선순위 큐에서 난이도가 낮은 문제가 우선순위를 가지도록 하여 풀 수 있는 문제 중에 난이도가 낮은 문제부터 풀도록 한다.

*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M;
int A, B;
int invertex[32001];
vector<int> graph[32001];
//큐에 삽입된 int 중 작은 값이 우선순위를 가지도록 한다.
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		graph[A].push_back(B);
		invertex[B]++;
	}
	for (int i = 1; i <= N; i++) {
		if (invertex[i] == 0) pq.push(i);
	}
	int solved = 0;
	while (!pq.empty() && solved < N) {
		int curr = pq.top(); pq.pop();
		solved++;
		cout << curr << ' ';
		for (int i = 0; i < graph[curr].size(); i++) {
			int next = graph[curr][i];
			invertex[next]--;
			if (invertex[next] == 0) pq.push(next);
		}
		
	}
	return 0;
}
