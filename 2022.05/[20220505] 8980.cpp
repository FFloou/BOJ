/*

2022.05.05.
- 8980 택배: https://www.acmicpc.net/problem/8980
- 그리디 알고리즘, 정렬
- 골드Ⅲ

- 도착 순서가 작은 순, 도착 순서가 같을 때는 출발 순서가 큰 순서대로 정렬한다.
   -> 우선순위 큐 사용
- 큐에서 나오는 순서대로 출발지에서 도착지까지 넣을 수 있는 짐의 최대 크기를 확인한다.

*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct load {
	int from;
	int to;
	int box;
};

struct cmp { // 도착 숫자가 작은 순 -> 출발 순서가 큰 순
	bool operator()(load a, load b) {
		if (a.to == b.to) return a.from < b.from;
		else return a.to > b.to;
	}
};

int N, C, M;
int a, b, c;
int answer;
int space[2001];
priority_queue<load, vector<load>, cmp> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> C >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		pq.push({ a,b,c });
	}
  
	for (int i = 1; i <= N; i++) { // 운반 가능한 크기로 초기화
		space[i] = C;
	}
  
	while (!pq.empty()) {
		load curr = pq.top(); pq.pop();
	
		int min_left = C;
		for (int i = curr.from; i < curr.to; i++) { //from ~ to 비어있는 짐칸의 최소 값
			min_left = min({ min_left, space[i], curr.box});
		}

		if (min_left == 0) continue;

		for (int i = curr.from; i < curr.to; i++) {
			space[i] -= min_left;
		}
		answer += min_left;
	}
  
	cout << answer;
	return 0;
}
