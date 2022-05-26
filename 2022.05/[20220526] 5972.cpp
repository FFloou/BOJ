/*

2022.05.26.
- 5972 택배 배송: https://www.acmicpc.net/problem/5972
- 골드Ⅴ
- 그래프 이론, 다익스트라

- 각 길의 소의 개수를 가중치로 저장하여 다익스트라를 통해 1에서 N까지 
   최소의 소를 만나는 경로(가중치가 가장 작은 경로)를 찾는다.

*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
const int MAX = 2000000000;
int N, M;
int A, B, C;

vector<pii> graph[50001];
priority_queue<pii, vector<pii>, greater<pii>>q;
int cost[50001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		graph[A].push_back({ C, B });
		graph[B].push_back({ C, A });
	}
	for (int i = 1; i < 50001; i++) {
		cost[i] = MAX;
	}

	cost[1] = 0;
	q.push({ 0, 1 });

	while (!q.empty()) {
		pii curr = q.top();
		q.pop();
		for (int i = 0; i < graph[curr.second].size(); i++) {
			pii next = graph[curr.second][i];
			if (next.first + curr.first < cost[next.second]) {
				cost[next.second] = next.first + curr.first;
				q.push({ cost[next.second], next.second});
			}
		}
	}
	cout << cost[N];
	return 0;
}
