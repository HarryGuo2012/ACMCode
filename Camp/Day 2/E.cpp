#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
#define MAX_N 200005
#define MAX_D 55
using namespace std;

int father[MAX_N];
bool vis[MAX_N];
struct edge{
	int u,v;
	edge(int uu,int vv):u(uu),v(vv){}
	edge(){}
};

const long long mod=1000000007;

int n,m;

vector<edge> allEdge[MAX_D];

void init(){
	for(int i=0;i<=n;i++)vis[i]=0;
	for(int i=0;i<MAX_D;i++)allEdge[i].clear();
}

void init0(int nn){
	for(int i=0;i<=nn;i++)father[i]=i;
}

int Find(int x){
	if(x==father[x])return x;
	return father[x]=Find(father[x]);
}

void unionSet(int x,int y){
	int u=Find(x),v=Find(y);
	if(u==v)return;
	father[u]=v;
}

bool Same(int x,int y){
	return Find(x)==Find(y);
}

void add_edge(int u,int v,int k){
	allEdge[k].push_back(edge(u,v));
}

void Kruskal(int k){
	init0(min(2*m+2,MAX_N));
	for(int i=0;i<allEdge[k].size();i++){
		edge e=allEdge[k][i];
		int u=e.u,v=e.v;
		if(Same(u,v))continue;
		unionSet(u,v);
		int t=k-1;
		add_edge(u,v,t);
		add_edge(u+(1<<t),v+(1<<t),t);
	}
}

typedef long long ll;

ll Pow(ll a,int x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return res;
}

int main(){
	while(scanf("%d%d",&n,&m)==2){
		init();
		for(int i=1;i<=m;i++){
			int u,v,L;
			scanf("%d%d%d",&u,&v,&L);
			int k=0;
			while((1<<k)<=L)k++;
			k--;
			add_edge(u,v,k);
			add_edge(u+L-(1<<k),v+L-(1<<k),k);
		}
		for(int i=MAX_D-1;i>=0;i--)
			Kruskal(i);
		init0(n);
		for(int i=0;i<allEdge[0].size();i++){
			edge e=allEdge[0][i];
			int u=e.u,v=e.v;
			unionSet(u,v);
		}
		int cnt=0;
		for(int i=1;i<=n;i++)
			vis[Find(i)]=1;
		for(int i=1;i<=n;i++)cnt+=vis[i];
		printf("%I64d\n",Pow(26,cnt));
	}
	return 0;
}