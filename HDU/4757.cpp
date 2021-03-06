#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstdio>
#define MAX_N 100005
#define MAX_S 24
#define MAX_A 16
#define MAX_T 2000006
using namespace std;

vector<int> G[MAX_N];
int n,m;
int a[MAX_N];

int ancestor[MAX_N][MAX_S];
int deep[MAX_N];

struct LCA{
	LCA(){
		memset(ancestor,0,sizeof(ancestor));
		memset(deep,0,sizeof(deep));
		getAncestor();
	}
	void dfs(int u,int p){
		deep[u]=deep[p]+1;
		ancestor[u][0]=p;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==p)continue;
			dfs(v,u);
		}
	}
	void getAncestor(){
		dfs(1,0);
		for(int j=1;j<MAX_S;j++)
			for(int i=1;i<=n;i++)
				ancestor[i][j]=ancestor[ancestor[i][j-1]][j-1];
	}
	int getLca(int u, int v) {
        if (deep[u] < deep[v])swap(u, v);
        for (int i = MAX_S - 1; i >= 0; i--) {
            if (deep[ancestor[u][i]] >= deep[v]) {
                u = ancestor[u][i];
                if (deep[u] == deep[v])break;
            }
        }
        if (u == v)return u;
        for (int i = MAX_S - 1; i >= 0; i--) {
            if (ancestor[u][i] != ancestor[v][i]) {
                u = ancestor[u][i];
                v = ancestor[v][i];
            }
        }
        return ancestor[u][0];
    }	
}lca;


struct Node{
	int child[2];
	int cnt;
	Node(){
		memset(child,0,sizeof(child));
		cnt=0;
	}
};

Node tree[MAX_T];
int root[MAX_N],treeCnt;

struct Trie{
	Trie(){
		lca=LCA();
		for(int i=0;i<MAX_T;i++)tree[i]=Node();
		treeCnt=1;root[0]=0;
		build(1,0);
	}
	int insert(int u,int x){
		tree[treeCnt]=tree[u];
		int ret=u=treeCnt++;
		for(int i=15;i>=0;i--){
			int tmp=(x>>i)&1,t=treeCnt++;
			tree[t]=tree[tree[u].child[tmp]];
			tree[t].cnt++;
			tree[u].child[tmp]=t;
			u=t;
		}
		return ret;
	}
	void build(int u,int p){
		root[u]=insert(root[p],a[u]);
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(v==p)continue;
			build(v,u);
		}
	}
	int query(int u,int v,int K){
		int l=lca.getLca(u,v);
		int ans=a[l]^K;
		l=root[l],u=root[u],v=root[v];
		int tmp=0;
		for(int i=15;i>=0;i--){
			int now=(K>>i)&1;
			now^=1;
			int x=tree[tree[u].child[now]].cnt+tree[tree[v].child[now]].cnt-2*tree[tree[l].child[now]].cnt;
			if(x==0)now^=1;
			u=tree[u].child[now],v=tree[v].child[now],l=tree[l].child[now];
			if(x)tmp|=(1<<i);
		}
		ans=max(ans,tmp);
		return ans;
	}
}trie;


int main(){
	while(scanf("%d%d",&n,&m)==2){
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)G[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		trie=Trie();
		while(m--){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			printf("%d\n",trie.query(x,y,z));
		}
	}
	return 0;
}
