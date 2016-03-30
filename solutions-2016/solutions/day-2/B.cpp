#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXN = 3000 + 10;
LL dp[MAXN];
int x[MAXN], n;

inline LL sqr(LL x) {return x * x;}

int main() {
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i < n; ++ i) scanf("%d", x + i);
    if (n == 1) {puts("0\n0"); continue;}
    dp[n - 2] = 2 * sqr(x[n - 1] - x[n - 2]);
    for (int i = n - 3; i >= 0; -- i) {
      dp[i] = 1ll << 60;
      LL sum = sqr(x[i + 1] - x[i]);
      for (int j = i + 2, k(i); j < n; ++ j) {
        while (x[k] - x[i] < x[j] - x[k]) ++ k;
        LL cost = sum + dp[j - 1] - sqr(x[j] - x[j - 1]);
        dp[i] = min(dp[i], cost + sqr(min(x[k] - x[i], x[j] - x[k - 1])));
        sum += sqr(x[j] - x[j - 1]);
      }
    }
    printf("%lld\n", dp[0]);
  }
  return 0;
}
