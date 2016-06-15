#include <cstdio>

long long ans = 0;

int main() {
	for (int i = 1; i < 1000; i++)
		if (i % 3 == 0 || i % 5 == 0) ans += i;
	printf("%lld\n", ans);
	return 0;
}