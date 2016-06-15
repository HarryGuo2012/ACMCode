#include <cstdio>
#include <cmath>

int m, n;
const double pi = acos(-1);

#define MAX_N 17

int dp[MAX_N][MAX_N];

int main() {
	scanf("%d%d", &m, &n);
	for (m = 1; m < MAX_N; m++) {
		for (n = 1; n < MAX_N; n++) {
			double sum = 1;
			for (int i = 1; i <= m / 2; i++)
				for (int j = 1; j <= n / 2; j++)
					sum = sum * (4 * sqr(cos(i * pi / (m + 1))) + 4 * sqr(cos(j * pi / (n + 1))));
			dp[m][n] = sum + 0.5;
		}
	}
	
	return 0;
}