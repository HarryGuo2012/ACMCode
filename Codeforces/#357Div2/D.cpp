#include <cstdio>
#include <vector>

#define MAX_N 100005

int luck[MAX_N];
std::vector<int> G[MAX_N];
std::vector<int> ans;
bool flag = false;

bool vis[MAX_N];

void dfs(int u, int now) {
	vis[u] = 1;
	if (flag) return;
	if (now && luck[u]) {
		flag = true;
		return;
	}
	if (luck[u]) now = luck[u] - 1;
	else if (now) now--;
	for (auto v : G[u])
		dfs(v, now);
	if (luck[u]) ans.push_back(u);
}

bool f[MAX_N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) f[i] = 1;
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		f[v] = 0;
	}
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		luck[a]++;
	}
	for (int i = 1; i <= n; i++) 
		if ((!vis[i]) && (!flag) && f[i])
			dfs(i, 0);
	if (flag)
		printf("-1\n");
	else {
		printf("%d\n", ans.size());
		for (auto u : ans)
			printf("%d\n", u);
	}
	return 0;
}