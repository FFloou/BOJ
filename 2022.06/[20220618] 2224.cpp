/*

2022.06.18.
- 2224 명제증명: https://www.acmicpc.net/problem/2224
- 골드Ⅴ
- 그래프 이론, 플로이드-워셜

- 명제의 전건 후건을 하나의 간선으로 보고 플로이드-워셜로 각 조건에서 다른 조건으로 이동할 수 있는 경로를 확인
   -> 길이가 중요하지 않기 때문에 이동 가능하면 1로 통일(자기자신은 이동 가능하기 때문에 1로 초기화)
- cin의 경우 공백 이전까지의 값만 받아오고 개행 문자를 버퍼에 남겨두고 값을 가져온다.
  -> getline과 섞어 쓸 경우 버퍼에 남아있는 개행 문자를 처리해줘야한다.(cin.ignore(), cin.get()...)

  */
#include <iostream>
#include <vector>
using namespace std;

int graph[60][60];
char s[10];
int N, cnt;
vector<pair<char, char>> answer;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 60; i++) {
		graph[i][i] = 1;
	}

	cin >> N;
	cin.ignore();
	for (int i = 0; i < N; i++) {
		cin.getline(s, sizeof(s), '\n');
		graph[s[0] - 'A'][s[5] - 'A'] = 1;
	}

	for (int k = 0; k < 60; k++) {
		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 60; j++) {
				if (graph[i][k] == 1 && graph[k][j] == 1) graph[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			if (i == j) continue;
			if (graph[i][j] == 1) {
				answer.push_back({ char(i + 'A'), char(j + 'A') });
				cnt++;
			}
		}
	}
	cout << cnt << '\n';
	for (int i = 0; i < cnt; i++) {
		cout << answer[i].first << " => " << answer[i].second << '\n';
	}
	return 0;
}
