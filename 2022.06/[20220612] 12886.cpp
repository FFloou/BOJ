/*

2022.06.12.
- 12886 돌 그룹: https://www.acmicpc.net/problem/12886
- 골드Ⅳ
- 그래프 이론, 그래프 탐색, 너비 우선 탐색

- 돌 집합은 순서가 상관없으므로 가장 큰 그룹, 가장 작은 그룹만 큐와 visited로 체크하면서 bfs를 진행한다.
  -> 나머지 그룹은 전체 합에서 두 그룹의 합을 뺀 값으로 알 수 있다.

*/
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


int A, B, C;
int newa, newb, newc;
int maximum, minimum;
bool visited[1001][1001];
queue<pair<int, int>> q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> A >> B >> C;
	int total = A + B + C;

	if (total % 3 != 0) {
		cout << 0;
		return 0;
	}
	int answer = 0;
	minimum = min({ A, B, C });
	maximum = max({ A, B, C });
	q.push({minimum, maximum});
	visited[minimum][maximum];

	while (!q.empty()) {
		int a = q.front().first;  // min
		int c = q.front().second; // max
		int b = total - a - c;    // middle
		q.pop();

		if (a == b && b == c) {
			answer = 1;
			break;
		}

		//a와 b선택
		if (a != b ) {
			newa = a + a;
			newb = b - a;
			newc = c;

			maximum = max({ newa, newb, newc });
			minimum = min({ newa, newb, newc });
			if (!visited[minimum][maximum]) {
				visited[minimum][maximum] = true;
				q.push({ minimum, maximum });
			}
		}
		//b와 c선택
		if (b != c) {
			newa = a;
			newb = b + b;
			newc = c - b;

			maximum = max({ newa, newb, newc });
			minimum = min({ newa, newb, newc });
			if (!visited[minimum][maximum]) {
				visited[minimum][maximum] = true;
				q.push({ minimum, maximum });
			}
		}
		//a와 c선택
		if (a != c) {
			newa = a + a;
			newb = b;
			newc = c - a;
			maximum = max({ newa, newb, newc });
			minimum = min({ newa, newb, newc });
			if (!visited[minimum][maximum]) {
				visited[minimum][maximum] = true;
				q.push({ minimum, maximum });
			}
		}
	}
	cout << answer;


	return 0;
}
