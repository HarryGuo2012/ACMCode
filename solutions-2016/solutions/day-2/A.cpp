#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000000 + 10;
typedef long long LL;
int a[MAXN], l[MAXN], r[MAXN];
LL b[MAXN];
int n, m;

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    l[0] = r[0] = 0;
    for (int i = 0; i < n; ++ i) {
      scanf("%d", a + i); b[i] = 0;
      int tl = l[i] + a[i], tr = r[i] + a[i];
      tl = max(tl, 0); tr = min(tr, m);
      if (tl > tr) {
        b[i] = -1;
        tl = 0; tr = m;
      }
      l[i + 1] = tl, r[i + 1] = tr;
    }
    LL tar = (l[n] + r[n]) / 2;
    for (int i = n - 1; i >= 0; -- i) {
      if (b[i] == -1) {
        LL x = (LL)tar - r[i] - a[i];
        LL y = (LL)tar - l[i] - a[i];
        b[i] = (x + y) / 2;
        tar -= a[i] + b[i];
      }
      else tar -= a[i];
    }
    for (int i = 0; i < n; ++ i) {
      printf("%lld%c", b[i],  " \n"[i == n - 1]);
    }
  }
  return 0;
}