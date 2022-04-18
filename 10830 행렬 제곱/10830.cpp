
#include <iostream>
using namespace std;

const int MOD = 1000;
int N;
long long B;
int dim[6][6];
int answer[6][6];

int answer_tmp[6][6];
int dim_tmp[6][6];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> B;
	for (int i = 0; i < N; i++) {
		answer[i][i] = 1; // I로 초기화
		for (int j = 0; j < N; j++) {
			cin >> dim[i][j];
		}
	}

	long long d = 1;
	while (d <= B) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dim_tmp[i][j] = dim[i][j];
				answer_tmp[i][j] = answer[i][j];
			}
		}
		
		if ((d & B) != 0) { // 비트가 일치하는 경우 answer = answer * dim
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					int sum = 0;
					for (int k = 0; k < N; k++) {
						int add_num = (answer_tmp[i][k] * dim_tmp[k][j]) % MOD;
						sum = (sum + add_num) % MOD;
					}
					answer[i][j] = sum;
				}
			}

		}

		//dim 업데이트(dim^N -> dim^2N) dim = dim * dim
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int sum = 0;
				for (int k = 0; k < N; k++) {
					int dim_num = (dim_tmp[i][k] * dim_tmp[k][j]) % MOD;
					sum= (sum + dim_num) % MOD;
				}
				dim[i][j] = sum;
			}
		}

		d = d << 1;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << answer[i][j] << ' ';
		}
		cout << '\n';
	}


	return 0;
}
