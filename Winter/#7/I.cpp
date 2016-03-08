#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <climits>
#define MAX_N 1003
#define MAX_P 1000006
#define MAX_D 100
#define INF LLONG_MAX
using namespace std;

typedef long long ll;

ll p[MAX_N];
int a[MAX_N];
int k;
int b[MAX_N];
int c[MAX_N];

ll ans=INF;
ll Po[MAX_N][MAX_D];

ll AA,BB,CC;

bool flag=false;

ll cnt=0;

void update(){
	ll A=1,B=1,C=1;
	for(int i=0;i<k;i++){
		B=B*Po[i][b[i]];
		C=C*Po[i][c[i]];
		A=A*Po[i][a[i]-b[i]-c[i]];
	}
	if(ans>A*B+B*C+C*A){
		cnt=0;
		ans=A*B+B*C+C*A;
		AA=A,BB=B,CC=C;
	}
	cnt++;
}

void dfs2(int i){
	if(flag&&cnt>70000)return;
	if(i==k){
		update();
		return;
	}
	for(int j=0;j<=a[i]-b[i];j++){
		c[i]=j;
		dfs2(i+1);
	}
}

void dfs(int i){
	if(flag&&cnt>70000)return;
	if(i==k){
		dfs2(0);
		return;
	}
	for(int j=0;j<=a[i];j++){
		b[i]=j;
		dfs(i+1);
	}
}

int T;

void Div(ll x){
	for(int i=0;i<k;i++){
		int j=0;
		while(j<=a[i]&&x%Po[i][j]==0)j++;
		j--;
		b[i]=j;
	}
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--){
		cnt=0;
		flag=false;
		ans=INF;
		scanf("%d",&k);
		for(int i=0;i<k;i++)
			scanf("%I64d%d",&p[i],&a[i]);
		for(int i=0;i<k;i++){
			Po[i][0]=1;
			for(int j=1;j<=a[i];j++)
				Po[i][j]=Po[i][j-1]*p[i];
		}
		ll u,V=1;
		for(int i=0;i<k;i++)
			V*=Po[i][a[i]];
		for(ll i=1;(ll)i*i*i<=V;i++)
			if(V%i==0)u=i;
		Div(u);
		dfs2(0);
		cnt=0;
		flag=true;
		dfs(0);
		printf("%I64d %I64d %I64d %I64d\n",ans*2,AA,BB,CC);
	}
	return 0;
}