/*

2022.06.04.
- 1715 카드 정렬하기: https://www.acmicpc.net/problem/1715
- 골드Ⅳ
- 자료 구조, 그리디 알고리즘, 우선순위 큐

- 우선순위 큐로 카드 수 대로 묶음을 오름차순 정렬하고, 수가 작은 묶음 두 개를 꺼내어 새로운 묶음을 만들어 큐에 넣는다.
- 묶음 두 개를 하나의 묶음으로 만들 때마다 비교 횟수를 더하여 저장해둔다.
- 우선순위 큐에 묶음이 하나가 남을 때 까지 위 과정을 반복한다.

*/
#include <iostream>
#include <queue>

using namespace std;

int N;
int input;
int answer;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input;
		pq.push(input);
	}

	while (pq.size() > 1) {
		int fd = pq.top(); pq.pop();
		int sd = pq.top(); pq.pop();
		answer += fd + sd;
		pq.push(fd + sd);
	}
	cout << answer;
	return 0;
}
