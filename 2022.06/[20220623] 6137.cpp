/*

2022.06.23.
- 6137 문자열 생성: https://www.acmicpc.net/problem/6137
- 골드Ⅳ
- 문자열, 그리디 알고리즘, 두 포인터

- 앞과 뒤의 문자 중 사전순으로 빠른 것을 선택하여 T에 넣는다.
- 앞과 뒤의 문자가 같을 때는 두 포인터가 같지 않은 문자를 가리킬 때까지 포인터를 한칸씩 이동시킨다.
   -> 같지 않은 문자 중 빠른 쪽의 실제 포인터의 문자를 T에 넣고 한 칸 이동시킨다.
   -> 두 포인터가 서로 만날 때 까지 같다면 아무쪽이나 선택하여 T에 넣는다.

*/

#include <iostream>

using namespace std;

int N;
char s[2001];
char t[2001];


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> s[i];
	}
	int f = 0;
	int r = N - 1;
	int idx = 1;

	while (f <= r) {
		if (s[f] < s[r]) {
			t[idx++] = s[f++];
		}
		else if (s[f] > s[r]) {
			t[idx++] = s[r--];
		}
		else {
			int nextf = f;
			int nextr = r;
			while (nextf <= nextr) {
				if (s[nextf] < s[nextr]) {
					t[idx++] = s[f++];
					break;
				}
				else if (s[nextf] > s[nextr]) {
					t[idx++] = s[r--];
					break;
				}
				else {
					nextf++;
					nextr--;
				}
			}
			if (nextf > nextr) t[idx++] = s[f++];
		}
	}
	for (int i = 1; i <= N; i++) {
		cout << t[i];
		if (i % 80 == 0) cout << '\n';
	}

	return 0;
}
