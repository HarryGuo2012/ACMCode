#include <cstdio>
#include <algorithm>
#include <climits>

#define INF 123456789
#define MAX_S (1 << 15)

int N;
long long cost[MAX_S];

long long dp[MAX_S];

int main() {
	std::fill(cost, cost + MAX_S, INF);
	std::fill(dp, dp + MAX_S, INF);
	dp[0] = 0;
	for (int i = 0; i < 15; i++) 
		scanf("%d", &cost[1 << i]);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int a, mask = 0;
		scanf("%d", &a);
		for (int i = 0; i < a; i++) {
			int t;
			scanf("%d", &t);
			t--;
			mask |= 1 << t;
		}
		long long d;
		scanf("%lld", &d);
		cost[mask] = std::min(cost[mask], d);
	}

	for (int s = 0; s < MAX_S; s++) {
		if (cost[s] == INF) continue;
		dp[s] = std::min(dp[s], cost[s]);
		int tmp = ((1 << 15) - 1) ^ s;
		for (int t = tmp; t; t = (t - 1) & tmp) 
			if (dp[t] != INF)
				dp[t | s] = std::min(dp[t | s], cost[s] + dp[t]);
	}
	printf("%lld\n", dp[(1 << 15) - 1]);
	return 0;
}