#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX_N 200005

struct edge{
	int to, val;
	edge(int tt, int vv):to(tt), val(vv){}
	edge(){}
	bool operator < (const edge &a) const {
		return val < a.val;
	}
};

bool cmp(edge a, edge b){
	if(a.val == b.val)
		return a.to < b.to;
	return a.val < b.val;
}

std::vector<edge> G[MAX_N];
int n;

int father[MAX_N], color[MAX_N];
int fail[MAX_N];
std::queue<int> que;

int at(int u){
	if(father[u] == 0)return 0;
	int v = -1;
	while(v != 0){
		v = fail[father[u]];
		auto it = std::lower_bound(G[v].begin(), G[v].end(), edge(0,color[u]));
		if(it == G[v].end() || it->val != color[u])continue;
		return it->to;
	}
	return 0;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &father[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &color[i]);
	for(int i = 1; i <= n; i++)
		G[father[i]].push_back(edge(i, color[i]));
	for(int i = 0; i <= n; i++)
		std::sort(G[i].begin(), G[i].end(), cmp);

	que.push(0);
	while(que.size()){
		int u = que.front();que.pop();
		fail[u] = at(u);
		for(auto v:G[u])
			que.push(v.to);
	}

	for(int i = 1; i <= n; i++)
		printf("%d%c", fail[i], (i == n ? '\n' : ' '));
	return 0;
}