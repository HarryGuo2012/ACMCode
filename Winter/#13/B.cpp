#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
#define MAX_N 11
#define MAX_S (1<<MAX_N)
using namespace std;

double dp[MAX_N][MAX_S];
vector<int> G[MAX_N];

int n,m;

struct node{
	int cnt,val;
	node(int c,int v):cnt(c),val(v){}
	node(){}
};

vector<node> ones;

int getOnes(int x){
	int res;
	while(x){
		if(x&1)res++;
		x>>=1;
	}
	return res;
}

bool cmp(node a,node b){
	return a.cnt<b.cnt;
}

bool g[MAX_N][MAX_N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		u--,v--;
		G[u].push_back(v);
		G[v].push_back(u);
		g[u][v]=g[v][u]=1;
	}
	for(int i=0;i<(1<<n);i++){
		if(getOnes(i)>1)
			ones.push_back(node(getOnes(i),i));
	}
	ones.push_back(node(1,1));
	sort(ones.begin(),ones.end(),cmp);
	for(int i=ones.size()-2;i>=0;i--){
		int s=ones[i].val;
		for(int u=0;u<n;u++){
			if(((s>>u)&1)==0)continue;
			for(int v=0;v<n;v++){
				if(g[u][v]==0)continue;
				if((s>>v)&1)continue;
				int t=s+(1<<v);
				dp[u][s]+=1.0+dp[v][t]/(double)G[u].size();
			}
		}
	}
	printf("%.6f\n",dp[0][1]);
	cin>>n;
	return 0;
}