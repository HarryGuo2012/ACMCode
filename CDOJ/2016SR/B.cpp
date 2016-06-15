#include <iostream>
#include <queue>
#include <cstring>

#define MAX_N 55

struct node {
	int x, y, z;
	node(int xx, int yy, int zz) : x(xx), y(yy), z(zz) {}
	node() {}
};

char G[MAX_N][MAX_N][MAX_N];
int d[MAX_N][MAX_N][MAX_N];
int n, m, H;

std::queue<node> que;

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int bfs(node s, node t) {
	que.push(s);
	d[s.x][s.y][s.z] = 0;
	while (que.size()) {
		node now = que.front();
		que.pop();
		int x = now.x, y = now.y, z = now.z;
		if (G[x][y][z] != 'x') {
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (nx >= 1 && ny >= 1 && nx <= n && ny <= m && d[nx][ny][z] == -1 && G[nx][ny][z] != 'x') {
					d[nx][ny][z] = d[x][y][z] + 1;
					que.push(node(nx, ny, z));
				}
			}
		}
		if (G[x][y][z] == 'U' && z + 1 <= H && G[x][y][z + 1] != 'x' && d[x][y][z + 1] == -1) {
			d[x][y][z + 1] = d[x][y][z] + 1;
			que.push(node(x, y, z + 1));
		}
		if (G[x][y][z] == 'D' && z - 1 >= 1 && G[x][y][z - 1] != 'x' && d[x][y][z - 1] == -1) {
			d[x][y][z - 1] = d[x][y][z] + 1;
			que.push(node(x, y, z - 1));
		}
	}
	return d[t.x][t.y][t.z];
}

int main() {
	std::cin >> H >> n >> m;
	node s, t;
	for (int h = 1; h <= H; h++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				std::cin >> G[i][j][h];
				if (G[i][j][h] == 'X') s = node(i, j, h);
				if (G[i][j][h] == 'Y') t = node(i, j, h);
			}
		}
	}
	memset(d, -1, sizeof(d));
	std::cout << bfs(s, t) << std::endl;
	return 0;
}