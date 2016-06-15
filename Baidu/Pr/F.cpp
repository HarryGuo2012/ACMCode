#include <cstdio>
#include <queue>
#include <functional>
#include <cstring>
#include <vector>
#define INF 100005

std::priority_queue <int> que;

#define MAX_N 100005

std::vector<int> G[MAX_N];
int d[MAX_N];

int tree[MAX_N];

bool vis[MAX_N];

long long bfs() {
	int minNum = INF;
	long long ans = 0;
	while (que.size()) {
		int u = que.top();
		que.pop();
		//printf("%d\n", u);
		minNum = std::min(minNum, u);
		ans = ans + minNum;
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			d[v]--;
			if (d[v] == 0) 
				que.push(v);
		}
	}
	return ans;
}	

int main() {
	int T, N, M;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		memset(vis, 0, sizeof(vis));
		while (que.size()) que.pop();
		memset(d, 0, sizeof(d));
		for (int i = 0; i < MAX_N; i++)G[i].clear();
		scanf("%d%d", &N, &M);
		while (M--) {
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			d[v]++;
		}
		for (int i = 1; i <= N; i++)
			if (d[i] == 0) {
				vis[i] = 1;
				que.push(i);
			}
		printf("%lld\n", bfs());
	}
	return 0;
}