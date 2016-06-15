#include <cstdio>

int A, B;
int M;

int main() {
	scanf("%d%d%d", &A, &B, &M);
	A++, B++;
	int q = 0, p = 0;
	bool flag = false;
	for (int i = 1; i <= M; i++) {
		int a, x, b, y;
		scanf("%d%d%d%d", &x, &a, &y, &b);
		if (flag) continue;
		if (a == x + y && b != x + y) q++;
		if (b == x + y && a != x + y) p++;
		if (A == q) {
			printf("A\n%d\n", p);
			flag = true;
		}
		if (B == p) {
			printf("B\n%d\n", q);
			flag = true;
		}
	}
	return 0;
}