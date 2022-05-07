/*
2022.05.07.
- 1976 여행 가자: https://www.acmicpc.net/problem/1976
- 그래프 이론, 자료 구조, 그래프 탐색, 분리 집합
- 골드Ⅳ

- union-find 알고리즘 이용
- 서로 이동가능한 도시들을 하나의 집합으로 union한다.
- 방문하고 싶은 도시들의 최상위 부모를 find하여 같은 집합에 속해 있는지 확인한다.
   -> 같은 집합에 속해 있으면 이동 가능

*/
#include <iostream>

using namespace std;

int N, M;
int tmp;
int union_arr[201];

void initialize(int num) {
	for (int i = 1; i <= num; i++) {
		union_arr[i] = i;
	}
}

int find_parent(int n) {
	if (union_arr[n] == n) return n;
	else return union_arr[n] = find_parent(union_arr[n]);
}

void make_union(int a, int b) {
	int aparent = find_parent(a);
	int bparent = find_parent(b);
	if (aparent != bparent) union_arr[aparent] = bparent;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	

	cin >> N >> M;
	initialize(N);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> tmp;
			if (tmp == 1) make_union(i, j);
		}
	}

	int parent = 0;
	bool answer = true;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		int tparent = find_parent(tmp);
		if (parent == 0) {
			parent = tparent;
			continue;
		}
		if (parent != tparent) {
			answer = false;
			break;
		}
	}
	if (answer) cout << "YES";
	else cout << "NO";

	return 0;
}
