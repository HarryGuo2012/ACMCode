#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <set>

#define INF (INT_MAX - 5)

#define MAX_N 16

int T, N;

int p[MAX_N], a[MAX_N];
bool used[MAX_N];

//std::set<int> se[2][1 << MAX_N];

//int dp[2][MAX_N][1 << MAX_N];

int dp[1 << MAX_N][MAX_N];
bool vis[1 << MAX_N][MAX_N];
int ones[1 << MAX_N];

int getOne(int x) {
	int res = 0;
	while (x) {
		if (x & 1) res++;
		x >>= 1;
	}
	return res;
}

int cnt[1 << MAX_N];

bool cmp(int x, int y) {
	return cnt[x] < cnt[y];
}

int must[MAX_N];

void update(int &x, int y) {
	x = std::max(x, y);
}

int pos[MAX_N];

int main() {
	scanf("%d", &T);
	int cas = 0;
	for (int i = 0; i < (1 << MAX_N); i++)
		cnt[i] = getOne(i);
	while (T--) {
		for (int s = 0; s < (1 << MAX_N); s++)
			for (int i = 0; i < MAX_N; i++)
				dp[s][i] = -INF;
		memset(must, 0, sizeof(must));
		memset(vis, 0, sizeof(vis));
		memset(p, 0, sizeof(p));
		memset(a, 0, sizeof(a));
		memset(used, 0, sizeof(used));
		memset(pos, 0, sizeof(pos));
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			a[i] = u;//id i is u
			p[i] = v;//id i must sit in pos v
			if (v != -1)
				used[v] = 1, pos[v] = i;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				if (p[j] != -1 && p[j] <= i)
					must[i] |= (1 << j);
		}
		int freeNum = 0;
		for (int i = 0; i < N; i++) {
			if (p[i] == -1)
				freeNum |= (1 << i);
		}
		if (used[0]) {
			dp[1 << pos[0]][pos[0]] = 0;
		 	vis[1 << pos[0]][pos[0]] = 1;
		}
		else {
			for (int i = 0; i < N; i++) {
				dp[1 << i][i] = 0;
				vis[1 << i][i] = 1;
			}
		}
		memset(ones, 0, sizeof(ones));
		for (int i = 0; i < (1 << N); i++)
			ones[i] = i;
		std::sort(ones, ones + (1 << N), cmp);
		for (int mas = 0; mas < (1 << N); mas++) {
			int mask = ones[mas];
			int i = cnt[mask] - 1;
			for (int j = 0; j < N; j++) {// num id j
				if (used[i] && p[j] != i) continue;
				if ((mask >> j & 1) == 0) continue;
				if ((mask & must[i]) != must[i]) continue;
				int rest = mask ^ must[i];
				if ((rest & freeNum) != rest) continue;
				for (int k = 0; k < N; k++) {
					if (k != j && (mask >> k & 1) && vis[mask ^ (1 << j)][k])
						update(dp[mask][j], dp[mask ^ (1 << j)][k] + a[j] * a[k]);
				}
				vis[mask][j] = 1;
			}
		}
		int ans = -INF;
		for (int i = 0; i < N; i++)
			update(ans, dp[(1 << N) - 1][i]);
		printf("Case #%d:\n%d\n", ++cas, ans);
	}
	return 0;
}