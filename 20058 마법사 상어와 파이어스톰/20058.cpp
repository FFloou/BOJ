#include <iostream>
#include <queue>
using namespace std;


int dr[4] = { 0,0,1,-1 };
int dc[4] = { 1,-1,0,0 };

int N, Q;
int A[65][65];
int tmp_A[65][65];
int L[1001];


bool visited[65][65];
queue<pair<int, int>> q;

void initialize() {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			tmp_A[i][j] = 0;
		}
	}
	return;
}
void rotate_map(int grid) {
	initialize();
	for (int i = 1; i <= N; i += grid) {
		for (int j = 1; j <= N; j += grid) {
			// (i,j)는 나누어진 격자의 시작점
			for (int r = 0; r < grid; r++) {
				for (int c = 0; c < grid; c++) {
					tmp_A[i+c][j+grid-1-r] = A[i + r][j + c];
				}
			}
		}
	}
	return;
}

void melt_ice() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tmp_A[i][j] == 0) {
				A[i][j] = 0;
				continue;
			}
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nextr = i + dr[k];
				int nextc = j + dc[k];

				if (nextr > 0 && nextr <= N && nextc > 0 && nextc <= N && tmp_A[nextr][nextc] != 0) {
					cnt++;
				}
			}
			if (cnt >= 3) A[i][j] = tmp_A[i][j];
			else A[i][j] = tmp_A[i][j] - 1;
		}
	}
	return;
}

int ice_sum() {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sum += A[i][j];
		}
	}
	return sum;
}

int largest_ice() {
	int ice_size = 0;
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] == true) continue;
			if (A[i][j] == 0) {
				visited[i][j] = true;
				continue;
			}

			visited[i][j] = true;
			q.push({ i, j });
			cnt = 0;

			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				cnt++;

				q.pop();

				for (int k = 0; k < 4; k++) {
					int nextr = r + dr[k];
					int nextc = c + dc[k];

					if (nextr > 0 && nextr <= N && nextc > 0 && nextc <= N && visited[nextr][nextc] == false && A[nextr][nextc] != 0) {
						visited[nextr][nextc] = true;
						q.push({ nextr, nextc });
					}
				}
			}
			ice_size = max(ice_size, cnt);
		}
	}
	if (ice_size == 1) ice_size = 0; //덩어리가 없는 경우
	return ice_size;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> Q;
	N = 1 << N;  // 격자 개수
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 1; i <= Q; i++) {
		cin >> L[i];
	}

	int t = 1;
	while (t <= Q) {
		int l = 1 << L[t];
		rotate_map(l);
		melt_ice();
		t++;
	}

	cout << ice_sum() << '\n';
	cout << largest_ice();

	return 0;
}
