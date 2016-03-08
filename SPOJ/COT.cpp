#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<queue>
#define MAX_N 100005
using namespace std;

ll a[MAX_N];
ll b[MAX_N];

struct node{
	int childs[2];
	int sum;
}tree[MAX_N*20];

int tot=1;

int N,M;
vector<ll> val;

void build(int v=1,int L=1,int R=N){
	memset(tree[v].childs,0,sizeof(tree[v].childs));
	tree[v].sum=0;

}

int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++){
		ll v;
		scanf("%I64d",&v);
		a[i]=v;
		val.push_back(v);
	}
	sort(val.begin(),val.end());
	for(int i=1;i<=N;i++){
		int t=lower_bound(val.begin(),val.end(),a[i])+1;
		b[t]=a[i];
		a[i]=t;
	}
	for(int i=1;i<=N-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	N+=5;
	return 0;
}
