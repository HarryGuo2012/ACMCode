#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAX_N 100005
#define MAX_K 12

typedef long long ll;

ll N, K;

ll MAXY;
ll leaves[MAX_N << 2];

struct SegmentTree {
	struct Node {
		ll cover, length;
		ll cnt[MAX_K];
	} tree[MAX_N << 4];

#define lchild l, m, v << 1
#define rchild m + 1, r, v << 1 | 1

	void build (int l = 1, int r = MAXY, int v = 1) {
		tree[v].cover = 0;
		memset(tree[v].cnt, 0, sizeof(tree[v].cnt));
		if (l == r) {
			tree[v].length = leaves[l];
			return;
		}
		int m = (l + r) >> 1;
		build(lchild);
		build(rchild);
		tree[v].length = tree[v << 1].length + tree[v << 1 | 1].length;
	}

	void pushUp (int l, int r, int v) {
		if (l == r) 
			tree[v].cnt[std::min(tree[v].cover, K + 1)] = tree[v].length;
		else {
			ll extra = tree[v].cover;
			for (int i = 0; i <= K + 1; i++)
				tree[v].cnt[std::min(extra + i, K + 1)] = tree[v << 1].cnt[i] + tree[v << 1 | 1].cnt[i];
		}
	}

	void update (int L, int R, int x, int l = 1, int r = MAXY, int v = 1) {
		memset(tree[v].cnt, 0, sizeof(tree[v].cnt));
		if (L <= l && r <= R) 
			tree[v].cover += x;
		else {
			int m = (l + r) >> 1;
			if (L <= m) update(L, R, x, lchild);
			if (R > m) update(L, R, x, rchild);
		}
		pushUp(l, r, v);
	}

	ll query (int L, int R, int l = 1, int r = MAXY, int v = 1) {
		if (L <= l && r <= R)
			return tree[v].cnt[K];
		int m = (l + r) >> 1;
		ll res = 0 ;
		if (L <= m) res += query(L, R, lchild);
		if (R > m) res += query(L, R, rchild);
	}
}seg;

struct Line {
	int flag;
	int x, ya, yb;
	Line (int xx, int yya, int yyb, int ff) : x(xx), ya(yya), yb(yyb), flag(ff) { }
	Line () { }
};

bool cmp(Line a, Line b) {
	if (a.x == b.x)
		return a.flag > b.flag;
	return a.x < b.x;
}

std::vector<Line> Li[4];
std::vector<int> allY;

int main() {
	scanf("%lld%lld", &N, &K);
	for (int i = 1; i <= N; i++) {
		int xa, ya, xb, yb, za, zb;
		scanf("%d%d%d%d%d%d", &xa, &ya, &za, &xb, &yb, &zb);
		if (xa == xb || ya == yb || za == zb) continue;

		allY.push_back(ya);
		allY.push_back(yb);
		for (int z = za; z < zb; z++) {
			Li[z].push_back(Line(xa, ya, yb - 1, 1));
			Li[z].push_back(Line(xb, ya, yb - 1, -1));
		}
	}

	if (allY.size() == 0) {
		printf("0\n");
		return 0;
	}

	std::sort(allY.begin(), allY.end());
	auto it = std::unique(allY.begin(), allY.end());
	allY.resize(std::distance(allY.begin(), it));
	for (int i = 0; i < allY.size() - 1; i++)
		leaves[i + 1] = allY[i + 1] - allY[i];

	MAXY = allY.size();
	ll ans = 0;

	for (int z = 1; z <= 2; z++) {
		seg.build();
		std::sort(Li[z].begin(), Li[z].end(), cmp);
		for (int i = 0; i < Li[z].size(); i++) {
			Li[z][i].ya = std::lower_bound(allY.begin(), allY.end(), Li[z][i].ya) - allY.begin() + 1;
			Li[z][i].yb = std::lower_bound(allY.begin(), allY.end(), Li[z][i].yb + 1) - allY.begin();
		}
		for (int i = 0; i < Li[z].size(); i++) {
			if (i != 0)
				ans += seg.query(1, MAXY) * (Li[z][i].x - Li[z][i - 1].x);
			seg.update(Li[z][i].ya, Li[z][i].yb, Li[z][i].flag);
		}
	}

	printf("%lld\n", ans);
	return 0;
}