#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <complex>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define pbk pop_back
#define sz(s) ((int) (s).size())
#define all(x) (x).begin(), (x).end()
#ifdef LOCAL42
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#define cerr if (0) cerr
#endif
#if _WIN32 || __WIN32__ || _WIN64 || __WIN64__
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif
#define next _next
#define prev _prev
#define link _link
#define rank _rank
#define hash _hash
#define y1 yy1

typedef long long ll;
typedef long long llong;
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned long long ullong;
typedef unsigned long long lint;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long double ld;

const int inf = 1e9;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);
const int N = int(5e5) + 100;

int n, m;
vector<pair<int, char> > g[N];
char s[N];
int pv[N];
char pc[N];
pii dp1[N], dp2[N];

struct last {
    
    int last[26];
    vector<pair<int*, int> > changes;
    
    inline void init() {
        for (int i = 0; i < 26; ++i) {
            last[i] = -1;
        }
        changes.clear();
    }
    
    inline void set(int a, int b) {
        changes.pb({ last + a, last[a] });
        last[a] = b;
    }
    
    inline int mark() {
        return sz(changes);
    }
    
    inline int get(int a) {
        return last[a];
    }
    
    inline void rollback(int mark) {
        while (sz(changes) > mark) {
            *(changes.back().fs) = changes.back().sc;
            changes.pbk();
        }
    }
    
};

last last;

void dfs1(int v, int pv) {
    if (pv != -1) {
        g[v].erase(find(all(g[v]), mp(pv, pc[v])));
    }
    for (auto u : g[v]) {
        ::pv[u.fs] = v;
        pc[u.fs] = u.sc;
        dfs1(u.fs, v);
    }
}

void dfs2(int v, pii* dp) {
    int mark = last.mark();
    if (pv[v] != -1) {
        last.set(pc[v] - 'a', v);
    }
    pii ch(0, v);
    for (auto u : g[v]) {
        dfs2(u.fs, dp);
        ch = max(ch, dp[u.fs]);
    }
    if (ch.fs < m) {
        int ver = last.get(s[ch.fs] - 'a');
        if (ver != -1) {
            dp[ver] = max(dp[ver], { ch.fs + 1, ch.sc });
        }
    }
    dp[v] = max(dp[v], ch);
    last.rollback(mark);
}

int main() {
#ifdef LOCAL42
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        char c;
        scanf("%d %d %c", &a, &b, &c);
        --a;
        --b;
        g[a].pb({ b, c });
        g[b].pb({ a, c });
    }
    pv[0] = -1;
    dfs1(0, -1);
    scanf("%s", s);
    for (int i = 0; i < n; ++i) {
        dp1[i] = dp2[i] = mp(0, i);
    }
    last.init();
    dfs2(0, dp1);
    reverse(s, s + m);
    dfs2(0, dp2);
    for (int i = 0; i < n; ++i) {
        if (dp1[i].fs == m) {
            cout << dp1[i].sc + 1 << " " << i + 1 << endl;
            return 0;
        }
        if (dp2[i].fs == m) {
            cout << i + 1 << " " << dp2[i].sc + 1 << endl;
            return 0;
        }
        pii max1(-inf, -1), max2(-inf, -1);
        for (auto j : g[i]) {
            pii cur(dp2[j.fs].fs, j.fs);
            if (cur > max1) {
                max2 = max1;
                max1 = cur;
            } else {
                max2 = max(max2, cur);
            }
        }
        for (auto j : g[i]) {
            int len = dp1[j.fs].fs + (max1.sc == j.fs ? max2.fs : max1.fs);
            if (len >= m) {
                cout << dp1[j.fs].sc + 1 << " " << dp2[(max1.sc == j.fs ? max2.sc : max1.sc)].sc + 1 << endl;
                return 0;
            }
        }
    }
    cout << -1 << " " << -1 << endl;
    return 0;
}