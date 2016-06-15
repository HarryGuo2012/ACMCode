#include <cstdio>

long long n;

int main() {
	scanf("%I64d", &n);
	bool flag = false;
	for (long long a = 0; a * 1234567 <= n; a++)
		for (long long b = 0; b * 123456 + a * 1234567 <= n; b++) {
			long long t = n - a * 1234567 - b * 123456;
			if (t % 1234 == 0) flag = true;
		}
	if (flag)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}