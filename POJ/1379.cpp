#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define INF 1e100

#define MAX_N 1003

struct Point {
	double x, y;
	Point(double xx, double yy) : x(xx), y(yy) {}
	Point() {}
	double norm() {
		return x * x + y * y;
	}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	void output() {
		printf("The safest point is (%.1f, %.1f).\n", x, y);  
	}
	Point operator + (Point a) {
		return Point(x + a.x, y + a.y);
	}
	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}
	friend Point operator * (Point a, double b) {
		return Point(a.x * b, a.y * b);
	}
};

double drand() {
	return rand() % 10000 / 10000.0;
}

double r = 0.99140142;
int N;

double distance(Point a, Point b) {
	return (a - b).norm();
}

Point P[MAX_N];

int T;

double Estimate(Point S) {
	double dis = INF;
	for (int i = 1; i <= N; i++)
		dis = std::min(distance(S, P[i]), dis);
	return -dis;
}

Point Nei(Point S, double Te) {
	return S + Point(drand() * 2 - 1.0, drand() * 2 - 1.0) * Te;
}

double X, Y;
const double eps = 1e-9;

Point SimulatedAnnealing(Point S, double Te) {
	double E = Estimate(S);
	while (Te > eps) {
		Point nS = Nei(S, Te);
		nS.x = std::min(std::max(nS.x, 0.0), X), nS.y = std::min(std::max(nS.y, 0.0), Y);
		double nE = Estimate(nS);
		double dE = nE - E;
		if (dE < 0 || drand() < exp(-dE / Te)) 
			S = nS, E = nE;
		Te *= r;
	}
	return S;
}

int main() {
	srand(time(0));
	scanf("%d", &T);
	while (T--) {
		scanf("%lf%lf%d", &X, &Y, &N);
		for (int i = 1; i <= N; i++)
			P[i].input();
		Point S = Point(X / 2.0, Y / 2.0);
		S = SimulatedAnnealing(S, std::max(X , Y) / 2);
		S.output();
	}
	return 0;
}