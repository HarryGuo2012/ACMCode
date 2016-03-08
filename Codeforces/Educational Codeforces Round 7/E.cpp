#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <climits>
#define MAX_N 500005
#define INF INT_MAX
using namespace std;

vector<int> G[MAX_N];
vector<int> dp[MAX_N];

int n;
int ans=0;

vector<int> tmp;

void dfs(int u,int p,int deep){
	bool isLeaf=true;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		isLeaf=false;
		dfs(v,u,deep+1);
	}
	if(isLeaf)
		tmp.push_back(deep);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=0;i<G[1].size();i++){
		int u=G[1][i];
		tmp.clear();
		dfs(u,1,1);
		sort(tmp.begin(),tmp.end());
		int now=tmp[0];
		for(int j=1;j<tmp.size();j++){
			if(now>=tmp[j])now=now+1;
			else now=tmp[j];
		}
		ans=max(ans,now);
	}
	cout<<ans<<endl;
	return 0;
}