#include <cstdio>
#include <vector>

#define MAX_N 100005

std::vector<int> G[MAX_N];
std::vector<int> ans;
bool flag = false;

bool vis[MAX_N];

int now = 0;
int b[MAX_N];

void dfs(int u) {
    vis[u] = 1;
    for (auto v : G[u]) {
        dfs(v);
        if (!vis)
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) 
        scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) 
        if ((!vis[i]) && (!flag)) {
            b[0] = i;
            dfs(0, i);
    if (flag)
        printf("-1\n");
    else {
        printf("%d\n", ans.size());
        for (auto u : ans)
            printf("%d\n", u);
    }
    return 0;
}