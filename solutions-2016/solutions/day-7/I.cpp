#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>

#undef NDEBUG
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <deque>
#include <complex>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define mt make_tuple
#define fs first
#define sc second
#define sz(s) ((int) (s).size())
#define len(s) ((int) (s).size())
#define all(x) (x).begin(), (x).end()
#define next hunext
#define prev huprev
#define rank hurank
#define hash huhash
#ifdef LOCAL42
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#define cerr if (0) cerr
#endif
#if _WIN32 || __WIN32__ || _WIN64 || __WIN64__
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

typedef long long ll;
typedef long long llong;
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned long long ullong;
typedef unsigned long long lint;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;
typedef long double ldouble;

const int inf = 1e9;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);
const int N = int(5e5) + 10;
const int LOG = 20;

struct tans {
    
    int ans, left_pos, right_pos, left_len, right_len;
    
    
};

int n, maxv;
int mas[N], rmq[4 * N];
tans go_left[LOG][N], go_right[LOG][N];
unordered_map<int, int> prev;

inline tans merge(tans a, tans b) {
    tans c;
    c.ans = max(a.ans, b.ans);
    c.left_pos = a.left_pos;
    c.left_len = a.left_len;
    c.right_pos = b.right_pos;
    c.right_len = b.right_len;
    if (a.right_pos == b.left_pos) {
        c.ans = max(c.ans, a.right_len + b.left_len);
    }
    if (a.left_pos + a.left_len == b.left_pos) {
        c.left_len += b.left_len;
    }
    if (b.right_pos - b.right_len == a.right_pos) {
        c.right_len += a.right_len;
    }
    c.ans = max(c.ans, c.left_len);
    c.ans = max(c.ans, c.right_len);
    return c;
}

inline int get_max(int l, int r) {
    int res = -inf;
    l += maxv;
    r += maxv;
    while (l <= r) {
        res = max(res, rmq[l]);
        l = (l + 1) / 2;
        res = max(res, rmq[r]);
        r = (r - 1) / 2;
    }
    return res;
}

int main() {
#ifdef LOCAL42
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        scanf("%d", mas + i);
    }
    maxv = 1;
    while (maxv < n) {
        maxv *= 2;
    }
    for (int i = 0; i < n; ++i) {
        rmq[i + maxv] = mas[i];
    }
    for (int i = n; i < maxv; ++i) {
        rmq[i + maxv] = -inf;
    }
    for (int i = maxv - 1; i > 0; --i) {
        rmq[i] = max(rmq[i * 2], rmq[i * 2 + 1]);
    }
    for (int i = n - 1; i >= 0; --i) {
        if (prev.count(mas[i]) && get_max(i, prev[mas[i]]) == mas[i]) {
            int j = prev[mas[i]];
            tans c;
            c.ans = j - i;
            c.left_pos = i;
            c.left_len = j - i;
            c.right_pos = j;
            c.right_len = j - i;
            go_right[0][i] = c;
        } else {
            tans c;
            c.ans = 0;
            c.left_pos = i;
            c.left_len = 0;
            c.right_pos = i + 1;
            c.right_len = 0;
            go_right[0][i] = c;
        }
        prev[mas[i]] = i;
    }
    prev.clear();
    for (int i = 0; i < n; ++i) {
        if (prev.count(mas[i]) && get_max(prev[mas[i]], i) == mas[i]) {
            int j = prev[mas[i]];
            tans c;
            c.ans = i - j;
            c.left_pos = j;
            c.left_len = i - j;
            c.right_pos = i;
            c.right_len = i - j;
            go_left[0][i] = c;
        } else {
            tans c;
            c.ans = 0;
            c.left_pos = i - 1;
            c.left_len = 0;
            c.right_pos = i;
            c.right_len = 0;
            go_left[0][i] = c;
        }
        prev[mas[i]] = i;
    }
    for (int i = 1; i < LOG; ++i) {
        for (int j = 0; j < n; ++j) {
            go_right[i][j] = go_right[i - 1][j];
            if (go_right[i][j].right_pos < n) {
                go_right[i][j] = merge(go_right[i][j], go_right[i - 1][go_right[i][j].right_pos]);
            }
            go_left[i][j] = go_left[i - 1][j];
            if (go_left[i][j].left_pos >= 0) {
                go_left[i][j] = merge(go_left[i - 1][go_left[i][j].left_pos], go_left[i][j]);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        --l;
        --r;
        tans cur;
        cur.ans = 0;
        cur.left_pos = l;
        cur.left_len = 0;
        cur.right_pos = l;
        cur.right_len = 0;
        for (int j = LOG - 1; j >= 0; --j) {
            if (go_right[j][cur.right_pos].right_pos <= r) {
                cur = merge(cur, go_right[j][cur.right_pos]);
            }
        }
        int ans = cur.ans, g = cur.right_pos;
        cur.ans = 0;
        cur.left_pos = r;
        cur.left_len = 0;
        cur.right_pos = r;
        cur.right_len = 0;
        for (int j = LOG - 1; j >= 0; --j) {
            if (go_left[j][cur.left_pos].left_pos >= g) {
                cur = merge(go_left[j][cur.left_pos], cur);
            }
        }
        ans = max(ans, cur.ans);
        printf("%d\n", ans);
    }
    return 0;
}