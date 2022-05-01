/*

2022.04.10.
- 1644 소수의 연속합: https://www.acmicpc.net/problem/1644
- 수학, 정수론, 두 포인터, 소수 판정, 에라토스테네스의 체
- GoldIII

- 에라토스테네스의 체를 통해 주어진 범위의 모든 소수를 구한다.
    - n까지의 소수를 찾을 때, n의 제곱근까지만 확인한다.
    - 소수인 숫자 i의 배수를 없앨 때, i\*i부터 시작하여 i씩 늘려가며 없앤다.
- 해당 소수보다 작은 소수들을 합한 누적합을 저장하여 계산에 사용한다.
- 목표한 값보다 합이 작으면 큰 값쪽의 포인터를 뒤로 움직인다.
- 목표한 값보다 합이 크면 작은 값 쪽의 포인터를 뒤로 움직인다.

*/


#include <iostream>

using namespace std;

int N;
bool prime[4000001];
int	prime_sum[4000001];

void find_prime() { //문제 최대값 까지 모든 소수를 찾는 함수
	for (int i = 0; i <= 4000000; i++) prime[i] = true;
	for (int i = 2; i <= 2000; i++) {
		if (prime[i] == false) continue;
		for (int j = i * i; j <= 4000000; j += i)
			prime[j] = false;
	}
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	find_prime();

	cin >> N;

	int idx = 1;
	int prime_cnt = 0;
	for (int i = 2; i <= N; i++) {
		if (prime[i] == true) {//소수의 누적합을 배열에 저장
			prime_sum[idx] = prime_sum[idx - 1] + i;
			idx++;
			prime_cnt++;
		}
	}
	int ptr1 = 0;
	int ptr2 = 1;
	int cnt = 0;
	while (ptr1 <= prime_cnt && ptr2<=prime_cnt) {
		int sum = prime_sum[ptr2] - prime_sum[ptr1]; //ptr1~ptr2까지 합계산
		if (sum < N) {// 목표값보다 작은 경우 범위를 위로 한 칸 늘림
			ptr2++;
		}
		else {//목표 값보다 크거나 같은 경우 아래쪽 범위를 한 칸 좁힘
			if (sum == N) cnt++;
			ptr1++;
		}
	}
	cout << cnt;
	return 0;
}
