#include <cstdio>

#define MAX_N 1000006
#define lchild l, m, v << 1
#define rchild m + 1, r, v << 1 | 1

typedef int ll;

int N, Q;
ll A[MAX_N];

const ll mod = 772002 + 233;

void add(ll &x, ll a){
	x = (x + a) % mod;
}

struct SegmentTree{
	struct node{
		ll coverTime;
		ll headNum;
	}tree[MAX_N * 4];

	SegmentTree();
	void build(int, int, int);
	void pushDown(int, int, int);
	void update(int, int, ll, int, int, int);
	ll query(int, int, int, int);
}seg;

SegmentTree::SegmentTree(){
	for(int i = 0; i < MAX_N * 4; i++)
		tree[i].coverTime = tree[i].headNum = 0;
}

void SegmentTree::build(int l = 1,int r = N, int v = 1){
	if(l == r){
		tree[v].headNum = A[l];
		return;
	}
	int m = (l + r) >> 1;
	build(lchild);
	build(rchild);
}

void SegmentTree::pushDown(int l, int r, int v){
	int m = (l + r) >> 1;
	add(tree[v << 1].coverTime, tree[v].coverTime);
	add(tree[v << 1 | 1].coverTime, tree[v].coverTime);
	add(tree[v << 1].headNum, tree[v].headNum);
	add(tree[v << 1 | 1].headNum, (tree[v].headNum - (m - l + 1) * tree[v].coverTime % mod) % mod);
	tree[v].coverTime = tree[v].headNum = 0; 
}

void SegmentTree::update(int L, int R, ll x, int l = 1, int r = N, int v = 1){
	if(L <= l && r <= R){
		add(tree[v].headNum, x - (l - L));
		add(tree[v].coverTime, 1);
		return;
	}
	if(tree[v].coverTime) pushDown(l, r, v);
	int m = (l + r) >> 1;
	if(L <= m) SegmentTree::update(L, R, x, lchild);
	if(R > m) SegmentTree::update(L, R, x, rchild);
} 

ll SegmentTree::query(int a, int l = 1, int r = N, int v = 1){
	if(l == r) 
		return (tree[v].headNum %mod + mod) % mod;
	if(tree[v].coverTime) pushDown(l, r, v);
	int m = (l + r) >> 1;
	if(a <= m) return SegmentTree::query(a, lchild);
	else return SegmentTree::query(a, rchild);
}

int main(){
	scanf("%d%d", &N, &Q);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		A[i] %= mod;
	}
	seg.build();
	while(Q--){
		int op, x, y;
		scanf("%d%d", &op, &x);
		if(op == 1){
			scanf("%d", &y);
			int z = x + y - 1 > N ? N : x + y - 1;
			seg.update(x, z, y);
		}
		else
			printf("%d\n", seg.query(x));
	}
	return 0;
}