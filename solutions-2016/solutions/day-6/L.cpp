/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#  define err(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef unsigned long long ull;

const int maxC = 1e5;

int n, C;
ull a[maxC / 64 + 2];

inline int getBit( int i ) { return (a[i >> 6] >> (i & 63)) & 1; }
inline void setBit( int i ) { a[i >> 6] |= 1ULL << (i & 63); }

inline double area( double a, double b, double c ) {
	double p = (a + b + c) / 2;
	return p * (p - a) * (p - b) * (p - c);
}

inline int readInt() {
	int c = getchar(), x = 0;
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x;
}

void solve() {
	n = readInt();
	C = readInt();
	assert(C <= maxC);
	memset(a, 0, sizeof(a[0]) * (C / 64 + 2)); 
	forn(i, n)	
		setBit(readInt());
	while (!getBit(C))
		C--;
		                                    		
	int x = 1;
	double inf = 1e100, ans = inf;
	for (int diff = 1; 2 * diff + 2 <= C; diff++) {
		while (x <= diff || !getBit(x))
			x++;
		int c = x + 1, lim, add, shift;
		for (; c & 63; c++)
			if (getBit(c) && getBit(c + diff)) {
				ans = min(ans, area(x, c, c + diff));	
				goto end;
			}
		lim = (C - diff) >> 6, add = diff >> 6, shift = diff & 63;
		c >>= 6;
		while (c <= lim && !(a[c] & ((a[c + add] >> shift) | (a[c + add + 1] << (64 - shift)))))
			c++;
		c <<= 6;
		forn(_, 64) {
			if (getBit(c) && getBit(c + diff)) {
				ans = min(ans, area(x, c, c + diff));	
				goto end;
			}
			c++;
		}
		end:;
	}
	if (ans == inf)
		puts("-1");
	else
		printf("%.15f\n", sqrt(ans));
}

int main() {
	int tn = readInt();
	while (tn--)
		solve();
	fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
	return 0;
}
