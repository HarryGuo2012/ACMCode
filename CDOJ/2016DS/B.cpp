#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAX_Q 100005
#define MAX_N (2 * MAX_Q)

int leaves[MAX_N], N;

struct SegmentTree {
	struct Node {
		bool lazy;
		int sum;
	} tree[MAX_N * 4];

	#define lchild l, m, v << 1
	#define rchild m + 1, r, v << 1 | 1

	void pushUp (int v) {
		tree[v].sum = tree[v << 1].sum + tree[v << 1 | 1].sum;
	}

	void pushDown (int v) {
		tree[v << 1].sum = tree[v << 1 | 1].sum = 0;
		tree[v << 1].lazy = tree[v << 1 | 1].lazy = 1;
		tree[v].lazy = 0;
	}

	void build (int l = 1, int r = N, int v = 1) {
		tree[v].lazy = 0;
		if (l == r) {
			tree[v].sum = leaves[l];
			return;
		}
		int m = (l + r) >> 1;
		build(lchild);
		build(rchild);
		pushUp(v);
	}

	int query (int L, int R, int l = 1, int r = N, int v = 1) {
		if (L <= l && r <= R) return tree[v].sum;
		if (tree[v].lazy) pushDown(v);
		int m = (l + r) >> 1, res = 0;
		if (L <= m) res += query(L, R, lchild);
		if (R > m) res += query(L, R, rchild);
		return res;
	}

	void update (int L, int R, int l = 1, int r = N, int v = 1){
		if(L <= l && r <= R) {
			tree[v].lazy = 1;
			tree[v].sum = 0;
			return;
		}
		if(tree[v].lazy) pushDown(v);
		int m = (l + r) >> 1;
		if (L <= m) update(L, R, lchild);
		if (R > m) update(L, R, rchild);
		pushUp(v);
	}
}seg;

int Q;

struct Quer {
	int ty, x, y;
};

std::vector<Quer> vq;
std::vector<int> v;

int main(){
	scanf("%d%d", &N, &Q);
	for (int i = 0; i < Q; i++) {
		Quer qu;
		scanf("%d%d%d", &qu.ty, &qu.x, &qu.y);
		vq.push_back(qu);
		v.push_back(qu.x);
		v.push_back(qu.y + 1);
	}

	std::sort(v.begin(), v.end());
	auto it = std::unique(v.begin(), v.end());
	v.resize(std::distance(v.begin(), it));
	for (int i = 0; i < v.size() - 1; i++)
		leaves[i + 1] = v[i + 1] - v[i];

	N = v.size();
	seg.build();

	for (int i = 0; i < vq.size(); i++) {
		vq[i].x = std::lower_bound(v.begin(), v.end(), vq[i].x) - v.begin() + 1;
		vq[i].y = std::lower_bound(v.begin(), v.end(), vq[i].y + 1) - v.begin();
	}	

	for (int i = 0; i < vq.size(); i++) {
		if (vq[i].ty == 1) 
			seg.update(vq[i].x, vq[i].y);
		else
			printf("%d\n", seg.query(vq[i].x, vq[i].y));
	}
	
	return 0;
}