#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <climits>

#define INF (LLONG_MAX - 5)

typedef long long ll;

struct Point {
	ll x, y;
	Point(ll xx, ll yy) : x(xx), y(yy) {}
	Point() {}

	Point operator + (Point a) {
		return Point(x + a.x, y + a.y);
	}

	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}

	ll operator * (Point a) {
		return x * a.x + y * a.y;
	}

	ll operator ^ (Point a) {
		return x * a.y - y * a.x;
	}
};

bool cmp(Point a, Point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

#define MAX_Q 300005

struct Ope {
	int t;
	ll q;
	Point p;
	Ope() {}
}Op[MAX_Q];

std::vector<Point> tmpPoint, nowPoint;
std::set<int> se;

ll res[MAX_Q];

int st[MAX_Q], top = 0;

void build() {
	std::sort(nowPoint.begin(), nowPoint.end(), cmp);
	top = 0;
	for (int i = 0; i < nowPoint.size(); i++) {
		while (top > 1 && ((nowPoint[st[top]] - nowPoint[st[top - 1]]) ^ (nowPoint[i] - nowPoint[st[top]])) > 0) top--;
		st[++top] = i;
	}
}

ll Get(ll q, int i) {
	return nowPoint[st[i]].x * q + nowPoint[st[i]].y;
}

void Query(int t) {
	if (top == 1) {
		res[t] = std::max(res[t], Get(Op[t].q, top));
		return;
	}
	if (Get(Op[t].q, top) > Get(Op[t].q, top - 1)) {
		res[t] = std::max(res[t], Get(Op[t].q, top));
		return;
	}
	int l = 1, r = top;
	while (r - l > 1) {
		int l1 = (r - l) / 3 + l;
		int r1 = 2 * (r - l) / 3 + l;
		if (Get(Op[t].q, r1) < Get(Op[t].q, l1)) r = r1;
		else l = l1;
	}
	res[t] = std::max(res[t], Get(Op[t].q, l));
}

void Update(int M, int R, int l, int r) {
	nowPoint.clear();
	if (r == R) nowPoint = tmpPoint;
	if (l == r) {
		if (r == R && Op[l].t == 3) {
			build();
			Query(l);
		}
		return;
	}
	int mid = (l + r) >> 1;
	Update(M, R, mid + 1, r);
	for (int i = r; i >= mid + 1; i--) 
		if (Op[i].t == 2 && Op[i].q < M) nowPoint.push_back(Op[Op[i].q].p);
	build();
	for (int i = l; i <= mid; i++)
		if (Op[i].t == 3)
			Query(i);
	Update(M, R, l, mid);
}

int rid[MAX_Q];

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);

	nowPoint.clear();
	se.clear();
	for (int i = l; i <= mid; i++) {
		if (Op[i].t == 1 && rid[i] <= mid) se.insert(i);
		if (Op[i].t == 2) se.erase(i);
	}
	for (auto u : se)
		tmpPoint.push_back(Op[u].p);
	Update(mid + 1, r, mid + 1, r);
	cdq(mid + 1, r);
}

int N;

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) res[i] = -INF;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &Op[i].t);
		if (Op[i].t == 1) scanf("%I64d%I64d", &Op[i].p.x, &Op[i].p.y);
		if (Op[i].t == 2 || Op[i].t == 3) {
			scanf("%I64d", &Op[i].q);
			if (Op[i].t == 2) rid[Op[i].q] = i;
		}
	}
	cdq(1, N);
	for (int i = 1; i <= N; i++) {
		if (Op[i].t != 3) continue;
		if (res[i] == -INF) printf("EMPTY SET\n");
		else printf("%I64d\n", res[i]);
	}
	return 0;
}