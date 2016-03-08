#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#define INF INT_MAX
#define MAX_N 1003
using namespace std;

typedef long long ll;

struct edge{
	int to;
	ll cost;
	int h;
	edge(int tt,int hh,ll cc):to(tt),h(hh),cost(cc){}
	edge(){}
};

vector<edge> G[MAX_N];
queue<int> que;
bool inQue[MAX_N];
ll d[MAX_N];

ll spfa(int s,int t,int nh){
	while(que.size())que.pop();
	memset(inQue,0,sizeof(inQue));
	for(int i=0;i<MAX_N;i++)
		d[i]=INF;
	d[s]=0;
	que.push(s);
	inQue[s]=1;
	while(que.size()){
		int u=que.front();
		que.pop();
		inQue[u]=0;
		for(int i=0;i<G[u].size();i++){
			if(G[u][i].h<nh)continue;
			int v=G[u][i].to;
			if(d[v]>d[u]+G[u][i].cost){
				d[v]=d[u]+G[u][i].cost;
				if(!inQue[v]){
					que.push(v);
					inQue[v]=1;
				}
			}
		}
	}
	return d[t];
}

int n,m;

int S,T;
int Lim;

bool flag=false;

int main(){
	int cas=0;
	while(scanf("%d%d",&n,&m)==2){
		if(n==0&&m==0)break;
		if(flag)puts("");
		flag=true;
		for(int i=0;i<=n;i++)
			G[i].clear();
		for(int i=0;i<m;i++){
			int u,v;
			ll c;
			int h;
			scanf("%d%d%d%lld",&u,&v,&h,&c);
			if(h==-1)h=INF;
			G[u].push_back(edge(v,h,c));
			G[v].push_back(edge(u,h,c));
		}
		scanf("%d%d%d",&S,&T,&Lim);
		int L=0,R=Lim+1;
		ll ans=-1;
		printf("Case %d:\n",++cas);
		if(spfa(S,T,0)==INF){
			printf("cannot reach destination\n");
			continue;
		}
		while(R-L>1){
			int mid=(R+L)/2;
			ll tmp=spfa(S,T,mid);
			if(tmp!=INF){
				ans=tmp;
				L=mid;
			}
			else R=mid;
		}
		if(ans==-1)ans=spfa(S,T,0);
		printf("maximum height = %d\nlength of shortest route = %lld\n",L,ans);
	}
	return 0;
}