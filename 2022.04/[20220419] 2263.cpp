/*

2022.04.19.
- 2263 트리의 순회: https://www.acmicpc.net/problem/2263
- 트리, 분할 정복, 재귀
- GoldⅡ

- 포스트오더에서 루트를 찾아내고, 인오더를 참고하여 루트를 기준으로 왼쪽 서브트리와 오른쪽 서브트리를 나눈다.
- 인오더는 노드의 인덱스(순서)를 저장하여 서브트리의 시작 인덱스와 종료 인덱스를 빨리 찾을 수 있도록 한다.
- 오른쪽 서브트리의 경우, 서브트리를 나눌 때 마다 인오더에서의 인덱스와의 차이가 발생하는 것을 보정해준다.

*/
#include <iostream>
#include <vector>
using namespace std;

int n, input;
int inorder_idx[100001];
int postorder[100001];
vector<int> preorder;


void pre_order(int s, int e, int num) {
	if (s > e) return;
	int node = postorder[e];
	preorder.push_back(node);

	// 중간에 위치한 노드값이 빠진 경우의 index 위치 보정
	int node_idx = inorder_idx[node] - num;

	// left subtree
	pre_order(s, node_idx-1, num);
	// right subtree
	pre_order(node_idx, e-1, num+1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) { //inorder는 번호로 index를 찾을 수 있게 저장
		cin >> input;
		inorder_idx[input] = i;
	}
	
	for (int i = 0; i < n; i++) {
		cin >> postorder[i];
	}
	pre_order(0, n - 1, 0);
	for (auto value : preorder) {
		cout << value << ' ';
	}
	return 0;
}
