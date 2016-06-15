#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 555
#define INF 12345678912345

int N;

struct edge {
	int to, cost;
	edge(int tt, int cc) : to(tt), cost(cc) {}
	edge(){}
};

std::vector<edge> G[MAX_N];
int siz[MAX_N];
typedef long long ll;
ll dp[MAX_N][MAX_N][2];

void update(ll &x, ll a) {
	x = std::min(x, a);
}

void dfs(int u, int p) {
	siz[u] = 1;
	for (auto e : G[u]) {
		int v = e.to, c = e.cost;
		if (v == p) continue;
		dfs(v, u);
		siz[u] += siz[v];
		for (int j = siz[u]; j >= 1; j--)
			for (int t = 0; t <= std::min(siz[v], j); t++) {
				update(dp[u][j][1], dp[u][j - t][1] + (dp[v][t][1] + 2 * c) * (t > 0));
				update(dp[u][j][0], dp[u][j - t][1] + (dp[v][t][0] + c) * (t > 0));
				update(dp[u][j][0], dp[u][j - t][0] + (dp[v][t][1] + 2 * c) * (t > 0));
				//printf("%d %d %lld %lld\n", u, j, dp[u][j][1], dp[u][j][0]);
			}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		u++, v++;
		G[u].push_back(edge(v, d));
		G[v].push_back(edge(u, d));
	}
	for (int i = 1; i <= N; i++)
		for (int j = 2; j <= N; j++) 
			for (int k = 0; k < 2; k++)
				dp[i][j][k] = INF;
	dfs(1, 0);
	int q;
	scanf("%d", &q);
	while (q--) {
		int M;
		scanf("%d", &M);
		int ans = 0;
		for (int j = 1; j <= N; j++)
		if (dp[1][j][0] <= M)
			ans = j;
		printf("%d\n", ans);
	}
	return 0;
}