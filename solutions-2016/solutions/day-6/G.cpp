/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()

typedef unsigned uint;

const int N = 700;

char s[N + 1], t[N + 1];
int sn, tn, f[N + 2][N + 1], lcp[N + 1][N + 1];
unsigned p[N + 2][N + 1];

inline void relax( int i, int j, int F, unsigned P ) {
	if (f[i][j] > F)
		f[i][j] = F, p[i][j] = P; 
}

int main() {
	gets(s), sn = strlen(s);
	gets(t), tn = strlen(t);
	memset(f, 0x3F, sizeof(f));
	for (int i = sn - 1; i >= 0; i--)
		for (int j = tn - 1; j >= 0; j--)
			lcp[i][j] = (s[i] == t[j] ? 1 + lcp[i + 1][j + 1] : 0);
	#define ANS sn + 1, 0
	relax(ANS, sn, sn << 2);
	for (int len = 1; len < sn; len++) { 
		if (s[len - 1] != t[len - 1]) {
			relax(ANS, len + (len != sn), (len << 2) + (len != sn));
			break;
		}
		relax(len, len, len, -2);
	}
	f[0][0] = 1;
	forn(i, sn)
		forn(j, tn) {
			int F = f[i][j], x = j;
			relax(i + 1, j, F, -1);
			for (int len = 1; i + len <= sn; len++) {
				if (i + len == sn)
					x = tn - len;
				while (x + len <= tn && lcp[i][x] < len)
					x++;
				if (x + len > tn) {
					relax(ANS, F + len + (i + len != sn), ((((uint)i << 20) + (j << 10) + len) << 2) + 2 + (i + len != sn));
					break;
				}
				relax(i + len, x + len, F + len + 1, (j << 10) + len);
			}
		}
	int i = sn + 1, j = 0, len, no_star = 0;
	string ans;
	while (i) {
		unsigned P = p[i][j];
		//fprintf(stderr, "%d, %d : %d\n", i, j, P);
		assert(sz(ans) <= 2 * N);
		if (i > sn) {
			if (P & 1)
				ans = "*";
			len = (P >> 2) & 1023;
			if (P & 2) 
				j = (P >> 12) & 1023, i = (P >> 22);
			else 
				i = j = 0, no_star = 1;
		} else if (P == (uint)-1) {
			len = 0, i--;
		} else if (P == (uint)-2) {
			len = i, i = j = 0;
			no_star = 1;
		} else {
			len = P & 1023;
			j = P >> 10, i -= len;
			ans += "*";
		}
		forn(k, len)
			ans += s[i + len - 1 - k];
	}
	if (!no_star)
		ans += "*";
	reverse(all(ans));
	cout << ans << endl;
	fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
	return 0;
}
