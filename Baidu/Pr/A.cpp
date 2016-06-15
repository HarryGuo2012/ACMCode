#include <cstdio>
#include <cstring>
#include <algorithm>
int x, m, k, c;

#define MAX_N 40004

int vis[MAX_N];

int main() {
	int T;
	scanf("%d", &T);
	int a, b;
	for (int cas = 1; cas <= T; cas++) {
		memset(vis, 0, sizeof(vis));
		scanf("%d%d%d%d", &x, &m, &k, &c);
		int t = 0, L;
		for (int i = 1; i < 40004; i++) {
			t = (t * 10 + x) % k;
			if (vis[t]) {
				L = i - vis[t];
				a = vis[t] - 1;
				break; 
			}
			vis[t] = i;
		}
		m--;
		m = (m - a) % L + a;
		//printf("%d %d %d\n", a, L, m);
		t = 0;
		for (int i = 0; i <= m; i++) 
			t = (t * 10 + x) % k;
		bool flag = (t == c);
		printf("Case #%d:\n", cas);
		if (flag)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}