/*

2022.04.22.
- 16235 나무 재테크: https://www.acmicpc.net/problem/16235
- 구현, 시뮬레이션
- GoldⅣ

- 단순 구현 문제
- 조건이 복잡하기 때문에 조건을 잘 읽어보고 작성한다.
- 각 계절의 과정은 다음 과정에 영향을 미칠 수 있기 때문에 같이 묶어서 처리할 때는 주의한다.

*/
#include <iostream>
#include <vector>
using namespace std;

int N, M, K; 
int x, y, z;
int tree_cnt;

int A[11][11];
int nourish[11][11];
vector<int> trees[11][11];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			nourish[i][j] = 5;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		trees[x][y].push_back(z);
		tree_cnt++;
	}
	while (K--) {
		// 봄 여름
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (trees[i][j].size() == 0) continue;
				int dead_tree = 0;
				int dead_sum = 0;

				for (int k = 0; k < trees[i][j].size(); k++) {
					if (nourish[i][j] - trees[i][j][k] >= 0) {
						nourish[i][j] -= trees[i][j][k];
						trees[i][j][k]++;
					}
					else {
						dead_tree++;
						dead_sum += (trees[i][j][k] / 2);
					}
				}
				tree_cnt -= dead_tree;
				nourish[i][j] += dead_sum;
				trees[i][j].erase(trees[i][j].end() - dead_tree, trees[i][j].end());
			}
		}

		// 가을
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (trees[i][j].size() == 0) continue;
				for (int k = 0; k < trees[i][j].size(); k++) {
					if (trees[i][j][k] % 5 == 0) {
						int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
						int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
						for (int p = 0; p < 8; p++) {
							int nextx = i + dx[p];
							int nexty = j + dy[p];
							if (nextx > 0 && nextx <= N && nexty > 0 && nexty <= N) {
								trees[nextx][nexty].insert(trees[nextx][nexty].begin(), 1);
								tree_cnt++;
							}
						}
					}
				}
			}
		}
		// 겨울
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				nourish[i][j] += A[i][j];
			}
		}
	}

	cout << tree_cnt;
	return 0;
}
