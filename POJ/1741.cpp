#include<iostream>
#include<climits>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#include<cstdio>
#define MAX_N 10004
using namespace std;

struct edge{
public:
    int to,length;
    edge(int t,int l):to(t),length(l){}
    edge(){}
};

int N,K;

vector<edge> G[MAX_N];

bool centroid[MAX_N];
int subtree_size[MAX_N];

int ans;

int compute_subtree_size(int v,int p){
    int c=1;
    for(int i=0;i<G[v].size();i++){
        int w=G[v][i].to;
        if(w==p||centroid[w])continue;
        c+=compute_subtree_size(G[v][i].to,v);
    }
    subtree_size[v]=c;
    return c;
}

pair<int,int> search_centroid(int v,int p,int t){
    pair<int,int> res=make_pair(INT_MAX,-1);
    int s=1,m=0;
    for(int i=0;i<G[v].size();i++){
        int w=G[v][i].to;
        if(w==p||centroid[w])continue;

        res=min(res,search_centroid(w,v,t));

        m=max(m,subtree_size[w]);
        s+=subtree_size[w];
    }
    m=max(m,t-s);
    res=min(res,make_pair(m,v));
    return res;
}

void enumeratr_paths(int v,int p,int d,vector<int> &ds){
    ds.push_back(d);
    for(int i=0;i<G[v].size();i++){
        int w=G[v][i].to;
        if(w==p||centroid[w])continue;
        enumeratr_paths(w,v,d+G[v][i].length,ds);
    }
}

int count_pairs(vector<int> &ds){
    int res=0;
    sort(ds.begin(),ds.end());
    int j=ds.size();
    for(int i=0;i<ds.size();i++){
        while(j>0&&ds[i]+ds[j-1]>K)--j;
        res+=j-(j>i?1:0);
    }
    return res/2;
}

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

bool input(){
    if(scanf("%d%d",&N,&K)!=2||N+K==0)return false;
    for(int i=0;i<=N;i++)G[i].clear();
    for(int i=0;i<N-1;i++){
        int u,v;
        int c;
        scanf("%d%d",&u,&v);
        scanf("%d",&c);
        u--,v--;
        G[u].push_back(edge(v,c));
        G[v].push_back(edge(u,c));
    }
    return true;
}

int main(){
    while(input()){
        ans=0;
        memset(subtree_size,0,sizeof(subtree_size));
        memset(centroid,0,sizeof(centroid));
        solve();
    }
    return 0;
}
