#include <cstdio>
#include <cmath>

#define MAX_N 100005

int n;
double maxAB[MAX_N], minAB[MAX_N];
double a[MAX_N], b[MAX_N];

double sumA[MAX_N], sumB[MAX_N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &maxAB[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &minAB[i]);
	for (int i = 1; i <= n; i++) {
		double p0 = maxAB[i] + minAB[i];
		double B = sumB[i - 1] - sumA[i - 1] + p0;
		double C = p0 * sumA[i - 1] - maxAB[i];
		//printf("%.3f %.3f %.3f\n", B, C, -B + sqrt(B * B + 4 * C));
		//printf("%.3f\n",  a[i]);
		double t = B * B + 4 * C;
		if (t < 0) t = 0;
		a[i] = (-B + sqrt(t)) / (-2.0);
		//printf("%.3f\n",  a[i]);
		b[i] = p0 - a[i];
		sumA[i] = sumA[i - 1] + a[i];
		sumB[i] = sumB[i - 1] + b[i];
	}
	for (int i = 1; i <= n; i++)
		printf("%.7f ", a[i]);
	printf("\n");
	for (int i = 1; i <= n; i++)
		printf("%.7f ", b[i]);
	printf("\n");
	return 0;
}