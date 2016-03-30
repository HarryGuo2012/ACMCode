#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define IS(a, i) (((a) >> (i)) & 1)
#define pb push_back

typedef pair<int, int> pii;

const int N = 400;

int n, k, maxW;
int w[N][N], c[N][N], f[N + 1][N + 1], p[N + 1][N + 1]; 
vector<pii> path;

inline void relax( int i, int j, int F, int P ) {
	if (f[i][j] > F)
		f[i][j] = F, p[i][j] = P;
}

int main() {
	scanf("%d%d%d", &n, &k, &maxW);
	assert(n <= N);
	forn(i, n)
		forn(j, n)
			scanf("%d", &w[i][j]);
	forn(i, n)
		forn(j, n)
			scanf("%d", &c[i][j]), c[i][j]--;

	int ans = k + 1;
	forn(mask, 1 << k) {
		int bn = __builtin_popcount(mask);
		if (!IS(mask, c[n - 1][n - 1]) || bn >= ans)
			continue;
		memset(f, 0x3F, sizeof(f));
		f[0][0] = 0;
		forn(i, n) {
			bool run = 0;
			forn(j, n) {
				if (!IS(mask, c[i][j]))
					continue;
				f[i][j] += w[i][j];
				if (f[i][j] <= maxW) {
					relax(i + 1, j, f[i][j], 0);
					relax(i, j + 1, f[i][j], 1);
					run = 1;
				}
			}
			if (!run)
		    	break;
		}
		if (f[n - 1][n - 1] <= maxW) {
			ans = bn;
			path.clear();
			int i = n - 1, j = n - 1;
			while (i || j)
				path.pb(pii(i, j)), (p[i][j] ? j : i) -= 1;
			path.pb(pii(i, j));
		}
	}
	printf("%d\n", ans == k + 1 ? -1 : ans);
	reverse(path.begin(), path.end());
	for (auto p : path)
		printf("%d %d ", p.first + 1, p.second + 1);
	return 0;
}
