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
