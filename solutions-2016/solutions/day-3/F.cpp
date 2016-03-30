#include<stdio.h>
const int MAXN = 400;
int N, K;
const int mod = 1000000007;// 10 ^ 9 + 7
long long dp[MAXN * MAXN + 10];
int main(){
	scanf("%d%d",&N,&K);
	dp[0] = 1;
	int nsum = 0;
	for(int i = 1; i <= N; ++i){
		nsum += i - 1;
		for(int j = 1; j <= nsum; ++j){
			dp[j] += dp[j - 1];
		}
		for(int j = nsum; j >= i; -- j){
			dp[j] = (dp[j] - dp[j - i]) % mod;
		}
		for(int j = i - 1; j >= 0; --j){
			dp[j] = dp[j] % mod;
		}
	}
	printf("%d\n",int(dp[K]));
	return 0;
}
