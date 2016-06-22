#include <cstdio>
#include <algorithm>
#include <cstring>

void update(int &x, int a) {
	x = std::max(x, a);
}

#define MAX_N 1003
#define MAX_K 11

int dp[MAX_N][MAX_N][MAX_K], dp2[MAX_N][MAX_N][MAX_K];
char s[MAX_N], t[MAX_N];

int N, M, K;

int main() {
	scanf("%d%d%d", &N, &M, &K);
	scanf("%s%s", s + 1, t + 1);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			for (int k = 1; k <= K; k++) {
				if (s[i] == t[j]) {
					update(dp[i][j][k], dp2[i - 1][j - 1][k - 1] + 1);
					update(dp[i][j][k], dp[i - 1][j - 1][k] + 1);
				}
				update(dp2[i][j][k], dp2[i - 1][j - 1][k]);
				update(dp2[i][j][k], dp2[i - 1][j][k]);
				update(dp2[i][j][k], dp2[i][j - 1][k]);
				update(dp2[i][j][k], dp[i][j][k]);
			}
	printf("%d\n", dp2[N][M][K]);
	return 0;
}