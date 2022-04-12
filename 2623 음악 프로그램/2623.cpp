#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;
int tmp, from, to;
vector<int> graph[1001];
int connected[1001];
queue<int> q;
vector<int> sorted;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		cin >> from;
		for (int j = 1; j < tmp; j++) {
			cin >> to;
			graph[from].push_back(to);
			connected[to]++;
			from = to;
		}
	}
	for (int i = 1; i <= N; i++) {
		if (connected[i] == 0) q.push(i);
	}
	while (!q.empty() && sorted.size() < N) {
		int curr = q.front(); q.pop();
		sorted.push_back(curr);
		for (int i = 0; i < graph[curr].size(); i++) {
			int next = graph[curr][i];
			connected[next]--;
			if (connected[next] == 0) q.push(next);
		}
	}

	if (sorted.size() == N) {
		for (int i = 0; i < sorted.size(); i++) {
			cout << sorted[i] << "\n";
		}
	}
	else cout << 0;
	return 0;
}
