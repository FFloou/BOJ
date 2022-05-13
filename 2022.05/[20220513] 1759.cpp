/*

2022.05.13.
- 1759 암호 만들기: https://www.acmicpc.net/problem/1759
- 골드Ⅴ
- 수학, 브루트포스 알고리즘, 조합론, 백트래킹

- 주어진 문자를 정렬한 후 조합을 만들어 사전 순의 암호를 만든다.
- 조합을 만드는 함수에서 선택한 문자가 모음인지 여부를 체크한다.
   -> 포함된 모음 수를 출력 전에 확인하여 모음 수, 자음 수 조건을 만족하는지 확인한다.
- 앞으로 선택해야할 문자 수와 선택할 수 있는 문자수를 비교하여 가망이 없으면 진행하지 않는다.

*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int L, C;
char letter[16];
vector <char> password;

void find_password(int idx, int vowel) {
	if (password.size() == L) { // 암호 생성 완료
		if (vowel >= 1 && L - vowel >= 2) { // 모음 개수, 자음 개수 조건 확인
			for (int i = 0; i < L; i++) {
				cout << password[i];
			}
			cout << '\n';
		}
		return;
	}

	for (int i = idx; i < C; i++) {
		if (L - password.size() > C - i) break; // prune
		password.push_back(letter[i]); 
		
    //선택한 문자가 모음인지 확인
    if (letter[i] == 'a' || letter[i] == 'e' || letter[i] == 'i' || letter[i] == 'o' || letter[i] == 'u') {
			find_password(i + 1, vowel+1);
		}
		else find_password(i+1, vowel);
    
		password.pop_back();
	}
	return;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> L >> C;
	for (int i = 0; i < C; i++) {
		cin >> letter[i];
	} 
	sort(letter, letter + C);
	find_password(0, 0);

	return 0;
}
