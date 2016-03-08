#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#define MAX_N 100005
#define MAX_D 25
using namespace std;

vector<int> G[MAX_N];
int depth[MAX_N],father[MAX_N];
long long siz[MAX_N],dp[MAX_N],dp2[MAX_N];
int n,m;
int ancestor[MAX_N][MAX_D];

void dfs(int u,int p){
	siz[u]=1;
	depth[u]=depth[p]+1;
	father[u]=p;
	ancestor[u][0]=p;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		dfs(v,u);
		siz[u]+=siz[v];
		dp[u]+=dp[v]+siz[v];
	}
}

void dfs2(int u,int p){
	if(p==0)dp2[u]=dp[u];
	else dp2[u]=dp2[p]-siz[u]+siz[1]-siz[u];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		dfs2(v,u);
	}
}

void getAncestor(){
	for(int j=1;j<MAX_D;j++)
		for(int i=1;i<=n;i++)
			ancestor[i][j]=ancestor[ancestor[i][j-1]][j-1];
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

int LCA2(int u,int v){
	for(int i=MAX_D-1;i>=0;i--){
		if(depth[ancestor[u][i]]-1>=depth[v]){
			u=ancestor[u][i];
			if(depth[u]-1==depth[v])break;
		}
	}
	if(father[u]==v)return u;
	for(int i=MAX_D-1;i>=0;i--){
		if(ancestor[u][i]!=ancestor[v][i]){
			u=ancestor[u][i];
			v=ancestor[u][0];
		}
	}
	return u;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);dfs2(1,0);getAncestor();
	long long cnt=0;
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		if(depth[u]<depth[v])swap(u,v);
		int l=LCA(u,v);
		long long tot=0;
		if(l!=v){
			cnt=siz[v]*dp[u]+siz[u]*dp[v]+(siz[v]*siz[u])*(depth[u]-depth[l])+(siz[v]*siz[u])*(depth[v]-depth[l])+siz[u]*siz[v];
			tot=siz[v]*siz[u];
		}
		else{
			int t=LCA2(u,v);
			cnt=(siz[1]-siz[t])*dp[u]+siz[u]*(dp2[v]-dp[t]-siz[t])+(2+depth[u]-depth[t])*((siz[1]-siz[t])*siz[u]);
			tot=siz[u]*(siz[1]-siz[t]);
		}
		//cout<<cnt<<endl;
		printf("%.7f\n",cnt/(double)(tot));
	}
	return 0;
}
/*
10 100
1 2
2 3
2 5
2 4
5 6
5 7
1 8
8 9
8 10
*/