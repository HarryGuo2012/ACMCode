#include <cstdio>

#define MAX_N 1 << 20

int n;
typedef int ll;
ll a[MAX_N];

const ll mod = 772002;

void add(ll &x, ll y) {
	x = (x + y) % mod;
	if (x < 0) x = x + mod;
}

void mobius(ll *v, ll d) {
	for (int i = 0; i < n; i++)
		for (int mask = 0; mask < (1 << n); mask++) {
			if (mask >> i & 1) continue;
			add(v[mask | (1 << i)], d * v[mask]);
		}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < (1 << n); i++)
		scanf("%d", &a[i]);
	mobius(a, 1);
	for (int i = 0; i < (1 << n); i++)
		a[i] = (long long)a[i] * a[i] % mod;
	mobius(a, -1);
	for (int i = 0; i < (1 << n); i++)
		printf("%d\n", a[i]);
	return 0;
}