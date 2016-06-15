#include <cstdio>

long long ans = 0;

long long u = 1, v = 1;

int main() {
	while (v <= 4000000) {
		if ((v & 1) == 0)
			ans += v;
		long long t = v;
		v = u + v;
		u = t;
	}
	printf("%lld\n", ans);
	return 0;
}