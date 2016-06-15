#include <cstdio>

#define MAX_N 1 << 20

long long a[MAX_N];
long long ans[MAX_N];
long long mod = 772002;
int n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < (1 << n); i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j < (1 << n); j++)
			ans[i | j] = (ans[i | j] + a[i] * a[j] % mod) % mod;
	for (int i = 0; i < (1 << n); i++)
		printf("%lld\n", ans[i]);
	return 0;
}