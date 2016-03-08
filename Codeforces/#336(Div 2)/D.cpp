#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<string>
#include<vector>
#define INF 10086
#define MAX_N 523
using namespace std;

int n,a[MAX_N],dp[MAX_N][MAX_N];

int dfs(int L,int R){
	if(L==R)
		return dp[L][R]=1;
	if(L+1==R&&a[L]==a[R])
		return dp[L][R]=1;
	if(L+1==R)
		return dp[L][R]=2;
	if(dp[L][R])return dp[L][R];
	int res=INF;
	if(a[L]==a[R])res=dfs(L+1,R-1);
	for(int k=L;k<R;k++)
		res=min(res,dfs(L,k)+dfs(k+1,R));
	return dp[L][R]=res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int ans=dfs(1,n);
	cout<<ans<<endl;
	return 0;
}
