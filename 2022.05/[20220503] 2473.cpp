/*

2022.05.03.
- 2473 세 용액: https://www.acmicpc.net/problem/2473
- 정렬, 이분 탐색, 두 포인터
- 골드Ⅳ

- 두 포인터를 사용할 수 있도록 주어진 용액의 특성값을 정렬한다.
- 하나의 용액을 선택하여 고정시키고 그 용액의 뒤부터 두 포인터를 사용하여 세 합이 0에 가까운 조합을 찾는다

*/
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const long long INF = 3000000000;

int N;
long long liquid[5010];
long long answer[3];
long long min_sum = INF;
int ptr1, ptr2;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> liquid[i];
	}
	sort(liquid, liquid+ N);
	for (int i = 0; i < N-2; i++) {
		long long s1 = liquid[i];
		ptr1 = i + 1;
		ptr2 = N - 1;
		while (ptr1 < ptr2) {
			long long sum = s1 + liquid[ptr1] + liquid[ptr2];
			if (abs(sum) < min_sum) {
				min_sum = abs(sum);
				answer[0] = s1;
				answer[1] = liquid[ptr1];
				answer[2] = liquid[ptr2];
			}
			if (min_sum == 0) break;
			else if (sum < 0) ptr1++;
			else ptr2--;
		}
	}
	cout << answer[0] << ' ' << answer[1] << ' ' << answer[2] << '\n';
	return 0;
}
