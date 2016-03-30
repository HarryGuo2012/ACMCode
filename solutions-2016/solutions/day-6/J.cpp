/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int MOD = 1e9 + 7;
const int N = 2000;

int n, p[N], f[N], cnt[N], dp[N + 1];

void Add( int &a, int b ) { if ((a += b) >= MOD) a -= MOD; }
int Mul( int a, int b ) { return (long long)a * b % MOD; }

struct Fenwick {
	int t[N];

	void clear() {
		memset(t, 0, sizeof(t));
	}
	void add( int y, int d ) {
		for (int x = y; x < n; x |= x + 1)
			Add(t[x], d);
	}
	int get( int x ) {
		int r = 0;
		for (; x >= 0; x &= x + 1, x--) 
			Add(r, t[x]); 
		return r;
	}
} tree;

int main() {
	scanf("%d", &n);
	forn(i, n) 
		scanf("%d", &p[i]), p[i]--, f[i] = 1;
	forn(k, n) {
		cnt[k] = accumulate(f, f + n, 0LL) % MOD;
		tree.clear();
		forn(i, n) {
			int tmp = tree.get(p[i]);
			tree.add(p[i], f[i]);
			f[i] = tmp;
		}
	}
	dp[1] = 1;
	forn(i, n - 1)
		for (int j = n; j > 0; j--) 
			dp[j] = Mul(dp[j], j), Add(dp[j], dp[j - 1]);

	int ans = 0, fact = 1;
	forn(j, n) 
		Add(ans, Mul(Mul(cnt[j], dp[j + 1]), fact = Mul(fact, j + 1)));
	printf("%d\n", ans);
	return 0;
}
