/*

2022.05.27.
- 2109 순회강연: https://www.acmicpc.net/problem/2109
- 골드Ⅲ
- 자료 구조, 그리디 알고리즘, 정렬, 우선순위 큐

- 우선순위 큐를 활용하여 강연료 기준으로 내림차순 정렬한다.
- 우선순위 큐에서 하나씩 꺼내면서 정해진 날짜 안에 강연이 가능한지 확인한다.
   -> d에서 1까지 확인하면서 가능한 날짜(빈 날짜)에 가능하다고 표시한다.

*/
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
int n, d, p;
bool reserved[10001];
priority_queue<pii> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p >> d;
		pq.push({p, d});
	}

	int answer = 0;
	while (!pq.empty()) {
		pii curr = pq.top(); pq.pop();
		for (int i = curr.second; i > 0; i--) {
			if (reserved[i] == false) {
				reserved[i] = true;
				answer += curr.first;
				break;
			}
		}
	}
	cout << answer;
	return 0;
}
