#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct node {
	int x;
	int y;
	double dist;
};
struct cmp { //dist가 작은 것이 우선순위를 가지도록 하는 비교 함수
	bool operator()(node a, node b) {
		return a.dist > b.dist;
	}
};
priority_queue<node, vector<node>, cmp> pq;
vector<pair<double, double>> v;
int n;
double x, y;
int uni[101];

void initialize() { //union 초기화
	for (int i = 1; i <= n; i++) {
		uni[i] = i;
	}
	return;
}

int find(int a) {
	if (uni[a] == a) return a;
	else return uni[a] = find(uni[a]); //거리 압축
}

bool make_union(int a, int b) {
	int aRoot = find(a);
	int bRoot = find(b);
	if (aRoot == bRoot) return false; //같은 집합인 경우 false 리턴
	else {//다른 집합인 경우 union하고 true 리턴
		uni[aRoot] = bRoot;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		v.push_back({ x, y });
	}

	for (int i = 0; i < n - 1; i++) { //모든 가능한 (p1, p2) 순서쌍 계산
		for (int j = i + 1; j < n; j++) {
			double dist = sqrt(pow(v[i].first - v[j].first, 2) + pow(v[i].second - v[j].second, 2));
			pq.push({ i, j, dist });
		}
	}
	int cnt = 0; //추가된 간선 개수
	double answer = 0;
	initialize();
	while (cnt < n - 1) { //간선이 n-1개 추가 될 때 까지 반복
		node curr = pq.top(); pq.pop();
		bool result = make_union(curr.x, curr.y); //union에 성공하면 true, 실패하면(같은 집합이면) false
		if (result == true) {
			answer += curr.dist;
			cnt++;
		}
	}
	//소수점 둘째자리까지 표현
	cout<<fixed;
	cout.precision(2);

	cout << answer;
	return 0;
}
