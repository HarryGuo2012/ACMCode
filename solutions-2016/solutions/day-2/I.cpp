#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;

namespace MU { // Memory Buffer
  int buf[MAXN * 40], *p;
  void clr() {p = buf;}
  LL *allocL(int len) {
    LL *res = (LL*)p;
    memset(res, 0, sizeof(LL) * len);
    p += len * 2; return res;
  }
  int *allocI(int len) {
    memset(p, 0, sizeof(int) * len);
    p += len; return p - len;
  }
}

struct FenwickTree {
  LL u[MAXN];
  int n;
  void clr(int _n) {
    n = _n;
    memset(u, 0, sizeof(LL) * (n + 1));
  }
  void add(int x, LL v) {
    for (; x <= n; x += ~x & x + 1) u[x] += v;
  }
  LL sum(int x) {
    LL r(0);
    for (; x >= 0; x -= ~x & x + 1) r += u[x];
    return r;
  }
  LL sum(int l, int r) { // [l, r]
    if (l > r) return 0;
    else return sum(r) - sum(l - 1);
  }
};

struct Vector {
  int sz;
  vector<int> data;
  void clr() {
    sz = 0;
    data.clear();
  }
  int& operator[](int i) {return data[sz - i - 1];}
  const int& operator[](int i) const {return data[sz - i - 1];}
  void add(int x) {
    data.push_back(x);
    sz ++;
  }
  void swap(Vector &rhs) {
    std::swap(sz, rhs.sz);
    data.swap(rhs.data);
  }
};

struct Edge {
  int v, nx;
  Edge() {}
  Edge(int a, int b): v(a), nx(b) {}
} E[MAXN << 1];

int G[MAXN], n;

namespace Centroid {
  int total, rt, mins, curNode;
  int sz[MAXN], dep[MAXN], ht[MAXN];
  LL *tp[MAXN], *low[MAXN], *high[MAXN], *cnt;
  bool vs[MAXN];
  Vector down[MAXN];
  FenwickTree bit[2];

  void clr(int n) {
    memset(vs, 0, sizeof(vs[0]) * n);
  }
  void getCenter(int u, int f = -1) {
    int mx = 0; sz[u] = 1;
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v; if (v == f || vs[v]) continue;
      getCenter(v, u);
      mx = max(mx, sz[v]);
      sz[u] += sz[v];
    }
    mx = max(mx, total - sz[u]);
    if (mx < mins) mins = mx, rt = u;
  }
  void getSize(int u, int f = -1) {
    ht[u] = sz[u] = 1; down[u].clr();
    if (f != -1) dep[u] = dep[f] + 1;
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v; if (v == f || vs[v]) continue;
      getSize(v, u); sz[u] += sz[v];
      ht[u] = max(ht[u], ht[v] + 1);
    }
  }
  LL count(int u, int sq[], int m) {
    int mx = ht[u];
    LL *add1 = MU::allocL(mx + 1), *add2 = MU::allocL(mx + 1);
    LL *sub = MU::allocL(mx + 1), ret(0);
    for (int i = 0; i < m; ++ i) {
      LL *a = tp[sq[i]], s(0);
      for (int j = ht[sq[i]]; j >= 0; -- j) {
        ret += a[j] * (add1[j + 1] * (add1[j + 1] - 1) - sub[j + 1]);
        sub[j + 1] += s * (s - 1);
        add1[j + 1] += s; s += a[j];
      }
    }
    memset(sub, 0, sizeof(LL) * (mx + 1));
    for (int i = m - 1; i >= 0; -- i) {
      LL *a = tp[sq[i]], s(0);
      for (int j = ht[sq[i]]; j >= 0; -- j) {
        ret += a[j] * (add2[j + 1] * (add2[j + 1] - 1) - sub[j + 1]);
        sub[j + 1] += s * (s - 1);
        add1[j + 1] -= s; ret += add1[j + 1] * add2[j + 1] * a[j] * 2;
        add2[j + 1] += s; s += a[j];
      }
    }
    return ret;
  }
  void merge(int u, int offset) {
    offset -= ht[u];
    int curSize = ht[u] * 2;
    for (int i = 0; i < curSize; ++ i) {
      bit[0].add(i + offset, high[u][i]);
      bit[1].add(i + offset, low[u][i]);
    }
  }
  bool cmpByHeight(int u, int v) {
    return ht[u] > ht[v];
  }
  void mergeDown(int u, int f, int m) {
    int *pt = MU::allocI(m); m = 0;
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v;
      if (v != f && !vs[v]) pt[m ++] = v;
    }
    sort(pt, pt + m, cmpByHeight);
    down[u].clr();
    if (m >= 1) {
      int sz = m == 1 ? 0 : ht[pt[1]], extraSum = Centroid::sz[pt[0]];
      int *sum = MU::allocI(sz);
      for (int i = 0; i < m; ++ i) {
        int v = pt[i];
        int upp = min(sz, down[v].sz);
        for (int j = 0; j < upp; ++ j) {
          sum[j] += down[v][j];
          if (!i) extraSum -= sum[j];
        }
      }
      int sumHigh(extraSum), sumLow(extraSum);
      int *sufSum = MU::allocI(m);
      sufSum[0] = extraSum;
      for (int h = sz; h >= 1; -- h) { // key = h - dep[u] + ht[curNode]
        sumHigh += sum[h - 1];
        int key = h - dep[u] + ht[curNode];
        for (int i = 0; i < m; ++ i) {
          int v = pt[i]; if (down[v].sz < h) break;
          low[curNode][key] += 1ll * down[v][h - 1] * (sumLow - sufSum[i]);
          high[curNode][key] += 2ll * down[v][h - 1] * (sumLow - sufSum[i]);
          sufSum[i] += down[v][h - 1];
          high[curNode][key] += 1ll * down[v][h - 1] * (sum[h - 1] - down[v][h - 1]);
        }
        sumLow += sum[h - 1];
      }
      int key = ht[curNode] - dep[u]; // low = 0
      low[curNode][key] += sumLow;

      down[u].swap(down[pt[0]]);
      for (int i = 0; i < sz; ++ i) {
        down[u][i] = sum[i];
      }
      MU::p -= m;
      MU::p -= sz;
    }
    down[u].add(1);
    MU::p -= m;
  }
  LL dfs(int u, int f = -1, int o = 0) {
    cnt[dep[u]] ++;
    LL ret(0), m(0);
    ret += bit[1].sum(0, dep[u] + ht[rt] - 1) * 2;
    ret += bit[0].sum(dep[u] + ht[rt] + 1, ht[rt] * 2);
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v; if (v == f || vs[v]) continue;
      ret += dfs(v, u, o); m ++;
    }
    if (o) mergeDown(u, f, m);
    return ret;
  }
  LL solve(int u, int tot) {
    total = tot; mins = total * 2;
    getCenter(u);
    u = rt; vs[u] = 1; dep[u] = 0;
    getSize(u);

    MU::clr();
    int *sq = MU::allocI(tot);
    int m = 0, offset = ht[u];

    bit[0].clr(offset * 2); // low, (high, high)
    bit[1].clr(offset * 2); // high, (low, high)

    LL ret(0); m = tot = 0;
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v; if (vs[v]) continue;
      sq[m ++] = curNode = v;
      cnt = tp[v] = MU::allocL(ht[v] + 1);

      low[v] = MU::allocL(ht[v] * 2);
      high[v] = MU::allocL(ht[v] * 2);

      ret += dfs(v, u, 1);
      merge(v, offset);

      ret += 2ll * sz[v] * tot; // low = 0
      tot += sz[v];
    }
    ret += count(u, sq, m); // common point is centroid

    ret += bit[0].sum(offset + 1, offset * 2); // low end is centroid
    ret += bit[1].sum(0, offset - 1) * 2; // high end is centroid

    bit[0].clr(offset * 2); // low, (high, high)
    bit[1].clr(offset * 2); // high, (low, high)
    for (int i = m - 1; i >= 0; -- i) {
      ret += dfs(sq[i], u);
      merge(sq[i], offset);
    }
    //cout << "center: " << rt << ", add: " << ret << endl;
    for (int it = G[u]; ~it; it = E[it].nx) {
      int v = E[it].v; if (vs[v]) continue;
      ret += solve(v, sz[v]);
    }
    return ret;
  }
}

int main() {
  while (scanf("%d", &n) == 1) {
    memset(G, -1, sizeof(G[0]) * n);
    for (int i = 1, sz = 0; i < n; ++ i) {
      int u, v; scanf("%d%d", &u, &v);
      -- u; -- v;
      E[sz] = Edge(v, G[u]); G[u] = sz ++;
      E[sz] = Edge(u, G[v]); G[v] = sz ++;
    }
    Centroid::clr(n);
    LL ret =(LL)n * (n - 1) * (n - 2) - Centroid::solve(0, n);
    printf("%lld\n", ret);
  }
  return 0;
}
