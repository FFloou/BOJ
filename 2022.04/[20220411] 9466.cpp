/*

2022.04.11.
- 9466 텀 프로젝트: https://www.acmicpc.net/problem/9466
- 그래프 이론, 그래프 탐색, 깊이 우선 탐색
- GoldⅢ

- 위상 정렬 알고리즘을 사용한다.(정석 풀이는 dfs와 cycle을 찾는 방식을 사용한다)
- cycle을 이루는 노드들은 팀을 구성하고, 그렇지 못한 노드를 세는 문제이다.
- cycle에 포함된 노드는 위상 정렬 진행 중에 큐에 들어가지 못한다.
   -> 위상 정렬 진행 중 큐가 비어 종료된 경우에 방문하지 못한 노드는 cycle에 포함된다.
- 위상 정렬을 큐가 빌 때 까지 방문한 노드는 팀을 이루지 못하는 노드이므로 방문한 노드 수를 세어 표시한다.

*/

#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100001;
int T, n;
int selected[MAX];
int select_sum[MAX];
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

  //위상 정렬 알고리즘 이용
	cin >> T;
	while (T--) {
		//값 초기화
		while (!q.empty()) q.pop();
		for (int i = 1; i <= n; i++) {
			selected[i] = 0;
			select_sum[i] = 0;
		}
		cin >> n;
		int answer = 0;
		for (int i = 1; i <= n; i++) {
			cin >> selected[i];
			select_sum[selected[i]]++; //들어오는 간선의 수 저장
		}
		for (int i = 1; i <= n; i++) {//들어오는 간선이 없는 노드 큐에 추가
			if (select_sum[i] == 0) q.push(i);
		}
		while (!q.empty()) {
			int curr = q.front(); q.pop();
			answer++; //들어오는 간선이 없는 노드 == 팀을 이루지 못하는 노드
			
			int next = selected[curr]; //curr노드에서 나가는 간선이 도착하는 노드
			select_sum[next]--;
			if (select_sum[next] == 0) q.push(next); //들어오는 간선이 없다면 큐에 추가
		}
		cout << answer << '\n';
	}
	return 0;
}
