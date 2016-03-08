#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <climits>
#define INF ((long long)32767*1000000+5)
#define MAX_N 1000006
using namespace std;

typedef long long ll;

ll a[MAX_N],dp[2][MAX_N],s[MAX_N],pre[MAX_N];
int n,m;

int main(){
	while(scanf("%d%d",&m,&n)==2){
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
		for(int i=0;i<=n;i++)
			dp[0][i]=dp[1][i]=-INF;
		memset(pre,0,sizeof(pre));
		pre[0]=-INF;
		for(int i=1;i<=m;i++){
			for(int j=i;j<=n;j++){
				dp[i&1][j]=s[j]+pre[j];
				pre[j]=max(pre[j-1],dp[i&1][j]-s[j]);
				cout<<dp[i&1][j]<<" "<<dp[i&1][j]-s[j]<<" "<<pre[j]<<endl;
			}
			cout<<endl;
		}
		ll ans=-INF;
		for(int j=1;j<=n;j++)
			ans=max(ans,dp[m&1][j]);
		printf("%lld\n",ans);
	}
	return 0;
}