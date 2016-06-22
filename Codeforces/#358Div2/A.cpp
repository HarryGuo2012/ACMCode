#include <cstdio>

int n, m;

long long ans = 0;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int t = 5 - i % 5;
		ans += ((m % 5) >= t) + (long long)m / 5;
	}
	printf("%I64d\n", ans);
	return 0;
}