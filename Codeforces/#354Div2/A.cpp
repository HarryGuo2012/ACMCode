#include <cstdio>
#include <algorithm>

int a, b;

int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		 int t;
		 scanf("%d", &t);
		 if (t == 1) a = i;
		 if (t == N) b = i;
	}
	int ans = a - 1 + 1;
	ans = std::max(ans, b - 1 + 1);
	ans = std::max(ans, N - a + 1);
	ans = std::max(ans, N - b + 1);
	printf("%d\n", ans - 1);
	return 0;
}