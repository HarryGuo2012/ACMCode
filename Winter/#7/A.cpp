#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#define MAX_N 100005
using namespace std;

vector<int> G[MAX_N];
vector<int> rG[MAX_N];
int f[MAX_N];

int n,m;

bool canUsing[MAX_N];
bool canAss[MAX_N];

void dfs0(int u){
	canUsing[u]=1;
	if(f[u]==1)return;
	for(int i=0;i<rG[u].size();i++){
		int v=rG[u][i];
		if(canUsing[v])continue;
		dfs0(v);
	}
}

void dfs1(int u){
	canAss[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(canAss[v])continue;
		dfs1(v);
	}
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		rG[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(f[i]==2&&canUsing[i]==0)dfs0(i);
		if(f[i]==1&&canAss[i]==0)dfs1(i);
	}
	for(int i=1;i<=n;i++){
		int t=canAss[i]&canUsing[i];
		printf("%d\n",t);
	}
	return 0;
}