#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const ull inf = 1ull << 63;
const double alpha = 0.8;

const int MAXN = 200000 + 10, U = 16;
int n, m;

namespace ST {// Scapegoat Tree
  struct Node {
    Node *ch[2], *fa;
    ull tl, tr, tm;
    int sz;
  } pool[MAXN], *np, *null, *rt;
  Node* id[MAXN]; int cnt;
  Node* alloc(Node* f, ull a, ull b) {
    np->sz = 1; np->fa = f;
    np->ch[0] = np->ch[1] = null;
    np->tl = a, np->tr = b; np->tm = (a + b) >> 1;
    return np ++;
  }
  void clr() {
    null = pool; np = pool + 1; rt = null;
    null->fa = null->ch[0] = null->ch[1] = null;
    null->sz = 0; null->tl = null->tr = null->tm = 0;
  }
  Node* ins(Node* o, int c) {
    o->sz ++;
    if (o->ch[c] == null) {
      if (!c) o->ch[c] = alloc(o, o->tl, o->tm);
      else o->ch[c] = alloc(o, o->tm, o->tr);
      return o->ch[c];
    }
    else return ins(o->ch[c], c);
  }
  void dfs(Node* o) {
    if (o == null) return;
    dfs(o->ch[0]);
    id[++ cnt] = o;
    dfs(o->ch[1]);
  }
  Node* build(Node* f, int l, int r, ull a, ull b) {
    if (l > r) return null;
    int m = (l + r) >> 1;
    Node *o = id[m];
    o->fa = f; o->sz = 1;
    o->ch[0] = o->ch[1] = null;
    o->tl = a; o->tr = b; o->tm = (a + b) >> 1;
    if (l == r) return o;
    o->ch[0] = build(o, l, m - 1, a, o->tm);
    o->ch[1] = build(o, m + 1, r, o->tm, b);
    o->sz += o->ch[0]->sz + o->ch[1]->sz;
    return o;
  }
  Node* rebuild(Node* o) {
    cnt = 0; dfs(o);
    return build(o->fa, 1, cnt, o->tl, o->tr);
  }
  Node* kth(int k) {
    for (Node* o = rt; ; ) {
      o->sz ++;
      int rk = o->ch[0]->sz + 1;
      if (k == rk) return o;
      if (k < rk) o = o->ch[0];
      else k -= rk, o = o->ch[1];
    }
  }
  Node* ins_kth(int k, Node *o = null) {
    if (rt == null) return rt = alloc(null, 0, inf);
    if (k == 1) o = ins(rt, 0);
    else if (k > rt->sz) o = ins(rt, 1);
    else {
      o = kth(k);
      if (o->ch[0] != null) o = ins(o->ch[0], 1);
      else o->ch[0] = alloc(o, o->tl, o->tm), o = o->ch[0];
    }
    int dep(1);
    Node *z = o;
    while (z->fa != null) z = z->fa, ++ dep;
    if (dep < log(np - pool) / log(1.0 / alpha)) return o;
    for (z = o; max(z->ch[0]->sz, z->ch[1]->sz) < alpha * z->sz; z = z->fa);
    if (z == null) return o;
    if (z == rt) rt = rebuild(z);
    else {
      Node *y = z->fa;
      int c = y->ch[1] == z;
      y->ch[c] = rebuild(z);
    }
    return o;
  }
  int rank(ull v) {
    int ret(0);
    for (Node *o = rt; ; ) {
      if (v == o->tm) return ret + 1 + o->ch[0]->sz;
      if (v < o->tm) o = o->ch[0];
      else ret += 1 + o->ch[0]->sz, o = o->ch[1];
    }
    return -1;
  }
  inline ull getID(int k) {
    return pool[k].tm;
  }
}

using ST::getID;
void takemax(int &x, int y) {
  if (x == -1 || (y != -1 && getID(x) < getID(y))) x = y;
}
void takemin(int &x, int y) {
  if (x == -1 || (y != -1 && getID(x) > getID(y))) x = y;
}

namespace DST {// Dynamic 4-D Segment Tree
  const int SIZE = U * U * U * 8;
  struct W {
    int a, b;
    W(): a(-1), b(-1) {}
    W(int x, int y): a(x), b(y) {}
  };
  struct Node {
    int ls, rs, x;
    W ps[2], ss[2];
    void clr() {
      ls = rs = x = -1;
      ps[0] = ps[1] = ss[0] = ss[1] = W();
    }
    void updP(int u, int v) {// u-th is v
      if (v == ps[0].a || ps[0].a == -1) {takemin(ps[0].b, u); ps[0].a = v; return;}
      if (v == ps[1].a || ps[1].a == -1) {takemin(ps[1].b, u); ps[1].a = v; return;}
      ull x = getID(u), y = getID(ps[0].b), z = getID(ps[1].b);
      if (x < y) ps[1] = ps[0], ps[0] = W(v, u);
      else if (x < z) ps[1] = W(v, u);
    }
    void updS(int u, int v) {// u-th is v
      if (v == ss[0].a || ss[0].a == -1) {takemax(ss[0].b, u); ss[0].a = v; return;}
      if (v == ss[1].a || ss[1].a == -1) {takemax(ss[1].b, u); ss[1].a = v; return;}
      ull x = getID(u), y = getID(ss[0].b), z = getID(ss[1].b);
      if (x > y) ss[1] = ss[0], ss[0] = W(v, u);
      else if (x > z) ss[1] = W(v, u);
    }
    void upd(int u, int v) {// u-th is v
      updP(u, v); updS(u, v);
      if (ps[1].a != -1 && getID(ps[1].b) < getID(ps[0].b)) swap(ps[0], ps[1]);
      assert(ps[1].a != ps[0].a);
      if (ss[1].a != -1 && getID(ss[1].b) > getID(ss[0].b)) swap(ss[0], ss[1]);
      assert(ss[1].a != ss[0].a);
    }
  } pt[SIZE];
  int sz, rt, rx, ry, x[4];
  void clr() {rt = -1; sz = 0;}
  int alloc() {
    pt[sz].clr(); return sz ++;
    return sz ++;
  }
  void ins(int d, int &o, int l, int r) {
    if (o == -1) o = alloc();
    if (d == 2) pt[o].upd(m, x[3]);
    else ins(d + 1, pt[o].x, 0, U);
    if (l + 1 == r) return;
    int m = (l + r) >> 1;
    if (x[d] < m) ins(d, pt[o].ls, l, m);
    else ins(d, pt[o].rs, m, r);
  }
  void ask(int d, int o, int l, int r, int L, int R) {
    if (L >= R || o == -1) return;
    if (L <= l && R >= r) {
      if (d == 2) {
        if (pt[o].ps[0].a != x[3]) takemin(rx, pt[o].ps[0].b);
        if (pt[o].ps[1].a != x[3]) takemin(rx, pt[o].ps[1].b);
        if (pt[o].ss[0].a != x[3]) takemax(ry, pt[o].ss[0].b);
        if (pt[o].ss[1].a != x[3]) takemax(ry, pt[o].ss[1].b);
      }
      else {
        ask(d + 1, pt[o].x, 0, U, 0, x[d + 1]);
        ask(d + 1, pt[o].x, 0, U, x[d + 1] + 1, U);
      }
      return;
    }
    int m = (l + r) >> 1;
    if (m > L) ask(d, pt[o].ls, l, m, L, R);
    if (m < R) ask(d, pt[o].rs, m, r, L, R);
  }
};

int main() {
  while (scanf("%d", &n) == 1) {
    ST::clr(); DST::clr();
    int last = m = 0;
    for (int i = 0, k; i < n; ++ i) {
      char t[10]; scanf("%s", &t);
      if (t[0] == '+') {
        m ++; scanf("%d", &k); k ^= last;
        for (int j = 0; j < 4; ++ j) {
          scanf("%d", DST::x + j);
          DST::x[j] ^= last; DST::x[j] --;
        }
        ST::ins_kth(k);
        DST::ins(0, DST::rt, 0, U);
      }
      else {
        for (int j = 0; j < 4; ++ j) {
          scanf("%d", DST::x + j);
          DST::x[j] ^= last; DST::x[j] --;
        }
        DST::rx = DST::ry = -1;
        DST::ask(0, DST::rt, 0, U, 0, DST::x[0]);
        DST::ask(0, DST::rt, 0, U, DST::x[0] + 1, U);
        int l = DST::rx, r = DST::ry;
        if (l == -1 || r == -1) last = 0;
        else {
          l = ST::rank(getID(l)); assert(l != -1);
          r = ST::rank(getID(r)); assert(r != -1);
          last = r - l;
        }
        printf("%d\n", last);
      }
    }
  }
  return 0;
}
