#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <queue>

#define MAX_N 1111

//+ - | ^ > < v L R U D *
//0 1 2 3 4 5 6 7 8 9 10 11

int change[11][4] = {
	{0, 0, 0, 0},
	{1, 2, 1, 2},
	{2, 1, 2, 1},
	{3, 4, 6, 5},
	{4, 6, 5, 3},
	{5, 3, 4, 6},
	{6, 5, 3, 4},
	{7, 9, 8, 10},
	{8, 10, 7, 9},
	{9, 8, 10, 7},
	{10, 7, 9, 8}
};

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

//+ - | ^ > < v L R U D *
//0 1 2 3 4 5 6 7 8 9 10 11

bool door[11][4] = {
	{1, 1, 1, 1},
	{1, 0, 1, 0},
	{0, 1, 0, 1},
	{0, 0, 0, 1},
	{1, 0, 0, 0},
	{0, 0, 1, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 1},
	{0, 1, 1, 1},
	{1, 1, 1, 0},
	{1, 0, 1, 1}
};

char table[12] = {'+', '-', '|', '^', '>', '<', 'v', 'L', 'R', 'U', 'D', '*'};

struct node {
	int x, y;
	int cnt;
	node (int xx, int yy, int cc) : x(xx), y(yy), cnt(cc) {}
	node () {}
};

int d[MAX_N][MAX_N][4];

std::queue<node> que;

char G[MAX_N][MAX_N];
int n, m;

int Get(char c) {
	int p = 0;
	while (table[p] != c) p++;
	return p;
}

void bfs(node s) {
	que.push(s);
	memset(d, -1, sizeof(d));
	d[s.x][s.y][s.cnt] = 0;
	while (que.size()) {
		node now = que.front();
		que.pop();
		if (d[now.x][now.y][(now.cnt + 1) % 4] == -1) {
			d[now.x][now.y][(now.cnt + 1) % 4] = d[now.x][now.y][now.cnt] + 1;
			que.push(node(now.x, now.y, (now.cnt + 1) % 4));
		}
		for (int i = 0; i < 4; i++) {
			int nx = now.x + dx[i], ny = now.y + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m || G[nx][ny] == '*' || d[nx][ny][now.cnt] != -1) continue;
			int u = change[Get(G[now.x][now.y])][now.cnt], v = change[Get(G[nx][ny])][now.cnt];
			if (door[u][i] && door[v][(i + 2) % 4]) {
				d[nx][ny][now.cnt] = d[now.x][now.y][now.cnt] + 1;
				que.push(node(nx, ny, now.cnt));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", G[i]);
	node s, t;
	scanf("%d%d", &s.x, &s.y);
	scanf("%d%d", &t.x, &t.y);
	s.x--;s.y--;
	s.cnt = 0;
	bfs(s);
	int ans = INT_MAX;
	for (int i = 0; i < 4; i++)
		if (d[t.x - 1][t.y - 1][i] != -1) ans = std::min(ans, d[t.x - 1][t.y - 1][i]);
	if (ans == INT_MAX)
		printf("-1\n");
	else
		printf("%d\n", ans);
	return 0;
}