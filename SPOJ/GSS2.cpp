#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<climits>
#define INF (LLONG_MAX-5)
#define lchild L,m,v<<1
#define rchild m+1,R,v<<1|1
#define MAX_N 100005
using namespace std;

typedef long long ll;
int N,Q;

class SegmentTree{
	public:
		struct node{
			ll maxVal,lazy,everMax,everLazy;
			node():maxVal(0),lazy(0),everMax(0),everLazy(0){}
		};
		node tree[MAX_N*4];
		SegmentTree(){
			clear();
		}	
		void pushUp(int v){
			tree[v].maxVal=max(tree[v<<1].maxVal,tree[v<<1|1].maxVal);
			tree[v].everMax=max(tree[v<<1].everMax,tree[v<<1|1].everMax);
		}
		void pushDown(int v){
			tree[v<<1].everLazy=max(tree[v<<1].everLazy,tree[v<<1].lazy+tree[v].everLazy);
			tree[v<<1|1].everLazy=max(tree[v<<1|1].everLazy,tree[v<<1|1].lazy+tree[v].everLazy);
			tree[v<<1].everMax=max(tree[v<<1].everMax,tree[v<<1].maxVal+tree[v].everLazy);
			tree[v<<1|1].everMax=max(tree[v<<1|1].everMax,tree[v<<1|1].maxVal+tree[v].everLazy);
			tree[v].everLazy=0;
			tree[v<<1].maxVal+=tree[v].lazy;
			tree[v<<1].lazy+=tree[v].lazy;
			tree[v<<1|1].maxVal+=tree[v].lazy;
			tree[v<<1|1].lazy+=tree[v].lazy;
			tree[v].lazy=0;
		}
		void update(int a,int b,ll x,int L=1,int R=N,int v=1){
			//cout<<a<<" "<<b<<" "<<x<<" "<<L<<" "<<R<<" "<<v<<endl;
			if(a<=L&&R<=b){
				tree[v].lazy+=x;
				tree[v].maxVal+=x;
				tree[v].everLazy=max(tree[v].lazy,tree[v].everLazy);
				tree[v].everMax=max(tree[v].everMax,tree[v].maxVal);
				return;
			}
			int m=(L+R)>>1;
			if(tree[v].lazy) pushDown(v);
			if(a<=m) update(a,b,x,lchild);
			if(b>m) update(a,b,x,rchild);
			pushUp(v);
		}
		ll query(int a,int b,int L=1,int R=N,int v=1){
			//cout<<a<<" "<<b<<" "<<L<<" "<<R<<" "<<v<<endl;
			if(a<=L&&R<=b)return tree[v].everMax;
			if(tree[v].lazy||tree[v].everLazy)pushDown(v);
			int m=(L+R)>>1;
			ll res=-INF;
			if(a<=m)res=max(res,query(a,b,lchild));
			if(b>m)res=max(res,query(a,b,rchild));
			return res;
		}
		void clear(){
			for(int i=0;i<MAX_N*4;i++)
				tree[i]=node();
		}
}seg;

int Hash(int x){
	return x+MAX_N-1;
}

int Last[MAX_N*2];
int lef[MAX_N];
vector<int> righ[MAX_N];
ll ans[MAX_N];
int a[MAX_N];

int main(){
	scanf("%d",&N);
	/*
	int qq;
	cin>>qq;
	while(qq--){
		char op;int x,y,z;
		cin>>op>>x>>y;
		if(op=='q')cout<<seg.query(x,y)<<endl;
		else{
			cin>>z;
			seg.update(x,y,z);
		}
	}
	*/
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		righ[y].push_back(i);
		lef[i]=x;
	}
	for(int i=1;i<=N;i++){
		//cout<<Last[Hash(i)]+1<<" "<<i<<" "<<a[i]<<endl;
		seg.update(Last[Hash(a[i])]+1,i,a[i]);
		Last[Hash(a[i])]=i;
		for(int j=0;j<righ[i].size();j++){
			int t=lef[righ[i][j]];
			ans[righ[i][j]]=seg.query(t,i);
		}
	}
	for(int i=1;i<=Q;i++)printf("%lld\n",ans[i]);
	return 0;
}
