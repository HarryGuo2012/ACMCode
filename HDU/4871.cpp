#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<queue>
#define INF 600000008
#define MAX_N 30004
using namespace std;

struct edge{
	int to,cost;
	edge(int t,int c):to(t),cost(c){}
	edge(){}
};

struct dijNode{
	int v,c,p;
	dijNode(int vv,int cc,int pp):v(vv),c(cc),p(pp){}
	dijNode(){}
	friend bool operator<(const dijNode &a,const dijNode &b)const{
		if(a.c==b.c)
			return a.v>b.v;
		else
			return a.c<b.c;
	}
};

int N,M,K;

vector<edge> G[MAX_N];
vector<edge> T[MAX_N];

priority_queue<dijNode> que;
int dis[MAX_N];

void dijkstra(){
	while(que.size())que.pop();
	for(int i=0;i<MAX_N;i++){
		T[i].clear();
		dis[i]=INF;
	}

	que.push(dijNode(1,0,0));
	dis[1]=0;
	while(que.size()){
		dijNode now=que.top();
		que.pop();
		int u=now.v,c=now.c;
		if(dis[u]<c)continue;
		if(u!=1){
			T[u].push_back(edge(now.p,dis[u]-dis[now.p]));
			T[now.p].push_back(edge(u,dis[u]-dis[now.p]));
		}
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].to;
			if(dis[v]>dis[u]+G[u][i].cost){
				pre[v]=G[u][i];
				dis[v]=dis[u]+G[u][i].cost;
				que.push(dijNode(v,dis[v],u));
			}
		}
	}
}

bool centroid[MAX_N];
int subtree_size[MAX_N];

int ans;

int compute_subtree_size(int v,int p){
    int c=1;
    for(int i=0;i<T[v].size();i++){
        int w=T[v][i].to;
        if(w==p||centroid[w])continue;
        c+=compute_subtree_size(T[v][i].to,v);
    }
    subtree_size[v]=c;
    return c;
}

pair<int,int> search_centroid(int v,int p,int t){
    pair<int,int> res=make_pair(INT_MAX,-1);
    int s=1,m=0;
    for(int i=0;i<T[v].size();i++){
        int w=T[v][i].to;
        if(w==p||centroid[w])continue;

        res=min(res,search_centroid(w,v,t));

        m=max(m,subtree_size[w]);
        s+=subtree_size[w];
    }
    m=max(m,t-s);
    res=min(res,make_pair(m,v));
    return res;
}

struct node{
	int cnt,val;
	node(int c,int v):cnt(c),val(v){}
	node(){}
};

void enumeratr_paths(int v,int p,int d,int c,vector<node> &ds){
    ds.push_back(node(c,d));
    for(int i=0;i<T[v].size();i++){
        int w=G[v][i].to;
        if(w==p||centroid[w])continue;
        enumeratr_paths(w,v,d+T[v][i].cost,c+1,ds);
    }
}

void update

void solve_subproblem(int v){
    compute_subtree_size(v,-1);
    int s=search_centroid(v,-1,subtree_size[v]).second;
    centroid[s]=1;

    for(int i=0;i<G[s].size();i++){
        if(centroid[G[s][i].to])continue;
        solve_subproblem(G[s][i].to);
    }

    vector<int> ds;
    ds.push_back(0);
    for(int i=0;i<G[s].size();i++){
        if(centroid[G[s][i].to])continue;

        vector<int> tds;
        enumeratr_paths(G[s][i].to,s,G[s][i].length,tds);

        ans-=count_pairs(tds);
        ds.insert(ds.end(),tds.begin(),tds.end());
    }
    ans+=count_pairs(ds);
    centroid[s]=false;
}

void solve(){
    ans=0;
    solve_subproblem(0);
    printf("%d\n",ans);
}

int main(){
	return 0;
}
