#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
ll dp[11][100005];
ll sum[11][100005];
const ll mod=1000000007;
class DivFreed2{
public:
	int count(int n,int k){
		for(int i=1;i<=k;i++)
			dp[1][i]=1;
		for(int i=1;i<=k;i++)
			sum[1][i]=sum[1][i-1]+dp[1][i];
		for(int i=2;i<=n;i++){
			for(int j=1;j<=k;j++){
				dp[i][j]=(sum[i-1][k]+dp[i][j])%mod;
				for(int t=2;t*j<=k;t++)
					dp[i][j]=(dp[i][j]-dp[i-1][t*j])%mod;
			}
			for(int j=1;j<=k;j++)
				sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
		}
		ll ans=0;
		for(int i=1;i<=k;i++)
			ans=(ans+dp[n][i])%mod;
		return ans;
	}
};