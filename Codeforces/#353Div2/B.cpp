#include <cstdio>
#include <algorithm>

int n;

bool check(int x) {
	return x >= 1 && x <= n;
}

int main() {
	int a, b, c, d;
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
	long long ans = 0;

	for (int x = 1; x <= n; x++) {
		int S = x + a + b;
		int x2 = S - a - c;
		int x3 = S - b - d;
		int x4 = S - c - d;
		if (check(x2) && check(x3) && check(x4)) ans = ans + n;
	}
	printf("%I64d\n", ans);
	return 0;
}