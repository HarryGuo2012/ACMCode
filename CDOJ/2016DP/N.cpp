#include <cstdio>
#include <algorithm>

#define MAX_N 100005

int n, k, a[MAX_N];

typedef long long ll;
const ll mod = 1000000009;

ll tree[MAX_N];

void add(ll &x, ll a) {
	x = (x + a) % mod;
}

void update(int x, ll a) {
	while (x < MAX_N) {
		add(tree[x], a);
		x += x & (-x);
	}
}

ll query(int x) {
	ll res = 0;
	while (x) {
		add(res, tree[x]);
		x -= x & (-x);
	}
	return res;
}

ll dp[MAX_N];
std::vector<int> v;

ll ans;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		v.push_back(a[i]);
	}
	v.push_back(-1);
	std::sort(v.begin(), v.end());
	auto it = std::unique(v.begin(), v.end());
	v.resize(std::distance(v.begin(), it));
	for (int i = 1; i <= n; i++) {
		int L = std::lower_bound(v.begin(), v.end(), a[i] - k) - v.begin();
		L = std::max(L, 1);
		int R = std::upper_bound(v.begin(), v.end(), a[i] + k) - v.begin();
		R = std::max(R - 1, 1);
		int P = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		ll sum = query(R) - query(L - 1);
		dp[i] = (sum % mod + mod) % mod;
		update(P, dp[i] + 1);
		add(ans, dp[i]);
	}
	printf("%lld\n", ans);
	return 0;
}