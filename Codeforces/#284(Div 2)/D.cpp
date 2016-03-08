#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
#include<algorithm>
#define MAX_N 5555
using namespace std;

long long dp[2][MAX_N];

long long Pow(long long x,int k){
	long long res=1;
	long long tmp=x;
	while(k){
		if(k&1)res*=tmp;
		tmp=tmp*tmp;
		k>>=1;
	}
	return res;
}

int n,T;

long long p[MAX_N],t[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>T;
	for(int i=1;i<=n;i++)
		cin>>p[i]>>t[i];
	for(int i=1;i<=n;i++){
		int u=i&1;
		int v=!u;
		memset(dp[u],0,sizeof(dp[u]));
		for(int j=1;j<=T;j++)
			dp[u][j]+=dp[v][]
	}
	return 0;
}
