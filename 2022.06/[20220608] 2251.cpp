/*

2022.06.08.
- 2251 물통: https://www.acmicpc.net/problem/2251
- 골드Ⅴ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색, 깊이 우선 탐색

- A, B, C 물통에 있는 물의 양을 노드로 생각하여 3차원 배열로 방문 여부를 확인한다.
- 두 물통을 선택하여 물을 이동시킬 때, 이동시킬 수 있는 경우인지 확인하고 물을 이동시킨다

*/
#include <iostream>
#include <queue>

using namespace std;

struct waters {
	int a;
	int b;
	int c;
};
int A, B, C;

bool visited[201][201][201];
bool answer[201];

queue<waters> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> A >> B >> C;
	q.push({ 0,0,C });
	visited[0][0][C] = true;

	while (!q.empty()) {
		waters curr = q.front(); q.pop();
		if (curr.a == 0) answer[curr.c] = true;

		if (curr.a > 0) {
			// a -> b
			if (curr.b < B) {
				int nextb = (curr.b + curr.a > B) ? (B) : (curr.b + curr.a);
				int nexta = curr.a - (nextb - curr.b);
				if (visited[nexta][nextb][curr.c] == false) {
					q.push({ nexta, nextb, curr.c });
					visited[nexta][nextb][curr.c] = true;
				}
			}
			// a -> c
			if (curr.c < C) {
				int nextc = (curr.c + curr.a > C) ? (C) : (curr.c + curr.a);
				int nexta = curr.a - (nextc - curr.c);
				if (visited[nexta][curr.b][nextc] == false) {
					q.push({ nexta, curr.b, nextc });
					visited[nexta][curr.b][nextc] = true;
				}
			}
		}
		if (curr.b > 0) {
			// b -> a
			if (curr.a < A) {
				int nexta = (curr.b + curr.a > A) ? (A) : (curr.b + curr.a);
				int nextb = curr.b - (nexta - curr.a);
				if (visited[nexta][nextb][curr.c] == false) {
					q.push({ nexta, nextb, curr.c });
					visited[nexta][nextb][curr.c] = true;
				}
			}
			// b -> c
			if (curr.c < C) {
				int nextc = (curr.b + curr.c > C) ? (C) : (curr.b + curr.c);
				int nextb = curr.b - (nextc - curr.c);
				if (visited[curr.a][nextb][nextc] == false) {
					q.push({ curr.a, nextb, nextc });
					visited[curr.a][nextb][nextc] = true;
				}
			}
		}
		if (curr.c > 0) {
			// c -> a
			if (curr.a < A) {
				int nexta = (curr.c + curr.a > A) ? (A) : (curr.c + curr.a);
				int nextc = curr.c - (nexta - curr.a);
				if (visited[nexta][curr.b][nextc] == false) {
					q.push({ nexta, curr.b, nextc });
					visited[nexta][curr.b][nextc] = true;
				}
			}
			// c -> b
			if (curr.b < B) {
				int nextb = (curr.c + curr.b > B) ? (B) : (curr.c + curr.b);
				int nextc = curr.c - (nextb - curr.b);
				if (visited[curr.a][nextb][nextc] == false) {
					q.push({ curr.a, nextb, nextc });
					visited[curr.a][nextb][nextc] = true;
				}
			}
		}
	}
	for (int i = 0; i <= C; i++) {
		if (answer[i]) cout << i<<' ';
	}
	return 0;
}
