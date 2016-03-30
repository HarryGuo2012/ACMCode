/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define __USE_MINGW_ANSI_STDIO 1

#include <cstring>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define zero(a) memset(a, 0, sizeof(a))

typedef long long ll;

const int N = 1e6;
const int L = 1 << 30;
const int M = 1 << 15;
const ll inf = 1e18;

int n, k, x[2 * N], *up = x;
int cnt[M + 1], *x2 = x + N;
ll sx[2 * N + 1];

inline ll f( int l, int r ) {
  return sx[l] - sx[(l + r + 1) >> 1] + sx[r] - sx[(l + r) >> 1];
}

bool solve( ll sum ) {
  int r = 0;
  if (f(n - 1, n - 1 + n) <= sum)
    return 1;
  forn(l, n) {
    while (f(l, r + 1) <= sum)
      r++;
    up[l] = r, up[l + n] = r + n;
  }
  for (int l = 0; l <= up[0]; l++) {
    int x = l;
    forn(i, k) 
      if ((x = up[x]) >= l + n) 
        return 1;
    if (up[x] < l + n)
      return 0;
  }
  return 0;
}

void stamp( const char *s ) {
  fprintf(stderr, "time = %.2f : %s\n", 1. * clock() / CLOCKS_PER_SEC, s); // stamp
}

int main() {
  unsigned seed, add;
  cin >> n >> k >> seed >> add;
  assert(n <= N);
  forn(i, n) {
    x[i] = seed = (seed * 239017 + add) & (L - 1);
    cnt[(seed & 32767) + 1]++;
  }
  stamp("read");

  forn(i, M) cnt[i + 1] += cnt[i];
  forn(i, n) x2[cnt[x[i] & 32767]++] = x[i];
  zero(cnt);
  forn(i, n) cnt[(x[i] >> 15) + 1]++;
  forn(i, M) cnt[i + 1] += cnt[i];
  forn(i, n) x[cnt[x2[i] >> 15]++] = x2[i];
  stamp("sort");

  forn(i, n)
    sx[i + 1] = sx[i] + x[i];
  forn(i, n)
    sx[n + i + 1] = sx[n + i] + x[i] + L;

  int have = (n + k - 1) / k;
  ll l = inf, r = -inf, m;
  forn(i, n) {
    ll F = f(i, i + have);
    l = min(l, F);
    r = max(r, F);
  }
  stamp("precalc");

  int cnt = 0;
  fprintf(stderr, "binary search on [%lld..%lld]\n", l, r);
  for (; l != r; cnt++)
    if (solve(m = (l + r) / 2))
      r = m;
    else
      l = m + 1;
  stamp("binary search");

  fprintf(stderr, "binary search: %d steps\n", cnt);
  cout << l << endl;
  return 0;
}
