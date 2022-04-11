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
