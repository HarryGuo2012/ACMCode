#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 16;
int n, m, k;
int map[maxn][maxn], Fa[maxn];
int f[1<<maxn], num[maxn], me[1<<maxn], s[1<<maxn];
bool vis[maxn], vis2[maxn];

int Find(int x) {
	if(Fa[x] == x) return x;
	return Fa[x] = Find(Fa[x]);
}

void update(int &x,int y) {
	if(x) x = min(x, y);
	else x = y;
}

int main() {
	scanf("%d%d%d",&n,&m,&k);
	if(k == 0) {
		printf("%d\n",  m);
		return 0;
	}
	for(int i = 1; i <= n; i++) Fa[i] = i;
	int u, v;
	for(int i = 0; i < m; i++) {
		scanf("%d%d",&u,&v);
		u--; v--;
		if(u == v) continue;
		map[u][v] = map[v][u] = 1;
		f[(1<<u)|(1<<v)] = 1;
	}
	for(int i = 0; i < k; i++) {
		scanf("%d%d",&u,&v);
		vis2[u] = vis2[v] = true;
		if(Find(u) != Find(v)) {
			Fa[Find(v)] = Find(u);
		}
	}
	int maxst = 1<<n;
	for(int i = 0; i < maxst; i++) if(f[i]) {
		for(u = 0; u < n; u++) if(i & (1<<u)) {
			for(v = 0; v < n; v++) if((!(i & (1<<v))) && map[u][v])
				update(f[i|(1<<v)], f[i]+1);
		}
	}
	int cnt = 0, resme = 0;
	for(int i = 1; i <= n; i++) {
		if(!vis[Find(i)]) {
			vis[Find(i)] = true;
			num[Find(i)] = cnt++;
		}
		if(vis2[i]) resme |= 1<<num[Find(i)];
		me[1<<num[Find(i)]] |= 1<<(i-1);
	}
	int maxc = 1<<cnt, res = 0x3f3f3f3f;
	for(int i = 1; i < maxc; i++) {
		if(i&(i-1)) me[i] = me[i&(i-1)] | me[i^(i&(i-1))];
		s[i] = f[me[i]];
		for(int j = i&(i-1); j; j = i&(j-1)) {
			int t = i^j;
			if(s[t] && s[j]) update(s[i], s[t]+s[j]);
		}
		if(((i^resme) & resme) == 0 && s[i]) update(res, s[i]);
	}
	printf("%d\n",res==0x3f3f3f3f?-1:m-res);
	
	return 0;
}