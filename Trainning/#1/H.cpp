#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX_V 11111
#define MAX_N 11111
#define INF 2500005
using namespace std;

struct edge{int to,cap,rev;bool isRev;};

vector<edge> G[MAX_N];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from,int to,int cap) {
    G[from].push_back((edge) {to, cap, (int)G[to].size(),0});
    G[to].push_back((edge) {from, 0, (int)G[from].size() - 1,1});
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

int N, M, S, T;

int Hash(int x, int y){
    return x * 101 + y;
}

bool vis[111][111];

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        if(N + M == 0) break;
        S = MAX_V - 1, T = MAX_V - 2;
        memset(vis, 0, sizeof(vis));
        memset(iter, 0, sizeof(iter));
        memset(level, 0, sizeof(level));
        for(int i = 0; i < MAX_N; i++)
            G[i].clear();
        for(int i = 1; i <= N; i++){
            int x, y;
            scanf("%d%d", &x, &y);
            if(vis[x][y]) continue;
            vis[x][y] = 1;
            int u = Hash(x, y), v = Hash(x + 1, y);
            if((x + y) & 1)
                swap(u, v);
            add_edge(u, v, 1);
        }
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= M; i++){
            int x, y;
            scanf("%d%d", &x, &y);
            if(vis[x][y]) continue;
            vis[x][y] = 1;
            int u = Hash(x, y), v = Hash(x, y + 1);
            if((x + y) & 1)
                swap(u, v);
            add_edge(u, v, 1);
        }
        for(int i = 0; i <= 100; i++)
            for(int j = 0; j <= 100; j++){
                if((i + j) & 1)
                    add_edge(Hash(i, j), T, 1);
                else
                    add_edge(S, Hash(i, j), 1);
            }
        printf("%d\n", max_flow(S, T));
    }
    return 0;
}