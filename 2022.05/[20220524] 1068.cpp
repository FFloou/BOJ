/*

2022.05.24.
- 1068 트리: https://www.acmicpc.net/problem/1068
- 골드Ⅴ
- 그래프 이론, 그래프 탐색, 트리, 깊이 우선 탐색

- 노드의 자식을 vector에 저장하는 방식으로 트리를 생성한다.
- root에서 부터 tree를 순회하면서 리프 노드의 개수를 센다.
  -> 자식이 없는 노드이거나, 자식이 지울 노드 하나 밖에 없는 경우(노드를 지우면 리프노드가 되는 경우)
- 지울 노드에 방문하면 지울 노드의 자식은 방문하지 않는다.

*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
int parent;
int del_node;
vector<int> tree[51];
queue<int> q;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> parent;
		if (parent == -1) q.push(i);
		else tree[parent].push_back(i);
	}
	cin >> del_node;

	int answer = 0;

	while (!q.empty()) {
		int curr = q.front(); q.pop();
		if (curr == del_node) continue;

		// 자손이 없는 리프 노드이거나 
		// 자손이 지울 노드 하나 뿐인 경우(노드를 삭제하면 리프노드가 되는 경우)
		if (tree[curr].size() == 0 || 
			(tree[curr].size() == 1 && tree[curr][0] == del_node)) {
			answer++;
			continue;
		}
		for (int i = 0; i < tree[curr].size(); i++) {
			q.push(tree[curr][i]);
		}
	}
	cout << answer;
	return 0;
}
