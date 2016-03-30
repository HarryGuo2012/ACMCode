#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200000 + 10, MOD = 1e9 + 7;

struct Entry {
  int s, t, l;
  bool operator < (const Entry &rhs) const {
    return l > rhs.l;
  }
} E[MAXN], F[MAXN << 2], tp[MAXN << 2];

int dsu[MAXN], n, m;

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int reduce(Entry E[], int sz, int len) {
  static int ok[MAXN], cnt;
  if (sz == 0) return 0;
  for (int i = 0; i < n; ++ i) dsu[i] = i;
  for (int i = cnt = 0; i < sz; ++ i) {
    int u = get(E[i].s), v = get(E[i].t);
    if (u != v) {
      ok[cnt ++] = i << 1;
      dsu[u] = v;
    }
    u = get(E[i].s + E[i].l - len);
    v = get(E[i].t + E[i].l - len);
    if (u != v) {
      ok[cnt ++] = i << 1 | 1;
      dsu[u] = v;
    }
  }
  for (int i = 0; i < cnt; ++ i) {
    tp[i] = E[ok[i] >> 1];
    if (ok[i] & 1) {
      tp[i].s += tp[i].l - len;
      tp[i].t += tp[i].l - len;
    }
    tp[i].l = len;
  }
  memcpy(E, tp, sizeof(Entry) * cnt);
  return cnt;
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i < m; ++ i) {
      scanf("%d%d%d", &E[i].s, &E[i].t, &E[i].l);
      E[i].s --; E[i].t --;
    }
    sort(E, E + m);
    int len = 1, tot = 0;
    while (len < n) len <<= 1;
    for (int i = 0; len >= 1; len >>= 1) {
      while (i < m && E[i].l >= len) {
        F[tot ++] = E[i ++]; 
      }
      tot = reduce(F, tot, len);
    }
    for (int i = 0; i < n; ++ i) dsu[i] = i;
    for (int i = 0; i < tot; ++ i) {
      int u = get(F[i].s), v = get(F[i].t);
      if (u != v) dsu[u] = v;
    }
    int ret(1);
    for (int i = 0; i < n; ++ i) {
      if (get(i) == i) ret = ret * 26ll % MOD;
    }
    printf("%d\n", ret);
  }
  return 0;
}
