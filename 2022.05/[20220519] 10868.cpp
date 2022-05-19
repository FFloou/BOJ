/*

2022.05.19.
- 10868 최솟값: https://www.acmicpc.net/problem/10868
- 골드Ⅰ
- 자료 구조, 세그먼트 트리, 희소 배열

- 최소값을 저장하는 세그먼트 트리를 사용하는 문제
- N의 최대값에 따른 트리의 최대 길이에 주의

*/
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_NUM = 1000000001;
int N, M;
int SIZE = 1;
int tree[270000];
int tmp;
int a, b;

void insert(int idx, int num) {
	while (idx > 0) {
		tree[idx] = min(tree[idx], num);
		idx /= 2;
	}
}

int find_min(int idx1, int idx2) {
	int left = idx1;
	int right = idx2;
	int range_min = MAX_NUM;

	while (left <= right) {
		if (left % 2 == 1) {
			range_min = min(range_min, tree[left]);
		}
		if (right % 2 == 0) {
			range_min = min(range_min, tree[right]);
		}

		left = (left + 1) / 2;
		right = (right - 1) / 2;

	}

	return range_min;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	while (SIZE < N) SIZE *= 2;
	for (int i = 1; i < SIZE * 2; i++) {
		tree[i] = MAX_NUM;
	}

	for (int i = 0; i < N; i++) {
		cin >> tmp;
		insert(i+SIZE, tmp);
	}
	
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cout << find_min(a+SIZE-1, b+SIZE-1) << '\n';
	}

	return 0;
}
