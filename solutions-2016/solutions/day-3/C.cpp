#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300 + 5;
const int DEBUG = 0;

struct Point
{
	long long x, y;
	Point() {}
	Point(long long x, long long y) : x(x), y(y) {}
	int operator < (const Point &that) const {
		return x < that.x;
	}
};

struct Angle
{
	long long x, y;
	int which, from, to;
	Angle() {}
	Angle(long long x, long long y, int which, int from, int to) : x(x), y(y), which(which), from(from), to(to) {}
};

long long cross(long long xs, long long ys, long long xa, long long ya, long long xb, long long yb)
{
	return (xa - xs) * (yb - ys) - (xb - xs) * (ya - ys);
}

long long area(long long xs, long long ys, long long xa, long long ya, long long xb, long long yb)
{
	return abs(cross(xs, ys, xa, ya, xb, yb));
}

int operator < (const Angle &a, const Angle &b)
{
	long long delta = cross(0, 0, a.x, a.y, b.x, b.y);
	if (delta) return delta > 0;
	if (a.which == b.which) return a.from < b.from;
	return false;
}

long long n, d;
vector<Point> up, down;
vector<Angle> angles;
long long dp_up[N][N][N], dp_down[N][N][N];
int nxt[N * N >> 1][N], cur[N];

void update(long long &a, long long b)
{
	a = max(a, b);
}

void go(int u, int v, int t, long long x)
{
	if (t == angles.size()) return;
	if (angles[t].which == 0) {
		if (DEBUG) cout << "GO UP " << u << ' ' << angles[t].to << ' ' << v << ' ' << x << endl;
		update(dp_up[u][angles[t].to][v], x);
	} else {
		if (DEBUG) cout << "GO DOWN " << v << ' ' << angles[t].to << ' ' << u << ' ' << x << endl;
		update(dp_down[v][angles[t].to][u], x);
	}
}

long long dist(const Point &u, const Point &v)
{
	return (u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y);
}

void solve()
{
	cin >> n >> d;
	for(int i = 0; i < n; ++ i) {
		long long x, y;
		cin >> x >> y;
		if (y == 0) continue;
		if (x * x + y * y > d * d) continue;
		if ((x - d) * (x - d) + y * y > d * d) continue;
		if (y > 0) {
			up.push_back(Point(x, y));
		} else {
			down.push_back(Point(x, y));
		}
	}
	if (up.size() + down.size() == 0) {
		cout << 0 << endl;
		return;
	}

	up.push_back(Point(0, 0)); up.push_back(Point(d, 0));
	sort(up.rbegin(), up.rend());
	for(int i = 0; i < up.size(); ++ i) {
		for(int j = i + 1; j < up.size(); ++ j) {
			if (up[j].x < up[i].x) {
				angles.push_back(Angle(up[i].x - up[j].x, up[i].y - up[j].y, 0, i, j));
			}
		}
	}
	if (DEBUG) {
		cout << up.size() << endl;
		for(int i = 0; i < up.size(); ++ i) {
			cout << up[i].x << ' ' << up[i].y << endl;
		}
	}
	down.push_back(Point(0, 0)); down.push_back(Point(d, 0));
	sort(down.begin(), down.end());
	for(int i = 0; i < down.size(); ++ i) {
		for(int j = i + 1; j < down.size(); ++ j) {
			if (down[j].x > down[i].x) {
				angles.push_back(Angle(down[j].x - down[i].x, down[j].y - down[i].y, 1, i, j));
			}
		}
	}
	if (DEBUG) {
		cout << down.size() << endl;
		for(int i = 0; i < down.size(); ++ i) {
			cout << down[i].x << ' ' << down[i].y << endl;
		}
	}

	sort(angles.begin(), angles.end());

	if (DEBUG) {
		cout << angles.size() << endl;
		for(int i = 0; i < angles.size(); ++ i) {
			cout << angles[i].which << ' ' << angles[i].from << ' ' << angles[i].to << endl;
		}
	}

	for(int i = 0; i < down.size() + up.size(); ++ i) {
		cur[i] = angles.size();
	}
	for(int i = angles.size() - 1; i >= 0; -- i) {
		for(int j = 0; j < down.size() + up.size(); ++ j) {
			nxt[i][j] = cur[j];
		}
		if (angles[i].which == 0) {
			cur[angles[i].from] = i;
		} else {
			cur[angles[i].from + up.size()] = i;
		}
	}
	
	memset(dp_up, -1, sizeof dp_up);
	memset(dp_down, -1, sizeof dp_down);

	for(int i = 1; i < up.size(); ++ i) {
		dp_up[0][i][0] = 0;
	}
	for(int i = 1; i < down.size(); ++ i) {
		dp_down[0][i][0] = 0;
	}
	long long ret = 0;
	for(int i = 0; i < angles.size(); ++ i) {
		int u1 = angles[i].from;
		int u2 = angles[i].to;
		if (angles[i].which == 0) {
			if (u2 == up.size() - 1) {
				update(ret, dp_up[u1][u2][down.size() - 1]);
			}
			for(int v = 0; v < down.size(); ++ v) {
				if (dp_up[u1][u2][v] < 0) continue;
				if (DEBUG) cout << "NOW IS UP " << u1 << ' ' << u2 << ' ' << v << ' ' << dp_up[u1][u2][v] << endl;
				{
					int j = min(nxt[i][u1], nxt[i][v + up.size()]);
					go(u1, v, j, dp_up[u1][u2][v]);
				}
				if (dist(up[u2], down[v]) <= d * d) {
					int j = min(nxt[i][u2], nxt[i][v + up.size()]);
					go(u2, v, j, dp_up[u1][u2][v] + area(0, 0, up[u1].x, up[u1].y, up[u2].x, up[u2].y));
				}
			}
		} else {
			if (u2 == down.size() - 1) {
				update(ret, dp_down[u1][u2][up.size() - 1]);
			}
			for(int v = 0; v < up.size(); ++ v) {
				if (dp_down[u1][u2][v] < 0) continue;
				if (DEBUG) cout << "NOW IS DOWN " << u1 << ' ' << u2 << ' ' << v << ' ' << dp_down[u1][u2][v] << endl;
				{
					int j = min(nxt[i][u1 + up.size()], nxt[i][v]);
					go(v, u1, j, dp_down[u1][u2][v]);
				}
				if (dist(down[u2], up[v]) <= d * d) {
					int j = min(nxt[i][u2 + up.size()], nxt[i][v]);
					go(v, u2, j, dp_down[u1][u2][v] + area(d, 0, down[u1].x, down[u1].y, down[u2].x, down[u2].y));
				}
			}
		}
	}
	cout << ret << endl;
}

int main()
{
	solve();
	return 0;
}
