#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

int maxn;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 2e6 + 100;

struct dsu {
	int parent[N], rank[N];
	int cycles = 0;
	vector<pair<int*, int>> changes;

	dsu() {
		for (int i = 0; i < N; i++) {
			parent[i] = i;
		}
	}

	int findSet(int v) {
		return parent[v] != v ? findSet(parent[v]) : v;
	}

	void set(int *a, int b) {
		changes.pb(mp(a, *a));
		*a = b;
	}

	void unite(int a, int b) {
		a = findSet(a), b = findSet(b);
		if (a == b) {
			return void (set(&cycles, 1));
		}
		if (rank[a] == rank[b]) {
			set(rank + a, rank[a] + 1);
		}
		if (rank[a] > rank[b]) {
			swap(a, b);
		}
		set(parent + a, b);
	}

	void revert(int size) {
		while (len(changes) > size) {
			*changes.back().fs = changes.back().sc;
			changes.pbk();
		}
	}
};

int n, m;
dsu d;

vector<int> ans;
pair<int, int> e[N];
int l[N];

void solve(int ii, int l, int r) {
	if (d.cycles) {
		return ;
	}
	if (l == r) {
		if (!d.cycles) {
			ans.push_back(l);
		}
	} else {
		int len = len(d.changes);
		for (int z = ::l[(l + r) / 2 + 1]; z < ::l[r + 1]; z++) {
			int i = e[z].fs, j = e[z].sc;
			if (l <= j && j <= (l + r) / 2) {
				continue;
			}
			if ((l + r) / 2 + 1 <= j && j <= r && i > j) {
				continue;
			}
			d.unite(i, j);
		}
		solve(ii * 2, l, (l + r) / 2);
		d.revert(len);
		for (int z = ::l[l]; z < ::l[(l + r) / 2 + 1]; z++) {
			int i = e[z].fs, j = e[z].sc;
			if ((l + r) / 2 + 1 <= j && j <= r) {
				continue;
			}
			if (l <= j && j <= (l + r) / 2 && i > j) {
				continue;
			}
			d.unite(i, j);
		}
		solve(ii * 2 + 1, (l + r) / 2 + 1, r);
		d.revert(len);
	}
}

int main() {
	static int deg[N];
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b), a--, b--;
		e[i * 2] = mp(a, b);
		e[i * 2 + 1] = mp(b, a);
		deg[a] ^= 1;
		deg[b] ^= 1;
	}
	sort(e, e + m * 2);
	for (int i = 0; i < n; i++) {
		l[i] = lower_bound(e, e + m * 2, mp(i, -1)) - e;
	}
	l[n] = 2 * m;
	//for (int i = 0; i < n; i++) {
	//	sort(all(g[i]));
	//}
	for (int i = 0; i < n; i++) {
		if (deg[i] % 2 != 0) {
			puts("0");
			return 0;
		}
	}
	solve(1, 0, n - 1);
	printf("%d\n", len(ans));
	for (int i : ans) {
		printf("%d ", i + 1);
	}
	puts("");
    return 0;
}
