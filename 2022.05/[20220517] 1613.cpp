/*

2022.05.17.
- 1613 역사: https://www.acmicpc.net/problem/1613
- 골드Ⅲ
- 그래프 이론, 플로이드-와샬

- 플로이드-와샬 알고리즘으로 모든 정점에서 이동 가능한 정점 찾기
- 거리를 구할 필요가 없으므로 처음에 -1로 초기화하고 중간점 k를 거쳐 이동가능하면 1로 변경

*/
#include <iostream>


using namespace std;

int n, k, s;
int a, b;
int map[401][401];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 401; i++) {
		for (int j = 0; j < 401; j++) {
			map[i][j] = -1;  // 이동 불가능한 점 == -1 
			if (i == j) map[i][j] = 1;
		}
	}
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		map[a][b] = 1;  // 이동 가능한점 == 1
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				// k를 거쳐 i -> j 이동이 불가능한 경우 건너뛰기
				if (map[i][k] == -1 || map[k][j] == -1) continue; 
				else map[i][j] = 1;
			}
		}
	}

	cin >> s;
	for (int i = 0; i < s; i++) {
		cin >> a >> b;
		if (map[a][b] == 1) { // a -> b
			cout << -1 << '\n';
		}
		else if (map[b][a] == 1) { // b -> a
			cout << 1 << '\n';
		}
		else {  // a와 b가 연결이 없는 경우
			cout << 0 << '\n';
		}
	}
	
	return 0;
}
