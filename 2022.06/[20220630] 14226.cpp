/*

2022.06.30.
- 14226 이모티콘: https://www.acmicpc.net/problem/14226
- 골드Ⅳ
- 다이나믹 프로그래밍, 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 가능한 연산을 진행하면서 화면에 S개의 이모티콘이 나올 때 까지 bfs로 탐색한다.
- 클립보드의 이모티콘 개수와 화면의 이모티콘 개수를 상태로 고려하여 방문여부를 체크한다.
- 화면에 붙여넣는 연산을 할 때 값이 증가하기 때문에 연산을 수행하기 전에 최대 값을 넘어가는지 체크하여
  넘어가는 경우에는 진행하지 않는다.

*/

#include <iostream>
#include <queue>


using namespace std;

struct info {
	int clip;
	int view;
	int t;
};

queue<info> q;
// [clip][view]
bool visited[3000][3000];
int S;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> S;

	q.push({ 0, 1, 0 });
	visited[0][1];

	while (!q.empty()) {
		info curr = q.front();
		q.pop();

		if (curr.view == S) {
			cout << curr.t;
			break;
		}

		/// 클립보드에 저장
		if (curr.view > 0 && !visited[curr.view][curr.view]) {
			visited[curr.view][curr.view] = true;
			q.push({ curr.view, curr.view, curr.t + 1 });
		}
		// 화면에 붙여넣기
		if (curr.clip > 0 && (curr.clip + curr.view) <= 1000 ) {
			if (!visited[curr.clip][curr.view + curr.clip]) {
				visited[curr.clip][curr.view + curr.clip] = true;
				q.push({ curr.clip, curr.view + curr.clip, curr.t + 1 });
			}
		}
		// 이모티콘 하나 삭제
		if (curr.view > 0 && !visited[curr.clip][curr.view-1]) {
			visited[curr.clip][curr.view - 1] = true;
			q.push({ curr.clip, curr.view - 1, curr.t + 1 });
		}
	}

	return 0;
}
