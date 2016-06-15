#include <cstdio>
#include <algorithm>

#define MAX_N 555

int dp[2][MAX_N][MAX_N];
int a[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];

int n, m;

int S(int xa, int ya, int xb, int yb) {
	return sum[xb][yb] - sum[xb][ya - 1] - sum[xa - 1][yb] + sum[xa - 1][ya - 1];
}

int ans;
bool first;

void output(int x) {
	printf("-----\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%d ", dp[x][i][j]);
		printf("\n");
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	first = true;
	for (int i = 1; i + 2 <= n; i++)
		for (int j = 1; j + 2 <= m; j++) {
			dp[1][i][j] = S(i, j, i + 2, j + 2) - S(i + 1, j, i + 1, j + 1);
			if (first) ans = dp[1][i][j], first = false;
			else ans = std::max(ans, dp[1][i][j]);
		}
	for (int k = 2; k <= n; k++) {
		for (int i = 1; i + 2 * k <= n; i++)
			for (int j = 1; j + 2 * k <= m; j++) {
				dp[k & 1][i][j] = -dp[1 - (k & 1)][i + 1][j + 1] - a[i + 1][j] + S(i, j, i + 2 * k, j + 2 * k);
				ans = std::max(dp[k & 1][i][j], ans);
			}
		//output(k & 1);
	}
	printf("%d\n", ans);
	return 0;
}