#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX_V 222
#define MAX_N 222
#define INF 25000050
using namespace std;

struct edge{
    int to,cap,rev;
    bool isRev;
    edge(int t, int c, int r, bool i) : to(t), cap(c), rev(r), isRev(i) {}
    edge() {}
};

vector<edge> G[MAX_N];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from,int to,int cap) {
    G[from].push_back(edge(to, cap, G[to].size(),0));
    G[to].push_back(edge(from, 0, G[from].size() - 1,1));
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f) {
    if (v == t)return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s,int t) {
    int flow = 0;
    for (; ;) {
        bfs(s);
        if (level[t] < 0)return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}

int Gr[MAX_N][MAX_N];
int N, M, L;
int K[MAX_N], P[MAX_N];

void floyd() {
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                Gr[i][j] = std::min(Gr[i][j], Gr[i][k] + Gr[k][j]);
}

int S = MAX_N - 1, T = MAX_N - 2;

void build() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if(Gr[i][j] < L)
                add_edge(i, j + N, INF);
    for (int i = 1; i <= N; i++)
        add_edge(S, i, P[i]);
    for (int i = 1; i <= N; i++)
        add_edge(i + N, T, K[i]);
}

void init() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            Gr[i][j] = i == j ? 0 : INF;
    memset(level, 0, sizeof(level));
    memset(iter, 0, sizeof(iter));
    for (int i = 0; i < MAX_N; i++)
        G[i].clear();
}

int main() {
    while (scanf("%d%d%d", &N, &M, &L) == 3) {
        init();
        for (int i = 1; i <= M; i++) {
            int a, b, d;
            scanf("%d%d%d", &a, &b, &d);
            Gr[a][b] = d;
            Gr[b][a] = d;
        }
        for (int i = 1; i <= N; i++)
            scanf("%d", &P[i]);
        for (int i = 1; i <= N; i++)
            scanf("%d", &K[i]);
        floyd();
        build();
        printf("%d\n", max_flow(S,T));
    }
    return 0;
}