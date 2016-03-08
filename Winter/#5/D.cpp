#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 534
#define MAX_M 51234
using namespace std;

typedef long long ll;

int father[MAX_N];
bool used[MAX_M];

struct edge{
	public:
		int from,to;
		long long cost;
		edge(int f,int t,ll c):from(f),to(t),cost(c){}
		edge(){}
};

edge E[MAX_M];

bool cmp(edge a,edge b){
	return a.cost<b.cost;
}

int n,m;

void init(){
	for(int i=0;i<=n;i++)
		father[i]=i;
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

vector<int> treeEdge;

int Kruskal(bool firstTime){
	init();
	ll res=0;
	for(int i=0;i<m;i++){
		if(used[i])continue;
		int u=E[i].from,v=E[i].to;
		if(Same(u,v))continue;
		unionSet(u,v);
		res+=E[i].cost;
		if(firstTime)treeEdge.push_back(i);
	}	
	return res;
}

int main(){
	while(scanf("%d%d",&n,&m)==2){
		memset(used,0,sizeof(used));
		treeEdge.clear();
		for(int i=0;i<m;i++){
			int u,v;
			long long c;
			scanf("%d%d%lld",&u,&v,&c);
			E[i]=edge(u,v,c);
		}
		sort(E,E+m,cmp);
		ll tot=Kruskal(1);
		int x=0;
		ll y=0;
		for(int i=0;i<treeEdge.size();i++){
			used[treeEdge[i]]=1;
			ll tmp=Kruskal(0);
			if(tmp!=tot)
				x++,y+=E[treeEdge[i]].cost;
			used[treeEdge[i]]=0;
		}
		printf("%d %lld\n",x,y);
	}
	return 0;
}
