#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#define MAX_N 300005
#define MAX_A 10000007
using namespace std;

typedef long long ll;

int n;

int prime[MAX_A],tot=0;
bool check[MAX_A];
int phi[MAX_A];

void Euler(){
	phi[1]=1;
	for(int i=2;i<MAX_A;i++){
		if(!check[i]){
			prime[tot++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<tot;j++){
			if(i*prime[j]>=MAX_A)break;
			check[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

struct SegmentTree{
public:
	struct node{
		ll sum[25],lazy[25];
	}tree[MAX_N*4];
	void init(){
		for(int i=0;i<=n*4;i++){
			memset(tree[i].sum,0,sizeof(tree[i].sum));
			memset(tree[i].lazy,0,sizeof(tree[i].lazy));
		}
	}
	void pushUp(int i){
		for(int j=0;j<25;j++)
			tree[i].sum[j]=tree[i<<1].sum[j]+tree[i<<1|1].sum[j];
	}
	void pushDown(int v,int l,int r){
		int m=(l+r)>>1;
		for(int j=0;j<25;j++){
			tree[v<<1].sum[j]=tree[v].lazy[j]*(m-l+1);
			tree[v<<1].lazy[j]=tree[v].lazy[j];
			tree[v<<1|1].sum[j]=tree[v].lazy[j]*(r-m);
			tree[v<<1|1].lazy[j]=tree[v].lazy[j];
			tree[v].lazy[j]=0;
		}
	}
	#define lchild l,m,v<<1
	#define rchild m+1,r,v<<1|1
	void update(int L,int R,ll x,int l=1,int r=n,int v=1){
		if(L<=l&&r<=R){
			tree[v].lazy[0]=x;
			tree[v].sum[0]=x*(r-l+1);
			for(int i=1;i<25;i++){
				tree[v].lazy[i]=phi[tree[v].lazy[i-1]];
				tree[v].sum[i]=tree[v].lazy[i]*(r-l+1);
			}
			return;
		}
		if(tree[v].lazy[0])pushDown(v,l,r);
		int m=(l+r)>>1;
		if(L<=m)update(L,R,x,lchild);
		if(R>m)update(L,R,x,rchild);
		//if(v==2)cout<<tree[v<<1].sum[0]<<" "<<tree[v<<1|1].sum[0]<<endl;
		pushUp(v);
	}
	void update1(int L,int R,int l=1,int r=n,int v=1){
		if(L<=l&&r<=R){
			for(int i=0;i<24;i++){
				tree[v].lazy[i]=tree[v].lazy[i+1];
				tree[v].sum[i]=tree[v].sum[i+1];
			}
			tree[v].lazy[24]=phi[tree[v].lazy[23]];
			tree[v].sum[24]=tree[v].lazy[24]*(r-l+1);
			return;
		}
		if(tree[v].lazy[0])pushDown(v,l,r);
		int m=(l+r)>>1;
		if(L<=m)update1(L,R,lchild);
		if(R>m)update1(L,R,rchild);
		pushUp(v);
	}
	ll query(int L,int R,int l=1,int r=n,int v=1){
		if(L<=l&&r<=R)
			return tree[v].sum[0];
		ll res=0;
		pushDown(v,l,r);
		ll m=(l+r)>>1;
		if(L<=m)res+=query(L,R,lchild);
		if(R>m)res+=query(L,R,rchild);
		return res;
	}
}seg;

int T;

int main(){
	Euler();
	scanf("%d",&T);
	while(T--){
		int m;
		scanf("%d%d",&n,&m);
		seg.init();
		for(int i=1;i<=n;i++){
			int a;
			scanf("%d",&a);
			seg.update(i,i,a);
		}
		while(m--){
			int t,l,r;
			scanf("%d%d%d",&t,&l,&r);
			if(t==1)
				seg.update1(l,r);
			else if(t==2){
				int x;
				scanf("%d",&x);
				seg.update(l,r,x);
			}
			else if(t==3){
				printf("%lld\n",seg.query(l,r));
			}
		}
	}
	return 0;
}