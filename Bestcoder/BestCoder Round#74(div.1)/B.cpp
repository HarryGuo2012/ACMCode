#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAX_N 40
#define MAX_M ((1<<17)+100)
#define INF (MAX_N*MAX_M+100)
using namespace std;

int T,n,m;
int a[MAX_N];

struct edge{
	int to,cost;
	edge(int t,int c):to(t),cost(c){}
	edge(){}
};

vector<edge> G[MAX_M];

bool vis[MAX_M];
queue<int> qu;
void bfs(){
	qu.push(0);
	while(qu.size()){
		int u=qu.front();
		qu.pop();if(vis[u])continue;
		vis[u]=1;
		for(int i=1;i<=n;i++){
			int v=u^a[i];
			G[u].push_back(edge(v,1));
			G[v].push_back(edge(u,1));
			if(!vis[v])
				qu.push(v);
		}
		for(int i=0;i<17;i++){
			int v=u^(1<<i);
			G[u].push_back(edge(v,1));
			G[v].push_back(edge(u,1));
			if(!vis[v])qu.push(v);
		}
	}
}

int d[MAX_M];//最短路

struct node{
	int u,c;
	node(int uu,int cc):u(uu),c(cc){}
	node(){}
	bool operator<(const node &a)const {
		return c>a.c;
	}
};
priority_queue<node> que;
//最短路算法，s是起点
void dijkstra() {
    while (que.size())que.pop();
    fill(d, d + MAX_M, INF);
    que.push(node(0, 0));
    d[0] = 0;
    while (que.size()) {
        node now = que.top();
        que.pop();
        int u = now.u, c = now.c;
        if (d[u] < c)continue;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].to;
            if (d[v] > d[u] + G[u][i].cost) {
                d[v] = d[u] + G[u][i].cost;
                que.push(node(v, d[v]));
            }
        }
    }
}

typedef long long ll;

int main(){
	cout<<(99999^12345)<<endl;
	scanf("%d",&T);
	while(T--){
		ll sum=0;
		memset(vis,0,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=0;i<MAX_M;i++)G[i].clear();
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		bfs();//cout<<"***"<<endl;
		dijkstra();
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			sum=(sum+(ll)d[u^v]*i%1000000007)%1000000007;
		}
		printf("%I64d\n",sum);
	}
	return 0;
}