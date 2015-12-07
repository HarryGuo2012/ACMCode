#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#define MAX_N 100005
#define MAX_M 102
using namespace std;

#define lchild l,m,v<<1
#define rchild m+1,r,v<<1|1

int N,M;
int Q;

struct SegmentTree{
	struct Node{
		int lazy;//-1 means no lazy
		bool flag;//1 means there is at least one 1
		Node():lazy(-1),flag(0){}
	};	
	Node tree[MAX_N*4];
	SegmentTree{
		for(int i=0;i<MAX_N*4;i++)tree[i]=Node();
	}
	void pushUp(int v){
		tree[v].flag=tree[v>>1].flag|tree[v>>1|1].flag;
	}
	void pushDown(int v){
		tree[v>>1].flag=tree[v>>1|1].flag=tree[v].lazy;
		tree[v>>1].lazy=tree[v>>1|1].lazy=tree[v].lazy;
	}
	void update(int a,int b,bool x,int l=1,int r=N,int v=1){
		if(a==b){
			tree[v].flag=tree[v].lazy=x;
			return;
		}
		if(a<=l&&r<=b){
			tree[v].flag=tree[v].lazy=x;
			return;
		}
		if(tree[v].lazy!=-1)pushDown(v);
		int m=(l+r)>>1;
		if(a<=m)update(a,b,x,lchild);
		if(b>m)update(a,b,x,rchild);
		pushUp(v);
	}
	bool query(int a,int b,int l=1,int r=N,int v=1){
		if(a<=l&&r<=b)return tree[v].flag;
		int m=(l+r)>>1;
		bool res=0;
		if(tree[v].lazy!=-1)pushDown(v);
		if(a<=m)res|=query(a,b,x,lchild);
		if(b>m)res|=query(a,b,x,rchild);
		return res;
	}
}seg[MAX_M];

int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++){
		int x;
		scanf("%d",&x);
		seg[x].update(i,i,1);
	}
	scanf("%d",&Q);
	while(Q--){
		char op;
		int x,y,z;
		scanf("%c %d%d",&op,&x,&y);
		if(op=='M'){
			scanf("%d",&z);
			for(int i=1;i<=M;i++)
				seg[i].update(x,y,z==i);
		}
		else{
			int ans=0;
			for(int i=1;i<=M;i++)
				ans+=seg[i].query(x,y);
			printf("%d\n",ans);
		}
	}
	return 0;
}

