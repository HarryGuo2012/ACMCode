#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000000 + 10, M = N / 2;

//z[i]表示s[i..n-1]和s[0..m-1]的最长前缀
void calcZ(char *s, int n, int z[]) {
  memset(z, 0, sizeof(z[0]) * n);
  for (int i=1,x=0,y=0;i<n;++i) {
    if (i<=y) z[i]=min(y-i,z[i-x]);
    while (i+z[i]<n&&s[i+z[i]]==s[z[i]]) z[i]++;
    if (y<=i+z[i]) x=i,y=i+z[i];
  }
  z[0] = n;
}

char s[M], t[M], tmp[N];
int ex[M], za[N], zb[N];
LL sum[M];
int q, n, m;

inline LL calc(int n, int l) {
  int i = upper_bound(ex, ex + n, l) - ex;
  return sum[i] + LL(n - i) * l;
}

int main() {
  while (scanf("%d%d%d", &n, &m, &q) == 3) {
    scanf("%s%s", s, t);
    
    memcpy(tmp, t, sizeof(char) * m); tmp[m] = '#';
    memcpy(tmp + m + 1, s, sizeof(char) * n); tmp[n + m + 1] = 0;
    calcZ(tmp, n + m + 1, za); za[0] = m;
    reverse_copy(s, s + n, tmp); tmp[n] = '#';
    reverse_copy(t, t + m, tmp + n + 1); tmp[n + m + 1] = 0;
    calcZ(tmp, n + m + 1, zb); zb[0] = n;
    reverse(zb, zb + n + m + 1);
    
    memset(ex, 0, sizeof(int) * n);
    for (int i = 1; i < n + m + 1; ++ i) if (za[i]) {
      int l = zb[i - 1];
      ex[n - l] = max(ex[n - l], za[i]);
    }
    for (int i = 1; i < n; ++ i) ex[i] = max(ex[i], ex[i - 1]);
    for (int i = 1; i <= n; ++ i) sum[i] = sum[i - 1] + ex[i - 1];
    for (int i = 1; i <= q; ++ i) {
      int ls, rs, lt, rt;
      scanf("%d%d%d%d", &ls, &rs, &lt, &rt);
      LL ret = calc(rs, rt) - calc(rs, lt - 1) - calc(ls - 1, rt) + calc(ls - 1, lt - 1);
      printf("%lld\n", ret);
    }
  }
  return 0;
}