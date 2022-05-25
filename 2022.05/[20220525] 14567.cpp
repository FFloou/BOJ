/*

2022.05.25.
- 14567 선수과목 (Prerequisite): https://www.acmicpc.net/problem/14567
- 골드Ⅴ
- 다이내믹 프로그래밍, 그래프 이론, 위상정렬

- 위상정렬을 사용하여 선수과목부터 과목을 정렬해나간다.
- 한 단계가 진행될 때마다(한 학기가 지날 때마다) 단계가 시작될 때 
    큐에 있던 값들에는 같은 값을 저장한다.

*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;
int A, B;

vector<int> next_cnt[1001];
int pre_cnt[1001];
int order[1001];
queue<int> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		next_cnt[A].push_back(B);
		pre_cnt[B]++;
	}

	for (int i = 1; i <= N; i++) {
		if (pre_cnt[i] == 0) q.push(i);
	}

	int semester = 1;
	while (!q.empty()) {
		int qsize = q.size();
		for (int i = 0; i < qsize; i++) {
			int curr = q.front(); q.pop();
			order[curr] = semester;

			for (int j = 0; j < next_cnt[curr].size(); j++) {
				int next = next_cnt[curr][j];
				pre_cnt[next]--;
				if (pre_cnt[next] == 0) q.push(next);
			}

		}
		semester++;
	}
	for (int i = 1; i <= N; i++) {
		cout << order[i] << ' ';
	}
	return 0;
}
