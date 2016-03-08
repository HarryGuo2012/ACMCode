//找重心
//统计子树i的答案
//在子树i维护map
//i->i+1
//分治
#include <climits>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#define MAX_N 100005
using namespace std;

typedef long long ll;

vector<int> G[MAX_N];//tree

int n;
map<int,ll> ma;

bool centroid[MAX_N];
int subtree_size[MAX_N];


void input(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

int compute_subtree_size(int v,int p){
    int c=1;
    for(int i=0;i<G[v].size();i++){
        int w=G[v][i];
        if(w==p||centroid[w])continue;
        c+=compute_subtree_size(G[v][i],v);
    }
    subtree_size[v]=c;
    return c;
}

pair<int,int> search_centroid(int v,int p,int t){
    pair<int,int> res=make_pair(INT_MAX,-1);
    int s=1,m=0;
    for(int i=0;i<G[v].size();i++){
        int w=G[v][i];
        if(w==p||centroid[w])continue;

        res=min(res,search_centroid(w,v,t));

        m=max(m,subtree_size[w]);
        s+=subtree_size[w];
    }
    m=max(m,t-s);
    res=min(res,make_pair(m,v));
    return res;
}

ll ans=0;

void count_pair(int v,int p,int now){
	ans+=ma[now];
	for(int i=0;i<G[v].size();i++){
		int w=G[v][i];
		if(w==p||centroid[w])continue;
		count_pair(w,v,now^w);
	}
}

void maintain_map(int v,int p,int now){
	ma[now]++;
	for(int i=0;i<G[v].size();i++){
		int w=G[v][i];
		if(w==p||centroid[w])continue;
		maintain_map(w,v,now^w);
	}
}

void solve_subproblem(int v){
	compute_subtree_size(v,-1);
    int s=search_centroid(v,-1,subtree_size[v]).second;
    centroid[s]=1;

    for(int i=0;i<G[s].size();i++){
        if(centroid[G[s][i]])continue;
        solve_subproblem(G[s][i]);
    }
    /*------Algorithm in normal Tree-------*/
    ma.clear();
    ma[s]++;
    for(int i=0;i<G[s].size();i++){
    	int w=G[s][i];
    	if(centroid[w])continue;
    	count_pair(w,s,w);
    	maintain_map(w,s,w^s);
    }
    /*----------------END------------------*/
    centroid[s]=0;
}

void solve(){
	ans=0;
	solve_subproblem(1);
	printf("%lld\n",ans);
}

int main(){
	input();
	solve();
	cin>>n;
	return 0;
}