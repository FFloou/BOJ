#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T;
int N, K, W;
int X, Y;
vector<int> graph[1001];
queue<int> q;
int Dtime[1001]; //각 건물을 짓는데 걸리는 시간
int connect[1001]; //이전에 건설해야 하는 건물 수
int min_time[1001]; //시작 시간~각 건물을 완성하기까지 걸리는 시간

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	while (T--) {
		for (int i = 0; i < 1001; i++) { //initialize
			Dtime[i] = 0;
			connect[i] = 0;
			graph[i].clear();
			min_time[i] = 0;
		}
		while (!q.empty()) q.pop();

    //입력
		cin >> N >> K;
		for (int i = 1; i <= N; i++) {
			cin >> Dtime[i];
		}
		for (int i = 0; i < K; i++) {
			cin >> X >> Y;
			graph[X].push_back(Y);
			connect[Y]++;
		}
		cin >> W;
    
    //처음에 건설 할 수 있는 건물 큐에 삽입
		for (int i = 1; i <= N; i++) {
			if (connect[i] == 0) {
				min_time[i] = Dtime[i];
				q.push(i);
			}
		}

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			if (curr == W) { //목표 건물을 지었을 경우
				cout << min_time[curr] << '\n';
				break;
			}

      //curr에서 나가는 방향 모두 확인
			for (int i = 0; i < graph[curr].size(); i++) {
				int next = graph[curr][i];
				connect[next]--;
				min_time[next] = max(min_time[next], Dtime[next] + min_time[curr]);
				
				if (connect[next] == 0) { //들어오는 화살표가 없는 건물 큐에 삽입
					q.push(next);
				}
			}
		}

	}
	return 0;
}
