#include <cstdio>
#include <algorithm>

int m;

#define MAX_N 222

int g[MAX_N][MAX_N];

int get(int a, int b) {
	return ((a + 1) * (b + 1) - g[a][b] - 1) / 2;
}

bool isSq[MAX_N * MAX_N];

int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			g[i][j] = std::__gcd(i, j);
	for (int i = 1; i < MAX_N; i++)
		isSq[i * i] = 1;
	int ans = 0;
	//printf("%d\n", get(1, 1));
	for (int a = 1; a <= m; a++)
		for (int b = 1; b <= m; b++)
			for (int c = 1; c <= m; c++)
				for (int d = 1; d <= m; d++) {
					int cnt = get(a, b) + get(b, c) + get(c, d) + get(d, a) - a - b - c - d + 1;
					//printf("%d %d %d %d %d\n", a, b, c, d, cnt);
					ans += isSq[cnt];
				}
	printf("%d\n", ans);
	return 0;
}