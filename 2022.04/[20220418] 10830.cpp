/*

2022.04.18.
- 10830 행렬 제곱: https://www.acmicpc.net/problem/10830
- 수학, 분할 정복, 분할 정복을 이용한 거듭제곱, 선형대수학
- GoldⅣ

- 주어진 행렬을 제곱하여 저장한다. (A -> A^2 -> A^4 -> ... )
- 승수 B를 이진수로 나타냈을 때, 1이 나타나는 곳의 자리수에 해당하는 행렬의 제곱을 답에 곱한다.
- 행렬 곱셈 과정에서 숫자를 읽어오는 배열과 숫자를 저장하는 배열을 따로 설정해야 한다.

*/
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
