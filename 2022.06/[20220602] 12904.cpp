/*

2022.06.02.
- 12904 A와 B: https://www.acmicpc.net/problem/12904
- 골드Ⅴ
- 구현, 문자열, 그리디 알고리즘

- 문자열의 뒤에서 부터 확인하면서 문자열에 행해졌을 연산을 거꾸로 적용한다.
- S와 T의 길이가 같아지면 S와 T를 비교하여 같은 문자열인지 확인한다.
- 문자열의 앞 뒤의 인덱스를 st, ed에 저장하고, 뒤집는 연산은 두 인덱스의 값을 바꿔 적용한다.
  -> 두 문자열을 비교할 때 st -> ed 방향으로 훑어갈 수 있도록 조정이 필요하다. 

*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string s;
string t;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> s;
	cin >> t;

	int st = 0;
	int ed = t.length() - 1;

	while (s.length() < (abs(st - ed) + 1)) {
		if (st < ed) {
			if (t[ed--] == 'B') swap(st, ed);
		}
		else {
			if (t[ed++] == 'B') swap(st, ed);
		}
	}

	int answer = 1;

	int sign = (st < ed) ? 1 : -1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != t[st + (sign * i)]) {
			answer = 0;
			break;
		}
	}
	cout << answer;
	return 0;
}
