#include <cstdio>
#include <algorithm>
#include <vector>

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
	Update(R, mid + 1, r);
	for (int i = r; i >= mid + 1; i--) 
		if (Op[i].t == 2 && Op[i].q < M) nowPoint.push_back(Op[Op[i].q]].p);
	
}

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);

	nowPoint.clear();
	se.clear();
	for (int i = l; i <= mid; i++) {
		if (Op[i].t == 1) se.insert(i);
		if (Op[i].t == 2) se.erase(i);
	}
	for (auto u : se)
		tmpPoint.push_back(Op[*u].p);
	Update(mid + 1, r, mid + 1, r);
	cdq(mid + 1, r);
}

int main() {
	return 0;
}