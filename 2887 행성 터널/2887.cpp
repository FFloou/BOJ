#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


struct node {
	int dist;
	int from;
	int to;
};
struct cmp {
	bool operator()(node A, node B) {
		return A.dist > B.dist;
	}
};
int N, a, b, c;
int uni[100001];
vector<pair<int, int>> x;
vector<pair<int, int>> y;
vector<pair<int, int>> z;
priority_queue<node,vector<node>, cmp> pq;

int find(int idx) {
	if (uni[idx] == idx) return idx;
	else return uni[idx] = find(uni[idx]);
}

bool make_union(int a, int b) {
	int aParent = find(a);
	int bParent = find(b);
	if (aParent == bParent) return false;
	else {
		uni[aParent] = bParent;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> a >> b >> c;
		//x, y, z 좌표와 행성 번호를 각각 벡터에 저장
		x.push_back({ a, i });
		y.push_back({ b, i });
		z.push_back({ c, i });
	}
	//정렬
	sort(x.begin(), x.end());
	sort(y.begin(),y.end());
	sort(z.begin(), z.end());

	for (int i = 0; i < N-1; i++) {
		//x, y, z 좌표 별로 인접한 행성끼리 우선순위 큐에 삽입
		pq.push({ abs(x[i].first - x[i + 1].first), x[i].second, x[i + 1].second });
		pq.push({ abs(y[i].first - y[i + 1].first), y[i].second, y[i + 1].second });
		pq.push({ abs(z[i].first - z[i + 1].first), z[i].second, z[i + 1].second });
	}

	for (int i = 1; i <= N; i++) {
		uni[i] = i;
	}
	int cnt = 0;
	int cost = 0;
	//크루스칼 MST
	while (!pq.empty() && cnt < N - 1) {
		node curr = pq.top(); pq.pop();
		if (make_union(curr.from, curr.to)) {
			cnt++;
			cost += curr.dist;
		}
	}
	cout << cost;
	return 0;
}
