#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_N 1000006
using namespace std;

int n, m;
int a[MAX_N];

struct node {
	int pos, val;
	node(int pp, int vv) : pos(pp), val(vv){}
	node() {}
	bool operator < (const node& y) const {
		return val < y.val;
	}
	
}b[MAX_N];

std::vector<int> v;
int dp[MAX_N];

int tree[MAX_N];

void update(int x, int a) {
	while (x < MAX_N) {
		tree[x] = std::max(tree[x], a);
		x += x & (-x);
	}
}

int query(int x) {
	int res = 0;
	while (x > 0) {
		res = std::max(res, tree[x]);
		x -= x & (-x);
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	std::swap(n, m);
	for (int j = 1; j <= m; j++) {
		scanf("%d", &b[j].val);
		b[j].pos = j;
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	std::sort(b + 1, b + 1 + m);
	for (int i = 1; i <= n; i++) {
		int tmp = std::lower_bound(b + 1, b + 1 + m, node(0, a[i])) - b;
		if (tmp <= m && b[tmp].val == a[i]) 
			v.push_back(b[tmp].pos);
	}

	for (int i = 0; i < v.size(); i++) {
		dp[i] = query(v[i] - 1) + 1;
		update(v[i], dp[i]);
	}

	int ans = 0;

	for (int i = 0; i < v.size(); i++)
		ans = std::max(ans, dp[i]);

	printf("%d\n", ans + 1);
	return 0;
}