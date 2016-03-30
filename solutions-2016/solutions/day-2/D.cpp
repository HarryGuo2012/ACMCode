#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000 + 10, MOD = 1e9 + 7, U = 50;

LL dp[2][MAXN][2][U + 1], S[U + 1][U + 1], C[U];
int p[MAXN], n, k;

void upd(LL *a, LL *b, int x, int y) {
  for (int i = 0; i <= k; ++ i) {
    if (x > y && i < k) a[i + 1] += b[i];
    a[i] += b[i]; a[i] %= MOD;
  }
}

int main() {
  S[0][0] = 1;
  for (int n = 1; n <= U; ++ n) {
    S[n][0] = 0;
    for (int k = 1; k <= n; ++ k) {
        S[n][k] = (k * S[n - 1][k] + S[n - 1][k - 1]) % MOD;
    }
  }
  while (scanf("%d%d", &n, &k) == 2) {
    for (int i = 1, fact = 1; i <= k; ++ i) {
      fact = (LL)fact * i % MOD;
      C[i] = S[k][i] * fact % MOD;
    }
    for (int i = 0; i < n; ++ i) {
      scanf("%d", p + i);
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0][1][0] = dp[0][0][0][0] = 1;
    for (int i = 0; i + 1 < n; ++ i) {
      int x = i & 1, y = x ^ 1;
      for (int j = 0; j <= i + !i; ++ j) {
        memset(dp[y][j], 0, sizeof(dp[y][j]));
      }
      for (int j = 0; j < (i + !i); ++ j) {
        LL *a, *b;
        // i + 1 left, i left
        upd(dp[y][j][0], dp[x][j][0], p[i + 1], p[i]);
        // i + 1 left, i right
        upd(dp[y][i][0], dp[x][j][1], p[i + 1], p[j]);
        // i + 1 right, i left
        upd(dp[y][i][1], dp[x][j][0], p[j], p[i + 1]);
        // i + 1 right, i right
        upd(dp[y][j][1], dp[x][j][1], p[i], p[i + 1]);
      }
    }
    LL ret(0);
    for (int i = 0; i < n; ++ i) {
      for (int o = 0; o < 2; ++ o) {
        for (int j = 1; j <= k; ++ j) {
            ret += dp[n & 1 ^ 1][i][o][j] * C[j] % MOD;
        }
      }
    }
    printf("%lld\n", ret % MOD);
  }
  return 0;
}
