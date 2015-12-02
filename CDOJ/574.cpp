#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<string>
#define MAX_N 50004
#define lchild L,m,v<<1
#define rchild m+1,R,v<<1|1
using namespace std;


typedef long long ll;

ll A[MAX_N],S[MAX_N];
int N,P,T;

class SegmentTree{
public:
	struct node{
		ll lazy,sum;
		node():lazy(0),sum(0){}
	};
	node tree[MAX_N*4];
	virtual ll getVal(int L,int R){
		return S[R]-S[L-1];	
	}
	void clear(){
		for(int i=0;i<MAX_N*4;i++)tree[i]=node();
	}
	void pushDown(int v,int L,int R){
		int m=(L+R)>>1;
		tree[v<<1].lazy+=tree[v].lazy;
		tree[v<<1|1].lazy+=tree[v].lazy;
		tree[v<<1].sum+=tree[v].lazy*getVal(L,m);
		tree[v<<1|1].sum+=tree[v].lazy*getVal(m+1,R);
		tree[v].lazy=0;
	}
	void pushUp(int v){
		tree[v].sum=tree[v<<1].sum+tree[v<<1|1].sum;
	}
	void update(int a,int b,ll x,int L=1,int R=N,int v=1){
		if(a<=L&&R<=b){
			tree[v].lazy+=x;
			tree[v].sum+=x*getVal(L,R);
			return;
		}
		int m=(L+R)>>1;
		if(tree[v].lazy)pushDown(v,L,R);
		if(a<=m)update(a,b,x,lchild);
		if(b>m)update(a,b,x,rchild);
		pushUp(v);
	}
	ll query(int a,int b,int L=1,int R=N,int v=1){
		if(a<=L&&R<=b)return tree[v].sum;
		if(tree[v].lazy)pushDown(v,L,R);
		int m=(L+R)>>1;
		ll res=0;
		if(a<=m)res+=query(a,b,lchild);
		if(b>m)res+=query(a,b,rchild);
		return res;
	}
}seg1;

class NormalSeqmentTree:public SegmentTree{
public:
	ll getVal(int L,int R){
		return R-L+1;
	}
}seg2;

vector<int> G[MAX_N];

int tot=0,dfn[MAX_N];

int siz[MAX_N];
int AA[MAX_N];

void dfs(int x,int p){
	siz[x]=1;
	AA[x]=AA[p]+1;
	dfn[++tot]=x;
	for(int i=0;i<G[x].size();i++){
		int v=G[x][i];
		if(v==p)continue;
		dfs(v,x);
		siz[x]+=siz[v];
	}
}

int in[MAX_N],out[MAX_N];

void init(){
	memset(siz,0,sizeof(siz));
	memset(dfn,0,sizeof(dfn));
	tot=0;
	for(int i=0;i<=N;i++)G[i].clear();
	memset(A,0,sizeof(A));
	memset(AA,0,sizeof(AA));
	memset(S,0,sizeof(S));
	seg1.clear();
	seg2.clear();
}
int cas=0;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&N,&P);
		init();
		for(int i=2;i<=N;i++){
			int t;
			scanf("%d",&t);
			G[i].push_back(t);
			G[t].push_back(i);
		}		
		dfs(1,0);
		for(int i=1;i<=N;i++)A[i]=AA[dfn[i]];
		for(int i=1;i<=N;i++)S[i]=S[i-1]+A[i];
		for(int i=1;i<=N;i++)in[dfn[i]]=i,out[dfn[i]]=i+siz[dfn[i]]-1;
		printf("Case #%d:\n",++cas);
		while(P--){
			char op[2];
			int x,y;
			scanf("%s ",op);
			if(op[0]=='Q'){
				scanf("%d",&x);
				//cout<<seg1.query(in[x],out[x])<<" "<<seg2.query(in[x],out[x])<<endl;
				printf("%lld\n",seg1.query(in[x],out[x])-seg2.query(in[x],out[x]));
			}
			else{
				scanf("%d%d",&x,&y);
				seg1.update(in[x],out[x],1);
				seg2.update(in[x],out[x],A[in[x]]-y);
			}
		}
	}
	return 0;
}
