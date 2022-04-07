#include <iostream>
#include <algorithm>

using namespace std;

int N, t;
int ptr;
int arr[1000001];

int bs(int s, int e, int num) { //lower bound의 index 리턴
	int mid = 0;
	while (s < e) {
		mid = (s + e) / 2;
		if (num <= arr[mid]) e = mid;
		else s = mid + 1;
	}
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> t;
		if (ptr == 0 || arr[ptr] < t) { //비었거나 수열의 마지막 숫자보다 큰 경우. arr[1]부터 저장
			arr[++ptr] = t;
		}
		else {//lower bound의 위치를 찾아 삽입
			arr[bs(1, ptr, t)] = t;
		}
	}
	cout << ptr;
	return 0;

}
