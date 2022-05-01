/*

2022.04.15.
- 20040 사이클 게임: https://www.acmicpc.net/problem/20040
- 자료 구조, 분리 집합
- GoldⅣ

- Union-Find 알고리즘을 활용한다.
- 추가되는 간선이 같은 집합에 속한 두 점을 이을 때 사이클이 생성된다.
- 입력된 두 점을 이어나가다 처음으로 union에 실패하는 때가 사이클이 발생하는 때이다.

*/
#include <iostream>

using namespace std;

int N, M;
int p1, p2;
int uni[500001];

//find
int find(int a) {
	if (uni[a] == a) return a;
	else return uni[a] = find(uni[a]);
}
//union
bool make_union(int a, int b) {
	int aparent = find(a);
	int bparent = find(b);
	if (aparent == bparent) return false;
	else {
		uni[bparent] = aparent;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) { //initialaize
		uni[i] = i;
	}
	int answer = 0;
	for (int j = 1; j <= M; j++) {
		cin >> p1 >> p2;
		// union을 시도했을 때 이미 같은 union에 속함 -> cycle이 생성됨
		if (make_union(p1, p2) == false) { 
			answer = j;
			break;
		}
	}
	cout << answer;
	return 0;
}
