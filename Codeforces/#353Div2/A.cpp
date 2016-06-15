#include <cstdio>

long long abs(long long x) {
	if (x < 0) return -x;
	else return x;
}

long long a, b, c;

int main() {
	scanf("%I64d%I64d%I64d", &a, &b, &c);
	if (c == 0) {
		if (a == b) printf("YES\n");
		else printf("NO\n");
		return 0;
	}
	if ((abs(b - a)) % abs(c) == 0) {
		if (c > 0) {
			if (b >= a) printf("YES\n");
			else printf("NO\n");
		}
		else if (c < 0) {
			if (b <= a) printf("YES\n");
			else printf("NO\n");
		}
	}
	else {
		printf("NO\n");
	}
	return 0;
}