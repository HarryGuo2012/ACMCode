#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 100005
using namespace std;

int dp[MAX_N];

int n;
int a[MAX_N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		dp[a[i]]=dp[a[i]-1]+1;
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	printf("%d\n",n-ans);
	return 0;
}
