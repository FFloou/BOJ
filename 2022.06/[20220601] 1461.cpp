/*

2022.06.01.
- 1461 도서관: https://www.acmicpc.net/problem/1461
- 골드Ⅴ
- 그리디 알고리즘, 정렬

- 음수와 양수 좌표를 섞어서 방문하는 것은 양수와 음수 좌표를 따로 다녀오는 것과 이동거리가 같다. 
   (0 -> 양수 좌표 -> 0 -> 음수 좌표 -> 0) => 음수와 양수 좌표를 따로 저장하여 고려한다.
- 먼 점들은 한 번에 다녀오는 것이 이득이므로 먼 점들은 묶어서 방문한다.
   -> 거리 절대값 기준 내림차순 정렬하여 앞에서 부터 최대인 M개씩 묶어 방문한다.
- 가장 멀리 있는 점을 가장 뒤에 편도로 방문하는 것이 가장 이득이다.
   -> 방문해야하는 점들까지의 거리를 저장하고, 가장 먼 곳 까지의 거리만 한 번 더하고 나머지는 두 번 더한다.

*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;
int tmp;
int cnt;

vector<int> mv;
vector<int> pv;
vector<int> v;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		if (tmp > 0) pv.push_back(tmp);
		else mv.push_back(-tmp);
	}
	
	// 내림차순 정렬
	sort(pv.rbegin(), pv.rend());
	sort(mv.rbegin(), mv.rend());

	for (int i = 0; i < pv.size(); i += M) {
		v.push_back(pv[i]);
	}
	for (int j = 0; j < mv.size(); j += M) {
		v.push_back(mv[j]);
	}
	
	sort(v.begin(), v.end());

	int answer = v[v.size()-1];
	for (int i = 0; i < v.size() - 1; i++) {
		answer += (v[i] * 2);
	}
	cout << answer;
	return 0;
}
