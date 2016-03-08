#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_N 200005
using namespace std;

vector<int> G[MAX_N];

typedef long long ll;

ll x,y;

int n;

ll dp[MAX_N][3];
vector<int> tmp;

vector<ll> dv;

void dfs(int u,int p){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		dfs(v,u);
	}

	tmp.clear();
	dv.clear();
	
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		tmp.push_back(max(dp[v][0],max(dp[v][1],dp[v][2])));
		dv.push_back(tmp[tmp.size()-1]-max(dp[v][0],dp[v][1]));
	}

	ll sum=0;
	for(int i=0;i<tmp.size();i++)sum+=tmp[i];

	dp[u][0]=sum;
	sort(dv.begin(),dv.end());
	int cnt=dv.size();
	if(cnt>=1)
		dp[u][1]=sum-dv[0]+1;
	if(cnt>=2)
		dp[u][2]=sum-dv[1]-dv[0]+2;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>x>>y;
	for(int i=0;i<n-1;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if(x>=y){
		bool flag=false;
		for(int i=1;i<=n;i++)
			flag|=(G[i].size()==(n-1));
		if(flag)cout<<(n-2)*y+x<<endl;
		else cout<<(n-1)*y<<endl;
		return 0;
	}
	dfs(1,0);
	ll t=max(dp[1][0],max(dp[1][1],dp[1][2]));
	cout<<t*x+(n-1-t)*y<<endl;
	//char cc;cin>>cc;
	return 0;
}