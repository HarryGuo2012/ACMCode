#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAX_Q 50004
#define MAX_Z 100005

struct Ope {
	int x, y, z;
	int ty, id;
	Ope (int xx, int yy, int zz, int tt, int ii) : x(xx), y(yy), z(zz), ty(tt), id(ii) {}
	Ope () {}
};

bool cmp(Ope a, Ope b) {
	if (a.x == b.x) return a.id < b.id;
	return a.x < b.x;
}

bool cmp2(Ope a, Ope b) {
	if (a.y == b.y) return a.id < b.id;
	return a.y < b.y;
}

std::vector<Ope> ope, ope2, ope3;

int tree[MAX_Z];
int ans[MAX_Q];
bool isQuery[MAX_Q];

void update(int x, int a) {
	while (x < MAX_Z) {
		tree[x] += a;
		x += (x & (-x));
	}
}

int query(int x) {
	int res = 0;
	while (x) {
		res += tree[x];
		x -= (x & (-x));
	}
	return res;
}

void countStar() {
	for (int i = 0; i < ope3.size(); i++) {
		if (ope3[i].ty == 0) update(ope3[i].z, 1);
		else {
			int t = query(ope3[i].z);
			ans[ope3[i].id] += t * ope3[i].ty;
		}
	}
	for (int i = 0; i < ope3.size(); i++)
		if (ope3[i].ty == 0) update(ope3[i].z, -1);
}

void CDQ2(int L, int R) {
	if (L >= R) return;
	int mid = (L + R) >> 1;
	CDQ2(L, mid);
	ope3.clear();
	for (int i = L; i <= mid; i++)
		if (ope2[i].ty == 0) ope3.push_back(ope2[i]);
	for (int i = mid + 1; i <= R; i++)
		if (ope2[i].ty != 0) ope3.push_back(ope2[i]);
	std::sort(ope3.begin(), ope3.end(), cmp2);
	countStar();
	CDQ2(mid + 1, R);
}

void CDQ(int L, int R) {
	if (L >= R) return;
	int mid = (L + R) >> 1;
	CDQ(L, mid);
	ope2.clear();
	for (int i = L; i <= mid; i++) 
		if (ope[i].ty == 0) ope2.push_back(ope[i]);
	for (int i = mid + 1; i <= R; i++)
		if (ope[i].ty != 0) ope2.push_back(ope[i]);
	std::sort(ope2.begin(), ope2.end(), cmp);
	CDQ2(0, ope2.size() - 1);
	CDQ(mid + 1, R);
}

int T, Q;

std::vector<int> allZ;

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(isQuery, 0, sizeof(isQuery));
		memset(ans, 0, sizeof(ans));
		ope.clear();
		allZ.clear();
		memset(tree, 0, sizeof(tree));
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			int a;
			scanf("%d", &a);
			if (a == 1) {
				int x, y, z;
				scanf("%d%d%d", &x, &y, &z);
				ope.push_back(Ope(x, y, z, 0, i));
				allZ.push_back(z);
			}
			else {
				isQuery[i] = 1;
				int xa, ya, za, xb, yb, zb;
				scanf("%d%d%d%d%d%d", &xa, &ya, &za, &xb, &yb, &zb);
				ope.push_back(Ope(xa - 1, ya - 1, za - 1, -1, i));
				ope.push_back(Ope(xa - 1, ya - 1, zb, 1, i));
				ope.push_back(Ope(xa - 1, yb, za - 1, 1, i));
				ope.push_back(Ope(xa - 1, yb, zb, -1, i));
				ope.push_back(Ope(xb, ya - 1, za - 1, 1, i));
				ope.push_back(Ope(xb, ya - 1, zb, -1, i));
				ope.push_back(Ope(xb, yb, za - 1, -1, i));
				ope.push_back(Ope(xb, yb, zb, 1, i));
				allZ.push_back(za - 1);
				allZ.push_back(zb);
			}
		}
		std::sort(allZ.begin(), allZ.end());
		auto it = std::unique(allZ.begin(), allZ.end());
		allZ.resize(std::distance(allZ.begin(), it));
		for (int i = 0; i < ope.size(); i++)
			ope[i].z = std::lower_bound(allZ.begin(), allZ.end(), ope[i].z) - allZ.begin() + 1;
		CDQ(0, ope.size() - 1);
		for (int i = 0; i < Q; i++)
			if (isQuery[i]) printf("%d\n", ans[i]);
	}
	return 0;
}