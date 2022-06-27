/*

2022.06.27.
- 14428 수열과 쿼리 16: https://www.acmicpc.net/problem/14428
- 골드Ⅰ
- 자료 구조, 세그먼트 트리

- 세그먼트 트리를 구성할 때 값과 함께 인덱스도 비교하고 저장하여 값이 같을 때 가장 작은 인덱스를
  찾을 수 있도록 한다.
- 새로운 값으로 업데이트 할 때는 부모로 거슬러 올러가면서 자식 값들 중 최소값을 선택하여 저장한다.

*/

#include <iostream>

using namespace std;

typedef pair<int, int> pii;
const int MAX = 1 << 18;
const int INF = 2000000000;
int N, M;
int a, b, c;
int sidx = 1;
// <value, index>
pii tree[MAX];

void update(int value, int idx) {
	int loc = sidx + idx - 1;
	tree[loc] = { value, idx };
	loc /= 2;
	while (loc > 0) {
		pii left = tree[loc * 2];
		pii right = tree[loc * 2 + 1];

		if (left.first > right.first) {
			tree[loc] = right;
		}
		else if (left.first == right.first) {
			if (left.second > right.second) {
				tree[loc] = right;
			}
			else tree[loc] = left;
		}
		else {
			tree[loc] = left;
		}
		loc /= 2;
	}
}

int find(int s, int e) {
	int l = sidx + s - 1;
	int r = sidx + e - 1;
	pii minimum = { INF, INF };

	while (l <= r) {
		if (l % 2 == 1) {
			if (minimum.first > tree[l].first) {
				minimum = tree[l];
			}
			else if (minimum.first == tree[l].first) {
				minimum.second = min(minimum.second, tree[l].second);
			}
			l++;
		}
		if (r % 2 == 0) {
			if (minimum.first > tree[r].first) {
				minimum = tree[r];
			}
			else if (minimum.first == tree[r].first) {
				minimum.second = min(minimum.second, tree[r].second);
			}
			r--;
		}
		l /= 2;
		r /= 2;
	}
	return minimum.second;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	while (sidx < N)sidx *= 2;
	for (int i = 0; i < sidx * 2; i++) {
		tree[i] = { INF, INF };
	}
	for (int i = 1; i <= N; i++) {
		cin >> a;
		update(a, i);
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			update(c, b);
		}
		else {
			cout << find(b, c) << '\n';
		}
	}


	return 0;
}
