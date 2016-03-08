#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_N 100005
using namespace std;

typedef long long ll;

int N;
vector<int> T[MAX_N];

class SegmentTree{
public:
	class Node{
	public:
		ll lazy,sum;
	}tree[4*MAX_N];

	#define lchild L,m,v<<1
	#define rchild m+1,R,v<<1|1

	void initSeg(){
		for(int i=0;i<4*MAX_N;i++)tree[i].lazy=tree[i].sum=0;
	}
	
	void pushDown(int v,int L,int R){
		int m=(L+R)>>1;
		tree[v<<1].lazy+=tree[v].lazy;
		tree[v<<1|1].lazy+=tree[v].lazy;
		tree[v<<1].sum+=tree[v].lazy*(m-L+1);
		tree[v<<1|1].sum+=tree[v].lazy*(R-m);
		tree[v].lazy=0;
	}

	void pushUp(int v){
		tree[v].sum=tree[v<<1].sum+tree[v<<1|1].sum;
	}

	void Update(int a,int b,ll x,int L=1,int R=N,int v=1){
		if(a<=L&&R<=b){
			tree[v].sum+=x;
			tree[v].lazy+=x;
			return;
		}
		pushDown(v,L,R);
		int m=(L+R)>>1;
		Update(a,b,x,lchild);
		Update(a,b,x,rchild);
		pushUp(v);
	}

	ll Query(int a,int b,int L=1,int R=N,int v=1){
		if(a<=L&&R<=b)
			return tree[v].sum;
		pushDown(v,L,R);
		int m=(L+R)>>1;
		ll res=0;
		res+=Query(a,b,lchild);
		res+=Query(a,b,rchild);
		return res;
	}
};

class HLD:SegmentTree{
public:
	int dep[MAX_N],fa[MAX_N],sz[MAX_N];
	int son[MAX_N],top[MAX_N],dfn[MAX_N];
	int dfs_clock;

	void init(){
		memset(dep,0,sizeof(dep));
		memset(son,0,sizeof(son));
		dep[1]=1;
		dfs_clock=0;
		initSeg();
		dfs1(1),dfs2(1,1);
	}

	void dfs1(int u){
		sz[u]=1;
		for(int i=0;i<T[u].size();i++){
			int v=T[u][i];
			if(dep[v])continue;
			dep[v]=dep[u]+1;
			fa[v]=u;
			dfs1(v);
			sz[u]+=sz[v];
			if(sz[son[u]]<sz[v])
				son[u]=v;
		}
	}

	void dfs2(int u,int tp){
		top[u]=tp;
		dfn[u]=++dfs_clock;
		if(son[u])dfs2(son[u],tp);
		for(int i=0;i<T[u].size();i++){
			int v=T[u][i];
			if(v==fa[u]||v==son[u])continue;
			dfs2(v,v);
		}
	}

	ll getSum(int u,int v){
		ll ans=0;
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]])swap(u,v);
			ans+=Query(dfn[top[v]],dfn[v],0);
			v=fa[top[v]];
		}
		if(dep[u]>dep[v])swap(u,v);
		ans+=Query(dfn[u],dfn[v]);
		return ans;
	}

	void update(int u,int v,ll x){
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]])swap(u,v);
			Update(dfn[u],dfn[v],x);
			v=fa[top[v]];
		}
		if(dep[u]>dep[v])swap(u,v);
		Update(dfn[u],dfn[v],x);
	}
}hld;

int main(){
	scanf("%d",&N);
	for(int i=1;i<N;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		T[u].push_back(v);
		T[v].push_back(u);
	}
	hld.init();
	int M;
	scanf("%d",&M);
	while(M--){
		int q,a,b,x;
		scanf("%d%d%d",&q,&a,&b);
		if(q==0){
			cout<<hld.getSum(a,b)<<endl;
		}
		else{
			scanf("%d",&x);
			hld.Update(a,b,x);
		}
	}
	return 0;
}