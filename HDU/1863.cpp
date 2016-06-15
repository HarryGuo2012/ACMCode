#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_N 103

struct edge {
	int to;
	long long cost;
	edge(int tt, long long cc) : to(tt), cost(cc) {}
	edge() {}
	bool operator< (const edge &a) const {
		return a.cost < cost;
	}
};

std::priority_queue<edge> que;
std::vector<edge> G[MAX_N];
bool vis[MAX_N];
int N, M;

long long prim() {
	long long res = 0;
	vis[1] = 1;
	for (int i = 0; i < G[1].size(); i++)
		que.push(G[1][i]);
	while (que.size()) {
		edge e = que.top();
		que.pop();
		if (vis[e.to]) continue;
		vis[e.to] = 1;
		res += e.cost;
		for (int i = 0; i < G[e.to].size(); i++)
			que.push(G[e.to][i]);
	}
	return res;
}

int main() {
	while (scanf("%d%d", &M, &N) == 2) {
		if (M == 0) break;
		for (int i = 0; i <= N; i++)
			G[i].clear();
		while (que.size()) que.pop();
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= M; i++) {
			int u, v;
			long long cost;
			scanf("%d%d%lld", &u, &v, &cost);
			G[u].push_back(edge(v, cost));
			G[v].push_back(edge(u, cost));
		}
		long long res = prim();
		for (int i = 1; i <= N; i++)
			if (!vis[i]) res = -1;
		if (res == -1)
			printf("?\n");
		else
			printf("%lld\n", res);
	}
	return 0;
}