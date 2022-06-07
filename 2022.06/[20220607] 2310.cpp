/*

2022.06.07.
- 2130 어드벤처 게임: https://www.acmicpc.net/problem/2310
- 골드Ⅴ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 깊이 우선 탐색

- dfs로 방을 탐색하면서 n까지 도달할 수 있는지 확인한다.
- 방의 종류에 따라 소지금을 계산하고, 다음 방으로 이동하거나 조건에 따라 이동하지 못한다.
- 현재 루트에서 방문했던 방을 다른 루트에서도 방문할 수 있어야 하기 때문에 자식 노드들의 dfs 탐색이 끝나면
  visited를 다시 false로 바꾸어 놓는다.
- bfs로도 구현할 수 있을 것 같은데, visited를 다루는 방식에 대해 고민해보고 다시 bfs로 풀어 볼것

*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
char room[1001];
int cost[1001];
int tmp;
bool visited[1001];
bool success;

vector<int> next_room[1001];
queue<pair<int, int>> pq;

void initialize() {
	for (int i = 0; i <= 1000; i++) {
		next_room[i].clear();
		visited[i] = false;
	}
	while (!pq.empty()) pq.pop();
	success = false;
}

void dfs(int node, int money) {
	if (room[node] == 'T') {
		money -= cost[node];
	}
	else if (room[node] == 'L') {
		if (money < cost[node]) money = cost[node];
	}
	if (money < 0) return;
	if(node == n){
		success = true;
		return;
	}
	visited[node] = true;
	for (int i = 0; i < next_room[node].size(); i++) {
		int next = next_room[node][i];
		if (visited[next] == true) continue;
		dfs(next, money);
		
	}
	visited[node] = false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		initialize();
		cin >> n;
		if (n == 0) break;
		for (int i = 1; i <= n; i++) {
			cin >> room[i] >> cost[i];
			while (true) {
				cin >> tmp;
				if (tmp == 0) break;
				else next_room[i].push_back(tmp);
			}
		}
		success = false;
		dfs(1, 0);
		if (success) cout << "Yes\n";
		else cout << "No\n";
	}

	return 0;
}
