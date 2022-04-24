#include <iostream>
#include <queue>
using namespace std;

struct state {
	int x;
	int y;
	int dist;
};
struct cmp {
	bool operator()(state a, state b) {
		if (a.dist == b.dist) {
			if (a.x == b.x) {
				return a.y > b.y;
			}
			else return a.x > b.x;
		}
		else return a.dist > b.dist;
	}
};
int dx[4] = { 0,0,1,-1 };
int dy[4] = { -1,1,0,0 };

int N, M, F;
int a, b, c, d;
int map[21][21];

int guest[21][21];
pair<int, int> dest[410];
pair<int, int> taxi;

bool visited[21][21];
priority_queue<state, vector<state>, cmp> pq;


state find_guest(int x, int y) {
	state selected_guest = { -1,-1,-1 };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = false;
		}
	}
	while (!pq.empty()) pq.pop();

	pq.push({ x, y, 0 });
	visited[x][y] = true;

	while (!pq.empty()) {
		state curr = pq.top(); pq.pop();
		if (guest[curr.x][curr.y] != 0) {
			selected_guest = curr;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx <= 0 || nextx > N || nexty <= 0 || nexty > N || visited[nextx][nexty] == true || map[nextx][nexty] == 1) {
				continue;
			}
			else {
				visited[nextx][nexty] = true;
				pq.push({ nextx, nexty, curr.dist + 1 });
			}
		}
	}
	
	return selected_guest;
}

state move_to_dest(int x, int y, int guest_num) {
	state arrived_dest = { -1,-1,-1 };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visited[i][j] = false;
		}
	}
	while (!pq.empty()) pq.pop();

	int destx = dest[guest_num].first;
	int desty = dest[guest_num].second;
	pq.push({ x, y, 0 });
	visited[x][y] = true;

	while (!pq.empty()) {
		state curr = pq.top(); pq.pop();
		if (curr.x == destx && curr.y == desty) {
			arrived_dest = curr;
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nextx = curr.x + dx[i];
			int nexty = curr.y + dy[i];
			if (nextx <= 0 || nextx > N || nexty <= 0 || nexty > N || visited[nextx][nexty] == true || map[nextx][nexty] == 1) {
				continue;
			}
			else {
				visited[nextx][nexty] = true;
				pq.push({ nextx, nexty, curr.dist + 1 });
			}
		}
	}
	return arrived_dest;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> F;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	cin >> taxi.first >> taxi.second;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c >> d;
		guest[a][b] = i;
		dest[i] = { c, d };
	}
	
	while (M > 0) {
		state selected_guest = find_guest(taxi.first, taxi.second);
		if (selected_guest.dist == -1 || F-selected_guest.dist<=0)  break;
		F -= selected_guest.dist;
		
		int guest_num = guest[selected_guest.x][selected_guest.y];
		guest[selected_guest.x][selected_guest.y] = 0;

		state arrived_dest = move_to_dest(selected_guest.x, selected_guest.y, guest_num);
		
		if (arrived_dest.dist == -1 || F-arrived_dest.dist<0) break;
		F += arrived_dest.dist;

		taxi = { arrived_dest.x , arrived_dest.y };
		M--;
	}
	if (M > 0) cout << -1;
	else cout << F;

	return 0;
}
