#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 100005
#define MAX_D 18
using namespace std;

struct edge{
	public:
		int to,cost;
		bool ci;
		edge(int t,int c):to(t),cost(c),ci(0){}
		edge(){}
};

vector<edge> G[MAX_N];

int na,nb,co;

bool vis[MAX_N];

bool flag=false;

void dfs(int u,int p){
	if(flag)return;
	vis[u]=1;
	int cnt=0;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to;
		if(v==p&&cnt==0){
			cnt++;
			continue;
		}
		if(vis[v]){
			na=u,nb=v,co=G[u][i].cost;
			G[u][i].ci=1;
			flag=true;
			break;
		}
		dfs(v,u);
	}
}
int n,q;

int ancestor[MAX_N][MAX_D];
int depth[MAX_N];

int dis[MAX_N];

void init(){
flag=false;
    memset(dis,0,sizeof(dis));
    memset(ancestor,0,sizeof(ancestor));
    memset(depth,0,sizeof(depth));
    for(int i=0;i<=n;i++)G[i].clear();
	memset(vis,0,sizeof(vis));
}

void dfs2(int u,int p) {
    for (int i = 0; i < G[u].size(); i++) {
		if(G[u][i].ci)continue;
        int v = G[u][i].to;
        if (v == p)continue;
        dis[v]=dis[u]+G[u][i].cost;
        depth[v] = depth[u] + 1;
        ancestor[v][0] = u;
        dfs2(v, u);
    }
}

void getAncestor() {
    for (int j = 1; j < MAX_D; j++)
        for (int i = 1; i <= n; i++)
            ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
}

int LCA(int u,int v) {
    if (depth[u] < depth[v])swap(u, v);
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
    return dis[u] + dis[v] - 2 * dis[L];
}

int main(){
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		init();
		for(int i=0;i<n;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			u++,v++;
			G[u].push_back(edge(v,c));
			G[v].push_back(edge(u,c));
		}
		dfs(1,0);
		dfs2(1,0);
		getAncestor();
		scanf("%d",&q);
		while(q--){
			int u,v;
			scanf("%d%d",&u,&v);
			u++,v++;
			int ans=min(getDis(u,v),min(getDis(u,na)+getDis(nb,v)+co,getDis(u,nb)+getDis(na,v)+co));
			printf("%d\n",ans);
		}
	}
	return 0;
}
