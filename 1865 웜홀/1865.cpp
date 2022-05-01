#include <iostream>
#include <vector>

using namespace std;

const int INF = 1 << 30;
struct info {
	int from;
	int to;
	int dist;
};
int TC;
int N, M, W;
int S, E, T;

vector<info> road;
int bellman[501];

void initialize() {
	road.clear();
	for (int i = 0; i < 501; i++) {
		bellman[i] = INF;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> TC;

	while (TC--) {
		initialize();
		cin >> N >> M >> W;
		for (int i = 0; i < M; i++) {
			cin >> S >> E >> T;
			road.push_back({ S, E, T });
			road.push_back({ E, S, T });
		}
		for (int i = 0; i < W; i++) {
			cin >> S >> E >> T;
			road.push_back({ S, E, -T });
		}
		bellman[1] = 0;
		for (int i = 0; i < N - 1; i++) { // 벨만포드
			for (int i = 0; i < road.size(); i++) {
				info curr = road[i];
				bellman[curr.to] = min(bellman[curr.to], bellman[curr.from] + curr.dist);
			}
		}
		bool cycle = false;
		for (int i = 0; i < road.size(); i++) { //사이클 체크
			info curr = road[i];
			if (bellman[curr.to] > bellman[curr.from] + curr.dist) {
				cycle = true;
				break;
			}
		}

		if (cycle) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
