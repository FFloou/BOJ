/*

2022.04.26.
- 15684 사다리 조작: https://www.acmicpc.net/problem/15684
- 구현, 브루트포스 알고리즘, 백트래킹
- 골드Ⅳ

- 사다리를 표현하는 2차원 배열 ladder의 좌표가 의미하는 것이 무엇인지 헷갈리지 않도록 주의한다.
- 백트래킹을 할 때 확인하지 않는 가로선이 없도록 주의한다.
   -> 다음 가로선을 선택할 때 for문의 시작점에 유의한다.
- 가로선에 포함된 두 점은 다른 가로선을 만들 수 없음에 유의한다.

*/
#include <iostream>
using namespace std;

int N, M, H;
int a, b;
int ladder[40][20];
int min_num = 4;


bool check_ladder() { // 조건에 맞는 사다리인지 확인
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		int node = i;
		for (int j = 1; j <= H; j++) {
			if (ladder[j][node] == 0) continue;
			else node = ladder[j][node];
		}
		if (node != i) break;
		else cnt++;
	}
	if (cnt == N) return true; // 조건 만족
	else return false;  // 조건 불만족
}

void choose_ladder(int num, int h) {
	if (num > 3) return;  //3개를 넘어가면 prune
	if (check_ladder() == true) { // 조건 만족
		min_num = min(min_num, num);
		return;
	}
	for (int i = h; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			//확인하는 지점과 이어진 가로선이 있는 경우 뛰어넘기
			if (ladder[i][j] != 0 || ladder[i][j+1] != 0) continue;

			ladder[i][j] = j + 1;
			ladder[i][j + 1] = j;

			choose_ladder(num + 1, i);

			ladder[i][j] = 0;
			ladder[i][j + 1] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> H;

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		ladder[a][b] = b + 1;
		ladder[a][b + 1] = b;
	}
	choose_ladder(0, 1);

	if (min_num > 3) cout << -1;
	else cout << min_num;
	return 0;
}
