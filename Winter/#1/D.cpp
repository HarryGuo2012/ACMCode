//#include <iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<string>
#include<cmath>
#define MAX_V 1050
#define INF 1008611
using namespace std;
struct edge {
public:
    int to, cap, cost, rev;
    bool isRev;

    edge(int t, int c, int co, int re,bool ir) : to(t), cap(c), cost(co), rev(re),isRev(ir) { }

    edge() { }
};
int V=0;
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];

void add_edge(int from,int to,int cap,int cost) {
    G[from].push_back(edge(to,cap,cost,G[to].size(),0));
    G[to].push_back(edge(from,0,-cost,G[from].size()-1,1));
}

char cc;
int min_cost_flow(int s,int t,int f) {
    int res = 0;
    while (f > 0) {
        fill(dist, dist + V, INF);
        dist[s] = 0;
        bool update = 1;
        while (update) {
            update = 0;
            for (int v = 0; v < V; v++) {
                if (dist[v] == INF)continue;
                for (int i = 0; i < G[v].size(); i++) {
                    edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                        //cout<<"*"<<endl;
                        dist[e.to] = dist[v] + e.cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        update = 1;
                    }
                }
            }
        }
        if (dist[t] == INF)
            return -1;

        int d = f;
        for (int v = t; v != s; v = prevv[v])
            d = min(d, G[prevv[v]][preve[v]].cap);
        f -= d;
        res += d * dist[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}

void init(){
	for(int i=0;i<MAX_V;i++)
		G[i].clear();
	memset(prevv,0,sizeof(prevv));
	memset(preve,0,sizeof(preve));
	memset(dist,0,sizeof(dist));
}

int N,A,B;

int S,T;

int main(){
	while(scanf("%d%d%d",&N,&A,&B)==3){
		if(N==0&&A==0&&B==0)break;
		init();
		V=N+10;
		S=0,T=N+3;
		int sum=0;
		for(int i=1;i<=N;i++){
			int k,da,db;
			scanf("%d%d%d",&k,&da,&db);
			add_edge(S,i,k,0);
			add_edge(i,N+1,INF,da);
			add_edge(i,N+2,INF,db);
			sum+=k;
		}
		add_edge(N+1,T,A,0);
		add_edge(N+2,T,B,0);
		printf("%d\n",min_cost_flow(S,T,sum));
	}
	return 0;
}
