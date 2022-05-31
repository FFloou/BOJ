/*

2022.05.31.
- 1781 컵라면: https://www.acmicpc.net/problem/1781
- 골드Ⅱ
- 자료 구조, 그리디 알고리즘, 우선순위 큐

- pq에는 문제 전체를 aq에는 풀 문제를 저장한다.
- 데드라인 기준 오름차순으로 정렬하고, 데드라인이 같다면 보상 기준 내림차순으로 정렬한다.
- aq에 담긴 문제가 현재 확인한 문제의 데드라인보다 작으면 aq에 확인한 문제를 추가한다.
    -> 데드라인까지 일정이 비어 있어 문제를 풀 수 있다.
- aq에 담긴 문제가 현재 확인한 문제의 데드라인보다 크거나 같으면 aq에 저장된 문제 중 가장 보상이 작은 문제와
   현재 확인한 문제의 보상을 비교하여 더 큰 쪽을 aq에 넣는다.
   -> 현재 확인한 문제(pq)의 문제를 선택하는 것이 더 이득인 경우에 풀 문제를 바꾼다.

*/
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
struct cmp {
	bool operator()(pii &A, pii &B) {
		if (A.first == B.first) return A.second < B.second;
		else return A.first > B.first;
	}
};
int N;
long long int answer;
int a, b;

priority_queue<pii, vector<pii>, cmp> pq;
priority_queue<int, vector<int>, greater<int>> aq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> a >> b;
		pq.push({ a, b });
	}
	while (!pq.empty()) {
		pair<int, int> curr = pq.top(); pq.pop();
		int done = aq.size();
		
		// 일정이 가득 찼으나 curr을 선택하면 더 이득인 경우
		if (curr.first <= done && aq.top() < curr.second) {
			aq.pop();
			aq.push(curr.second);
		}
		// 일정이 비어있는 경우
		else if(curr.first > done) aq.push(curr.second);
	}
	while (!aq.empty()) {
		answer += aq.top();
		aq.pop();
	}
	cout << answer;
	return 0;
}
