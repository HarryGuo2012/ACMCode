#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1005;

struct vt {
	double x, y;
	vt(double _x, double _y) {
		x = _x, y = _y;
	}
	friend double operator ^(vt a, vt b) {
		return a.x * b.y - b.x * a.y;
	}
	friend double operator *(vt a, vt b) {
		return a.x * b.x + a.y * b.y;
	}
	friend vt operator -(vt a, vt b) {
		return vt(a.x - b.x, a.y - b.y);
	}
	friend vt operator +(vt a, vt b) {
		return vt(a.x + b.x, a.y + b.y);
	}
	double ang() {
		return atan2(y, x);
	}
	vt(){}
	friend bool operator <(vt a, vt b) {
		if (fabs(a.ang() - b.ang()) < 1e-11)
			return a * a < b * b;
		else
			return (a ^ b) >= 0;
	}
	vt norm() {
		double d = sqrt(x * x + y * y);
		return vt(x / d, y / d);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	friend vt operator *(vt v, double k) {
		return vt(v.x * k, v.y * k);
	}
};

vt P[N];
double R[N];

int w, h, n;

void build_piece(int id) {
	vector<vt> hull;
	hull.emplace_back(-1.0 / P[id].x, 0);
	hull.emplace_back(0, -1.0 / P[id].y);
	hull.emplace_back(1.0 / (w - P[id].x), 0);
	hull.emplace_back(0, 1.0 / (h - P[id].y));
	for (int i = 0; i < n; i++) {
		if (i == id)
			continue;
		double d = (P[i] - P[id]).abs();
		hull.push_back((P[i] - P[id]).norm() * (2.0 * d / (d * d + R[id] * R[id] - R[i] * R[i])));
	}
	int delta_i = -1;
	for (int i = 0; i < (int)hull.size(); i++)
		if (delta_i == -1 || hull[delta_i].y > hull[i].y)
			delta_i = i;
	rotate(hull.begin(), hull.begin() + delta_i, hull.end());
	vt delta = hull[0];
	for (vt& v : hull)
		v = v - delta;
	stable_sort(hull.begin() + 1, hull.end());
	int pt = 0;
	for (int i = 0; i < hull.size(); i++) {
		while (pt >= 2) {
			vt a = hull[pt - 2], b = hull[pt - 1], c = hull[i];
			if (((b - a) ^ (c - b)) <= 0)
				--pt;
			else
				break;
		}
		hull[pt++] = hull[i];
	}
	hull.resize(pt);
	for (int i = 0; i < hull.size(); i++) {
		vt a = hull[i], b = hull[(i + 1) % hull.size()], c = hull[(i + 2) % hull.size()];
	}
	for (vt& v : hull)
		v = v + delta;
	vector<vt> res;
	for (int i = 0; i < hull.size(); i++) {
		vt a = hull[i], b = hull[(i + 1) % hull.size()];
		double vp = a ^ b;
		vt v = P[id] + vt((b.y - a.y) / vp, (a.x - b.x) / vp);
		if (i == 0 || ((v - res.front()).abs() > 1e-4 && (v - res.back()).abs() > 1e-4))
			res.push_back(v);
	}
	printf("%d\n", (int)res.size());
	for (vt v : res)
		printf("%.10lf %.10lf\n", v.x, v.y);
}

int main() {
	scanf("%d %d %d", &w, &h, &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf %lf", &P[i].x, &P[i].y, &R[i]);
	}
	for (int i = 0; i < n; i++) {
		build_piece(i);
	}
}
