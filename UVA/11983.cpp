#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAX_N 30004

int leaf[MAX_N << 2];
int K, N;

int MAXY;

struct SegmentTree {
	struct node {
		int cover, siz;
		int cnt[12];
	}Tree[MAX_N << 4];

#define lchild l, m, v << 1
#define rchild m + 1, r, v << 1 | 1

	void build(int l = 1, int r = MAXY, int v = 1) {
		if (l == r) {
			Tree[v].siz = leaf[l];
			Tree[v].cnt[0] = leaf[l];
			return;
		}
		int m = (l + r) >> 1;
		build(lchild);
		build(rchild);
		Tree[v].siz = Tree[v << 1].siz + Tree[v << 1 | 1].siz;
		Tree[v].cnt[0] = Tree[v << 1].cnt[0] + Tree[v << 1 | 1].cnt[0];
	}

	void init() {
		memset(Tree, 0, sizeof(Tree));
		build();
	}

	void pushUp(int l, int r, int v) {
		if (l == r) {
			Tree[v].cnt[std::min(Tree[v].cover, K)] = Tree[v].siz;
			return;
		}
		int extra = Tree[v].cover;
		for (int i = 0; i <= K; i++)
			Tree[v].cnt[std::min(extra + i, K)] += Tree[v << 1].cnt[i] + Tree[v << 1 | 1].cnt[i];
	}

	void update(int L, int R, int x, int l = 1, int r = MAXY, int v = 1) {
		memset(Tree[v].cnt, 0, sizeof(Tree[v].cnt));
		if (L <= l && r <= R) {
			Tree[v].cover += x;
			pushUp(l, r, v);
			return;
		}
		int m = (l + r) >> 1;
		if (L <= m) update(L, R, x, lchild);
		if (R > m) update(L, R, x, rchild);
		pushUp(l, r, v);
	}

	int query(int L, int R, int l = 1, int r = MAXY, int v = 1) {
		if (L <= l && r <= R)
			return Tree[v].cnt[K];
		int m = (l + r) >> 1, res = 0;
		if (L <= m) res += query(L, R, lchild);
		if (R > m) res += query(L, R, rchild);
		return res;
	}
}seg;

int T;

struct Line {
	int flag;
	int x, ya, yb;
	Line(int xx, int yya, int yyb, int ff) : x(xx), ya(yya), yb(yyb), flag(ff) { }
	Line() { }
};

bool cmp(Line a, Line b) {
	if (a.x == b.x)
		return a.flag > b.flag;
	return a.x < b.x;
}

std::vector<Line> Li;
std::vector<int> allY;

int main() {
	int cas = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &K);
		Li.clear();
		allY.clear();
		memset(leaf, 0, sizeof(leaf));
		for (int i = 1; i <= N; i++) {
			int xa, ya, xb, yb;
			scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
			xb++, yb++;
			//if (xa == xb || ya == yb || za == zb) continue;

			allY.push_back(ya);
			allY.push_back(yb);
			Li.push_back(Line(xa, ya, yb - 1, 1));
			Li.push_back(Line(xb, ya, yb - 1, -1));
		}

		if (allY.size() == 0) {
			printf("0\n");
			continue;
		}

		std::sort(allY.begin(), allY.end());
		auto it = std::unique(allY.begin(), allY.end());
		allY.resize(std::distance(allY.begin(), it));
		for (int i = 0; i < allY.size() - 1; i++)
			leaf[i + 1] = allY[i + 1] - allY[i];

		MAXY = allY.size();
		long long ans = 0;

		seg.init();
		std::sort(Li.begin(), Li.end(), cmp);
		for (int i = 0; i < Li.size(); i++) {
			Li[i].ya = std::lower_bound(allY.begin(), allY.end(), Li[i].ya) - allY.begin() + 1;
			Li[i].yb = std::lower_bound(allY.begin(), allY.end(), Li[i].yb + 1) - allY.begin();
		}

		for (int i = 0; i < Li.size(); i++) {
			if (i != 0) 
				ans += (long long)(seg.query(1, MAXY)) * (Li[i].x - Li[i - 1].x);
			seg.update(Li[i].ya, Li[i].yb, Li[i].flag);
		}

		printf("Case %d: %lld\n", ++cas, ans);
	}
	return 0;
}