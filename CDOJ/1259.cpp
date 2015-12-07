#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

#define lchild l,m,v<<1
#define rchild m+1,r,v<<1|1

struct SegmentTree{
	struct Node{
		int lazy;//-1 means no lazy
		bool flag;//1 means there is at least one 1
		Node():lazy(-1),flag(0);
	}	
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
};

int main(){
	return 0;
}
