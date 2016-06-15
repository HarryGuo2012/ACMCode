#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAX_N 100005

int cnt[MAX_N], a[MAX_N];
int tot = 0;

void update(int b, int x) {
	if (cnt[b] == 0) tot++;
	cnt[b] += x;
	if (cnt[b] == 0) tot--;
}

struct query {
	int l, r, val, idx;
}res[MAX_N];

int pos[MAX_N];

bool cmp(query x, query y) {
	if (pos[x.l] == pos[y.l]) return x.r < y.r;
	return x.l < y.l;
}

bool cmp2(query x, query y) {
	return x.idx < y.idx;
}

int Q;

void solve() {
	int l, r;
	l = r = 1;
	update(a[1], 1);
	for (int i = 1; i <= Q; ++i) {
		for( ; l < res[i].l; ++l) update(a[l], -1);
		for( ; l > res[i].l; --l) update(a[l - 1], 1);
		for( ; r < res[i].r; ++r) update(a[r + 1], 1);
		for( ; r > res[i].r; --r) update(a[r], -1);
		res[i].val = tot;
		//printf("%d %lld\n",res[i].id,val);
	}
}

int N;

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) 
		scanf("%d", &a[i]);
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d", &res[i].l, &res[i].r);
		res[i].idx = i;
	}
	int B = sqrt(N) + 1;
	for (int i = 1; i <= N; i++) pos[i] = i / B;
	std::sort(res + 1, res + 1 + Q, cmp);
	solve();
	std::sort(res + 1, res + 1 + Q, cmp2);
	for (int i = 1; i <= Q; i++)
		printf("%d\n", res[i].val);
	return 0;
}