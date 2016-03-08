#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int T;
int V,E;

struct edge{
	int u,v,c;
	edge(int uu,int vv,int cc):u(uu),v(vv),c(cc){}
	edge(){}
};

bool cmp(edge a,edge b){
	return a.c<b.c;
}

vector<edge> eg;

int father[555];

void init(){
	for(int i=0;i<555;i++)
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

int Kruskal(){
	init();
	int res=0;
	sort(eg.begin(),eg.end(),cmp);
	for(int i=0;i<eg.size();i++){
		int u=eg[i].u,v=eg[i].v,c=eg[i].c;
		if(Same(u,v))continue;
		res+=c;
		unionSet(u,v);
	}
	return res;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&V,&E);
		eg.clear();
		for(int i=0;i<E;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			eg.push_back(edge(u,v,c));
		}
		printf("%d\n",Kruskal());
	}
	return 0;
}