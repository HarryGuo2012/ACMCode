#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 1111

struct node {
	int a, b;
}s[MAX_N];

int N, M;
int dp[MAX_N][MAX_N];

bool cmp(node x, node y) {
	return x.b > y.b;
}

int A[MAX_N][MAX_N];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &s[i].a);
	for (int i = 1; i <= N; i++)
		scanf("%d", &s[i].b);
	std::sort(s + 1, s + 1 + N, cmp);
	for (int i = 1; i <= N; i++)
		A[i][1] = s[i].a;
	for (int i = 1; i <= N; i++)
		for (int j = 2; j <= M; j++)
			A[i][j] = std::max(A[i][j - 1] - s[i].b, 0);
	int ans = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - 1] + A[i][j]);
			ans = std::max(ans, dp[i][j]);
		}
	printf("%d\n", ans);
	return 0;
}