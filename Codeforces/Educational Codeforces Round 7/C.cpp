#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define MAX_N 200005
using namespace std;

int a[MAX_N];
int dp[MAX_N];
int n,m;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i>=1;i--){
		if(a[i]==a[i+1])
			dp[i]=dp[i+1];
		else
			dp[i]=i;
	}
	while(m--){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		if(a[l]!=x)printf("%d\n",l);
		else if(dp[l]>=r)printf("%d\n",-1);
		else printf("%d\n",dp[l]+1);
	}
	return 0;
}