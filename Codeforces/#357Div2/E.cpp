#include <cstdio>
#include <cmath>

const double pi = acos(-1);

double sqr(double x) {
	return x * x;
}

struct Point {
	double x, y;
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	Point(double xx, double yy) : x(xx), y(yy) {}
	Point() {}
	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}
	double operator * (Point a) {
		return x * a.x + y * a.y;
	}
	Point operator ^ (Point a) {
		return x * a.y - y * a.x;
	}
	double norm() {
		return sqrt(sqr(x) + sqr(y));
	}
	double Angle() {
		return acos((*this) * Point(1, 0)/ (*this).norm());
	}
};

int N;
double v , T;

Point p0;

int main() {
	p0.input();
	scanf("%lf%lf", &v, &T);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		Point c;
		double r;
		c.input();
		scanf("%lf", &r);
		c = c - p0;
		double a = c.Angle(), b = asin(r / c.norm);
		double s = a - b, t = a + b;
	}
	return 0;
}