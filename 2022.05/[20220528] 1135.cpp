/*

2022.05.28.
- 1135 뉴스 전하기: https://www.acmicpc.net/problem/1135
- 골드Ⅱ
- 다이나믹 프로그래밍, 그리디 알고리즘, 정렬, 트리, 트리에서의 다이나믹 프로그래밍

- dfs를 사용하여 현재 노드에서 전파를 시작했을 때 leaf node까지 전파가 완료될 때까지 걸리는 최대 시간을 구한다.
- 현재 노드의 자식노드들의 전파 시간을 구하여 정렬 한 후, 가장 오래걸리는 것부터 전파한다.
    -> 가장 오래 걸리는 subtree부터 걸리는 시간에 +0, +1, +2, ...을 하여 구한다.
- 자식노드들에게 전파하였을 때 걸리는 최대 시간을 구하고, 본인에게 전파되는 시간 1을 더하여 리턴한다.

*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int tmp;
vector<int> tree[51];

// 현재 노드에서 전파를 시작하여 완료할 때까지 걸리는 시간 구하기
int dfs(int s) {
	// leaf node인 경우 1 리턴
	if (tree[s].size() == 0) {
		return 1;
	}
	vector<int> v;
	// 각 child에 대해 dfs 저장
	for (int i = 0; i < tree[s].size(); i++) {
		v.push_back(dfs(tree[s][i]));
	}
	// 내림차순으로 정렬
	sort(v.rbegin(), v.rend());

	// 오래 걸리는 자식부터 전파해 나갈 때 가장 오래걸리는 시간 측정
	int maximum = 0;
	for (int i = 0; i < v.size(); i++) {
		maximum = max(maximum, v[i]+i);
	}
	// 본인(s)에게 전파되는 시간 +1하여 리턴
	return maximum+1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		if (tmp != -1) tree[tmp].push_back(i);
	}
	cout << dfs(0) -1;
	return 0;
}
