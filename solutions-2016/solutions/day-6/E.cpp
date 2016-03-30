/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define IS(a, i) (((a) >> (i)) & 1)
#define pb push_back

inline int readInt() {
	int c = getchar(), x = 0;
	if (c == 'a' || c == 'b') {
		getchar();
		return -1;
	}
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}

const int N = 5e4;
const int M = 5e5;

typedef pair <int, int> pii;

int n, m, fr[M], len[M], f[N], rest[M], diff[M];
vector<int> was[M], c[M];
vector<pii> link[N];

void dfs( int v, int value );

inline void use_rule( int i ) {
	int sum = len[i], diff = 0;
	for (int to : c[i])
		if (f[to] == 3) 
			diff = 1;
		else 
			sum ^= (f[to] == 2);
	dfs(fr[i], sum);
	dfs(fr[i], sum ^ diff);
}

inline void dfs( int v, int value ) {
	if (IS(f[v], value))
		return;
	f[v] |= 1 << value;
	for (pii p : link[v]) {
		int i = p.first, j = p.second, run = 0;
		if (was[i][j] == 0)
			run = 1, was[i][j] = 1, rest[i]--;
		if (diff[i] == 0 && f[v] == 3)
			run = 1, diff[i] = 1;
		if (run && !rest[i])
			use_rule(i);
	}
}

int main() {
	while (1) {
		n = readInt();
		m = readInt();
		if (!n && !m)
			break;
		forn(i, n)
			link[i].clear();
		forn(i, m) {
			fr[i] = readInt() - 1;
			int k = readInt();
			len[i] = rest[i] = diff[i] = 0;
			c[i].clear();
			was[i].clear();
			forn(j, k) {
				int a = readInt();
				if (a == -1)
					len[i] ^= 1;
				else {
					a--;
					link[a].pb(pii(i, was[i].size()));
					was[i].pb(0);
					c[i].pb(a);
					rest[i]++;
				}
			}
		}
		fill(f, f + n, 0);
		forn(i, m)
			if (!c[i].size())
				use_rule(i);
		puts(IS(f[0], 1) ? "YES" : "NO");
	}
	fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
}
