#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 555
#define MAX_D 22

int N;

int a[MAX_N];

std::vector<int> G[MAX_N];

int depth[MAX_N];
int father[MAX_N];
int ancestor[MAX_N][MAX_D];

void dfs(int u,int p) {
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == p)continue;
        depth[v] = depth[u] + 1;
        ancestor[v][0] = u;
        dfs(v, u);
    }
}

void getAncestor() {
    for (int j = 1; j < MAX_D; j++)
        for (int i = 1; i <= N; i++)
            ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
}

int LCA(int u,int v) {
    if (depth[u] < depth[v])std::swap(u, v);
    for (int i = MAX_D - 1; i >= 0; i--) {
        if (depth[ancestor[u][i]] >= depth[v]) {
            u = ancestor[u][i];
            if (depth[u] == depth[v])break;
        }
    }
    if (u == v)return u;
    for (int i = MAX_D - 1; i >= 0; i--) {
        if (ancestor[u][i] != ancestor[v][i]) {
            u = ancestor[u][i];
            v = ancestor[v][i];
        }
    }
    return ancestor[u][0];
}

int getDis(int u,int v) {
    int L = LCA(u, v);
    return depth[u] + depth[v] - 2 * depth[L];
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) 
		scanf("%d", &a[i]);
	for (int i = 1; i < N; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	getAncestor();
	long long ans = 0;
	for (int i = 1; i <= N; i++) 
		for (int j = 1; j < i; j++) 
			if (i != j && std::__gcd(a[i], a[j]) == 1) {
				ans = ans + getDis(i, j);
			}
	printf("%lld\n", ans);
	return 0;
}