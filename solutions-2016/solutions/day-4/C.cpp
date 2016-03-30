#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <numeric>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 200000;

int weight[N], match_x[N], match_y[N], timestamp, visited[N], parent[N], via[N];
std::vector<int> graph[N], rgraph[N];

bool by_weight(int i, int j) {
    return weight[i] > weight[j];
}

bool find(int u) {
    if (visited[u] == timestamp) {
        return false;
    }
    visited[u] = timestamp;
    for (int v : graph[u]) {
        if (match_y[v] == -1) {
            match_x[u] = v;
            match_y[v] = u;
            return true;
        }
    }
    for (int v : graph[u]) {
        if (find(match_y[v])) {
            match_x[u] = v;
            match_y[v] = u;
            return true;
        }
    }
    return false;
}

void dfs(int u) {
    visited[u] = timestamp;
    for (int v : graph[u]) {
        int w = match_y[v];
        if (w != -1 && visited[w] != timestamp) {
            parent[w] = u;
            via[w] = v;
            dfs(w);
        }
    }
}

void rdfs(int u) {
    visited[u] = timestamp;
    if (match_x[u] != -1) {
        for (int v : rgraph[match_x[u]]) {
            if (visited[v] != timestamp) {
                parent[v] = u;
                via[v] = match_x[u];
                rdfs(v);
            }
        }
    }
}

int main() {
    timestamp = 0;
    memset(visited, -1, sizeof(visited));
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", weight + i);
    }
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        graph[a].push_back(b);
        rgraph[b].push_back(a);
    }
    memset(match_x, -1, sizeof(match_x));
    memset(match_y, -1, sizeof(match_y));
    int sum = 0;
    {
        std::vector<int> order(n);
        std::iota(ALL(order), 0);
        std::sort(ALL(order), by_weight);
        memset(match_x, -1, sizeof(match_x));
        memset(match_y, -1, sizeof(match_y));
        timestamp ++;
        for (int v : order) {
            if (weight[v] < 0) {
                break;
            }
            if (find(v)) {
                sum += weight[v];
                timestamp ++;
            }
        }
    }
    while (q --) {
        int u, w;
        scanf("%d%d", &u, &w);
        u --;
        timestamp ++;
        do {
            if (match_x[u] == -1) {
                weight[u] = w;
                if (w < 0) {
                    continue;
                }
                if (find(u)) {
                    sum += weight[u];
                } else {
                    timestamp ++;
                    dfs(u);
                    int best = u;
                    for (int v = 0; v < n; ++ v) {
                        if (visited[v] == timestamp && weight[v] < weight[best]) {
                            best = v;
                        }
                    }
                    if (best != u) {
                        match_x[best] = -1;
                    }
                    for (int p = best; p != u; p = parent[p]) {
                        match_y[via[p]] = parent[p];
                        match_x[parent[p]] = via[p];
                    }
                    sum += weight[u] - weight[best];
                }
            } else {
                sum += w - weight[u];
                weight[u] = w;
                rdfs(u);
                int best = u;
                for (int v = 0; v < n; ++ v) {
                    if (visited[v] == timestamp && match_x[v] == -1 && weight[v] > weight[best]) {
                        best = v;
                    }
                }
                if (weight[best] <= 0) {
                    sum -= weight[u];
                    match_y[match_x[u]] = -1;
                    match_x[u] = -1;
                } else {
                    for (int p = best; p != u; p = parent[p]) {
                        match_x[p] = via[p];
                        match_y[via[p]] = p;
                    }
                    if (best != u) {
                        match_x[u] = -1;
                    }
                    sum += weight[best] - weight[u];
                }
            }
        } while (false);
        printf("%d\n", sum);
    }
    return 0;
}
