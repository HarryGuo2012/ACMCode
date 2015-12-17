#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<map>
#include<algorithm>
#define MAX_N 30004
using namespace std;

typedef long long ll;
int K;
struct segmentTree{
#define lchilds L,m,v<<1
#define rchilds m+1,R,v<<1|1
	ll tmp[12];
	struct node{
		ll lazy;
		ll sum[12];
		node(){
			memset(sum,0,sizeof(sum));
			lazy=0;
		}
	}tree[4*MAX_N];
	segmentTree(){
		for(int i=0;i<4*MAX_N;i++)
			tree[i]=node();
	}
	
};

int main(){
	return 0;
}
