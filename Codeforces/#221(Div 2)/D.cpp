#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#define MAX_N 5001
using namespace std;

bool G[MAX_N][MAX_N];
int n,m;

int dp[MAX_N][MAX_N];

int v[MAX_N],tot=0;

int a[MAX_N];

void Sort(){
	int maxV=0;
	for(int i=0;i<tot;i++)
		maxV=max(maxV,v[i]);
	for(int i=0;i<=maxV;i++)a[i]=0;
	for(int i=0;i<tot;i++)
		a[v[i]]++;
	int tmp=0;
	for(int i=0;i<=maxV;i++)
		while(a[i]){
			v[tmp++]=i;
			a[i]--;
		}
}

int main(){
	scanf("%d%d",&n,&m);
	getchar();
	for(int i=1;i<=n;i++,getchar())
		for(int j=1;j<=m;j++){
			char c;
			c=getchar();
			G[i][j]=c=='1';
		}
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--){
			if(!G[i][j])dp[i][j]=0;
			else dp[i][j]=dp[i][j+1]+1;
		}
	int ans=0;
	for(int j=1;j<=m;j++){
		tot=0;
		for(int i=1;i<=n;i++)
			if(dp[i][j])
				v[tot++]=dp[i][j];
		Sort();
		for(int i=0;i<tot;i++)
			ans=max(ans,(tot-i)*v[i]);
	}
	cout<<ans<<endl;
	return 0;
}
