#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <set>
#include <cstring>
#include <queue>

#define MAX_N 200005
#define INF MAX_N * 2

std::vector<int> G[MAX_N];
std::vector<int> T[MAX_N];
std::set<std::pair<int, int> > se;
int dfn[MAX_N], low[MAX_N], ind;
bool vis[MAX_N];

int id[MAX_N];

int tot = 0;
int N, M;

std::stack<int> st;

void Tarjan(int u, int p) {
	st.push(u);
    dfn[u] = low[u] = ++ind;
    vis[u] = 1;
    int cnt = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == p) {
        	cnt++;
        	if(cnt == 1) continue;
        }
        if (!vis[v]) {
            Tarjan(v,u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] > dfn[u]){ 
            	tot++;
            	while(st.size() && st.top() != v){
            		int t = st.top();
            		st.pop();
            		id[t] = tot;
            	}
            	id[st.top()] = tot;
            	st.pop();
            }
        }
        else
            low[u] = std::min(dfn[v], low[u]);
    }
}

int dis[MAX_N];
std::queue<int> que;
bool inQue[MAX_N];

std::pair<int, int> bfs(int s){
	std::fill(dis, dis + MAX_N, INF);
	while(que.size()) que.pop();
	memset(inQue, 0, sizeof(inQue));
	dis[s] = 0;
	que.push(s);
	inQue[s] = 1;
	while(que.size()){
		int u = que.front();
		que.pop();
		inQue[u] = 0;
		for(int i = 0; i < T[u].size(); i++){
			int v = T[u][i];
			if(dis[v] > dis[u] + 1){
				dis[v] = dis[u] + 1;
				if(!inQue[v]){
					que.push(v);
					inQue[v] = 1;
				}
			}
		}
	}
	int tmp = -1, pos;
	for(int i = 1; i <= tot; i++)
		if(dis[i] > tmp){
			tmp = dis[i];
			pos = i;
		}
	return std::make_pair(pos, tmp);
}

int main(){
	while(scanf("%d%d", &N, &M) == 2){
		if(N + M == 0) break;
		for(int i = 0; i < MAX_N; i++)
			G[i].clear();
		for(int i = 0; i < MAX_N; i++)
			T[i].clear();
		se.clear();
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
		ind = 0;
		memset(vis, 0, sizeof(vis));
		memset(id, 0, sizeof(id));
		tot = 0;
		while(st.size()) st.pop();
		while(M--){
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Tarjan(1, 0);
	
		for(int i = 1; i <= N; i++)
			for(int j = 0; j < G[i].size(); j++){
				int u = id[i] + 1, v = id[G[i][j]] + 1;
				if(u != v && se.find(std::make_pair(u, v)) == se.end() && se.find(std::make_pair(v, u)) == se.end()){
					T[u].push_back(v);
					T[v].push_back(u);
					se.insert(std::make_pair(u, v));
				}
			}
		tot++;
		std::pair<int, int> P = bfs(1);
		P = bfs(P.first);
		printf("%d\n", tot - 1 - P.second);
	}
	return 0;
}