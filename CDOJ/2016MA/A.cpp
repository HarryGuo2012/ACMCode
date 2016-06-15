#include <cstdio>
#include <algorithm>

#define MAX_N 26

long long dp[MAX_N][MAX_N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		dp[1][i] = 1;
	for (int i = 2; i <= k; i++)
		for (int j = 1; j <= n; j++)
			for (int a = 1; a <= j; a++)
				dp[i][j] += dp[i - 1][a];
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += dp[k][i];
	printf("%lld\n", ans);
	return 0;
}