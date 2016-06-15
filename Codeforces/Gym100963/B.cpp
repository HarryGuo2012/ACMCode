#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX_N 55
#define MAX_A 2323

int dp[MAX_N][MAX_A];
int a[MAX_N];

int N;

void solve() {
	for (int j = 1; j < MAX_A; j++)
		dp[1][j] = j;
	for (int i = 2; i <= N; i++)
		for (int j = 1; j < MAX_A; j++) {
			if (j < a[i]) 
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = std::min(dp[i - 1][j], dp[i][j - a[i]] + 1);
		}
}

int cnt(int x) {
	int res = 0;
	for (int i = N; i >= 1; i--) {
		res += x / a[i];
		x %= a[i];
	}
	return res;
}

int main() {
	int cas = 0;
	while (scanf("%d", &N) == 1) {
		if (N == 0) break;
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		printf("Case #%d: ", ++cas);
		if (a[1] != 1) {
			printf("Cannot pay some amount\n");
			continue;
		}
		memset(dp, 0, sizeof(dp));
		solve();
		bool flag = true;
		for (int j = 1; j < MAX_A; j++)
			if (dp[N][j] < cnt(j)) flag = false;
		if (!flag)
			printf("Cannot use greedy algorithm\n");
		else 
			printf("OK\n");
	}
	return 0;
}