#include <cstdio>

int n, a, b, d;

int T;

int haha[6];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &a, &b, &d, &n);
		if (n < 5) {
			int cnt = 0;
			long long tmp = 0;
			for (int i = 0; i < n; i++)
				tmp = tmp * 10 + a;
			tmp = tmp * b;
			while (tmp) {
				int c = tmp % 10;
				if (c == d) cnt++;
				tmp /= 10;
			}
			printf("%d\n", cnt);
			continue;
		}
		int len = 0;
		long long tmp = 0;
		int cnt = 0;
		for (int i = 0; i < 5; i++)
			tmp = tmp * 10 + a;
		tmp = tmp * b;
		int x, y, z, p;
		x = tmp % 10;
		y = tmp / 10 % 10;
		z = tmp / 100 % 10;
		while (tmp) {
			len++;
			if (tmp / 10 == 0) p = tmp;
			tmp /=10;
		}
		//printf("%d %d %d %d\n", x, y, z, p);
		int ans = 0;
		if (x == d) ans++;
		if (z == d) ans += n - 3 + (len - 5);
		if (y == d) ans++;
		if (p == d) ans++;
		printf("%d\n", ans);
	}
	return 0;
}