#include<cassert>
#include<set>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

struct Point {
	int x, y;

	Point (const int &x = 0, const int &y = 0): x(x), y(y) {}

	void in() {
		scanf("%d%d", &x, &y);
	}

	bool operator < (const Point &b) const {
		return x < b.x || (x == b.x && y < b.y);
	}

	bool operator == (const Point &b) const {
		return x == b.x && y == b.y;
	}
};

const int N = 20005, P = 5000005, M = P << 2;

int top, m;

Point p[P];

struct Segment {
	Point a, b;
	vector<int> ps;
	bool isVer;

	void in() {
		a.in(), b.in();
		if (!(a < b)) {
			swap(a, b);
		}
		isVer = a.x == b.x;
	}

	bool isOn(const Point &p) {
		if (isVer) {
			return p.x == a.x && a.y <= p.y && p.y <= b.y;
		} else {
			return p.y == a.y && a.x <= p.x && p.x <= b.x;
		}
	}
};

int n;

Segment s[N];

Point st, gl;

struct Grid {
	int x0, y0, x1, y1;
	vector<int> b;

	bool isIn(const Point &p) {
		return x0 <= p.x && p.x <= x1 && y0 <= p.y && p.y <= y1;
	}
};

vector<Grid> g;

const int INF = 1000000005;

void addPoint(const int &i, const int &pt) {
	if (s[i].ps.size() == 0 && !(p[pt] == s[i].a)) {
		p[top] = s[i].a;
		addPoint(i, top++);
	}
	s[i].ps.push_back(pt);
}

int newCrossPoint(const int &h, const int &v) {
	p[top] = Point(s[v].a.x, s[h].a.y);
	int u = top++;
	addPoint(h, u);
	addPoint(v, u);
	return u;
}

void newEndPoint(const int &u) {
	if (s[u].ps.size() > 0 && p[s[u].ps.back()] == s[u].b) {
		return;
	}
	p[top] = s[u].b;
	addPoint(u, top++);
}

void buildGrid(vector<int> &hori, set<pair<int, int> > &vert) {
	if (hori.size() == 0 || vert.size() == 0) {
		return;
	}
	if (hori.size() == 1) {
		for (set<pair<int, int> >::iterator it = vert.begin(); it != vert.end(); ++it) {
			newCrossPoint(hori[0], it->second);
		}
	} else {
		if (vert.size() == 1) {
			int v = vert.begin()->second;
			for (int i = 0; i < (int)hori.size(); ++i) {
				newCrossPoint(hori[i], v);
			}
		} else {
			Grid g;
			int left = vert.begin()->second,
				right = vert.rbegin()->second,
				down = hori[0],
				up = hori.back();
			g.x0 = s[left].a.x;
			g.x1 = s[right].a.x;
			g.y0 = s[down].a.y;
			g.y1 = s[up].a.y;
			for (set<pair<int, int> >::iterator it = vert.begin(); it != vert.end(); ++it) {
				g.b.push_back(newCrossPoint(down, it->second));
			}
			for (int i = 1; i + 1 < (int)hori.size(); ++i) {
				g.b.push_back(newCrossPoint(hori[i], left));
				g.b.push_back(newCrossPoint(hori[i], right));
			}
			for (set<pair<int, int> >::iterator it = vert.begin(); it != vert.end(); ++it) {
				g.b.push_back(newCrossPoint(up, it->second));
			}
			::g.push_back(g);
		}
	}
}

bool intersect(const int &l1, const int &r1, const int &l2, const int &r2) {
	return max(l1, l2) <= min(r1, r2);
}

bool byX(const int &i, const int &j) {
	return s[i].a.x < s[j].a.x;
}

void buildStrip(int l, int r, vector<pair<int, int> > &evts) {
	vector<int> hori;
	set<pair<int, int> > vert;
	for (int i = 0; i < (int)evts.size(); ++i) {
		int cury = evts[i].first;
		vector<int> addhori, freehori, newvert, delvert;
		{
			int j = i;
			while (j < (int)evts.size() && evts[j].first == cury) {
				int id = evts[j].second, rid = id < 0 ? -id - 1 : id;
				if (s[rid].isVer) {
					if (id >= 0) {
						newvert.push_back(rid);
					} else {
						delvert.push_back(rid);
					}
				} else {
					if (s[id].a.x <= l && r <= s[id].b.x) {
						addhori.push_back(rid);
					} else {
						freehori.push_back(rid);
					}
				}
				++j;
			}
			i = j - 1;
		}
		if (addhori.size() + freehori.size() + newvert.size() + delvert.size() > 0) {
			if (freehori.size() + newvert.size() + delvert.size() == 0) {
				for (int j = 0; j < (int)addhori.size(); ++j) {
					hori.push_back(addhori[j]);
				}
			} else if (freehori.size() + newvert.size() == 0) {
				for (int j = 0; j < (int)addhori.size(); ++j) {
					hori.push_back(addhori[j]);
				}
				buildGrid(hori, vert);
				hori.clear();
				for (int j = 0; j < (int)delvert.size(); ++j) {
					int u = delvert[j];
					newEndPoint(u);
					vert.erase(make_pair(s[u].a.x, u));
				}
			} else {
				buildGrid(hori, vert);
				hori.clear();
				for (int j = 0; j < (int)addhori.size(); ++j) {
					hori.push_back(addhori[j]);
				}
				for (int j = 0; j < (int)newvert.size(); ++j) {
					int u = newvert[j];
					vert.insert(make_pair(s[u].a.x, u));
				}
				if (freehori.size() + delvert.size() == 0) {
					continue;
				} else if (freehori.size() == 0) {
					buildGrid(hori, vert);
					hori.clear();
				} else {
					sort(freehori.begin(), freehori.end(), byX);
					int j = 0;
					for (set<pair<int, int> >::iterator it = vert.begin(); it != vert.end() && j < (int)freehori.size(); ++it) {
						int x = it->first, u = it->second, v = freehori[j];
						while (j < (int)freehori.size() && x > s[v].b.x) {
							newEndPoint(v);
							++j;
							if (j < (int)freehori.size()) {
								v = freehori[j];
							}
						}
						if (j == (int)freehori.size()) {
							break;
						}
						if (x < s[v].a.x) {
							continue;
						} else if (x <= s[v].b.x) {
							newCrossPoint(v, u);	
						}
					}
					while (j < (int)freehori.size()) {
						int v = freehori[j];
						if (s[v].b.x <= r) {
							newEndPoint(v);
						}
						++j;
					}
				}
				for (int j = 0; j < (int)delvert.size(); ++j) {
					int u = delvert[j];
					newEndPoint(u);
					vert.erase(make_pair(s[u].a.x, u));
				}
			}
		}
	}
}

void buildVertex() {
	vector<pair<int, int> > evts;
	for (int i = 0; i < n; ++i) {
		if (s[i].isVer) {
			evts.push_back(make_pair(s[i].a.y, i));
			evts.push_back(make_pair(s[i].b.y, -(i + 1)));
		} else {
			evts.push_back(make_pair(s[i].a.y, i));
		}
	}
	sort(evts.begin(), evts.end());
	vector<int> vxs;
	for (int i = 0; i < n; ++i) {
		if (s[i].isVer) {
			vxs.push_back(s[i].a.x + 1);
		}
	}
	if (vxs.size() == 0) {
		buildStrip(-INF, INF, evts);
	} else {
		sort(vxs.begin(), vxs.end());
		vxs.erase(unique(vxs.begin(), vxs.end()), vxs.end());
		vector<int> cuts;
		cuts.push_back(-INF);
		cuts.push_back(vxs[0] - 1);
		int l = (int)ceil(sqrt(vxs.size()));
		for (int i = l; i < (int)vxs.size(); i += l) {
			cuts.push_back(vxs[i]);
		}
		if (cuts.back() != vxs.back()) {
			cuts.push_back(vxs.back());
		}
		cuts.push_back(INF);
		vector<vector<pair<int, int> > > cutevts(cuts.size());
		for (int i = 0; i < (int)evts.size(); ++i) {
			int id = evts[i].second, rid = id < 0 ? -id - 1 : id;
			if (s[rid].isVer) {
				int x = s[rid].a.x, pos = lower_bound(cuts.begin(), cuts.end(), x) - cuts.begin();
				cutevts[pos].push_back(evts[i]);
			} else {
				int posl = lower_bound(cuts.begin(), cuts.end(), s[rid].a.x) - cuts.begin(),
					posr = lower_bound(cuts.begin(), cuts.end(), s[rid].b.x) - cuts.begin();
				for (int j = posl; j <= posr; ++j) {
					cutevts[j].push_back(evts[i]);
				}
			}
		}
		for (int i = 1; i < (int)cutevts.size(); ++i) {
			buildStrip(cuts[i - 1], cuts[i], cutevts[i]);
		}
	}
}

#define next NEXT
int ttop, head[P], to[M], next[M];

long long len[M];

inline long long manDis(const Point &a, const Point &b) {
	return (long long)abs(a.x - b.x) + abs(a.y - b.y);
}

inline long long manDis(const int &i, const int &j) {
	return manDis(p[i], p[j]);
}

void addEdge(int u, int v) {
	to[ttop] = v, next[ttop] = head[u], len[ttop] = manDis(u, v), head[u] = ttop++;
}

void buildEdge() {
	ttop = 0;
	memset(head, -1, sizeof(head));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j + 1 < (int)s[i].ps.size(); ++j) {
			int u = s[i].ps[j], v = s[i].ps[j + 1];
			addEdge(u, v);
			addEdge(v, u);
		}
	}
}

long long dis[P];

bool byP(const int &i, const int &j) {
	return p[i] < p[j];
}

const long long LLINF = 1ll << 60;

long long calcDist() {
	int stn, gln;
	p[stn = top++] = st;
	p[gln = top++] = gl;
	for (int i = 0; i < top; ++i) {
		dis[i] = LLINF;
	}
	dis[stn] = 0;
	priority_queue<pair<long long, int> > heap;
	heap.push(make_pair(-dis[stn], stn));
	bool fst = false, fgl = false;
	for (int i = 0; i < n; ++i) {
		if (s[i].isOn(st)) {
			if (s[i].isOn(gl)) {
				return manDis(st, gl);
			}
			fst = true;
			int l = lower_bound(s[i].ps.begin(), s[i].ps.end(), stn, byP) - s[i].ps.begin();
			int u = s[i].ps[l];
			if (p[u] == st) {
				addEdge(stn, u);
			} else {
				addEdge(stn, u);
				int v = s[i].ps[l - 1];
				addEdge(stn, v);
			}
		}
		if (s[i].isOn(gl)) {
			fgl = true;
			int l = lower_bound(s[i].ps.begin(), s[i].ps.end(), gln, byP) - s[i].ps.begin();
			int u = s[i].ps[l];
			if (p[u] == gl) {
				addEdge(u, gln);
			} else {
				addEdge(u, gln);
				int v = s[i].ps[l - 1];
				addEdge(v, gln);
			}
		}
	}
	if (!fst || !fgl) {
		return -1ll;
	}
	for (int i = 0; i < (int)g.size(); ++i) {
		if (g[i].isIn(st)) {
			if (g[i].isIn(gl)) {
				return manDis(st, gl);
			}
			for (int j = 0; j < (int)g[i].b.size(); ++j) {
				int u = g[i].b[j];
				addEdge(stn, u);
			}
		}
		if (g[i].isIn(gl)) {
			for (int j = 0; j < (int)g[i].b.size(); ++j) {
				int u = g[i].b[j];
				addEdge(u, gln);
			}
		}
	}
	while (heap.size()) {
		long long d = -heap.top().first;
		int u = heap.top().second;
		heap.pop();
		if (dis[u] != d) {
			continue;
		}
		if (u == gln) {
			break;
		}
		for (int i = head[u]; ~i; i = next[i]) {
			int v = to[i];
			long long nd = dis[u] + len[i];
			if (dis[v] > nd) {
				dis[v] = nd;
				if (dis[v] + manDis(v, gln) < dis[gln]) {
					heap.push(make_pair(-dis[v], v));
				}
			}
		}
	}
	return dis[gln] == LLINF ? -1ll : dis[gln];
}

int main() {
	top = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		s[i].in();
	}
	st.in();
	gl.in();
	buildVertex();
	buildEdge();
	long long ans = calcDist();
	cout << ans << endl;
	return 0;
}