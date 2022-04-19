
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
