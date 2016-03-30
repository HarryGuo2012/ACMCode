//#include <iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<string>
#include<cmath>
#define MAX_V 555
#define MAX_N MAX_V
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

void init(){
    for(int i=0;i<MAX_V;i++)
        G[i].clear();
    memset(dist,0,sizeof(dist));
    memset(prevv,0,sizeof(prevv));
    memset(preve,0,sizeof(preve));
}

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

int n,k,m,P,Q;
int p[MAX_N];
int s[MAX_N],t[MAX_N];
int Te;

int main(){
    scanf("%d",&Te);
    while(Te--){
        init();
        scanf("%d%d",&n,&k);
        int sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&p[i]);
            sum+=p[i];
        }
        scanf("%d%d%d",&m,&P,&Q);
        for(int i=1;i<=m;i++)
            scanf("%d%d",&s[i],&t[i]);
        V=2*n+6;
        int S=2*n+1,T=2*n+2,BP=2*n+3,AP=2*n+4;
        for(int i=1;i<=n;i++){
            add_edge(i,i+n,p[i],0);
            add_edge(BP,i,INF,0);
            if(i>P)add_edge(AP,i,INF,0);
            for(int j=1;j<=m;j++){
                int tmp=i+t[j];
                for(int x=tmp;x<=n;x++)
                    add_edge(i+n,x,INF,s[j]);
            }
            add_edge(i+n,T,INF,0);
        }
        add_edge(S,BP,k,0);
        add_edge(S,AP,INF,Q);
        printf("%d\n",min_cost_flow(S,T,sum));
    }
    return 0;
}
