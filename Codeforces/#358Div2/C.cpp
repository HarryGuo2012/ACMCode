#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 100005

struct edge {
	int to;
	long long cost;
	edge (int tt, long long cc) : to(tt), cost(cc) {}
	edge() {}
};

std::vector<edge> G[MAX_N];
long long a[MAX_N];

int siz[MAX_N], ans = 0;

void getSize(int u, int p) {
	siz[u] = 1;
	for (auto e : G[u]) {
		if (e.to != p) {
			getSize(e.to, u);
			siz[u] += siz[e.to];
		}
	}
}

void dfs(int u, int p, long long md) {
	if (md > a[u]) {
		ans += siz[u];
		return;
	}
	for (auto e : G[u]) {
		long long c = e.cost;
		int v = e.to;
		if (v != p)
			dfs(v, u, std::max(c, md + c));
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%I64d", &a[i]);
	for (int i = 1; i < n; i++) {
		int p;
		long long c;
		scanf("%d%I64d", &p, &c);
		G[i + 1].push_back(edge(p, c));
		G[p].push_back(edge(i + 1, c));
	}
	getSize(1, 0);
	dfs(1, 0, 0);
	printf("%d\n", ans);
	return 0;
}