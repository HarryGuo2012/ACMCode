#include <iostream>
#include <string>
#include <algorithm>

#define MAX_N 22
#define MAX_M 100005
#define MAX_S 1 << 21

typedef long long ll;

int n, m;

std::string a[MAX_N];
ll num[MAX_M];
ll cnt[MAX_S], mi[MAX_S];

int ones(int x) {
	int res = 0;
	while (x) {
		res += x & 1;
		x >>= 1;
	}
	return res;
}

void walsh(ll *v, int d) {
	for (int i = 0; i < n; i++)
		for (int mask = 0; mask < (1 << n); mask++) {
			if(mask >> i & 1) continue;
			ll l = v[mask], r = v[mask | (1 << i)];
			v[mask] = l + r, v[mask | (1 << i)] = l - r;
		}
	for (int mask = 0; mask < (1 << n); mask++)
		v[mask] /= d;
}

ll f[MAX_S];

int main() {
	std::cin >> n >> m;
	for (int i = 0; i < n; i++)
		std::cin >> a[i];
	for (int j = 0; j < m; j++) {
		int tmp = 0;
		for (int i = 0; i < n; i++)
			tmp |= (a[i][j] - '0') << i;
		num[j] = tmp;
		cnt[tmp]++;
	}
	for (int mask = 0; mask < (1 << n); mask++)
		mi[mask] = std::min(ones(mask), n - ones(mask));
	walsh(mi, 1);
	walsh(cnt, 1);
	for (int mask = 0; mask < (1 << n); mask++)
		f[mask] = cnt[mask] * mi[mask];
	walsh(f, 1 << n);
	ll ans, tmp = n * m + 1;
	for (int mask = 0; mask < (1 << n); mask++)
		if (tmp > f[mask])
			tmp = f[mask], ans = mask;
	printf("%lld\n", tmp);
	return 0;
}