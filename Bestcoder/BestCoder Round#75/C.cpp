#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 2222
using namespace std;

typedef long long ll;
ll dp[MAX_N][27][4];
const ll mod=1000000007;
int main(){
	dp[0][0][0]=1;
	for(int i=1;i<MAX_N;i++)
		for(int j=1;j<=26;j++)
			for(int k=1;k<=3;k++)
				for(int x=0;x<=26;x++){
					if(k==1&&x!=j)
						dp[i][j][k]+=dp[i-1][x][0]+dp[i-1][x][1]+dp[i-1][x][2]+dp[i-1][x][3];
					else if(x==j)
						dp[i][j][k]+=dp[i-1][x][k-1];
					dp[i][j][k]%=mod;
				}
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		ll ans=0;
		for(int i=0;i<=26;i++)
			for(int j=0;j<=3;j++)
				ans=(ans+dp[n][i][j])%mod;
		printf("%I64d\n",ans);
	}
	return 0;
}