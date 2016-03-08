#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#define MAX_N 555
using namespace std;

vector<int> G[MAX_N];
bool vis[MAX_N];
void dfs(int x,int deep){
	if(deep%2)
		cout<<x<<" ";
	vis[x]=1;
	for(int i=0;i<G[x].size();i++)if(!vis[G[x][i]])
		dfs(G[x][i],deep+1);
	if(deep%2==0)cout<<x<<" ";
}

int n;

vector<int> GG[MAX_N];

void dfs2(int u){
	vis[u]=1;
	for(int i=0;i<GG[u].size();i++){
		int v=GG[u][i];
		if(vis[v])continue;
		G[u].push_back(v);
		G[v].push_back(u);
		dfs2(v);
	}
}
int K;

int main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			char c;
			cin>>c;
			if(c=='1')GG[i].push_back(j),GG[j].push_back(i);
		}
	dfs2(1);
	memset(vis,0,sizeof(vis));
	dfs(1,0);
	return 0;
}