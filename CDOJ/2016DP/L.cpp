#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 100005

struct node {
	int x, v, y;
}a[MAX_N];

bool cmp(node u, node v) {
	return u.x < v.x;
}

int N;
std::vector<int> ve;

typedef long long ll;
ll dp[MAX_N];
ll ans;

struct SegmentTree {
	ll tree[MAX_N * 4];
	void pushUp(int v) {
		tree[v] = std::max(tree[v << 1], tree[v << 1 | 1]);
	}

	#define lchild l, m, v << 1
	#define rchild m + 1, r, v << 1 | 1

	void update(int x, ll a, int l = 1, int r = N, int v = 1) {
		if (l == r) {
			tree[v] = std::max(tree[v], a);
			return;
		}
		int m = (l + r) >> 1;
		if (x <= m) update(x, a, lchild);
		else update(x, a, rchild);
		pushUp(v);
	}

	ll query(int L, int R, int l = 1, int r = N, int v = 1) {
		if (L <= l && r <= R) 
			return tree[v];
		int m = (l + r) >> 1;
		ll res = 0;
		if (L <= m) res = std::max(query(L, R, lchild), res);
		if (R > m) res = std::max(query(L, R, rchild), res);
		return res; 
	}
}seg;

int main() {
	scanf("%d", &N);
	ve.push_back(0);
	for (int i = 1; i <= N; i++) {
		scanf("%d%d%d", &a[i].x, &a[i].v, &a[i].y);
		ve.push_back(a[i].x);
	}
	std::sort(ve.begin(), ve.end());
	auto it = std::unique(ve.begin(), ve.end());
	ve.resize(std::distance(ve.begin(), it));
	for (int i = 1; i <= N; i++) {
		int L = std::lower_bound(ve.begin(), ve.end(), std::max(a[i].x - a[i].y, 1)) - ve.begin();
		int R = std::upper_bound(ve.begin(), ve.end(), a[i].x) - ve.begin() - 1;
		//printf("%d %d\n", L, R);
		dp[i] = seg.query(L, R) + a[i].v;
		seg.update(R, dp[i]);
		ans = std::max(ans, dp[i]);
	}
	printf("%lld\n", ans);
	return 0;
}