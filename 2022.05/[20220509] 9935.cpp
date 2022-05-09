/*

2022.05.09.
- 9935 문자열 폭발: https://www.acmicpc.net/problem/9935
- 자료 구조, 문자열, 스택
- 골드Ⅳ

- 한 글자씩 스택에 넣는다.
- 스택에 들어있는 문자의 수가 폭발 문자열의 수 이상이면 폭발할 문자열이 있는지 확인한다.
- 문자열 폭발은 새로운 문자가 스택에 들어올 때 발생하므로 새 문자를 넣고 폭발 여부를 확인한다.

*/
#include <iostream>
#include <string>

using namespace std;

string input;
string explosion;

char stack[1000001];
int ptr = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> input;
	cin >> explosion;

	int elength = explosion.length(); // 폭발 문자열 길이
	for (int i = 0; i < input.length(); i++) {
		stack[ptr++] = input[i];  // 스택에 삽입

		if (ptr >= elength) { // 스택에 든 문자 수가 폭발 문자 수 이상일 때 폭발 여부 확인
			int cnt = 0;
			for (int j = 0; j < elength; j++) {
				if (stack[ptr - elength + j] == explosion[j]) cnt++;
			}
			if (cnt == elength) { // 문자열 폭발. 스택에서 꺼내기
				ptr -= elength;
			}
		}

	}
	if (ptr == 0) cout << "FRULA";
	else {
		for (int i = 0; i < ptr; i++) {
			cout << stack[i];
		}
	}
	return 0;
}
