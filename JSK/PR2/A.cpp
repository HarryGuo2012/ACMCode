#include <cstdio>
#include <cmath>

double t, l1, l2;

double Get(double x) {
	x = x / 180 * acos(-1);
	return x;
}

double sqr(double x) {
	return x * x;
}

int main() {
	scanf("%lf%lf%lf", &l1, &l2, &t);
	t = Get(t);
	double xa = l1, ya = 0;
	double xb = l2 * cos(t), yb = l2 * sin(t);
	double R = sqr(xa / 2 - xb / 2) + sqr(ya / 2 - yb / 2);
	R = sqrt(R);
	R += l1 / 2 + l2 / 2;
	R /= 2;
	printf("%.7f\n", R * R * acos(-1));
	return 0;
}