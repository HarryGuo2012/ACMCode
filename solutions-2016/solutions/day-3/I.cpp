#include<cassert>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[8] = {2, 1, 2, -1, 1, -2, -1, -2},
		  dy[8] = {1, 2, -1, 2, -2, 1, -2, -1};

const int N = 1005 + 1;

bool vis[N][N];

int n, m, t;

vector<pair<int, int> > ans;

int dis[N][N];

int bfs(int x, int y) {
	vector<pair<int, int> > q;
	q.push_back(make_pair(x, y));
	dis[x][y] = 0;
	vis[x][y] = true;
	for (int i = 0; i < (int)q.size() && !vis[n][m]; ++i) {
		int x = q[i].first, y = q[i].second;
		for (int j = 0; j < 8; ++j) {
			int tx = x + dx[j], ty = y + dy[j];
			if (tx > 0 && tx <= n && ty > 0 && ty <= m && !vis[tx][ty]) {
				q.push_back(make_pair(tx, ty));
				dis[tx][ty] = dis[x][y] + 1;
				vis[tx][ty] = true;
			}
		}
	}
	int ret = vis[n][m] ? dis[n][m] : t + 1;
	for (int i = 0; i < (int)q.size(); ++i) {
		int x = q[i].first, y = q[i].second;
		vis[x][y] = false;
	}
	return ret;
}

bool go(int x, int y, int c) {
	if (bfs(x, y) + c > t) {
		return false;
	}
	if (n == x && y == m && c == t) {
		ans.push_back(make_pair(x, y));
		return true;
	} else if ((n == x && y == m) || c == t) {
		return false;
	}
	vis[x][y] = true;
	for (int i = 0; i < 8; ++i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (tx > 0 && tx <= n && ty > 0 && ty <= m && !vis[tx][ty]) {
			if (go(tx, ty, c + 1)) {
				ans.push_back(make_pair(x, y));
				return true;
			}
		}
	}
	vis[x][y] = false;
	return false;
}

const int SMAP1[4][4] = {
	{1, 12, 7, 10},
	{6, 9, 4, 15},
	{13, 2, 11, 8},
	{-1, 5, 14, 3}
};

const int SMAP2r[4][4] = {
	{12, 1, 8, 5},
	{7, 4, 11, 14},
	{2, 13, 6, 9},
	{-1, 10, 3, -1}
};

const int SMAP2d[4][4] = {
	{-1, 1, 8, 13},
	{11, 14, 5, 2},
	{4, 7, 12, 9},
	{15, 10, 3, 6}
};

const int SMAP3l[4][4] = {
	{5, 8, 1, -1},
	{14, 11, 4, 7},
	{9, 6, 13, 2},
	{12, 3, 10, -1}
};

const int SMAP3d[4][4] = {
	{13, 8, 1, -1},
	{2, 5, 14, 11},
	{9, 12, 7, 4},
	{6, 3, 10, 15}
};

vector<pair<int, int> > state1, state2r, state2d, state3l, state3d;

void record(const int map[4][4], vector<pair<int, int> > &state) {
	for (int id = 1; id <= 16; ++id) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (map[i][j] == id) {
					state.push_back(make_pair(i, j));
				}
			}
		}
	}
}

void init() {
	record(SMAP1, state1);
	state1.push_back(make_pair(0, 5));
	record(SMAP2r, state2r);
	state2r.push_back(make_pair(0, 5));
	record(SMAP2d, state2d);
	state2d.push_back(make_pair(4, 2));
	record(SMAP3l, state3l);
	state3l.push_back(make_pair(0, -2));
	record(SMAP3d, state3d);
	state3d.push_back(make_pair(4, 1));
}

int cur, state, cx, cy, bar;

vector<pair<int, int> > ansp;

void perform(const vector<pair<int, int> > &delta) {
	int ox = cx - delta[0].first, oy = cy - delta[0].second;
	for (int i = 1; i < (int)delta.size() && t - cur > bar; ++i) {			
		cx = ox + delta[i].first, cy = oy + delta[i].second;
		assert(cx >= 1 && cx <= n && cy >= 1 && cy <= m && !vis[cx][cy]);
		ansp.push_back(make_pair(cx, cy));
		vis[cx][cy] = true;
		++cur;
	}
}

void performConstruction() {
	while (t - cur > bar) {
		if (n - cx <= 6 && m - cy <= 6) {
			break;
		}
		if (state == 1) {
			perform(state1);
			state = 2;
		} else if (state == 2) {
			if (cy + 6 <= m) {
				perform(state2r);
			} else {
				perform(state2d);
				state = 3;
			}
		} else if (state == 3) {
			if (cy - 6 >= 1) {
				perform(state3l);
			} else {
				perform(state3d);
				state = 2;
			}
		}
	}
}

void performSearch() {
	go(cx, cy, cur);
	ans.pop_back();
	reverse(ans.begin(), ans.end());
	ans.insert(ans.begin(), ansp.begin(), ansp.end());
}

int main() {
	init();
	scanf("%d%d%d", &n, &m, &t);
	vis[cx][cy] = true;
	cur = 0, state = 1, cx = 1, cy = 1, bar = (n + m) / 2.5 + 7;
	performConstruction();
	performSearch();
	for (int i = 0; i < (int)ans.size(); ++i) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}