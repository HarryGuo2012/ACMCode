#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_N 1111

int T;
char A[MAX_N], B[MAX_N], C[MAX_N];

int f[MAX_N][MAX_N], g[MAX_N][MAX_N];

int a[MAX_N], b[MAX_N];

int cas;

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		memset(a, 0 ,sizeof(a));
		memset(b, 0, sizeof(b));
		scanf("%s%s%s", A + 1, B + 1, C + 1);
		int n = strlen(A + 1), m = strlen(B + 1), k = strlen(C + 1);
		for (int i = 1; i <= n; i++) {
			if (A[i] == C[1]) {
				int t = 1, j = i;
				while (t <= k && j <= n) {
					if (A[j] == C[t]) t++;
					j++;
				}
				if (t == k + 1) a[i] = j - 1;
			}
		}
		for (int i = 1; i <= m; i++) {
			if (B[i] == C[1]) {
				int t = 1, j = i;
				while (t <= k && j <= m) {
					if (B[j] == C[t]) t++;
					j++;
				}
				if (t == k + 1) b[i] = j - 1;
			}
		}
		
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
				if (A[i] == B[j]) f[i][j] = std::max(f[i][j], f[i - 1][j - 1] + 1);
			}
		for (int i = n; i >= 1; i--)
			for (int j = m; j >= 1; j--) {
				g[i][j] = std::max(g[i + 1][j], g[i][j + 1]);
				if (A[i] == B[j]) g[i][j] = std::max(g[i][j], g[i + 1][j + 1] + 1);
			}
		int ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (a[i] && b[j]) ans = std::max(ans, f[i - 1][j - 1] + g[a[i] + 1][b[j] + 1] + k);
			}
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
}