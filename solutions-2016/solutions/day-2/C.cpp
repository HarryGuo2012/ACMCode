#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 10, MOD = 1e9 + 7;

LL C[MAXN];
int x[MAXN], y[MAXN];
int n, a, b, c, m;

LL pm(LL a, LL n = MOD - 2) {
  LL r(1);
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % MOD;
    a = a * a % MOD;
  }
  return r;
}

LL solve(int l, int r) {
  LL rx(0), ry(0);
  for (int t = x[l] - m; t <= x[l] + m; t += 2) {
    LL tp(1);
    for (int i = l; i < r && tp; ++ i) {
      int d = m - abs(t - x[i]);
      if (d < 0 || d % 2 == 1) tp = 0;
      else tp = tp * C[d >> 1] % MOD;
    }
    rx += tp;
  }
  for (int t = y[l] - m; t <= y[l] + m; t += 2) {
    LL tp(1);
    for (int i = l; i < r && tp; ++ i) {
      int d = m - abs(t - y[i]);
      if (d < 0 || d % 2 == 1) tp = 0;
      else tp = tp * C[d >> 1] % MOD;
    }
    ry += tp;
  }
  return (rx % MOD) * (ry % MOD) % MOD;
}

int main() {
  while (scanf("%d%d%d%d", &n, &a, &b, &m) == 4) {
    c = n - a - b; C[0] = 1;
    for (int i = 1; i <= m; ++ i) {
      C[i] = C[i - 1] * (m - i + 1) % MOD * pm(i) % MOD;
    }
    for (int i = 0; i < n; ++ i) {
      int tx, ty; scanf("%d%d", &tx, &ty);
      x[i] = tx + ty, y[i] = tx - ty;
    }
    LL ra = solve(0, a), rb = solve(a, a + b), rc = solve(a + b, n);
    LL ret = ra * rb % MOD * rc % MOD;
    ret += 2 * solve(0, n);
    ret -= rc * solve(0, a + b) % MOD;
    ret -= ra * solve(a, n) % MOD;
    rotate(x + a, x + a + b, x + n);
    rotate(y + a, y + a + b, y + n);
    ret -= rb * solve(0, a + c) % MOD;
    ret %= MOD; ret += MOD; ret %= MOD;
    printf("%lld\n", ret);
  }
  return 0;
}
