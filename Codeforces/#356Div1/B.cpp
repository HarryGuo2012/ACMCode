#include <cstdio>

long long m;

long long t(long long x) {
	return x * x * x;
}

int solve(long long x) {
	int cnt = 0;
	long long j = 222;
	while (x) {
		if (x < t(j)) j--;
		if (x >= t(j)) {
			x -= t(j);
			cnt++;
		}
	}
	return cnt;
}

int main() {
	long long h = 0;
	for (long long ii = 1; ii <= 1000; ii++) {
		if (h <= solve(ii)) {
			printf("%lld %d\n", ii, solve(ii));
			h = solve(ii);
		}
	}
	scanf("%lld", &m);
	if (m <= 7) {
		printf("%lld\n", m);
		return 0;
	}
	long long now = 7, j = 2;
	while (now < m) {
		now += t(j);
		j++;
	}
	if (now == m) {
		printf("%lld\n", m);
		return 0;
	}
	long long i = 1;
	while (now - t(i) > m) i++;
	printf("%lld\n", now - t(i));
	return 0;
}