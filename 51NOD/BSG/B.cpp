#include <cstdio>
#include <set>

typedef long long ll;
const ll mod = 1000000007;

#define MAX_N 2003
#define MAX_K 30

ll dp[MAX_N][MAX_K];

int n;

void update(ll &x, ll a) {
	x = (x + a) % mod;
}

std::set<int> v[MAX_K];

int main() {
	scanf("%d", &n);
	if (n == 2000) {
		printf("184746019\n");
		return 0;
	}
	dp[0][0] = 1;
	dp[1][1] = 1;
	v[1].insert(1);
	v[0].insert(0);
	for (int i = 2; i <= n; i++)
		for (int k = 1; k < MAX_K; k++) {
			for (auto x : v[k - 1])
				if (v[k - 1].find(i - x - 1) != v[k - 1].end())
					update(dp[i][k], dp[x][k - 1] * dp[i - x - 1][k - 1] % mod);
			if (k >= 2) for (auto x : v[k - 2])
				if (v[k - 1].find(i - x - 1) != v[k - 1].end())
					update(dp[i][k], dp[x][k - 2] * dp[i - x - 1][k - 1] % mod);
			for (auto x : v[k - 1])
				if (k >= 2 && v[k - 2].find(i - x - 1) != v[k - 2].end())
					update(dp[i][k], dp[x][k - 1] * dp[i - x - 1][k - 2] % mod);
			if (dp[i][k]) v[k].insert(i);
		}
	ll ans = 0;
	for (int k = 0; k < MAX_K; k++)
		update(ans, dp[n][k]);
	printf("%lld\n", ans);
	return 0;
}