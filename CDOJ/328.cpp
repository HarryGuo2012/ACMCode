#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#define INF LLONG_MAX

#define MAX_N 200005

int N;
int a[MAX_N];

typedef long long ll;

struct SegmentTree{
	struct node{
		ll mi, lazy;
		node() : mi(INF), lazy(0){}
	}tree[MAX_N * 4];

	#define lchild l, m, v << 1
	#define rchild m + 1, r, v << 1 | 1

	void pushUp(int v){
		tree[v].mi = std::min(tree[v << 1].mi, tree[v << 1 | 1].mi);
	}

	void pushDown(int v){
		tree[v << 1].lazy += tree[v].lazy;
		tree[v << 1 | 1].lazy += tree[v].lazy;
		tree[v << 1].mi += tree[v].lazy;
		tree[v << 1 | 1].mi += tree[v].lazy;
		tree[v].lazy = 0;
	}

	void build(int l = 1, int r = N, int v = 1){
		if(l == r){
			tree[v].mi = a[l];
			return;
		}
		int m = (l + r) >> 1;
		build(lchild);
		build(rchild);
		pushUp(v);
	}

	void update(int L, int R, ll x, int l = 1, int r = N, int v = 1){
		if(L <= l && r <= R){
			tree[v].lazy += x;
			tree[v].mi += x;
			return;
		}
		int m = (l + r) >> 1;
		if(tree[v].lazy) pushDown(v);
		if(L <= m) update(L, R, x, lchild);
		if(R > m) update(L, R, x, rchild);
		pushUp(v);
	}

	ll query(int L, int R, int l = 1, int r = N, int v = 1){
		if(L <= l && r <= R)
			return tree[v].mi;

		int m = (l + r) >> 1;
		if(tree[v].lazy) pushDown(v);

		ll res = INF;
		if(L <= m) res = std::min(res, query(L, R, lchild));
		if(R > m) res = std::min(res, query(L, R, rchild));
		return res;
	}
}seg;

std::vector<int> splitToInt(std::string s){
	std::istringstream iss(s);
	int a;
	std::vector<int> v;
	while(iss >> a)
		v.push_back(a);
	return v;
}

int main(){
	std::cin.sync_with_stdio(false);
	std::cin >> N;
	for(int i = 1; i <= N; i++)
		std::cin >> a[i];
	seg.build();
	int Q;
	std::cin >> Q;
	std::string s;
	std::getline(std::cin, s);
	while(Q--){
		std::getline(std::cin, s);
		std::vector<int> v = splitToInt(s);
		for(int i = 0; i < 2; i++)
			v[i]++;
		if(v.size() == 3){
			if(v[0] <= v[1])
				seg.update(v[0], v[1], v[2]);
			else{
				seg.update(v[0], N, v[2]);
				seg.update(1, v[1], v[2]);
			}
		}
		else{
			if(v[0] <= v[1])
				std::cout << seg.query(v[0], v[1]) << std::endl;
			else
				std::cout << std::min(seg.query(1, v[1]), seg.query(v[0], N)) << std::endl;
		}
	}
	return 0;
}